#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <errno.h>
#include <stdlib.h>
#include <signal.h>

#include "apdu.h"
#include "wic.h"
#include "wic_transport.h"
#include "wic_utils.h"
#include "log.h"

static struct wic_inst inst;
struct wic_init_arg arg;
static int s;
static APDU_t* apdu;

void
ws_recvCmd(void)
{
	if (!transport_recv(s, &inst)) {
		fprintf(stderr, "ERROR: failed to receive data.\n");
		exit(EXIT_FAILURE);
	}

	memcpy(apdu->buffer, inst.rx.s.read, inst.rx.s.pos);
	apdu->sendLength = 0x00;
}

void
ws_recvData(void)
{
	/* Nothing to do for WebSocket, because in contrast to T0, the ws_recvCmd()
	 * function fetches both the command header and the data buffer at a time. */
}

void
ws_sendData(uint8_t* data, uint16_t length)
{
	memcpy(apdu->buffer + apdu->sendLength, data, length);
	apdu->sendLength += length;
}

void
ws_sendSW(uint16_t sw)
{
	apdu->SW = sw;
	apdu->buffer[apdu->sendLength] = apdu->SW >> 8;
	apdu->buffer[apdu->sendLength + 1] = apdu->SW & 0xFF;
	apdu->sendLength += 2;

	wic_printAnswer((const void*)apdu->buffer, apdu->sendLength);
	wic_send_binary(&inst, true, (const void*)apdu->buffer, apdu->sendLength);

	memset(apdu->buffer, 0x00, APDU_COMMAD_LENGTH + APDU_DATA_LENGTH);
	apdu->sendLength = 0x00;
}


////////////////////////////// WebSocket specific handlers ///////////////////////////////

static bool
on_message_handler(struct wic_inst *inst, enum wic_encoding encoding, bool fin, const char *data, uint16_t size)
{
    if (encoding == WIC_ENCODING_UTF8) {
        LOG("<< %.*s", size, data);
    } else {
		wic_printCommand((const void*)data, size);
	}

    return true;
}

static void
on_handshake_failure_handler(struct wic_inst *inst, enum wic_handshake_failure reason)
{
    LOG("websocket handshake failed for reason %d", reason);
}

static void
on_open_handler(struct wic_inst *inst)
{
    const char *name, *value;

    LOG("websocket is open");
    
    LOG("received handshake:");

    for(value = wic_get_next_header(inst, &name); value; value = wic_get_next_header(inst, &name)){

        LOG("%s: %s", name, value);
    }

    wic_printAtr(ATR, sizeof(ATR));
	wic_send_binary(inst, true, (const void *)ATR, sizeof(ATR));
} 

static void
on_close_handler(struct wic_inst *inst, uint16_t code, const char *reason, uint16_t size)
{
    LOG("websocket closed for reason %u", code);
}

static void
on_close_transport_handler(struct wic_inst *inst)
{
    transport_close((int *)wic_get_app(inst));
}

static void
on_send_handler(struct wic_inst *inst, const void *data, size_t size, enum wic_buffer type)
{
    LOG("sending buffer type %d", type);

    transport_write(*(int *)wic_get_app(inst), data, size);
}

static void*
on_buffer_handler(struct wic_inst *inst, size_t min_size, enum wic_buffer type, size_t *max_size)
{
    static uint8_t tx[1000];

    *max_size = sizeof(tx);

    return (min_size <= sizeof(tx)) ? tx : NULL;
}

static void
err_sys(const char* x)
{
    perror(x);
    exit(1);
}

static void
interruptExecution(int num)
{
	printf("Disconnecting from virtual reader... ");
	wic_close(&inst);
	printf("Done.\n");
}

void
ws_init(APDU_t* instance)
{
	static uint8_t rx[1000];
	static char url[1000] = "ws://127.0.0.1:8525";

	struct wic_header user_agent = {
		.name = "User-Agent",
		.value = "wic"
	};

	arg.rx = rx; arg.rx_max = sizeof(rx);    
	arg.on_send = on_send_handler;
	arg.on_buffer = on_buffer_handler;
	arg.on_message = on_message_handler;        
	arg.on_open = on_open_handler;        
	arg.on_close = on_close_handler;        
	arg.on_close_transport = on_close_transport_handler;        
	arg.on_handshake_failure = on_handshake_failure_handler;
	arg.app = &s;
	arg.url = url;
	arg.role = WIC_ROLE_CLIENT;
	apdu = instance;
	
	if (signal(SIGINT, interruptExecution) == SIG_ERR) {
		err_sys("ERROR: can't catch SIGINT");
	}

	if(!wic_init(&inst, &arg)) {
		fprintf(stderr, "ERROR: failed to init ws client.\n");
		exit(EXIT_FAILURE);
	};

	(void)wic_set_header(&inst, &user_agent);

	if (!transport_open_client( wic_get_url_schema(&inst),
								wic_get_url_hostname(&inst),
								wic_get_url_port(&inst),
								&s))
	{
		fprintf(stderr, "ERROR: failed to open connection.\n");
		exit(EXIT_FAILURE);
	}

	if(wic_start(&inst) != WIC_STATUS_SUCCESS) {
		fprintf(stderr, "ERROR: handshaking failed.\n");
		exit(EXIT_FAILURE);
	}
}