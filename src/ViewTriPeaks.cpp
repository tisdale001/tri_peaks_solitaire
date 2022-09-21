// ViewTriPeaks.cpp
// View for Tri Peaks Solitaire
#ifndef VIEW_CPP 
#define VIEW_CPP

#include <iostream>
#include <memory>
#include <cstdlib>
#include <ctime>
// include header files
#include <ViewTriPeaks.hpp>

View::View() {}
View::~View() {}

void View::initiateView(std::shared_ptr<std::vector<std::vector<Node>>> graph_, 
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> drawPile_, 
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> wastePile_, 
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> movePile_, 
    std::shared_ptr<Deck> deck_) {
    graph = graph_;
    drawPile = drawPile_;
    wastePile = wastePile_;
    movePile = movePile_;
    deck = deck_;
    cardHeight = deck->getTopSprite()->getGlobalBounds().height;
    cardWidth = deck->getTopSprite()->getGlobalBounds().width;
    stackDistance = (int)(cardHeight / 2);
    image.create(bounds_width, bounds_height, sf::Color::Black);
    texture.loadFromImage(image);
    sprite.setTexture(texture);
}

// checks if clicked on a graph node
Node* View::getClickOnGraph(sf::Vector2f mousePos) {
    // check nodes from bottom to top
    for (int i = 3; i >= 0; i--) {
        for (int j = 0; j < i + 7; j++) {
            if (!graph->at(i).at(j).empty()) {
                if (graph->at(i).at(j).getCard()->getPSprite()->getGlobalBounds().contains(mousePos)) {
                    return &(graph->at(i).at(j));
                }
            }
        }
    }
    return nullptr;
}

// checks if clicked on pile
std::shared_ptr<std::vector<std::shared_ptr<Card>>> View::getClickOnPiles(sf::Vector2f mousePos) {
    // only registers click if pile is not empty
    if (!drawPile->empty()) {
        if (drawPile->back()->getPSprite()->getGlobalBounds().contains(mousePos)) {
            return drawPile;
        }
    }
    if (!wastePile->empty()) {
        if (wastePile->back()->getPSprite()->getGlobalBounds().contains(mousePos)) {
            return wastePile;
        }
    }
    return nullptr;
}

// sets position of all sprites except movePile
void View::setPosition() {
    // set position of sprites in graph
    // row 0
    for (int i = 0; i < 7; i += 3) {
        if (!graph->at(0).at(i).empty()) {
            graph->at(0).at(i).getCard()->getPSprite()->setPosition(startPointX - cardWidth / 2 - cardWidth * 3 -
            distBtwCards * 3 + cardWidth * i + distBtwCards * i, startPointY);
        }
    }
    // row 1
    for (int i = 0; i < 8; i++) {
        if (!graph->at(1).at(i).empty()) {
            graph->at(1).at(i).getCard()->getPSprite()->setPosition(startPointX - cardWidth * 4 - distBtwCards / 2 -
            distBtwCards * 3 + cardWidth * i + distBtwCards * i, startPointY + stackDistance);
        }
    }
    // row 2
    for (int i = 0; i < 9; i++) {
        if (!graph->at(2).at(i).empty()) {
            graph->at(2).at(i).getCard()->getPSprite()->setPosition(startPointX - cardWidth / 2 - cardWidth * 4 -
            distBtwCards * 4 + cardWidth * i + distBtwCards * i, startPointY + stackDistance * 2);
        }
    }
    // row 3
    for (int i = 0; i < 10; i++) {
        if (!graph->at(3).at(i).empty()) {
            graph->at(3).at(i).getCard()->getPSprite()->setPosition(startPointX - cardWidth * 5 - distBtwCards / 2 -
            distBtwCards * 4 + cardWidth * i + distBtwCards * i, startPointY + stackDistance * 3);
        }
    }
    // set position of sprites in piles
    // drawPile
    if (!drawPile->empty()) {
        drawPile->back()->getPSprite()->setPosition(startPointX - distBtwPiles / 2 - cardWidth, startPointY +
        stackDistance * 3 + cardHeight + startPointY);
    }
    // wastePile
    if (!wastePile->empty()) {
        wastePile->back()->getPSprite()->setPosition(startPointX + distBtwPiles / 2, startPointY +
        stackDistance * 3 + cardHeight + startPointY);
    }
}

