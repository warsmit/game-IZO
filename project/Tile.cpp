#include "Tile.hpp"

Tile::Tile(TextureManager& textureManager, int x, int y)
    : mTexture(textureManager.get(ID::Texture::TILE))
    , mTextureRed(textureManager.get(ID::Texture::TILE_FOCUS))
    , mTextureWay(textureManager.get(ID::Texture::TILE_WAY))
    , mX(x)
    , mY(y)
{
    mSprite.setOrigin(WIDTH / 2, HEIGHT / 2);
    mSprite.setTexture(mTexture);
    mSprite.setPosition(mX, mY);
}

void Tile::draw(sf::RenderWindow& window)
{
    window.draw(mSprite);
}

void Tile::focus()
{
     mSprite.setTexture(mTextureRed);
}

void Tile::unfocus()
{
     mSprite.setTexture(mTexture);
}

sf::Vector2i Tile::getPosition()
{
    return sf::Vector2i(mX,mY);
}

bool Tile::isFocus()
{
    return mSprite.getTexture() == &mTexture;
}


void Tile::setWay()
{
    mSprite.setTexture(mTextureWay);
}

void Tile::unsetWay()
{
     mSprite.setTexture(mTexture);
}
