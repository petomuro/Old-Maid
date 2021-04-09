#include <iostream>
#include <cstdlib>
#include <time.h>
#include <algorithm>
using namespace std;

int counter = 0;

class players
{
protected:
	int number;
public:
	int howMany()
	{
	    cout << endl;
        cout << "Rules for Old Maid:" << endl;
        cout << "Take turns going around in a circle picking a card from the next player's hand. If you get a pair, you reducing the number of cards in your hand. The last player left with the number of 17 loses the game." << endl;
        cout << endl;

		do {
			cout << "How many players are going to play? (2 - 5)" << endl;
			cin >> this->number;

			if ((number > 5) || (number < 2))
			{
				cout << "You must choose 2 - 5 players!!" << endl;
				continue;
			}

		} while ((number > 5) || (number < 2));

		for (int i = 0; i < number; i++)
			counter++;

		return counter;
	}

	void printPlayers()
	{
		cout << "*************************Welcome in Game - Old Maid!*************************" << endl;
		cout << "Players: (" << howMany() << ")" << endl;
	}
};

class cards : public players
{
protected:
    int *ptr, *card0, *card1;
public:
	/*int randrange(int low, int high)
	{
		return rand() % (high - low + 1) + low;
	}*/

	void randomCardsAndPtr()
	{
		this->ptr = (int*)malloc(counter * sizeof(int));

		for (int i = 0; i < counter; i++)
		{
			if (counter == 2)
				ptr[i] = i + 16;
			/*else if (counter == 3) ptr[i] = randrange(11, 11);
				else if (counter == 4) ptr[i] = randrange(8, 9);
					else ptr[i] = randrange(6, 7);*/
		}

		this->card0 = (int*)malloc((*ptr * counter) * sizeof(int));
		this->card1 = (int*)malloc((*ptr * counter) * sizeof(int));

		if (counter == 2)
		{
			for (int i = 0; i < ptr[0]; i++)
				card0[i] = i + 1;

			random_shuffle(&card0[0], &card0[ptr[0]]);

			for (int i = 0; i < ptr[1]; i++)
				card1[i] = i + 1;

			random_shuffle(&card1[1], &card1[ptr[1]]);

		}
	}

	void printRandomCardsAndPtr()
	{
		players::printPlayers();
		randomCardsAndPtr();
	}
};

