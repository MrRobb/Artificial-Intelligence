#include "ofApp.h"
#include "DNA.hpp"

void evolve(Population& population, const vector<int>& scores)
{
	population.calculateFitness(scores);
	int i = population.getBest();
	vector<float> best = population[i].getValues();
	
	// Print stats
	cerr << population.getAverage() << " ";
	cerr << population.getGenerations() << " -> ";
	cerr << "Best: ";
	cerr << scores[i];
	for (auto& value : best) {
		cerr << ' ' << value;
	}
	cerr << endl;
	
	// Set new generation
	Population aux = population.generate();
	population = move(aux);
}

void init_game_with_player(vector<Tetris>& games, queue<unsigned char>& pieces, int rowSize, int cols, int n, int ai, bool training)
{
	int w = ofGetWidth()/2;
	int h = ofGetHeight();
	for (int i = 0; i < 100000; i++) {
		pieces.push(rand());
	}
	for (int i = 0; i < n-1; i++) {
		int w1 = w/rowSize * (i % rowSize);
		int w2 = w/rowSize * ((i % rowSize) + 1);
		int h1 = h/cols * int(i/rowSize);
		int h2 = h/cols * int(i/rowSize) + h/cols;
		games[i] = Tetris (w1, w2, h1, h2, (i < ai), NULL, pieces, training);
	}
	int i = n - 1;
	games[i] = Tetris (w, w*2, 0, h, (i < ai), NULL, pieces, training);
}

void init_game_without_player(vector<Tetris>& games, Population& population, queue<unsigned char>& pieces, int rowSize, int cols, int n, int ai, bool training)
{
	int w = ofGetWidth();
	int h = ofGetHeight();
	int generation = population.getGenerations();
	for (int i = 0; i < 100 * (generation + 1); i++) {
		pieces.push(rand());
	}
	for (int i = 0; i < n; i++) {
		int w1 = w/rowSize * (i % rowSize);
		int w2 = w/rowSize * ((i % rowSize) + 1);
		int h1 = h/cols * int(i/rowSize);
		int h2 = h/cols * int(i/rowSize) + h/cols;
		games[i] = Tetris (w1, w2, h1, h2, (i < ai), population[i], pieces, training);
	}
}

void draw_instructions()
{
	ofTrueTypeFont myFont;
	int x = 20;
	int y = ofGetHeight();
	int line = 50;
	myFont.load("data/myfont.otf", 22);
	ofSetColor(255, 255, 255);
	myFont.drawString("left arrow: move left", x, y - line * 1);
	myFont.drawString("right arrow: move right", x, y - line * 2);
	ofSetHexColor(ofHexToInt("36E0FF"));
	myFont.drawString("down arrow: +speed", x, y - line * 3);
	ofSetHexColor(ofHexToInt("53D504"));
	myFont.drawString("up arrow: rotate", x, y - line * 4);
	ofSetHexColor(ofHexToInt("F8931D"));
	myFont.drawString("M: max speed", x, y - line * 5);
	ofSetHexColor(ofHexToInt("FEE356"));
	myFont.drawString("N: normal speed", x, y - line * 6);
	ofSetHexColor(ofHexToInt("F92338"));
	myFont.drawString("space: pause / reset", x, y - line * 7);
	ofSetHexColor(ofHexToInt("C973FF"));
	myFont.drawString("enter: reset while playing", x, y - line * 8);
	ofSetColor(150, 150, 150);
	myFont.drawString("H: show/hide instructions", x, y - line * 9);
}

//--------------------------------------------------------------
void ofApp::setup(){
	// Config
	ofSetVerticalSync(false);
	ofSetFrameRate(60);
	ofSetBackgroundColorHex(ofHexToInt("0D1B1E"));
	ofDisableDataPath();
	
	// Initialize
	myFont.load("data/myfont.otf", min(ofGetWidth(), ofGetHeight()) / (rowSize * 20));
	games = vector<Tetris> (n);
	scores = vector<int> (n, 0);
	gameOvers = vector<bool> (n, false);
	queue<unsigned char> pieces;
	population = Population(4, ai, 0.025, 0);
	
	// Init Game
	if (ai == n) {
		init_game_without_player(games, population, pieces, rowSize, cols, n, ai, training);
	}
	else {
		init_game_with_player(games, pieces, rowSize, cols, n, ai, training);
	}
}

//--------------------------------------------------------------
void ofApp::update(){
	if (not isPaused) {
		for (int i = 0; i < n; i++) {
			if (not gameOvers[i] and ofGetFrameNum() % int(20/speed) == 0) {
				games[i].update();
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	if (isPaused)
	{
		ofSetColor(255, 255, 255);
		myFont.drawString("PAUSED", ofGetWidth()/2 - 85, ofGetHeight()/2);
	}
	else {
		// All are dead
		if (dead == n and dead == ai and training) {
			// Evolve
			evolve(population, scores);
			
			// Draw new game
			queue<unsigned char> pieces;
			gameOvers = vector<bool> (n, false);
			dead = 0;
			init_game_without_player(games, population, pieces, rowSize, cols, n, ai, training);
		}
		
		for (int i = 0; i < n; i++) {
			ofSetColor(255, 255, 255);
			if (gameOvers[i]) {
				games[i].gameOver(myFont);
			}
			else {
				scores[i] = games[i].drawScore(myFont);
				gameOvers[i] = games[i].draw(myFont);
				if (gameOvers[i] == true) {
					++dead;
				}
			}
		}
		
		if (instructions)
			draw_instructions();
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	queue<unsigned char> pieces;
	switch (key) {
		case OF_KEY_DOWN:
			if (not isPaused and not gameOvers[n-1]) {
				speed = 5.0;
			}
			break;
			
		case OF_KEY_RIGHT:
			if (not isPaused and not gameOvers[n-1]) {
				games[n-1].moveRight();
			}
			break;
			
		case OF_KEY_LEFT:
			if (not isPaused and not gameOvers[n-1]) {
				games[n-1].moveLeft();
			}
			break;
			
		case OF_KEY_UP:
			if (not isPaused and not gameOvers[n-1]) {
				if (finishRotation) {
					games[n-1].rotate();
					finishRotation = false;
				}
			}
			break;
			
		case OF_KEY_RETURN:
			if (not isPaused) {
				if (n > 2 and (gameOvers[0] or gameOvers[1])) {
					gameOvers[0] = false;
					gameOvers[1] = false;
				}
				init_game_with_player(games, pieces, rowSize, cols, n, ai, training);
			}
			break;
			
		case ' ':
			if (gameOvers[n-1]) {
				gameOvers[n-1] = false;
				games[n-1].reset();
			}
			else {
				isPaused = not isPaused;
			}
			break;
		
		case 'm':
			speed = 20.0;
			ofSetFrameRate(speed * 60);
			break;
			
		case 'n':
			speed = 2.0;
			ofSetFrameRate(speed * 60);
			
		case 'h':
			instructions = !instructions;

		default:
			break;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	switch (key) {
		case OF_KEY_DOWN:
			speed = 1.25;
			ofSetFrameRate(speed * 60);
			break;
			
		case OF_KEY_UP:
			finishRotation = true;
			break;
			
		default:
			break;
	}
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
	// Initialize
	for (int i = 0; i < n; i++) {
		if (n != ai) rowSize++;
		games[i].realloc(w/rowSize * (i%rowSize), w/rowSize * ((i%rowSize) + 1), h/cols * int(i/rowSize), h/cols * int(i/rowSize) + h/cols);
		if (n != ai) rowSize--;
	}
	myFont.load("data/myfont.otf", min(w, h)/ (rowSize * 20));
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
