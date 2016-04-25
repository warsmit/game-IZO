#ifndef LEVEL_H
#define LEVEL_H

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include "TextureManager.hpp"
#include "Tile.hpp"
#include "Block.hpp"
#include "Player.hpp"

class Level
{
public:

public:
    Level(TextureManager& textureManager, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
    void update(sf::Time dt);
    void handleEvent(const sf::Event& event);
private:
    const int GRILLE_SIZE;
    std::vector<std::vector<Tile*> > mTileLIst;
    std::vector<std::vector<Block*> > mBlockList;

    std::vector<std::vector<Block*> > mBlockWallList;

    TextureManager& mTextureManager;
    sf::RenderWindow& mWindow;

    int lastTileX;
    int lastTileY;
    sf::Vector2i getCoordToLevel(int x, int y);
    sf::Vector2i getCoordToReal(int x, int y);
    const int WINDOW_WIDTH;
    const int WINDOW_HEIGHT;
    const int GRILLE_BEGIN_X;
    const int GRILLE_BEGIN_Y;

    const int TILE_HEIGHT_HALF;
    const int TILE_WIDTH_HALF;

        Player mPlayer;
		std::array<std::array<char, 30>, 30> mBlockGrille;
        int mPPosX;
        int mPPosY;
        std::vector<sf::Vector2i> way;
};

#endif // LEVEL_H

