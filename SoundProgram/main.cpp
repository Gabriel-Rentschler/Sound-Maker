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

    sf::Color bgcolor(41, 150, 38, 191);

    Textbox inputFreqOscillator1(15, sf::Color::White, false, "0");
    Textbox inputAmpOscillator1(15, sf::Color::White, false, "0");

    #pragma region textboxSetup
    inputFreqOscillator1.setFont(roboto);
    inputFreqOscillator1.setPosition({ 100, 100 });
    inputFreqOscillator1.setBackground({ 100, 20 }, bgcolor);
    inputFreqOscillator1.setLimit(true, 4);

    inputAmpOscillator1.setFont(roboto);
    inputAmpOscillator1.setPosition({ 100, 150 });
    inputAmpOscillator1.setBackground({ 100, 20 }, bgcolor);
    inputAmpOscillator1.setLimit(true, 4);
    #pragma endregion

    Oscillator oscillator(100, 0.8);

    sf::Clock clock;

    window.clear();

    while (window.isOpen()) {
        sf::Event event;

        #pragma region textboxSelect
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            inputFreqOscillator1.mouseSelect(window);
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            inputAmpOscillator1.mouseSelect(window);
        }
        if (inputFreqOscillator1.getSelected()) {
            double freq = atof(inputFreqOscillator1.getText().c_str());
            oscillator.setFrequency(freq);
        }
        if (inputAmpOscillator1.getSelected()) {
            double amp = atof(inputAmpOscillator1.getText().c_str());
            oscillator.setAmplitude(amp);
        }
        #pragma endregion

        if (clock.getElapsedTime().asMicroseconds() > 1000000) {
            oscillator.stop();
            clock.restart().asMicroseconds();
            oscillator.play();
        }
        

        while (window.pollEvent(event)) {
            switch (event.type) {

            case sf::Event::Closed:
                window.close();

            case sf::Event::TextEntered:
                inputFreqOscillator1.typedOn(event);
                inputAmpOscillator1.typedOn(event);
            case sf::Event::KeyPressed:
                inputFreqOscillator1.arrowControl(event);
                inputAmpOscillator1.arrowControl(event);
            }
        }

        window.clear();
        #pragma region drawObjects
        inputFreqOscillator1.drawTo(window);
        inputAmpOscillator1.drawTo(window);
        #pragma endregion
        window.display();
    }

    return 0;
}