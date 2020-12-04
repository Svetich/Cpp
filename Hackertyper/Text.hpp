#include <SFML/Graphics.hpp>
#include "String.hpp"

class Text
{
    public:
        sf::Text text;
        sf::Font font;
        sf::Color color;
        
        int size;

    public:
        Text(sf::Text text, sf::Font font, sf::Color color = sf::Color::Green, int size = 15)
        {
            this->text = text;
            this->font = font;
            this->color = color;
            this->size = size;
        }    
    
    void printText(String visibleText; sf::RenderWindow *window)
    {
        text.setFont(font);
        text.setString(visibleText);
        text.setCharacterSize(size); 
        text.setFillColor(color);

        window->draw(text);
    }
};