void View::draw(sf::RenderWindow* window) {
    window->clear();
    // set all sprite positions
    setPosition();
    // draw all relevant sprites in graph
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < i + 7; j++) {
            if (!graph->at(i).at(j).empty()) {
                window->draw(*(graph->at(i).at(j).getCard()->getPSprite()));
            }
        }
    }
    // draw all relevant sprites in piles
    if (!drawPile->empty()) {
        window->draw(*(drawPile->back()->getPSprite()));
    }
    if (!wastePile->empty()) {
        window->draw(*(wastePile->back()->getPSprite()));
    }
    if (!movePile->empty()) {
        window->draw(*(movePile->back()->getPSprite()));
    }

    window->display();
}

void View::drawAnimation(sf::RenderWindow* window) {
    window->clear();
    
    // draw all relevant sprites in graph
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < i + 7; j++) {
            if (!graph->at(i).at(j).empty()) {
                window->draw(*(graph->at(i).at(j).getCard()->getPSprite()));
            }
        }
    }
    // draw all relevant sprites in piles
    if (!drawPile->empty()) {
        window->draw(*(drawPile->back()->getPSprite()));
    }
    

    window->display();
}

void View::animateCardGraph(sf::RenderWindow* window, int xPos, int yPos) {
    // animate cards in movePile to xPos, yPos
    if (movePile->empty()) {
        return;
    }
    int num_frames = 50;
    sf::Vector2f beg_pos = movePile->back()->getPSprite()->getPosition();
    float x1 = beg_pos.x;
    float y1 = beg_pos.y;
    float x2 = (float) xPos;
    float y2 = (float) yPos;
    
    float x_to_move = (x2 - x1) / num_frames;
    float y_to_move = (y2 - y1) / num_frames;
    // animate card
    for (int i = 0; i < num_frames; i++) {
        x1 += x_to_move;
        y1 += y_to_move;
        movePile->back()->getPSprite()->setPosition(x1, y1);
            
        draw(window);
    }
}

void View::animateCardDrawPile(sf::RenderWindow* window, int xPos, int yPos) {
    // animate cards in movePile to xPos, yPos
    if (movePile->empty()) {
        return;
    }
    int num_frames = 30;
    sf::Vector2f beg_pos = movePile->back()->getPSprite()->getPosition();
    float x1 = beg_pos.x;
    float y1 = beg_pos.y;
    float x2 = (float) xPos;
    float y2 = (float) yPos;
    
    float x_to_move = (x2 - x1) / num_frames;
    float y_to_move = (y2 - y1) / num_frames;
    // animate card
    for (int i = 0; i < num_frames; i++) {
        x1 += x_to_move;
        y1 += y_to_move;
        movePile->back()->getPSprite()->setPosition(x1, y1);
            
        draw(window);
    }
}

// animation at deal
void View::dealAnimation(sf::RenderWindow* window) {
    int numFrames = 200;
    // set position of drawPile
    if (!drawPile->empty()) {
        drawPile->back()->getPSprite()->setPosition(startPointX - distBtwPiles / 2 - cardWidth, startPointY +
        stackDistance * 3 + cardHeight + startPointY);
    }
    // create vector to hold all wrappers
    std::vector<AnimationWrapper> ani_vec;
    // create wrappers for each card in graph
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < i + 7; j++) {
            if (!graph->at(i).at(j).empty()) {
                ani_vec.push_back(AnimationWrapper(graph->at(i).at(j).getCard()->getPSprite(), 
                (float)this->getXPositionNode(i, j), (float)(startPointY + stackDistance * 3), 
                (float)this->getXPositionNode(i, j), (float)this->getYPositionNode(i), numFrames));
            }
        }
    }
    
    // loop number of frames and advance each animation
    for (int i = 0; i < numFrames; i++) {
        //window->clear();
        for (auto wrapper : ani_vec) {
            wrapper.advance(i);
            //std::cout << "wrapper advanced\n";
        }
        drawAnimation(window);
        //std::cout << i << std::endl;
    }
}

