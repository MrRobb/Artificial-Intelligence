//
//  AI.cpp
//  Tetris AI
//
//  Created by Roberto Ariosa Hernández on 09/01/2018.
//  Copyright © 2018 Mr.Robb. All rights reserved.
//

#include "AI.hpp"

void AI::rotateCustom(Shape &s, bool clockwise) {
	s.shape = Blocks((s.shape - (s.shape % 4)) + ((s.shape + (clockwise ? 1 : -1)) % 4));
}

bool AI::in (Shape &s, int offset_x, int offset_y) {
	for (int i = 0; i < shapes[s.shape].size(); i++) {
		for (int j = 0; j < shapes[s.shape][i].size(); j++)
		{
			if (shapes[s.shape][i][j]) {
				int _x = s.x + j + offset_x;
				int _y = s.y + i + offset_y;
				if (_x < 0 or _x >= int(grid[0].size()) or
					_y < 0 or _y >= int(grid.size()) or
					grid[s.y + i + offset_y][s.x + j + offset_x])
					return true;
			}
		}
	}
	return false;
}

bool AI::moveLeft(Shape &s) {
	if (not in(s, -1, 0)) {
		s.x--;
		return true;
	}
	else return false;
}

void AI::moveRight(Shape &s) {
	if (not in(s, 1, 0)) {
		s.x++;
		return true;
	}
	else return false;
}

bool AI::moveDown(Shape &s) {
	if (not in(s, 0, 1)) {
		s.y++;
		return true;
	}
	else return false;
}

AI::AI() {
	
}

AI::AI(map<int,vector< vector<unsigned char> > > &shapes) {
	this->shapes = shapes;
}

void AI::setGrid(vector< vector<unsigned char> > &grid) {
	this->grid = grid;
}

void AI::setDNA(float aggregate_height, float complete_lines, float holes, float bumpiness) {
	this->aggregate_height = aggregate_height;
	this->complete_lines = complete_lines;
	this->holes = holes;
	this->bumpiness = bumpiness;
}

void AI::place_piece(Shape &s) {
	for (int i = 0; i < shapes[s.shape].size(); i++) {
		for (int j = 0; j < shapes[s.shape][i].size(); j++) {
			if (shapes[s.shape][i][j]) {
				grid[s.y + i][s.x + j] = shapes[s.shape][i][j];
			}
		}
	}
}

void AI::remove_piece(Shape &s) {
	for (int i = 0; i < shapes[s.shape].size(); i++) {
		for (int j = 0; j < shapes[s.shape][i].size(); j++) {
			if (shapes[s.shape][i][j]) {
				grid[s.y + i][s.x + j] = 0;
			}
		}
	}
}

int AI::columnHeight(int col) {
	for (int i = 0; i < grid.size(); i++) {
		if (grid[i][col]) return 20 - i;
	}
	return 0;
}

float AI::calculate_height(Shape &s) {
	int total = 0;
	for (int j = 0; j < grid[0].size(); j++) {
		total += columnHeight(j);
	}
	return total;
}

float AI::calculate_lines(Shape &s) {
	int lines = 0;
	for (int i = 0; i < grid.size(); i++) {
		bool complete = true;
		for (int j = 0; j < grid[0].size(); j++) {
			if (grid[i][j] == 0) {
				complete = false;
			}
		}
		if (complete) lines++;
	}
	return lines;
}

float AI::calculate_holes(Shape &s) {
	int total = 0;
	for (int j = 0; j < grid[0].size(); j++) {
		bool hole = false;
		for (int i = 0; i < grid.size(); i++) {
			if (grid[i][j] != 0) hole = true;
			else if (grid[i][j] == 0 and hole) ++total;
		}
	}
	return total;
}

float AI::calculate_bumpiness(Shape &s) {
	int bump = 0;
	for (int j = 0; j < grid[0].size() - 1; j++) {
		bump += abs(columnHeight(j) - columnHeight(j + 1));
	}
	return bump;
}

float AI::score(Shape &s)
{
	float a = calculate_height(s) * aggregate_height;
	float b = calculate_lines(s) * complete_lines;
	float c = calculate_holes(s) * holes;
	float d = calculate_bumpiness(s) * bumpiness;
	return a+b+c+d;
}

pair<Shape, float> AI::getBest(vector<Shape> s_inicial, int i)
{
	s_inicial[i].shape = Blocks(s_inicial[i].shape - s_inicial[i].shape % 4);
	float bestScore;
	Shape best;
	bool start = true;
	best.shape = s_inicial[i].shape;
	
	for (int rotation = 0; rotation < 4; rotation++) {
		
		while (moveLeft(s_inicial[i]));
		
		while (!in(s_inicial[i], 0, 0))
		{
			Shape s = s_inicial[i];
			
			while (moveDown(s));
			
			place_piece(s);
			float points = score(s);
			
			if (i < s_inicial.size() - 1) {
				points += getBest(s_inicial, i+1).second;
			}
			if (start or points > bestScore) {
				best.x = s.x;
				best.y = s.y;
				best.shape = s.shape;
				bestScore = points;
				start = false;
			}
			remove_piece(s);
			
			s_inicial[i].x++;
		}
		
		rotateCustom(s_inicial[i], CLOCKWISE);
	}
	
	return make_pair(best, bestScore);
}

