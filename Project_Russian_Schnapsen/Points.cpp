#include "Points.h"

sf::Text Points::pointsTextP1;
int Points::pointsP1 = 0;
int Points::pointsP1tmp = 0;

sf::Text Points::pointsTextP2;
int Points::pointsP2 = 0;
int Points::pointsP2tmp = 0;

sf::Text Points::pointsTextP3;
int Points::pointsP3 = 0;
int Points::pointsP3tmp = 0;

bool Points::winP1 = 0;
bool Points::winP2 = 0;
bool Points::winP3 = 0;


void Points::sumPoints(std::string cardP1, std::string cardP2, std::string cardP3) {
	int roundPoints = 0;

	if (cardP1 == "A")
		roundPoints += 11;
	else if (cardP1 == "K")
		roundPoints += 4;
	else if (cardP1 == "Q")
		roundPoints += 3;
	else if (cardP1 == "J")
		roundPoints += 2;
	else if (cardP1 == "10")
		roundPoints += 10;

	if (cardP2 == "A")
		roundPoints += 11;
	else if (cardP2 == "K")
		roundPoints += 4;
	else if (cardP2 == "Q")
		roundPoints += 3;
	else if (cardP2 == "J")
		roundPoints += 2;
	else if (cardP2 == "10")
		roundPoints += 10;

	if (cardP3 == "A")
		roundPoints += 11;
	else if (cardP3 == "K")
		roundPoints += 4;
	else if (cardP3 == "Q")
		roundPoints += 3;
	else if (cardP3 == "J")
		roundPoints += 2;
	else if (cardP3 == "10")
		roundPoints += 10;

	if (winP1 == 1) {
		pointsP1tmp += roundPoints;
	}
	else if (winP2 == 1) {
		pointsP2tmp += roundPoints;
	}
	else if (winP3 == 1) {
		pointsP3tmp += roundPoints;
	}
	roundPoints = 0;
	/*
	* Je�eli gra runda si� ko�czy, podliczane s� roundPoints zdobyte podczas tej rundy
	*/
	if (Bidding::reset == 7) {
		/*
		* Gracz, kt�ry prowadzi� licytacj�, je�eli nie osi�gn�� tylu punkt�w ile zalicytowa�,
		* to tyle punkt�w zostaje odj�tych, w przypadku reszty graczy roundPoints sumuj� si� z ju� zdobytymi
		*/
		if (Bidding::whoWonBid == 1) {
			if (Bidding::pointsNeeded < pointsP1tmp) {
				pointsP1 += pointsP1tmp;
			}
			else {
				pointsP1 -= Bidding::pointsNeeded;
			}
			pointsP2 += pointsP2tmp;
			pointsP3 += pointsP3tmp;
			Bidding::whoWonMatch = 1;
		}
		if (Bidding::whoWonBid == 2) {
			if (Bidding::pointsNeeded < pointsP2tmp) {
				pointsP2 += pointsP2tmp;
			}
			else {
				pointsP2 -= Bidding::pointsNeeded;
			}
			pointsP1 += pointsP1tmp;
			pointsP3 += pointsP3tmp;
			Bidding::whoWonMatch = 2;
		}
		if (Bidding::whoWonBid == 3) {
			if (Bidding::pointsNeeded < pointsP3tmp) {
				pointsP3 += pointsP3tmp;
			}
			else {
				pointsP3 -= Bidding::pointsNeeded;
			}
			pointsP1 += pointsP1tmp;
			pointsP2 += pointsP2tmp;
			Bidding::whoWonMatch = 3;
		}
		/*
		* Zerowanie zmiennych odpowiadaj�cych za podlicznie punkt�w podczas rundy
		*/
		pointsP1tmp = 0;
		pointsP2tmp = 0;
		pointsP3tmp = 0;
		Bidding::circle1.setFillColor(sf::Color::Green);
		Bidding::circle2.setFillColor(sf::Color::Green);
		Bidding::circle3.setFillColor(sf::Color::Green);
		if (pointsP1 >= 200) {
			//koniec = true;
			//czyWygralem = true;
			//czyReset = true;
			//przejscieDo = 4;
		}
		if (pointsP2 >= 200 || pointsP3 >= 200) {
			//koniec = true;
			//czyReset = true;
			//przejscieDo = 4;
		}
	}
}