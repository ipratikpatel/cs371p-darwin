#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==

#include "gtest/gtest.h"

#include "Darwin.h"
#include "stdexcept"
// -----------
// TestDarwin
// -----------

// -------------
// specie 
// -------------


// -------------
// specie default
// -------------

TEST(Darwin, specie1_def) {
	Specie x1('f');
    ASSERT_TRUE(x1.name == 'f');
}

TEST(Darwin, specie2_def) {
    Specie x1('h');
    ASSERT_TRUE(x1.name == 'h');
}

TEST(Darwin, specie3_def) {
    Specie x1('r');
    ASSERT_TRUE(x1.name == 'r');
}

// -------------
// specie add_instruction
// -------------


TEST(Darwin, specie1_add_instr) {
	Specie food('f');
	food.addInstruction("left");
    food.addInstruction("go 0");
    ASSERT_TRUE(food.instructions[0] == "left");
}

TEST(Darwin, specie2_add_instr) {
    Specie food('f');
    food.addInstruction("left");
    food.addInstruction("go 0");
    ASSERT_TRUE(food.instructions[0] == "left");
    ASSERT_TRUE(food.instructions[1] == "go 0");
}

TEST(Darwin, specie3_add_instr) {
    Specie food('h');
    food.addInstruction("hop");
    food.addInstruction("go 0");
    ASSERT_TRUE(food.instructions[0] == "hop");
    ASSERT_TRUE(food.instructions[1] == "go 0");
}

// -------------
// specie is_equal
// -------------


TEST(Darwin, specie1_is_equal) {
	Specie food('f');
	food.addInstruction("left");
    food.addInstruction("go 0");
    Specie hopper('h');
    ASSERT_TRUE(!hopper.is_equal(food));
}

TEST(Darwin, specie2_is_equal) {
    Specie food('f');
    food.addInstruction("left");
    food.addInstruction("go 0");
    Specie food2('f');
    ASSERT_TRUE(food2.is_equal(food));
}

TEST(Darwin, specie3_is_equal) {
    Specie food('f');
    food.addInstruction("left");
    food.addInstruction("go 0");
    Specie rover('r');
    ASSERT_TRUE(!rover.is_equal(food));
}

// ---------
// Creature 
// ---------

// ---------
// Creature default 
// ---------

TEST(Darwin, creature1_def) {
	Creature x1;
    ASSERT_TRUE(x1.pc == 0);
    ASSERT_TRUE(x1.direction == WEST);
    ASSERT_TRUE(x1.cr_row == 0);
    ASSERT_TRUE(x1.cr_col == 0);
    ASSERT_TRUE(x1.max_row == 0);
    ASSERT_TRUE(x1.max_col == 0);
    ASSERT_TRUE(x1.cr_grid == NULL);

}

TEST(Darwin, creature2_def) {
    Creature x1;
    ASSERT_TRUE(x1.pc == 0);
    ASSERT_TRUE(x1.direction == WEST);
    ASSERT_TRUE(x1.cr_row == 0);
    ASSERT_TRUE(x1.cr_col == 0);
    ASSERT_TRUE(x1.max_row == 0);
    ASSERT_TRUE(x1.max_col == 0);
    ASSERT_TRUE(x1.cr_grid == NULL);

}

TEST(Darwin, creature3_def) {
    Creature x1;
    ASSERT_TRUE(x1.pc == 0);
    ASSERT_TRUE(x1.direction == WEST);
    ASSERT_TRUE(x1.cr_row == 0);
    ASSERT_TRUE(x1.cr_col == 0);
    ASSERT_TRUE(x1.max_row == 0);
    ASSERT_TRUE(x1.max_col == 0);
    ASSERT_TRUE(x1.cr_grid == NULL);

}

// ---------
// Creature constructor 
// ---------


TEST(Darwin, creature1_cons) {
	Specie food('f');
	food.addInstruction("left");
    food.addInstruction("go 0");

	Creature x1(SOUTH, food);
    ASSERT_TRUE(x1.pc == 0);
    ASSERT_TRUE(x1.direction == SOUTH);
    ASSERT_TRUE(x1.cr_row == 0);
    ASSERT_TRUE(x1.cr_col == 0);
    ASSERT_TRUE(x1.max_row == 0);
    ASSERT_TRUE(x1.max_col == 0);
    ASSERT_TRUE(x1.cr_grid == NULL);
    ASSERT_TRUE(x1.specie.is_equal(food));
}

