#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	// Config
	ofSetWindowPosition(ofGetScreenWidth()/2 - ofGetWidth()/2, 0);
	ofSetVerticalSync(false);
	ofSetFrameRate(60);
	ofSetBackgroundColorHex(ofHexToInt("0D1B1E"));
	ofEnableDataPath();
	
	// Init
	w = ofGetWidth();
	h = ofGetHeight();
	
	// GUI
		// Fonts
	ofxSmartFont::add("../fonts/SFDisplayRegular.otf", 27, "SFDisplayRegular");
	input.setFont(ofxSmartFont::get("SFDisplayRegular"));
	
		// Rect
	input.setRect(25, h - 100, w - 50, 70, 20);
}

//--------------------------------------------------------------
void ofApp::update()
{
	
}

//--------------------------------------------------------------
void ofApp::draw()
{
	input.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	input.update(key);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

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
	this->w = w;
	this->h = h;
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg)
{
	cout << "Mensaje recibido: " << msg.message << endl;
	piBot.whatAreYouTalkingAbout(msg.message);
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
