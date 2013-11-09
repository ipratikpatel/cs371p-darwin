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


    // Helper function to generate random creatures
void addRandomCreature (Darwin& d, Specie& s, int height, int width)
{
        int pos = rand() % (height * width);
        int row = pos / height;
        int col = pos % height;
        int dir = static_cast<int> (rand() % 4) + 1;
        d.add_creature(row, col, s, dir);
}

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


     // ----
    // best
    // ----

      Specie best('b');

     best.addInstruction("if_enemy 8");
     best.addInstruction("if_empty 6");
     best.addInstruction("left");
     best.addInstruction("go 0");
     best.addInstruction("right");
     best.addInstruction("go 0");
     best.addInstruction("hop");
     best.addInstruction("go 0");
     best.addInstruction("infect");
     best.addInstruction("go 0");

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
            cout << endl;
            for (int i = 1; i <= 5; ++i)
            {
              cout << "Turn : " << i << endl;
                darwin1.darwin_turn();
                darwin1.print();
                cout << endl;
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
                cout << endl;
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
        cout << "*** Center Death Trap 8x8 ***" << endl;
        srand(0);
        Darwin d(8, 8);
        d.add_creature(0, 0, rover, EAST);
        d.add_creature( 7, 2, rover,NORTH);
        d.add_creature( 7, 6,rover, SOUTH);
        d.add_creature( 1, 6,rover, SOUTH); 
        d.add_creature( 3, 3,trap, NORTH);
        d.add_creature( 3, 4,trap, EAST);  
        d.add_creature( 4, 3,trap, WEST);  
        d.add_creature( 4, 4,trap, SOUTH);  
        const int NUM_MOVES = 200;
        cout << "Turn = " << 0 << "." << endl;
        d.print();
        std::cout << std::endl;
        for (int i = 1; i <= NUM_MOVES; ++i) {
            d.darwin_turn();
            if (i % 10 == 0) {
                cout << "Turn = " << i << "." << endl;
                d.print();
                std::cout << endl;
            }
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
        Darwin d(72, 72);
        const int NUM_CREATURES = 10;
        for (int i = 0; i < NUM_CREATURES; ++i)
            addRandomCreature (d, food, 72, 72);
        for (int i = 0; i < NUM_CREATURES; ++i)
            addRandomCreature (d, hopper, 72, 72);
        for (int i = 0; i < NUM_CREATURES; ++i)
            addRandomCreature (d, rover, 72, 72);
        for (int i = 0; i < NUM_CREATURES; ++i)
            addRandomCreature (d, trap, 72, 72);
        for (int i = 0; i < NUM_CREATURES; ++i)
            addRandomCreature (d, best, 72, 72);

        int NUM_MOVES = 9;
        cout << "Turn = " << 0 << "." << endl;
        d.print();
        std::cout << std::endl;
        for (int i = 1; i <= NUM_MOVES; ++i) {
          cout << "Turn = " << i << "." << endl;
            d.darwin_turn();
            d.print();
            std::cout << endl;
        }

        NUM_MOVES = 1000;
        for (int i = 10; i <= NUM_MOVES; ++i) {
            d.darwin_turn();
            if (i % 100 == 0) {
              cout << "Turn = " << i << "." << endl;
                d.print();
                std::cout << endl;
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
        Darwin d(72, 72);
        const int NUM_CREATURES = 5;
        for (int i = 0; i < NUM_CREATURES; ++i)
            addRandomCreature (d, food, 72, 72);
        for (int i = 0; i < NUM_CREATURES; ++i)
            addRandomCreature (d, hopper, 72, 72);
        for (int i = 0; i < NUM_CREATURES; ++i)
            addRandomCreature (d, rover, 72, 72);
        for (int i = 0; i < NUM_CREATURES; ++i)
            addRandomCreature (d, trap, 72, 72);
        for (int i = 0; i < NUM_CREATURES; ++i)
            addRandomCreature (d, best, 72, 72);

        int NUM_MOVES = 9;
        cout << "Turn = " << 0 << "." << endl;
        d.print();
        std::cout << std::endl;
        for (int i = 1; i <= NUM_MOVES; ++i) {
          cout << "Turn = " << i << "." << endl;
            d.darwin_turn();
            d.print();
            std::cout << endl;
        }

        NUM_MOVES = 1000;
        for (int i = 10; i <= NUM_MOVES; ++i) {
            d.darwin_turn();
            if (i % 100 == 0) {
              cout << "Turn = " << i << "." << endl;
                d.print();
                std::cout << endl;
            }
        }
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}



      // ------------------
    // Rover Takeover 8x8
    // ------------------

    try {
        cout << "*** Rover Takeover 8x8 ***" << endl;
        srand(0);
                                /*        
                                8x8 Darwin
                                Rover, facing south at (3, 4)
                                Food, facing south at (0, 2)
                                Food, facing south at (7, 4)
                                Food, facing south at (2, 7)
                                Food, facing north at (3, 0)
                                Food, facing north at (4, 5)
                                Food, facing north at (5, 2)
                                Food, facing north at (6, 3)
                                Simulate 100 moves
                                Print first 10 moves and multiples of 10
                                */
                                Darwin d(8, 8);
                                d.add_creature(3, 4, rover, 4);
                                d.add_creature(0, 2, food, 4);
                                d.add_creature(7, 4, food, 4);
                                d.add_creature(2, 7, food, 4);
                                d.add_creature(3, 0, food, 2);
                                d.add_creature(4, 5, food, 2);
                                d.add_creature(5, 2, food, 2);
                                d.add_creature(6, 3, food, 2);

                                cout << "Turn = " << 0 << "." << endl;
                                d.print();
                                for (int i = 1; i <= 100; i++){
                                        d.darwin_turn();
                                        if (i < 10 || i % 10 == 0)
                                        { cout << "Turn = " << i << "." << endl;
                                                d.print();
                                                std::cout << endl;
                                        }
                                }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}


  //*****************************ensign Test cases *********************************
            try {
            cout << "*** Rover 1x1 ***" << endl;
            srand(0);
                                    /*        
                                    1x1 Darwin
                                    Rover, facing north at (0, 0)
                                    Simulate 10 moves
                                    Print every move
                                    */
                                    Darwin d(1, 1);
                                    d.add_creature(0, 0, rover, 1);
                                    cout << "Turn = " << 0 << "." << endl;
                                    d.print();
                                    cout << endl;
                                    for (int i = 1; i <= 10; i++){
                                            d.darwin_turn();
                                            cout << "Turn = " << i << "." << endl;
                                            d.print();
                                            cout << endl;        
                        }
                    }
        catch (const invalid_argument&) {
            assert(false);}
        catch (const out_of_range&) {
            assert(false);}

        // -------------------------
        // Full Grid, 1 Trap 20x20
        // -------------------------

        try {
            cout << "*** Full Grid, 1 Trap 20x20 ***" << endl;
            srand(0);
                                    /*        
                                    20x20 Darwin
                                    1 Trap, facing west at (10, 10)
                                    399 Food, facing north at each location except (10, 10)
                                    Simulate 50 moves
                                    Print first 10 moves and every multiple of 10
                                    */
                                    Darwin d(20, 20);
                        
                                    d.add_creature(10, 10,trap, 1);
                                    for (int i = 0; i < 20; i++){
                                            for (int j = 0; j < 20; j++){
                                                    if (!(i == 10 && j == 10)){
                                                          d.add_creature( i, j, food, 2);
                                                    }
                                            }
                                    }
                                    cout << "Turn = " << 0 << "." << endl;
                                    d.print();
                                    cout << endl;
                                    for (int i = 1; i <= 50; i++){
                                            d.darwin_turn();
                                            if ((i < 10) || (i % 10 == 0))
                                            { cout << "Turn = " << i << "." << endl;
                                                    d.print();   
                                              }     
                                    }
        }
        catch (const invalid_argument&) {
            assert(false);}
        catch (const out_of_range&) {
            assert(false);}


        try {
        cout << "*** Hopper Collide 10x4 ***" << endl;
        srand(0);
                                /*        
                                10x4 Darwin
                                4 Hoppers, facing south in each column of row 0
                                4 Hoppers, facing north in each column of row 9
                                Simulate 10 moves
                                Print every move
                                */
                                Darwin d(10, 4);
                                
                                d.add_creature(0, 0, hopper, 4);
                                d.add_creature(0, 1, hopper, 4);
                                d.add_creature(0, 2, hopper, 4);
                                d.add_creature(0, 3, hopper, 4);
                                d.add_creature(9, 0, hopper, 2);
                                d.add_creature(9, 1, hopper, 2);
                                d.add_creature(9, 2, hopper, 2);
                                d.add_creature(9, 3, hopper, 2);
                                cout << "Turn = " << 0 << "." << endl;
                                d.print();
                                cout << endl;
                                for (int i = 1; i <= 10; i++){
                                        d.darwin_turn();
                                        cout << "Turn = " << i << "." << endl;
                                        d.print();
                                }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}


    // ------------------
    // Rover Takeover 8x8
    // ------------------

    try {
        cout << "*** Rover Takeover 8x8 ***" << endl;
        srand(0);
                                /*        
                                8x8 Darwin
                                Rover, facing south at (3, 4)
                                Food, facing south at (0, 2)
                                Food, facing south at (7, 4)
                                Food, facing south at (2, 7)
                                Food, facing north at (3, 0)
                                Food, facing north at (4, 5)
                                Food, facing north at (5, 2)
                                Food, facing north at (6, 3)
                                Simulate 100 moves
                                Print first 10 moves and multiples of 10
                                */
                                Darwin d(8, 8);
                                
                                d.add_creature(3, 4, rover, 4);
                                d.add_creature(0, 2, food, 4);
                                d.add_creature(7, 4, food, 4);
                                d.add_creature(2, 7, food, 4);
                                d.add_creature(3, 0, food, 2);
                                d.add_creature(4, 5, food, 2);
                                d.add_creature(5, 2, food, 2);
                                d.add_creature(6, 3, food, 2);
                                cout << "Turn = " << 0 << "." << endl;
                                d.print();
                                cout << endl;
                                for (int i = 1; i <= 100; i++){
                                        d.darwin_turn();
                                        if (i < 10 || i % 10 == 0)
                                          {cout << "Turn = " << i << "." << endl;    
                                            d.print();
                                            cout << endl;
                                          }
                                }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ------------------
    // Hop Down 10x1
    // ------------------

    try {
        cout << "*** Hop Down 10x1 ***" << endl;
        srand(0);
                                /*        
                                10x1 Darwin
                                Hopper, facing south at (0, 0)
                                Simulate 9 moves
                                Print every move
                                */
                                Darwin d(10, 1);
                               
                                d.add_creature(0, 0, hopper, 3);
                                cout << "Turn = " << 0 << "." << endl;  
                                d.print();
                                cout << endl;
                                for (int i = 1; i <= 9; i++){
                                        d.darwin_turn();
                                        cout << "Turn = " << i << "." << endl;  
                                        d.print();
                                        cout << endl;
                                }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ------------------
    // Hoppers Trapped 4x4
    // ------------------

    try {
        cout << "*** Hoppers Trapped 4x4 ***" << endl;
        srand(0);
                                /*        
                                4x4 Darwin
                                Hopper, facing east at (0, 0)
                                Hopper, facing south at (0, 1)
                                Hopper, facing west at (1, 1)
                                Hopper, facing north at (1, 0)
                                Simulate 10
                                Print every move
                                */
                                Darwin d(4, 4);
                                
                                d.add_creature( 0, 0, hopper, 3);
                                d.add_creature( 0, 1, hopper, 4);
                                d.add_creature( 1, 1, hopper, 1);
                                d.add_creature( 1, 0, hopper, 2);
                                cout << "Turn = " << 0 << "." << endl;  
                                d.print();
                                for (int i = 1; i <= 10; i++){
                                        d.darwin_turn();
                                        cout << "Turn = " << i << "." << endl;  
                                        d.print();
                                }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

// ************************************** DAVIDSCM *****************************************************

         // ------------
    // fod_walk_east 4x4
    // ------------
    // hoppers march in a line, like an aircraft carrier fod walk
    try {
        cout << "*** Fod Walk East 4x4 ***" << endl;
        Darwin d(4, 4);
        d.add_creature(0, 0, hopper, EAST);
        d.add_creature( 1, 0, hopper,EAST);
        d.add_creature( 2, 0, hopper, EAST);
        d.add_creature( 3, 0, hopper, EAST);
        const int NUM_MOVES = 5;
      cout << "Turn = " << 0 << "." << endl; 
        d.print();
        std::cout << std::endl;
        for (int i = 1; i <= NUM_MOVES; ++i) {
            d.darwin_turn();
            cout << "Turn = " << i << "." << endl;  
            d.print();
            std::cout << endl;
        }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ------------
    // fod_walk_north 4x4
    // ------------
    // hoppers march in a line, like an aircraft carrier fod walk
    try {
        cout << "*** Fod Walk North 4x4 ***" << endl;
        Darwin d(4, 4);
        d.add_creature( 3, 0, hopper,NORTH);
        d.add_creature( 3, 1,hopper, NORTH);
        d.add_creature(3, 2, hopper, NORTH);
        d.add_creature(3, 3, hopper, NORTH);
        const int NUM_MOVES = 5;
              cout << "Turn = " << 0 << "." << endl; 
        d.print();
        std::cout << std::endl;
        for (int i = 1; i <= NUM_MOVES; ++i) {
            d.darwin_turn();
            cout << "Turn = " << i << "." << endl;  
            d.print();
            std::cout << endl;
        }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}   

    // ------------
    // fod_walk_west 4x4
    // ------------
    // hoppers march in a line, like an aircraft carrier fod walk
    try {
        cout << "*** Fod Walk West 4x4 ***" << endl;
        Darwin d(4, 4);
        d.add_creature(0, 3, hopper, WEST);
        d.add_creature(1, 3, hopper, WEST);
        d.add_creature(2, 3, hopper, WEST);
        d.add_creature( 3, 3, hopper,WEST);
        const int NUM_MOVES = 5;
              cout << "Turn = " << 0 << "." << endl; 
        d.print();
        std::cout << std::endl;
        for (int i = 1; i <= NUM_MOVES; ++i) {
            d.darwin_turn();
            cout << "Turn = " << i << "." << endl;  
            d.print();
            std::cout << endl;
        }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}   

    // ------------
    // fod_walk_south 4x4
    // ------------
    // hoppers march in a line, like an aircraft carrier fod walk
    try {
        cout << "*** Fod Walk South 4x4 ***" << endl;
        Darwin d(4, 4);
        d.add_creature(0, 0, hopper, SOUTH);
        d.add_creature(0, 1, hopper, SOUTH);
        d.add_creature(0, 2, hopper, SOUTH);
        d.add_creature(0, 3, hopper, SOUTH);
        const int NUM_MOVES = 5;
              cout << "Turn = " << 0 << "." << endl; 
        d.print();
        std::cout << std::endl;
        for (int i = 1; i <= NUM_MOVES; ++i) {
            d.darwin_turn();
            cout << "Turn = " << i << "." << endl;  
            d.print();
            std::cout << endl;
        }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ------------
    // fod_walk_meet_in_middle 4x4
    // ------------
    // hoppers march in a line, like an aircraft carrier fod walk
    try {
        cout << "*** Fod Walk Meet In Middle 4x4 ***" << endl;
        Darwin d(4, 6);
        d.add_creature(0, 0, hopper,  EAST);
        d.add_creature(1, 0, hopper, EAST);
        d.add_creature(2, 0, hopper, EAST);
        d.add_creature(3, 0, hopper, EAST);
        d.add_creature(0, 5, hopper, WEST);
        d.add_creature(1, 5, hopper, WEST);
        d.add_creature(2, 5, hopper, WEST);
        d.add_creature(3, 5, hopper, WEST);
        const int NUM_MOVES = 4;
              cout << "Turn = " << 0 << "." << endl; 
        d.print();
        std::cout << std::endl;
        for (int i = 1; i <= NUM_MOVES; ++i) {
            d.darwin_turn();
            cout << "Turn = " << i << "." << endl;  
            d.print();
            std::cout << endl;
        }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}    

    // ------------
    // rover_tiny_board 1x1
    // ------------
    // Should be stuck but not crash
    try {
        cout << "*** Rover Tiny Board 1x1 ***" << endl;
        Darwin d(1, 1);
        d.add_creature(0, 0, rover, EAST);
        const int NUM_MOVES = 3;
              cout << "Turn = " << 0 << "." << endl; 
        d.print();
        std::cout << std::endl;
        for (int i = 1; i <= NUM_MOVES; ++i) {
            d.darwin_turn();
            cout << "Turn = " << i << "." << endl;  
            d.print();
            std::cout << endl;
        }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);} 

    // ------------
    // rover_tiny_board 2x2
    // ------------
    // Should bounce around in his cage
    try {
        cout << "*** Rover Tiny Board 2x2 ***" << endl;
        srand(0);
        Darwin d(2, 2);
        d.add_creature(0, 0, rover, EAST);
        const int NUM_MOVES = 100;
              cout << "Turn = " << 0 << "." << endl; 
        d.print();
        std::cout << std::endl;
        for (int i = 1; i <= NUM_MOVES; ++i) {
            d.darwin_turn();
            if (i % 10 == 0) {
                cout << "Turn = " << i << "." << endl;  
                d.print();
                std::cout << endl;
            }
        }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);} 

    // ------------
    // center death trap 8x8
    // ------------
    // 4 traps in the center wait for the rovers
    try {
        cout << "*** Center Death Trap 8x8 ***" << endl;
        srand(0);
        Darwin d(8, 8);
        d.add_creature(0, 0, rover, EAST);
        d.add_creature(7, 2, rover, NORTH);
        d.add_creature(7, 6, rover, SOUTH);
        d.add_creature(1, 6, rover, SOUTH); 
        d.add_creature(3, 3, trap, NORTH);
        d.add_creature(3, 4, trap, EAST);  
        d.add_creature(4, 3, trap, WEST);  
        d.add_creature(4, 4, trap, SOUTH);  
        const int NUM_MOVES = 200;
              cout << "Turn = " << 0 << "." << endl; 
        d.print();
        std::cout << std::endl;
        for (int i = 1; i <= NUM_MOVES; ++i) {
            d.darwin_turn();
            if (i % 10 == 0) {
                cout << "Turn = " << i << "." << endl;  
                d.print();
                std::cout << endl;
            }
        }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);} 

// temp***************************************ericsu-RunDarwin*****************************************************************

    // ------------
    // rover_skinny_board 8x1
    // ------------
    try {
        cout << "*** Rover Skinny Board 8x1 ***" << endl;
        srand(0);
        Darwin d(8, 1);
        d.add_creature(3, 0, rover, EAST);
        const int NUM_MOVES = 100;
              cout << "Turn = " << 0 << "." << endl; 
        d.print();
        std::cout << std::endl;
        for (int i = 1; i <= NUM_MOVES; ++i) {
            d.darwin_turn();
            if (i % 10 == 0) {
                cout << "Turn = " << i << "." << endl;  
                d.print();
                std::cout << endl;
            }
        }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);} 

    // ------------
    // rover_skinny_board 1x8
    // ------------
    try {
        cout << "*** Rover Skinny Board 8x1 ***" << endl;
        srand(0);
        Darwin d(1, 8);
        d.add_creature(0, 3, rover, EAST);
        const int NUM_MOVES = 100;
              cout << "Turn = " << 0 << "." << endl; 
        d.print();
        std::cout << std::endl;
        for (int i = 1; i <= NUM_MOVES; ++i) {
            d.darwin_turn();
            if (i % 10 == 0) {
                cout << "Turn = " << i << "." << endl;  
                d.print();
                std::cout << endl;
            }
        }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);} 

    //------------------------
    // center trap all 4 types
    //------------------------
    try {
        cout << "*** Center Trap All 4 Creatures 17x17 ***" << endl;
        srand(0);
        Darwin d(17, 17);
        const int NUM_CREATURES = 5;
        for (int i = 0; i < NUM_CREATURES; ++i)
            addRandomCreature (d, food, 17, 17);
        for (int i = 0; i < NUM_CREATURES; ++i)
            addRandomCreature (d, hopper, 17, 17);
        for (int i = 0; i < NUM_CREATURES; ++i)
            addRandomCreature (d, rover, 17, 17);

        // Center Trap
        d.add_creature(8, 8, trap, NORTH);
        d.add_creature(8, 9, trap, EAST);  
        d.add_creature(9, 8, trap, WEST);  
        d.add_creature(9, 9, trap, SOUTH); 
        d.add_creature(9, 9, trap, SOUTH); // Readding to same spot, shouldn't crash

        int NUM_MOVES = 9;
        cout << "Turn = " << 0 << "." << endl;  
        d.print();
        std::cout << std::endl;
        for (int i = 1; i <= NUM_MOVES; ++i) {
            d.darwin_turn();
            cout << "Turn = " << i << "." << endl;  
            d.print();
            std::cout << endl;
        }

        NUM_MOVES = 1000;
        for (int i = 10; i <= NUM_MOVES; ++i) {
            d.darwin_turn();
            if (i % 100 == 0) {
                cout << "Turn = " << i << "." << endl;  
                d.print();
                std::cout << endl;
            }
        }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

  // **********************************ethan-RunDarwin.c*******************************

    try {
        cout << "*** Darwin 8x8 Corners ***" << endl;
        /*
        8x8 Darwin
        Hopper, facing west, at (0, 3)
        Hopper, facing east,  at (0, 4)
        Hopper, facing west, at (7, 3)
        Hopper, facing east,  at (7, 4)
        Simulate 5 moves.
        Print every grid.
        */
        Darwin a(8, 8);
        
        a.add_creature(0, 3, hopper, WEST);
        a.add_creature(0, 4, hopper, EAST);
        a.add_creature(7, 3, hopper, WEST);
        a.add_creature(7, 4, hopper, EAST);

        
        cout << "Turn = " << 0 << "." << endl;  
                                        a.print();
                                        cout << endl;

        for (int i = 0; i < 5; i++) {
            a.darwin_turn();
           cout << "Turn = " << i << "." << endl;  
                                        a.print();
                                        cout << endl;
        }
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

        
        try {
        cout << "*** Darwin 8x8 Rover Around ***" << endl;
        /*
        8x8 Darwin
        Rover, facing south, at (0, 0)
        Food, facing east,  at (7, 0)
        Food, facing north, at (7, 7)
        Food, facing east,  at (0, 7)
        Simulate 25 moves.
        Print every grid.
        */
        Darwin a(8, 8);
        

        a.add_creature(0, 0, rover, SOUTH);
        a.add_creature(7, 0, food, EAST);
        a.add_creature(7, 7, food, NORTH);
        a.add_creature(0, 7, food, EAST);

        cout << "Turn = " << 0 << "." << endl;  
                                        a.print();
                                        cout << endl;

        for (int i = 0; i < 25; i++) {
            a.darwin_turn();
            cout << "Turn = " << i << "." << endl;  
                                        a.print();
                                        cout << endl;
        }
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

     try {
        cout << "*** Darwin 3x8 Guantlet***" << endl;
        /*
        3x8 Darwin
        Trap, facing south, at (0, 3)
        Trap, facing east,  at (0, 4)
        Trap, facing north, at (2, 3)
        Trap, facing east,  at (2, 4)
        Hopper, facing east,  at (1, 0)
        Simulate 10 moves.
        Print every grid.
        */
        Darwin a(3, 8);
        

        a.add_creature(0, 3, trap, SOUTH);
        a.add_creature(0, 4, trap, EAST);
        a.add_creature(2, 3, trap, NORTH);
        a.add_creature(2, 4, trap, EAST);
        a.add_creature(1, 0, hopper, EAST);

        cout << "Turn = " << 0 << "." << endl;  
                                        a.print();
                                        cout << endl;


        for (int i = 0; i < 10; i++) {
            a.darwin_turn();
            cout << "Turn = " << i << "." << endl;  
                                        a.print();
                                        cout << endl;
        }
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

// temp**************************************************idrepeng-RunDarwin****************************************************8
        try {
        cout << "*** Darwin 5x5 Trap!***" << endl;
        /*
        3x8 Darwin
        Trap, facing south, at (2, 2)
        Hopper, facing south,  at (0, 2)
        Hopper, facing west, at (2, 4)
        Hopper, facing north,  at (4, 2)
        Hopper, facing east,  at (2, 0)
        Simulate 10 moves.
        Print every grid.
        */
        Darwin a(5, 5);
        

        a.add_creature(2, 2, trap, SOUTH);
        a.add_creature(0, 2, hopper, SOUTH);
        a.add_creature(2, 4,hopper, WEST);
        a.add_creature(4, 2, hopper, NORTH);
        a.add_creature(2, 0, hopper, EAST);

        cout << "Turn = " << 0 << "." << endl;  
                                        a.print();
                                        cout << endl;


        for (int i = 0; i < 10; i++) {
            a.darwin_turn();
           cout << "Turn = " << i << "." << endl;  
                                        a.print();
                                        cout << endl;
        }
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}


        try {
        cout << "*** Darwin 3x3 infect all***" << endl;
        /*
        3x3 Darwin
        Trap, facing south, at (1, 1)
        Food, everywhere else, facing whatever direction
        Simulate 20 moves.
        Print first and last grid.
        */
        Darwin a(3, 3);
      

        a.add_creature(1, 1, rover, SOUTH);
        a.add_creature(0, 0, food, EAST);
        a.add_creature(0, 1, food, NORTH);
        a.add_creature(0, 2, food, EAST);
        a.add_creature(1, 0, food, EAST);
        a.add_creature(1, 2, food, EAST);
        a.add_creature(2, 0, food, NORTH);
        a.add_creature(2, 1, food, EAST);
        a.add_creature(2, 2, food, EAST);

        cout << "Turn = " << 0 << "." << endl;  
                                        a.print();
                                        cout << endl;


        for (int i = 0; i < 20; i++) {
            a.darwin_turn();
            cout << "Turn = " << i << "." << endl;  
                                        a.print();
                                        cout << endl;
        }
        
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}




    return 0;}