TEST(Darwin, creature2_cons) {
	Specie food('f');
	food.addInstruction("left");
    food.addInstruction("go 0");

	Creature x1(SOUTH, food);
    ASSERT_TRUE(x1.pc == 0);
    ASSERT_TRUE(x1.direction == SOUTH);
    ASSERT_TRUE(x1.cr_row == 0);
    ASSERT_TRUE(x1.cr_col == 0);
    ASSERT_TRUE(x1.max_row == 0);
    ASSERT_TRUE(x1.max_col == 0);
    ASSERT_TRUE(x1.cr_grid == NULL);
    ASSERT_TRUE(x1.specie.is_equal(food));
    ASSERT_TRUE(x1.specie.instructions[0] == "left");

    Darwin darwin1(8, 8);
}

TEST(Darwin, creature3_cons) {
    Specie food('f');
    food.addInstruction("left");
    food.addInstruction("go 0");

    Creature x1(EAST, food);
    ASSERT_TRUE(x1.pc == 0);
    ASSERT_TRUE(x1.direction == EAST);
    ASSERT_TRUE(x1.cr_row == 0);
    ASSERT_TRUE(x1.cr_col == 0);
    ASSERT_TRUE(x1.max_row == 0);
    ASSERT_TRUE(x1.max_col == 0);
    ASSERT_TRUE(x1.cr_grid == NULL);
    ASSERT_TRUE(x1.specie.is_equal(food));
    ASSERT_TRUE(x1.specie.instructions[0] == "left");

    Darwin darwin1(8, 8);
}


// ---------
// Creature left() 
// ---------

TEST(Darwin, creature1_left) {
    Specie food('f');
    food.addInstruction("left");
    food.addInstruction("go 0");

    Creature x1(SOUTH, food);
    ASSERT_TRUE(x1.pc == 0);
    ASSERT_TRUE(x1.direction == SOUTH);
    ASSERT_TRUE(x1.cr_row == 0);
    ASSERT_TRUE(x1.cr_col == 0);
    ASSERT_TRUE(x1.max_row == 0);
    ASSERT_TRUE(x1.max_col == 0);
    ASSERT_TRUE(x1.cr_grid == NULL);
    ASSERT_TRUE(x1.specie.is_equal(food));
    ASSERT_TRUE(x1.specie.instructions[0] == "left");

    x1.left();
    ASSERT_TRUE(x1.direction == EAST);
    x1.left();
    ASSERT_TRUE(x1.direction == NORTH);
    x1.left();
    ASSERT_TRUE(x1.direction == WEST);
    x1.left();
    ASSERT_TRUE(x1.direction == SOUTH);

    Darwin darwin1(8, 8);
}

TEST(Darwin, creature2_left) {
    Specie food('f');
    food.addInstruction("left");
    food.addInstruction("go 0");

    Creature x1(EAST, food);
    ASSERT_TRUE(x1.pc == 0);
    ASSERT_TRUE(x1.direction == EAST);
    ASSERT_TRUE(x1.cr_row == 0);
    ASSERT_TRUE(x1.cr_col == 0);
    ASSERT_TRUE(x1.max_row == 0);
    ASSERT_TRUE(x1.max_col == 0);
    ASSERT_TRUE(x1.cr_grid == NULL);
    ASSERT_TRUE(x1.specie.is_equal(food));
    ASSERT_TRUE(x1.specie.instructions[0] == "left");

    x1.left();
    ASSERT_TRUE(x1.direction == NORTH);
    x1.left();
    ASSERT_TRUE(x1.direction == WEST);
    x1.left();
    ASSERT_TRUE(x1.direction == SOUTH);

    Darwin darwin1(8, 8);
}

