#include "service_serial_stdio.h"
#include <Arduino.h>
#include <stdio.h>

// Serial port stream
FILE* service_serial_stdio_stream;

void service_serial_stdio_setup() {
    Serial.begin(9600);
    service_serial_stdio_stream = fdevopen((int(*)(char, FILE*))put_char, (int(*)(FILE*))get_char);

    // Link standard input, output, and error streams
    stdin = stdout = stderr = service_serial_stdio_stream;
}

// Function to read a character from Serial
char get_char(void) {
    while (!Serial.available());  // Wait until data is available
    return Serial.read();
}

// Function to write a character to Serial
void put_char(char c) {
    Serial.write(c);
}
