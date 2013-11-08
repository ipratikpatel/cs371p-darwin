#include "Darwin.h"
#include <cassert>   // assert
#include <cstdlib>   // rand, srand
#include <iostream>  // cout, endl
#include <stdexcept> // invalid_argument, out_of_range
#include <string>
#include <sstream>
#include <vector>

#define DB 0

using namespace std;

Specie::Specie()
{
	name = ' ';
	instructions = vector<string>(0);
}

Specie::Specie(const char c)
{
	name = c;
	instructions = vector<string>(0);
}

void Specie::addInstruction (string s)
{
	if(DB) cout << "Specie::addInstruction" << endl;
	instructions.push_back(s);
}

bool Specie::is_equal (const Specie& rhs)
{
	if(DB) cout << "Specie::is_equal" << endl;
	return name == rhs.name;
}

Creature::Creature()
{
	pc = 0;
	direction = WEST;
	cr_row = 0;
	cr_col = 0;
	max_row = 0;
	max_col = 0;
	cr_grid = NULL;
}

Creature::Creature(int dir, Specie sp)
{
	pc = 0;
	direction = dir;
	specie = sp;
	cr_row = 0;
	cr_col = 0;
	max_col = 0;
	max_row = 0;
	cr_grid = NULL;
	is_done = false;
}

bool Creature::right()
{
	if(DB) cout << "Creature::right" << endl;
	if(direction == SOUTH)
		direction = WEST;
	if(direction == WEST)
		direction = NORTH;
	if(direction == NORTH)
		direction = EAST;
	if(direction == EAST)
		direction = SOUTH;	
	// go to next instruction
	++pc;
	is_done = true;
	// return false because we don't want any more instructions to run in run_creature look at run_creature...
	return false;
}

bool Creature::left()
{
	if(DB) cout << "Creature::left" << endl;
	if(direction == SOUTH)
		direction = EAST;
	if(direction == WEST)
		direction = SOUTH;
	if(direction == NORTH)
		direction = WEST;
	if(direction == EAST)
		direction = NORTH;
	++pc;
	is_done = true;
	// return false because we don't want any more instructions to run in run_creature look at run_creature...
	return false;	
}

static int get_next_col(int col, int dir)
{
	if(DB) cout << "Creature::get_next_col" << endl;
	if (dir == NORTH || dir == SOUTH)
		return col;
	else if (dir == EAST)
		return (col + 1);
	else
		return (col - 1);
}

static int get_next_row(int row, int dir)
{
	if(DB) cout << "Creature::get_next_row" << endl;
	if (dir == WEST || dir == EAST)
		return row;
	else if (dir == SOUTH)
		return (row + 1);
	else
		return (row - 1); 	
}

bool Creature::if_wall(int next_pc, bool check)
{
	if(DB) cout << "Creature::if_wall" << endl;
	assert(cr_grid != NULL);
	assert(max_row != 0);
	assert(max_col != 0);

	int next_r = get_next_row(cr_row, direction);
	int next_c = get_next_col(cr_col, direction);
	bool is_wall = false;

	if(next_c < 0 || next_c >= (int)max_col)
		is_wall = true;

	if (next_r < 0 || next_r >= (int)max_row)
		is_wall = true;

	// TODO: in  take _action
	if(!check)
	{
		if(is_wall)
		{
			pc = next_pc;
		}	
		else
			++pc;
		// return true because we want any more instructions to run in run_creature look at run_creature...
		if(DB) cout << "end of if_wall " << endl;
		return true; 
	}
	if(DB) cout << "end of if_wall " << endl;
	return is_wall;
}

bool Creature::if_empty (int next_pc, bool check)
{
	if(DB) cout << "Creature::if_empty" << endl;
	assert(cr_grid != NULL);
	assert(max_row != 0);
	assert(max_col != 0);

	int next_r = get_next_row(cr_row, direction);
	int next_c = get_next_col(cr_col, direction);
	bool is_empty = false;

	if (!(*this).if_wall(0, true))
	{
		if( ((*cr_grid)[next_r][next_c]).cr_grid == NULL )
			is_empty = true;
	}

	if(!check )
	{
		if(is_empty)
			pc = next_pc;
		else
			++pc;
		if(DB) cout << "end of if_empty " << endl;
		return true;
	}
	if(DB) cout << "end of if_empty " << endl;
	return is_empty;
}

bool Creature::if_enemy (int next_pc, bool check)
{
	if(DB) cout << "Creature::if_enemy" << endl;
	assert(cr_grid != NULL);
	assert(max_row != 0);
	assert(max_col != 0);

	int next_r = get_next_row(cr_row, direction);
	int next_c = get_next_col(cr_col, direction);
	bool is_enemy = false;

	if(!(*this).if_wall(0, true) && !(*this).if_empty(0, true))
	{
		if( !specie.is_equal( ((*cr_grid)[next_r][next_c]).specie) )
			is_enemy = true;
	}

	if(!check)
	{
		if(is_enemy)
			pc = next_pc;
		else
			++pc;
		return true;
	}

	return is_enemy;
}

