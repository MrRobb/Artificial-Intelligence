//
//  InputTextField.cpp
//  piBot
//
//  Created by Roberto Ariosa Hernández on 22/01/2018.
//

#include "InputTextField.hpp"

InputTextField::InputTextField()
{
}

InputTextField::InputTextField(const string &text)
{
	this->text = text;
}

string InputTextField::getText()
{
	return this->text;
}

void InputTextField::setText(const string &text)
{
	this->text = text;
}

void InputTextField::update(int key)
{
	// Alpha numeric
	if ((key >= 'a' and key <= 'z') or
		(key >= 'A' and key <= 'Z') or
		(key == ' ') or
		(key == '?') or
		(key == '!'))
	{
		this->text.push_back(char(key));
	}
	
	else if (key == OF_KEY_BACKSPACE)
	{
		if (not text.empty())
			this->text.pop_back();
	}
	
	// Send Message
	else if (key == OF_KEY_RETURN)
	{
		ofSendMessage(this->text);
		this->text = "";
	}
	
	// Other
	else if ((key != OF_KEY_SHIFT) and
			 (key != OF_KEY_COMMAND))
	{
		cerr << "This is weird: " << char(key) << endl;
	}
}

void InputTextField::setRect(float x, float y, float w, float h, float r)
{
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
	this->r = r;
}

void InputTextField::setFont(shared_ptr<ofxSmartFont> font)
{
	this->font = font;
}

void InputTextField::draw()
{
	// Draw box
	ofSetHexColor(ofHexToInt("232F32"));
	ofDrawRectRounded(this->x, this->y, this->w, this->h, this->r);
	
	// Draw text
	ofSetColor(255, 255, 255, 255);
	font->draw(this->text, this->x + 20, this->y + this->h / 2 + font->height(this->text) / 2);
}
