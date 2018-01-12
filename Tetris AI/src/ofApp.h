#pragma once

#include "ofMain.h"
#include "Tetris.hpp"
#include "Population.hpp"

class ofApp : public ofBaseApp{

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	float speed = 1.0;
	int timeFrame = 0;
	vector<Tetris> games;
	float counter = 0;
	bool finishRotation = true;
	bool isPaused = false;
	vector<bool> gameOvers;
	bool withAI = true;
	vector<int> scores;
	int n = 80;
	int ai = 80;
	int rowSize = 10;
	int cols = ai / (rowSize+1) + 1;
	ofTrueTypeFont myFont;
	Population population;
};
