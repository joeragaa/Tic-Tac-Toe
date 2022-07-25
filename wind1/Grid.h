#ifndef HEADER_H
#define HEADER_H

#include <time.h> //to seed rand()
#include <SFML\Graphics.hpp>
#include <SFML/Audio.hpp>
using namespace std;

sf::Vector2f screen(800, 600);  //size of game window

enum gameStates { TIE, X_WINS, O_WINS };
enum FLAGS { flago, flagx, blank };
enum diff {easy,medium,hard};


class Button: public sf::RectangleShape {
private:
	//flag variable indicating what state the button is in
	FLAGS flag;
public:
	//flag is initialized to blank
	Button()
	{
		flag = blank;
	}
	bool isclicked(sf::RenderWindow &w)
	{
		//function get position returns vector2i type so vector2f constructor had to be used on mouse coordinates
		sf::Vector2f P(sf::Vector2f(sf::Mouse::getPosition(w).x, sf::Mouse::getPosition(w).y));
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (sf::RectangleShape::getGlobalBounds().contains(P))
			{
				return 1;
			}
		}
		return 0;
	}
	void setflag(FLAGS state)
	{
		flag = state;
	}
	FLAGS getflag()
	{
		return flag;
	}
};

class Grid {
protected:
	Button block[3][3];
public:
	int turn = 1; //player 1 is odd number of turns and player 2 is even

