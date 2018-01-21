//
//  Chatbot.cpp
//  piBot
//
//  Created by Roberto Ariosa Hernández on 21/01/2018.
//

#include "Chatbot.hpp"

string Chatbot::whatAreYouTalkingAbout(string text)
{
	string s = "";
	string wit = understandSentence(text);
	ofxJSON js;
	
	bool b = js.parse(wit);
	
	if (b) {
		ofLog() << js["entities"] << endl;
	}
	
	else {
		ofLogError() << "Error --> parsing" << endl;
	}
	
	return s;
}

string Chatbot::understandSentence(string &text)
{
	ofHttpRequest y;
	
	// Create request
	y.url = "https://api.wit.ai/message?v=20180121&q=" + urlEncoding(text);
	y.headers["Authorization"] = "Bearer WE3JCWB5KU23OC5ZTYBOI5NAOESFD7VN";
	y.GET;
	
	// Execute request
	auto response = ofURLFileLoader().handleRequest(y);
	return response.data;
}

string Chatbot::urlEncoding(const string &text)
{
	string ret;
	char ch;
	int ii;
	
	for (int i = 0; i < text.length(); i++)
	{
		if (int(text[i]) == '%')
		{
			sscanf(text.substr(i + 1, 2).c_str(), "%x", &ii);
			ch = static_cast<char> (ii);
			ret += ch;
			i = i + 2;
		}
		else
			ret += text[i];
	}
	
	return ret;
}
