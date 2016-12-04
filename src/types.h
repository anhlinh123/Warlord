#ifndef __TYPES_H__
#define __TYPES_H__

typedef char int8;
typedef short int16;
typedef int int32;
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;

#define INTRINSIC_STRING_LENGTH 32

typedef struct Generic
{
	uint32 size;
	void* data;
} Generic;

typedef enum Result
{
	Result_SUCCESS = 0,
	Result_FAILURE = -1
} Result;

#endif