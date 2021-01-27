#include "funny.h"

static void _libhook_init() __attribute__ ((constructor));
static void _libhook_init() {   

    debug_printf("hooking!\n");

    orig_open_func = (orig_open_func_type)dlsym(RTLD_NEXT, FUNC_NAME_OPEN64);
    orig_send_func = (orig_send_func_type)dlsym(RTLD_NEXT, FUNC_NAME_SEND);
    
    funny_read_conf();
}

int open64(const char *pathname, int flags, ...) {
    int enable_open = 0;
    
    if (funny_is_php_file(pathname) == 1) {
        if (funny_is_php_path(pathname) == 1) {
            debug_printf("enable_open == 1\n");
            enable_open = 1;
        } else {
            enable_open = -1;
        }
    }
 
    if (enable_open == -1) {
        //TODO
        //_set_errno()
        return -1;
    }

    if (flags & O_CREAT) {
        va_list args;
        va_start(args, flags);
        int mode = va_arg(args, int);
        va_end(args);    
     
        return orig_open_func(pathname, flags, mode);
     } else {
        return orig_open_func(pathname, flags);
     }
}

ssize_t send(int sockfd, const void *buf, size_t len, int flags){
    
#if BUILD_OSS
        return orig_send_func(sockfd, buf, len, flags);
#endif

#if BUILD_FUNNY
    char *newbuf = funny_send(sockfd, buf, len, flags); 
    return orig_send_func(sockfd, newbuf, len, flags);
#endif
}

