#pragma once

#include <iostream>
#include <locale>
#include <vector>
#include <fstream>

/**
point
**/
struct point {
	int x;
	int y;
};
/**
Labirint class 
**/
class Labirinth {
private:
	std::vector<std::vector<int>> matrix;
	int length;
public:
	/**
	Upload labirinth from file
	@param filename - object of class string (file path)
	**/
	void load(const std::string& filename);
	/**
	Finding a way by wave algorithm
	@param start - object of struct point (structure for start point coordinates describing)
	@param finish - object of struct point (structure for finish point coordinates describing)
	@param step_mode  - object of bool (sets the type of step construction)
	**/
	void find_way(const point& start, const point& finish, bool step_mode);
	/**
	Save labirinth to file
	@param filename - object of class string (file path)
	**/
	void save_answer(const std::string& filename);
	/**
	Overload << operator for Labirinth
	@param out - object of class îstream (output stream class to operate on files)
	@param o - object of class Labirinth 
	**/
	friend std::ostream& operator<<(std::ostream& out, const Labirinth& o);
};