TEST(Darwin, creature3_left) {
    Specie food('f');
    food.addInstruction("left");
    food.addInstruction("go 0");

    Creature x1(NORTH, food);
    ASSERT_TRUE(x1.pc == 0);
    ASSERT_TRUE(x1.direction == NORTH);
    ASSERT_TRUE(x1.cr_row == 0);
    ASSERT_TRUE(x1.cr_col == 0);
    ASSERT_TRUE(x1.max_row == 0);
    ASSERT_TRUE(x1.max_col == 0);
    ASSERT_TRUE(x1.cr_grid == NULL);
    ASSERT_TRUE(x1.specie.is_equal(food));
    ASSERT_TRUE(x1.specie.instructions[0] == "left");

    x1.left();
    ASSERT_TRUE(x1.direction == WEST);
    x1.left();
    ASSERT_TRUE(x1.direction == SOUTH);

    Darwin darwin1(8, 8);
}

// ---------
// Creature right() 
// ---------

TEST(Darwin, creature1_right) {
    Specie food('f');
    food.addInstruction("left");
    food.addInstruction("go 0");

    Creature x1(SOUTH, food);
    ASSERT_TRUE(x1.pc == 0);
    ASSERT_TRUE(x1.direction == SOUTH);
    ASSERT_TRUE(x1.cr_row == 0);
    ASSERT_TRUE(x1.cr_col == 0);
    ASSERT_TRUE(x1.max_row == 0);
    ASSERT_TRUE(x1.max_col == 0);
    ASSERT_TRUE(x1.cr_grid == NULL);
    ASSERT_TRUE(x1.specie.is_equal(food));
    ASSERT_TRUE(x1.specie.instructions[0] == "left");

    x1.right();
    ASSERT_TRUE(x1.direction == WEST);
    x1.right();
    ASSERT_TRUE(x1.direction == NORTH);
    x1.right();
    ASSERT_TRUE(x1.direction == EAST);
    x1.right();
    ASSERT_TRUE(x1.direction == SOUTH);
    

    Darwin darwin1(8, 8);
}

TEST(Darwin, creature2_right) {
    Specie food('f');
    food.addInstruction("left");
    food.addInstruction("go 0");

    Creature x1(NORTH, food);
    ASSERT_TRUE(x1.pc == 0);
    ASSERT_TRUE(x1.direction == NORTH);
    ASSERT_TRUE(x1.cr_row == 0);
    ASSERT_TRUE(x1.cr_col == 0);
    ASSERT_TRUE(x1.max_row == 0);
    ASSERT_TRUE(x1.max_col == 0);
    ASSERT_TRUE(x1.cr_grid == NULL);
    ASSERT_TRUE(x1.specie.is_equal(food));
    ASSERT_TRUE(x1.specie.instructions[0] == "left");

    x1.right();
    ASSERT_TRUE(x1.direction == EAST);
    x1.right();
    ASSERT_TRUE(x1.direction == SOUTH);
    

    Darwin darwin1(8, 8);
}

TEST(Darwin, creature3_right) {
    Specie food('f');
    food.addInstruction("left");
    food.addInstruction("go 0");

    Creature x1(WEST, food);
    ASSERT_TRUE(x1.pc == 0);
    ASSERT_TRUE(x1.direction == WEST);
    ASSERT_TRUE(x1.cr_row == 0);
    ASSERT_TRUE(x1.cr_col == 0);
    ASSERT_TRUE(x1.max_row == 0);
    ASSERT_TRUE(x1.max_col == 0);
    ASSERT_TRUE(x1.cr_grid == NULL);
    ASSERT_TRUE(x1.specie.is_equal(food));
    ASSERT_TRUE(x1.specie.instructions[0] == "left");

    x1.right();
    ASSERT_TRUE(x1.direction == NORTH);
    x1.right();
    ASSERT_TRUE(x1.direction == EAST);
    x1.right();
    ASSERT_TRUE(x1.direction == SOUTH);
    

    Darwin darwin1(8, 8);
}

// ---------
// Creature if_wall 
// ---------

