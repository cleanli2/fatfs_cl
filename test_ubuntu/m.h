#ifndef _M___H
#define _M___H
#include <stdio.h>


#define PRT_LINE printf("%d %s\n", __LINE__, __func__)

void do_backtrace();
void v_init();
void v_r_sec(int n, char*buf);
void v_w_sec(int n, char*buf);

#endif
