#ifndef DARWIN_H
#define DARWIN_H
// --------
// includes
// --------

#include <cassert>   // assert
#include <cstdlib>   // rand, srand
#include <iostream>  // cout, endl
#include <stdexcept> // invalid_argument, out_of_range
#include <string>
#include <sstream>
#include <vector>


#define WEST 1
#define NORTH 2
#define EAST 3
#define SOUTH 4

using namespace std;
class Specie
{
	
	public:
		vector<string> instructions;
		char name;
		
		/**
		* Specie Default constructor
		*/
		Specie();

		/**
		* Specie char constructor
		*/
		Specie(const char c);

		/**
		* Add instruction s to specie's instruction vector
		* @param s a string
		*/
		void addInstruction(string s);

		/**
		* Checks if rhs is the same specie as lhs
		* @param s a string
		* @return true if they are same specie, false otherwise
		*/
		bool is_equal(const Specie& rhs);
};

class Creature
{
	public:
	// Program counter tell which instruction to execute next
	int pc;
	// Keeps direction where creature is facing
	int direction;
	// Specie of the creature
	Specie specie;
	// What row this creature is in the darwin grid
	size_t cr_row;
	// What col this creature is in the darwin grid
	size_t cr_col;
	// max row of the darwin grid where this creature lives
	size_t max_row;
	// max col of the darwin grid where this creature lives
	size_t max_col;
	// pointer to the darwin grid where this creature lives
	std::vector<std::vector<Creature> > *cr_grid; // TODO: when you put the creature on grid set this to the grid's 
												  // 2-d array
	// To check if this creature already had his turn or not
	bool is_done;

 
	// default constructor
	Creature();

	/**
	* Constructor with pc, dir and specie argument
	* @param dir an integer tells a direction
	* @param sp a Specie of the Creature
	*/
	Creature(int dir, Specie sp);
	
	/**
	* creature turns left (counter clockwise) 90 degrees to face in a new direction
	* @return false to tell the creature_action to not do any more instructions
	*/
	bool left();

	
	/**
	* creature turns right (clockwise) 90 degrees to face in a new direction
	* @return false to tell the creature_action to not do any more instructions
	*/
	bool right();
	
	/**
	* If the creature is facing a wall jump to step n, that is 
	* continue execution from step n. Otherwise (not facing a wall) continue with the next instruction.
	* @param next_pc an int, step num to jump to
	* @param check a bool, check if this is a real call or used as a helper function
	* @return false if used as a helper and there is no wall else true, if not used as a helper then return true
	*/
	bool if_wall (int next_pc, bool check); 

	/**
	* If the square in front of the creature is unoccupied
	* @param next_pc an int, step num to jump to
	* @param check a bool, check if this is a real call or used as a helper function
	* @return false if used as a helper and there is not empty else true, if not used as a helper then return true
	*/
	bool if_empty (int next_pc, bool check);

	
	/**
	* If the next space is occupied by a creature of an enemy species 
	* @param next_pc an int, step num to jump to
	* @param check a bool, check if this is a real call or used as a helper function
	* @return false if used as a helper and there is no enemy else true, if not used as a helper then return true
	*/
	bool if_enemy (int next_pc, bool check);

	
	/**
	* If the square directly in front of the creature is empty, the creature hops into it.
	* @return false to tell the creature_action to not do any more instructions
	*/
	bool hop(); // TODO: make sure to update the cr_row, cr_col, and cr_grid

	/**
	* If the square immediately in front of this creature is occupied by a creature of a different 
	* species (an ``enemy''), this creature ``infects'' the enemy, causing it to change its species to be the same as the infecting creature's species.
	* @return false to tell the creature_action to not do any more instructions
	*/
	bool infect(); // update the grid.....

	
	/**
	* calls appropriate methos of the creature
	* @param string, what command to run
	* @return value returned by the command
	*/
	bool creature_action (string s);

	/**
	* Does all the instruction untill a it sees an action
	*/
	void run_creature();

};

class Darwin
{
public:
	std::vector<std::vector<Creature> > grid;
	std::vector<std::vector<Creature> > *grid_p;
private:
	size_t _maxR;
	size_t _maxC;

public:	

	/**
	* Darwin default constructor
	*/
	Darwin();

	/**
	* Darwin constructor
	* @param rows, num_rows in darwin grid/world
	* @param cols, num_cols in darwin grid/world
	*/
	Darwin(size_t rows, size_t cols); // TODO: grid(rows, vector<point>(cols));

	/**
	* goes through one "year" of the Darwin grid/world
	*/
	void darwin_turn ();

	/**
	* prints out the grid
	*/
	void print();

	/**
	* inserts creatures into the grid at (row, col)
	* @param row an int, row where this creature lives
	* @param col an int, col where this creature lives
	* @param sp a Specie, specie of this creature
	* @param dir an int, what direction this creature is facing
	*/
	void add_creature(int row, int col, Specie sp, int dir);
};

#endif
