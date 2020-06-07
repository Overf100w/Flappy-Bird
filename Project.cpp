#include <iostream>
#include <windows.h>
#include <conio.h>
#include <ctime>
#include <random>

class bird {
public:
	const char* down = "\\\\\\\\_"; // falling bird model
	const char* up = "////-"; // rising bird model
	const char* model = up; // pointer to the position of bird

	int y = 15;
	int delay = 15; // delay of dropping

	void flap() {
		delay = 1; // time after flap becomes zero
		model = up; // wing flap
	}

	void physic() {
		if (delay < 7) { // first 288 ms after flap bird rises
			model = up;
			if(delay % 2 == 0) y--;
		}
		else if (delay > 7) { // then fly down
			model = down; // wing flap
			y++;
		}
	}
};
	
class block {
public:
	block() {
		y = rand() % 20 + 5; // position of gateway
		y2 = y + 4;
		x = 57; // x position of gateway
	}

	int x, y, y2;

	void toBegining() { // in case x == 0 block returns to beginning
		if (x == 1) {
			x = 57;
			y = rand() % 20 + 5;
			y2 = y + 4;
		}
	}
};

void drow(int y, const char* bird, int blX, int blY, int blY2);

int score = 0;
bool game = 1;
int readP; // read potin (buffer)
char arr[2000] = "lol"; // buffer

int main() {
	srand(time(NULL));

	bird player; // bird class
	block first; // block class
	
	while (game) { // 15 ms loop
		first.x--; // *gateway moves left*
		player.delay++;

		player.physic(); // physic of dropping
		drow(player.y, player.model, first.x, first.y, first.y2);
		std::cout << arr << '\n' << score; // buffer outputs

		if (player.y == 31 || player.y == 1) game = 0; // get ground or top
		if ((first.x > 15 && first.x < 22) && (player.y < first.y || player.y > first.y2)) game = 0; // get block
		if (first.x == 7) score++; // pass block

		if (_kbhit()) if (_getch() == (char)32) player.flap(); //event for keypress

		first.toBegining(); // block x = 0 

		Sleep(70);
	}

	std::cout << "\nYOU MISSED IT! GOTTA TRY AGAIN." << std::endl; // ohh, u'll be really upset
	system("pause");

	return 0;
}

void drow(int y, const char* bird, int blX, int blY, int blY2) {
	system("cls");
	readP = -1; // next position in *arr* array

	for (int i = 1; i < 30; i++) { // 30 rows
		if (i == y) { // check bird row

			if (blX > 21 && (i < blY || i > blY2)) { //
				arr[++readP] = '\t'; // bird left side indent
				arr[++readP] = '\t'; // bird left side indent
				for (int j = 0; j < 5; j++) arr[++readP] = bird[j]; // drowing bird

				for (int m = 0; m < blX - 21; m++) arr[++readP] = ' ';

				arr[++readP] = '|'; // --|
				arr[++readP] = '='; // --|-- block body
				arr[++readP] = '|'; // --|

				arr[++readP] = '\n'; // selecting new row
			}
			else if (blX < 16 && (i < blY || i > blY2)) {
				for (int m = 0; m < blX; m++) arr[++readP] = ' ';

				arr[++readP] = '|'; // --|
				arr[++readP] = '='; // --|-- block body
				arr[++readP] = '|'; // --|

				for (int m = 0; m < 11 - blX; m++) arr[++readP] = ' ';

				for (int j = 0; j < 5; j++) arr[++readP] = bird[j]; // drowing bird

				arr[++readP] = '\n'; // selecting new row
			}
			else {
				arr[++readP] = '\t';
				arr[++readP] = '\t';
				for (int j = 0; j < 5; j++) arr[++readP] = bird[j]; // drowing bird
				arr[++readP] = '\n'; // selecting new row
			}
		}																			 
		else if (i < blY || i > blY2){
			for (int j = 0; j < blX; j++) arr[++readP] = ' ';
			arr[++readP] = '|'; // -|
			arr[++readP] = '='; // -|-- block body
			arr[++readP] = '|'; // -|

			arr[++readP] = '\n'; // selecting new row
		}
		else arr[++readP] = '\n';

	}
	for (int j = 0; j < 60; j++) arr[++readP] = '-'; // ground
	arr[readP] = '\0'; // last symbol
}