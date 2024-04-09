Whack-a-Mole-game:

I created this simple text-based game for the lab 6 assignment in my Systems Programming class (CS 480 in Cal Poly Humboldt). I made it during April 7-12, 2023.
This game is written in C and uses the ncurses library to create a text-based user interface for the game.
In this game, there are some "holes" on the screen where moles can show up (a hole is represented as a 0 with a number below it). The mole is represented by an M in place of the zero for the hole. The player presses the key on their keyboard with the same number as that hole to whack the mole. The user can either gain or lose a point (down to a minimum score of zero) based on whether they chose the right number on time. The game ends when the user runs out of rounds.
