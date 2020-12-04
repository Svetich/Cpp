#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdio>
#include <stdio.h>
#include "String.hpp"
#include "Text.hpp"


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
    char* buf = new char[len + 1];

    fread(buf, sizeof(char), len, code);
    fclose(code);

    String visibleText = new char[len + 1];   
    String buffer = buf;

    sf::Font font;    
    font.loadFromFile("arial.ttf");

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Hackertyper");
    
    while (window.isOpen())
    {
        sf::Event evnt;
        while (window.pollEvent(evnt))
        {
            switch (evnt.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                if (evnt.key.code == sf::Keyboard::Space)
                    window.close();
                break;
            }
        }
        window.clear();

        if (evnt.type == sf::Event::KeyReleased)
        {   
            visibleText = visibleText + String(buf[count]);
            visibleText = visibleText + bu


            if (visibleText.countChar('\n'))
            {

            }
            count += 2;

            String newText = buf[count] + buf[count + 1]; 

            visibleText = visibleText + newText;  

            

            sf::Text text;

            text.setFont(font);
            text.setString(visibleText.str);
            text.setCharacterSize(15); 
            text.setFillColor(sf::Color::Green);

            window.draw(text);
            
            window.display();    
        }
        
        
    }
    return 0;



   


   //len = FileLen("hackercode.py")
   
    //char str1[] = "dsfsfs";
    // char str2[] = "ferffg";
    
    // String string1 = {str1};
    
    // String string2 = {str2};
    // String new_str = string1 + string2;
    // std::cout << new_str.str << std::endl;

    // return 0;

}