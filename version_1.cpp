#include <SFML/Graphics.hpp>
#include<iostream>
#include<sstream>
#include<string>
#include<unistd.h>
#include<ctime>
#include<cstdlib>
using namespace std;
using namespace sf;

int points = 0;
int win = 0;

int handle_move(int player_move){
	
	srand(time(NULL));
	int x = rand();
    int num = points - 1;

    //rational move
    if(num % 4 == 0 && win == 0){
        int move = x % 3 + 1;
        return move;
    }
    //irrational moves and Al wins
    else{
        if(win == 0){
            win = 1;
            int remain = (points - 1) % 4;
            int best = 4 - remain;
            return best;
        }
        else{
            int best = 4 - player_move;
            return best;
        }
    }
}


int main()
{
	RenderWindow window(VideoMode(640,640), "InterFace");
	
	Texture title;
	title.loadFromFile("background.png");
	
	Sprite First_Cover(title);
	First_Cover.setScale(Vector2f(1.4f,1.4f));
	
	Texture Purple;
	Purple.loadFromFile("purple.png");
	
	/*Texture Blue;
	Blue.loadFromFile("blue.png");*/
	
	/*Texture Black;
	Black.loadFromFile("Black.png");*/
	
	/*Texture Orange;
	Orange.loadFromFile("orange.png");*/

	Sprite Purple_cash(Purple);
	Purple_cash.setScale(Vector2f(0.2f,0.1f));
	Purple_cash.setPosition(Vector2f(20.f, 30.f));
	
	
	
	
	
	/******封面*********/ 
	RectangleShape Game_1(Vector2f(200.f, 50.f)); //range(20-220, 80-130)
	Game_1.setFillColor(Color::Black);
	Game_1.setPosition(Vector2f(20.f, 80.f));
	
	RectangleShape Game_2(Vector2f(200.f, 50.f)); //間隔 range(420-620, 80-130)
	Game_2.setFillColor(Color::Black);
	Game_2.setPosition(Vector2f(420.f, 80.f)); // 640-200-20(空格) 
	
	RectangleShape Game_3(Vector2f(200.f, 50.f)); //間隔 range(20-220, 510-560)
	Game_3.setFillColor(Color::Black);
	Game_3.setPosition(Vector2f(20.f, 510.f));//640-50-80(空格) 
	
	RectangleShape Game_4(Vector2f(200.f, 50.f)); //間隔 range(420-620, 510-560)
	Game_4.setFillColor(Color::Black);
	Game_4.setPosition(Vector2f(420.f, 510.f));
	
	Font font;
	font.loadFromFile("Arial.ttf");
	
	Text Game_1_txt;
	Game_1_txt.setFont(font);
	Game_1_txt.setFillColor(Color::White);
	Game_1_txt.setCharacterSize(30);
	Game_1_txt.setPosition(Vector2f(70.f, 85.f));
	Game_1_txt.setString("1-30");
	
	Text Game_2_txt;
	Game_2_txt.setFont(font);
	Game_2_txt.setFillColor(Color::White);
	Game_2_txt.setCharacterSize(30);
	Game_2_txt.setPosition(Vector2f(270.f, 325.f));
	Game_2_txt.setString("Menu");
	/*******************************/
	/*************遊戲1*************/ 
	RectangleShape Plus_1(Vector2f(100.f, 100.f));// +1
	Plus_1.setFillColor({ 55, 55, 55, 255 }); //Color => { 55, 55, 55, 255 } = Gray
	Plus_1.setPosition(Vector2f(120.f, 500.f));
	
	RectangleShape Plus_2(Vector2f(100.f, 100.f));// +2
	Plus_2.setFillColor({ 55, 55, 55, 255 });
	Plus_2.setPosition(Vector2f(270.f, 500.f));
	
	RectangleShape Plus_3(Vector2f(100.f, 100.f));// +3
	Plus_3.setFillColor({ 55, 55, 55, 255 });
	Plus_3.setPosition(Vector2f(420.f, 500.f));
	
	Text Plus_1_txt;
	Plus_1_txt.setFont(font);
	Plus_1_txt.setFillColor(Color::White);
	Plus_1_txt.setCharacterSize(50);
	Plus_1_txt.setPosition(Vector2f(140.f, 520.f)); // 120+10
	Plus_1_txt.setString("+1");
	
	Text Plus_2_txt;
	Plus_2_txt.setFont(font);
	Plus_2_txt.setFillColor(Color::White);
	Plus_2_txt.setCharacterSize(50);
	Plus_2_txt.setPosition(Vector2f(290.f, 520.f));
	Plus_2_txt.setString("+2");
	
	Text Plus_3_txt;
	Plus_3_txt.setFont(font);
	Plus_3_txt.setFillColor(Color::White);
	Plus_3_txt.setCharacterSize(50);
	Plus_3_txt.setPosition(Vector2f(440.f, 520.f)); 
	Plus_3_txt.setString("+3");
		
	int step = 0;
	ostringstream cur;
	cur << "Current: " << step;
	
	Text current; // 目前到哪 
	current.setFont(font);
	current.setFillColor(Color::Red);
	current.setCharacterSize(30);
	current.setPosition(Vector2f(250.f, 20.f)); 
	current.setString(cur.str());

	RectangleShape square[31];
	int length = 75;
	for(int i = 1; i <= 6; i++)
	{

		for(int j = 1; j <= 5; j++)
		{
			square[i+((j-1)*6)].setSize(Vector2f(length, length));
			square[i+((j-1)*6)].setFillColor(Color::Black);
			square[i+((j-1)*6)].setPosition(Vector2f(100.f + length*(i-1) , 80.f + length*(j-1)));
		}
	}
	
	int amount = 1;
	ostringstream digit;

	Text number[31];
	for(int i = 1; i <= 6; i++)
	{
		for(int j = 1; j <= 5; j++)
		{
			amount = i+((j-1)*6);
			digit << amount;
			number[i+((j-1)*6)].setFont(font);
			number[i+((j-1)*6)].setFillColor(Color::White);
			number[i+((j-1)*6)].setCharacterSize(50);
			number[i+((j-1)*6)].setPosition(Vector2f(100.f + length*(i-1), 80.f + length*(j-1)));
			number[i+((j-1)*6)].setString(digit.str());
			digit.str("");
		}
		
	}
	/*******************************/
	bool Press = false;
	float Mx = 0; //Mouse的x的position
	float My = 0; //Mouse的y的position
	
	main_game:
	Press = false;
	while(window.isOpen())
	{
		Event event;
		while(window.pollEvent(event))
		{
			Mx = Mouse::getPosition(window).x;
			My = Mouse::getPosition(window).y;
			//cout << "Mx= " << Mx << " ,My= " << My << "\n";
			if(event.type == Event::Closed)
                window.close();
            else if(event.type == Event::MouseButtonPressed)//range(20-220, 80-130)
            {
            	if(event.mouseButton.x >= 20 && event.mouseButton.x <= 220)//x軸
				{
					if(event.mouseButton.y >= 80 && event.mouseButton.y <= 130)//y軸 
					{
						Press = true;

					}
				}	
			}
			
			if(Mx >= 20 && Mx <= 220 && My >= 80 && My <= 130)//Game_1
			{
				Game_1.setFillColor({128, 64, 192});	
			}
			else
				Game_1.setFillColor(Color::Black);
				
			if(Mx >= 420 && Mx <= 620 && My >= 80 && My <= 130)//Game_2 range(420-620, 80-130)
			{
				Game_2.setFillColor(Color::Cyan);
			}
			else
				Game_2.setFillColor(Color::Black);
			
			if(Mx >= 20 && Mx <= 220 && My >= 510 && My <= 560)//Game_3 range(20-220, 510-560)
			{
				Game_3.setFillColor({64, 64, 64});
			}
			else
				Game_3.setFillColor(Color::Black);
				
			if(Mx >= 420 && Mx <= 620 && My >= 510 && My <= 560)//Game4 range(420-620, 510-560)
			{
				Game_4.setFillColor({255, 160, 64});
			}
			else
				Game_4.setFillColor(Color::Black);
		}
		
		window.clear();
		window.draw(First_Cover);
		window.draw(Game_1);
		window.draw(Game_2);
		window.draw(Game_3);
		window.draw(Game_4);
		window.draw(Game_1_txt);
		window.draw(Purple_cash);
		window.display();
		if(Press == true)
			break;
	}
	
	int former = 0;
	win = 0;
	int robot = 0;
	int win_person = -1; // 0 = robot, 1 = us, -1 = not yet
	points = 0;
	step = 0;
	cur.str("");
	cur << "Current: " << step;
	current.setString(cur.str());
	
	for(int i = 1; i <= 30; i++)
	{
		square[i].setFillColor(Color::Black);
	}
	while(window.isOpen())
	{	
		if(robot != 0){
			sleep(1);
			points += robot;
			int reply = handle_move(robot);
			former = step;
			step += reply;
			points += reply;
			for(int i = former+1; i <= step; i++)
			{
				square[i].setFillColor(Color::Green);
			}
						
			cur.str("");
			cur << "Current: " << step;
			current.setString(cur.str());
			robot = 0;
			
			if(step == 29)
				win_person = 0;
		}
		Event event;
		while(window.pollEvent(event))	
		{
			if(event.type == Event::Closed)
                window.close();
			
			if(event.type == Event::MouseButtonPressed)
			{
				if(event.mouseButton.x >= 140 && event.mouseButton.x <= 240)//x軸	
				{
					if(event.mouseButton.y >= 520 && event.mouseButton.y <= 620)
					{
						former = step;
						
						step++;
						cur.str("");
						cur << "Current: " << step;
						current.setString(cur.str());
						
						
						for(int i = former+1; i <= step; i++)
						{
							square[i].setFillColor(Color::Blue);
						}
						robot = 1;
						
						if(step == 29)
							win_person = 1;
					}
				}
				else if(event.mouseButton.x >= 290 && event.mouseButton.x <= 390)
				{
					if(event.mouseButton.y >= 520 && event.mouseButton.y <= 620)
					{
						former = step;
						
						step += 2;
						cur.str("");
						cur << "Current: " << step;
						current.setString(cur.str());
						
						for(int i = former+1; i <= step; i++)
						{
							square[i].setFillColor(Color::Blue);
						}
						robot = 2;
						
						if(step == 29)
							win_person = 1;
					}
				}
				else if(event.mouseButton.x >= 440 && event.mouseButton.x <= 540)
				{
					if(event.mouseButton.y >= 520 && event.mouseButton.y <= 620)
					{
						former = step;
						
						step += 3;
						cur.str("");
						cur << "Current: " << step;
						current.setString(cur.str());
						
						for(int i = former+1; i <= step; i++)
						{
							square[i].setFillColor(Color::Blue);
						}
						robot = 3;
						
						if(step == 29)
							win_person = 1;
					}
				}
			}
		}
		
		window.clear(Color::White);
		//window.draw(object);
		window.draw(Plus_1);
		window.draw(Plus_2);
		window.draw(Plus_3);
		window.draw(Plus_1_txt);
		window.draw(Plus_2_txt);
		window.draw(Plus_3_txt);
		window.draw(current);
		for(int i = 1; i <= 30; i++)
		{
			window.draw(square[i]);
			window.draw(number[i]);
		}
		window.display();
		
		if(win_person != -1)
		{
			sleep(1);
			//cout<< "END" << '\n';
			goto main_game;
		}
	}
	
}
