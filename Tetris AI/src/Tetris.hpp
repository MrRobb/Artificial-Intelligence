//
//  Tetris.hpp
//  Tetris AI
//
//  Created by Roberto Ariosa Hernández on 06/01/2018.
//

#ifndef Tetris_hpp
#define Tetris_hpp

#include <stdio.h>
#include <vector>
#include <map>
#include <string>

#include "ofMain.h"
#include "AI.hpp"
#include "DNA.hpp"

#define CLOCKWISE true
#define COUNTERCLOCKWISE false

using namespace std;

class Tetris {
private:
	// Content
	vector< vector<unsigned char> > grid;
	map<int,vector< vector<unsigned char> > > shapes;
	map<int,string> colors;
	Shape current;
	Shape next;
	Shape the_one;
	
	// Parameters
	int height = 20;
	int width = 10;
	int score = 0;
	int blockSize = 50;
	int w1;
	int w2;
	int h1;
	int h2;
	int x;
	int y;
	bool withAI = true;
	AI bot;
	
	// Functions
	void init_shapes();
	
	void init_colors();
	
	void rotateShape(bool clockwise);
	
public:
	Tetris();
	
	Tetris(int w1, int w2, int h1, int h2, bool withAI, DNA dna);
	
	void setDNA(float aggregate_height, float complete_lines, float holes, float bumpiness);
	
	bool ground();
	
	bool in (int offset);
	
	void moveLeft();
	
	void moveRight();
	
	void rotate();
	
	void update();
	
	void realloc(int w1, int w2, int h1, int h2);
	
	void toggleAI();
	
	void gameOver(ofTrueTypeFont &myFont);
	
	void reset();
	
	int drawScore(ofTrueTypeFont &myFont);
	
	bool draw(ofTrueTypeFont &myFont);
};

#endif /* Tetris_hpp */
