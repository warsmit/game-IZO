#include "Game.hpp"

const sf::Time Game::TIME_PER_FRAME = sf::seconds(1.f/60.f);

void upload(TextureManager& me)
{
    me.load(ID::Texture::TILE,          "texture/tile.png");
    me.load(ID::Texture::TILE_FOCUS,    "texture/tile_focus.png");
    me.load(ID::Texture::TILE_WAY,      "texture/tile_way.png");
    me.load(ID::Texture::BLOCK_WALL,    "texture/block_wall.png");
    me.load(ID::Texture::BLOCK_NORMAL,  "texture/block_normal.png");
    me.load(ID::Texture::BLOCK_WALL_TRANSPARENT,    "texture/block_wall_transparent.png");
    me.load(ID::Texture::BLOCK_NORMAL_TRANSPARENT,  "texture/block_normal_transparent.png");

    me.load(ID::Texture::PLAYER, "texture/player.png");
}

Game::Game()
: mWindow(sf::VideoMode(WIDTH, HEIGHT), "IZO", sf::Style::Default)
, mTextureManager(upload)
, mLevel(mTextureManager, mWindow)
{
    srand(time(NULL));
    mWindow.setFramerateLimit(60);
}

void Game::run()
{

    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    while (mWindow.isOpen())
    {
        sf::Time elapsedTime = clock.restart();
        timeSinceLastUpdate += elapsedTime;
        while (timeSinceLastUpdate > TIME_PER_FRAME)
        {
            processInput();
            timeSinceLastUpdate -= TIME_PER_FRAME;
            update(TIME_PER_FRAME);
        }
        render();
    }
}

void Game::update(sf::Time elapsedTime)
{
    mLevel.update(elapsedTime);
}

void Game::render()
{
    mWindow.clear(sf::Color::Black);
    mLevel.draw(mWindow);
    mWindow.display();
}

void Game::processInput()
{
    sf::Event event;
    while (mWindow.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            mWindow.close();
        mLevel.handleEvent(event);
    }
}



