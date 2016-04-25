#include "TextureManager.hpp"

TextureManager::TextureManager(void(&fun)(TextureManager& textureManager))
{
    fun(*this);
}

void TextureManager::load(const ID::Texture& id, const std::string& filename)
{
    std::unique_ptr<sf::Texture> texture(new sf::Texture);
    if (!texture->loadFromFile(filename))
        throw std::runtime_error("TextureManager::load - Failed to load " + filename);

    insertTexture(id, std::move(texture));
}

sf::Texture& TextureManager::get(const ID::Texture& id)
{
    auto found = mTextureMap.find(id);
    assert(found != mTextureMap.end());
    return *found->second;
}

const sf::Texture& TextureManager::get(const ID::Texture& id) const
{
    auto found = mTextureMap.find(id);
    assert(found != mTextureMap.end());
    return *found->second;
}

void TextureManager::insertTexture(const ID::Texture& id, std::unique_ptr<sf::Texture> texture)
{
    auto insert = mTextureMap.insert(std::make_pair(id, std::move(texture)));
    assert(insert.second);
}
