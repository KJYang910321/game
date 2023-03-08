#include<iostream> 
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>

using namespace sf;



Sprite load_picture(int commodity, int number, bool time, RenderWindow &window)
{
	Sprite comd[5];
	Sprite jewel_x[5];
	Sprite special_x[5];

	Sprite none;
	Texture comd_0_text;
	comd_0_text.loadFromFile("image/Game4/�p��.png");
		
	comd[0].setTexture(comd_0_text);
	comd[0].setScale(Vector2f(0.593f,0.593f));
	
	Texture comd_1_text;
	comd_1_text.loadFromFile("image/Game4/�P��.png");
		
	comd[1].setTexture(comd_1_text);
	comd[1].setScale(Vector2f(0.593f,0.593f));
	
	Texture comd_2_text;
	comd_2_text.loadFromFile("image/Game4/BoredApe_��.png");
		
	comd[2].setTexture(comd_2_text);
	comd[2].setScale(Vector2f(0.593f,0.593f));
	
	Texture comd_3_text;
	comd_3_text.loadFromFile("image/Game4/�X�R�R��_��.png");
		
	comd[3].setTexture(comd_3_text);
	comd[3].setScale(Vector2f(0.593f,0.593f));
	
	Texture comd_4_text;
	comd_4_text.loadFromFile("image/Game4/�I�h�s_��.png");
		
	comd[4].setTexture(comd_4_text);
	comd[4].setScale(Vector2f(0.593f,0.593f));
	
	Texture jewel_0_text;
	jewel_0_text.loadFromFile("image/Game4/���R��դk�����p��.png");
		
	jewel_x[0].setTexture(jewel_0_text);
	jewel_x[0].setScale(Vector2f(0.593f,0.593f));
	
	Texture jewel_1_text;
	jewel_1_text.loadFromFile("image/Game4/���_����C����_5.png");
		
	jewel_x[1].setTexture(jewel_1_text);
	jewel_x[1].setScale(Vector2f(0.593f,0.593f));
	
	Texture jewel_2_text;
	jewel_2_text.loadFromFile("image/Game4/CHANEL ���_��_10.png");
		
	jewel_x[2].setTexture(jewel_2_text);
	jewel_x[2].setScale(Vector2f(0.593f,0.593f));
	
	Texture jewel_3_text;
	jewel_3_text.loadFromFile("image/Game4/�q���p��_50.png");
		
	jewel_x[3].setTexture(jewel_3_text);
	jewel_x[3].setScale(Vector2f(0.593f,0.593f));
	
	Texture jewel_4_text;
	jewel_4_text.loadFromFile("image/Game4/�q���[��_100.png");
		
	jewel_x[4].setTexture(jewel_4_text);
	jewel_x[4].setScale(Vector2f(0.593f,0.593f));
	
	Texture special_0_text;
	special_0_text.loadFromFile("image/Game4/�C�K�����D_1000.png");
		
	special_x[0].setTexture(special_0_text);
	special_x[0].setScale(Vector2f(0.593f,0.593f));
	
	Texture special_1_text;
	special_1_text.loadFromFile("image/Game4/���誺�O�ɱ�.png");
		
	special_x[1].setTexture(special_1_text);
	special_x[1].setScale(Vector2f(0.593f,0.593f));
	
	Texture special_2_text;
	special_2_text.loadFromFile("image/Game4/���@������.png");
		
	special_x[2].setTexture(special_2_text);
	special_x[2].setScale(Vector2f(0.593f,0.593f));
	
	Texture special_3_text;
	special_3_text.loadFromFile("image/Game4/TaipeiBanana_1000.png");
		
	special_x[3].setTexture(special_3_text);
	special_x[3].setScale(Vector2f(0.593f,0.593f));
	
	Texture special_4_text;
	special_4_text.loadFromFile("image/Game4/Coding101 �a�x����.png");
		
	special_x[4].setTexture(special_4_text);
	special_x[4].setScale(Vector2f(0.593f,0.593f));
	
	if(time == 0)
	{
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
			cout << "NUMBER: " << number << "\n";
			if(commodity == 0)
			{
				window.draw(comd[number]);
			}
			else if(commodity == 1)
			{
				window.draw(jewel_x[number]);
			}
			else if(commodity == 2)
			{
				window.draw(special_x[number]);	
			}
			window.display();
			sleep(3);
			break;
		}
	}
	else
	{
		if(commodity == 0)
		{
			return comd[number];
		}
		else if(commodity == 1)
		{
			return jewel_x[number];
		}
		else if(commodity == 2)
		{
			return special_x[number];	
		}
	}
}
