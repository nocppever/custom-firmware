#ifndef DECISION_TREE_HPP
#define DECISION_TREE_HPP

#include <Arduino.h>

class DecisionTree {
private:
    struct Node {
        uint8_t feature;
        uint16_t threshold;
        uint8_t left;
        uint8_t right;
    };

    struct Leaf {
        bool is_intrusion;
    };

    static const uint8_t NUM_NODES = 7;
    static const uint8_t NUM_LEAVES = 8;
    const Node nodes[NUM_NODES];
    const Leaf leaves[NUM_LEAVES];

    void extract_features(const uint8_t* packet, size_t length, uint16_t features[4]);
    bool traverse(uint8_t node_index, const uint16_t features[4]);

public:
    DecisionTree();
    bool classify(const uint8_t* packet, size_t length);
};

#endif // DECISION_TREE_HPP