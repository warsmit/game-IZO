#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>

#include "Level.hpp"
#include "TextureManager.hpp"

class Game
{
public:
    Game();
    void run();
private:
    void update(sf::Time elapsedTime);
    void render();
    void processInput();
private:
    static const int        HEIGHT = 600 + 42*1.5;
    static const int        WIDTH = 1200 + 39 /2 ;
    static const sf::Time   TIME_PER_FRAME;
private:
    sf::RenderWindow    mWindow;
    TextureManager      mTextureManager;
    Level               mLevel;
};


#endif // GAME_H