TEST(Darwin, darwin1_if_wall) {
    Specie food('f');
    food.addInstruction("left");
    food.addInstruction("go 0");

    Darwin darwin1(2, 3);
    
    darwin1.add_creature(0, 0, food, WEST);
    ASSERT_TRUE(darwin1.grid[0][0].if_wall(3, false));
    ASSERT_TRUE(darwin1.grid[0][0].pc == 3);

    darwin1.add_creature(0, 1, food, NORTH);
    ASSERT_TRUE(darwin1.grid[0][1].if_wall(3, true));

    darwin1.add_creature(0, 2, food, NORTH);
    ASSERT_TRUE(darwin1.grid[0][2].if_wall(3, false));
    ASSERT_TRUE(darwin1.grid[0][2].pc == 3);
    
    darwin1.add_creature(1, 0, food, SOUTH);
    ASSERT_TRUE(darwin1.grid[1][0].if_wall(3, false));
    ASSERT_TRUE(darwin1.grid[1][0].pc == 3);

    darwin1.add_creature(1, 1, food, SOUTH);
    ASSERT_TRUE(darwin1.grid[1][1].if_wall(3, false));
    ASSERT_TRUE(darwin1.grid[1][1].pc == 3);

    darwin1.add_creature(1, 2, food, EAST);
    ASSERT_TRUE(darwin1.grid[1][2].if_wall(3, true));
    ASSERT_TRUE(darwin1.grid[1][2].pc == 0);
    
}



TEST(Darwin, darwin2_if_wall) {
    Specie food('f');
    food.addInstruction("left");
    food.addInstruction("go 0");

    Darwin darwin1(2, 3);
    
    darwin1.add_creature(1, 2, food, EAST);
    ASSERT_TRUE(darwin1.grid[1][2].if_wall(3, true));
    ASSERT_TRUE(darwin1.grid[1][2].pc == 0);
    
    darwin1.add_creature(1, 0, food, SOUTH);
    ASSERT_TRUE(darwin1.grid[1][0].if_wall(3, false));
    ASSERT_TRUE(darwin1.grid[1][0].pc == 3);

    darwin1.add_creature(1, 1, food, SOUTH);
    ASSERT_TRUE(darwin1.grid[1][1].if_wall(3, false));
    ASSERT_TRUE(darwin1.grid[1][1].pc == 3);

    
}

TEST(Darwin, darwin3_if_wall) {
    Specie food('f');
    food.addInstruction("left");
    food.addInstruction("go 0");

    Darwin darwin1(2, 3);
    
    darwin1.add_creature(1, 2, food, EAST);
    ASSERT_TRUE(darwin1.grid[1][2].if_wall(3, true));
    ASSERT_TRUE(darwin1.grid[1][2].pc == 0);
    
    darwin1.add_creature(1, 0, food, SOUTH);
    ASSERT_TRUE(darwin1.grid[1][0].if_wall(3, false));
    ASSERT_TRUE(darwin1.grid[1][0].pc == 3);

        
}

// ---------
// Creature if_empty 
// ---------


TEST(Darwin, darwin1_if_empty) {
    Specie food('f');
    food.addInstruction("left");
    food.addInstruction("go 0");

    Specie hopper('h');
    food.addInstruction("hop");
    food.addInstruction("go 0");

    Darwin darwin1(2, 3);
    
    darwin1.add_creature(0, 0, food, EAST);    
    darwin1.add_creature(1, 0, hopper, NORTH);
    darwin1.add_creature(1, 1, food, WEST);
    ASSERT_TRUE(!darwin1.grid[1][0].if_empty(3, true));
    ASSERT_TRUE(darwin1.grid[1][0].pc == 0);
        
}

TEST(Darwin, darwin2_if_empty) {
    Specie food('f');
    food.addInstruction("left");
    food.addInstruction("go 0");

    Specie hopper('h');
    food.addInstruction("hop");
    food.addInstruction("go 0");

    Darwin darwin1(2, 3);
    
    darwin1.add_creature(0, 0, food, EAST);    
    darwin1.add_creature(1, 0, hopper, NORTH);
    darwin1.add_creature(1, 1, food, WEST);
    ASSERT_TRUE(darwin1.grid[0][0].if_empty(3, false));
    ASSERT_TRUE(darwin1.grid[0][0].pc == 3);
        
}