class its_your_turn : public cards
{
protected:
    int turn0, turn1;
    int *player, *cardIYT0 , *cardIYT1;
public:
	void yourTurn()
	{
		this->player = (int*)malloc(counter * sizeof(int));

		for (int i = 0; i < counter; i++)
			player[i] = ptr[i];

		this->cardIYT0 = (int*)malloc(*player * sizeof(int));
		this->cardIYT1 = (int*)malloc(*player * sizeof(int));

		for (int i = 0; i < player[0]; i++)
			cardIYT0[i] = card0[i];

		for (int i = 0; i < player[1]; i++)
			cardIYT1[i] = card1[i];

		if (counter == 2)
		{
			do {
				cout << "Player 1: ";

				for (int i = 0; i < player[0]; i++)
					//cout << cardIYT0[i] << ", ";
					cout << "#, ";

				cout << endl;
				cout << "Player 2: ";

				for (int i = 0; i < player[1]; i++)
					//cout << cardIYT1[i] << ", ";
					cout << "#, ";

				cout << endl << endl;

				while (player[0])
				{
					cout << "********************************************************************************" << endl;
					cout << "This is P1 deck: ";

					for (int i = 0; i < player[0]; i++)
						cout << cardIYT0[i] << ", ";

					cout << endl;

					cout << "It's P1 turn" << endl << endl;
					cout << "Which index do you want to turn?" << endl;
					cout << "You can turn card within the range with index 0 - " << player[1] - 1 << endl;
					do {
						cin >> turn1;

						if ((turn1 > player[1] - 1) || (turn1 < 0))
						{
							cout << "You must turn card within the range with index 0 - " << player[1] - 1 << endl;
							continue;
						}

					} while ((turn1 > player[1] - 1) || (turn1 < 0));
					cout << "You turned card: " << cardIYT1[turn1] << " from index: " << turn1 << endl << endl;

					for (int i = 0; i < player[0]; i++)
					{
						if (cardIYT1[turn1] == cardIYT0[i])
						{
							cardIYT0[i] = 0;
							swap(cardIYT0[i], cardIYT0[player[0] - 1]);
							player[0]--;

							cardIYT1[turn1] = 0;
							swap(cardIYT1[turn1], cardIYT1[player[1] - 1]);
							player[1]--;

							cout << "Cards missing: " << player[0] << endl;
							break;
						}

						else if (cardIYT1[turn1] == 17)
						{
							player[0]++;
							cardIYT1[turn1] = 0;
							cardIYT0[player[0] - 1] = 17;

							swap(cardIYT1[turn1], cardIYT1[player[1] - 1]);
							player[1]--;

							cout << "Cards missing: " << player[0] << endl;
							break;
						}
					}

					cout << "********************************************************************************" << endl << endl << endl;
					break;
				}

				cout << "Player 1: ";

				for (int i = 0; i < player[0]; i++)
					//cout << cardIYT0[i] << ", ";
					cout << "#, ";

				cout << endl;
				cout << "Player 2: ";

				for (int i = 0; i < player[1]; i++)
					//cout << cardIYT1[i] << ", ";
					cout << "#, ";

				cout << endl << endl;

				while (player[1])
				{
					cout << "********************************************************************************" << endl;
					cout << "This is P2 deck: ";

					for (int i = 0; i < player[1]; i++)
						cout << cardIYT1[i] << ", ";

					cout << endl;

					cout << "It's P2 turn" << endl << endl;
					cout << "Which index do you want to turn?" << endl;
					cout << "You can turn card within the range with index 0 - " << player[0] - 1 << endl;
					do {
						cin >> turn0;

						if ((turn0 > player[0] - 1) || (turn0 < 0))
						{
							cout << "You must turn card within the range with index 0 - " << player[0] - 1 << endl;
							continue;
						}

					} while ((turn0 > player[0] - 1) || (turn0 < 0));
					cout << "You turned card: " << cardIYT0[turn0] << " from index: " << turn0 << endl << endl;

					for (int i = 0; i < player[1]; i++)
					{
						if (cardIYT0[turn0] == cardIYT1[i])
						{
							cardIYT1[i] = 0;
							swap(cardIYT1[i], cardIYT1[player[1] - 1]);
							player[1]--;

							cardIYT0[turn0] = 0;
							swap(cardIYT0[turn0], cardIYT0[player[0] - 1]);
							player[0]--;

							cout << "Cards missing: " << player[1] << endl;
							break;
						}

						else if (cardIYT0[turn0] == 17)
						{
							player[1]++;
							cardIYT0[turn0] = 0;
							cardIYT1[player[1] - 1] = 17;

							swap(cardIYT0[turn0], cardIYT0[player[0] - 1]);
							player[0]--;

							cout << "Cards missing: " << player[1] << endl;
							break;
						}
					}

					cout << "********************************************************************************" << endl << endl << endl;
					break;
				}

				if (player[0] == 0)
                {
                    cout << "Winner is P1 and P2 is old maid!" << endl;
                    break;
                }
                    else if (player[1] == 0)
                    {
                        cout << "Winner is P2 and P1 is old maid!" << endl;
                        break;
                    }

			} while ((player[0] != 0) || (player[1] != 0));

		}

		free(ptr); free(card0); free(card1); free(player); free(cardIYT0); free(cardIYT1);

	}

	void print()
	{
		cards::printRandomCardsAndPtr();
		yourTurn();
	}
};

int main()
{
	its_your_turn game;
	game.print();

	system("pause");

	return 0;
}
