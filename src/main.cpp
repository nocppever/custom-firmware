#include <Arduino.h>
#include <SPI.h>
#include <Ethernet.h>
#include <SD.h>
#include "error_handling.h"
#include "decision_tree.hpp"
#include "logging.h"

DecisionTree classifier;

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192, 168, 1, 177);
EthernetServer server(80);

// Function declarations
int initialize_hardware();
void process_packet(const uint8_t* packet, size_t length);
void trigger_alert();

void setup() {
    Serial.begin(9600);
    int error = initialize_hardware();
    if (error != 0) {
        char error_msg[256];
        get_error_string(error, error_msg, sizeof(error_msg));
        Serial.print(F("Initialization error: "));
        Serial.println(error_msg);
        while(1); // Halt if initialization fails
    }
    Serial.println(F("NIDS initialized successfully"));
}

void loop() {
    EthernetClient client = server.available();
    if (client) {
        uint8_t packet_buffer[1518]; // Max Ethernet frame size
        size_t packet_size = 0;
        while (client.available() && packet_size < sizeof(packet_buffer)) {
            packet_buffer[packet_size++] = client.read();
        }
        if (packet_size > 0) {
            process_packet(packet_buffer, packet_size);
        }
    }
}

int initialize_hardware() {
    if (Ethernet.begin(mac) == 0) {
        return ERR_NETWORK_INIT_FAILED;
    }
    if (!SD.begin(4)) {
        return ERR_LOG_INIT_FAILED;
    }
    server.begin();
    return 0;
}

void process_packet(const uint8_t* packet, size_t length) {
    if (classifier.classify(packet, length)) {
        log_intrusion(packet, length);
        trigger_alert();
    }
}

void trigger_alert() {
    Serial.println(F("ALERT: Potential intrusion detected!"));
    // Add additional alert mechanisms here
}