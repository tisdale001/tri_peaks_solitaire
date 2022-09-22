// ControllerTriPeaks.cpp
// Controller for Tri Peaks Solitaire
#ifndef CONTROLLER_CPP 
#define CONTROLLER_CPP 

#include <iostream>
// include Header files
#include <ControllerTriPeaks.hpp>

Controller::Controller() {}
Controller::~Controller() {}

// undo one item from stack
void Controller::Undo() {
    if (!undoStack.empty()) {
        undoStack.top()->undo();
        // push to redo stack
        redoStack.push(undoStack.top());
        undoStack.pop();
    }
}

// redo one item from stack
void Controller::Redo() {
    if (!redoStack.empty()) {
        redoStack.top()->execute();
        // push to undo stack
        undoStack.push(redoStack.top());
        redoStack.pop();
    }
}

// clear redoStack
void Controller::clearRedoStack() {
    while (!redoStack.empty()) {
        redoStack.pop();
    }
}

void Controller::playGame() {
    // initiate view
    view.initiateView(model.getGraph(), model.getDrawPile(), model.getWastePile(), model.getMovePile(), model.getDeck());
    // deal hand

    sf::RenderWindow window(sf::VideoMode(view.getBoundsWidth(), view.getBoundsHeight()), 
    "Tri Peaks Solitaire", sf::Style::Close);

    model.cardsFromDeckToDrawPile();
    model.dealTableau();
    view.dealAnimation(&window);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if(event.type == sf::Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    //std::cout << "Mouse button released\n";
                    sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
                    Node* node = view.getClickOnGraph(mousePos);
                    std::shared_ptr<std::vector<std::shared_ptr<Card>>> pile = view.getClickOnPiles(mousePos);
                    if (node == nullptr) {
                        // try piles
                        if (pile != nullptr) {
                            // pile was click-released on
                            if (pile == model.getDrawPile()) {
                                // create DrawCard
                                std::shared_ptr<Command> drawCard = std::make_shared<DrawCard>(&model, &view, &window);
                                undoStack.push(drawCard);
                                drawCard->execute();
                                this->clearRedoStack();
                            }
                        }
                        else {
                            // both node and pile are null
                        }
                    }
                    else {
                        // node was click-released on
                        bool moveIsLegal = false;
                        if (node->getCard()->getFaceUp() == true && model.getWastePile()->empty()) {
                            moveIsLegal = true;
                        }
                        else if (node->getCard()->getFaceUp() == true && 
                                model.legalMove(node->getCard()->getValue(), model.getWastePile()->back()->getValue())) {
                            moveIsLegal = true;
                        }
                        if (moveIsLegal) {
                            // move is legal: create CardFromGraph command
                            std::shared_ptr<Command> cardFromGraph = 
                                std::make_shared<CardFromGraph>(&model, &view, &window, node);
                            undoStack.push(cardFromGraph);
                            cardFromGraph->execute();
                            this->clearRedoStack();
                            if (model.checkWin()) {
                                std::cout << "WINNER!\n";
                                view.animateWin(&window);
                            }
                        }
                    }
                }
            }
            else if (event.type == sf::Event::Closed) {
				window.close();
                break;
			}
            else if (event.type == sf::Event::KeyReleased) {
				//std::cout << "Key Pressed" << std::endl;
				
				if (event.key.code == sf::Keyboard::Escape) {
					//std::cout << "escape Pressed" << std::endl;
					window.close();
					break;
				}
                else if (event.key.code == sf::Keyboard::D) {
                    this->clearRedoStack();
                    while (!undoStack.empty()) {
                        undoStack.pop();
                    }
                    model.redeal();
                    view.dealAnimation(&window);
                }
                else if (event.key.code == sf::Keyboard::Z) {
                    //std::cout << "Z pressed\n";
                    this->Undo();
                }
                else if (event.key.code == sf::Keyboard::Y) {
                    //std::cout << "Y pressed\n";
                    this->Redo();
                }
                else if (event.key.code == sf::Keyboard::A) {
                    view.animateWin(&window);
                }
            }
        }
        view.draw(&window);
    }
}



#endif