// DrawCard.hpp
// Header file for DrawCard for Tri Peaks Solitaire
#ifndef DRAWCARD_HPP
#define DRAWCARD_HPP
// Include Header files
#include <Command.hpp>
#include <ModelTriPeaks.hpp>
#include <ViewTriPeaks.hpp>

class DrawCard : public Command {
    private:
    Model* model;
    View* view;
    sf::RenderWindow* window;
    
    public:
    DrawCard(Model* model_, View* view_, sf::RenderWindow* window_);
    ~DrawCard();

    void execute();
    void undo();
};

#endif