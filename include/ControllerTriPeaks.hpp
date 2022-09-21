// ControllerTriPeaks.hpp
// Header file for controller for Tri Peaks Solitaire
#ifndef CONTROLLER_HPP 
#define CONTROLLER_HPP 
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <vector>
#include <memory>
#include <stack>

// include Header files
#include<Node.hpp>
#include <Card.hpp>
#include <Deck.hpp>
#include <ViewTriPeaks.hpp>
#include <ModelTriPeaks.hpp>
#include <Command.hpp>
#include <DrawCard.hpp>
#include <CardFromGraph.hpp>

class Controller {
    private:
    Model model = Model();
    View view = View();

    // stack to hold commands for undo
    std::stack<std::shared_ptr<Command>> undoStack;
    // stack to hold commands for redo
    std::stack<std::shared_ptr<Command>> redoStack;
    

    public:
    Controller();
    ~Controller();
    void Undo();
    void Redo();
    void clearRedoStack();
    void playGame();
};

#endif