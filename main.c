#include <stdio.h>
#include "funny.h"

int main(int argc, char *argv[]) {
    //fake data, for source code analysis
    
    _libhook_init();
    
    char *pathname = "/var/www/index.php"
    char *buf = "hello";
    
    open64(pathname, 1);
    send(1, buf, 1, 1);
}
