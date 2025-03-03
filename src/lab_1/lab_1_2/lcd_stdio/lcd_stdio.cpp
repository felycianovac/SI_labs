#include "lcd_stdio.h"

// LCD instance connected to the following pins
LiquidCrystal_I2C lcd(0x27, 16, 2);
// Stream for LCD output
FILE lcd_stdout;
// Current cursor position
static uint8_t current_col = 0;
static uint8_t current_row = 0;

void lcdSetup() {
    // Initialize LCD
    lcd.init();
    lcd.backlight();
    lcd.begin(16, 2);
    // Set up the LCD stream
    fdev_setup_stream(&lcd_stdout, lcd_putchar, NULL, _FDEV_SETUP_WRITE);
}

int lcd_putchar(char c, FILE* stream) {
    // Handle special characters
    if (c == '\n') {
        // Move to the next row
        current_row = (current_row + 1) % 2;
        // Reset the column
        current_col = 0;
        // Clear the display if moving to the first row
        if (current_row == 0) {
            // Clear the display
            lcd.clear();
        }
        // Move the cursor
        lcd.setCursor(current_col, current_row);
        return 0;
    }

    // Wrap around if the end of the line is reached
    if (current_col >= 16) {
        // Move to the next row
        current_row = (current_row + 1) % 2;
        // Reset the column
        current_col = 0;
        // Clear the display if moving to the first row
        if (current_row == 0) {
            lcd.clear();
        }
        // Move the cursor
        lcd.setCursor(current_col, current_row);
    }

    // Write the character to the LCD
    lcd.write(c);
    // Move the cursor
    current_col++;
    return 0;
}
