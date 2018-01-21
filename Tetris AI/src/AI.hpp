//
//  AI.hpp
//  Tetris AI
//
//  Created by Roberto Ariosa Hernández on 09/01/2018.
//  Copyright © 2018 Mr.Robb. All rights reserved.
//

#ifndef AI_hpp
#define AI_hpp

#include <stdio.h>
#include <vector>
#include <map>

using namespace std;

#define CLOCKWISE true
#define COUNTERCLOCKWISE false

// Data Structures
enum Blocks {I=0,J=4,L=8,O=12,S=16,T=20,Z=24};
struct Shape {
	int x;
	int y;
	Blocks shape;
};

class AI {
	float aggregate_height = 0.132802;
	float complete_lines = 0.132802;
	float holes = -0.344799;
	float bumpiness = -0.0387222;
	
	vector< vector<unsigned char> > grid;
	map<int,vector< vector<unsigned char> > > shapes;
	
	void rotateCustom(Shape &s, bool clockwise);
	
	bool in (Shape &s, int offset_x, int offset_y);
	
	bool moveLeft(Shape &s);
	
	void moveRight(Shape &s);
	
	bool moveDown(Shape &s);
	
public:
	AI();
	
	AI(map<int,vector< vector<unsigned char> > > &shapes);
	
	void setGrid(vector< vector<unsigned char> > &grid);
	
	void setDNA(float aggregate_height, float complete_lines, float holes, float bumpiness);
	
	void place_piece(Shape &s);
	
	void remove_piece(Shape &s);
	
	int columnHeight(int col);
	
	float calculate_height(Shape &s);
	
	float calculate_lines(Shape &s);
	
	float calculate_holes(Shape &s);
	
	float calculate_bumpiness(Shape &s);
	
	float score(Shape &s);
	
	pair<Shape, float> getBest(vector<Shape> s_inicial, int i);
};

#endif /* AI_hpp */
