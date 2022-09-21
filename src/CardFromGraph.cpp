// CardFromGraph.cpp
// Command that takes card from graph in Tri Peaks Solitaire
#ifndef CARDFROMGRAPH_CPP
#define CARDFROMGRAPH_CPP
// Include Header files
#include <CardFromGraph.hpp>

CardFromGraph::CardFromGraph(Model* model_, View* view_, sf::RenderWindow* window_, Node* node_) {
    model = model_;
    view = view_;
    window = window_;
    node = node_;
}
CardFromGraph::~CardFromGraph() {}

void CardFromGraph::execute() {
    // put card in movePile: does not check if drawPile is empty
    model->getMovePile()->push_back(node->getCard());
    node->popCard();
    // animate Card
    view->animateCardGraph(window, view->getXPositionWastePile(), view->getYPositionWastePile());
    // put card in wastePile, faceUP
    model->getWastePile()->push_back(model->getMovePile()->back());
    model->getMovePile()->pop_back();
    // turn appropriate cards faceUP
    model->turnCardsFaceUp(node->getPosI(), node->getPosJ());
}

void CardFromGraph::undo() {
    // put card in movePile: does not check if wastePile is empty
    model->getMovePile()->push_back(model->getWastePile()->back());
    model->getWastePile()->pop_back();
    // animate Card
    view->animateCardGraph(window, view->getXPositionNode(node->getPosI(), node->getPosJ()), 
        view->getYPositionNode(node->getPosI()));
    // put card in node
    node->pushCard(model->getMovePile()->back());
    model->getMovePile()->pop_back();
    // turn appropriate cards faceDOWN
    model->turnCardsFaceDown(node->getPosI(), node->getPosJ());
}

#endif