#include "ofApp.h"

vector<Specimen> v;
ofVec2f old;
ofVec2f target;
int n = 20;
float speed = 1.0;

//--------------------------------------------------------------
void ofApp::setup(){
	// Config
	ofSetVerticalSync(false);
	ofSetFrameRate(speed * 60);
	ofSetBackgroundColorHex(ofHexToInt("0D1B1E"));
	
	// Initialize
	v = vector<Specimen> (n);
	for (int i = 0; i < n; i++) {
		v[i] = Specimen(abs(int(rand())) % ofGetWidth(), abs(int(rand())) % ofGetHeight());
	}
}

//--------------------------------------------------------------
void ofApp::update()
{
	// Compute
	for (auto& ind : v) {
		ind.applyBehaviors(v);
		ind.update();
	}
	
	// Print
}

//--------------------------------------------------------------
void ofApp::draw(){
	for (auto& ind : v) {
		ind.draw();
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == GLFW_KEY_1) {
		speed = 1;
	}
	if (key == GLFW_KEY_2) {
		speed = 2;
	}
	if (key == GLFW_KEY_3) {
		speed = 3;
	}
	if (key == GLFW_KEY_4) {
		speed = 4;
	}
	if (key == GLFW_KEY_5) {
		speed = 5;
	}
	if (key == GLFW_KEY_6) {
		speed = 6;
	}
	if (key == GLFW_KEY_7) {
		speed = 7;
	}
	if (key == GLFW_KEY_8) {
		speed = 8;
	}
	if (key == GLFW_KEY_9) {
		speed = 9;
	}
	if (key == GLFW_KEY_0) {
		speed = 0;
	}
	ofSetFrameRate(speed * 60);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
	old = target;
	target = ofVec2f(mouseX, mouseY);
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	if (button == OF_MOUSE_BUTTON_1)
		v.push_back(Specimen(x, y));
	else
		v.pop_back();
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	if (button == OF_MOUSE_BUTTON_1)
		v.push_back(Specimen(x, y));
	else
		v.pop_back();
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
