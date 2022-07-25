#include <iostream>
#include "Grid.h"
#include "player.h"
#include "Menu.h"
#include <SFML\Graphics.hpp>
#include <SFML/Audio.hpp>
using namespace std;
int main()
{
	//GUI initializtion
	sf::RenderWindow window(sf::VideoMode(800,600), "tic tac toe");
	window.setFramerateLimit(60);

	sf::Texture tex_back, tex_grid, tex_x, tex_o;
	if (tex_back.loadFromFile("Data/background.jpg")==0)
		return -1;
	if (tex_grid.loadFromFile("Data/grid.png") == 0)
		return -1;
	if (tex_x.loadFromFile("Data/X.png") == 0)
		return -1;
	if (tex_o.loadFromFile("Data/O.png") == 0)
		return -1;

	sf::RectangleShape background,grid_shape;
	background.setSize(screen);
	background.setTexture(&tex_back);
	grid_shape.setSize(screen - sf::Vector2f(100, 100));
	grid_shape.setPosition(sf::Vector2f(50, 50));
	grid_shape.setTexture(&tex_grid);

	//menu gui
	sf::Texture sp, mp, e_b, m_b, h_b, Start_b;
	sp.loadFromFile("Data/SPf.png");
	mp.loadFromFile("Data/multip1.png");
	e_b.loadFromFile("Data/easy1.png");
	m_b.loadFromFile("Data/med1.png");
	h_b.loadFromFile("Data/hard1.png");
	Start_b.loadFromFile("Data/start.png");

	Button sp_button, mp_button;
	sp_button.setSize(sf::Vector2f(200, 75));
	mp_button.setSize(sf::Vector2f(200, 75));
	sp_button.setPosition(100, 75);
	sp_button.setTexture(&sp);
	mp_button.setPosition(500, 75);
	mp_button.setTexture(&mp);

	Button easy_b, medium_b, hard_b, playerx, playero, startb;
	easy_b.setSize(sf::Vector2f(200, 75));
	medium_b.setSize(sf::Vector2f(200, 75));
	hard_b.setSize(sf::Vector2f(200, 75));
	playerx.setSize(sf::Vector2f(100, 75));
	playero.setSize(sf::Vector2f(100, 75));
	easy_b.setPosition(300, 200);
	medium_b.setPosition(300, 275);
	hard_b.setPosition(300, 350);
	playerx.setPosition(100, 470);
	playero.setPosition(260, 470);
	easy_b.setTexture(&e_b);
	medium_b.setTexture(&m_b);
	hard_b.setTexture(&h_b);
	playerx.setTexture(&tex_x);
	playero.setTexture(&tex_o);
	startb.setSize(sf::Vector2f(200, 75));
	startb.setPosition(450, 460);
	startb.setTexture(&Start_b);


	Menu menu;
	//main menu loop
	while (menu.isopen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			if (sp_button.isclicked(window))
			{
				menu.setplayerNumber(1);
				sp_button.setOutlineThickness(2);
				sp_button.setOutlineColor(sf::Color::Red);
			}
			if (mp_button.isclicked(window))
			{
				menu.setplayerNumber(0);
				mp_button.setOutlineThickness(2);
				mp_button.setOutlineColor(sf::Color::Red);
			}
			if (easy_b.isclicked(window))
			{
				menu.set_difficulty(easy);
				easy_b.setOutlineThickness(2);
				easy_b.setOutlineColor(sf::Color::Red);
			}
			if (medium_b.isclicked(window))
			{
				menu.set_difficulty(medium);
				medium_b.setOutlineThickness(2);
				medium_b.setOutlineColor(sf::Color::Red);
			}
			if (hard_b.isclicked(window))
			{
				menu.set_difficulty(hard);
				hard_b.setOutlineThickness(2);
				hard_b.setOutlineColor(sf::Color::Red);
			}
			if (playero.isclicked(window)) 
			{
				menu.selectMark(0);
				playero.setOutlineThickness(2);
				playero.setOutlineColor(sf::Color::Red);
			}
			if (playerx.isclicked(window))
			{
				menu.selectMark(1);
				playerx.setOutlineThickness(2);
				playerx.setOutlineColor(sf::Color::Red);
			}
			if (startb.isclicked(window))
			{
				menu.closeMenu();
			}
		}

		//rendering
		window.clear();
		window.draw(background);
		window.draw(sp_button);
		window.draw(mp_button);
		window.draw(easy_b);
		window.draw(medium_b);
		window.draw(hard_b);
		window.draw(playerx);
		window.draw(playero);
		window.draw(startb);
		window.display();
	}

	//variables
	Button* clicked_button = nullptr;
	//variables from main menu
	bool singleplayer = menu.getnumberofplayer();
	bool player1_mark = menu.getselectedMark();
	diff Difficulty = menu.getDifficulty();

	//initialize players
	player p1(player1_mark), p2(!player1_mark);
	sf::Texture player1_texture = (p1.getMark() == 1 ? tex_x : tex_o);
	sf::Texture player2_texture = (p1.getMark() == 1 ? tex_o : tex_x);

	//main game loop
	while (window.isOpen()) {
		Grid grid(grid_shape);
		bool game = 1;
		while (game)  // loop indicating a single game 
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					window.close();
				}
				for (int i = 0; i < 3; i++)
				{
					for (int j = 0; j < 3; j++)
					{
						if (grid.getelement(i, j).isclicked(window) && grid.getelement(i, j).getflag() == blank)
						{
							clicked_button = grid.getpelement(i, j);
						}
					}
				}
			}//end event poll loop

			//LOGIC
			if (grid.turn % 2 == 0 && singleplayer && grid.turn < 10)  //computer's turn if single player
			{
				Button* p = grid.bestmove(Difficulty, p1.getMark());
				p->setTexture(&player2_texture);
				p->setflag((p2.getMark() == 1 ? flagx : flago));
				grid.turn++;
			}
			if (clicked_button != nullptr)
			{
				if (grid.turn % 2 != 0) //first player's turn
				{
					clicked_button->setTexture(&player1_texture);
					clicked_button->setflag( (p1.getMark()==1? flagx:flago) );
					grid.turn++;
					clicked_button = nullptr;
				}
				else if (grid.turn % 2 == 0 && !singleplayer) //second player's turn if not single player
				{
					clicked_button->setTexture(&player2_texture);
					clicked_button->setflag((p2.getMark() == 1 ? flagx : flago));
					grid.turn++;
					clicked_button = nullptr;
				}
			}

			// checking for win, loss or tie
			switch (grid.check())
			{
			case X_WINS:
				cout << "x wins"<<endl;
				(p1.getMark() == 1 ? p1.IncrementScore() : p2.IncrementScore()); //if player1 is x increment his score
				game = 0;
				break;
			case O_WINS:
				cout << "o wins"<<endl;
				(p1.getMark() == 0 ? p1.IncrementScore() : p2.IncrementScore()); //if player1 is o increment his score
				game = 0;
				break;
			}
			if (grid.turn == 10) //9 turns have passed and nobody won
			{
				cout << "tie" << endl;
				game = 0;
				//game is a draw 
			}

			//DRAWING ON SCREEN
			window.clear();
			window.draw(background);
			window.draw(grid_shape);
			grid.draw(window);
			window.display();
		} //end game
		cout << p1.getscore() << endl;
		cout << p2.getscore() << endl;
	} //end main game loop

	return 0;
}
