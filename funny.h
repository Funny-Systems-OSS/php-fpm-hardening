#ifndef FUNNY_H
#define FUNNY_H

#define _GNU_SOURCE

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <dlfcn.h>
#include <fcntl.h>
#include <stdarg.h>
#include <malloc.h>
#include <sys/socket.h>
#include <errno.h> //auto return errno for open64().

#include "funny_debug.h"
#include "funny_build.h"

#include "funny_php.h"

#if BUILD_FUNNY
    #include "funny_cloud_sql.h"
#endif

const char *FUNC_NAME_OPEN64 = "open64";
const char *FUNC_NAME_SEND = "send";

typedef int (*orig_open_func_type)(const char *pathname, int flags, ...);
typedef int (*orig_send_func_type)(int sockfd, const void *buf, size_t len, int flags);

orig_open_func_type orig_open_func;
orig_send_func_type orig_send_func;

#endif

