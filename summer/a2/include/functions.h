#ifndef _DHERA_FUNCTIONS_
#define _DHERA_FUNCTIONS_

#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include "HashTableAPI.h"

void printData(void * data);
int hashData(size_t hashSize, char * dataKey);
void clearTextLine(int x, int y);
void makeMainMenu(int maxX, int maxY);
void makeMainMenuOptions(int maxX, int maxY, int i, char * menuOptions);
void clearMainMenu(int maxX, int maxY);
void getPos(int *, int *);

#endif
