# php-fpm Hardening
+ [Features](#Features)
+ [Config](#Config)
+ [Usage](#Usage)

## Features
+ Make **.php** file not in path defineded in `funny_php.conf` be invisible to php-fpm by LD_PRELOAD trick.
+ Compare with original php-fpm:

&nbsp;             | php-fpm                 | php-fpm hardening <br />(OSS Edition) | php-fpm hardening <br />(Enterpise Edition)
---------------------|-------------------------|-------------------------------------------|----------------------------------------------
PATH_NOT_TRUSTED/ANY.php      | Happy executing...      | **No such file!**                         | **No such file!**
Bind with <br />Cloud SQL Proxy Hardening (Enterpise Edition) | No                      | No                                 | **Yes**
> Contact [oss@funny.systems](mailto:oss@funny.systems) for more infomation.
## Config
The `funny_php.conf` should be consist with two sections, and each path should be seperated by newline.
+ enable:\
  This section declares the paths where trusted .php files would be placed.
+ disable:\
  This section declares paths where .php files will not be visible to php-fpm.

**Path found in both section would be treat as untrusted.**

```funny_path.conf.example
[enable]
/var/www/html
/var/www/project

[disable]
/var/www/html/uploads
```
## Usage
1. Define trusted path and excluded path in `funny_php.conf`.
2. Move `funny_php.conf` to `/`.
   + **`funny_php.conf` MUST be place at `/` or php-fpm would exit with error.**
3. Execute php-fpm like this:
`LD_PRELOAD=funny.so php-fpm`

That's all!
