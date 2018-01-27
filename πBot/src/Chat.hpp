//
//  Chat.hpp
//  piBot
//
//  Created by Roberto Ariosa Hernández on 24/01/2018.
//

#ifndef Chat_hpp
#define Chat_hpp

#include <vector>

#include "ofMain.h"
#include "ofxSmartFont.h"

using namespace std;

struct ChatMessage {
	bool user;
	string message;
};

class Chat {
	
public:
	
	Chat();
	
	Chat(string path);
	
	bool loadChat();
	
	bool saveChat();
	
	void setRect(float w, float h);
	
	void setFont(shared_ptr<ofxSmartFont> font);
	
	void writeMessage(bool user, string message);
	
	void update();
	
	void draw();
	
private:
	vector<ChatMessage> chat;
	
	ofFile file;
	
	float x;
	float y;
	float sizeOfMessage = 50;
	float separationMessage = 20;
	shared_ptr<ofxSmartFont> font;
};

#endif /* Chat_hpp */
