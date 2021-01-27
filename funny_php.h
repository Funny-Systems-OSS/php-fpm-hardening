#ifndef FUNNY_PHP_H
#define FUNNY_PHP_H

int funny_is_php_path(const char *pathname);
int funny_is_php_file(const char *pathname);
int funny_get_file_size();
void funny_read_conf();
void funny_read_conf_fail_and_exit();

#endif
