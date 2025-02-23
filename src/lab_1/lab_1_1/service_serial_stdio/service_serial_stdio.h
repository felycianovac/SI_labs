#ifndef SERVICE_SERIAL_STDIO_H
#define SERVICE_SERIAL_STDIO_H

#include <stdio.h>

void service_serial_stdio_setup();

int get_serial_char(FILE *stream);
int put_serial_char(char c, FILE *stream);

#endif // SERVICE_SERIAL_STDIO_H
