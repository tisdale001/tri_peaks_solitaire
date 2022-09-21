// Node.cpp
// This represents a node in a graph in triPeaks solitaire
#ifndef NODE_CPP 
#define NODE_CPP

#include<vector>

//include header files
#include<Card.hpp>
#include<Node.hpp>

// constructor stores position in graph
Node::Node(int posI_, int posJ_) {
    posI = posI_;
    posJ = posJ_;
}
// deconstructor automatically clears the card_vec
Node::~Node() {
    card_vec.clear();
}

bool Node::empty() {
    return card_vec.empty();
}

void Node::popCard() {
    if (!card_vec.empty()) {
        card_vec.pop_back();
    }
}

std::shared_ptr<Card> Node::getCard() {
    if (!card_vec.empty()) {
        return card_vec.back();
    }
    return nullptr;
}

void Node::pushCard(std::shared_ptr<Card> card) {
    card_vec.push_back(card);
}

// getter methods
int Node::getPosI() {
    return posI;
}
int Node::getPosJ() {
    return posJ;
}

#endif