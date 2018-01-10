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

#include "ofApp.h"
#include "AI.hpp"

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
	
	// Parameters
	int height = 20;
	int width = 10;
	int score = 0;
	int blockSize = 50;
	int x = 1400 / 2 - blockSize * width/2;
	int y = 1400 / 2 - blockSize * height/2;
	
	Shape the_one;
	
	// Functions
	void init_shapes();
	
	void init_colors();
	
	void rotateShape(bool clockwise);
	
public:
	Tetris();
	
	bool ground();
	
	bool in (int offset);
	
	void moveLeft();
	
	void moveRight();
	
	void rotate();
	
	void update();
	
	void realloc(int h, int w);
	
	void gameOver(ofTrueTypeFont &myFont);
	
	void reset();
	
	int drawScore(ofTrueTypeFont &myFont);
	
	void draw(ofTrueTypeFont &myFont, bool &gameOver);
};

#endif /* Tetris_hpp */