TEST(Darwin, darwin3_if_empty) {
    Specie food('f');
    food.addInstruction("left");
    food.addInstruction("go 0");

    Specie hopper('h');
    food.addInstruction("hop");
    food.addInstruction("go 0");

    Darwin darwin1(2, 3);
    
    darwin1.add_creature(0, 0, food, EAST);    
    darwin1.add_creature(1, 0, hopper, NORTH);
    darwin1.add_creature(1, 1, food, WEST);
    ASSERT_TRUE(!darwin1.grid[1][1].if_empty(3, true));
    ASSERT_TRUE(darwin1.grid[1][1].pc == 0);
        
}

// ---------
// Creature if_enemy 
// ---------

TEST(Darwin, darwin1_if_enemy) {
    Specie food('f');
    food.addInstruction("left");
    food.addInstruction("go 0");

    Specie hopper('h');
    food.addInstruction("hop");
    food.addInstruction("go 0");

    Darwin darwin1(2, 3);
    
    darwin1.add_creature(0, 0, food, EAST);  
    darwin1.add_creature(0, 1, food, EAST);    
    darwin1.add_creature(1, 0, hopper, NORTH);
    darwin1.add_creature(1, 1, food, WEST);
    ASSERT_TRUE(darwin1.grid[1][1].if_enemy(3, true));
    ASSERT_TRUE(darwin1.grid[1][1].pc == 0);
        
}

TEST(Darwin, darwin2_if_enemy) {
    Specie food('f');
    food.addInstruction("left");
    food.addInstruction("go 0");

    Specie hopper('h');
    food.addInstruction("hop");
    food.addInstruction("go 0");

    Darwin darwin1(2, 3);
    
    darwin1.add_creature(0, 0, food, EAST);  
    darwin1.add_creature(0, 1, food, EAST);    
    darwin1.add_creature(1, 0, hopper, NORTH);
    darwin1.add_creature(1, 1, food, WEST);
    ASSERT_TRUE(!darwin1.grid[0][0].if_enemy(3, true));
    ASSERT_TRUE(darwin1.grid[0][0].pc == 0);
        
}

TEST(Darwin, darwin3_if_enemy) {
    Specie food('f');
    food.addInstruction("left");
    food.addInstruction("go 0");

    Specie hopper('h');
    food.addInstruction("hop");
    food.addInstruction("go 0");

    Darwin darwin1(2, 3);
    
    darwin1.add_creature(0, 0, food, EAST);  
    darwin1.add_creature(0, 1, food, EAST);    
    darwin1.add_creature(1, 0, hopper, NORTH);
    darwin1.add_creature(1, 1, food, WEST);
    ASSERT_TRUE(!darwin1.grid[0][1].if_enemy(3, true));
    ASSERT_TRUE(darwin1.grid[0][1].pc == 0);
        
}


// ---------
// Creature hop 
// ---------

TEST(Darwin, darwin1_hop) {
    Specie food('f');
    food.addInstruction("left");
    food.addInstruction("go 0");

    Specie hopper('h');
    food.addInstruction("hop");
    food.addInstruction("go 0");

    Darwin darwin1(2, 3);
    
    darwin1.add_creature(0, 1, food, EAST);    
    darwin1.add_creature(1, 0, hopper, NORTH);
    darwin1.add_creature(1, 1, food, WEST);
    darwin1.grid[1][0].hop();
    ASSERT_TRUE(darwin1.grid[0][0].max_col == 3);
    ASSERT_TRUE(darwin1.grid[0][0].pc == 1);
    ASSERT_TRUE(darwin1.grid[1][0].max_col == 0);
    ASSERT_TRUE(darwin1.grid[1][0].pc == 0);
        
}

TEST(Darwin, darwin2_hop) {
    Specie food('f');
    food.addInstruction("left");
    food.addInstruction("go 0");

    Specie hopper('h');
    food.addInstruction("hop");
    food.addInstruction("go 0");

    Darwin darwin1(2, 3);
    
    darwin1.add_creature(0, 0, food, EAST); 
    darwin1.add_creature(0, 1, food, EAST);    
    darwin1.add_creature(1, 0, hopper, NORTH);
    darwin1.add_creature(1, 1, food, WEST);
    darwin1.grid[1][0].hop();
    ASSERT_TRUE(darwin1.grid[0][0].max_col == 3);
    ASSERT_TRUE(darwin1.grid[0][0].pc == 0);
    ASSERT_TRUE(darwin1.grid[1][0].max_col == 3);
    ASSERT_TRUE(darwin1.grid[1][0].pc == 1);
        
}

