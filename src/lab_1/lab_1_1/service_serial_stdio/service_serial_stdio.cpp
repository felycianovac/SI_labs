#include "service_serial_stdio.h"
#include <Arduino.h>
#include <stdio.h>

// Serial port stream
FILE* service_serial_stdio_stream;

void service_serial_stdio_setup() {
    // Initialize Serial port
    Serial.begin(9600);
    // Create a stream for the Serial port
    service_serial_stdio_stream = fdevopen(put_serial_char, get_serial_char);

    // Link standard input, output, and error streams
    stdin = stdout = stderr = service_serial_stdio_stream;
}

// Function to read a character from Serial
int get_serial_char(FILE *stream) {
    while (!Serial.available());
    char c = Serial.read();
    Serial.write(c);  // ECHO: scrie înapoi caracterul în terminal
    return c;
}

// Function to write a character to Serial
int put_serial_char(char c, FILE *stream) {
    Serial.write(c);
    return c;
}
