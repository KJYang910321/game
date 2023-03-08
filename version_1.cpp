#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include<iostream>
#include<sstream>
#include<string>
#include<unistd.h>
#include<ctime>
#include<cstdlib>
#include"extra.h"
#include"extra_end.h"
#include"outcome.h" 
#include"auction.h"
#include"Game4_image.h"
#include<vector>

using namespace std;
using namespace sf;

int points = 0;
int win = 0;

bool lock_rank_2 = true;// 鎖住 
bool avoid = 0;


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

int rounds = 0;
int last = 0;

int normal_AI(int round){
    if(round == 0){
        return 25;
    }
    else{
        int choice = (25 + last)/2;
        return choice;
    }
}

int smart_AI(int round){
    if(round == 0){
        return 25;
    }
    else{
        int miss = rand() % 4;
        int choice = (12 + last + miss)/2;
        return choice;
    }
}

int super_AI(int round){
	if(round == 0){
		return 10;
	}
	else if(round % 2 == 0){
		int choice = (9 + last)/2;
		choice += rand() % 4;
		return choice / 2;
	}
	else{
		int choice = (37 + (2 * last))/ 3;
		choice += rand() % 4;
		return choice / 2; 
	}
}

int random_AI(int round){
	int choice;
    if (round % 2 == 0){
        choice = last /2;
        return choice;
    }
    else{
        int choice = 50 + (rand() % round);
        return choice;
    }
}


