#ifndef __CONFIG_H__
#define __CONFIG_H__

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "types.h"

#define ASSERT assert

#define LOG_I(...)	printf(__VA_ARGS__);
#define LOG_E(...)	printf(__VA_ARGS__);
#define LOG_W(...)	printf(__VA_ARGS__);

#endif