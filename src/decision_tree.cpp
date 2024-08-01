#include "decision_tree.hpp"

DecisionTree::DecisionTree() : 
    nodes{
        {0, 49151, 1, 2},
        {1, 6, 3, 4},
        {2, 1500, 5, 6},
        {3, 80, 0, 1},
        {3, 443, 2, 3},
        {3, 22, 4, 5},
        {3, 25, 6, 7}
    },
    leaves{
        {false}, {true}, {false}, {true},
        {false}, {true}, {false}, {true}
    }
{}

void DecisionTree::extract_features(const uint8_t* packet, size_t length, uint16_t features[4]) {
    // Extract relevant features from the packet
    features[0] = (packet[36] << 8) | packet[37];  // Destination port
    features[1] = packet[23];                      // Protocol
    features[2] = length;                          // Packet size
    features[3] = (packet[34] << 8) | packet[35];  // Source port
}

bool DecisionTree::traverse(uint8_t node_index, const uint16_t features[4]) {
    if (node_index >= NUM_NODES) {
        return leaves[node_index - NUM_NODES].is_intrusion;
    }

    const Node& node = nodes[node_index];
    if (features[node.feature] <= node.threshold) {
        return traverse(node.left, features);
    } else {
        return traverse(node.right, features);
    }
}

bool DecisionTree::classify(const uint8_t* packet, size_t length) {
    uint16_t features[4];
    extract_features(packet, length, features);
    return traverse(0, features);
}