	//construct the grid logic based on the gui 
	Grid(sf::RectangleShape layout)
	{
		sf::Vector2f O = layout.getPosition();
		float elementX = layout.getGlobalBounds().width/3;
		float elementY = layout.getGlobalBounds().height/3;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				sf::Vector2f localO = O + sf::Vector2f(elementX * i, elementY * j);
				block[i][j].setPosition(localO);
				block[i][j].setSize(sf::Vector2f(elementX, elementY));
			}
		}
	}
	
	Button getelement(int i, int j)
	{
		return block[i][j];
	}
	Button* getpelement(int i, int j)
	{
		return &block[i][j];
	}
	//check for win, loss or a tie
	gameStates check()
	{
		//check columns
		for (int i = 0; i <= 2; i++)
		{
			if (block[i][0].getflag() == block[i][1].getflag() && block[i][1].getflag() == block[i][2].getflag()
				&& block[i][0].getflag() == flagx)
			{
				return X_WINS;
			}
			else if (block[i][0].getflag() == block[i][1].getflag() && block[i][1].getflag() == block[i][2].getflag()
				&& block[i][0].getflag() == flago)
			{
				return O_WINS;
			}
		}
		//check rows
		for (int j = 0; j <= 2; j++)
		{
			if (block[0][j].getflag() == block[1][j].getflag() && block[1][j].getflag() == block[2][j].getflag()
				&& block[0][j].getflag() == flagx)
			{
				return X_WINS;
			}
			else if (block[0][j].getflag() == block[1][j].getflag() && block[1][j].getflag() == block[2][j].getflag()
				&& block[0][j].getflag() == flago)
			{
				return O_WINS;
			}
		}
		//check diagonals
		if (block[0][0].getflag() == block[1][1].getflag() && block[2][2].getflag() == block[1][1].getflag()
			&& block[0][0].getflag() == flagx)
			return X_WINS;
		else if (block[0][0].getflag() == block[1][1].getflag() && block[2][2].getflag() == block[1][1].getflag()
			&& block[0][0].getflag() == flago)
			return O_WINS;
		else if (block[0][2].getflag() == block[1][1].getflag() && block[2][0].getflag() == block[1][1].getflag()
			&&block[0][2].getflag()==flagx)
			return X_WINS;
		else if (block[0][2].getflag() == block[1][1].getflag() && block[2][0].getflag() == block[1][1].getflag()
			&& block[0][2].getflag() == flago)
			return O_WINS;
		else
			return TIE;
	}
	void draw(sf::RenderWindow& w)
	{
		for (int ii = 0; ii < 3; ii++)
		{
			for (int jj = 0; jj < 3; jj++)
			{
				if (block[ii][jj].getflag() != blank)
					w.draw(block[ii][jj]);
			}
		}
	}
	//AI (not so I)
	Button* bestmove(diff D,bool opponent_mark)
	{
		if (D > medium) //HARD
		{
			for (int i = 0; i <= 2; i++)
			{
				for (int k = 0; k < 2; k++)
				{   
					//play in third row
					if (block[i][k].getflag() == block[i][k + 1].getflag())
					{
						if (k == 0)
						{
							return &block[i][k + 2];
						}
						else
						{
							return &block[i][k - 1];
						}
					}
					// play in third column
					if (block[k][i].getflag() == block[k + 1][i].getflag())
					{
						if (k == 0)
						{
							return &block[k + 2][i];
						}
						else
						{
							return &block[k - 1][i];
						}
					}
					//play between rows
					if (block[i][0].getflag() == block[i][2].getflag())
					{
						return &block[i][1];
					}
					//play between columns
					if (block[0][i].getflag() == block[2][i].getflag())
					{
						return &block[1][i];
					}
				}
			}
			// play in the third block of diagonal
			for (int j = 0; j < 2; j++)
			{
				if (block[j][j].getflag() == block[j + 1][j + 1].getflag())
				{
					if (j == 0) { return &block[j + 2][j + 2]; }
					else { return &block[j - 1][j - 1]; }
				}

				if (block[2 - j][j].getflag() == block[(2 - j) - 1][j + 1].getflag())
				{
					if (j == 0) { return &block[0][2]; }
					else { return &block[2][0]; }
				}
			}
			if (block[0][1].getflag() == block[0][2].getflag())
			{
				return &block[1][1];
			}
			if (block[0][0].getflag() == block[2][2].getflag())
			{
				return &block[1][1];
			}
		} 
		if (D > easy) //medium
		{
			// protect from defeat
			for (int i = 0; i <= 2; i++)
			{
				for (int k = 0; k < 2; k++)
				{  
					//play in third row
					if (block[i][k].getflag() == block[i][k + 1].getflag() && block[i][k].getflag() == opponent_mark)
					{
						if (k == 0)
							return &block[i][k + 2];
						else
							return &block[i][k - 1];
					}
					// play in third column
					if (block[k][i].getflag() == block[k + 1][i].getflag() && block[i][k].getflag() == opponent_mark)
					{
						if (k == 0)
							return &block[k + 2][i];
						else
							return &block[k - 1][i];
					}
					//play between rows
					if (block[i][0].getflag() == block[i][2].getflag() && block[i][0].getflag() == opponent_mark)
					{
						return &block[i][1];
					}
					//play between columns
					if (block[0][i].getflag() == block[2][i].getflag() && block[i][0].getflag() == opponent_mark)
					{
						return &block[1][i];
					}
				}

			}
			// play in the third block of diagonal
			for (int j = 0; j < 2; j++)
			{
				if (block[j][j].getflag() == block[j + 1][j + 1].getflag() && block[j][j].getflag() == opponent_mark)
				{
					if (j == 0) { return &block[j + 2][j + 2]; }
					else { return &block[j - 1][j - 1]; }
				}

				if (block[2-j][j].getflag() == block[(2-j)-1][j+1].getflag() && block[2-j][j].getflag() == opponent_mark)
				{
					if (j == 0) { return &block[0][2]; }
					else { return &block[2][0]; }
				}
			}
			if (block[0][2].getflag() == block[2][0].getflag() && block[0][2].getflag() == opponent_mark)
			{
				return &block[1][1];
			}
			if (block[0][0].getflag() == block[2][2].getflag() && block[0][0].getflag() == opponent_mark)
			{
				return &block[1][1];
			}
		}
		if (D >= easy) //easy
		{
			while (1) //loop until function returns a valid move
			{
				//two variables to get 2 different numbers
				srand(time(0));
				int x = rand() % 3;
				int y = rand() % 3;
				Button* bb = &block[x][y];
				if (block[x][y].getflag() == blank)
				{
					return bb;
				}
			}
		}
	}
};



#endif
