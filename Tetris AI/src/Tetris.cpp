//
//  Tetris.cpp
//  Tetris AI
//
//  Created by Roberto Ariosa Hernández on 06/01/2018.
//

#include "Tetris.hpp"

class Tetris {
	// Data Structures
	enum Blocks {I=0,J=4,L=8,O=12,S=16,T=20,Z=24};
	struct Shape {
		int x;
		int y;
		Blocks shape;
	};
	
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
	
	// Functions
	void init_shapes() {
		shapes[I] = {{0,0,0,0}, {1,1,1,1}, {0,0,0,0}, {0,0,0,0}};
		shapes[I+1] = {{0,0,1,0}, {0,0,1,0}, {0,0,1,0}, {0,0,1,0}};
		shapes[I+2] = {{0,0,0,0}, {0,0,0,0}, {1,1,1,1}, {0,0,0,0}};
		shapes[I+3] = {{0,1,0,0}, {0,1,0,0}, {0,1,0,0}, {0,1,0,0}};
		
		shapes[J] = {{2,0,0}, {2,2,2}, {0,0,0}};
		shapes[J+1] = {{0,2,2}, {0,2,0}, {0,2,0}};
		shapes[J+2] = {{0,0,0}, {2,2,2}, {0,0,2}};
		shapes[J+3] = {{0,2,0}, {0,2,0}, {2,2,0}};
		
		shapes[L] = {{0,0,3}, {3,3,3}, {0,0,0}};
		shapes[L+1] = {{0,3,0}, {0,3,0}, {0,3,3}};
		shapes[L+2] = {{0,0,0}, {3,3,3}, {3,0,0}};
		shapes[L+3] = {{3,3,0}, {0,3,0}, {0,3,0}};
		
		shapes[O] = {{4,4}, {4,4}};
		shapes[O+1] = {{4,4}, {4,4}};
		shapes[O+2] = {{4,4}, {4,4}};
		shapes[O+3] = {{4,4}, {4,4}};
		
		shapes[S] = {{0,5,5}, {5,5,0}, {0,0,0}};
		shapes[S+1] = {{0,5,0}, {0,5,5}, {0,0,5}};
		shapes[S+2] = {{0,0,0}, {0,5,5}, {5,5,0}};
		shapes[S+3] = {{5,0,0}, {5,5,0}, {0,5,0}};
		
		shapes[T] = {{0,6,0}, {6,6,6}, {0,0,0}};
		shapes[T+1] = {{0,6,0}, {0,6,6}, {0,6,0}};
		shapes[T+2] = {{0,0,0}, {6,6,6}, {0,6,0}};
		shapes[T+3] = {{0,6,0}, {6,6,0}, {0,6,0}};
		
		shapes[Z] = {{7,7,0}, {0,7,7}, {0,0,0}};
		shapes[Z+1] = {{0,0,7}, {0,7,7}, {0,7,0}};
		shapes[Z+2] = {{0,0,0}, {7,7,0}, {0,7,7}};
		shapes[Z+3] = {{0,7,0}, {7,7,0}, {7,0,0}};
		
	}
	
	void init_colors() {
		colors[I] = "F92338";
		colors[I] = "F92338";
		colors[I] = "F92338";
		colors[I] = "F92338";
		colors[J] = "C973FF";
		colors[L] = "1C76BC";
		colors[O] = "FEE356";
		colors[S] = "53D504";
		colors[T] = "36E0FF";
		colors[Z] = "F8931D";
	}
	
	void rotateShape(bool clockwise) {
		current.shape = Blocks((current.shape - (current.shape % 4)) + ((current.shape + (clockwise ? 1 : -1)) % 4));
	}
	
public:
	Tetris() {
		// Initialize
		grid = vector< vector<unsigned char> > (height, vector<unsigned char> (width, 0));
		init_shapes();
		init_colors();
		
		// Current Initialization
		current.x = 4;
		current.y = 0;
		current.shape = Blocks(int(rand() % 7) * 4);
		
		next.x = 4;
		next.y = 0;
		next.shape = Blocks(int(rand() % 7) * 4);
	}
	
	bool ground() {
		for (int i = 0; i < shapes[current.shape].size(); i++) {
			for (int j = 0; j < shapes[current.shape][i].size(); j++) {
				if (shapes[current.shape][i][j] and (current.y+i+1 >= height or grid[current.y+i+1][current.x+j] != 0)) {
					return true;
				}
			}
		}
		return false;
	}
	
	bool in (int offset) {
		for (int i = 0; i < shapes[current.shape].size(); i++) {
			for (int j = 0; j < shapes[current.shape][i].size(); j++) {
				if (shapes[current.shape][i][j] and (current.x + j + offset < 0 or current.x + j + offset >= width or grid[current.y + i][current.x + j + offset])) {
					return true;
				}
			}
		}
		return false;
	}
	
