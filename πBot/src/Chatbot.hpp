//
//  Chatbot.hpp
//  piBot
//
//  Created by Roberto Ariosa Hernández on 21/01/2018.
//

#ifndef Chatbot_hpp
#define Chatbot_hpp

#include "ofxJSON.h"

using namespace std;

class Chatbot {
	
public:
	/**
	 @brief Processes the data and provides little response about his understanding.
	 @param text The text to process and comment about.
	 @return Little comment about the data provided.
	 */
	string whatAreYouTalkingAbout(string text);
	
private:
	/**
	 @brief Sends the string to the NLP engine via HTTP request and returns the response.
	 @param text Is the sentence to process.
	 @return The response JSON in string format.
	 */
	string understandSentence(string &text);
	
	/**
	 @brief Encodes most of the non-alphanumeric values to URL encoding.
	 @param text The string to encode.
	 @post The string is URL ready.
	 */
	string urlEncoding(const string &text);
};

#endif /* Chatbot_hpp */
