// DrawCard.cpp
// DrawCard Command for Tri Peaks Solitaire
#ifndef DRAWCARD_CPP
#define DRAWCARD_CPP

// Include header files
#include <DrawCard.hpp>

DrawCard::DrawCard(Model* model_, View* view_, sf::RenderWindow* window_) {
    model = model_;
    view = view_;
    window = window_; 
}
DrawCard::~DrawCard() {}
    
void DrawCard::execute() {
    // put card in movePile: does not check if drawPile is empty
    model->getMovePile()->push_back(model->getDrawPile()->back());
    model->getDrawPile()->pop_back();
    // animate Card
    view->animateCardDrawPile(window, view->getXPositionWastePile(), view->getYPositionWastePile());
    // put card in wastePile, faceUP
    model->getWastePile()->push_back(model->getMovePile()->back());
    model->getMovePile()->pop_back();
    model->getWastePile()->back()->setFaceUp(true);
}
void DrawCard::undo() {
    // put card in movePile: does not check if wastePile is empty
    model->getMovePile()->push_back(model->getWastePile()->back());
    model->getWastePile()->pop_back();
    // animate Card
    view->animateCardDrawPile(window, view->getXPositionDrawPile(), view->getYPositionDrawPile());
    // put card in drawPile, faceDOWN
    model->getDrawPile()->push_back(model->getMovePile()->back());
    model->getMovePile()->pop_back();
    model->getDrawPile()->back()->setFaceUp(false);
}

#endif