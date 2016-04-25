#include "Level.hpp"

sf::Vector2i Level::getCoordToLevel(int x, int y)
{
    sf::Vector2i result;
    result.x = Level::GRILLE_BEGIN_X + (y - x) * Level::TILE_WIDTH_HALF;
    result.y = Level::GRILLE_BEGIN_Y + (y + x +1) * Level::TILE_HEIGHT_HALF;
    return result;
}

sf::Vector2i Level::getCoordToReal(int x, int y)
{
    int RealX = x - GRILLE_BEGIN_X ;
    int RealY = y - GRILLE_BEGIN_Y ;
    int newGRILLE_BEGIN_X = ((RealX * TILE_HEIGHT_HALF + RealY * TILE_WIDTH_HALF) / (2 * TILE_HEIGHT_HALF * TILE_WIDTH_HALF)) ;
    int newGRILLE_BEGIN_Y = ((-RealX * TILE_HEIGHT_HALF + RealY * TILE_WIDTH_HALF) / (2 * TILE_HEIGHT_HALF * TILE_WIDTH_HALF));

    return sf::Vector2i(newGRILLE_BEGIN_X , newGRILLE_BEGIN_Y);
}

Level::Level(TextureManager& textureManager, sf::RenderWindow& window)
: GRILLE_SIZE(30)
, mTileLIst(GRILLE_SIZE)
, mBlockList(GRILLE_SIZE)
, mBlockWallList(4)
, mTextureManager(textureManager)
, mWindow(window)
, lastTileX(0)
, lastTileY(0)
, WINDOW_WIDTH(window.getSize().x)
, WINDOW_HEIGHT(window.getSize().y)
, GRILLE_BEGIN_X(WINDOW_WIDTH / 2)
, GRILLE_BEGIN_Y(41)
, TILE_HEIGHT_HALF(Tile::HEIGHT / 2 )
, TILE_WIDTH_HALF(Tile::WIDTH / 2 )
, mPlayer(textureManager, 0, 0)
, mPPosX(0)
, mPPosY(0)
,way()
{
    for(int i = 0; i < GRILLE_SIZE; i++)
        for(int j = 0; j < GRILLE_SIZE; j++)
                mBlockGrille[i][j] = -1;

    for(int i = 0; i < GRILLE_SIZE; i++)
    {
        mTileLIst[i].resize(GRILLE_SIZE);
        for(int j = 0; j < GRILLE_SIZE; j++)
        {
            sf::Vector2i temp = getCoordToLevel(i , j);
            mTileLIst[i][j] = new Tile(textureManager, temp.x, temp.y);
        }
    }

    for(int i = 0; i < GRILLE_SIZE; i++)
    {
        mBlockList[i].resize(GRILLE_SIZE);
        for(int j = 0; j < GRILLE_SIZE; j++)
        {
            mBlockList[i][j] = nullptr;
        }
    }

    for(int i = 0; i < 4; i++)
    {
        mBlockWallList[i].resize(GRILLE_SIZE + 2);
        for(int j = 0; j < GRILLE_SIZE + 2; j++)
        {
            mBlockWallList[i][j] = nullptr;
        }
    }

    for(int j = -1; j <= GRILLE_SIZE; j++)
    {
        int i = 0;
        sf::Vector2i temp = getCoordToLevel(i - 2 , j - 1);
        mBlockWallList[i][j+1] = new Block(textureManager, temp.x, temp.y, TypeBlock::WALL);
    }


    for(int j = 0; j <= GRILLE_SIZE; j++)
    {
        int i = 1;
        sf::Vector2i temp = getCoordToLevel( j - 1,i - 3);
        mBlockWallList[i][j+1] = new Block(textureManager, temp.x, temp.y, TypeBlock::WALL);
    }

    for(int j = 0; j <= GRILLE_SIZE; j++)
    {
        int i = 2;
        sf::Vector2i temp = getCoordToLevel(i - 3 + GRILLE_SIZE, j - 1 );
        mBlockWallList[i][j+1] = new Block(textureManager, temp.x, temp.y, TypeBlock::WALL);
        mBlockWallList[i][j+1]->transparent();
    }


    for(int j = 0; j < GRILLE_SIZE; j++)
    {
        int i = 3;
        sf::Vector2i temp = getCoordToLevel(j - 1 , i - 4 + GRILLE_SIZE);
        mBlockWallList[i][j+1] = new Block(textureManager, temp.x, temp.y, TypeBlock::WALL);
        mBlockWallList[i][j+1]->transparent();
    }

    sf::Vector2i newGRILLE_BEGIN = getCoordToLevel(GRILLE_SIZE - 1,0);
    mPlayer.setPosition(newGRILLE_BEGIN.x,newGRILLE_BEGIN.y);

    sf::Vector2i newBEGIN = getCoordToReal(mPlayer.getPosition().x,mPlayer.getPosition().y);
    mPPosX = newBEGIN.x;
    mPPosY = newBEGIN.y;
}