	void moveLeft() {
		if (not in(-1)) {
			current.x--;
		}
	}
	
	void moveRight() {
		if (not in(1)) {
			current.x++;
		}
	}
	
	void rotate() {
		rotateShape(CLOCKWISE);
		for (int i = 0; i < 4 and in(0); i++) {
			if (not in(-1)) {
				current.x--;
			}
			else if (not in (1)) {
				current.x++;
			}
			else {
				rotateShape(COUNTERCLOCKWISE);
				return;
			}
		}
	}
	
	void update() {
		// Update
		if (ground()) {
			for (int i = 0; i < shapes[current.shape].size(); i++) {
				for (int j = 0; j < shapes[current.shape][i].size(); j++) {
					if (shapes[current.shape][i][j]) {
						grid[current.y + i][current.x + j] = shapes[current.shape][i][j];
					}
				}
			}
			current = next;
			next.shape = Blocks(int(rand() % 7) * 4);
			next.y = 0;
			next.x = 4;
		}
		else {
			current.y++;
		}
	}
	
	void realloc(int h, int w) {
		this->blockSize = min(w, h) / 28;
		this->x = w / 2 - blockSize * width/2;
		this->y = h / 2 - blockSize * height/2;
	}
	
	void reset() {
		score = 0;
		
		grid = vector< vector<unsigned char> > (height, vector<unsigned char> (width, 0));
		
		// Current Initialization
		current.y = 0;
		current.shape = Blocks(int(rand() % 7) * 4);
		current.x = 4;
		
		next.y = 0;
		next.shape = Blocks(int(rand() % 7) * 4);
		next.x = 4;
	}
	
	void drawScore(ofTrueTypeFont &myFont) {
		string s = to_string(score);
		myFont.drawString(s, x - 300, y + blockSize);
	}
	
	void draw() {
		// Game over
		for (int j = 0; j < width; j++) {
			if (grid[1][j]) {
				reset();
			}
		}
		
		// Boundaries
		for (int i = -1; i < height + 1; i++) {
			for (int j = -1; j < width + 1; j++) {
				if (i == -1 or i == height or j == -1 or j == width) {
					ofSetHexColor(ofHexToInt("394446"));
					ofDrawRectangle(x + j * blockSize, y + i * blockSize, blockSize, blockSize);
				}
				else {
					ofSetHexColor(ofHexToInt("656D6F"));
					ofDrawRectangle(x + j * blockSize, y + i * blockSize, blockSize, blockSize);
				}
			}
		}
		
		// Lines
		ofSetHexColor(ofHexToInt("394446"));
		for (int i = 0; i < width; i++) {
			ofDrawLine(x + i * blockSize, y, x + i * blockSize, y + height * blockSize);
		}
		for (int i = 0; i < height; i++) {
			ofDrawLine(x, y + i * blockSize, x + width * blockSize, y + i * blockSize);
		}
		
		// Blocks
		unsigned char lines_cleared = 0;
		for (int i = 0; i < height; i++) {
			bool complete = true;
			for (int j = 0; j < width; j++) {
				if (grid[i][j] != 0) {
					ofSetHexColor(ofHexToInt(colors[Blocks((grid[i][j] - 1) * 4)]));
					ofDrawRectangle(x + j * blockSize, y + i * blockSize, blockSize, blockSize);
				}
				else {
					complete = false;
				}
			}
			if (complete) {
				// Update score
				++lines_cleared;
				switch (lines_cleared) {
					case 1:
						score += 40;
						break;
						
					case 2:
						score += 60;
						break;
						
					case 3:
						score += 200;
						break;
						
					case 4:
						score += 1000;
						break;
						
					default:
						reset();
						break;
				}
				
				// Clear
				for (int k = i; k > 0; k--) {
					for (int l = 0; l < width; l++) {
						grid[k][l] = grid[k-1][l];
					}
				}
			}
		}
		
		// Current
		ofSetHexColor(ofHexToInt(colors[current.shape - (current.shape % 4)]));
		for (int i = 0; i < shapes[current.shape].size(); i++) {
			for (int j = 0; j < shapes[current.shape][i].size(); j++) {
				if (shapes[current.shape][i][j]) {
					ofDrawRectangle(x + current.x * blockSize + j * blockSize, y + current.y * blockSize + i * blockSize, blockSize, blockSize);
				}
			}
		}
		
		// Next shape
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				ofSetHexColor(ofHexToInt("0D1B1E"));
				if (i >= 0 and i < shapes[next.shape].size() and j >= 0 and j < shapes[next.shape][i].size()) {
					if (shapes[next.shape][i][j]) {
						ofSetHexColor(ofHexToInt(colors[next.shape]));
					}
				}
				ofDrawRectangle(x + (width+3) * blockSize + j * blockSize, y + i * blockSize, blockSize, blockSize);
			}
		}
	}
};
