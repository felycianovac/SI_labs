#ifndef LCD_STDIO_H
#define LCD_STDIO_H

#include <stdio.h>
#include <LiquidCrystal.h>

extern LiquidCrystal lcd;
extern FILE lcd_stdout;

void lcdSetup();
int lcd_putchar(char c, FILE* stream);

#endif
