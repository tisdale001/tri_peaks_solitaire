// ModelTriPeaks.cpp
// Model for Tri Peaks Solitaire
#ifndef MODEL_CPP 
#define MODEL_CPP

#include<iostream>
#include<vector>
#include <memory>
//include header files
#include<Deck.hpp>
#include<Card.hpp>
#include<Node.hpp>
#include<ModelTriPeaks.hpp>

Model::Model(){
    this->createGraph();
}

Model::~Model(){}

// creates 'graph': container full of nodes to hold cards
void Model::createGraph(){
    // add nodes to triPeaks graph
    for (int i = 0; i < 5; i++) {
        std::vector<Node> v1 = std::vector<Node>();
        for (int j = 0; j < i + 7; j++) {
            v1.push_back(Node(i, j));
        }
        graph->push_back(v1);
    }
}

// transfers all cards to 'deck' (to be reshuffled)
// deck handles turning them all face down
void Model::allCardsToDeck(){
    // put all tableau cards in waste pile
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < i + 7; j++) {
            if (!graph->at(i).at(j).empty()) {
                wastePile->push_back(graph->at(i).at(j).getCard());
                graph->at(i).at(j).popCard();
            }
        }
    }
    // return all cards to deck
    if (!drawPile->empty()) {
        deck->returnCards(drawPile);
    }
    if (!wastePile->empty()) {
        deck->returnCards(wastePile);
    }
    if (!movePile->empty()) {
        deck->returnCards(movePile);
    }
}

// deals tableau from draw pile: turns face up as necessary
void Model::dealTableau(){
    // does not check if drawPile is empty
    // deal to 0 row
    for (int i = 0; i < 7; i += 3) {
        graph->at(0).at(i).pushCard(drawPile->back());
        drawPile->pop_back();
    }
    // deal to 1 row
    for (int i = 0; i < 8; i++) {
        if (i != 2 && i != 5) {
            graph->at(1).at(i).pushCard(drawPile->back());
            drawPile->pop_back();
        }
    }
    // deal to 2 row
    for (int i = 0; i < 9; i++) {
        graph->at(2).at(i).pushCard(drawPile->back());
        drawPile->pop_back();
    }
    // deal to 3 row
    for (int i = 0; i < 10; i++) {
        drawPile->back()->setFaceUp(true);
        graph->at(3).at(i).pushCard(drawPile->back());
        drawPile->pop_back();
    }
}

// puts all cards from deck to drawPile
void Model::cardsFromDeckToDrawPile(){
    while (!deck->isEmpty()) {
        deck->dealCard(drawPile);
    }
}

// returns all cards to deck, shuffles, puts all cards in drawPile, deals tableau
void Model::redeal(){
    this->allCardsToDeck();
    deck->shuffleDeck();
    this->cardsFromDeckToDrawPile();
    this->dealTableau();
}

// turns appropriate cards faceUP relative to node at position i, j
void Model::turnCardsFaceUp(int posI, int posJ) {
    if (posI == 0) {
        return;
    }
    if (posJ <= posI + 5) {
        if (!graph->at(posI - 1).at(posJ).empty()) {
            if (this->unblocked(posI - 1, posJ)) {
                graph->at(posI - 1).at(posJ).getCard()->setFaceUp(true);
            }
        }
    }
    if (posJ - 1 >= 0) {
        if (!graph->at(posI - 1).at(posJ - 1).empty()) {
            if (this->unblocked(posI - 1, posJ - 1)) {
                graph->at(posI - 1).at(posJ - 1).getCard()->setFaceUp(true);
            }
        }
    }
}

// turns appropriate cards faceDOWN relative to node at position i, j
void Model::turnCardsFaceDown(int posI, int posJ) {
    if (posI == 0) {
        return;
    }
    if (posJ <= posI + 5) {
        if (!graph->at(posI - 1).at(posJ).empty()) {
            graph->at(posI - 1).at(posJ).getCard()->setFaceUp(false);
        }
    }
    if (posJ - 1 >= 0) {
        if (!graph->at(posI - 1).at(posJ - 1).empty()) {
            graph->at(posI - 1).at(posJ - 1).getCard()->setFaceUp(false);
        }
    }
}

// checks if card in graph is unblocked
bool Model::unblocked(int posI, int posJ) {
    // does not check if posI and posJ are in bounds
    // does not check if there is a card at posI, posJ
    if (!graph->at(posI + 1).at(posJ).empty()) {
        return false;
    }
    if (!graph->at(posI + 1).at(posJ + 1).empty()) {
        return false;
    }
    return true;
}

// checks if legal move based on card values
bool Model::legalMove(int val_1, int val_2) {
    // checks if value 'turns the corner'
    if ((val_1 == val_2 + 1) || (val_1 == val_2 - 1) || (val_1 == val_2 + 13 - 1) ||
        (val_1 == val_2 - 13 + 1)) {
        return true;
    }
    return false;
}

// checks if graph is empty: returns true if all nodes are empty
bool Model::checkWin(){
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < i + 7; j++) {
            if (!graph->at(i).at(j).empty()) {
                return false;
            }
        }
    }
    return true;
}
// getter method for graph
std::shared_ptr<std::vector<std::vector<Node>>> Model::getGraph(){
    return graph;
}
// getter method for drawPile
std::shared_ptr<std::vector<std::shared_ptr<Card>>> Model::getDrawPile(){
    return drawPile;
}
// getter method for wastePile
std::shared_ptr<std::vector<std::shared_ptr<Card>>> Model::getWastePile(){
    return wastePile;
}
// getter method for movePile
std::shared_ptr<std::vector<std::shared_ptr<Card>>> Model::getMovePile() {
    return movePile;
}
// getter method for deck
std::shared_ptr<Deck> Model::getDeck() {
    return deck;
}

#endif