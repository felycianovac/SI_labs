#ifndef LCD_STDIO_H
#define LCD_STDIO_H

#include <stdio.h>
#include <LiquidCrystal.h>

extern LiquidCrystal lcd; // LCD instance
extern FILE lcd_stdout; // Stream for LCD output

void lcdSetup();
int lcd_putchar(char c, FILE* stream);

#endif
