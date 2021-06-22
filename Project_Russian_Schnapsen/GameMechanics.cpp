#include "GameMechanics.h"

std::pair<bool, bool> GameMechanics::whoFirst = { true, true };
bool GameMechanics::throwCard = true;
int GameMechanics::who = 0;
float GameMechanics::a = 600.0f;
float GameMechanics::b = 720.0f;
int GameMechanics::bidder = 0;



Card* GameMechanics::previousCardP1Ptr = nullptr;
Card* GameMechanics::previousCardP2Ptr = nullptr;
Card* GameMechanics::previousCardP3Ptr = nullptr;


void GameMechanics::sendValues(Card& playerCard, Card& botCard) {
	Card cardP2, cardP3;

	if (whoFirst.first == true && whoFirst.second == true) {
		cardP2 = sendValuesBot(playerCard, Players::player2, a);
		cardP3 = sendValuesBot(playerCard, Players::player3, b);

		checkGame(playerCard, cardP2, cardP3);
	}
	else if (whoFirst.first == false && whoFirst.second == true) {
		cardP3 = sendValuesBot(botCard, Players::player3, b);

		checkGame(playerCard, botCard, cardP3);
	}
	else if (whoFirst.first == true && whoFirst.second == false) {
		cardP2 = sendValuesBot(botCard, Players::player2, a);

		checkGame(playerCard, cardP2, botCard);
	}
	previousCardP1Ptr = &playerCard;
	Points::pointsTextP1.setString(std::to_string(Points::pointsP1));
	Points::pointsTextP2.setString(std::to_string(Points::pointsP2));
	Points::pointsTextP3.setString(std::to_string(Points::pointsP3));

}

Card GameMechanics::sendValuesBot(Card botCard[], float position) {
	int indexOfCard{}, value{};
	
	if (value == 0 && indexOfCard == 0) {
		for (int i = 0; i < 8; i++) {
			if (botCard[i].use == false) {
				indexOfCard = i;
				break;
			}
		}
	}
	
	botCard[indexOfCard].use = true;
	if (position == 720.0f) {
		botCard[indexOfCard].cardImg.setRotation(00.0f);
	}
	botCard[indexOfCard].cardImg.setPosition(sf::Vector2f(position, 400.0f));
	Move::turnFront(botCard[indexOfCard]);
	getCardAddress(botCard[indexOfCard]);

	return botCard[indexOfCard];
}

Card GameMechanics::sendValuesBot(Card& playerCard, Card botCard[], float position) {
	int indexOfCard{}, value{};

	for (int i = 0; i < 8; i++) {
		if (playerCard.color == botCard[i].color && botCard[i].use == false) {
			if (botCard[i].value > value) {
				value = botCard[i].value;
				indexOfCard = i;
			}
		}
	}

	if (value == 0 && indexOfCard == 0) {
		for (int i = 0; i < 8; i++) {
			if (botCard[i].use == false) {
				indexOfCard = i;
				break;
			}
		}
	}

	botCard[indexOfCard].use = true;
	if (position == 720.0f) {
		botCard[indexOfCard].cardImg.setRotation(0.0f);
	}
	Move::turnFront(botCard[indexOfCard]);
	botCard[indexOfCard].cardImg.setPosition(sf::Vector2f(position, 400.0f));
	getCardAddress(botCard[indexOfCard]);
	return botCard[indexOfCard];
}

void GameMechanics::getCardAddress(Card& botCard) {
	
	if (who == 0) {
		previousCardP2Ptr = &botCard;
		who = 1;
	}
	else {
		previousCardP3Ptr = &botCard;
		who = 0;
	}

}

