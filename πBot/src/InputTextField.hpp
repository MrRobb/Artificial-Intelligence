//
//  InputTextField.hpp
//  piBot
//
//  Created by Roberto Ariosa Hernández on 22/01/2018.
//

#ifndef InputTextField_hpp
#define InputTextField_hpp

#include "ofMain.h"
#include "ofxSmartFont.h"

using namespace std;

class InputTextField {
	
public:
	
	InputTextField();
	
	InputTextField(const string &text);
	
	string getText();
	
	void setText(const string &text);
	
	void update(int key);
	
	void setRect(float x, float y, float w, float h, float r);
	
	void setFont(shared_ptr<ofxSmartFont> font);
	
	void draw();
	
private:
	float x;
	float y;
	float w;
	float h;
	float r;
	string text = "";
	shared_ptr<ofxSmartFont> font;
};

#endif /* InputTextField_hpp */
