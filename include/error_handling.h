#ifndef ERROR_HANDLING_H
#define ERROR_HANDLING_H

// Use a smaller offset to avoid overflow
#define ERR_OFFSET 0x8000

#define ERR_NETWORK_INIT_FAILED (ERR_OFFSET | 0x01)
#define ERR_LOG_INIT_FAILED     (ERR_OFFSET | 0x02)
#define ERR_PACKET_READ_FAILED  (ERR_OFFSET | 0x03)
#define ERR_CLASSIFICATION_FAILED (ERR_OFFSET | 0x04)
#define ERR_LOG_WRITE_FAILED    (ERR_OFFSET | 0x05)

void get_error_string(int error_code, char* buffer, int buffer_size);

#endif // ERROR_HANDLING_H