void GameMechanics::checkGame(Card& cardP1, Card& cardP2, Card& cardP3) {

	bool wylozonycolor = false;
	if (activeT != 0) {
		/*
		* 1 - pik
		* 2 - trefl
		* 3 - karo
		* 4 - kier
		* edit
		*/
		if (activeT == 1) {
			if (cardP1.color == "pik" && cardP2.color == "pik" && cardP3.color == "pik") {
				wylozonycolor = true;
				if (cardP1.value > cardP2.value && cardP1.value > cardP3.value) {
					Points::winP1 = 1;
					bidder = 1;
					whoFirst.first = true;
					whoFirst.second = true;
				}
				else if (cardP2.value > cardP1.value && cardP2.value > cardP3.value) {
					Points::Points::winP2 = 1;
					bidder = 2;
					whoFirst.first = false;
					whoFirst.second = true;
				}
				else if (cardP3.value > cardP1.value && cardP3.value > cardP3.value) {
					Points::winP3 = 1;
					bidder = 3;
					whoFirst.first = true;
					whoFirst.second = false;
				}
			}
			else if (cardP1.color == "pik" && cardP2.color == "pik" && cardP3.color != "pik") {
				wylozonycolor = true;
				if (cardP1.value > cardP2.value) {

					Points::winP1 = 1;
					bidder = 1;
					whoFirst.first = true;
					whoFirst.second = true;
				}
				else if (cardP2.value > cardP1.value) {

					Points::winP2 = 1;
					bidder = 2;
					whoFirst.first = false;
					whoFirst.second = true;
				}
			}
			else if (cardP1.color == "pik" && cardP3.color == "pik" && cardP2.color != "pik") {
				wylozonycolor = true;
				if (cardP1.value > cardP3.value) {

					Points::winP1 = 1;
					bidder = 1;
					whoFirst.first = true;
					whoFirst.second = true;
				}
				else if (cardP3.value > cardP1.value) {
					Points::winP3 = 1;
					bidder = 3;
					whoFirst.first = true;
					whoFirst.second = false;
				}
			}
			else if (cardP3.color == "pik" && cardP2.color == "pik" && cardP1.color != "pik") {
				wylozonycolor = true;
				if (cardP3.value > cardP2.value) {

					Points::winP3 = 1;
					bidder = 3;
					whoFirst.first = true;
					whoFirst.second = false;
				}
				else if (cardP2.value > cardP3.value) {

					Points::winP2 = 1;
					bidder = 2;
					whoFirst.first = false;
					whoFirst.second = true;
				}
			}
			else if (cardP1.color == "pik" && cardP2.color != "pik" && cardP3.color != "pik") {

				wylozonycolor = true;
				Points::winP1 = 1;
				bidder = 1;
				whoFirst.first = true;
				whoFirst.second = true;
			}
			else if (cardP1.color != "pik" && cardP2.color == "pik" && cardP3.color != "pik") {

				wylozonycolor = true;
				Points::winP2 = 1;
				bidder = 2;
				whoFirst.first = false;
				whoFirst.second = true;
			}
			else if (cardP1.color != "pik" && cardP2.color != "pik" && cardP3.color == "pik") {
				wylozonycolor = true;
				Points::winP3 = 1;
				bidder = 3;
				whoFirst.first = true;
				whoFirst.second = false;
			}
		}
		else if (activeT == 2) {
			if (cardP1.color == "trefl" && cardP2.color == "trefl" && cardP3.color == "trefl") {
				wylozonycolor = true;
				if (cardP1.value > cardP2.value && cardP1.value > cardP3.value) {
					Points::winP1 = 1;
					bidder = 1;
					whoFirst.first = true;
					whoFirst.second = true;
				}
				else if (cardP2.value > cardP1.value && cardP2.value > cardP3.value) {
					Points::winP2 = 1;
					bidder = 2;
					whoFirst.first = false;
					whoFirst.second = true;
				}
				else if (cardP3.value > cardP1.value && cardP3.value > cardP3.value) {
					Points::winP3 = 1;
					bidder = 3;
					whoFirst.first = true;
					whoFirst.second = false;
				}
			}
			else if (cardP1.color == "trefl" && cardP2.color == "trefl" && cardP3.color != "trefl") {
				wylozonycolor = true;
				if (cardP1.value > cardP2.value) {
					Points::winP1 = 1;
					bidder = 1;
					whoFirst.first = true;
					whoFirst.second = true;
				}
				else if (cardP2.value > cardP1.value) {
					Points::winP2 = 1;
					bidder = 2;
					whoFirst.first = false;
					whoFirst.second = true;
				}
			}
			else if (cardP1.color == "trefl" && cardP3.color == "trefl" && cardP2.color != "trefl") {
				wylozonycolor = true;
				if (cardP1.value > cardP3.value) {
					Points::winP1 = 1;
					bidder = 1;
					whoFirst.first = true;
					whoFirst.second = true;
				}
				else if (cardP3.value > cardP1.value) {
					Points::winP3 = 1;
					bidder = 3;
					whoFirst.first = true;
					whoFirst.second = false;
				}
			}
			else if (cardP3.color == "trefl" && cardP2.color == "trefl" && cardP1.color != "trefl") {
				wylozonycolor = true;
				if (cardP3.value > cardP2.value) {
					Points::winP3 = 1;
					bidder = 3;
					whoFirst.first = true;
					whoFirst.second = false;
				}
				else if (cardP2.value > cardP3.value) {
					Points::winP2 = 1;
					bidder = 2;
					whoFirst.first = false;
					whoFirst.second = true;
				}
			}
			else if (cardP1.color == "trefl" && cardP2.color != "trefl" && cardP3.color != "trefl") {
				wylozonycolor = true;
				Points::winP1 = 1;
				bidder = 1;
				whoFirst.first = true;
				whoFirst.second = true;
			}
			else if (cardP1.color != "trefl" && cardP2.color == "trefl" && cardP3.color != "trefl") {
				wylozonycolor = true;
				Points::winP2 = 1;
				bidder = 2;
				whoFirst.first = false;
				whoFirst.second = true;
			}
			else if (cardP1.color != "trefl" && cardP2.color != "trefl" && cardP3.color == "trefl") {
				wylozonycolor = true;
				Points::winP3 = 1;
				bidder = 3;
				whoFirst.first = true;
				whoFirst.second = false;
			}
		}
		else if (activeT == 3) {
			if (cardP1.color == "karo" && cardP2.color == "karo" && cardP3.color == "karo") {
				wylozonycolor = true;
				if (cardP1.value > cardP2.value && cardP1.value > cardP3.value) {
					Points::winP1 = 1;
					bidder = 1;
					whoFirst.first = true;
					whoFirst.second = true;
				}
				else if (cardP2.value > cardP1.value && cardP2.value > cardP3.value) {
					Points::winP2 = 1;
					bidder = 2;
					whoFirst.first = false;
					whoFirst.second = true;
				}
				else if (cardP3.value > cardP1.value && cardP3.value > cardP3.value) {
					Points::winP3 = 1;
					bidder = 3;
					whoFirst.first = true;
					whoFirst.second = false;
				}
			}
			else if (cardP1.color == "karo" && cardP2.color == "karo" && cardP3.color != "karo") {
				wylozonycolor = true;
				if (cardP1.value > cardP2.value) {
					Points::winP1 = 1;
					bidder = 1;
					whoFirst.first = true;
					whoFirst.second = true;
				}
				else if (cardP2.value > cardP1.value) {
					Points::winP2 = 1;
					bidder = 2;
					whoFirst.first = false;
					whoFirst.second = true;
				}
			}
			else if (cardP1.color == "karo" && cardP3.color == "karo" && cardP2.color != "karo") {
				wylozonycolor = true;
				if (cardP1.value > cardP3.value) {
					Points::winP1 = 1;
					bidder = 1;
					whoFirst.first = true;
					whoFirst.second = true;
				}
				else if (cardP3.value > cardP1.value) {
					Points::winP3 = 1;
					bidder = 3;
					whoFirst.first = true;
					whoFirst.second = false;
				}
			}
			else if (cardP3.color == "karo" && cardP2.color == "karo" && cardP1.color != "karo") {
				wylozonycolor = true;
				if (cardP3.value > cardP2.value) {
					Points::winP3 = 1;
					bidder = 3;
					whoFirst.first = true;
					whoFirst.second = false;
				}
				else if (cardP2.value > cardP3.value) {
					Points::winP2 = 1;
					bidder = 2;
					whoFirst.first = false;
					whoFirst.second = true;
				}
			}
			else if (cardP1.color == "karo" && cardP2.color != "karo" && cardP3.color != "karo") {
				wylozonycolor = true;
				Points::winP1 = 1;
				bidder = 1;
				whoFirst.first = true;
				whoFirst.second = true;
			}
			else if (cardP1.color != "karo" && cardP2.color == "karo" && cardP3.color != "karo") {
				wylozonycolor = true;
				Points::winP2 = 1;
				bidder = 2;
				whoFirst.first = false;
				whoFirst.second = true;
			}
			else if (cardP1.color != "karo" && cardP2.color != "karo" && cardP3.color == "karo") {
				wylozonycolor = true;
				Points::winP3 = 1;
				bidder = 3;
				whoFirst.first = true;
				whoFirst.second = false;
			}
		}
		else if (activeT == 4) {
			if (cardP1.color == "kier" && cardP2.color == "kier" && cardP3.color == "kier") {
				wylozonycolor = true;
				if (cardP1.value > cardP2.value && cardP1.value > cardP3.value) {
					Points::winP1 = 1;
					bidder = 1;
					whoFirst.first = true;
					whoFirst.second = true;
				}
				else if (cardP2.value > cardP1.value && cardP2.value > cardP3.value) {
					Points::winP2 = 1;
					bidder = 2;
					whoFirst.first = false;
					whoFirst.second = true;
				}
				else if (cardP3.value > cardP1.value && cardP3.value > cardP3.value) {
					Points::winP3 = 1;
					bidder = 3;
					whoFirst.first = true;
					whoFirst.second = false;
				}
			}
			else if (cardP1.color == "kier" && cardP2.color == "kier" && cardP3.color != "kier") {
				wylozonycolor = true;
				if (cardP1.value > cardP2.value) {
					Points::winP1 = 1;
					bidder = 1;
					whoFirst.first = true;
					whoFirst.second = true;
				}
				else if (cardP2.value > cardP1.value) {
					Points::winP2 = 1;
					bidder = 2;
					whoFirst.first = false;
					whoFirst.second = true;
				}
			}
			else if (cardP1.color == "kier" && cardP3.color == "kier" && cardP2.color != "kier") {
				wylozonycolor = true;
				if (cardP1.value > cardP3.value) {
					Points::winP1 = 1;
					bidder = 1;
					whoFirst.first = true;
					whoFirst.second = true;
				}
				else if (cardP3.value > cardP1.value) {
					Points::winP3 = 1;
					bidder = 3;
					whoFirst.first = true;
					whoFirst.second = false;
				}
			}
			else if (cardP3.color == "kier" && cardP2.color == "kier" && cardP1.color != "kier") {
				wylozonycolor = true;
				if (cardP3.value > cardP2.value) {
					Points::winP3 = 1;
					bidder = 3;
					whoFirst.first = true;
					whoFirst.second = false;
				}
				else if (cardP2.value > cardP3.value) {
					Points::winP2 = 1;
					bidder = 2;
					whoFirst.first = false;
					whoFirst.second = true;
				}
			}
			else if (cardP1.color == "kier" && cardP2.color != "kier" && cardP3.color != "kier") {
				wylozonycolor = true;
				Points::winP1 = 1;
				bidder = 1;
				whoFirst.first = true;
				whoFirst.second = true;
			}
			else if (cardP1.color != "kier" && cardP2.color == "kier" && cardP3.color != "kier") {
				wylozonycolor = true;
				Points::winP2 = 1;
				bidder = 2;
				whoFirst.first = false;
				whoFirst.second = true;
			}
			else if (cardP1.color != "kier" && cardP2.color != "kier" && cardP3.color == "kier") {
				wylozonycolor = true;
				Points::winP3 = 1;
				bidder = 3;
				whoFirst.first = true;
				whoFirst.second = false;
			}
		}
	}
	if (!wylozonycolor) {
		if (whoFirst.first == true && whoFirst.second == true) {
			if (cardP1.marriage == true) {
				if (cardP1.color == "pik") {
					Points::pointsP1tmp += 40;
					activeT = 1;
				}
				else if (cardP1.color == "trefl") {
					Points::pointsP1tmp += 60;
					activeT = 2;
				}
				else if (cardP1.color == "karo") {
					Points::pointsP1tmp += 80;
					activeT = 3;
				}
				else if (cardP1.color == "kier") {
					Points::pointsP1tmp += 100;
					activeT = 4;
				}
			}
			if (cardP1.color == cardP2.color && cardP1.color == cardP3.color) {
				if (cardP1.value > cardP2.value && cardP1.value > cardP3.value) {
					Points::winP1 = 1;
					bidder = 1;
					whoFirst.first = true;
					whoFirst.second = true;
				}
				else if (cardP2.value > cardP1.value && cardP2.value > cardP3.value) {
					Points::winP2 = 1;
					bidder = 2;
					whoFirst.first = false;
					whoFirst.second = true;
				}
				else if (cardP3.value > cardP1.value && cardP3.value > cardP2.value) {
					Points::winP3 = 1;
					bidder = 3;
					whoFirst.first = true;
					whoFirst.second = false;
				}
			}
			else if (cardP1.color == cardP2.color) {
				if (cardP1.value > cardP2.value) {
					Points::winP1 = 1;
					bidder = 1;
					whoFirst.first = true;
					whoFirst.second = true;
				}
				else {
					Points::winP2 = 1;
					bidder = 2;
					whoFirst.first = false;
					whoFirst.second = true;
				}
			}
			else if (cardP1.color == cardP3.color) {
				if (cardP1.value > cardP3.value) {
					Points::winP1 = 1;
					bidder = 1;
					whoFirst.first = true;
					whoFirst.second = true;
				}
				else {
					Points::winP3 = 1;
					bidder = 3;
					whoFirst.first = true;
					whoFirst.second = false;
				}
			}
			else {
				Points::winP1 = 1;
				bidder = 1;
				whoFirst.first = true;
				whoFirst.second = true;
			}
		}
		else if (whoFirst.first == false && whoFirst.second == true) {
			if (cardP2.marriage == true) {
				if (cardP2.color == "pik") {
					Points::pointsP2tmp += 40;
					activeT = 1;
				}
				else if (cardP2.color == "trefl") {
					Points::pointsP2tmp += 60;
					activeT = 2;
				}
				else if (cardP2.color == "karo") {
					Points::pointsP2tmp += 80;
					activeT = 3;
				}
				else if (cardP2.color == "kier") {
					Points::pointsP2tmp += 100;
					activeT = 4;
				}
			}
			if (cardP2.color == cardP1.color && cardP2.color == cardP3.color) {
				if (cardP2.value > cardP1.value && cardP2.value > cardP3.value) {
					Points::winP2 = 1;
					bidder = 2;
					whoFirst.first = false;
					whoFirst.second = true;
				}
				else if (cardP1.value > cardP2.value && cardP1.value > cardP3.value) {
					Points::winP1 = 1;
					bidder = 1;
					whoFirst.first = true;
					whoFirst.second = true;
				}
				else if (cardP3.value > cardP2.value && cardP3.value > cardP1.value) {
					Points::winP3 = 1;
					bidder = 3;
					whoFirst.first = true;
					whoFirst.second = false;
				}
			}
			else if (cardP2.color == cardP1.color) {
				if (cardP2.value > cardP1.value) {
					Points::winP2 = 1;
					bidder = 2;
					whoFirst.first = false;
					whoFirst.second = true;
				}
				else {
					Points::winP1 = 1;
					bidder = 1;
					whoFirst.first = true;
					whoFirst.second = true;
				}
			}
			else if (cardP2.color == cardP3.color) {
				if (cardP2.value > cardP3.value) {
					Points::winP2 = 1;
					bidder = 2;
					whoFirst.first = false;
					whoFirst.second = true;
				}
				else {
					Points::winP3 = 1;
					bidder = 3;
					whoFirst.first = true;
					whoFirst.second = false;
				}
			}
			else {
				Points::winP2 = 1;
				bidder = 2;
				whoFirst.first = false;
				whoFirst.second = true;
			}
		}
		else if (whoFirst.first == true && whoFirst.second == false) {
			if (cardP3.marriage == true) {
				if (cardP3.color == "pik") {
					Points::pointsP3tmp += 40;
					activeT = 1;
				}
				else if (cardP3.color == "trefl") {
					Points::pointsP3tmp += 60;
					activeT = 2;
				}
				else if (cardP3.color == "karo") {
					Points::pointsP3tmp += 80;
					activeT = 3;
				}
				else if (cardP3.color == "kier") {
					Points::pointsP3tmp += 100;
					activeT = 4;
				}
			}
			if (cardP3.color == cardP2.color && cardP3.color == cardP1.color) {
				if (cardP3.value > cardP2.value && cardP3.value > cardP1.value) {
					Points::winP3 = 1;
					bidder = 3;
					whoFirst.first = true;
					whoFirst.second = false;
				}
				else if (cardP2.value > cardP3.value && cardP2.value > cardP1.value) {
					Points::winP2 = 1;
					bidder = 2;
					whoFirst.first = false;
					whoFirst.second = true;
				}
				else if (cardP1.value > cardP3.value && cardP1.value > cardP2.value) {
					Points::winP1 = 1;
					bidder = 1;
					whoFirst.first = true;
					whoFirst.second = true;
				}
			}
			else if (cardP3.color == cardP2.color) {
				if (cardP3.value > cardP2.value) {
					Points::winP3 = 1;
					bidder = 3;
					whoFirst.first = true;
					whoFirst.second = false;
				}
				else {
					Points::winP2 = 1;
					bidder = 2;
					whoFirst.first = false;
					whoFirst.second = true;
				}
			}
			else if (cardP3.color == cardP1.color) {
				if (cardP3.value > cardP1.value) {
					Points::winP3 = 1;
					bidder = 3;
					whoFirst.first = true;
					whoFirst.second = false;
				}
				else {
					Points::winP1 = 1;
					bidder = 1;
					whoFirst.first = true;
					whoFirst.second = true;
				}
			}
			else {
				Points::winP3 = 1;
				bidder = 3;
				whoFirst.first = true;
				whoFirst.second = false;
			}
		}
	}
	Points::sumPoints(cardP1.figure, cardP2.figure, cardP3.figure);
}

void GameMechanics::removeCard() {
	previousCardP1Ptr->cardImg.setPosition(sf::Vector2f(-100.0f, -100.0f));
	previousCardP2Ptr->cardImg.setPosition(sf::Vector2f(-100.0f, -100.0f));
	previousCardP3Ptr->cardImg.setPosition(sf::Vector2f(-100.0f, -100.0f));
}