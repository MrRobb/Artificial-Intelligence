//
//  Graph.hpp
//  piBot
//
//  Created by Roberto Ariosa Hernández on 23/01/2018.
//

#ifndef Graph_hpp
#define Graph_hpp

#include <string>
#include <map>
#include <set>
#include <unordered_set>
#include <unordered_map>

#include "ofxJSON.h"

using namespace std;

struct Action {
	// ID
	string value;
	set<string> synonymous;
	
	// Agent: Node.value
	string agent;
	
	// Object: Node.value
	string object;
	
	bool operator==(const Action &other) const
	{
		return (value == other.value
			  && agent == other.agent
			  && object == other.object);
	}
	
	Action(string value, string agent = "", string object = "")
	{
		this->value = value;
		this->agent = agent;
		this->object = object;
	}
	
	bool addSynonym(string synonym)
	{
		this->synonymous.insert(synonym);
	}
};

namespace std {
	
	template <>
	struct hash<Action>
	{
		std::size_t operator()(const Action& k) const
		{
			using std::size_t;
			using std::hash;
			using std::string;
			
			// Compute individual hash values for first,
			// second and third and combine them using XOR
			// and bit shifting:
			
			return ((hash<string>()(k.value)
					^ (hash<string>()(k.agent) << 1)) >> 1)
					^ (hash<string>()(k.object) << 1);
		}
	};
}

struct Node {
	// ID
	string value;
	set<string> synonymous;
	
	// Class
	string entity;
	
	// Attributes
	map<string, string> attributes;
	
	// Actions
	unordered_set<Action> actions;
	
	bool addSynonym(string synonym)
	{
		synonymous.insert(synonym);
	}
	
	bool addAttribute(string attribute, string value)
	{
		attributes[attribute] = value;
	}
	
	bool addActionToValue(Action action)
	{
		actions.insert(action);
	}
};


typedef map<string, Node> Graph;
typedef set<string> Entities;
typedef set<string> Relations;

bool JSONToData(const ofxJSON& parser, Graph& brain, Entities& entities, Relations& relations);
bool dataToJSON(ofxJSON& parser, const Graph& brain, const Entities& entities, const Relations& relations);

#endif /* Graph_hpp */
