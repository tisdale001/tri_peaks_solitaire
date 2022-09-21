// ModelTriPeaks.hpp
// Header file for model for Tri Peaks Solitaire
#ifndef MODEL_HPP 
#define MODEL_HPP

#include<vector>
#include <memory>
//include header files
#include<Deck.hpp>
#include<Card.hpp>
#include<Node.hpp>

class Model {
    private:
    std::shared_ptr<std::vector<std::vector<Node>>> graph = std::make_shared<std::vector<std::vector<Node>>>();
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> drawPile = 
        std::make_shared<std::vector<std::shared_ptr<Card>>>();
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> wastePile = 
        std::make_shared<std::vector<std::shared_ptr<Card>>>();
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> movePile = 
        std::make_shared<std::vector<std::shared_ptr<Card>>>();
    std::shared_ptr<Deck> deck = std::make_shared<Deck>();

    
    public:
    Model();
    ~Model();
    void createGraph();
    void allCardsToDeck();
    void dealTableau();
    void cardsFromDeckToDrawPile();
    void redeal();
    void turnCardsFaceUp(int posI, int posJ);
    void turnCardsFaceDown(int posI, int posJ);
    bool unblocked(int posI, int posJ);
    bool legalMove(int val_1, int val_2);
    
    bool checkWin();

    std::shared_ptr<std::vector<std::vector<Node>>> getGraph();
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> getDrawPile();
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> getWastePile();
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> getMovePile();
    std::shared_ptr<Deck> getDeck();
};


#endif