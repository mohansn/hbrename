#ifndef __LIBCLEANUP_H__
#define __LIBCLEANUP_H__
#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>
#include <utime.h>

#define NAMELEN 255
#ifdef DEBUG
extern int EF_DISABLE_BANNER;
#endif

char *new_name(char *argv_ptr);
int d_printf(const char *fmt, ...);
#endif
