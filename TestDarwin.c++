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

TEST(Darwin, specie1_def) {
	Specie x1('f');
    ASSERT_TRUE(x1.name == 'f');
}

TEST(Darwin, specie1_add_instr) {
	Specie food('f');
	food.addInstruction("left");
    food.addInstruction("go 0");
    ASSERT_TRUE(food.instructions[0] == "left");
}

TEST(Darwin, specie1_is_equal) {
	Specie food('f');
	food.addInstruction("left");
    food.addInstruction("go 0");
    Specie hopper('h');
    ASSERT_TRUE(!hopper.is_equal(food));
}

// ---------
// Creature 
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



TEST(Darwin, darwin1_const) {
	Specie food('f');
	food.addInstruction("left");
    food.addInstruction("go 0");

    Darwin darwin1(8, 8);
    ASSERT_TRUE(darwin1.grid[0][0].max_row == 0);
    ASSERT_TRUE(darwin1.grid[0][0].max_col == 0);
    ASSERT_TRUE(darwin1.grid[0][0].cr_grid == NULL);
}

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