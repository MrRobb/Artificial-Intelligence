//
//  Chatbot.cpp
//  piBot
//
//  Created by Roberto Ariosa Hernández on 21/01/2018.
//

#include "Chatbot.hpp"

Message Chatbot::whatAreYouTalkingAbout(string text)
{
	string s = "";
	Message wit = understandSentence(text);
	ofxJSON json;
	
	if (not wit.error and json.parse(wit.text)) {
		ofLog() << "Parsed successfully" << endl;
		return {"I understand.", false};
	}
	
	else {
		ofLogError() << "Error --> parsing: " << wit.text << endl;
		return {"I don't understand that, yet.", true};
	}
}

{
	ofHttpRequest y;
	
	// Create request
	y.url = "https://api.wit.ai/message?v=20180121&q=" + urlEncoding(text);
	y.headers["Authorization"] = "Bearer WIXOTR45JU26WFBYK6QIQLHMM4MK4NKL";
	y.GET;
	
	// Execute request
	auto response = ofURLFileLoader().handleRequest(y);
	
	// Check response
	switch (response.status)
	{
		case 400:
			return {response.data, false};
			break;
			
		default:
			return {response.error, true};
			break;
	}
}

Message Chatbot::understandSentence(string &text)
{
	// Create request
	string version = ofGetTimestampString("%Y%m%d");
	string url = "https://api.wit.ai/message?v=" + version + "&q=" + urlEncoding(text);
	return get(url);
}

string Chatbot::urlEncoding(const string &text)
{
	ostringstream escaped;
	escaped.fill('0');
	escaped << hex;
	
	for (string::const_iterator i = text.begin(), n = text.end(); i != n; ++i)
	{
		string::value_type c = (*i);
		
		// Keep alphanumeric and other accepted characters intact
		if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~')
		{
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

Message Chatbot::get(string& url)
{
	ofHttpRequest req;
	
	// Create request
	req.url = url;
	req.headers["Authorization"] = "Bearer SV4X2QKSLNUAHJWMQG37JURK54R23GT2";
	req.GET;
	
	// Execute request
	auto resp = ofURLFileLoader().handleRequest(req);
	
	switch (resp.status)
	{
		case 200:
			return {resp.data, false};
			break;
		
		case 400:
			return {resp.data, false};
			break;
			
		default:
			return {resp.error, true};
			break;
	}
}