int main()
{

	RenderWindow window(VideoMode(640,640), "InterFace");
	
	Texture title;
	title.loadFromFile("image/cp.png");
	
	Texture first_title;
	first_title.loadFromFile("image/cp_game1.png");
	
	Texture second_title;
	second_title.loadFromFile("image/cp_game2.png");
	
	Texture third_title;
	third_title.loadFromFile("image/cp_game3.png");
	
	Texture fourth_title;
	fourth_title.loadFromFile("image/cp_game4.png");
	
	Music background;
	float volume = 50;
	background.openFromFile("music/battleground.ogg"); 
	background.setVolume(volume);
	background.setLoop(true);  //使music的音樂可以重複播放，反之可設為false
    background.play();
	
	Music button;
	button.openFromFile("music/mouse_click.ogg");
	button.setVolume(75);
	
	
	Sprite Cover(title);
	Cover.setScale(Vector2f(0.593f,0.593f));
	
	Sprite First_Cover(first_title);
	First_Cover.setScale(Vector2f(0.593f,0.593f));
	
	Sprite Second_Cover(second_title);
	Second_Cover.setScale(Vector2f(0.593f,0.593f));
	
	Sprite Third_Cover(third_title);
	Third_Cover.setScale(Vector2f(0.593f,0.593f));
	
	Sprite Fourth_Cover(fourth_title);
	Fourth_Cover.setScale(Vector2f(0.593f,0.593f));
	
	/******封面*********/ 
	RectangleShape Game_1(Vector2f(85.f, 85.f)); //range(50-135, 380-465)
	Game_1.setFillColor(Color::Transparent);
	Game_1.setPosition(Vector2f(50.f, 380.f));
	
	
	RectangleShape Game_2(Vector2f(105.f, 85.f)); //range(190-295, 530-615)
	Game_2.setFillColor(Color::Transparent);
	Game_2.setPosition(Vector2f(190.f, 530.f));
	
	RectangleShape Game_3(Vector2f(105.f, 85.f)); //range(490-595, 440-525)
	Game_3.setFillColor(Color::Transparent);
	Game_3.setPosition(Vector2f(490.f, 440.f));
	
	RectangleShape Game_4(Vector2f(85.f, 85.f)); //range(360-445, 280-365)
	Game_4.setFillColor(Color::Transparent);
	Game_4.setPosition(Vector2f(360.f, 280.f)); 
	
	Font font;
	font.loadFromFile("font/Phosphorus_Triselenide/Phosph10.ttf");

	/*******************************/
	
	/*************遊戲1*************/ 
	Texture rule_1;
	rule_1.loadFromFile("image/Rule_g1.png");
	
	Sprite rule_game_1(rule_1);
	rule_game_1.setScale(Vector2f(0.625f, 0.625f));
	
	Texture back_1;
	back_1.loadFromFile("image/cp_game1_底圖.png");
	
	Sprite back_1_cover(back_1);
	back_1_cover.setScale(Vector2f(0.593f,0.593f)); 
	
	Texture hint_1_1_text;
	hint_1_1_text.loadFromFile("image/Hint_g1.png");
	
	Sprite hint_1_1(hint_1_1_text);
	hint_1_1.setScale(Vector2f(0.623f,0.623f));
	
	RectangleShape Plus_1(Vector2f(120.f, 70.f));// range(130~250, 475~545)
	Plus_1.setFillColor(Color::Transparent); //Color => { 55, 55, 55, 255 } = Gray
	Plus_1.setPosition(Vector2f(130.f, 475.f));
	
	RectangleShape Plus_2(Vector2f(120.f, 70.f));// range(260~380, 475~545)
	Plus_2.setFillColor(Color::Transparent);
	Plus_2.setPosition(Vector2f(260.f, 475.f));
	
	RectangleShape Plus_3(Vector2f(120.f, 70.f));// range(390~510, 475~545)
	Plus_3.setFillColor(Color::Transparent);
	Plus_3.setPosition(Vector2f(390.f, 475.f));
	
	int step = 0;
	ostringstream cur;
	cur << "Current: " << step;
	
	Text current; //目前到哪 
	current.setFont(font);
	current.setFillColor(Color::Red);
	current.setCharacterSize(30);
	current.setPosition(Vector2f(250.f, 20.f)); 
	current.setString(cur.str());

	CircleShape circle[31];
	int length = 30;
	for(int i = 1; i <= 6; i++)
	{

		for(int j = 1; j <= 5; j++)
		{
			circle[i+((j-1)*6)].setRadius(length);
			circle[i+((j-1)*6)].setFillColor(Color::Black);
			circle[i+((j-1)*6)].setPosition(Vector2f(135.f + 2*length*(i-1) , 165.f + 2*length*(j-1)));
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
			if(amount < 10)//為了對齊 
			{
				digit << amount;
				number[i+((j-1)*6)].setFont(font);
				number[i+((j-1)*6)].setFillColor(Color::White);
				number[i+((j-1)*6)].setCharacterSize(24);
				number[i+((j-1)*6)].setPosition(Vector2f(156.f + 2*length*(i-1), 178.f + 2*length*(j-1)));
				number[i+((j-1)*6)].setString(digit.str());
				digit.str("");
			}
			else if(10 <= amount && amount < 20)
			{
				digit << amount;
				number[i+((j-1)*6)].setFont(font);
				number[i+((j-1)*6)].setFillColor(Color::White);
				number[i+((j-1)*6)].setCharacterSize(24);
				number[i+((j-1)*6)].setPosition(Vector2f(150.f + 2*length*(i-1), 178.f + 2*length*(j-1)));
				number[i+((j-1)*6)].setString(digit.str());
				digit.str("");
			}
			else
			{
				digit << amount;
				number[i+((j-1)*6)].setFont(font);
				number[i+((j-1)*6)].setFillColor(Color::White);
				number[i+((j-1)*6)].setCharacterSize(24);
				number[i+((j-1)*6)].setPosition(Vector2f(147.f + 2*length*(i-1), 178.f + 2*length*(j-1)));
				number[i+((j-1)*6)].setString(digit.str());
				digit.str("");	
			}
		}
		
	}
		
	/*************遊戲1過渡*********/ 

	
	Texture game1_middle;
	game1_middle.loadFromFile("image/cp_choose-level.png");
	
	Sprite game1_choose_1(game1_middle);
	game1_choose_1.setScale(Vector2f(0.57f,0.57f));
	game1_choose_1.setPosition(Vector2f(41.f, 361.f));
	
	Texture game1_middle_2;
	game1_middle_2.loadFromFile("image/cp_choose-level_2.png");
	
	Sprite game1_choose_2(game1_middle_2);
	game1_choose_2.setScale(Vector2f(0.57f,0.57f));
	game1_choose_2.setPosition(Vector2f(41.f, 361.f));
	
	RectangleShape game1[2];
	
	game1[0].setSize(Vector2f(40.f, 40.f));
	game1[0].setPosition(Vector2f(60.f, 395.f));
	game1[0].setFillColor(Color::Transparent);

	game1[1].setSize(Vector2f(35.f, 35.f));
	game1[1].setPosition(Vector2f(110.f, 430.f));
	game1[1].setFillColor(Color::Transparent);
	
	
	/*******************************/
	
	/**********遊戲1-2**************/
	Texture back_1_2;
	back_1_2.loadFromFile("image/cp_game1_2.png");
	
	Sprite back_1_2_cover(back_1_2);
	back_1_2_cover.setScale(Vector2f(0.593f, 0.593f)); 
	
	
	/************遊戲2**************/
	
	Texture back_2;
	back_2.loadFromFile("image/cp_game2_底圖.png");
	
	Sprite back_2_cover(back_2);
	back_2_cover.setScale(Vector2f(0.593f,0.593f));
	
	Texture rule_2;
	rule_2.loadFromFile("image/Rule_g2.png");
	
	Sprite rule_game_2(rule_2);
	rule_game_2.setScale(Vector2f(0.625f, 0.625f));	
	
	Texture hint_2_text;
	hint_2_text.loadFromFile("image/Hint_g2.png");
	
	Sprite hint_2(hint_2_text);
	hint_2.setScale(Vector2f(0.623f,0.623f));
	
	/************Cancel鍵**************/ 

	Texture cancel_button_text;
	cancel_button_text.loadFromFile("image/cancel.png");
	
	Sprite cancel_button(cancel_button_text);
	cancel_button.setScale(Vector2f(0.1f, 0.1f));
	cancel_button.setPosition(Vector2f(544, 55));
	
	Texture hint_text;
	hint_text.loadFromFile("image/idea.png");
	
	Sprite hint(hint_text);
	hint.setScale(Vector2f(0.1f, 0.1f));
	hint.setPosition(Vector2f(45, 55));
	
	RectangleShape cancel_hint;
	cancel_hint.setSize(Vector2f(40, 40));
	cancel_hint.setPosition(Vector2f(495, 135));
	cancel_hint.setTexture(&cancel_button_text);
	
	RectangleShape cancel_hint_4;
	cancel_hint_4.setSize(Vector2f(40, 40));
	cancel_hint_4.setPosition(Vector2f(544, 87));
	cancel_hint_4.setTexture(&cancel_button_text);
	
	
	/**********遊戲3****************/
	Texture back_3;
	back_3.loadFromFile("image/cp_game3_底圖.png");
	
	Sprite back_3_cover(back_3);
	back_3_cover.setScale(Vector2f(0.593f,0.593f));
	
	Texture choose_texture;
	choose_texture.loadFromFile("image/cp_game3_choose.png");
	
	Sprite choose(choose_texture);
	choose.setScale(Vector2f(0.593f,0.593f));
	
	Texture choose_t_texture;
	choose_t_texture.loadFromFile("image/cp_game3_choose2.png");
	
	Sprite choose_t(choose_t_texture);
	choose_t.setScale(Vector2f(0.593f,0.593f));
	
	Texture choose_s_texture;
	choose_s_texture.loadFromFile("image/cp_game3_choose3.png");
	
	Sprite choose_s(choose_s_texture);
	choose_s.setScale(Vector2f(0.593f,0.593f));
	
	Texture rule_3;
	rule_3.loadFromFile("image/Rule_g3.png");
	
	Sprite rule_game_3(rule_3);
	rule_game_3.setScale(Vector2f(0.625f, 0.625f));
	
	Texture hint_3_text;
	hint_3_text.loadFromFile("image/Hint_g3.png");
	
	Sprite hint_3(hint_3_text);
	hint_3.setScale(Vector2f(0.623f,0.623f));
		
	/*******************************/ 
	/*********遊戲4***************/
	
	Texture rule_4;
	rule_4.loadFromFile("image/Rule_g4.png");
	
	Sprite rule_game_4(rule_4);
	rule_game_4.setScale(Vector2f(0.625f, 0.625f));	
	
	Texture hint_4_text;
	hint_4_text.loadFromFile("image/Hint_g4.png");
	
	Sprite hint_4(hint_4_text);
	hint_4.setScale(Vector2f(0.623f,0.623f));
	
	/*****************************/
	int Press = 0;
	int rank = 0;
	float Mx = 0; //Mouse的x的position
	float My = 0; //Mouse的y的position
	int condition = 0;
	
	main_game:
	Press = false;
	rank = false;
	while(window.isOpen())
	{
		Event event;
		while(window.pollEvent(event))
		{
			Mx = Mouse::getPosition(window).x;
			My = Mouse::getPosition(window).y;
			//
			if(event.type == Event::Closed)
                window.close();
            else if(event.type == Event::MouseButtonPressed)//range(50-135, 380-465)
            {
            	cout << "Mx= " << Mx << " ,My= " << My << "\n";
            	if(Press == 1)
				{
					
					if(event.mouseButton.x >= 60 && event.mouseButton.x <= 100)
					{
						if(event.mouseButton.y >= 395 && event.mouseButton.y <= 435)
							rank = 1;
					}	
					else if(lock_rank_2 == false)//如果打開了 
					{	
						if(event.mouseButton.x >= 110 && event.mouseButton.x <= 145)
						{
							if(event.mouseButton.y >= 430 && event.mouseButton.y <= 465)
								rank = 2;
						}
					}
					
				}
				
            	if(event.mouseButton.x >= 50 && event.mouseButton.x <= 135)//Game_1
				{
					if(event.mouseButton.y >= 380 && event.mouseButton.y <= 465)//y
						Press = 1;	
				}	
				else if(event.mouseButton.x >= 190 && event.mouseButton.x <= 295)//Game_2
				{
					if(event.mouseButton.y >= 530 && event.mouseButton.y <= 615)
						Press = 2;
				}
				else if(event.mouseButton.x >= 490 && event.mouseButton.x <= 595)//Game3
				{
					if(event.mouseButton.y >= 440 && event.mouseButton.y <= 525)
						Press = 3;
				}
				else if(event.mouseButton.x >= 360 && event.mouseButton.x <= 445)
				{
					if(event.mouseButton.y >= 280 && event.mouseButton.y <= 365)
						Press = 4;
				}
			}
			else if(event.type == Event::KeyPressed)//調整音量 
			{
				if(event.key.code == Keyboard::Up)//UP鍵是調大聲 
				{
					volume += 5;
					background.setVolume(volume);
				}
				else if(event.key.code == Keyboard::Down)//DOWN鍵是調小聲 
				{
					volume -= 5;
					background.setVolume(volume);
				}
			}
			
			if(Mx >= 50 && Mx <= 135 && My >= 380 && My <= 465)//Game_1 range(50-135, 380-465)
			{
				condition = 1;		
			}	
			else if(Mx >= 190 && Mx <= 295 && My >= 530 && My <= 615)//Game_2 range(190-295, 530-615)
			{
				condition = 2; 
			}	
			else if(Mx >= 490 && Mx <= 595 && My >= 440 && My <= 525)//Game3 range(490-595, 440-525)
			{
				condition = 3;
			}
			else if(Mx >= 360 && Mx <= 445 && My >= 280 && My <= 365)//Game_4 range(360-445, 280-365)
			{
				condition = 4;
			}
			else 
				condition = 0;

			
		}
		
		window.clear();
		
		if(condition == 0)
			window.draw(Cover);
		else if(condition == 1)
			window.draw(First_Cover);
		else if(condition == 2)
			window.draw(Second_Cover);
		else if(condition == 3)
			window.draw(Third_Cover);
		else if(condition == 4)
			window.draw(Fourth_Cover);
		
		if((Press == 1) and (Mx >= 50 && Mx <= 135) and (My >= 380 && My <= 465))
		{
			if(lock_rank_2 == true)
				window.draw(game1_choose_1);
			else
				window.draw(game1_choose_2);
				
			window.draw(game1[0]);
			window.draw(game1[1]);
			if(rank != 0)
				break;
		}	
		window.draw(Game_1);
		window.draw(Game_2);
		window.draw(Game_3);
		window.draw(Game_4);
	  //window.draw(Game_1_txt);
		window.display();
		if(Press > 1)
			break;
	}
	
	 
	if(Press == 1 && rank == 1)//Game_1 
	{
		int Mx = 0;
		int My = 0;
		bool open_hint_1_1 = false;
		
		
		bool close = false;
		while(window.isOpen())
		{
			
			Event event;
			while(window.pollEvent(event))	
			{
				if(event.type == Event::Closed)
	                window.close();
				else if(event.type == Event::MouseButtonPressed)
				{
					
					if(event.mouseButton.x >= 261 && event.mouseButton.x <= 386)
					{
						if(event.mouseButton.y >= 426 && event.mouseButton.y <= 460)
						{
							close = true;
						}
					}
					//cout << "(" << event.mouseButton.x << ", " << event.mouseButton.y << ")\n";
				}
			}
			if(close == true)
				break;
			window.clear();
			window.draw(rule_game_1);
			//window.draw(tmp);
			window.display();
		}
		
		int former = 0;
		win = 0;
		int robot = 0;
		int win_person = -1; // 0 = robot, 1 = us, -1 = not yet
		points = 0;
		step = 0;
		avoid = 0;
		cur.str("");
		cur << "Current: " << step;
		current.setString(cur.str());
		
		for(int i = 1; i <= 30; i++)
		{
			circle[i].setFillColor({0, 102, 128});
		}
		while(window.isOpen())
		{	
			Mx = Mouse::getPosition(window).x;
			My = Mouse::getPosition(window).y;
			if(robot != 0){
				sleep(1);
				points += robot;
				int reply = handle_move(robot);
				former = step;
				step += reply;
				points += reply;
				for(int i = former+1; i <= step; i++)
				{
					circle[i].setFillColor({178,136,237});
				}
							
				cur.str("");
				cur << "Current: " << step;
				current.setString(cur.str());
				robot = 0;
				avoid = 0;
				
				if(step == 29)
					win_person = 0;
			}
			
			Event event;
			while(window.pollEvent(event))	
			{
				if(event.type == Event::Closed)
	                window.close();
				
				if(open_hint_1_1 == false)
				{
					
					if(event.type == Event::MouseButtonPressed && avoid == 0)//Press
					{
						cout << "Mx= " << Mx << " ,My= " << My << "\n";
						if(event.mouseButton.x >= 45 && event.mouseButton.x <= 96 && event.mouseButton.y >= 55 && event.mouseButton.y <= 106)
						{
							open_hint_1_1 = true;
						}
						else if(event.mouseButton.x >= 544 && event.mouseButton.x <= 595 && event.mouseButton.y >= 55 && event.mouseButton.y <= 106)
						{
							goto main_game;
						}
						if(event.mouseButton.x >= 130 && event.mouseButton.x <= 250)// range(130~250, 475~545)	
						{
							if(event.mouseButton.y >= 475 && event.mouseButton.y <= 545)
							{
								button.play();
								former = step;
								
								step++;
								cur.str("");
								cur << "Current: " << step;
								current.setString(cur.str());
								
								
								for(int i = former+1; i <= step; i++)
								{
									circle[i].setFillColor({237, 237, 93});
								}
								robot = 1;
								avoid = 1;
								
								if(step == 29)
									win_person = 1;
								
								
							}
						}
						else if(event.mouseButton.x >= 260 && event.mouseButton.x <= 380)// range(260~380, 475~545)
						{
							if(event.mouseButton.y >= 475 && event.mouseButton.y <= 545)
							{
								button.play();
								former = step;
								
								step += 2;
								cur.str("");
								cur << "Current: " << step;
								current.setString(cur.str());
								
								for(int i = former+1; i <= step; i++)
								{
									circle[i].setFillColor({237, 237, 93});
								}
								robot = 2;
								avoid = 1;
								
								if(step == 29)
									win_person = 1;
							}
						}
						else if(event.mouseButton.x >= 390 && event.mouseButton.x <= 510)// range(390~510, 475~545)
						{
							if(event.mouseButton.y >= 475 && event.mouseButton.y <= 545)
							{
								button.play();
								former = step;
								
								step += 3;
								cur.str("");
								cur << "Current: " << step;
								current.setString(cur.str());
								
								for(int i = former+1; i <= step; i++)
								{
									circle[i].setFillColor({237, 237, 93});
								}
								robot = 3;
								avoid = 1;
								
								if(step == 29)
									win_person = 1;
							}
						}
					}
				}
				else
				{
					if(event.mouseButton.x >= 495 && event.mouseButton.x <= 535 && event.mouseButton.y >= 135 && event.mouseButton.y <= 175)
					{
						open_hint_1_1 = 0;
					}
				}
			}
			
			window.clear();
			if(open_hint_1_1 == 0)
			{
				window.draw(back_1_cover);
				window.draw(Plus_1);
				window.draw(Plus_2);
				window.draw(Plus_3);
				window.draw(cancel_button);
				window.draw(hint);
				//window.draw(xx);
				for(int i = 1; i <= 30; i++)
				{
					window.draw(circle[i]);
					window.draw(number[i]);
				}
			}
			else if(open_hint_1_1 != 0)
			{
				window.draw(hint_1_1);
				window.draw(cancel_hint);
			}
			window.display();
			
			/*if(open_hint_1_1 != 0)
			{
				sleep(3);
				open_hint_1_1 = false;
			}*/
			if(win_person != -1)
			{
				sleep(1);
				break;

			}
		}
		
		//win and lose的畫面
		if(win_person == 1)
			lock_rank_2 = false;
		else
			; //do nothing
			
		end_image(win_person, window);
		goto main_game;
	}
	else if(Press == 1 && rank == 2)
	{
		
		Texture rule_1_2_text;
		rule_1_2_text.loadFromFile("image/Rule_g1_2.png");
	
		Sprite rule_1_2(rule_1_2_text);
		rule_1_2.setScale(Vector2f(0.625f, 0.625f));
		
		
		bool close_1_2 = false;
		while(window.isOpen())
		{
			
			Event event;
			while(window.pollEvent(event))	
			{
				if(event.type == Event::Closed)
	                window.close();
				else if(event.type == Event::MouseButtonPressed)
				{
					
					if(event.mouseButton.x >= 261 && event.mouseButton.x <= 386)
					{
						if(event.mouseButton.y >= 426 && event.mouseButton.y <= 460)
						{
							close_1_2 = true;
						}
					}
					//cout << "(" << event.mouseButton.x << ", " << event.mouseButton.y << ")\n";
				}
			}
			if(close_1_2 == true)
				break;
			window.clear();
			window.draw(rule_1_2);
			//window.draw(tmp);
			window.display();
		}
		
		
		ostringstream output;
		
		ostringstream now;
		now << 30;
		
		Text cur_num_2;
		cur_num_2.setFont(font);
		cur_num_2.setFillColor(Color::Black);
		cur_num_2.setCharacterSize(24);
		cur_num_2.setPosition(Vector2f(240.f , 465.f));
		cur_num_2.setString(now.str());
		
		Text IN;
		IN.setFont(font);
		IN.setFillColor(Color::Black);
		IN.setCharacterSize(30);
		IN.setPosition(Vector2f(390.f, 425.f)); 
		IN.setString(output.str());
		
		Text AI_text;
		AI_text.setFont(font);
		AI_text.setFillColor(Color::Black);
		AI_text.setCharacterSize(30);
		AI_text.setPosition(Vector2f(200.f, 200.f)); 
		AI_text.setString("");
		
		Text available_text;
		available_text.setFont(font);
		available_text.setFillColor(Color::Black);
		available_text.setCharacterSize(30);
		available_text.setPosition(Vector2f(400.f, 200.f)); 
		available_text.setString("");
		
		
		int number;
		int current = 30;
		int receive = 0;
		bool condition = 0;
		bool result = false;
		string input;
		string record;
		string now_str;
		string range;
		
		init();
		
		while(window.isOpen())
		{
			
			if(condition == 1)
			{
				if(current == 0)
				{
					result = true;
					break;
				}
				sleep(1);
				// AI接收收到的數字
				current -= receive; 
        	    now_str = to_string(current);
				cur_num_2.setString(now_str);
				condition = 0;
				
				if(current == 0)
				{
					result = false;
					break;
				}
			}
			
			
			Event event;
			while(window.pollEvent(event))	
			{
				Mx = Mouse::getPosition(window).x;
				My = Mouse::getPosition(window).y;
				if(event.type == Event::Closed)
	                window.close();    
	            else if(event.type == Event::MouseButtonPressed)
	            {
	            	if(event.mouseButton.x >= 544 && event.mouseButton.x <= 595 && event.mouseButton.y >= 55 && event.mouseButton.y <= 106)
					{
						goto main_game;
					}
				}
				else if(event.type == Event::KeyPressed)
				{
					if(event.key.code == Keyboard::Return)
	                {
	                	number = stoi(record);
	                	record = "";
	                	output.str("");
	                	IN.setString(output.str());
	                	//output << "Enter Number:\n";
	                	IN.setString(output.str());
	                	cout << "Me: " << number << "\n";
	                	receive = AI_move(number);
	                	cout << "AI: " << receive << "\n";
	                	if(receive != -1)//正確的範圍 
	                	{
	                		range = "";	
	                		range += "1-";
	                		range += to_string(2*receive);
	                		available_text.setString(range);
	                		
	                		if(receive < 10)
	                		{
								AI_text.setPosition(Vector2f(200.f, 200.f));
								available_text.setPosition(Vector2f(410.f, 200.f)); 
							}
	                		else
	                		{
	                			AI_text.setPosition(Vector2f(180.f, 200.f));
	                			available_text.setPosition(Vector2f(400.f, 200.f)); 
	                			
							}
	                		
	                		AI_text.setString(to_string(receive));
							current -= number;
		                	now_str = to_string(current);
		                	cur_num_2.setString(now_str);
		                	condition = true;
		                	if(current == 0)
		                	{
		                		result = true;
		                		break;
							}
	                	}
	                	else
	                	{
	                		AI_text.setPosition(Vector2f(155.f, 200.f));
	                		AI_text.setString("illegal");
						}
	                	
					} 
					else if(event.key.code == Keyboard::Num0)
					{
						input = "0";
						record += "0";
						output << input;
						IN.setString(output.str());
					}
					else if(event.key.code == Keyboard::Num1)
					{
						input = "1";
						record += "1";
						output << input;
						IN.setString(output.str());
					}
					else if(event.key.code == Keyboard::Num2)
					{
						input = "2";
						record += "2";
						output << input;
						IN.setString(output.str());
					}
					else if(event.key.code == Keyboard::Num3)
					{
						input = "3";
						record += "3";
						output << input;
						IN.setString(output.str());
					}
					else if(event.key.code == Keyboard::Num4)
					{
						input = "4";
						record += "4";
						output << input;
						IN.setString(output.str());
					}
					else if(event.key.code == Keyboard::Num5)
					{
						input = "5";
						record += "5";
						output << input;
						IN.setString(output.str());
					}
					else if(event.key.code == Keyboard::Num6)
					{
						input = "6";
						record += "6";
						output << input;
						IN.setString(output.str());
					}
					else if(event.key.code == Keyboard::Num7)
					{
						input = "7";
						record += "7";
						output << input;
						IN.setString(output.str());					
					}
					else if(event.key.code == Keyboard::Num8)
					{
						input = "8";
						record += "8";
						output << input;
						IN.setString(output.str());
					}
					else if(event.key.code == Keyboard::Num9)
					{
						input = "9";
						record += "9";
						output << input;
						IN.setString(output.str());
					}
					else if(event.key.code == Keyboard::BackSpace)
					{
						record.pop_back();
						output.str("");
						output << record;
						//cout << output.str() << "\n";
						IN.setString(output.str());
					}
				}
			}
			
			window.clear();
			window.draw(back_1_2_cover);
			window.draw(IN);
			window.draw(cur_num_2);
			window.draw(AI_text);
			window.draw(available_text);
			window.draw(cancel_button);
			//window.draw(hint);
			window.display();
		}
		
		end_image(result, window);
		goto main_game;
		
	}
	else if(Press == 2)//Game_2
	{
		bool close = false;
		bool open_hint_2 = false;
		
	
		while(window.isOpen())
		{
			Event event;
			while(window.pollEvent(event))	
			{
				if(event.type == Event::Closed)
	                window.close();
				else if(event.type == Event::MouseButtonPressed)
				{
					if(event.mouseButton.x >= 261 && event.mouseButton.x <= 386)
					{
						if(event.mouseButton.y >= 426 && event.mouseButton.y <= 460)
						{
							close = true;
						}
					}
					//cout << "(" << event.mouseButton.x << ", " << event.mouseButton.y << ")\n";
				}
			}
			if(close == true)
				break;
			window.clear();
			window.draw(rule_game_2);
			window.display();
		}
		
		int number;

		string input;
		string record;
		
		int play = 0;
		int score[5] = {0};
		int wp = -1;
		bool result = 0;
		
		ostringstream output;
		ostringstream AI_1;
		ostringstream AI_2;
		ostringstream AI_3;
		ostringstream AI_4;

		Text IN;
		IN.setFont(font);
		IN.setFillColor(Color::Black);
		IN.setCharacterSize(30);
		IN.setPosition(Vector2f(296.f, 390.f)); 
		IN.setString(output.str());
		
		Text number_1;
		number_1.setFont(font);
		number_1.setFillColor(Color::Black);
		number_1.setCharacterSize(30);
		number_1.setPosition(Vector2f(65.f, 195.f));//個位數時 73 
		number_1.setString(AI_1.str());
		
		Text number_2;
		number_2.setFont(font);
		number_2.setFillColor(Color::Black);
		number_2.setCharacterSize(30);
		number_2.setPosition(Vector2f(173.f, 195.f));
		number_2.setString(AI_2.str());
		
		Text number_3;
		number_3.setFont(font);
		number_3.setFillColor(Color::Black);
		number_3.setCharacterSize(30);
		number_3.setPosition(Vector2f(385.f,195.f));
		number_3.setString(AI_3.str());
		
		Text number_4;
		number_4.setFont(font);
		number_4.setFillColor(Color::Black);
		number_4.setCharacterSize(30);
		number_4.setPosition(Vector2f(493.f, 195.f));
		number_4.setString(AI_4.str());
		
		Text score_me;
		score_me.setFont(font);
		score_me.setFillColor(Color::Black);
		score_me.setCharacterSize(30);
		score_me.setPosition(Vector2f(530.f, 460.f));
		score_me.setString("0");
		
		Text score_1;
		score_1.setFont(font);
		score_1.setFillColor(Color::Black);
		score_1.setCharacterSize(30);
		score_1.setPosition(Vector2f(120.f, 145.f));
		score_1.setString("0");
		
		Text score_2;
		score_2.setFont(font);
		score_2.setFillColor(Color::Black);
		score_2.setCharacterSize(30);
		score_2.setPosition(Vector2f(228.f,145.f));
		score_2.setString("0");
		
		Text score_3;
		score_3.setFont(font);
		score_3.setFillColor(Color::Black);
		score_3.setCharacterSize(30);
		score_3.setPosition(Vector2f(440.f,145.f));
		score_3.setString("0");
		
		Text score_4;
		score_4.setFont(font);
		score_4.setFillColor(Color::Black);
		score_4.setCharacterSize(30);
		score_4.setPosition(Vector2f(548.f,145.f));
		score_4.setString("0");
		
		Text average;
		average.setFont(font);
		average.setFillColor(Color::Black);
		average.setCharacterSize(50);
		average.setPosition(Vector2f(150.f,460.f));
		average.setString("");
		
		
		
		while(window.isOpen()) 
		{	
			if (play != 0)
			{
				//cout << "load\n";
				AI_1.str("");
				AI_2.str("");
				AI_3.str("");
				AI_4.str("");
				
				int board[5] = {0};
				board[0] = normal_AI(rounds);
				AI_1 << to_string(board[0]);
				number_1.setString(AI_1.str());
				if(board[0] >= 10)
					number_1.setPosition(Vector2f(65.f, 195.f));
				else
					number_1.setPosition(Vector2f(73.f, 195.f));//加 8 
				
				
				board[1] = smart_AI(rounds);
				AI_2 << to_string(board[1]);
				number_2.setString(AI_2.str());
				if(board[1] >= 10)
					number_2.setPosition(Vector2f(173.f, 195.f));
				else
					number_2.setPosition(Vector2f(181.f, 195.f));//加 8 
				
				board[2] = super_AI(rounds);
				AI_3 << to_string(board[2]);
				number_3.setString(AI_3.str());
				if(board[2] >= 10)
					number_3.setPosition(Vector2f(385.f, 195.f));
				else
					number_3.setPosition(Vector2f(393.f, 195.f));//加 8 
				
				board[3] = random_AI(rounds);
				AI_4 << to_string(board[3]);
				number_4.setString(AI_4.str());
				if(board[3] >= 10)
					number_4.setPosition(Vector2f(493.f, 195.f));
				else
					number_4.setPosition(Vector2f(501.f, 195.f));//加 8 
				
				board[4] = number;
				
				int sum = 0;
        		for(int i = 0; i < 5; i++){
            		sum += board[i];
        		}
        		int aver = sum /= 10;
        		cout << "average= " << aver << "\n";
        		int less = 1000;//很大的數字 
        		int win_idx = -1;
        		for(int i = 0; i < 5; i++){
            		board[i] -= aver;
            		if(board[i] < 0){
                		board[i] = -board[i];
            		}
            		if(board[i] <= less){
                		less = board[i];
                		win_idx = i;
            		}
        		}
        		
        		score[win_idx] += 1;
        		 
        		score_me.setString(to_string(score[4]));
        		score_1.setString(to_string(score[0]));
        		score_2.setString(to_string(score[1]));
        		score_3.setString(to_string(score[2]));
        		score_4.setString(to_string(score[3]));
        		average.setString(to_string(aver));
        		
        		if(aver < 10)
        			average.setPosition(Vector2f(150.f,460.f));
        		else
        			average.setPosition(Vector2f(135.f,460.f));
        		
        		if(score[win_idx] >= 5)//5分獲勝 
				{
        			wp = win_idx;
        			break;
				}
        		play = 0;
        		rounds ++;
        		last = aver;
				
			}
			Event event;
			while(window.pollEvent(event))
			{	
				if(event.type == Event::Closed)
                	window.close();
                if(open_hint_2 == 0)
                {
				
	                if(event.type == Event::MouseButtonPressed)
	                {
	                	if(event.mouseButton.x >= 45 && event.mouseButton.x <= 96 && event.mouseButton.y >= 55 && event.mouseButton.y <= 106)
						{
							open_hint_2 = true;
						}
	                	if(event.mouseButton.x >= 544 && event.mouseButton.x <= 595 && event.mouseButton.y >= 55 && event.mouseButton.y <= 106)
						{
							goto main_game;
						}
					}
	                else if(event.type == Event::KeyPressed)
	                {
	                	if(event.key.code == Keyboard::Return)
	                	{
	                		number = stoi(record);
	                		record = "";
	                		output.str("");
	                		IN.setString(output.str());
	                		//output << "Enter Number:\n";
	                		IN.setString(output.str());
	                		cout << number << "\n";
	                		play = 1;
						}
	                	else if(event.key.code == Keyboard::Num0)
						{
							input = "0";
							record += "0";
							output << input;
							IN.setString(output.str());
						}
						else if(event.key.code == Keyboard::Num1){
							input = "1";
							record += "1";
							output << input;
							IN.setString(output.str());
						}
						else if(event.key.code == Keyboard::Num2){
							input = "2";
							record += "2";
							output << input;
							IN.setString(output.str());
						}
						else if(event.key.code == Keyboard::Num3){
							input = "3";
							record += "3";
							output << input;
							IN.setString(output.str());
						}
						else if(event.key.code == Keyboard::Num4){
							input = "4";
							record += "4";
							output << input;
							IN.setString(output.str());
						}
						else if(event.key.code == Keyboard::Num5){
							input = "5";
							record += "5";
							output << input;
							IN.setString(output.str());
						}
						else if(event.key.code == Keyboard::Num6){
							input = "6";
							record += "6";
							output << input;
							IN.setString(output.str());
						}
						else if(event.key.code == Keyboard::Num7){
							input = "7";
							record += "7";
							output << input;
							IN.setString(output.str());
						}
						else if(event.key.code == Keyboard::Num8){
							input = "8";
							record += "8";
							output << input;
							IN.setString(output.str());
						}
						else if(event.key.code == Keyboard::Num9){
							input = "9";
							record += "9";
							output << input;
							IN.setString(output.str());
						}
						else if(event.key.code == Keyboard::BackSpace){
							record.pop_back();
							output.str("");
							output << record;
							//cout << output.str() << "\n";
							IN.setString(output.str());
						}
					}
				}
				else 
				{
					if(event.mouseButton.x >= 495 && event.mouseButton.x <= 535 && event.mouseButton.y >= 135 && event.mouseButton.y <= 175)
						open_hint_2 = false;
				}
			}
			
			if(open_hint_2 == 0)
			{	
				window.clear();
				window.draw(back_2_cover);
				window.draw(IN);
				window.draw(number_1);
				window.draw(number_2);
				window.draw(number_3);
				window.draw(number_4);
				window.draw(score_me);
				window.draw(score_1);
				window.draw(score_2);
				window.draw(score_3);
				window.draw(score_4);
				window.draw(average);
				window.draw(cancel_button);
				window.draw(hint);
			}
			else
			{
				window.draw(hint_2);
				window.draw(cancel_hint);
			}
			window.display();
			/*if(open_hint_2 != 0)
			{
				sleep(3);
				open_hint_2 = false;
			}*/
			
		}
		//win and lose的畫面
		if(wp >= 0 && wp < 4)
			result = false;
		else if(wp == 4)
			result = true;

		end_image(result, window);
		goto main_game;
	}
	else if(Press == 3)
	{
		Texture card_t;
		card_t.loadFromFile("image/Poker_teacher.png");
	
		Texture card_s;
		card_s.loadFromFile("image/Poker_student.png");
		
		Texture card_t_call;
		card_t_call.loadFromFile("image/Poker4.png");
		
		Texture card_t_no_call;
		card_t_no_call.loadFromFile("image/Poker3.png");
		
		Texture card_s_attend;
		card_s_attend.loadFromFile("image/Poker2.png");
		
		Texture card_s_no_attend;
		card_s_no_attend.loadFromFile("image/Poker1.png");
		
		Texture Player_Score_text;
		Player_Score_text.loadFromFile("image/cp_game3_new1.png");
		
		Texture AI_Score_text;
		AI_Score_text.loadFromFile("image/cp_game3_new2.png");
		
		Texture choose_in_text;
		choose_in_text.loadFromFile("image/cp_game3_new3.png");
		
		Texture cancel_in_text;
		cancel_in_text.loadFromFile("image/cp_game3_new4.png");
		
		Sprite Player_Score(Player_Score_text);
		Player_Score.setScale(Vector2f(0.5, 0.5));
		Player_Score.setPosition(Vector2f(110, 55));
		
		Sprite AI_Score(AI_Score_text);
		AI_Score.setScale(Vector2f(0.5, 0.5));
		AI_Score.setPosition(Vector2f(440, 55));
		
		Sprite choose_in(choose_in_text);
		choose_in.setPosition(Vector2f(440, 55));
		
		Sprite cancel_in(cancel_in_text);
		cancel_in.setPosition(Vector2f(440, 55));
		
		Text player;
		player.setFont(font);
		player.setFillColor(Color::Black);
		player.setCharacterSize(30);
		player.setPosition(Vector2f(141.f, 75.f)); 
		player.setString("0");
		
		Text AI;
		AI.setFont(font);
		AI.setFillColor(Color::Black);
		AI.setCharacterSize(30);
		AI.setPosition(Vector2f(471.f, 75.f)); 
		AI.setString("0");
		/******test********/
		
		RectangleShape test;
		test.setSize(Vector2f(225.f, 225.f));
		test.setPosition(Vector2f(330.f, 245.f));
		test.setFillColor(Color::Black);
		
		RectangleShape test_tall;
		test_tall.setSize(Vector2f(125.f, 285.f));
		test_tall.setPosition(Vector2f(380.f, 215.f));
		test_tall.setFillColor(Color::Black);
		
		int win_player = 0;
		int win_AI = 0;
		/******************/
		
		/******選擇畫面*****/ 
		
		bool open_hint_3 = false;
		int rank = 0;
		int cond = 0;
		int bx = 0;//bx = button_x
		int by = 0;//by = button_y
		/*******規則3*******/ 
		bool close_3 = false;
		while(window.isOpen())
		{
			Event event;
			while(window.pollEvent(event))	
			{
				if(event.type == Event::Closed)
	                window.close();
				else if(event.type == Event::MouseButtonPressed)
				{
					if(event.mouseButton.x >= 261 && event.mouseButton.x <= 386)
					{
						if(event.mouseButton.y >= 426 && event.mouseButton.y <= 460)
						{
							close_3 = true;
						}
					}
					//cout << "(" << event.mouseButton.x << ", " << event.mouseButton.y << ")\n";
				}
			}
			if(close_3 == true)
				break;
			window.clear();
			window.draw(rule_game_3);
			window.display();
		}
		/*****************/
		
		
		
		while(window.isOpen())
		{
			Mx = Mouse::getPosition(window).x;
			My = Mouse::getPosition(window).y;
			Event event;
			while(window.pollEvent(event))
			{
				if(event.type == Event::Closed)
					window.close();
				
				if(open_hint_3 == 0)
				{
					
					if(event.type == Event::MouseButtonPressed)
					{
						bx = event.mouseButton.x;
						by = event.mouseButton.y;
						cout << "bx: " << bx << " ,by: " << by << "\n";
						
						
							
						if(event.mouseButton.x >= 45 && event.mouseButton.x <= 96 && event.mouseButton.y >= 55 && event.mouseButton.y <= 106)
						{
							open_hint_3 = true;
						}
						else if(bx >= 544 && bx <= 595 && by >= 55 && by <= 106)
						{
							goto main_game;
						}
						if(((bx >= 85 && bx <= 310) and (by >= 245 && by <= 470)) or ((bx >= 135 && bx <= 260) and (by >= 215 && by <= 500)))
						{
							rank = 1;//choose teacher 
						}
						else if(((bx >= 330 && bx <= 555) and (by >= 245 && by <= 470)) or ((bx >= 380 && bx <= 505) and (by >= 215 && by <= 500)))
						{
							rank = 2;//choose student
						}
					}
					
					if(((Mx >= 85 && Mx <= 310) and (My >= 245 && My <= 470)) or ((Mx >= 135 && Mx <= 260) and (My >= 215 && My <= 500)))
					{
						cond = 1;//teacher condition
					}
					else if(((Mx >= 330 && Mx <= 555) and (My >= 245 && My <= 470)) or ((Mx >= 380 && Mx <= 505) and (My >= 215 && My <= 500)))
					{
						cond = 2;//student condition
					}
					else
						cond = 0;
				}
				else
				{
					if(event.mouseButton.x >= 495 && event.mouseButton.x <= 535 && event.mouseButton.y >= 135 && event.mouseButton.y <= 175)
						open_hint_3 = false;
				}
			}
			
			if(rank != 0)
				break;
			
			if(open_hint_3 == 0)
			{
				
				window.clear();
				if(cond == 0)
				{
					window.draw(choose);	
				}
				else if(cond == 1)
				{
					window.draw(choose_t);
				}
				else if(cond == 2)
				{
					window.draw(choose_s);	
				}
				window.draw(cancel_button);
				window.draw(hint);
			}
			else
			{
				window.draw(hint_3);
				window.draw(cancel_hint);
			}
			window.display();
			/*if(open_hint_3 != 0)
			{
				sleep(3);
				open_hint_3 = false;
			}*/
		}
		
		/*****************************/
		Game_3:
		bool t[5] = {0};//teacher random seed
		bool s[5] = {0};//student random seed
		int press = 0;
		int copy_press = 0;
		int copy_digit = 0;
		int win_tmp = -1;//平手 
		bool show = false;
		bool del_t[5] = {0};
		bool del_s[5] = {0};
		bx = 0;
		by = 0;
		
		
		Vector2f position_AI[5] = {Vector2f(0,0), Vector2f(95,180), Vector2f(220,180), Vector2f(345,180), Vector2f(470,180)};//紀錄 teacher 4張牌的 起始位置 
		Vector2f position_player[5] = {Vector2f(0,0), Vector2f(95,420), Vector2f(220,420), Vector2f(345,420), Vector2f(470,420)};//紀錄 student 4張牌的 起始位置 
		 
		srand(time(NULL));
		int value_t = rand() % 4 + 1;//決定哪一張牌是點名 
		
		srand(rand());
		int value_s = rand() % 4 + 1;
		
		//cout << "Teacher: " << value_t << " ,Student: " << value_s << "\n";
		
		t[value_t] = 1;//決定好誰是點名 
		s[value_s] = 1;//決定好誰是翹課 
		
		RectangleShape Poker_t_call;
		Poker_t_call.setSize(Vector2f(80.f, 100.f));
		Poker_t_call.setTexture(&card_t_call);
		
		RectangleShape Poker_t_no_call;
		Poker_t_no_call.setSize(Vector2f(80.f, 100.f));
		Poker_t_no_call.setTexture(&card_t_no_call);
		
		RectangleShape Poker_s_attend;
		Poker_s_attend.setSize(Vector2f(80.f, 100.f));
		Poker_s_attend.setTexture(&card_s_attend);
		
		RectangleShape Poker_s_no_attend;
		Poker_s_no_attend.setSize(Vector2f(80.f, 100.f));
		Poker_s_no_attend.setTexture(&card_s_no_attend);
		
		RectangleShape Poker_t[5];
		RectangleShape Poker_s[5];
		
		for(int i = 1; i < 5; i++)
		{
			Poker_t[i].setSize(Vector2f(80.f, 100.f));
			Poker_s[i].setSize(Vector2f(80.f, 100.f));
			
			if(rank == 1)//choose teacher
			{
				Poker_t[i].setPosition(position_player[i]);
				Poker_s[i].setPosition(position_AI[i]);
				Poker_s[i].setTexture(&card_s);
				if(i == value_t)
					Poker_t[i].setTexture(&card_t_call);
				else
					Poker_t[i].setTexture(&card_t_no_call);
			}
			else if(rank == 2)//choose student
			{
				Poker_t[i].setPosition(position_AI[i]);
				Poker_s[i].setPosition(position_player[i]);
				Poker_t[i].setTexture(&card_t);
				if(i == value_s)
					Poker_s[i].setTexture(&card_s_attend);
				else
					Poker_s[i].setTexture(&card_s_no_attend);
			}
		}
		
		Vector2f set[2] = {Vector2f(150.f, 300.f), Vector2f(350.f, 308.f)};
		
		choose_in.setPosition(set[0]);//(160-287), (315-385)
		cancel_in.setPosition(set[1]);//(362-489), (315-385)

		
		while(window.isOpen())
		{
					
			if(win_tmp != -1)//不是平手的話 
			{
				if(win_tmp == 1)
				{
					win_player += 1;
					player.setString(to_string(win_player));
				}
				else
				{
					win_AI += 1;
					AI.setString(to_string(win_AI));
				}
				
				break;
			}
			Event event;
			while(window.pollEvent(event))
			{
				if(event.type == Event::Closed)
				{
					rank = -1;
					window.close();
				}
				if(open_hint_3 == 0)
				{
					
					if(event.type == Event::MouseButtonPressed)	
					{
						bx = event.mouseButton.x;
						by = event.mouseButton.y;
						//cout << "bx: " << bx << ", by: " << by << "\n";
						if(event.mouseButton.x >= 45 && event.mouseButton.x <= 96 && event.mouseButton.y >= 55 && event.mouseButton.y <= 106)
						{
							open_hint_3 = true;
						} 
						else if(event.mouseButton.x >= 544 && event.mouseButton.x <= 595 && event.mouseButton.y >= 55 && event.mouseButton.y <= 106)
						{
							goto main_game;
						}
						if(press != 0)
						{
							if((bx >= 160 && bx <= 287) and (by >= 315 && by <= 385))//enter 
							{
								copy_press = press;
								int back = 0;
								int digit = 0;
								int seed = rand() + 10;
								if(rank == 1)//we are teacher
								{
									del_t[press] = true;
									
									while(back == 0)
									{
										srand(seed);
										digit = rand() % 4 + 1;
										if(del_s[digit] == 0)//未選過 
										{
											del_s[digit] = true;
											back = 1;
										}
										else
											seed += 1;
									}	
								}
								else if(rank == 2)
								{
									del_s[press] = true;
									
									while(back == 0)
									{
										srand(seed);
										//cout << rand() << "\n";
										digit = rand() % 4 + 1;
										if(del_t[digit] == 0)//未選過 
										{
											del_t[digit] = true;
											back = 1;
										}
										else
											seed += 1;
										//cout << "digit: " << digit << "\n"; 
									}
								}
								//cout << "press: " << press << " ,another: " << digit << "\n";
								show = true;
								copy_digit = digit;
								press = 0;
								win_tmp = outcome(copy_press, copy_digit, value_t, value_s, rank);
								//cout << "middle_tmp: " << win_tmp << "\n";		
							}
							else if((bx >= 362 && bx <= 489) and (by >= 315 && by <= 385))//cancel
							{
								press = 0;
							}
						}
						else if((bx >= 95 && bx <= 175) and (by >= 420 && by <= 520))//下方第一張 
						{
							if((rank == 1) and (del_t[1] == 0))
								press = 1;
							else if((rank == 2) and (del_s[1]) == 0)
								press = 1;
						}
						else if((bx >= 220 && bx <= 300) and (by >= 420 && by <= 520))//下方第二張 
						{
							if((rank == 1) and (del_t[2] == 0))
								press = 2;
							else if((rank == 2) and (del_s[2]) == 0)
								press = 2;
						}
						else if((bx >= 345 && bx <= 425) and (by >= 420 && by <= 520))//下方第三張 
						{
							if((rank == 1) and (del_t[3] == 0))
								press = 3;
							else if((rank == 2) and (del_s[3]) == 0)
								press = 3;
						}
						else if((bx >= 470 && bx <= 550) and (by >= 420 && by <= 520))//下方第四張 
						{
							if((rank == 1) and (del_t[4] == 0))
								press = 4;
							else if((rank == 2) and (del_s[4]) == 0)
								press = 4;
						}
					}
				}
				else
				{
					if(event.mouseButton.x >= 495 && event.mouseButton.x <= 535 && event.mouseButton.y >= 135 && event.mouseButton.y <= 175)
						open_hint_3 = false;
				}
			}
			
			
			window.clear();
			if(open_hint_3 == 0)
			{	
				window.draw(back_3_cover);
				for(int i = 1; i < 5; i++)
				{
					if(del_t[i] == 0) //尚未按下過 
						window.draw(Poker_t[i]);
					if(del_s[i] == 0)
						window.draw(Poker_s[i]);
				}
				if(press != 0)
				{
					window.draw(choose_in);
					window.draw(cancel_in);
				}
				if(show == true)
				{
					if(rank == 1)//teacher
					{
						if(copy_press == value_t)//等等要去掉 
						{
							Poker_t_call.setPosition(position_player[copy_press]);
							window.draw(Poker_t_call);
						}
						else
						{
							Poker_t_no_call.setPosition(position_player[copy_press]);
							window.draw(Poker_t_no_call);
						}
						
						if(copy_digit == value_s)//保留 
						{
							Poker_s_attend.setPosition(position_AI[copy_digit]);
							window.draw(Poker_s_attend);
						}
						else
						{
							Poker_s_no_attend.setPosition(position_AI[copy_digit]);
							window.draw(Poker_s_no_attend);
						}
					}
					else if(rank == 2)//student
					{
						if(copy_press == value_s)//去掉 
						{
							Poker_s_attend.setPosition(position_player[copy_press]);
							window.draw(Poker_s_attend);
						}
						else
						{
							Poker_s_no_attend.setPosition(position_player[copy_press]);
							window.draw(Poker_s_no_attend);
						}
						
						if(copy_digit == value_t)//保留 
						{
							Poker_t_call.setPosition(position_AI[copy_digit]);
							window.draw(Poker_t_call);
						}
						else
						{
							Poker_t_no_call.setPosition(position_AI[copy_digit]);
							window.draw(Poker_t_no_call);
						}
					}	
				}
				window.draw(cancel_button);
				window.draw(hint);
				window.draw(Player_Score);
				window.draw(AI_Score);
				window.draw(player);
				window.draw(AI);
			}
			else
			{
				window.draw(hint_3);
				window.draw(cancel_hint);
			}
			window.display();
			/*if(open_hint_3 != 0)
			{
				sleep(3);
				open_hint_3 = false;
			}*/
			if(show == true)
			{
				sleep(1);
				show = 0;
			}
		}
		
		cout << "\nPlayer: " << win_player << "\nAI: " << win_AI << "\n";
		if(rank == 1)
		{
			if(win_player == 3)
			{
				end_image(true, window);
				goto main_game;
			}
			else if(win_AI == 1)
			{
				end_image(false, window);
				goto main_game;
			}
		}
		else if(rank == 2)
		{
			if(win_player == 1)
			{
				end_image(true, window);
				goto main_game;
			}
			else if(win_AI == 3)
			{
				end_image(false, window);
				goto main_game;
			}
		}
		else
			goto main_game;
		
		goto Game_3;
	}
	else if(Press == 4)
	{
		build_up();
		
		/*************************/
		
		Sprite comd[5];
		Sprite jewel_x[5];
		Sprite special_x[5];
		Texture comd_0_text;
		comd_0_text.loadFromFile("image/Game4/小花.png");
			
		comd[0].setTexture(comd_0_text);
		comd[0].setScale(Vector2f(0.593f,0.593f));
		
		Texture comd_1_text;
		comd_1_text.loadFromFile("image/Game4/星空.png");
			
		comd[1].setTexture(comd_1_text);
		comd[1].setScale(Vector2f(0.593f,0.593f));
		
		Texture comd_2_text;
		comd_2_text.loadFromFile("image/Game4/BoredApe_假.png");
			
		comd[2].setTexture(comd_2_text);
		comd[2].setScale(Vector2f(0.593f,0.593f));
		
		Texture comd_3_text;
		comd_3_text.loadFromFile("image/Game4/蒙娜麗莎_假.png");
			
		comd[3].setTexture(comd_3_text);
		comd[3].setScale(Vector2f(0.593f,0.593f));
		
		Texture comd_4_text;
		comd_4_text.loadFromFile("image/Game4/富士山_假.png");
			
		comd[4].setTexture(comd_4_text);
		comd[4].setScale(Vector2f(0.593f,0.593f));
		
		Texture jewel_0_text;
		jewel_0_text.loadFromFile("image/Game4/伊麗莎白女王的鑽戒.png");
			
		jewel_x[0].setTexture(jewel_0_text);
		jewel_x[0].setScale(Vector2f(0.593f,0.593f));
		
		Texture jewel_1_text;
		jewel_1_text.loadFromFile("image/Game4/綠寶石紺青之拳_5.png");
			
		jewel_x[1].setTexture(jewel_1_text);
		jewel_x[1].setScale(Vector2f(0.593f,0.593f));
		
		Texture jewel_2_text;
		jewel_2_text.loadFromFile("image/Game4/CHANEL 紅寶石_10.png");
			
		jewel_x[2].setTexture(jewel_2_text);
		jewel_x[2].setScale(Vector2f(0.593f,0.593f));
		
		Texture jewel_3_text;
		jewel_3_text.loadFromFile("image/Game4/量產鑽石_50.png");
			
		jewel_x[3].setTexture(jewel_3_text);
		jewel_x[3].setScale(Vector2f(0.593f,0.593f));
		
		Texture jewel_4_text;
		jewel_4_text.loadFromFile("image/Game4/量產琥珀_100.png");
			
		jewel_x[4].setTexture(jewel_4_text);
		jewel_x[4].setScale(Vector2f(0.593f,0.593f));
		
		Texture special_0_text;
		special_0_text.loadFromFile("image/Game4/青春的味道_1000.png");
			
		special_x[0].setTexture(special_0_text);
		special_x[0].setScale(Vector2f(0.593f,0.593f));
		
		Texture special_1_text;
		special_1_text.loadFromFile("image/Game4/梅西的保時捷.png");
			
		special_x[1].setTexture(special_1_text);
		special_x[1].setScale(Vector2f(0.593f,0.593f));
		
		Texture special_2_text;
		special_2_text.loadFromFile("image/Game4/中世紀城堡.png");
			
		special_x[2].setTexture(special_2_text);
		special_x[2].setScale(Vector2f(0.593f,0.593f));
		
		Texture special_3_text;
		special_3_text.loadFromFile("image/Game4/TaipeiBanana_1000.png");
			
		special_x[3].setTexture(special_3_text);
		special_x[3].setScale(Vector2f(0.593f,0.593f));
		
		Texture special_4_text;
		special_4_text.loadFromFile("image/Game4/Coding101 冠軍獎盃.png");
			
		special_x[4].setTexture(special_4_text);
		special_x[4].setScale(Vector2f(0.593f,0.593f));
		
		/*************************/
		bool open_hint_4 = false;
		int amount = 0;
		bool sel[5] = {0};
		int list[3];
		int seed = 0;
		int chosen = -1;
		int round = 0;//目前回合 
		
		
		/******random list******/
		srand(time(NULL));
		while(amount < 3)
		{
			chosen = rand() % 5;
			
			if(sel[chosen] == false)
			{
				sel[chosen] = true;
				list[amount] = chosen;
				amount++;
			}
				
			seed = rand();
			srand(seed);	
		}
		
		for(int i = 0; i < 3; i++)
			cout << "list[" << i << "]= " << list[i] << "\n";
			
		
		bool close_4 = false;
		while(window.isOpen())
		{
			Event event;
			while(window.pollEvent(event))	
			{
				if(event.type == Event::Closed)
	                window.close();
				else if(event.type == Event::MouseButtonPressed)
				{
					if(event.mouseButton.x >= 261 && event.mouseButton.x <= 386)
					{
						if(event.mouseButton.y >= 426 && event.mouseButton.y <= 460)
						{
							close_4 = true;
						}
					}
					//cout << "(" << event.mouseButton.x << ", " << event.mouseButton.y << ")\n";
				}
			}
			if(close_4 == true)
				break;
			window.clear();
			window.draw(rule_game_4);
			window.display();
		}
		

		
		/********************/
		
		Game_4:
		Texture back_4_choose_1_text;
		back_4_choose_1_text.loadFromFile("image/cp_game4_choose.png");
		
		Sprite back_4_choose_1(back_4_choose_1_text);
		back_4_choose_1.setScale(Vector2f(0.593f,0.593f));
		
		Texture choose_1_item_1_text;
		choose_1_item_1_text.loadFromFile("image/cp_game4_choose_1.png");
		
		Sprite choose_1_item_1(choose_1_item_1_text);
		choose_1_item_1.setScale(Vector2f(0.593f,0.593f));
		
		Texture choose_1_item_2_text;
		choose_1_item_2_text.loadFromFile("image/cp_game4_choose_2.png");
		
		Sprite choose_1_item_2(choose_1_item_2_text);
		choose_1_item_2.setScale(Vector2f(0.593f,0.593f));
		
		Texture choose_1_item_3_text;
		choose_1_item_3_text.loadFromFile("image/cp_game4_choose_3.png");
		
		Sprite choose_1_item_3(choose_1_item_3_text);
		choose_1_item_3.setScale(Vector2f(0.593f,0.593f));
		
		
		
		Vector2f select_1[3] = {Vector2f(407,307), Vector2f(407,378), Vector2f(407,454)};//r = 50
		Vector2f select_2[4] = {Vector2f(472,297), Vector2f(472,362), Vector2f(472,426), Vector2f(472,491)};// r =50
		Vector2f select_3[3] = {Vector2f(480,307), Vector2f(480,381), Vector2f(480,455)};//r = 45
		
		
		/*RectangleShape qq;
		qq.setSize(Vector2f(50,50));
		qq.setPosition(select_2[2]);
		qq.setFillColor(Color::Black);*/
		
		
		
		bool close = false;
		int commodity = -1;
		int auction = -1;
		int marketing = -1;
		
		
		int bx = 0;
		int by = 0;
		int x = 0;
		int y = 0;
		int condition_1 = 0;
		int condition_2 = 0;
		int condition_3 = 0;
		
		while(window.isOpen())
		{
			if(commodity != -1)
			{
				cout << "commodity: " << commodity << "\n";
				break; 
			}
				
			x = Mouse::getPosition(window).x;
			y = Mouse::getPosition(window).y;
			Event event;
			while(window.pollEvent(event))
			{
				
				if(event.type == Event::Closed)
				{
					close = true;
					window.close();
				}
				if(open_hint_4 == 0)
				{
				
					if(event.type == Event::MouseButtonPressed)
					{
						if(event.mouseButton.x >= 45 && event.mouseButton.x <= 96 && event.mouseButton.y >= 55 && event.mouseButton.y <= 106)
						{
							open_hint_4 = true;
						}
						else if(event.mouseButton.x >= 544 && event.mouseButton.x <= 595 && event.mouseButton.y >= 55 && event.mouseButton.y <= 106)
						{
							goto main_game;
						}
						
						bx = event.mouseButton.x;
						by = event.mouseButton.y;
						
						if((bx >= select_1[0].x && bx <= select_1[0].x+50) and (by >= select_1[0].y && by <= select_1[0].y+50))
						{
							commodity = 0;
							break;
						}
						else if((bx >= select_1[1].x && bx <= select_1[1].x+50) and (by >= select_1[1].y && by <= select_1[1].y+50))
						{
							commodity = 1;
							break;
						}
						else if((bx >= select_1[2].x && bx <= select_1[2].x+50) and (by >= select_1[2].y && by <= select_1[2].y+50))
						{
							commodity = 2;
							break;
						}
					}
					
					if((x >= select_1[0].x && x <= select_1[0].x+50) and (y >= select_1[0].y && y <= select_1[0].y+50))
					{
						condition_1 = 1;
					}
					else if((x >= select_1[1].x && x <= select_1[1].x+50) and (y >= select_1[1].y && y <= select_1[1].y+50))
					{
						condition_1 = 2;
					}
					else if((x >= select_1[2].x && x <= select_1[2].x+50) and (y >= select_1[2].y && y <= select_1[2].y+50))
					{
						condition_1 = 3;
					}
					else
						condition_1 = 0;
				}
				else
				{
					if(event.mouseButton.x >= 544 && event.mouseButton.x <= 584 && event.mouseButton.y >= 87 && event.mouseButton.y <= 127)
						open_hint_4 = false;
				}
				
				
			}
			
			window.clear();
			if(open_hint_4 == 0)
			{
				window.draw(back_4_choose_1);
				if(condition_1 != 0)
				{
					if(condition_1 == 1)
						window.draw(choose_1_item_1);
					else if(condition_1 == 2)
						window.draw(choose_1_item_2);
					else if(condition_1 == 3)
						window.draw(choose_1_item_3);	
				}
				
				window.draw(cancel_button);
				window.draw(hint);
			}
			else
			{
				window.draw(hint_4);
				window.draw(cancel_hint_4);
			}
			window.display();
			/*if(open_hint_4 != 0)
			{
				sleep(3);
				open_hint_4 = false;
			}*/
		}
		
		//load_picture(commodity, list[round], 0, window);
		while(window.isOpen())
		{
			Event event;
			while(window.pollEvent(event))
			{
				if(event.type == Event::Closed)
				{
					window.close();
				}	
			}	
			
			window.clear();
			if(commodity == 0)
			{
				window.draw(comd[list[round]]);
			}
			else if(commodity == 1)
			{
				window.draw(jewel_x[list[round]]);
			}
			else if(commodity == 2)
			{
				window.draw(special_x[list[round]]);	
			}
			window.display();
			sleep(3);
			break;
		}
		
		
		Texture back_4_choose_2_text;
		back_4_choose_2_text.loadFromFile("image/cp_game4_choose3.png"); 
		
		Sprite back_4_choose_2(back_4_choose_2_text);
		back_4_choose_2.setScale(Vector2f(0.593f,0.593f));
		
		Texture choose_2_item_1_text;
		choose_2_item_1_text.loadFromFile("image/cp_game4_choose3_1.png");
		
		Sprite choose_2_item_1(choose_2_item_1_text);
		choose_2_item_1.setScale(Vector2f(0.593f,0.593f));
		
		Texture choose_2_item_2_text;
		choose_2_item_2_text.loadFromFile("image/cp_game4_choose3_2.png");
		
		Sprite choose_2_item_2(choose_2_item_2_text);
		choose_2_item_2.setScale(Vector2f(0.593f,0.593f));
		
		Texture choose_2_item_3_text;
		choose_2_item_3_text.loadFromFile("image/cp_game4_choose3_3.png");
		
		Sprite choose_2_item_3(choose_2_item_3_text);
		choose_2_item_3.setScale(Vector2f(0.593f,0.593f));
		
		Texture choose_2_item_4_text;
		choose_2_item_4_text.loadFromFile("image/cp_game4_choose3_4.png");
		
		Sprite choose_2_item_4(choose_2_item_4_text);
		choose_2_item_4.setScale(Vector2f(0.593f,0.593f));
		
		while(window.isOpen())
		{
			if(auction != -1)
			{
				cout << "auction: " << auction << "\n"; 
				break;
			}
				
				
			x = Mouse::getPosition(window).x;
			y = Mouse::getPosition(window).y;
			Event event;
			while(window.pollEvent(event))
			{ 
				if(event.type == Event::Closed)
				{
					close = true;
					window.close();
				}
				if(open_hint_4 == 0)
				{
				
					if(event.type == Event::MouseButtonPressed)
					{
						if(event.mouseButton.x >= 45 && event.mouseButton.x <= 96 && event.mouseButton.y >= 55 && event.mouseButton.y <= 106)
						{
							open_hint_4 = true;
						}
						else if(event.mouseButton.x >= 544 && event.mouseButton.x <= 595 && event.mouseButton.y >= 55 && event.mouseButton.y <= 106)
						{
							goto main_game;
						}
						
						bx = event.mouseButton.x;
						by = event.mouseButton.y;
						
						if((bx >= select_2[0].x && bx <= select_2[0].x+50) and (by >= select_2[0].y && by <= select_2[0].y+50))
						{
							auction = 1;//寫反 
							break;
						}
						else if((bx >= select_2[1].x && bx <= select_2[1].x+50) and (by >= select_2[1].y && by <= select_2[1].y+50))
						{
							auction = 0;//寫反 
							break;
						}
						else if((bx >= select_2[2].x && bx <= select_2[2].x+50) and (by >= select_2[2].y && by <= select_2[2].y+50))
						{
							auction = 2;
							break;
						}
						else if((bx >= select_2[3].x && bx <= select_2[3].x+50) and (by >= select_2[3].y && by <= select_2[3].y+50))
						{
							auction = 3;
							break;
						}
					}
					
					if((x >= select_2[0].x && x <= select_2[0].x+50) and (y >= select_2[0].y && y <= select_2[0].y+50))
					{
						condition_2 = 1;
						
					}
					else if((x >= select_2[1].x && x <= select_2[1].x+50) and (y >= select_2[1].y && y <= select_2[1].y+50))
					{
						condition_2 = 2;	
					}
					else if((x >= select_2[2].x && x <= select_2[2].x+50) and (y >= select_2[2].y && y <= select_2[2].y+50))
					{
						condition_2 = 3;
					}
					else if((x >= select_2[3].x && x <= select_2[3].x+50) and (y >= select_2[3].y && y <= select_2[3].y+50))
					{
						condition_2 = 4;
					}
					else
						condition_2 = 0;
				}
				else
				{
					if(event.mouseButton.x >= 544 && event.mouseButton.x <= 584 && event.mouseButton.y >= 87 && event.mouseButton.y <= 127)
						open_hint_4 = false;
				}
			} 
			
			window.clear();
			if(open_hint_4 == 0)
			{
				window.draw(back_4_choose_2);
				if(condition_2 != 0)
				{
					if(condition_2 == 1)
						window.draw(choose_2_item_1);
					else if(condition_2 == 2)
						window.draw(choose_2_item_2);
					else if(condition_2 == 3)
						window.draw(choose_2_item_3);	
					else if(condition_2 == 4)
						window.draw(choose_2_item_4);
				}
				window.draw(cancel_button);
				window.draw(hint);
			}
			else
			{
				window.draw(hint_4);
				window.draw(cancel_hint_4);
			}
			window.display();
			/*if(open_hint_4 != 0)
			{
				sleep(3);
				open_hint_4 = false;
			}*/
		}
		
	 
		Texture back_4_choose_3_text;
		back_4_choose_3_text.loadFromFile("image/cp_game4_choose2.png");//等等要搬走 
		
		Sprite back_4_choose_3(back_4_choose_3_text);
		back_4_choose_3.setScale(Vector2f(0.593f,0.593f));
		
		Texture choose_3_item_1_text;
		choose_3_item_1_text.loadFromFile("image/cp_game4_choose2_1.png");
		
		Sprite choose_3_item_1(choose_3_item_1_text);
		choose_3_item_1.setScale(Vector2f(0.593f,0.593f));
		
		Texture choose_3_item_2_text;
		choose_3_item_2_text.loadFromFile("image/cp_game4_choose2_2.png");
		
		Sprite choose_3_item_2(choose_3_item_2_text);
		choose_3_item_2.setScale(Vector2f(0.593f,0.593f));
		
		Texture choose_3_item_3_text;
		choose_3_item_3_text.loadFromFile("image/cp_game4_choose2_3.png");
		
		Sprite choose_3_item_3(choose_3_item_3_text);
		choose_3_item_3.setScale(Vector2f(0.593f,0.593f));
		
		while(window.isOpen())
		{
			if(marketing != -1)
			{
				cout << "marketing: " << marketing << "\n";
				break;	
			}
				
			x = Mouse::getPosition(window).x;
			y = Mouse::getPosition(window).y;
			Event event;
			while(window.pollEvent(event))
			{ 
				if(event.type == Event::Closed)
				{
					close = true;
					window.close();
				}
				if(open_hint_4 == 0)
				{
					
					if(event.type == Event::MouseButtonPressed)
					{
						if(event.mouseButton.x >= 45 && event.mouseButton.x <= 96 && event.mouseButton.y >= 55 && event.mouseButton.y <= 106)
						{
							open_hint_4 = true;
						}
						else if(event.mouseButton.x >= 544 && event.mouseButton.x <= 595 && event.mouseButton.y >= 55 && event.mouseButton.y <= 106)
						{
							goto main_game;
						}
						
						bx = event.mouseButton.x;
						by = event.mouseButton.y;
						
						if((bx >= select_3[0].x && bx <= select_3[0].x+50) and (by >= select_3[0].y && by <= select_3[0].y+50))
						{
							marketing = 0;
							break;
						}
						else if((bx >= select_3[1].x && bx <= select_3[1].x+50) and (by >= select_3[1].y && by <= select_3[1].y+50))
						{
							marketing = 1;
							break;
						}
						else if((bx >= select_3[2].x && bx <= select_3[2].x+50) and (by >= select_3[2].y && by <= select_3[2].y+50))
						{
							marketing = 2;
							break;
						}
					}
					
					if((x >= select_3[0].x && x <= select_3[0].x+50) and (y >= select_3[0].y && y <= select_3[0].y+50))
					{
						condition_3 = 1;
					}
					else if((x >= select_3[1].x && x <= select_3[1].x+50) and (y >= select_3[1].y && y <= select_3[1].y+50))
					{
						condition_3 = 2;
					}
					else if((x >= select_3[2].x && x <= select_3[2].x+50) and (y >= select_3[2].y && y <= select_3[2].y+50))
					{
						condition_3 = 3;
					}
					else
						condition_3 = 0;
				}
				else
				{
					if(event.mouseButton.x >= 544 && event.mouseButton.x <= 584 && event.mouseButton.y >= 87 && event.mouseButton.y <= 127)
						open_hint_4 = false;
				}
			} 
			
			window.clear();
			if(open_hint_4 == 0)
			{
				window.draw(back_4_choose_3);
				if(condition_3 != 0)
				{
					if(condition_3 == 1)
						window.draw(choose_3_item_1);
					else if(condition_3 == 2)
						window.draw(choose_3_item_2);
					else if(condition_3 == 3)
						window.draw(choose_3_item_3);	
				}
				window.draw(cancel_button);
				window.draw(hint);
			}
			else
			{
				window.draw(hint_4);
				window.draw(cancel_hint_4);
			}
			window.display();
			/*if(open_hint_4 != 0)
			{
				sleep(3);
				open_hint_4 = false;
			}*/
			
		}
		
		
		
		Vector2f set_pos[5] = {Vector2f(130,170), Vector2f(125,440), Vector2f(270,440), Vector2f(415,440), Vector2f(462.f, 340.f)};
		
		bool appear[3] = {0};
		int list_loc[3];
		int index = -1;
		int all = 0;
		int seed_loc = 0;
		srand(time(NULL));
		
		while(all < 3)
		{
			index = rand() % 3;
			if(appear[index] == false)
			{
				appear[index] = true;
				list_loc[all] = index;
				all++;
			}
			seed_loc = rand();
			srand(seed_loc);
		}
		
		
		
		int now = 0;
		int deal_price = 0;
		if(commodity == 0)
			deal_price = arts[list[round]][marketing][auction];	
		else if(commodity == 1)
			deal_price = jewel[list[round]][marketing][auction];	
		else if(commodity == 2)
			deal_price = special[list[round]][marketing][auction];
			
		cout << "deal_price: " << deal_price << "\n";
		
		Text end_price;
		end_price.setFont(font);
		end_price.setFillColor(Color::Black);
		end_price.setCharacterSize(30);
		end_price.setPosition(set_pos[4]); 
		end_price.setString(to_string(deal_price));	
		
		Text price[3];
		for(int i = 0; i < 3; i++)
		{
			price[i].setFont(font);
			price[i].setFillColor(Color::Black);
			price[i].setCharacterSize(30);
			price[i].setPosition(set_pos[i+1]); 
			
			
			if(list_loc[i] == 0)
			{
				price[i].setString(to_string((int)(0.3 * deal_price)));
				if((0.3 * deal_price) >= 1000)
					price[i].setPosition(Vector2f(set_pos[i+1].x - 10, set_pos[i+1].y)); 
				else if((0.3 * deal_price) < 100)
					price[i].setPosition(Vector2f(set_pos[i+1].x + 10, set_pos[i+1].y)); 
			}
			else if(list_loc[i] == 1)
			{
				price[i].setString(to_string((int)(0.6 * deal_price)));
				if((0.6 * deal_price) >= 1000)
					price[i].setPosition(Vector2f(set_pos[i+1].x - 10, set_pos[i+1].y)); 
				if((0.6 * deal_price) < 100)
					price[i].setPosition(Vector2f(set_pos[i+1].x + 10, set_pos[i+1].y)); 
			}
			else if(list_loc[i] == 2)
			{
				price[i].setString(to_string(deal_price));
				if((deal_price) >= 1000)
					price[i].setPosition(Vector2f(set_pos[i+1].x - 10, set_pos[i+1].y)); 
				else if(deal_price < 100)
					price[i].setPosition(Vector2f(set_pos[i+1].x + 10, set_pos[i+1].y)); 
			}
		}
		
		Text goal_price;
		goal_price.setFont(font);
		goal_price.setFillColor(Color::Black);
		goal_price.setCharacterSize(30);
		goal_price.setPosition(set_pos[0]); 
		goal_price.setString(to_string(goals[commodity][list[round]]));
		
		Texture back_4_text;
		back_4_text.loadFromFile("image/cp_game4_底圖.png");
		
		Sprite back_4(back_4_text);
		back_4.setScale(Vector2f(0.593f,0.593f));
		
		Sprite com;
		com = load_picture(commodity, list[round], 1, window);
		com.setScale(Vector2f(0.1f, 0.1f));
		com.setPosition(Vector2f(100,200));
		
		if(deal_price >= goals[commodity][list[round]])
			auction_score++;
		
		while(window.isOpen())
		{
			Event event;
			while(window.pollEvent(event))
			{
				if(event.type == Event::Closed)
				{
					close = true;
					window.close();
				}

					
			}
			
			window.clear();
			window.draw(back_4);
			if(commodity == 0)
			{
				comd[list[round]].setScale(Vector2f(0.1,0.1));
				comd[list[round]].setPosition(Vector2f(150, 225));
				window.draw(comd[list[round]]);
			}
			else if(commodity == 1)
			{
				jewel_x[list[round]].setScale(Vector2f(0.1,0.1));
				jewel_x[list[round]].setPosition(Vector2f(150, 225));
				window.draw(jewel_x[list[round]]);
			}
			else if(commodity == 2)
			{
				special_x[list[round]].setScale(Vector2f(0.1,0.1));
				special_x[list[round]].setPosition(Vector2f(150, 225));
				window.draw(special_x[list[round]]);
			}
			window.draw(goal_price);
			if(now != 0)
			{
				if(now >= 1)
					window.draw(price[0]);
				if(now >= 2)
					window.draw(price[1]);
				if(now >= 3)
					window.draw(price[2]);
				if(now >= 4)
					window.draw(end_price);
			}
			window.display();
			sleep(1);
			now++;
			if(now > 4)
			{
				round++;
				break;
			}
		}
		
		//Game4_end(commodity, number, price, goal_price, end_price, now, round, close, window);
		
		cout << "分數: " << auction_score << "\n"; 
		cout << "CLOSE: " << close << "\n";
		if(close == false)
		{	
			
			if(auction_score < 2 && round < 3)
				goto Game_4;
			if(auction_score == 2)
				end_image(true, window);
			else if(round >= 3)
				end_image(false, window);
		}
		goto main_game;
		
	}
	
}
