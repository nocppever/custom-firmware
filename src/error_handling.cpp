#include "error_handling.h"
#include <string.h>

static const char* ERROR_MESSAGES[] = {
    "Failed to initialize network interface",
    "Failed to initialize logging system",
    "Failed to read network packet",
    "Error occurred during packet classification",
    "Failed to write to log file",
    "Unknown error occurred"
};

void get_error_string(int error_code, char* buffer, int buffer_size) {
    if ((error_code & 0xFFFF0000) != ERR_OFFSET) {
        strncpy(buffer, "Invalid error code", buffer_size);
        return;
    }

    int index = (error_code & 0xFFFF) - 1;
    if (index >= 0 && index < sizeof(ERROR_MESSAGES) / sizeof(ERROR_MESSAGES[0])) {
        strncpy(buffer, ERROR_MESSAGES[index], buffer_size);
    } else {
        strncpy(buffer, ERROR_MESSAGES[sizeof(ERROR_MESSAGES) / sizeof(ERROR_MESSAGES[0]) - 1], buffer_size);
    }
}