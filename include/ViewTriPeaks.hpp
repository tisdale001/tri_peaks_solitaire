// ViewTriPeaks.hpp
// Header file for View in Tri Peaks Solitaire
#ifndef VIEW_HPP 
#define VIEW_HPP
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <vector>
#include <memory>

// include Header files
#include <Card.hpp>
#include <Deck.hpp>
#include <Node.hpp>
#include <AnimationWrapper.hpp>

class View {
    private:
    int bounds_width = 1100;
	int bounds_height = 750;
	int stackDistance = 0; // set stackDistance to be cardHeight/2
    int distBtwCards = 10;
    int distBtwPiles = 50;
    int cardHeight = 0; // set cardHeight with sprite.getSize()
    int cardWidth = 0; // set cardWidth with sprite.getSize()
    int startPointX = (int)(bounds_width / 2); 
    int startPointY = 100;
    sf::Image image; // initiate
    sf::Texture texture; // initiate
    sf::Sprite sprite; // initiate
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> wastePile; // initiate all below
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> movePile;
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> drawPile;
    std::shared_ptr<std::vector<std::vector<Node>>> graph;
    std::shared_ptr<Deck> deck;

    public:
    View();
    ~View();
    void initiateView(std::shared_ptr<std::vector<std::vector<Node>>> graph_, 
        std::shared_ptr<std::vector<std::shared_ptr<Card>>> drawPile_, 
        std::shared_ptr<std::vector<std::shared_ptr<Card>>> wastePile_, 
        std::shared_ptr<std::vector<std::shared_ptr<Card>>> movePile_, 
        std::shared_ptr<Deck> deck_);
    Node* getClickOnGraph(sf::Vector2f);
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> getClickOnPiles(sf::Vector2f);
    void setPosition();
    void draw(sf::RenderWindow*);
    void drawAnimation(sf::RenderWindow*);
    void animateCardGraph(sf::RenderWindow*, int xPos, int yPos);
    void animateCardDrawPile(sf::RenderWindow*, int xPos, int yPos);
    void dealAnimation(sf::RenderWindow* window);
    void animateWin(sf::RenderWindow* window);

    int getBoundsWidth();
    int getBoundsHeight();
    int getXPositionWastePile();
    int getYPositionWastePile();
    int getXPositionDrawPile();
    int getYPositionDrawPile();
    int getXPositionNode(int posI, int posJ);
    int getYPositionNode(int posI);

};

#endif