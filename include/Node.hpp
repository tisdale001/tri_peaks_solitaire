// Node.hpp
// Header file for node in a graph for triPeaks solitaire
#ifndef NODE_HPP 
#define NODE_HPP

#include <vector>
#include <memory>

//include header files
#include<Card.hpp>

class Node {
    private:
    std::vector<std::shared_ptr<Card>> card_vec;
    //positions on a graph
    int posI;
    int posJ;

    public:
    Node(int posI_, int posJ_);
    ~Node();
    bool empty();
    void popCard();
    std::shared_ptr<Card> getCard();
    void pushCard(std::shared_ptr<Card>);

    int getPosI();
    int getPosJ();
    
};


#endif