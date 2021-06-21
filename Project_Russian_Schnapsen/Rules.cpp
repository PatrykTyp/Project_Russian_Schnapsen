#include "Rules.h"



Rules::Rules() {
	texture.loadFromFile("ex/image/zasady.png");

	view.setSize(sf::Vector2f(1200.0f, 800.0f));
	view.setCenter(sf::Vector2f(600.0f, 400.0f));

	bground.setTexture(texture);

	font.loadFromFile("ex/font/sansation.ttf");
	text.setFont(font);
	text.setFillColor(sf::Color::Black);

	outRules();
}

Rules::~Rules() {}
void Rules::scrollUp() {
	if (view.getCenter().y > 400.0f)
		view.move(sf::Vector2f(0, -25.0f));
}

void Rules::scrollDown() {
	if (view.getCenter().y < 1200.0f)
		view.move(sf::Vector2f(0, 25.0f));
}

void Rules::scrollReset() {
	float tmp = -(view.getCenter().y - 400.0f);
	view.move(sf::Vector2f(0, tmp));
}

void Rules::draw(sf::RenderWindow& window) {
	window.setView(view);
	window.draw(bground);
	window.draw(text);
}
void Rules::outRules() {
	std::string line;
	std::ifstream rulesFile;
	std::string rulesText;
	rulesFile.open("ex/rules/zasady.txt");
	if (rulesFile) {
		while (std::getline(rulesFile, line)) {
			rulesText += line + "\n";
		}
	}
	else {
		std::cout << "Nie udalo sie otworzyc pliku";
	}
	text.setString(rulesText);
	text.setCharacterSize(25);
	text.setPosition(15.0f, 15.0f);
}