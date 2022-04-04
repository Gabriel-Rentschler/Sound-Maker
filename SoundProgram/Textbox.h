
#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>

#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27

class Textbox {
public:
	Textbox() { }

	Textbox(int size, sf::Color color, bool sel) {
		textbox.setCharacterSize(size);
		textbox.setFillColor(color);
		isSelected = sel;
		if (sel) {
			textbox.setString("_");
		}
		else {
			textbox.setString("");
		}
	}

	Textbox(int size, sf::Color color, bool sel, std::string initialValue) {
		textbox.setCharacterSize(size);
		textbox.setFillColor(color);
		isSelected = sel;
		if (sel) {
			textbox.setString(initialValue + "_");
		}
		else {
			textbox.setString(initialValue);
		}

		text.str() += initialValue;
	}

	void setFont(sf::Font &font) {
		textbox.setFont(font);
	}

	void setPosition(sf::Vector2f pos) {
		textbox.setPosition(pos);
		shape.setPosition(pos);
	}

	void setBackground(sf::Vector2f size, sf::Color fillColor) {
		shape.setSize(size);
		shape.setFillColor(fillColor);
	}

	sf::Vector2f getPosition() {
		return textbox.getPosition();
	}

	void setLimit(bool trueorfalse) {
		hasLimit = trueorfalse;
	}

	void setLimit(bool trueorfalse, int lim) {
		hasLimit = trueorfalse;
		limit = lim - 1;
	}

	void setSelected(bool sel) {
		isSelected = sel;
		if (!sel) {
			std::string t = text.str();
			std::string newT = "";
			for (int i = 0; i < t.length(); i++) {
				newT += t[i];
			}
			textbox.setString(newT);
		} else {
			textbox.setString(text.str() + "_");
		}
	}

	bool getSelected() {
		return isSelected;
	}

	std::string getText() {
		return text.str();
	}

	void drawTo(sf::RenderWindow& window) {
		window.draw(shape);
		window.draw(textbox);
	}

	void typedOn(sf::Event input) {
		if (isSelected) {
			int charTyped = input.text.unicode;
			if (charTyped < 128) {
				if (hasLimit) {
					if (text.str().length() <= limit) {
						inputLogic(charTyped);
					}
					else if (text.str().length() > limit && charTyped == DELETE_KEY) {
						deleteLastChar();
					}
				}
				else {
					inputLogic(charTyped);
				}
			}
		}
	}

	void mouseSelect(sf::RenderWindow &window) {
		
		sf::Vector2i pos;
		pos.x = textbox.getPosition().x;
		pos.y = textbox.getPosition().y;

		std::cout << sf::Mouse::getPosition(window).x;

		if (sf::Mouse::getPosition(window).x < pos.x + shape.getSize().x && sf::Mouse::getPosition(window).x > pos.x &&
			sf::Mouse::getPosition(window).y < pos.y + shape.getSize().y && sf::Mouse::getPosition(window).y > pos.y) {
			setSelected(true);
		} else {
			setSelected(false);
		}
		
	}
private:
	sf::Text textbox;
	std::ostringstream text;
	sf::RectangleShape shape;
	bool isSelected = false;
	bool hasLimit = false;
	int limit;

	void inputLogic(int charTyped) {
		if (charTyped != DELETE_KEY && charTyped != ENTER_KEY && charTyped != ESCAPE_KEY) {
			text << static_cast<char>(charTyped);
		}
		else if (charTyped == DELETE_KEY) {
			if (text.str().length() > 0) {
				deleteLastChar();
			}
		}
		textbox.setString(text.str() + "_");
	}

	void deleteLastChar() {
		std::string t = text.str();
		std::string newT = "";
		for (int i = 0; i < t.length() - 1; i++) {
			newT += t[i];
		}
		text.str("");
		text << newT;

		textbox.setString(text.str());
	}
};