TEST(Darwin, darwin3_hop) {
    Specie food('f');
    food.addInstruction("left");
    food.addInstruction("go 0");

    Specie hopper('h');
    food.addInstruction("hop");
    food.addInstruction("go 0");

    Darwin darwin1(2, 3);
    
    darwin1.add_creature(0, 0, food, EAST); 
    darwin1.add_creature(0, 1, food, EAST);    
    darwin1.add_creature(1, 0, hopper, NORTH);
    darwin1.add_creature(1, 1, food, WEST);
    darwin1.grid[1][0].left();
    darwin1.grid[1][0].hop();
    ASSERT_TRUE(darwin1.grid[0][0].max_col == 3);
    ASSERT_TRUE(darwin1.grid[0][0].pc == 0);
    ASSERT_TRUE(darwin1.grid[1][0].max_col == 3);
    ASSERT_TRUE(darwin1.grid[1][0].pc == 2);
    ASSERT_TRUE(darwin1.grid[1][0].specie.name == 'h');
        
}

// ---------
// Creature infect 
// ---------

TEST(Darwin, darwin1_infect) {
    Specie food('f');
    food.addInstruction("left");
    food.addInstruction("go 0");

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

    Darwin darwin1(2, 3);
    
    darwin1.add_creature(0, 0, food, EAST);  
    darwin1.add_creature(0, 1, food, EAST);    
    darwin1.add_creature(1, 0, rover, NORTH);
    darwin1.add_creature(1, 1, food, WEST);
    darwin1.grid[1][0].infect();
    ASSERT_TRUE(darwin1.grid[0][0].max_col == 3);
    ASSERT_TRUE(darwin1.grid[0][0].pc == 0);
    ASSERT_TRUE(darwin1.grid[0][0].specie.name == 'r');
    ASSERT_TRUE(darwin1.grid[1][0].max_col == 3);
    ASSERT_TRUE(darwin1.grid[1][0].pc == 1);
    ASSERT_TRUE(darwin1.grid[1][0].specie.name == 'r');
        
}

TEST(Darwin, darwin2_infect) {
    Specie food('f');
    food.addInstruction("left");
    food.addInstruction("go 0");

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

    Darwin darwin1(2, 3);
    
    darwin1.add_creature(0, 1, food, EAST);    
    darwin1.add_creature(1, 0, rover, NORTH);
    darwin1.add_creature(1, 1, food, WEST);
    darwin1.grid[1][0].infect();
    ASSERT_TRUE(darwin1.grid[0][0].max_col == 0);
    ASSERT_TRUE(darwin1.grid[0][0].pc == 0);
    ASSERT_TRUE(darwin1.grid[0][0].specie.name == ' ');
    ASSERT_TRUE(darwin1.grid[1][0].max_col == 3);
    ASSERT_TRUE(darwin1.grid[1][0].pc == 1);
    ASSERT_TRUE(darwin1.grid[1][0].specie.name == 'r');
        
}

TEST(Darwin, darwin3_infect) {
    Specie food('f');
    food.addInstruction("left");
    food.addInstruction("go 0");

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

    Darwin darwin1(2, 3);
    
    darwin1.add_creature(0, 1, food, EAST);    
    darwin1.add_creature(1, 0, rover, WEST);
    darwin1.add_creature(1, 1, food, WEST);
    darwin1.grid[1][0].infect();
    ASSERT_TRUE(darwin1.grid[0][0].max_col == 0);
    ASSERT_TRUE(darwin1.grid[0][0].pc == 0);
    ASSERT_TRUE(darwin1.grid[0][0].specie.name == ' ');
    ASSERT_TRUE(darwin1.grid[1][0].max_col == 3);
    ASSERT_TRUE(darwin1.grid[1][0].pc == 1);
    ASSERT_TRUE(darwin1.grid[1][0].specie.name == 'r');
        
}

// ---------
// Creature take_action() 
// ---------

