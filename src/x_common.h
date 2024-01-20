#ifndef X_COMMON_H
#define X_COMMON_H

typedef signed int     i32;
typedef signed int     u32;
typedef signed short   i16;
typedef unsigned short u16;
typedef signed char     i8;
typedef unsigned char   u8;
typedef unsigned char bool;

typedef enum {
	NO_ERROR,
	ERR_BAD_QID,
	ERR_BAD_PID,
	ERR_QTABLE_OVERFLOW,
	ERR_DEFER_UNKNOWN_OPTION,
	ERR_DEFER_OUT_OF_RANGE
} Status;

#endif // !X_COMMON_H