#ifndef LOGGING_H
#define LOGGING_H

#include <Arduino.h>

int init_logging();
int log_intrusion(const uint8_t* packet, size_t length);

#endif // LOGGING_H