TEST(Darwin, creature1_take_action) {
    Specie food('f');
    food.addInstruction("left");
    food.addInstruction("go 0");

    Creature x1(SOUTH, food);
    ASSERT_TRUE(x1.pc == 0);
    ASSERT_TRUE(x1.direction == SOUTH);
    ASSERT_TRUE(x1.specie.is_equal(food));
    ASSERT_TRUE(x1.specie.instructions[0] == "left");

    x1.creature_action("right");
    ASSERT_TRUE(x1.direction == WEST);
    
}

TEST(Darwin, darwin2_take_action) {
    Specie food('f');
    food.addInstruction("left");
    food.addInstruction("go 0");

    Specie hopper('h');
    food.addInstruction("hop");
    food.addInstruction("go 0");

    Darwin darwin1(2, 3);
    
    darwin1.add_creature(0, 1, food, EAST);    
    darwin1.add_creature(1, 0, hopper, NORTH);
    darwin1.add_creature(1, 1, food, WEST);
    darwin1.grid[1][0].creature_action("hop");
    ASSERT_TRUE(darwin1.grid[0][0].max_col == 3);
    ASSERT_TRUE(darwin1.grid[0][0].pc == 1);
    ASSERT_TRUE(darwin1.grid[1][0].max_col == 0);
    ASSERT_TRUE(darwin1.grid[1][0].pc == 0);
        
}

TEST(Darwin, darwin3_take_action) {
    Specie food('f');
    food.addInstruction("left");
    food.addInstruction("go 0");

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

    Darwin darwin1(2, 3);
    
    darwin1.add_creature(0, 0, food, EAST);  
    darwin1.add_creature(0, 1, food, EAST);    
    darwin1.add_creature(1, 0, rover, NORTH);
    darwin1.add_creature(1, 1, food, WEST);
    darwin1.grid[1][0].creature_action("infect");
    ASSERT_TRUE(darwin1.grid[0][0].max_col == 3);
    ASSERT_TRUE(darwin1.grid[0][0].pc == 0);
    ASSERT_TRUE(darwin1.grid[0][0].specie.name == 'r');
    ASSERT_TRUE(darwin1.grid[1][0].max_col == 3);
    ASSERT_TRUE(darwin1.grid[1][0].pc == 1);
    ASSERT_TRUE(darwin1.grid[1][0].specie.name == 'r');
        
}

//TODO: run_creature.....
// ---------
// Creature run_creature 
// ---------

/*TEST(Darwin, darwin1_run_creature) {
    Specie food('f');
    food.addInstruction("left");
    food.addInstruction("go 0");

    Specie hopper('h');
    food.addInstruction("hop");
    food.addInstruction("go 0");

    Darwin darwin1(2, 3);
    
    darwin1.add_creature(0, 1, food, EAST);    
    darwin1.add_creature(1, 0, hopper, NORTH);
    darwin1.add_creature(1, 1, food, WEST);
    darwin1.grid[1][0].run_creature();
    ASSERT_TRUE(darwin1.grid[0][0].max_col == 3);
    ASSERT_TRUE(darwin1.grid[0][0].pc == 1);
    ASSERT_TRUE(darwin1.grid[1][0].max_col == 0);
    ASSERT_TRUE(darwin1.grid[1][0].pc == 0);
        
}*/



// ---------
// Darwin constructor 
// ---------

TEST(Darwin, darwin1_const) {
	Specie food('f');
	food.addInstruction("left");
    food.addInstruction("go 0");

    Darwin darwin1(8, 8);
    ASSERT_TRUE(darwin1.grid[0][0].max_row == 0);
    ASSERT_TRUE(darwin1.grid[0][0].max_col == 0);
    ASSERT_TRUE(darwin1.grid[0][0].cr_grid == NULL);
}

TEST(Darwin, darwin2_const) {
     Darwin darwin1(8, 8);
    ASSERT_TRUE(darwin1.grid[7][7].max_row == 0);
    ASSERT_TRUE(darwin1.grid[7][7].max_col == 0);
    ASSERT_TRUE(darwin1.grid[7][7].cr_grid == NULL);
}

TEST(Darwin, darwin3_const) {
    Darwin darwin1(8, 8);
    ASSERT_TRUE(darwin1.grid[1][1].max_row == 0);
    ASSERT_TRUE(darwin1.grid[1][1].max_col == 0);
    ASSERT_TRUE(darwin1.grid[1][1].cr_grid == NULL);
}


