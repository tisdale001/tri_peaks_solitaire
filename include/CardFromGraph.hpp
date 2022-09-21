// CardFromGraph.hpp
// Header file for command in Tri Peaks Solitaire
#ifndef CARDFROMGRAPH_HPP
#define CARDFROMGRAPH_HPP
// Include Header files
#include <Command.hpp>
#include <Node.hpp>
#include <ModelTriPeaks.hpp>
#include <ViewTriPeaks.hpp>

class CardFromGraph : public Command {
    private:
    Model* model;
    View* view;
    sf::RenderWindow* window;
    Node* node;


    public:
    CardFromGraph(Model* model_, View* view_, sf::RenderWindow* window_, Node* node_);
    ~CardFromGraph();

    void execute();
    void undo();
};

#endif