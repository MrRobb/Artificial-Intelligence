#include "ofApp.h"
#include "Tetris.cpp"

float speed = 1.0;
int timeFrame = 0;
Tetris game;
float counter = 0;
bool finishRotation = true;

//--------------------------------------------------------------
void ofApp::setup(){
	// Config
	ofSetVerticalSync(false);
	ofSetFrameRate(speed * 60);
	ofSetBackgroundColorHex(ofHexToInt("0D1B1E"));
	
	// Initialize
	game = Tetris();
}

//--------------------------------------------------------------
void ofApp::update(){
	if (ofGetFrameNum() % int(20/speed) == 0)
		game.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	game.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch (key) {
		case OF_KEY_DOWN:
			speed = 3.0;
			ofSetFrameRate(speed * 60);
			break;
			
		case OF_KEY_RIGHT:
			game.moveRight();
			break;
			
		case OF_KEY_LEFT:
			game.moveLeft();
			break;
			
		case OF_KEY_UP:
			if (finishRotation) {
				game.rotate();
				finishRotation = false;
			}
			break;
			
		case ' ':
			game.reset();
			
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

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
