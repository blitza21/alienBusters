#include "game.h"

int main()
{
	int mode;
	do {
		cout << "Choose game mode: 1 for active ,  2 for silent\n";
		cin >> mode;
		cin.ignore();
	} while (mode != 1 && mode != 2);
	game AlienInvasion;
	AlienInvasion.simulateGame(mode);
}