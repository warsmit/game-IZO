#include "Block.hpp"

sf::Texture& getTextureForType(TextureManager& textureManager, TypeBlock type, bool isTransparent )
{
    switch (type)
    {
    case WALL:
        if(isTransparent)
            return textureManager.get(ID::Texture::BLOCK_WALL_TRANSPARENT);
        else
            return textureManager.get(ID::Texture::BLOCK_WALL);
    case NORNMALL:
        if(isTransparent)
            return textureManager.get(ID::Texture::BLOCK_NORMAL_TRANSPARENT);
        else
            return textureManager.get(ID::Texture::BLOCK_NORMAL);
        break;
    case WALL_GUN:
        if(isTransparent)
            return textureManager.get(ID::Texture::BLOCK_WALL_TRANSPARENT_GUN);
        else
            return textureManager.get(ID::Texture::BLOCK_WALL_GUN);
        break;
    default:
        break;
    }
}

void Block::transparent()
{
    mSprite.setTexture(mTextureTransparent);
}

void Block::untransparent()
{
    mSprite.setTexture(mTexture);
}


Block::Block(TextureManager& textureManager, int x, int y,TypeBlock type )
    : mTexture(getTextureForType(textureManager, type , false))
    , mTextureTransparent(getTextureForType(textureManager, type , true))
    , mX(x)
    , mY(y)
{
    mSprite.setOrigin(WIDTH / 2, HEIGHT / 2);
    mSprite.setTexture(mTexture);
    mSprite.setPosition(mX, mY);

}

void Block::draw(sf::RenderWindow& window)
{
    window.draw(mSprite);
}
