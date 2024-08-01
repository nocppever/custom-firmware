#include "logging.h"
#include <SD.h>

static File logFile;

int init_logging() {
    logFile = SD.open("nids_log.txt", FILE_WRITE);
    return logFile ? 0 : -1;
}

int log_intrusion(const uint8_t* packet, size_t length) {
    if (!logFile) {
        return -1;
    }
    logFile.write(packet, length);
    logFile.println();
    logFile.flush();
    return 0;
}