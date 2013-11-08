// -----------------------------
// projects/darwin/RunDarwin.c++
// Copyright (C) 2013
// Glenn P. Downing
// -----------------------------

/*
To run the program:
    % g++ -pedantic -std=c++0x -Wall Darwin.c++ RunDarwin.c++ -o RunDarwin
    % valgrind RunDarwin > RunDarwin.out

To configure Doxygen:
    doxygen -g
That creates the file Doxyfile.
Make the following edits:
    EXTRACT_ALL            = YES
    EXTRACT_PRIVATE        = YES
    EXTRACT_STATIC         = YES
    GENERATE_LATEX         = NO

To document the program:
    doxygen Doxyfile
*/

// --------
// includes
// --------

#include <cassert>   // assert
#include <cstdlib>   // rand, srand
#include <iostream>  // cout, endl
#include <stdexcept> // invalid_argument, out_of_range
#include "Darwin.h"

// ----
// main
// ----

int main () {
    using namespace std;

    // ----
    // food
    // ----

    /*
     0: left
     1: go 0
    */
     Specie food('f');
     food.addInstruction("left");
     food.addInstruction("go 0");
    // ------
    // hopper
    // ------

    /*
     0: hop
     1: go 0
    */
     Specie hopper('h');
     hopper.addInstruction("hop");
     hopper.addInstruction("go 0");

    // -----
    // rover
    // -----

    /*
     0: if_enemy 9
     1: if_empty 7
     2: if_random 5
     3: left
     4: go 0
     5: right
     6: go 0
     7: hop
     8: go 0
     9: infect
    10: go 0
    */
     Specie rover('r');
     rover.addInstruction("if_enemy 9");
     rover.addInstruction("if_empty 7");
     rover.addInstruction("if_random 5");
     rover.addInstruction("left");
     rover.addInstruction("go 0");
     rover.addInstruction("right");
     rover.addInstruction("go 0");
     rover.addInstruction("hop");
     rover.addInstruction("go 0");
     rover.addInstruction("infect");
     rover.addInstruction("go 0");

    // ----
    // trap
    // ----

    /*
     0: if_enemy 3
     1: left
     2: go 0
     3: infect
     4: go 0
    */
     Specie trap('t');
     trap.addInstruction("if_enemy 3");
     trap.addInstruction("left");
     trap.addInstruction("go 0");
     trap.addInstruction("infect");
     trap.addInstruction("go 0");

    // ----------
    // darwin 8x8
    // ----------

    try {
            cout << "*** Darwin 8x8 ***" << endl;
            /*
            8x8 Darwin
            Food,   facing east,  at (0, 0)
            Hopper, facing north, at (3, 3)
            Hopper, facing east,  at (3, 4)
            Hopper, facing south, at (4, 4)
            Hopper, facing west,  at (4, 3)
            Food,   facing north, at (7, 7)
            Simulate 5 moves.
            Print every grid.
            */
            Darwin darwin1(8, 8);
            //cout << " got darwin " << endl;
            //cout << "darwin1......instructions1" << food.instructions[0] << endl;
            darwin1.add_creature(0, 0, food, EAST);
            //cout << " Added first creture " << endl;
            darwin1.add_creature(3, 3, hopper, NORTH);
            darwin1.add_creature(3, 4, hopper, EAST);
            darwin1.add_creature(4, 4, hopper, SOUTH);
            darwin1.add_creature(4, 3, hopper, WEST);
            darwin1.add_creature(7, 7, food, NORTH);
            //cout << "Added last creature " << endl;

            cout << "Turn : " << 0 << endl;
            darwin1.print();
            for (int i = 1; i <= 5; ++i)
            {
              cout << "Turn : " << i << endl;
                darwin1.darwin_turn();
                darwin1.print();
            }
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ----------
    // darwin 7x9
    // ----------

    try {
        cout << "*** Darwin 7x9 ***" << endl;
        srand(0);
        /*
        7x9 Darwin
        Trap,   facing south, at (0, 0)
        Hopper, facing east,  at (3, 2)
        Rover,  facing north, at (5, 4)
        Trap,   facing west,  at (6, 8)
        Simulate 5 moves.
        Print every grid.
        */
        Darwin darwin1(7, 9);
            darwin1.add_creature(0, 0, trap, SOUTH);
            darwin1.add_creature(3, 2, hopper, EAST);
            darwin1.add_creature(5, 4, rover, NORTH);
            darwin1.add_creature(6, 8, trap, WEST);

            cout << "Turn = " << 0 << "." << endl;
            darwin1.print();
            for (int i = 1; i <= 5; ++i)
            {
              cout << "Turn = " << i << "." << endl;
                darwin1.darwin_turn();
                darwin1.print();
            }
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ------------
    // darwin 72x72
    // without best
    // ------------

    try {
        cout << "*** Darwin 72x72 without Best ***" << endl;
        srand(0);
        /*
        Randomly place the following creatures facing randomly.
        Call rand(), mod it with 5184 (72x72), and use that for the position
        in a row-major order grid.
        Call rand() again, mod it with 4 and use that for it's direction with
        the ordering: west, north, east, south.
        Do that for each kind of creature.
        10 Food
        10 Hopper
        10 Rover
        10 Trap
        Simulate 1000 moves.
        Print the first 10 grids          (i.e. 0, 1, 2...9).
        Print every 100th grid after that (i.e. 100, 200, 300...1000).
        */
          srand(0);
          Darwin grid(72, 72);
          for (int i = 0; i < 10; i++) 
          {
            int rand_num = rand();
            grid.add_creature(rand_num % 5184 / 72, rand_num % 5184 % 72, food, rand() % 4);
          }
          for (int i = 0; i < 10; i++) 
          {
            int rand_num = rand();
            grid.add_creature(rand_num % 5184 / 72, rand_num % 5184 % 72, hopper, rand() % 4);
          }
          for (int i = 0; i < 10; i++) 
          {
            int rand_num = rand();
            grid.add_creature(rand_num % 5184 / 72, rand_num % 5184 % 72, rover, rand() % 4);
          }
          for (int i = 0; i < 10; i++) 
          {
            int rand_num = rand();
            grid.add_creature(rand_num % 5184 / 72, rand_num % 5184 % 72, trap, rand() % 4);
          }
          cout << "Turn = 0.";
          grid.print();
          for (int i = 1; i <= 1000; ++i) 
          {
            grid.darwin_turn();
            if (i % 100 == 0)
            {
              cout << "Turn = " << i << ".";
              grid.print();
            }
          }
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ------------
    // darwin 72x72
    // with best
    // ------------

    try {
        cout << "*** Darwin 72x72 with Best ***" << endl;
        srand(0);
        /*
        Randomly place the following creatures facing randomly.
        Call rand(), mod it with 5184 (72x72), and use that for the position
        in a row-major order grid.
        Call rand() again, mod it with 4 and use that for it's direction with
        the ordering: 0:west, 1:north, 2:east, 3:south.
        Do that for each kind of creature.
        10 Food
        10 Hopper
        10 Rover
        10 Trap
        10 Best
        Simulate 1000 moves.
        Best MUST outnumber ALL other species for the bonus pts.
        Print the first 10 grids          (i.e. 0, 1, 2...9).
        Print every 100th grid after that (i.e. 100, 200, 300...1000).
        */
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    return 0;}
