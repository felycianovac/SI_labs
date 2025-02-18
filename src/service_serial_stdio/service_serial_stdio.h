#ifndef SERVICE_SERIAL_STDIO_H
#define SERVICE_SERIAL_STDIO_H

#include <stdio.h>


void service_serial_stdio_setup();
char get_char(void);

void put_char(char c);

#endif // SERVICE_SERIAL_STDIO_H