bool Creature::hop ()
{
	if(DB) cout << "Creature::hop" << endl;
	assert(cr_grid != NULL);
	assert(max_row != 0);
	assert(max_col != 0);

	int next_r = get_next_row(cr_row, direction);
	int next_c = get_next_col(cr_col, direction);

	if((*this).if_empty(0, true))
	{
		if(DB) cout << "now hopping " << endl;
		(*cr_grid)[next_r][next_c] = *this;		
		assert((*cr_grid)[next_r][next_c].cr_row == cr_row);
		(*cr_grid)[next_r][next_c].cr_row = (size_t)next_r;
		(*cr_grid)[next_r][next_c].cr_col = (size_t)next_c;
		assert((*cr_grid)[next_r][next_c].cr_col == next_c);
		assert((*cr_grid)[next_r][next_c].max_row == max_row);
		assert((*cr_grid)[next_r][next_c].cr_grid != NULL);
		(*cr_grid)[next_r][next_c].specie = specie;
		(*cr_grid)[next_r][next_c].pc = pc + 1;
		(*cr_grid)[next_r][next_c].is_done = true;
		assert((*cr_grid)[next_r][next_c].direction == direction);
		//TODO:  If not right check the dirction
		*this = Creature();
		if(DB) cout << "end hope with " << false << endl;
		return false;
	}
	else
	{
		++pc;
		is_done = true;
		if(DB) cout << "end hope with " << false << endl;
		return false;
	}
}

bool Creature::infect()
{
	if(DB) cout << "Creature::infect" << endl;
	assert(cr_grid != NULL);
	assert(max_row != 0);
	assert(max_col != 0);

	int next_r = get_next_row(cr_row, direction);
	int next_c = get_next_col(cr_col, direction);

	if((*this).if_enemy(0, true))
	{
		((*cr_grid)[next_r][next_c] ).specie = specie;
		((*cr_grid)[next_r][next_c] ).pc = 0;
	}
	++pc;
	is_done = true;
	return false;
}

bool Creature::creature_action(string str)
{	
	if(DB) cout << "Creature::creature_action" << endl;
	if(DB) cout << "Creature:: name" << specie.name << endl;
	if(DB) cout << "command " << str << endl;
	bool ans = false;
	if (str.compare("left") == 0)
	{
		ans = (*this).left();
		assert(ans == false);
		return ans;
	}
	if (str.compare("right") == 0)
	{	
		ans = (*this).right();
		assert(ans == false);
		return ans;
	}
	if (str.compare("hop") == 0)
	{	
		ans = (*this).hop();
		assert(ans == false);
		return ans;
	}
	if (str.compare("infect") == 0)
	{	
		ans = (*this).infect();
		assert(ans == false);
		return ans;
	}

    istringstream iss(str);
	string control;
	iss >> control;
	string num;
	iss >> num;
	int next_pc = atoi(num.c_str());
	if(DB) cout << "control " << control << endl;
	if(DB) cout << "Next PC after tokenizing " << next_pc << endl;

	if (control.compare("if_wall") == 0)
	{
		ans = (*this).if_wall(next_pc, false);
		assert(ans == true);
		return ans;
	}
	if (control.compare("if_empty") == 0)
	{
		ans = (*this).if_empty(next_pc, false);
		assert(ans == true);
		return ans;
	}
	if (control.compare("if_enemy") == 0)
	{
		ans = (*this).if_enemy(next_pc, false);
		assert(ans == true);
		return ans;
	}
	if (control.compare("if_random") == 0)
	{
		if((rand() % 2) == 1)
			pc = next_pc;
		else
			++pc;
		return true;
	}
	if (control.compare("go") == 0)
	{
		pc = next_pc;
		return true;
	}
	assert(false);
	return true;
}

bool check_grid (vector<vector<Creature> > *grid,int maxR, int maxC )
{
	for (int row = 0; row < (int)maxR; ++row)
		{
			for (int col = 0; col < (int)maxC; ++col)
			{
				cout << "( " << row << ", " << col << " )  max_row: " << (*grid)[row][col].max_row << "max_col: " << (*grid)[row][col].max_col
					 << "row: " << (*grid)[row][col].cr_row << "col: " << (*grid)[row][col].cr_row << endl;
 			}
			cout << endl;
		}
	return true;
}

