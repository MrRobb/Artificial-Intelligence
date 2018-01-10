#include "ofApp.h"

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
	
	// Initialize
	for (int i = 0; i < n; i++) {
		games[i] = Tetris (ofGetWidth()/n * i, ofGetWidth()/n * (i+1), 0, ofGetHeight(), (i < ai));
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
	for (int i = 0; i < n; i++) {
		games[i].realloc(w/n * i, w/n * (i+1), 0, h);
	}
	myFont.load("data/myfont.otf", min(w, h) / 38);
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
