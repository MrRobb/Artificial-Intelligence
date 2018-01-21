//
//  Chatbot.hpp
//  piBot
//
//  Created by Roberto Ariosa Hernández on 21/01/2018.
//

#ifndef Chatbot_hpp
#define Chatbot_hpp

#include <stdio.h>
#include "ofApp.h"

using namespace std;

class Chatbot {
	
public:

	string whatAreYouTalkingAbout(string text);
	
private:
	/**
	 @brief
	 */
	string understandSentence(string &text);
	
	/**
	 @brief Replaces all of the spaces to %20.
	 @param The string to change.
	 @post All of the spaces of the string will contain %20 instead.
	 */
	string urlEncoding(const string &text);
};

#endif /* Chatbot_hpp */
