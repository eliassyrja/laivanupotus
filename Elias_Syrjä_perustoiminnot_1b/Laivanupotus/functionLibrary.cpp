#include <iostream>
#include <string>
#include "functionLibrary.h"

using namespace std;

const int ROW = 7, COL = 7;
char arrayShips[ROW][COL] = { 0 };	//arrayShips stores locations of placed ships
char arrayShots[ROW][COL] = { 0 };	//arrayShots is used as the gameboard
char arraySunken[ROW][COL] = { 0 }; //arraySunken is used to store information on hits on particular ships, printShots will print out # when ship is sunken

void printMenu() {
	/*
	name: printMenu
	function: Prints out menu, and calls functions based on user inputs.
	parameters: none
	return values: none 
	*/
	char userInput;

	cout << "Ship Sinking Game" << endl;
	cout << "=================" << endl;
	cout << "Options:" << endl << endl << "1) Enter ship positions" << endl << "2) Play" << endl << "L) Quit" << endl << endl << "Input: ";

	cin >> userInput;
	userInput = toupper(userInput);

	if (userInput == '1') {
		setShips();
	}
	if (userInput == '2') {
		shotFunction();
	}
	if (userInput == 'L') {
		exit(1);
	}
	if (userInput != 'L' || userInput != '1' || userInput != '2') {
		cout << "Invalid input.." << endl;
		printMenu();
	}
}

void shotFunction() {
	/*
	name: shotFunction
	function:	asks user for shooting coordinates, calls functions to validate coordinates, marks hits and misses onto board, saves data of
				sunken ships into arraySunken
	parameters: none
	return values: none
	*/
	string shotCoordinate;
	int shipLength, shotMem1, shotMem2;
	int shipStatus = 0;
	int maxHits = 14;

	static int value = 1;
	static int hits;
	static int ship2, ship3, ship4, ship5;


	if (value == 1) {

		for (int x = 0; x < 7; x++) {
			for (int y = 0; y < 7; y++)

				if (checkShot(x, y) == 0) {
					system("cls");
					cout << "You have not entered ship positions yet." << endl;
					printMenu();
				}
				else value = 0;
		}
	}
	while (value == 0) {

		int result = 1;
		system("cls");
		printShots();
		cout << "Enter shooting coordinate: ";

		while (result == 1) {

			cin >> shotCoordinate;

			if (shotCoordinate.size() != 2) {
				cout << "Invalid input. Enter proper coordinate (e.g. A1)." << endl;
			}
			else result = 2;

			for (int O = 0; O < 1; O++) {
				shotCoordinate[O] = toupper(shotCoordinate[O]);
			}
			if (shotCoordinate[0] == '@') {
				system("cls");
				printShipPositions();
			}
			if (shotCoordinate[0] == 'P') {
				system("cls");
				cout << "You paused the game. " << endl;
				printMenu();
			}

			shotMem1 = shotCoordinate[0] - 65;
			shotMem2 = shotCoordinate[1] - 49;

			while (result == 2) {
				if (shotMem1 <= 6 && shotMem1 >= 0 && shotMem2 >= 0 && shotMem2 <= 6) {
					result = 3;
				}
				else { cout << "Invalid input. Enter proper coordinate (e.g. A1)." << endl; result = 1; }
			}
		}
		if (checkShip(shotMem1, shotMem2) == 0) {

			if (checkShot(shotMem1, shotMem2) == 1) {
				arrayShots[shotMem1][shotMem2] = '*';

				if (arrayShips[shotMem1][shotMem2] == '#') {
					ship5 += 1;
					arraySunken[shotMem1][shotMem2] = '#';
					shipLength = 0;
				}

				if (arrayShips[shotMem1][shotMem2] == '#' + 1) {
					arraySunken[shotMem1][shotMem2] = '#' + 1;
					ship4 += 1;
					shipLength = 1;
				}

				if (arrayShips[shotMem1][shotMem2] == '#' + 2) {
					ship3 += 1;
					arraySunken[shotMem1][shotMem2] = '#' + 2;
					shipLength = 2;
				}

				if (arrayShips[shotMem1][shotMem2] == '#' + 3) {
					ship2 += 1;
					arraySunken[shotMem1][shotMem2] = '#' + 3;
					shipLength = 3;
				}

				if (ship5 == 5 || ship4 == 4 || ship3 == 3 || ship2 == 2) {

					if (ship5 == 5)
					{
						ship5 += 1;
					}

					if (ship4 == 4)
					{
						ship4 += 1;
					}

					if (ship3 == 3)
					{
						ship3 += 1;
					}

					if (ship2 == 2)
					{
						ship2 += 1;
					}

					shipStatus = 1;
					for (int i = 0; i < 7; i++) {

						for (int k = 0; k < 7; k++) {

							if (arraySunken[i][k] == '#' + shipLength) {

								arrayShots[i][k] = '#';
							}
						}
					}
				}

				hits += 1;
			}

		}
		else {
			arrayShots[shotMem1][shotMem2] = 'x';
		}

		if (hits == maxHits) {
			system("cls");
			cout << "You sunk every ship!" << endl;
			value = 1;
		}
	}
	printMenu();
}

