#ifndef TILE_H
#define TILE_H


#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "TextureManager.hpp"
#include "Block.hpp"


class Tile
{
public:
    static const int WIDTH = 39;
    static const int HEIGHT = 21;
public:
    Tile(TextureManager& textureManager, int x, int y);
    void draw(sf::RenderWindow& window);
    void focus();
    void unfocus();
    bool isFocus();
    void setWay();
    void unsetWay();
    sf::Vector2i getPosition();
private:
    sf::Texture& mTexture;
    sf::Texture& mTextureRed;
    sf::Texture& mTextureWay;
    sf::Sprite mSprite;
    int mX;
    int mY;
    Block* mBlock;
};

#endif // TILE_H


