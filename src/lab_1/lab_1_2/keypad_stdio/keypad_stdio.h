#ifndef KEYPAD_STDIO_H
#define KEYPAD_STDIO_H

#include <stdio.h>
#include <Keypad.h>
#include "../lcd_stdio/lcd_stdio.h"  


extern Keypad keypad;
extern FILE keypad_stdin;
extern const char correctCode[];
extern char enteredCode[];

void keypadSetup();
int keypad_getchar(FILE* stream);

#endif