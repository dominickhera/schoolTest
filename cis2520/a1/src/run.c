// #include <string.h>
// #include <stdlib.h>
// #include <stdio.h>
 #include "run.h"

int main(void)
{
	// char str[] = "Carbon";
	// int string = strlen(str);
	int userChoice = 0;
	struct timeval startTime;
	struct timeval endTime;
	unsigned long long int startMicros;
	unsigned long long int endMicros;
	unsigned long long int deltaMicros;
	while (userChoice != 4)
	{
		printf("(1) carbon scramble\n(2) ackermann's function\n(3) newton's method\n(4) exit\nenter a number: ");
		scanf("%d", &userChoice);

		switch(userChoice)
		{
			case 1:
				carbonInit();
				// switcharoni(str, 0, string-1);
				printf("\n");
				break;
			case 2:
				ackermannInit();
				break;
			case 3:
				printf("you picked 3\n");
				gettimeofday(&startTime);
				/* do stuff */
				gettimeofday(&endTime);

				startMicros = (1000000 * startTime.tv_sec) + startTime.tv_usec;
				endMicros = (1000000 * endTime.tv_sec) + endTime.tv_usec;
				deltaMicros = endMicros - startMicros;
				break;
			case 4:
				printf("goodbye\n");
				exit(1);
			default:
				printf("enter a number between 1-4\n");
				break;
		}
	}
		return 0;
}