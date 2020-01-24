#pragma once

void printMenu();
void setShips();
void shotFunction();
void printShots();
void printShipPositions();

bool checkShip(int, int);
bool checkShot(int, int);
bool checkOverlap(int, int, int, char);
bool checkDirection(int, int, int, char);

#pragma once