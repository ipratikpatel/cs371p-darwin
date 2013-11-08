#include <cstdlib>
#include <string>    // strings for programs
#include <sstream>   // to get ints from strings

using namespace std;

class Species
{
  // holds the program for the species
  vector<string> program;

  public:
  // publicly available name
  char name;

  // default constructor
  Species()
  {
    name = '.';
    program = vector<string>(0);
  }

  // one char constructor
  Species(const char c)
  {
    name = c;
    program = vector<string>(0);
  }

  // add to the program
  void add_instruction(string s)
  {
    program.push_back(s);
  }

  // to get instructions from the program
  string operator [] (int i) 
  {
    return program[i];
  }

  // for infecting to make sure the classes are different
  bool operator != (const Species& rhs)
  {
    return(name != rhs.name);
  }
};

class Creature
{
  public:
    // program counter
    int pc;
    // direction from 0 - 4 (West - South)
    int direction;
    // boolean to make sure we don't check something twice
    bool checked;
    // the species of the creature
    Species species;

    // default constructor
    Creature()
    {
      pc = 0;
      direction = 0;
    }

    // Species and direction constructor
    Creature(Species s, int dir)
    {
      direction = dir % 4;
      pc = 0;
      species = s;
      checked = false;
    }

    // turn the creature left
    void left()
    { 
      if(direction == 0)
        direction = 3;
      else if(direction == 1)
        direction = 0;
      else if(direction == 2)
        direction = 1;
      else if(direction == 3)
        direction = 2;
    }
    
    // turn the creature right
    void right()
    {
      if(direction == 0)
        direction = 1;
      else if(direction == 1)
        direction = 2;
      else if(direction == 2)
        direction = 3;
      else if(direction == 3)
        direction = 4;
    }

    // get the next command from the species
    const string next()
    {
      if(!checked)
        return species[pc];
      return "";
    }
};

template <size_t ROWS, size_t COLS>
class Grid
{
  private:
    // grid of pointer for moving creatures
    Creature* _g[ROWS][COLS];
    // static bank of creatures that pointers point to
    Creature _c[ROWS][COLS];

  public:
    // the size of the grid
    size_t num_r;
    size_t num_c;

    // default constructor
    Grid()
    {
      if((ROWS < 1) || (COLS < 1))
        cout << "No good" << endl;
      for(int i = 0; i < (int)ROWS; i++)
        for(int j = 0; j < (int)COLS; j++)
          _g[i][j] = 0;
      num_r = ROWS;
      num_c = COLS;
    }

    // gets the row of one space in front of 
    // where the creature is facing given a direction
    static int next_r(int r, int d)
    {
      if(d == 0 || d == 2)
        return r;
      if(d == 1)
        return r - 1;
      else
        return r + 1;
    }

    // gets the column of one space in front of 
    // where the creature is facing given a direction
    static int next_c(int c, int d)
    {
      if(d == 1 || d == 3)
        return c;
      if(d == 0)
        return c - 1;
      else
        return c + 1;
    }

    // returns a random boolean
    static bool random()
    {
      return(rand() % 2 == 1);
    }

    // tells if the critter at spot (r, c) is facing a wall
    bool facing_wall(int r, int c)
    {
      int dir = _g[r][c]->direction;
      int nr = next_r(r, dir);
      int nc = next_c(c, dir);
      return (nr >= (int)ROWS) || (nr < 0) || (nc >= (int)COLS) || (nc < 0);
    }

    // tells if the critter at spot (r, c) is facing an empty space
    bool facing_empty(int r, int c)
    {
      int dir = _g[r][c]->direction;
      int nr = next_r(r, dir);
      int nc = next_c(c, dir);
      return !facing_wall(r, c) && _g[nr][nc] == 0;
    }

    // tells if the critter at spot (r, c) is facing an enemy
    bool facing_enemy(int r, int c)
    {
      int dir = _g[r][c]->direction;
      int nr = next_r(r, dir);
      int nc = next_c(c, dir);
      return !facing_wall(r, c) && !facing_empty(r, c) && _g[r][c]->species != _g[nr][nc]->species;
    }

    // hops the critter at spot (r, c) forward one space
    void hop(int r, int c)
    {
      int dir = _g[r][c]->direction;
      int nr = next_r(r, dir);
      int nc = next_c(c, dir);
      if(facing_empty(r, c))
      {
        _g[nr][nc] = _g[r][c];
        _g[r][c] = 0;
        ++(_g[nr][nc]->pc);
        _g[nr][nc]->checked = true;
      }
      else
      {
        ++(_g[r][c]->pc);
        _g[r][c]->checked = true;
      }
    }

