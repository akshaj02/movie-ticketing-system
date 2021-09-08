//Name: Akshaj Murhekar
//Movie Theater Ticekting Program

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_ROWS 9
#define MAX_COLS 9
#define TICKET_LIMIT 4

int numRow;
int numCol;
char arrSeat[MAX_ROWS*MAX_COLS];
char seatMap[MAX_ROWS][MAX_COLS];
void FillMovieTheater(char seatMap[MAX_ROWS][MAX_COLS], int numRow, int numCol, char arrSeat[MAX_ROWS*MAX_COLS]);
void PrintSeatMap(char seatMap[numRow][MAX_COLS], int numRow, int numCol);
int IsSeatSold(char seatMap[MAX_ROWS][MAX_COLS], int numRow, int numCol);
void WriteMovieTheater(char seatMap[MAX_ROWS][MAX_COLS], int numRow, int numCol);

void FillMovieTheater(char seatMap[MAX_ROWS][MAX_COLS], int numRow, int numCol, char arrSeat[MAX_ROWS*MAX_COLS])
{   int k=0;
    for (int i = 0; i < numRow; i++)
    {
        for (int j = 0; j < numCol; j++)
        {
            seatMap[i][j] = arrSeat[k];
            k++;
        }
    }
}

void PrintSeatMap(char seatMap[MAX_ROWS][MAX_COLS], int numRow, int numCol)
{
    printf("       ");
    for (int i = 1; i <= numCol; i++)
    {
        printf("%5d", i);
    }
    printf("\n");
    printf("       ");

    for (int i = 1; i <= numCol; i++)
    {
        printf("-----");
    }
    printf("\n");


    for (int i = 0; i < numRow; i++)
    {
        char rowAplha[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O',
        'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
        printf("Row %c |", rowAplha[i]);
        for (int j = 0; j < numCol; j++)
        {
            printf("%5c", seatMap[i][j]);
        }
        printf("\n");

    }

}

int IsSeatSold(char seatMap[MAX_ROWS][MAX_COLS], int ArrRow, int ArrCol)
{
    int flag;
    if(seatMap[ArrRow][ArrCol] == 'X')
    {
        flag = 1;
    } else
    {
        flag = 0;
        seatMap[ArrRow][ArrCol] = 'X';
    }

    return flag;
}

void WriteMovieTheater(char seatMap[MAX_ROWS][MAX_COLS], int numRow, int numCol)
{
    char filename[] = {};
    FILE *OutputFile = NULL;

    printf("Enter output filename: ");
    scanf("%s", filename);

    OutputFile = fopen(filename, "w+");

    if (OutputFile == NULL)
    {
        printf("File did not open properly. Exiting.");
        exit(0);
    }
    else
    {

    }
    fprintf(OutputFile, "%d %d\n", numRow, numCol);

    for (int i = 0; i < numRow; i++)
    {
        for (int j = 0; j < numCol; j++)
        {
            fprintf(OutputFile, "%c", seatMap[i][j]);
        }
    }

}

int main(void)
{
    int ticket;
    int tktSold=0;
    int ArrayRow;
    int ArrayCol;
    int ArrRow;
    int ArrCol;
    char usrRow;
    int usrSeat;
    char MovieTheater[MAX_ROWS][MAX_COLS] = {};

    FILE *InputFile;
    char filename[100] = {};
    char arrSeat[MAX_ROWS*MAX_COLS] = {};

    char rowCol[10];
    printf("Enter the Movie Theater file name: ");
    scanf("%s", filename);

    InputFile = fopen(filename, "w");

    if (InputFile == NULL)
    {
        printf("File did not open properly! Exiting");
        exit(0);
    }
    else
    {
        printf("All files opened\n");
    }

    fscanf(InputFile, "%d %d ", &ArrRow, &ArrCol);
    int line;
    for(line = 1; line < 3; line++)
    {
        fgets(arrSeat, MAX_ROWS*MAX_COLS-1, InputFile);
    }


    FillMovieTheater(MovieTheater, ArrRow, ArrCol, arrSeat);

    printf("How many tickets would you like to purchase? (limit %d) ", TICKET_LIMIT);
    scanf("%d", &ticket);

    while(ticket > TICKET_LIMIT)
    {
        printf("This is a special showing - limit of %d tickets per purchase\n", TICKET_LIMIT);
        printf("How many tickets would you like to purchase? (limit %d) ", TICKET_LIMIT);
        scanf("%d", &ticket);
    }

    if (ticket == 0)
    {
        printf("No movie for you!\n");
    }
    else
    {
        while(tktSold < ticket)
        {
            PrintSeatMap(MovieTheater, ArrRow, ArrCol);
            printf("Enter seat choice by entering row and seat\n");
            printf("Pick a seat ");
            scanf(" %c%d", &usrRow, &usrSeat);
            ArrayRow = toupper(usrRow) - 'A';
            ArrayCol = usrSeat -1;

            if (ArrayRow > ArrRow || ArrayCol > ArrCol)
			{
				printf("This seat is not in this theater!!\n");
			}
			else if (IsSeatSold(MovieTheater, ArrayRow, ArrayCol))
			{
			    printf("Seat %c%d is already sold. Pick a different seat.\n", usrRow, usrSeat);
			}
			else
			{
          tktSold++;
			}


        }
        printf("Please find your way to your seats using this map...\n");

        PrintSeatMap(MovieTheater, ArrRow, ArrCol);

        printf("Enjoy your movie!\n");

    }
    WriteMovieTheater(MovieTheater, ArrRow, ArrCol);
}