// creates animation after a win
void View::animateWin(sf::RenderWindow* window) {
    srand((unsigned) time(0));
    Deck deck1 = Deck();
    Deck deck2 = Deck();
    Deck deck3 = Deck();
    Deck deck4 = Deck();
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> card_vec = std::make_shared<std::vector<std::shared_ptr<Card>>>();
    while (!deck1.isEmpty()) {
        deck1.dealCard(card_vec);
        card_vec->back()->setFaceUp(true);
    }
    while (!deck2.isEmpty()) {
        deck2.dealCard(card_vec);
        card_vec->back()->setFaceUp(true);
    }
    while (!deck3.isEmpty()) {
        deck3.dealCard(card_vec);
        card_vec->back()->setFaceUp(true);
    }
    while (!deck4.isEmpty()) {
        deck4.dealCard(card_vec);
        card_vec->back()->setFaceUp(true);
    }
    // continue while loop till key is pressed or mouse clicked
    bool animation = true;
    while (animation) {
        sf::Event event;
        while (window->pollEvent(event)) {
            if(event.type == sf::Event::MouseButtonReleased) {
                animation = false;
                break;
            }
            else if (event.type == sf::Event::Closed) {
				//window->close();
                animation = false;
                break;
			}
            else if (event.type == sf::Event::KeyReleased) {
                animation = false;
                break;
            }
        }
        if (animation == false) {
            break;
        }
        // code card burst here
        // create wrapper vec
        int numFrames = 2400;
        std::vector<AnimationWrapper> ani_vec;
        int i = 0;
        for (auto item : *card_vec) {
            AnimationWrapper wrapper = AnimationWrapper(item->getPSprite(), bounds_width / 2 - cardWidth / 2, 
                bounds_height / 2 - cardHeight / 2,
                (rand() % (bounds_width + 200)) - 100, (rand() % (bounds_height + 200)) - 100, numFrames);
            wrapper.setID(i);
            ani_vec.push_back(wrapper);
            i++;
        }
        // iterate through ani_vec, adding one each time
        for (int i = 0; i < (int)ani_vec.size() - 1; i++) {
            window->clear();
            for (int j = 0; j < i + 1; j++) {
                ani_vec.at(j).advance(i - ani_vec.at(j).getID());
                window->draw(*(ani_vec.at(j).getPSprite()));
            }
            window->display();
        }
        // keep animating more frames
        for (int i = (int)ani_vec.size(); i < (int)ani_vec.size() + 200; i++) {
            window->clear();
            for (int j = 0; j < (int)ani_vec.size(); j++) {
                ani_vec.at(j).advance(i - ani_vec.at(j).getID());
                window->draw(*(ani_vec.at(j).getPSprite()));
            }
            window->display();
        }
    }
}

// getter method for bounds_width
int View::getBoundsWidth() {
    return bounds_width;
}

// getter method for bounds_height
int View::getBoundsHeight() {
    return bounds_height;
}

int View::getXPositionWastePile() {
    return (int)(startPointX + distBtwPiles / 2);
}

int View::getYPositionWastePile() {
    return (int)(startPointY + stackDistance * 3 + cardHeight + startPointY);
}

int View::getXPositionDrawPile() {
    return (int)(startPointX - distBtwPiles / 2 - cardWidth);
}

int View::getYPositionDrawPile() {
    return (int)(startPointY + stackDistance * 3 + cardHeight + startPointY);
}

int View::getXPositionNode(int posI, int posJ) {
    // return x coordinate of position of node
    if (posI == 0) {
        return (int)(startPointX - cardWidth / 2 - cardWidth * 3 -
            distBtwCards * 3 + cardWidth * posJ + distBtwCards * posJ);
    }
    else if (posI == 1) {
        return (int)(startPointX - cardWidth * 4 - distBtwCards / 2 -
            distBtwCards * 3 + cardWidth * posJ + distBtwCards * posJ);
    }
    else if (posI == 2) {
        return (int)(startPointX - cardWidth / 2 - cardWidth * 4 -
            distBtwCards * 4 + cardWidth * posJ + distBtwCards * posJ);
    }
    else if (posI == 3) {
        return (int)(startPointX - cardWidth * 5 - distBtwCards / 2 -
            distBtwCards * 4 + cardWidth * posJ + distBtwCards * posJ);
    }
    return 0;
}

int View::getYPositionNode(int posI) {
    if (posI == 0) {
        return (int)(startPointY);
    }
    else if (posI == 1) {
        return (int)(startPointY + stackDistance);
    }
    else if (posI == 2) {
        return (int)(startPointY + stackDistance * 2);
    }
    else if (posI == 3) {
        return (int)(startPointY + stackDistance * 3);
    }
    return 0;
}

#endif