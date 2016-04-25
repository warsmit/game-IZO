#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System.hpp>

#include "TextureManager.hpp"



class Player
{

public:
    static const int WIDTH = 39;
    static const int HEIGHT = 21;
public:
    Player(TextureManager& textureManager, int x, int y);
    void draw(sf::RenderWindow& window);
    void update(float time);
    void setPosition(int x, int y);
    std::vector<sf::Vector2i> setWay(int x, int y, std::array<std::array<char, 30>, 30> blockGrille);
    sf::Vector2i getPosition();
private:
    sf::Texture& mTexture;
    sf::Sprite mSprite;
    int mX;
    int mY;
    int speed = 1;
};

#endif // PLAYER_H

