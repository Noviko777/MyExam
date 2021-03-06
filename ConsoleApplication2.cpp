#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "map.h"

using namespace sf;
using namespace std;



template<class T>
const T& clamp(const T& x, const T& upper, const T& lower) {
	return min(upper, max(x, lower));
}

class Snow
{
public:
	
	CircleShape circle;
	float speed = 5.0f;
	Clock clock;

	Snow()
	{
		circle.setRadius(5);
		circle.setFillColor(Color::White);
		clock.restart();

	}

	void GoClock()
	{
		clock.restart();
	}
	
	void Move()
	{
		circle.move(0, speed);
		float a = clamp<float>(circle.getFillColor().a - 2, 255, 0);
		circle.setFillColor(Color(circle.getFillColor().r, circle.getFillColor().g, circle.getFillColor().b, a));
	}



};

class BackGround
{
public:

	Texture texture_background, texture_snow, texture_igloo, texture_tree;
	Sprite sprite_background, sprite_snow, sprite_igloo;
	Sprite tree;
	vector<Snow*> snows;
	Clock clock;

	BackGround()
	{
		texture_background.loadFromFile("PNG/BG.png");
		texture_snow.loadFromFile("PNG/Snow  x mas Moon_background 2 .png");
		texture_igloo.loadFromFile("PNG/Igloo.png");
		texture_tree.loadFromFile("PNG/Tree_1.png");
		sprite_igloo.setTexture(texture_igloo);
		sprite_background.setTexture(texture_background);
		sprite_snow.setTexture(texture_snow);
		tree.setTexture(texture_tree);
		sprite_snow.setPosition(0, 550);
		sprite_igloo.setPosition(640, 400);
		tree.setPosition(100, 400);
		clock.restart();
	}
	
	void GoSnow()
	{
		if (clock.getElapsedTime().asMilliseconds() >= 50)
		{
			snows.push_back(new Snow());
			snows[snows.size() - 1]->circle.setPosition(rand() % 1100, -5);
			snows[snows.size() - 1]->GoClock();
			clock.restart();
		}
		for (auto x : snows)
		{
			x->Move();
			if (x->clock.getElapsedTime().asMilliseconds() >= 4000)
			{
				snows.erase(snows.begin());
			}
		}

	
	}


};


class SnowMan
{
public:

	Texture texture_snowman, texure_palk1, texure_palk2;
	Sprite sprite_SnowMan, sprite_palkLeft, sprite_palkRight;
	float speed = 1.0f, SpeedJump = 2.5f, jump = 0;
	bool Up = false, Up2 = false, isJump = false;
	Clock clock;

	SnowMan()
	{

		texture_snowman.loadFromFile("PNG/SnowMan.png");
		texure_palk1.loadFromFile("PNG/palk.png");
		texure_palk2.loadFromFile("PNG/palk2.png");
		sprite_palkLeft.setTexture(texure_palk1);
		sprite_palkRight.setTexture(texure_palk2);
		sprite_palkLeft.setScale(0.5f, 0.5f);
		sprite_palkRight.setScale(0.5f, 0.5f);
		sprite_SnowMan.setTexture(texture_snowman);
	


		sprite_SnowMan.setPosition(550, 400);
		sprite_SnowMan.setOrigin(96.5f, 105);
		sprite_palkLeft.setPosition(sprite_SnowMan.getPosition().x - 15, sprite_SnowMan.getPosition().y - 15);
		sprite_palkRight.setPosition(sprite_SnowMan.getPosition().x + 20, sprite_SnowMan.getPosition().y - 15);
		sprite_palkLeft.setOrigin(112, 0);
	}

	void Jump()
	{
		sprite_palkLeft.setPosition(sprite_SnowMan.getPosition().x - 15, sprite_SnowMan.getPosition().y - 15);
		sprite_palkRight.setPosition(sprite_SnowMan.getPosition().x + 20, sprite_SnowMan.getPosition().y - 15);
		if (sprite_palkRight.getRotation() >= 277 || sprite_palkRight.getRotation() == 0)
		{
			if(Up == false)
			sprite_palkRight.rotate(-speed);
		}
		else
		{
			Up = true;
		}
		if (sprite_palkLeft.getRotation() <= 88 || sprite_palkRight.getRotation() == 0)
		{
			if(Up2 == false)
			sprite_palkLeft.rotate(speed);
		}
		else
		{
			Up2 = true;
		}
		if (Up == true)
		{
			if(sprite_palkRight.getRotation() != 0)
			sprite_palkRight.rotate(speed);
			else			Up = false;

		}
		if (Up2 == true)
		{
			if (sprite_palkLeft.getRotation() != 0)
				sprite_palkLeft.rotate(-speed);
			else			Up2 = false;

		}

		if (sprite_SnowMan.getPosition().y == 500)
		{
			isJump = true;
			SpeedJump = 2.5f;
		}
		if (sprite_SnowMan.getPosition().y == 300)
		{
			isJump = false;
			SpeedJump = 2.5f;
			clock.restart();
		}
		if (isJump == true && clock.getElapsedTime().asMilliseconds() >= 1500)
		{
			SpeedJump += 0.7f;
			jump = sprite_SnowMan.getPosition().y - SpeedJump;
			sprite_SnowMan.setPosition(sprite_SnowMan.getPosition().x, clamp<float>(jump, 500, 300));
		}
		else
		{

			SpeedJump += 0.3f;
	
			jump = sprite_SnowMan.getPosition().y + SpeedJump;
			sprite_SnowMan.setPosition(sprite_SnowMan.getPosition().x, clamp<float>(jump, 500, 300));

		}

		if(Keyboard::isKeyPressed(Keyboard::Space)) cout << sprite_palkLeft.getRotation() << endl;

		//cout << sprite_palkRight.getRotation() << endl;

	}


};


int main()
{
	sf::RenderWindow window(sf::VideoMode(1100, 700), "Example");

	window.setFramerateLimit(30);

	BackGround back;
	SnowMan snowMan;


	while (window.isOpen())
	{
		sf::Event event;


		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{

				window.close();

			}


		}

		snowMan.Jump();
		back.GoSnow();

		window.clear();


		window.draw(back.sprite_background);
		window.draw(snowMan.sprite_palkLeft);
		window.draw(snowMan.sprite_palkRight);
		window.draw(snowMan.sprite_SnowMan);
		window.draw(back.sprite_igloo);
		window.draw(back.tree);
		window.draw(back.sprite_snow);
		
		for (auto x : back.snows)
		{
			window.draw(x->circle);
		}

		window.display();




	}
	system("pause");
}