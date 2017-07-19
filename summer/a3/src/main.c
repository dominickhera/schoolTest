#include "heap.h"
#include "functions.h"

#define character "X"
#define wall '=';

int main(int argc, char* argv[])
{

    char * fileName = argv[1];
    char line[256];
    char tempID[256];
    char tempPriority[50];
    char tempSymptomCode[50];
    int parseCount = 0;
    int c;
    int v;
    int cycle = 0;
    int maxX;
    int maxY;
    int y = 0;
    int x = 0;
    int prevX;
    int prevY;
    FILE *fp;
    FILE *fo;

    char * menuOptions[] = {"Add New Client", "Remove Client", "Cycle through Clients", "Print List", "Exit"}; 
    int tempMenuNumb[7];
    if(argc != 2)
    {
        printf("wrong amount of arguements entered\n");
        exit(1);
    }

    fp = fopen(fileName, "r");
    fo = fopen("./assets/report.txt", "w");

    if(fp == NULL)
    {
        printf("invalid data file\n");
        exit(1);
    }

    Heap * heap = createHeap(500, MIN_HEAP, &free, &printData, &compareFunction);

    while(fgets(line, sizeof(line), fp) != NULL)
    {
        char * parse;

        if(line[strlen(line) - 1] == '\n')
        {
            line[strlen(line) - 1] = '\0';
        }

        if(strcmp(line, "\0") != 0)
        {

            parse = strtok(line, " ");

            strcpy(tempID, parse);


            while((parse = strtok(NULL, " ")) != NULL)
            {
                if(parseCount == 0)
                {
                    strcpy(tempPriority, parse);
                    parseCount++;
                }
                else
                {
                    strcpy(tempSymptomCode, parse);
                    parseCount--;
                }

            }

            insertHeapNode(heap, atoi(tempPriority), tempID, tempSymptomCode);
        }

        memset(tempID, 0, strlen(line));
        memset(tempPriority, 0, strlen(line));
        memset(tempSymptomCode, 0, strlen(line));

    }

    fclose(fp);


    initscr();
    noecho();
    getmaxyx(stdscr,maxY,maxX);

    makeMainMenu(maxX, maxY);

    for(int i = 1; i < 6; i++)
    {
        makeMainMenuOptions(maxX, maxY, i, menuOptions[i - 1]);

    }

    mvprintw((maxY/8),5,character);
    move((maxY/8),5);


    c = getch();

    while (c != 'q')
    {

        if(c == 'w') 
        {
            // clearTextLine(((maxY/6)*2) + 5 , (((maxX/6) * 2) - 5));
            getPos(&y,&x);
            if(y > 1) 
            {
                if((y - (maxY/8)) > 1)
                {

                    printw(" "); 
                    mvprintw((y - (maxY/8)), (x),character);
                    move(y - (maxY/8) , x);
                }
            }

        }
        else if(c == 's')
        {
            // clearTextLine(((maxY/6)*2) + 5 , (((maxX/6) * 2) - 5));
            getPos(&y,&x);
            if(y < (maxY - (maxY/8)))
            {
                if((y + (maxY/8)) < ((maxY/3) * 2))
                {
                    printw(" ");
                    mvprintw((y+(maxY/8)), x,character);
                    move((y + (maxY/8)), x);
                }
            }

        }
        else if(c == '\n')
        {

            getPos(&y, &x);

            prevY = y;
            prevX = x;
            for(int i = 1; i < 7; i++)
            {
                tempMenuNumb[i] = (maxY/8) * i;
            }

            for(int i = 0; i < maxX; i++)
            {
                mvaddch(((maxY/3)*2) + 3, i, ' ');
            }

            if(y == tempMenuNumb[1])
            {
                echo();
                clearTextLine((((maxY/3)*2) + 2),0);
                memset(tempID, 0, strlen(tempID));
                memset(tempPriority, 0, strlen(tempPriority));
                memset(tempSymptomCode, 0, strlen(tempSymptomCode));
                clearMainMenu(maxX, maxY);
                mvprintw(((maxY/6)*2) , (((maxX/6) * 2) - 5), "%s", "enter clientID : ");
                getstr(tempID);
                clearTextLine(((maxY/6)*2) , (((maxX/6) * 2) - 5));
                mvprintw(((maxY/6)*2) , (((maxX/6) * 2) - 5), "%s", "enter new client priority : ");
                getstr(tempPriority);
                clearTextLine(((maxY/6)*2) , (((maxX/6) * 2) - 5));
                mvprintw(((maxY/6)*2) , (((maxX/6) * 2) - 5), "%s", "enter symptom Code: ");
                getstr(tempSymptomCode);
                clearTextLine(((maxY/6)*2) + 5 , (((maxX/6) * 2) - 5));
                insertHeapNode(heap, atoi(tempPriority), tempID, tempSymptomCode);
                clearTextLine(((maxY/6)*2) , (((maxX/6) * 2) - 5));

                for(int i = 1; i < 6; i++)
                {
                    makeMainMenuOptions(maxX, maxY, i, menuOptions[i - 1]);

                }
            }
            else if(y == tempMenuNumb[2])
            {
                echo();
                clearMainMenu(maxX, maxY);
                memset(tempID, 0, 256);
                clearTextLine((((maxY/3)*2) + 2),0);
                mvprintw(((maxY/6)*2) , (((maxX/6) * 2) - 5), "%s","enter clientID you'd like to delete from the list. : ");
                getstr(tempID);
                clearTextLine(((maxY/6)*2) + 5 , (((maxX/6) * 2) - 5));
                deleteHeapNode(heap, tempID);

                for(int i = 1; i < 6; i++)
                {
                    makeMainMenuOptions(maxX, maxY, i, menuOptions[i - 1]);

                }
                makeMainMenu(maxX, maxY);
            }
            else if (y == tempMenuNumb[3])
            {
               echo();
               clearMainMenu(maxX, maxY);
			   mvprintw(5, (maxX / 2) - 7, "Client %d of %zu", cycle + 1, heap->initialSize);
			   mvprintw(3, (maxX / 2) - 18, "< A | D >   X - return to main menu");
               mvprintw(((maxY/6)*2) , (((maxX/6) * 2)), "Client ID: %s, Priority: %d, Symptom Code: %s\n", heap->heapTable[cycle]->clientID, heap->heapTable[cycle]->priority, heap->heapTable[cycle]->symptomCode);
               
                v = getch();

                while(v != 'x')
                {
                	if(v == 'd')
                	{
                		cycle++;
            	        if(cycle > heap->initialSize - 1)
                	    {
                    	    cycle = 0;
                    	}
                    	mvprintw(5, (maxX / 2) - 7, "Client %d of %zu", cycle + 1, heap->initialSize);
                    	mvprintw(((maxY/6)*2) , (((maxX/6) * 2)), "Client ID: %s, Priority: %d, Symptom Code: %s\n",  heap->heapTable[cycle]->clientID, heap->heapTable[cycle]->priority, heap->heapTable[cycle]->symptomCode);
                	}
                	else if(v == 'a')
                	{
                		cycle--;
            	        if(cycle < 0)
                	    {
                    	    cycle = heap->initialSize - 1;
                    	}
                    	mvprintw(5, (maxX / 2) - 7, "Client %d of %zu", cycle + 1, heap->initialSize);
                		mvprintw(((maxY/6)*2) , (((maxX/6) * 2)), "Client ID: %s, Priority: %d, Symptom Code: %s\n",  heap->heapTable[cycle]->clientID, heap->heapTable[cycle]->priority, heap->heapTable[cycle]->symptomCode);
                	}
                	else
                	{
                		noecho();
                	}

                	refresh();
                	v = getch();

                }
                clearTextLine(((maxY/6)*2) , (((maxX/6) * 2)));
                clearTextLine(5, (maxX / 2) - 7);
                clearTextLine(3, (maxX / 2) - 18);

                for(int i = 1; i < 6; i++)
                {
                    makeMainMenuOptions(maxX, maxY, i, menuOptions[i - 1]);

                }
                
                makeMainMenu(maxX, maxY);
    }
    else if(y == tempMenuNumb[4])
    {
        echo();
        clearMainMenu(maxX, maxY);


        for(int i = 1; i < 6; i++)
        {
            makeMainMenuOptions(maxX, maxY, i, menuOptions[i - 1]);

        }
        makeMainMenu(maxX, maxY);
    }
    else if(y == tempMenuNumb[5])
    {

        fp = fopen(fileName, "w");
        printf("Exiting...\n");
        fprintf(fo, "Client List (in Order Processed)\n\n");
        printHeap(heap, fo, 1);
        printHeap(heap, fp, 0);
        deleteHeap(heap);
        fclose(fp);
        fclose(fo);
        endwin();
        break;
    }
    else
    {
        printf("error");
    }

    noecho();
    mvprintw(prevY, prevX,character);
    move(prevY, prevX);

}

refresh();
c = getch();
}
endwin();

// 		case 3:
// 			// printf("go through heap from top to bottom\n");
//             // if(cycle >= heap->initialSize)
//             // {
//                 cycleCheck = 0;
//             // }
//             while(cycleCheck != 3)
//             {
//                 printf("<(1):(2)> Exit(3)\n\n/> ");
//                 scanf("%d", &cycleCheck);
//             switch(cycleCheck)
//             {
//                 // printf("<(1):(2)> Exit(3)\n\n");
//                 // scanf("%d", &cycleCheck);
//                 case 1:
//                     cycle--;
//                     if(cycle < 0)
//                     {
//                         cycle = heap->initialSize - 1;
//                     }
//                     // printf("cycle: %d\n", cycle);
//                     printf("[%d/%zu]: Client ID: %s, Priority: %d, Symptom Code: %s\n", cycle + 1, heap->initialSize, heap->heapTable[cycle]->clientID, heap->heapTable[cycle]->priority, heap->heapTable[cycle]->symptomCode);
//                     // cycle--;
//                     break;
//                 case 2:
//                     cycle++;
//                     if(cycle > heap->initialSize - 1)
//                     {
//                         cycle = 0;
//                     }
//                     // printf("cycle: %d\n", cycle);
//                     printf("[%d/%zu]: Client ID: %s, Priority: %d, Symptom Code: %s\n", cycle + 1, heap->initialSize, heap->heapTable[cycle]->clientID, heap->heapTable[cycle]->priority, heap->heapTable[cycle]->symptomCode);
//                     // cycle++;
//                     break;
//                 case 3:
//                     break;
//                 default:
//                     break;
//             }
//         }
//             // printf("[%d/%zu]: Client ID: %s, Priority: %d, Symptom Code: %s\n", cycle + 1, heap->initialSize, heap->heapTable[cycle]->clientID, heap->heapTable[cycle]->priority, heap->heapTable[cycle]->symptomCode);
// 			// cycle++;
//             break;
// 		case 4:
// 			// printf("printing list\n");
//             printHeap(heap, fo, 2);
// 			break;
// 		case 5:
//             // char tempMaxorMin[256];
// 			printf("heaipfy\n");
//             reheapifyMin(heap, 0);
//             // Node * tempMaxorMin = getMaxorMin(heap);
//             // printf("temp: %s\n", tempMaxorMin->clientID);
//             // getMaxorMin(heap);

return 0;
}
