/* cs480 Lab 6
by: Gracie Ceja
Whack a Mole Game using ncurses
first assigned: april 7, 2023
last modified: april 12, 2023 */

#include <stdio.h>  
#include <unistd.h>
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>


int main(){
    /* variable declaration section */
    /* strings for display: */
    char* title = "Whack-A-Mole!";
    char* instructions = "To whack a mole, type the hole number";
    char* score = "Score:";
    char* round = "Round:";
    char empty = '0';
    char mole = 'M';
    /* locations of mole holes: */
    /* holes:     0   1    2    3    4   5    6    7   8  9 */
    int rows[] = {15, 7,   8,   6,  16,  10,  9,  11, 14, 19};
    int cols[] = {25, 120, 90, 100, 110, 130, 61, 40, 50, 79};
    /* varibles for the rounds of the game */
    int i = 0;
    int molenum = -1;
    int roundnum = 0;
    int roundtime = 1;
    char answer;
    char* answerptr;
    int answerint = -1;
    int userscore = 0;
    // Intializes random number generator
    time_t t;
    srand((unsigned) time(&t));
    /* end variable declaration section */



    /* start the screen/window display */
    initscr();

    /* set up user interface for game */
    move(3, 81);    /* row 3, column 81 */
    printw("%s", title);
    move(4, 70);
    printw("%s", instructions);
    move(22, 20);
    printw("%s", score);
    move(22, 150);
    printw("%s", round);
    refresh();
    sleep(5);

    /* print all mole holes, play game (if block) after printing the third one */
    for(i = 0; i <= 9; i++){
        /* set up the holes */
        move(rows[i], cols[i]);
        attron(A_STANDOUT); // so the hole will stand out
        printw("%c", empty); /* empty hole */
        attroff(A_STANDOUT);
        move(rows[i] + 1, cols[i]);
        printw("%d", i);    /* hole number */


        /* playing the game */
        if(i >= 2){
            refresh();
            /* determine round number & display it to the user */
            roundnum = i - 1;
            move(23, 150);
            printw("%d", roundnum);
            refresh();

            /* select randomly which one will have the mole */
            while(molenum < 0 || molenum > i){
                molenum = rand() % 9;
            }
            move(rows[molenum], cols[molenum]);
            attron(A_STANDOUT); // so the mole will stand out
            printw("%c", mole); // mole 
            attroff(A_STANDOUT);


            // place where the user's input will be printed
            move(22, 75);  
            printw("user input:  ");
            /* determine how long the round will last */
            roundtime = 10 - (roundnum * 0.1);   /* 10 seconds in round 0, each round is 0.1s shorter than the previous one */
            halfdelay(roundtime * 10);  /* halfdelay input is 10ths of second, roundtime is in seconds */
            refresh();
            fflush(stdin);
            answer = getch();   /* due to halfdelay, it will wait the specified time for user input */
            answerptr = &answer;


            /* check user's answer & update score */
            if(answer == ERR || (answerint = atoi(answerptr)) != molenum){  /* user did not answer in time or correctly */
                if(userscore > 0){
                    userscore -= 1;
                }
            }
            else if(answerint == molenum){
                userscore++;
            }

            


            /* display score */
            move(23, 22);
            printw("%d", userscore);
            refresh();

            /* return hole back to no mole */
            move(rows[molenum], cols[molenum]);
            attron(A_STANDOUT); // so the mole will stand out
            printw("%c", empty); /* empty hole */
            attroff(A_STANDOUT);
            refresh();
            molenum = -1;
        }   // end if for playing the game
    }  // end of loop for printing holes & playing game
    refresh();
    sleep(10);
    
    
    endwin();
    exit(EXIT_SUCCESS);
}