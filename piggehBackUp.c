// Weo weo Dominick Hera  weo Weo//
// Weo weo    CIS1500     weo Weo//
// Weo weo  Assignment 1  weo Weo//
// Weo weo a game of pigs weo Weo//

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main(void) {

srand ((int)time(0));
char charAnswer = 'x' ;
char rollAnswer =  'x' ;
int gameTotal = 0;
int playerOneTotal = 0;
int playerTwoTotal = 0;
int randomNumber = 0;

printf("\nwelcome to a game  of pigthrones\n");
printf("---------------------------\n");
printf("  made by dominick hera   \n");
printf("\ndo you and your friend want to play a game? (y/n) :");
scanf("%c", &charAnswer);

if (charAnswer == 'y') {
printf("please set the game total: \n");
scanf("%d", &gameTotal);


printf("do you want to (r)oll or (h)old? : \n");

scanf("\n%c", &rollAnswer);

if (rollAnswer == 'r') {

randomNumber = ((rand() % 6) + 1);
//printf("%d\n", ((rand() % 6) + 1));
printf("%d\n", randomNumber);

switch (randomNumber) {
	case 0:
		printf("how the fuck did you even get here? Get the fuck out");
		break;

	case 1:
		if (playerOneTotal >= gameTotal) {
printf("Player one has won! weo weo weo\n");
} else if (playerTwoTotal >= gameTotal) {
printf("Player two has won! weo weo weo\n");
}
		break;


	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
		printf("TO BE CONTINUED");
		break;

	default:
		printf("default answer");
		break;}
} else if (rollAnswer == 'h') {
if (playerOneTotal >= gameTotal) {
printf("Player one wins! weo weo weo \n");
return 0;
} else if (playerTwoTotal >= gameTotal) {
printf("Player two wins! weo weo weo \n");
return 0;
} else {
printf("it's now the next players turn");
}
}
}
return 0;

}
