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

string Chatbot::urlEncoding(const string &text) {
	ostringstream escaped;
	escaped.fill('0');
	escaped << hex;
	
	for (string::const_iterator i = text.begin(), n = text.end(); i != n; ++i) {
		string::value_type c = (*i);
		
		// Keep alphanumeric and other accepted characters intact
		if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~') {
			escaped << c;
			continue;
		}
		
		// Any other characters are percent-encoded
		escaped << uppercase;
		escaped << '%' << setw(2) << int((unsigned char) c);
		escaped << nouppercase;
	}
	
	return escaped.str();
}
