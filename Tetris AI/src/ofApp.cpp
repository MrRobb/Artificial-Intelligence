#include "ofApp.h"
#include "DNA.hpp"

int dead = 0;

//--------------------------------------------------------------
void ofApp::setup(){
	// Config
	games = vector<Tetris> (n);
	scores = vector<int> (n, 0);
	gameOvers = vector<bool> (n, false);
	ofSetVerticalSync(false);
	ofSetFrameRate(60);
	ofSetBackgroundColorHex(ofHexToInt("0D1B1E"));
	ofDisableDataPath();
	myFont.load("data/myfont.otf", min(ofGetHeight(), ofGetWidth()) / 38);
	
	population = Population(4, 0.025, ai, 0);
	for (auto dna : population.allValues()) {
		for (auto value : dna) {
			cerr << value << ' ';
		}
		cerr << endl;
	}
	
	// Initialize
	if (ai == n) {
		int w = ofGetWidth();
		int h = ofGetHeight();
		for (int i = 0; i < n; i++) {
			int w1 = w/rowSize * (i % rowSize);
			int w2 = w/rowSize * ((i % rowSize) + 1);
			int h1 = h/cols * int(i/rowSize);
			int h2 = h/cols * int(i/rowSize) + h/cols;
			games[i] = Tetris (w1, w2, h1, h2, (i < ai), population[i]);
		}
	}
	else {
		int w = ofGetWidth()/2;
		int h = ofGetHeight();
		for (int i = 0; i < n-1; i++) {
			int w1 = w/rowSize * (i % rowSize);
			int w2 = w/rowSize * ((i % rowSize) + 1);
			int h1 = h/cols * int(i/rowSize);
			int h2 = h/cols * int(i/rowSize) + h/cols;
			games[i] = Tetris (w1, w2, h1, h2, (i < ai), population[i]);
		}
		int i = n - 1;
		games[i] = Tetris (w, w*2, 0, h, (i < ai), NULL);
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
	if (isPaused) {
		myFont.drawString("PAUSED", ofGetWidth()/2 - 85, ofGetHeight()/2);
	}
	else {
		if (dead == n and dead == ai) {
			// Evolve
			population.calculateFitness(scores);
			vector<float> best = population[population.getBest()].getValues();
			cerr << population.getAverage() << " ";
			cerr << population.getGenerations() << " -> ";
			
			cerr << "Best:";
			for (auto& value : best) {
				cerr << ' ' << value;
			}
			cerr << endl;
			population.naturalSelection();
			Population aux = population.generate(4);
			population = aux;
			int w = ofGetWidth()/2;
			int h = ofGetHeight();
			for (int i = 0; i < n; i++) {
				gameOvers[i] = not gameOvers[i];
				games[i].reset();
				int w1 = w/rowSize * (i % rowSize);
				int w2 = w/rowSize * ((i % rowSize) + 1);
				int h1 = h/cols * int(i/rowSize);
				int h2 = h/cols * int(i/rowSize) + h/cols;
				games[i] = Tetris (w1, w2, h1, h2, (i < ai), population[i]);
			}
			dead = 0;
		}
		for (int i = 0; i < n; i++) {
			ofSetColor(255, 255, 255);
			if (gameOvers[i]) {
				games[i].gameOver(myFont);
		//		cerr << "Player: " << score << endl;
		//		gameOver = false;
		//		games[0].reset();
			}
			else {
				scores[i] = games[i].drawScore(myFont);
				gameOvers[i] = games[i].draw(myFont);
				if (gameOvers[i] == true) {
					++dead;
				}
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch (key) {
		case OF_KEY_DOWN:
			if (not isPaused and not gameOvers[n-1]) {
				speed = 3.0;
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
			if (not isPaused and not gameOvers[n-1]) {
				games[n-1].reset();
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
			speed = 1.0;
			ofSetFrameRate(speed * 60);
		default:
			break;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	switch (key) {
		case OF_KEY_DOWN:
			speed = 1.0;
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
		games[i].realloc(w/rowSize * (i%rowSize), w/rowSize * ((i%rowSize) + 1), h/cols * int(i/rowSize), h/cols * int(i/rowSize) + h/cols);
	}
	myFont.load("data/myfont.otf", min(w, h) / 38);
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
