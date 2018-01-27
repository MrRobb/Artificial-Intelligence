//
//  Chatbot.hpp
//  piBot
//
//  Created by Roberto Ariosa Hernández on 21/01/2018.
//

#ifndef Chatbot_hpp
#define Chatbot_hpp

#include "ofxJSON.h"
#include "brain/Graph.hpp"
#include "Chat.hpp"

using namespace std;

struct Message {
	string text;
	bool error;
};

class Chatbot {
	
public:
	Chatbot();
	
	/**
	 @brief Processes the data and provides little response about his understanding.
	 @param text The text to process and comment about.
	 @return Little comment about the data provided.
	 */
	Message whatAreYouTalkingAbout(string text);
	
	bool fillBrain(string path, Chat& chat);
	
	bool loadBrain();
	
	bool saveBrain();
	
	bool addValue(Node value);
	
	bool addEntity(string entity);
	
	bool addRelation(string action);
	
private:
	/**
	 @brief Sends the string to the NLP engine via HTTP request and returns the response.
	 @param text Is the sentence to process.
	 @return The response JSON in string format.
	 */
	Message understandSentence(string &text);
	
	/**
	 @brief Encodes most of the non-alphanumeric values to URL encoding.
	 @param text The string to encode.
	 @post The string is URL ready.
	 */
	string urlEncoding(const string &text);
	
	Message get(string& url);
	
	Graph brain;
	
	Entities entities;
	
	Relations relations;
	
	ofFile brain_file;
};

#endif /* Chatbot_hpp */
