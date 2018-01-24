//
//  Chat.cpp
//  piBot
//
//  Created by Roberto Ariosa Hernández on 24/01/2018.
//

#include "Chat.hpp"

Chat::Chat(){}

Chat::Chat(ofFile &file)
{
	this->file = file;
	
	if (this->file.exists())
		loadChat();
	
	else
	{
		this->file.create();
		this->file.changeMode(ofFile::ReadWrite);
	}
	
	this->x = 0;
	this->y = ofGetHeight() - 100;
}

bool Chat::loadChat()
{
	this->file.changeMode(ofFile::ReadWrite);
	
	ofBuffer buff = this->file.readToBuffer();
	int u = 0;
	for (string line : buff.getLines())
	{
		ChatMessage msg;
		msg.user = line[0] == '1';
		msg.message = line.substr(1);
		this->chat.push_back(msg);
	}
}

bool Chat::saveChat()
{
	ofBuffer buff;
	this->file.changeMode(ofFile::ReadWrite);
	
	for (auto& msg : chat)
	{
		buff.append((msg.user ? "1" : "0") + msg.message + "\n");
	}
	
	this->file.writeFromBuffer(buff);
}

void Chat::setRect(float w, float h)
{
	this->x = 0;
	this->y = h - 100;
}

void Chat::setFont(shared_ptr<ofxSmartFont> font)
{
	this->font = font;
	this->sizeOfMessage = font->getLineHeight();
}

void Chat::writeMessage(bool user, string message)
{
	chat.push_back({user, message});
}

void Chat::update()
{
	int n = chat.size();
	for (int i = 0; i < n and y - (i + 1) * (sizeOfMessage + separationMessage) >= 0; i++)
	{
		// y
		float y_msg = y - (i + 1) * (sizeOfMessage + separationMessage);
		
		// x
		float x_msg;
		if (not chat[n - 1 - i].user)
			x_msg = 30;
		else
			x_msg = ofGetWidth() - font->width(chat[n - 1 - i].message) - 30;
		
		// Draw
		ofSetColor(255, 255, 255);
		font->draw(chat[n - 1 - i].message, x_msg, y_msg);
	}
}

void Chat::draw(){}