void Creature::run_creature()
{
	bool check = true;
	if(DB) cout << "Creature::run_creature******************************" << endl;
	while(check)
	{
			if(DB)  cout << "Creature::pc " << pc << endl;
			if(DB)  cout << "Creature::direction " << direction << endl; 
			if(DB)  cout << "Creature::max_row " << (*this).max_row << endl;
			if(DB)  cout << "Creature::max_col " << (*this).max_col << endl;
			if(DB)  cout << "Creature::row " << (*this).cr_row << endl;
			if(DB)  cout << "Creature::col " << (*this).cr_col << endl;
		if((*this).max_col > 0 && (*this).max_row > 0 ) 
		{
			if(DB) check_grid(cr_grid, 8, 8);
			if(DB)  cout << "Creature::inst_pc " << specie.instructions[pc] << endl;
			if(DB)  cout << "Creature::max_row " << max_row << endl;
			if(DB)  cout << "Creature::max_col " << max_col << endl;
			if(DB)  cout << "Creature::row " << cr_row << endl;
			if(DB)  cout << "Creature::col " << cr_col << endl;
			check = (*this).creature_action(specie.instructions[pc]);
			if(DB)  cout << "****************************************************************" << endl;
			if(DB) check_grid(cr_grid, 8, 8);
			if(DB)  cout << "Creature::pc " << pc << endl;
			if(DB) 	cout << "Creature::direction " << direction << endl; 
			if(DB) 	cout << "Creature::max_row " << max_row << endl;
			if(DB) 	cout << "Creature::max_col " << max_col << endl;
			if(DB) 	cout << "Creature::row " << cr_row << endl;
			if(DB) 	cout << "Creature::col " << cr_col << endl;
		}
		else
		{
			cout << "What?" << endl;
			//check_grid(cr_grid, 8, 8);
			cout << "Now?" << endl;
			break;
		}
			
	}
}

Darwin::Darwin()
{
	_maxR = 0;
	_maxC = 0;
	grid = vector<vector<Creature> >(0);
	grid_p = &grid;
}

Darwin::Darwin(size_t rows, size_t cols)
{
	_maxR = rows;
	_maxC = cols;
	grid = vector<vector<Creature> >(rows, vector<Creature>(cols));
	grid_p = &grid;
}

void Darwin::add_creature(int row, int col, Specie sp, int dir)
{
	if(DB) cout << "Darwin::add_creature" << endl;
	if ((int)_maxR > 0 && (int)_maxC > 0 && row < (int)_maxR && col < (int)_maxC && row >= 0 && col >= 0)
	{
		grid[row][col] = Creature(dir, sp);
		grid[row][col].cr_row = row;
		grid[row][col].cr_col = col;
		grid[row][col].max_row = _maxR;
		grid[row][col].max_col = _maxC;
		grid[row][col].cr_grid = grid_p;
	}
}


void Darwin::darwin_turn()
{
	if(DB) printf("Darwin::darwin_turn\n");
	for (int row = 0; row < (int)_maxR; ++row)
	{
		for (int col = 0; col < (int)_maxC; ++col)
		{
			if(DB)  cout << "(_maxR, _maxC) " << _maxR << " " << _maxC << endl;
			if (grid[row][col].max_row != 0 && grid[row][col].max_col != 0 && !grid[row][col].is_done )
			{

				if(DB)  cout << "darwin_turn" << endl;
				if(DB)  check_grid(grid_p, 8, 8);
				if(DB)  cout << "( row, col )" << row << " " << col << endl;
				if(DB)  cout << "pc " << grid[row][col].pc << endl;
				if(DB)  cout << "direction " << grid[row][col].direction << endl; 
				if(DB)  cout << "max_row " << grid[row][col].max_row << endl;
				if(DB)  cout << "max_col " << grid[row][col].max_col << endl;
				if(DB)  cout << "row " << grid[row][col].cr_row << endl;
				if(DB)  cout << "col " << grid[row][col].cr_col << endl;
				grid[row][col].run_creature();
			}
		}
	}

	for (int row = 0; row < (int)_maxR; ++row)
	{
		for (int col = 0; col < (int)_maxC; ++col)
		{
			grid[row][col].is_done = false;
		}
	}
}


void Darwin::print()
{	
	//cout << "Darwin::printf" << endl;
	if(_maxC != 0 && (int)_maxR != 0)
	{
		cout << "  ";
		for (int i = 0; i < (int)_maxC; ++i)
		{
			cout << i;
		}
		cout << endl;

		for (int row = 0; row < (int)_maxR; ++row)
		{
			cout << row << " ";
			for (int col = 0; col < (int)_maxC; ++col)
			{
				if(grid[row][col].max_row == 0)
					cout << ".";
				else
					cout << grid[row][col].specie.name;
			}
			cout << endl;
		}
		cout << endl;

		// for (int row = 0; row < (int)_maxR; ++row)
		// {
		// 	for (int col = 0; col < (int)_maxC; ++col)
		// 	{
		// 		cout << "( " << row << ", " << col << " )  max_row: " << grid[row][col].max_row << "max_col: " << grid[row][col].max_col
		// 			 << "row: " << grid[row][col].cr_row << "col: " << grid[row][col].cr_row << "direction: " << grid[row][col].direction << endl;
 	// 		}
		// 	cout << endl;
		// }
	}
}