void Level::draw(sf::RenderWindow& window)
{
	
    for(int i = 0; i < 2; i++)
        for(int j = 0; j < GRILLE_SIZE + 2; j++)
            if(mBlockWallList[i][j] != nullptr)
                 mBlockWallList[i][j]->draw(window);

    for(int i = 0; i < GRILLE_SIZE; i++)
        for(int j = 0; j < GRILLE_SIZE; j++)
            mTileLIst[i][j]->draw(window);

    for(int i = 0; i < GRILLE_SIZE; i++)
        for(int j = 0; j < GRILLE_SIZE; j++)
            if(mBlockList[i][j] != nullptr)
                mBlockList[i][j]->draw(window);

    mPlayer.draw(window);

    for(int i = 2; i < 4; i++)
        for(int j = 0; j < GRILLE_SIZE + 2; j++)
            if(mBlockWallList[i][j] != nullptr)
                 mBlockWallList[i][j]->draw(window);
}

void Level::update(sf::Time dt)
{

}



void Level::handleEvent(const sf::Event& event)
{
    if(event.type == sf::Event::MouseMoved)
    {
        sf::Vector2i localPosition = sf::Mouse::getPosition(mWindow);
        sf::Vector2i newGRILLE_BEGIN = getCoordToReal(localPosition.x,localPosition.y);

        if(newGRILLE_BEGIN.x >= 0 && newGRILLE_BEGIN.x < GRILLE_SIZE && newGRILLE_BEGIN.y >= 0 && newGRILLE_BEGIN.y < GRILLE_SIZE)
        {
            if(newGRILLE_BEGIN.x != lastTileX ||  newGRILLE_BEGIN.y != lastTileY)
            {
                mTileLIst[newGRILLE_BEGIN.y][newGRILLE_BEGIN.x]->focus();
                mTileLIst[lastTileY][lastTileX]->unfocus();
                lastTileX = newGRILLE_BEGIN.x;
                lastTileY = newGRILLE_BEGIN.y;
            }
        }
    }

    if(event.type == sf::Event::MouseButtonPressed)
    {
        if(event.mouseButton.button == sf::Mouse::Button::Right)
        {
            if(mBlockList[lastTileY][lastTileX] != nullptr)
            {
                delete mBlockList[lastTileY][lastTileX];
                mBlockList[lastTileY][lastTileX] = nullptr;
                mBlockGrille[lastTileY][lastTileX] = -1;
            }
            else
            {
                sf::Vector2i newBEGIN = getCoordToReal(mPlayer.getPosition().x,mPlayer.getPosition().y);
                if(lastTileX != newBEGIN.x || newBEGIN.y != lastTileY)
                {

                    int tx = mTileLIst[lastTileY][lastTileX]->getPosition().x;
                    int ty = mTileLIst[lastTileY][lastTileX]->getPosition().y - 20; // 20 высота грани куба в изо
                    Block* pBlock =  new Block(mTextureManager,tx ,ty, TypeBlock::NORNMALL);
                    pBlock->untransparent();
                    mBlockList[lastTileY][lastTileX] = pBlock;

                    mBlockGrille[lastTileY][lastTileX] = -3;
                }
            }
        }

        if(event.mouseButton.button == sf::Mouse::Button::Left)
        {
            if(mBlockList[lastTileY][lastTileX] == nullptr)
            {
                int tx = mTileLIst[lastTileY][lastTileX]->getPosition().x;
                int ty = mTileLIst[lastTileY][lastTileX]->getPosition().y;

                sf::Vector2i newBEGIN = getCoordToReal(mPlayer.getPosition().x,mPlayer.getPosition().y);
                mBlockGrille[newBEGIN.y][newBEGIN.x] = 0;
                mBlockGrille[lastTileY][lastTileX] = -2;

                if(!(lastTileX == newBEGIN.x && lastTileY == newBEGIN.y))
                {

                    for(auto i : way)
                    {
                        mTileLIst[i.x][i.y]->unsetWay();
                    }

                    way = mPlayer.setWay(lastTileX, lastTileY, mBlockGrille);
					if (way.size() != 0)
					{
						mPlayer.setPosition(tx, ty);


						for (auto i : way)
						{
							mTileLIst[i.x][i.y]->setWay();
						}
					}

					mBlockGrille[newBEGIN.y][newBEGIN.x] = -1;

					mBlockGrille[lastTileY][lastTileX] = -1;
                }
            }
        }
    }
}




