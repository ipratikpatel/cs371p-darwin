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
	
		Specie();
		Specie(const char c);

		void addInstruction(string s);
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
	//
	size_t cr_row;
	//
	size_t cr_col;
	//
	size_t max_row;
	//
	size_t max_col;
	//
	std::vector<std::vector<Creature> > *cr_grid; // TODO: when you put the creature on grid set this to the grid's 
												  // 2-d array
	bool is_done;

 
	// default constructor
	Creature();
	// Constructor with pc, dir and specie argument
	Creature(int dir, Specie sp);
	// creature turns left (counter clockwise) 90 degrees to face in a new direction
	bool left();
	// creature turns right (clockwise) 90 degrees to face in a new direction
	bool right();
	// return the row where creature will move if it hops if it faces west or east
	//static int get_next_row(int row, int dir);
	// return the row where creature will move if it hops if it faces west or east
	//static int get_next_col(int col, int dir);
	// True if the creature is facing a wall
	bool if_wall (int next_pc, bool check); 
	// If the square in front of the creature is unoccupied
	bool if_empty (int next_pc, bool check);
	// If the next space is occupied by a creature of an enemy species 
	bool if_enemy (int next_pc, bool check);
	// If the square directly in front of the creature is empty, the creature hops into it. 
	bool hop(); // TODO: make sure to update the cr_row, cr_col, and cr_grid
	// If the square immediately in front of this creature is occupied by a creature of a different species (an ``enemy''), this creature ``infects'' the enemy, causing it to change its species to be the same as the infecting creature's species.
	bool infect(); // update the grid.....
	// calls appropriate methos of the creature
	bool creature_action (string s);
	// Does all the instruction untill a it sees an action
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
	Darwin();

	Darwin(size_t rows, size_t cols); // TODO: grid(rows, vector<point>(cols));

	void darwin_turn ();

	void print();

	void add_creature(int row, int col, Specie sp, int dir);
};

#endif