void setShips() {
	/*
	name: setShips
	function: ask user for ship starpoint and direction, checks validity of coordinates by calling other functions, saves ships into arrayShips
	parameters: none
	return values: none
	*/
	memset(arrayShips, 0, sizeof(arrayShips[0][0]) * ROW * COL); 
	memset(arrayShots, 0, sizeof(arrayShots[0][0]) * ROW * COL);
	memset(arraySunken, 0, sizeof(arraySunken[0][0]) * ROW * COL);

	int rowCoordinate, colCoordinate;
	int shipLength;
	int var1 = 0;
	int shipNumber = 0;
	string shipStartPos;
	char shipDirection;

	while (var1 == 0) {

		if (shipNumber == 0) {
			cout << "Enter the starting point of 5 long ship (e.g. A1): " << endl;
			shipLength = 5;
		}

		cin >> shipStartPos;

		for (int i = 0; i < 2; i++) {
			shipStartPos[i] = toupper(shipStartPos[i]);
		}

		cout << "Give ship direction(P = North, E = South, I = East, L = West): ";

		cin >> shipDirection;

		shipDirection = tolower(shipDirection);

		rowCoordinate = shipStartPos[0] - 65;
		colCoordinate = shipStartPos[1] - 49;

		if (shipStartPos.size() == 2) {

			if (rowCoordinate <= 6 && rowCoordinate >= 0 && colCoordinate >= 0 && colCoordinate <= 6) {

				if (checkShip(rowCoordinate, colCoordinate) == 1) {

					if (checkDirection(rowCoordinate, colCoordinate, shipLength, shipDirection) == 1) {

						if (checkOverlap(rowCoordinate, colCoordinate, shipLength, shipDirection) == 1) {

							for (int i = 0; i < 5 - shipNumber; i++) {

								if (shipDirection == 'p') {
									arrayShips[rowCoordinate - i][colCoordinate] = '#' + shipNumber;
								}

								if (shipDirection == 'e') {
									arrayShips[rowCoordinate + i][colCoordinate] = '#' + shipNumber;
								}

								if (shipDirection == 'i') {
									arrayShips[rowCoordinate][colCoordinate + i] = '#' + shipNumber;
								}
								if (shipDirection == 'l') {
									arrayShips[rowCoordinate][colCoordinate - i] = '#' + shipNumber;
								}
							}
							shipNumber += 1;
							if (shipNumber == 1)
							{
								cout << "Enter the starting point of 4 long ship (e.g. A1): ";
								shipLength = 4;
							}
							if (shipNumber == 2)
							{
								cout << "Enter the starting point of 3 long ship (e.g. A1): ";
								shipLength = 3;
							}
							if (shipNumber == 3)
							{
								cout << "Enter the starting point of 2 long ship (e.g. A1): ";
								shipLength = 2;
							}
							if (shipNumber == 4)
							{
								printMenu();
							}
						}
						else cout << "Ship overlaps with another, enter new coordinates: " << endl;
					}
					else cout << "Ship cannot exceed board limits, enter new coordinates: " << endl;
				}
				else cout << "Starting point has a ship in it, enter new coordinates: " << endl;
			}
			else cout << "Ship cannot be placed outside board limits, enter new coordinates: " << endl;
		}
		else cout << "Faulty input.. Enter new coordinates: " << endl;
	}
}

