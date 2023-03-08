#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include<iostream>
#include<unistd.h>
#include<ctime>
#include<cstdlib>

using namespace std;
using namespace sf;

int end_image(bool result, RenderWindow &window)
{
	Texture win_image_ori;
	win_image_ori.loadFromFile("image/cp_win.png");
	
	Texture lose_image_ori;
	lose_image_ori.loadFromFile("image/cp_lose.png");
	
	Sprite win_image(win_image_ori);
	win_image.setScale(Vector2f(0.593f,0.593f));
	
	Sprite lose_image(lose_image_ori);
	lose_image.setScale(Vector2f(0.593f,0.593f));
	
	while(window.isOpen()) 
	{
		if(result == 0)// we lose
		{
			window.clear();
			window.draw(lose_image);
			window.display();
			sleep(3);	
		}
		else if(result == 1)// we win 
		{
			window.clear();
			window.draw(win_image);
			window.display();
			sleep(3);
		}
		
		break;
	}
}


