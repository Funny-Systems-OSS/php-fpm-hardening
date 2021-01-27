#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "funny_php.h"
#include "funny_debug.h"

#define FILENAME "/funny_php.conf"

char *path;
char *enable;
char *disable;

int funny_is_php_path (const char *pathname) {
    
    int is_funny_path = 0;
    int path_len = strlen(pathname);
    char *path_buf = (char *) malloc(sizeof(char) * path_len + 1);
    strcpy(path_buf, pathname);
    
    for (int last = path_len; last > 0; last--) {
        if ( path_buf[last] == '/' ) {
            path_buf[last] = '\0';
            break;
        } else
            path_buf[last] = '\0';
    }

    debug_printf("DEBUG : %d\n", DEBUG);
    debug_printf("pathname=%s\n", path_buf);
    debug_printf("enable=%s\n", enable);
    debug_printf("disable=%s\n", disable);

    //str_lower()
    //disable check

    char *tmp_enable = (char *) malloc(sizeof(char) * strlen(enable) + 1);
    char *tmp_disable = (char *) malloc(sizeof(char) * strlen(disable) + 1);
    
    strcpy(tmp_enable, enable);
    strcpy(tmp_disable, disable);
    
    char *dis_idx_path = strtok(tmp_disable, "\n");

    debug_printf("Disable path print begin\n");
    
    while (dis_idx_path != NULL) {
        
        debug_printf("%s\n", dis_idx_path);
        
        char *find_dis_idx = strstr(path_buf, dis_idx_path);

        if (find_dis_idx != NULL)
            return 0;

        dis_idx_path = strtok(NULL, "\n");
    }
    
    debug_printf("Enable path print begin\n");

    char *ena_idx_path = strtok(tmp_enable, "\n");
    
    while (ena_idx_path != NULL) {
        
        debug_printf("%s\n", ena_idx_path);
        
        char *find_ena_idx = strstr(path_buf, ena_idx_path);

        if (find_ena_idx != NULL) {
            is_funny_path = 1;
            break;
        }

        ena_idx_path = strtok(NULL, "\n");
    }

    return is_funny_path;
}

int funny_is_php_file (const char *pathname) {
    int last_idx = strlen(pathname) - 1;
    //".php"
    if(pathname[last_idx] == 'p' && pathname[last_idx - 1] == 'h' && pathname[last_idx - 2] == 'p' && pathname[last_idx - 3] == '.')
	    return 1;

    return 0;
}

int funny_get_file_size() {
    
    /*create variable of stat*/
    struct stat stp = { 0 };
    
    /*These functions return information about a file. No permissions are required on the file itself*/
    stat(FILENAME, &stp);
    
    /*determine the size of data which is in file*/
    return stp.st_size;
}

void funny_read_conf() {
    debug_printf("funny_read_conf()\n");

    FILE *fp;
    fp = fopen(FILENAME, "r");
    
    if (NULL == fp) {
        funny_read_conf_fail_and_exit();
    } 
        
    int filesize = funny_get_file_size();

    /*allocates the address to the message pointer and allocates memory*/
    path = (char *) malloc(sizeof(char) * filesize);

    //TODO
    //if malloc() fail? check path

    if (fread(path, 1, filesize - 1, fp) == -1) {
        error_printf("\nerror in reading\n");
    } else {  
        char *dis_begin_idx = strstr(path, "[disable]");
    
        enable = (char *) malloc(sizeof(char) * (dis_begin_idx - 1 - path));
        disable = (char *) malloc(sizeof(char) * (path + filesize - dis_begin_idx));
    
        //copy from path to enable, disable path
        strncpy(enable, path, (dis_begin_idx - path - 2));
        strncpy(disable, path + (dis_begin_idx - path), (path + filesize - dis_begin_idx));

    }

    fclose(fp);
    free(path);
}

void funny_read_conf_fail_and_exit() {
    error_printf("/funny_php.conf not found\n");
    exit(1);
}
