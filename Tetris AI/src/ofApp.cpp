#include "ofApp.h"
#include "Tetris.cpp"

float speed = 1.0;
int timeFrame = 0;
Tetris game;
float counter = 0;
bool finishRotation = true;
bool isPaused = false;
bool gameOver = false;
int score = 0;

//--------------------------------------------------------------
void ofApp::setup(){
	// Config
	ofSetVerticalSync(false);
	ofSetFrameRate(speed * 60);
	ofSetBackgroundColorHex(ofHexToInt("0D1B1E"));
	ofDisableDataPath();
	myFont.load("data/myfont.otf", min(ofGetHeight(), ofGetWidth()) / 38);
	
	// Initialize
	game = Tetris();
}

//--------------------------------------------------------------
void ofApp::update(){
	if (not isPaused and not gameOver) {
		if (ofGetFrameNum() % int(20/speed) == 0)
			game.update();
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetColor(255, 255, 255);
	if (isPaused) {
		myFont.drawString("PAUSED", ofGetWidth()/2 - 85, ofGetHeight()/2);
	}
	else if (gameOver) {
		// game.gameOver(myFont);
		cerr << score << endl;
		gameOver = false;
		game.reset();
	}
	else {
		score = game.drawScore(myFont);
		game.draw(myFont, gameOver);
	}
	
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch (key) {
		case OF_KEY_DOWN:
			if (not isPaused and not gameOver) {
				speed = 3.0;
				ofSetFrameRate(speed * 60);
			}
			break;
			
		case OF_KEY_RIGHT:
			if (not isPaused and not gameOver) {
				game.moveRight();
			}
			break;
			
		case OF_KEY_LEFT:
			if (not isPaused and not gameOver) {
				game.moveLeft();
			}
			break;
			
		case OF_KEY_UP:
			if (not isPaused and not gameOver) {
				if (finishRotation) {
					game.rotate();
					finishRotation = false;
				}
			}
			break;
			
		case OF_KEY_RETURN:
			if (not isPaused and not gameOver) {
				game.reset();
			}
			break;
			
		case ' ':
			if (gameOver) {
				gameOver = false;
				game.reset();
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
	game.realloc(h,w);
	myFont.load("data/myfont.otf", min(w, h) / 38);
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
