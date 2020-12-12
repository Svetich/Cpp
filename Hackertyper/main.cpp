#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdio>
#include <stdio.h>
#include "String.hpp"


int fileLen(FILE* file)
{
    fseek(file, 0, SEEK_END);
    int lenf = ftell(file);
    fseek(file, 0, SEEK_SET);
    return lenf;
}



int main()
{          
    const int WINDOW_WIDTH = 1000;
    const int WINDOW_HEIGHT = 500;

    int count = 0;
    int quantityN = 0;

    FILE * code = fopen("hackercode.py", "r");

    int len = fileLen(code);   
    char* buffer = new char[len + 1];

    fread(buffer, sizeof(char), len, code);
    fclose(code);

    String visibleText = new char[len + 1];

    String buf = buffer;    

    sf::Font font;    
    font.loadFromFile("arial.ttf");

    sf::Text visText;
    visText.setFont(font);
    visText.setCharacterSize(15); 
    visText.setFillColor(sf::Color::Green);


    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Hackertyper");

    while (window.isOpen())
    {
        sf::Event evnt;
        while (window.pollEvent(evnt))
        {
            if (evnt.type == sf::Event::Closed)
			{
				window.close();
			}
			if (evnt.type == sf::Event::KeyReleased)
			{  
            char* newSymbol;
            newSymbol[0] = buffer[count];
            newSymbol[1] = buffer[count + 1];

            std::cout<<newSymbol<<std::endl;

            if (visibleText.countChar('\n'))
            {

            }
            count += 2;

            String newText = newSymbol; 

            visibleText = visibleText + newText;
            }  
        }
            visText.setString(visibleText.str);
            
            window.clear();
            window.draw(visText);
            window.display();    
        


    }
    return 0;
}