// ---------
// Darwin add_creature
// ---------


TEST(Darwin, darwin1_add_creature) {
	Specie food('f');
	food.addInstruction("left");
    food.addInstruction("go 0");

    Darwin darwin1(8, 8);
    ASSERT_TRUE(darwin1.grid[0][0].max_row == 0);
    ASSERT_TRUE(darwin1.grid[0][0].max_col == 0);
    ASSERT_TRUE(darwin1.grid[0][0].cr_grid == NULL);
    darwin1.add_creature(0, 0, food, NORTH);
    ASSERT_TRUE(darwin1.grid[0][0].pc == 0);
    ASSERT_TRUE(darwin1.grid[0][0].direction == NORTH);
    ASSERT_TRUE(darwin1.grid[0][0].cr_row == 0);
    ASSERT_TRUE(darwin1.grid[0][0].cr_col == 0);
    ASSERT_TRUE(darwin1.grid[0][0].max_row == 8);
    ASSERT_TRUE(darwin1.grid[0][0].max_col == 8);
    vector<vector<Creature> > *temp_grid; 
    temp_grid = &darwin1.grid;
    ASSERT_TRUE(darwin1.grid[0][0].cr_grid == temp_grid);
    ASSERT_TRUE(darwin1.grid[0][0].specie.is_equal(food));
    ASSERT_TRUE(darwin1.grid[0][0].specie.instructions[0] == "left");
    ASSERT_TRUE((*(darwin1.grid[0][0].cr_grid))[0][1].max_row == 0);
    ASSERT_TRUE((*(darwin1.grid[0][0].cr_grid))[0][1].max_col == 0);
    ASSERT_TRUE((*(darwin1.grid[0][0].cr_grid))[0][1].cr_row == 0);
    ASSERT_TRUE((*(darwin1.grid[0][0].cr_grid))[0][1].cr_col == 0);
}

TEST(Darwin, darwin2_add_creature) {
    Specie food('f');
    food.addInstruction("left");
    food.addInstruction("go 0");

    Darwin darwin1(8, 8);
    ASSERT_TRUE(darwin1.grid[0][0].max_row == 0);
    ASSERT_TRUE(darwin1.grid[0][0].max_col == 0);
    ASSERT_TRUE(darwin1.grid[0][0].cr_grid == NULL);
    darwin1.add_creature(0, 0, food, NORTH);
    ASSERT_TRUE(darwin1.grid[0][0].pc == 0);
    ASSERT_TRUE(darwin1.grid[0][0].direction == NORTH);
    ASSERT_TRUE(darwin1.grid[0][0].cr_row == 0);
    ASSERT_TRUE(darwin1.grid[0][0].cr_col == 0);
    ASSERT_TRUE(darwin1.grid[0][0].max_row == 8);
    ASSERT_TRUE(darwin1.grid[0][0].max_col == 8);
}

TEST(Darwin, darwin3_add_creature) {
    Specie food('f');
    food.addInstruction("left");
    food.addInstruction("go 0");

    Darwin darwin1(8, 8);
    ASSERT_TRUE(darwin1.grid[0][0].max_row == 0);
    ASSERT_TRUE(darwin1.grid[0][0].max_col == 0);
    ASSERT_TRUE(darwin1.grid[0][0].cr_grid == NULL);
    darwin1.add_creature(0, 0, food, NORTH);
    vector<vector<Creature> > *temp_grid; 
    temp_grid = &darwin1.grid;
    ASSERT_TRUE(darwin1.grid[0][0].cr_grid == temp_grid);
    ASSERT_TRUE(darwin1.grid[0][0].specie.is_equal(food));
    ASSERT_TRUE(darwin1.grid[0][0].specie.instructions[0] == "left");
    ASSERT_TRUE((*(darwin1.grid[0][0].cr_grid))[0][1].max_row == 0);
    ASSERT_TRUE((*(darwin1.grid[0][0].cr_grid))[0][1].max_col == 0);
    ASSERT_TRUE((*(darwin1.grid[0][0].cr_grid))[0][1].cr_row == 0);
    ASSERT_TRUE((*(darwin1.grid[0][0].cr_grid))[0][1].cr_col == 0);
}

