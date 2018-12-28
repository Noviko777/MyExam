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



int main()
{
	sf::RenderWindow window(sf::VideoMode(1100, 700), "Example");

	window.setFramerateLimit(30);



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



		window.clear();

		//for (int i = 0; i < HEIGHT_MAP; i++)
		//{
		//	for (int j = 0; j < WIDTH_MAP; j++)
		//	{
		//		if (i == 0) background.MyBack.setPosition(j * 256, y * 256.0f);
		//		else background.MyBack.setPosition(j * 256, ((float)((float)i * y) * 256.0f));
		//		window.draw(background.MyBack);
		//		if (TileMap[i][j] == '2')
		//		{
		//
		//			if (i == 0)
		//			{
		//				background.meteors[countMeteors]->Meteor1.setPosition(j * 256, y * 256.0f);
		//				background.meteors[countMeteors]->text.setPosition(j * 256, y * 256.0f);
		//			}
		//			else
		//			{
		//				background.meteors[countMeteors]->Meteor1.setPosition(j * 256, ((float)((float)i * y) * 256.0f));
		//				background.meteors[countMeteors]->text.setPosition(j * 256, ((float)((float)i * y) * 256.0f));
		//			}
		//				
		//			background.meteors[countMeteors]->Meteor1.setRotation(background.anglyMeteors[i + j]);
		//			window.draw(background.meteors[countMeteors]->Meteor1);
		//			window.draw(background.meteors[countMeteors]->text);
		//			background.meteorsRect.push_back(background.meteors[countMeteors]->Meteor1.getGlobalBounds());
		//			countMeteors++;
		//		}
		//	}
		//}






		window.display();




	}
	system("pause");
}