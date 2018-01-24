//
//  Graph.hpp
//  piBot
//
//  Created by Roberto Ariosa Hernández on 23/01/2018.
//

#ifndef Graph_hpp
#define Graph_hpp

#include <vector>
#include <string>
#include <map>
#include <set>

using namespace std;

struct Action {
	// ID
	string value;
	vector<string> synonymous;
	
	// Agent: Node.value
	string agent;
	
	// Object: Node.value
	string object;
};

struct Node {
	// ID
	string value;
	vector<string> synonymous;
	
	// Class
	string entity;
	
	// Attributes
	map<string, string> attributes;
	
	// Actions
	set<Action> actions;
};

typedef map<string, Node> Graph;

#endif /* Graph_hpp */
