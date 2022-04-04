#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <iostream>
#include "Textbox.h"
#include "Oscillator.h"

using namespace std;

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Sound Maker");

    sf::Font roboto;
    roboto.loadFromFile("fonts/Roboto-Black.ttf");
    Textbox textbox1(15, sf::Color::White, false, "100");
    textbox1.setFont(roboto);
    textbox1.setPosition({ 100, 100 });
    textbox1.setBackground({ 100, 20 }, sf::Color::Blue);
    textbox1.setLimit(true, 4);

    Oscillator oscillator(100, 0.8);

    sf::Clock clock;

    window.clear();

    while (window.isOpen()) {
        sf::Event event;

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            textbox1.mouseSelect(window);
            if (!textbox1.getSelected()) {
                double freq = atof(textbox1.getText().c_str());
                oscillator.setFrequency(freq);
            }
        }
        if (clock.getElapsedTime().asSeconds() > 1) {
            oscillator.stop();
            clock.restart().asSeconds();
            oscillator.play();
        }
        

        while (window.pollEvent(event)) {
            switch (event.type) {

            case sf::Event::Closed:
                window.close();

            case sf::Event::TextEntered:
                textbox1.typedOn(event);
            }
        }

        window.clear();
        textbox1.drawTo(window);
        window.display();
    }

    return 0;
}