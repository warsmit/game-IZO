#ifndef BLOCK_H
#define BLOCK_H


#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "TextureManager.hpp"

enum TypeBlock
{
    WALL,
    NORNMALL,
    WALL_GUN,
};



class Block
{
public:
    static const int WIDTH = 39;
    static const int HEIGHT = 21;
public:
    Block();
public:
    Block(TextureManager& textureManager, int x, int y, TypeBlock type);
    void draw(sf::RenderWindow& window);

    void transparent();
    void untransparent();
private:
    sf::Texture& mTexture;
    sf::Texture& mTextureTransparent;
    sf::Sprite mSprite;
    int mX;
    int mY;
};

#endif // BLOCK_H
