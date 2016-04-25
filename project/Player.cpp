#include "Player.hpp"

Player::Player(TextureManager& textureManager, int x, int y)
: mTexture(textureManager.get(ID::Texture::PLAYER))
, mX(x)
, mY(y)
{
    mSprite.setOrigin(WIDTH / 2, HEIGHT / 2);
    mSprite.setTexture(mTexture);
    mSprite.setPosition(mX, mY);

}

void Player::draw(sf::RenderWindow& window)
{
    mSprite.setPosition(mX,mY);
    window.draw(mSprite);
}

void Player::update(float time)
{

}


void Player::setPosition(int x, int y)
{

    mX = x;
    mY = y;
}

sf::Vector2i Player::getPosition()
{
    return sf::Vector2i(mX, mY);
}

int fillWay(int num, std::array<std::array<char, 30>, 30>& brain, int height, int width)
{
	bool found = false;
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
		{	
			if (brain[i][j] == num)
			{
				found = true;
                if (i > 0)
                {
                    if (brain[i - 1][j] == -2) return num;
                    else if (brain[i - 1][j] == -1) brain[i - 1][j] = num + 1;
                }
                if (j > 0)
                {
                    if (brain[i][j - 1] == -2) return num;
                    else if (brain[i][j - 1] == -1) brain[i][j - 1] = num + 1;
                }
                if (i < height - 1)
                {
                    if (brain[i + 1][j] == -2) return num;
                    else if (brain[i + 1][j] == -1) brain[i + 1][j] = num + 1;
                }
                if (j < width - 1)
                {
                    if (brain[i][j + 1] == -2) return num;
                    else if (brain[i][j + 1] == -1) brain[i][j + 1] = num + 1;
                }
                if (i < height - 1 && j < width - 1)
                {
                    if (brain[i + 1][j + 1] == -2) return num;
                    else if (brain[i + 1][j + 1] == -1) brain[i + 1][j + 1] = num + 1;
                }
                if (i < height - 1 && j > 0)
                {
                    if (brain[i + 1][j - 1] == -2) return num;
                    else if (brain[i + 1][j - 1] == -1) brain[i + 1][j - 1] = num + 1;
                }
                if (i > 0 && j < width - 1)
                {
                    if (brain[i - 1][j + 1] == -2) return num;
                    else if (brain[i - 1][j + 1] == -1) brain[i - 1][j + 1] = num + 1;
                }
                if (i > 0 && j > 0)
                {
                    if (brain[i - 1][j - 1] == -2) return num;
                    else if (brain[i - 1][j - 1] == -1) brain[i - 1][j - 1] = num + 1;
                }
			}
		}
	
	if (!found) return -1;
	return fillWay(num + 1, brain, height, width);
}

int generateWay(int i, int j, const std::array<std::array<char, 30>, 30>& brain, int sizeWay, std::vector<sf::Vector2i>& way, int step, int height, int width)
{

    if (step <= 0) return 1;
    bool flag = false;

	if (step == sizeWay)
	{
        flag = true;
        way[step - 1] = sf::Vector2i(i, j);
        generateWay(i, j, brain, sizeWay, way, step - 1, height, width);
	}

    if(!flag)if (i > 0 )
        if( brain[i - 1][j] == step)
        {
            flag = true;
            way[step - 1] = sf::Vector2i(i -1 , j);
            generateWay(i - 1, j, brain, sizeWay, way, step - 1, height, width);
        }

    if(!flag)if (j > 0 )
        if(brain[i][j - 1] == step)
        {
            flag = true;
            way[step - 1] = sf::Vector2i(i, j -1);
            generateWay(i, j-1, brain, sizeWay, way, step - 1, height, width);
        }

    if(!flag)
        if (i < height - 1 )
            if(brain[i + 1][j] == step)
            {
                flag = true;
                way[step - 1] = sf::Vector2i(i+1, j);
                generateWay(i+1, j, brain, sizeWay, way, step - 1, height, width);
            }

    if(!flag)
        if (j < width - 1)
            if(brain[i][j + 1] == step)
            {
                flag = true;
                way[step - 1] = sf::Vector2i(i, j+1);
                generateWay(i, j+1, brain, sizeWay, way, step - 1, height, width);
            }

    if(!flag)
        if (i < height - 1 && j < width - 1 )
            if( brain[i + 1][j + 1] == step)
            {
                flag = true;
                way[step - 1] = sf::Vector2i(i+1, j+1);
                generateWay(i+1, j+1, brain, sizeWay, way, step - 1, height, width);
            }

    if(!flag)
        if (i < height - 1 && j > 0 )
            if(brain[i + 1][j - 1] == step)
            {
                flag = true;
                way[step - 1] = sf::Vector2i(i+1, j-1);
                generateWay(i+1, j-1, brain, sizeWay, way, step - 1, height, width);
            }

    if(!flag)
        if (i > 0 && j < width - 1 )
            if(brain[i - 1][j + 1] == step)
            {
                flag = true;
                way[step - 1] = sf::Vector2i(i-1, j+1);
                generateWay(i-1, j+1, brain, sizeWay, way, step - 1, height, width);
            }

    if(!flag)
        if (i > 0 && j > 0 )
            if(brain[i - 1][j - 1] == step)
            {
                flag = true;
                way[step - 1] = sf::Vector2i(i-1, j-1);
                generateWay(i-1, j-1, brain, sizeWay, way, step - 1, height, width);
            }

    return 0;
}

std::vector<sf::Vector2i> Player::setWay(int x, int y, std::array<std::array<char, 30>, 30> blockGrille)
{
    int num = fillWay(0, blockGrille, 30, 30) + 1;
	std::vector<sf::Vector2i> way;
	if (!(num == -1))
	{
		way.resize(num);
		generateWay(y, x, blockGrille, num, way, num, 30, 30);

		for (int i = 0; i < 30; i++)
		{
			for (int j = 0; j < 30; j++)
			{
                char pic = blockGrille[i][j];

                if (blockGrille[i][j] == -1)
                    pic = ' ';
                else if (blockGrille[i][j] == -3)
                    pic = '#';
                else if (blockGrille[i][j] == -2)
                    pic = 'o';
                else if (blockGrille[i][j] == 0)
                    pic = 'x';
            }
		}
	}
    return way;
}
