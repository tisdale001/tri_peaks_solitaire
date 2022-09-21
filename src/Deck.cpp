// deck.cpp
// a deck of cards for solitaire
//g++ -std=c++17 ./src/Card.cpp ./src/Deck.cpp -I./include/ -o deck -lsfml-graphics -lsfml-window -lsfml-system
#ifndef DECK_CPP 
#define DECK_CPP

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iostream>

#include <Deck.hpp>
#include <Card.hpp>

void Deck::createDeck() {
    // create front images
    std::vector<std::string> INameVec{"../deckOfCards/aceOfHearts.png", "../deckOfCards/twoOfHearts.png", 
    "../deckOfCards/threeOfHearts.png", 
    "../deckOfCards/fourOfHearts.png", "../deckOfCards/fiveOfHearts.png", "../deckOfCards/sixOfHearts.png", 
    "../deckOfCards/sevenOfHearts.png", "../deckOfCards/eightOfHearts.png",
    "../deckOfCards/nineOfHearts.png", "../deckOfCards/tenOfHearts.png", "../deckOfCards/jackOfHearts.png", 
    "../deckOfCards/queenOfHearts.png", "../deckOfCards/kingOfHearts.png",
    "../deckOfCards/aceOfDiamonds.png", "../deckOfCards/twoOfDiamonds.png", "../deckOfCards/threeOfDiamonds.png", 
    "../deckOfCards/fourOfDiamonds.png", "../deckOfCards/fiveOfDiamonds.png",
    "../deckOfCards/sixOfDiamonds.png", "../deckOfCards/sevenOfDiamonds.png", "../deckOfCards/eightOfDiamonds.png", 
    "../deckOfCards/nineOfDiamonds.png", "../deckOfCards/tenOfDiamonds.png",
    "../deckOfCards/jackOfDiamonds.png", "../deckOfCards/queenOfDiamonds.png", "../deckOfCards/kingOfDiamonds.png", 
    "../deckOfCards/aceOfSpades.png", "../deckOfCards/twoOfSpades.png", 
    "../deckOfCards/threeOfSpades.png", "../deckOfCards/fourOfSpades.png", "../deckOfCards/fiveOfSpades.png", 
    "../deckOfCards/sixOfSpades.png", "../deckOfCards/sevenOfSpades.png",
    "../deckOfCards/eightOfSpades.png", "../deckOfCards/nineOfSpades.png", "../deckOfCards/tenOfSpades.png", 
    "../deckOfCards/jackOfSpades.png", "../deckOfCards/queenOfSpades.png", 
    "../deckOfCards/kingOfSpades.png", "../deckOfCards/aceOfClubs.png", "../deckOfCards/twoOfClubs.png", 
    "../deckOfCards/threeOfClubs.png", "../deckOfCards/fourOfClubs.png", "../deckOfCards/fiveOfClubs.png",
    "../deckOfCards/sixOfClubs.png", "../deckOfCards/sevenOfClubs.png", "../deckOfCards/eightOfClubs.png", 
    "../deckOfCards/nineOfClubs.png", "../deckOfCards/tenOfClubs.png", 
    "../deckOfCards/jackOfClubs.png", "../deckOfCards/queenOfClubs.png", "../deckOfCards/kingOfClubs.png"};
    for (int i = 0; i < 52; i++) {
        std::shared_ptr<sf::Image> p_image = std::make_shared<sf::Image>();
        p_image->loadFromFile(INameVec[i]);
        pImageVec.push_back(p_image);
    }
    // create front textures
    for (int i = 0; i < 52; i++) {
        std::shared_ptr<sf::Texture> p_texture = std::make_shared<sf::Texture>();
        p_texture->loadFromImage(*pImageVec[i]);
        pTextureVec.push_back(p_texture);
    }
    // create front sprites
    for (int i = 0; i < 52; i++) {
        std::shared_ptr<sf::Sprite> p_sprite = std::make_shared<sf::Sprite>();
        p_sprite->setTexture(*pTextureVec[i]);
        p_sprite->setScale(scaleX, scaleY);
        pFrontSpriteVec.push_back(p_sprite);
    }
    //create back image
    std::shared_ptr<sf::Image> p_back_image = std::make_shared<sf::Image>();
    p_back_image->loadFromFile("../deckOfCards/backOfCard.png");
    pBackImageVec.push_back(p_back_image);
    // create back texture
    std::shared_ptr<sf::Texture> p_back_texture = std::make_shared<sf::Texture>();
    p_back_texture->loadFromImage(*pBackImageVec[0]);
    pBackTextureVec.push_back(p_back_texture);
    // create back sprites
    for (int i = 0; i < 52; i++) {
        std::shared_ptr<sf::Sprite> p_back_sprite = std::make_shared<sf::Sprite>();
        p_back_sprite->setTexture(*pBackTextureVec[0]);
        p_back_sprite->setScale(scaleX, scaleY);
        pBackSpriteVec.push_back(p_back_sprite);
    }
    // create cards
    std::vector<std::string> symbolVec{"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
    // hearts
    for (int i = 1; i < 14; i++) {
        std::shared_ptr<Card> card = std::make_shared<Card>(symbolVec[i - 1], "H", "R", i, pFrontSpriteVec[i - 1], 
            pBackSpriteVec[i - 1]);
        deckOfCards.push_back(card);
    }
    // diamonds
    for (int i = 1; i < 14; i++) {
        std::shared_ptr<Card> card = std::make_shared<Card>(symbolVec[i - 1], "D", "R", i, pFrontSpriteVec[i + 12], 
            pBackSpriteVec[i + 12]);
        deckOfCards.push_back(card);
    }
    // spades
    for (int i = 1; i < 14; i++) {
        std::shared_ptr<Card> card = std::make_shared<Card>(symbolVec[i - 1], "S", "B", i, pFrontSpriteVec[i + 25], 
            pBackSpriteVec[i + 25]);
        deckOfCards.push_back(card);
    }
    // clubs
    for (int i = 1; i < 14; i++) {
        std::shared_ptr<Card> card = std::make_shared<Card>(symbolVec[i - 1], "C", "B", i, pFrontSpriteVec[i + 38], 
            pBackSpriteVec[i + 38]);
        deckOfCards.push_back(card);
    }
    
    

}

void Deck::shuffleDeck() {
    //create vector and copy to it
    std::vector<std::shared_ptr<Card>> copyVec;
    long unsigned int size = deckOfCards.size();
    for (long unsigned int i = 0; i < size; i++) {
        copyVec.push_back(deckOfCards.back());
        deckOfCards.pop_back();
    }
    //put back at random
    srand(time(NULL));
    while (!copyVec.empty()) {
        int num = rand() % copyVec.size();
        deckOfCards.push_back(copyVec[num]);
        copyVec.erase(copyVec.begin() + num);
    }
    
}

Deck::Deck() {
    createDeck();
    shuffleDeck();
}

Deck::~Deck() {
    //std::cout << "Deck deconstructor called\n";
    deckOfCards.clear();
    pImageVec.clear();
    pBackImageVec.clear();
    pTextureVec.clear();
    pBackTextureVec.clear();
    pFrontSpriteVec.clear();
    pBackSpriteVec.clear();
}

bool Deck::isEmpty() {
    if (deckOfCards.empty()) {
        return true;
    }
    return false;
}

int Deck::dealCard(std::shared_ptr<std::vector<std::shared_ptr<Card>>> pile) {
    if (!deckOfCards.empty()) {
        std::shared_ptr<Card> p_card = deckOfCards.back();
        p_card->setFaceUp(false);
        pile->push_back(p_card);
        deckOfCards.pop_back();
        return 1;
    }
    return -1;
}

void Deck::returnCards(std::shared_ptr<std::vector<std::shared_ptr<Card>>> pile) {
    if (!pile->empty()) {
        while (!pile->empty()) {
            std::shared_ptr<Card> p_card = pile->back();
            p_card->setFaceUp(false);
            deckOfCards.push_back(p_card);
            pile->pop_back();
        }
    }
    return;
}

std::shared_ptr<sf::Sprite> Deck::getTopSprite() {
    return deckOfCards.back()->getPSprite();
}


#endif