    // tries to infect the space in front of (r, c) or wastes (r, c)'s turn
    void infect(int r, int c)
    {
      int dir = _g[r][c]->direction;
      int nr = next_r(r, dir);
      int nc = next_c(c, dir);
      if(facing_enemy(r, c))
      {
        _g[nr][nc]->species = _g[r][c]->species;
        _g[nr][nc]->pc = 0;
      }
      ++(_g[r][c]->pc);
      _g[r][c]->checked = true;
    }

    // interprets the command and calls the correct corresponding method
    bool take_action(string s, int r, int c)
    {
      if(s.compare("hop") == 0)
      {
        hop(r, c);
        return true;
      }
      if(s.compare("left") == 0)
      {
        _g[r][c]->left();
        ++(_g[r][c]->pc);
        _g[r][c]->checked = true;
        return true;
      }
      if(s.compare("right") == 0)
      {
        _g[r][c]->right();
        ++(_g[r][c]->pc);
        _g[r][c]->checked = true;
        return true;
      }
      if(s.compare("infect") == 0)
      {
        infect(r, c);
        return true;
      }
      stringstream ss;
      ss << s;
      string command = "";
      ss >> command;
      int jump_num;
      ss >> jump_num;
      if(command.compare("if_empty") == 0)
      {
        if(facing_empty(r, c))
          _g[r][c]->pc = jump_num;
        else
          ++(_g[r][c]->pc);
        return false;
      }
      if(command.compare("if_wall") == 0)
      {
        if(facing_wall(r, c))
          _g[r][c]->pc = jump_num;
        else
          ++(_g[r][c]->pc);
        return false;
      }
      if(command.compare("if_random") == 0)
      {
        if(random())
          _g[r][c]->pc = jump_num;
        else
          ++(_g[r][c]->pc);
        return false;
      }
      if(command.compare("if_enemy") == 0)
      {
        if(facing_enemy(r, c))
          _g[r][c]->pc = jump_num;
        else
          ++(_g[r][c]->pc);
        return false;
      }
      if(command.compare("go") == 0)
      {
        _g[r][c]->pc = jump_num; 
        return false;
      }
      return true;
    }

    // goes through one "year" of the Darwin grid
    void one_step()
    {
      for(int r = 0; r < (int)ROWS; r++)
        for(int c = 0; c < (int)COLS; c++)
          if(_g[r][c] != 0 && !_g[r][c]->checked)
          {
            string temp = _g[r][c]->next();
            while(temp.compare("") != 0 && !take_action(temp, r, c))
              temp = _g[r][c]->next();
          }
      for(int r = 0; r < (int)ROWS; r++)
        for(int c = 0; c < (int)COLS; c++)
          if(_g[r][c] != 0)
            _g[r][c]->checked = false;
    }

    // prints out the grid and tallies the totals for the species
    void print()
    {
      if((ROWS == 0) || (COLS == 0))
        return;
      cout << "\n  ";
      for(int i = 0; i < (int)COLS; i++)
        cout << i % 10;
      cout << endl;
      int foo = 0;
      int hop = 0;
      int rov = 0;
      int tra = 0;
      int bes = 0;

      for(int i = 0; i < (int)ROWS; i++)
      {
        cout << i % 10 << " ";
        for(int j = 0; j < (int)COLS; j++)  
        {
          if(_g[i][j] == 0)
            cout << '.';
          else
          {
            if((_g[i][j]->species).name == 'f')
              foo++;
            if((_g[i][j]->species).name == 'h')
              hop++;
            if((_g[i][j]->species).name == 'r')
              rov++;
            if((_g[i][j]->species).name == 't')
              tra++;
            if((_g[i][j]->species).name == 'b')
              bes++;
              cout << (_g[i][j]->species).name;
          }
        }
        cout << endl;
      }
      cout << "*******************************\n";
      cout << "f:" << foo << " ";
      cout << "h:" << hop << " ";
      cout << "r:" << rov << " ";
      cout << "t:" << tra << " ";
      cout << "b:" << bes << endl << "*******************************\n";

    }

    // inserts creatures into the grid at (r, c)
    bool change(int r, int c, Creature v)
    {
      if((ROWS == 0) || (COLS == 0))
        return false;
      if((r >= (int)ROWS) || (c >= (int)COLS))
        return false; 
      if((r < 0) || (c < 0))
        return false;
      _c[r][c] = Creature(v.species, v.direction);
      _g[r][c] = &_c[r][c];
      return true;
    }
};
/*#ifndef DARWIN_H
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
*/