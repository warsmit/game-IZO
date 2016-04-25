#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <map>
#include <memory>
#include <string>
#include <stdexcept>
#include <cassert>
#include <array>
#include <vector>
#include <math.h>

#include <SFML/Graphics/Texture.hpp>

#include "Identifiers.hpp"

class TextureManager;
void upload(TextureManager& textureManager);

class TextureManager
{
public:
    TextureManager(void(&fun)(TextureManager&));
    void load(const ID::Texture& id, const std::string& filename);
    sf::Texture& get(const ID::Texture& id);
    const sf::Texture& get(const ID::Texture& id) const;
private:
    void insertTexture(const ID::Texture& id, std::unique_ptr<sf::Texture> texture);
private:
    std::map<ID::Texture, std::unique_ptr<sf::Texture>> mTextureMap;
};

#endif // TEXTUREMANAGER_H