void printShots() {
	/*
	name: printShots
	function: prints out board and shots from arrayShots
	parameters: none
	return values: none
	*/
	cout << "Current game situation" << endl;
	char a = 'A';
	for (int i = 0; i < 7; a++, i++)
	{
		if (i == 0)
		{
			cout << "  1 2 3 4 5 6 7" << endl;
			cout << "  --------------" << endl;
		}
		cout << a << '|';
		for (int j = 0; j < 7; j++)
		{
			cout << arrayShots[i][j] << " ";
		}
		cout << '|' << a;
		cout << endl;
		if (i == 6)
		{
			cout << "  --------------" << endl;
			cout << "  1 2 3 4 5 6 7" << endl;
		}
	}
	cout << endl << "Enter P to pause the game." << endl;
}

void printShipPositions() {
	/*
	name: printShipPositions
	function: prints out positions of placed ships when "@" is entered as shooting coordinate, so called "Spy-Mode"
	parameters: none
	return values: none
	*/
	cout << "You entered SPY-MODE" << endl;
	char a = 'A';
	for (int i = 0; i < 7; a++, i++)
	{
		if (i == 0)
		{
			cout << "  1 2 3 4 5 6 7" << endl;
			cout << "  --------------" << endl;
		}
		cout << a << '|';
		for (int j = 0; j < 7; j++)
		{
			cout << arrayShips[i][j] << " ";
		}
		cout << '|' << a;
		cout << endl;
		if (i == 6)
		{
			cout << "  --------------" << endl;
			cout << "  1 2 3 4 5 6 7" << endl;
		}
	}
	cout << endl << "Enter shooting coordinate to exit SPY-MODE (e.g. A1): ";
}

bool checkShip(int row, int col) {
	/*
	name: checkShip
	function: checks coordinate for ships returns true if ships is in this coordinate
	parameters: int row and int col, coordinate positions
	return values: true, false
	*/
	if (arrayShips[row][col] == 0)
	{
		return true;
	}
	else return false;
}

bool checkShot(int row, int col) {
	/*
	name: checkShot
	function: checks coordinate for shots returns true if ships is in this coordinate
	parameters: int row and int col, coordinate positions
	return values: true, false
	*/
	if (arrayShots[row][col] == 0)
	{
		return true;
	}
	else return false;
}

bool checkDirection(int rowCoordinate, int colCoordinate, int shipLength, char shipDirection) {
	/*
	name: checkDirection
	function: checks that ships will not be placed outside of the play area.
	parameters: int coordinate positions, int ship length and char direction
	return values: true, false
	*/
	if (shipDirection == 'p')
	{
		if ((rowCoordinate - shipLength) >= -1)
		{
			return true;
		}
		else return false;
	}
	if (shipDirection == 'e')
	{
		if ((rowCoordinate + shipLength) <= 7)
		{
			return true;
		}
		else return false;
	}
	if (shipDirection == 'i')
	{
		if ((colCoordinate + shipLength) <= 8)
		{
			return true;
		}
		else return false;
	}
	if (shipDirection == 'l')
	{
		if ((colCoordinate - shipLength) >= -1)
		{
			return true;
		}
		else return false;
	}
}

bool checkOverlap(int rowCoordinate, int colCoordinate, int shipLength, char shipDirection) {
	/*
	name: checkOverlap
	function: checks that ships will not be placed on top of each other.
	parameters: int coordinate positions, int ship length and char direction
	return values: true, false
	*/
	if (checkShip(rowCoordinate, colCoordinate) == 1)
	{
		if (shipDirection == 'p')
		{
			for (int i = 0; i < shipLength; i++)
			{
				if (checkShip((rowCoordinate - i), colCoordinate) == 0)
				{
					return false;
				}
				if (i + 1 == shipLength)
				{
					return true;
				}
			}
		}
		if (shipDirection == 'e')
		{
			for (int i = 0; i < shipLength; i++)
			{
				if (checkShip(rowCoordinate + i, colCoordinate) == 0)
				{
					return false;
				}
				if (i + 1 == shipLength)
				{
					return true;
				}
			}
		}
		if (shipDirection == 'i')
		{
			for (int i = 0; i < shipLength; i++)
			{
				if (checkShip(rowCoordinate, colCoordinate + i) == 0)
				{
					return false;
				}
				if (i + 1 == shipLength)
				{
					return true;
				}
			}
		}
		if (shipDirection == 'l')
		{
			for (int i = 0; i < shipLength; i++)
			{
				if (checkShip(rowCoordinate, colCoordinate - i) == 0)
				{
					return false;
				}
				if (i + 1 == shipLength)
				{
					return true;
				}
			}
		}
	}
	else return false;
}

