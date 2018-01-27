//
//  Graph.cpp
//  piBot
//
//  Created by Roberto Ariosa Hernández on 25/01/2018.
//

#include "Graph.hpp"

bool JSONToData(const ofxJSON& parser, Graph& brain, Entities& entities, Relations& relations)
{
	// Load entities
	for (auto& entity : parser["entities"])
		entities.insert(entity.asString());
	
	// Load relations
	for (auto& relation : parser["relations"])
		relations.insert(relation.asString());
	
	// Load nodes
	for (auto& node : parser["nodes"])
	{
		Node n;
		n.value = node["value"].asString();
		n.entity = node["entity"].asString();
		
		for (auto& synonym : node["synonymous"])
			n.synonymous.insert(synonym.asString());
		
		auto members = node["attributes"].getMemberNames();
		for (auto& member : members)
			n.attributes[member] = node["attributes"][member].asString();
		
		for (auto& action : node["actions"])
		{
			Action a (action["value"].asString());
			a.agent = action["agent"].asString();
			a.value = action["object"].asString();
			for (auto& synonym : action["synonymous"])
				a.addSynonym(synonym.asString());
			n.actions.insert(a);
		}
		
		brain[n.value] = n;
	}
	return true;
}

bool dataToJSON(ofxJSON& parser, const Graph& brain, const Entities& entities, const Relations& relations)
{
	// Save entities
	ofxJSON::Value ent_value;
	for (auto& value : entities)
		ent_value.append(value);
	parser["entities"] = ent_value;
	
	// Save relations
	ofxJSON::Value rel_value;
	for (auto& value : relations)
		rel_value.append(value);
	parser["relations"] = rel_value;
	
	// Save nodes
	ofxJSON::Value array_nodes;
	for (auto& node : brain)
	{
		ofxJSON::Value node_obj;
		
		// ID
		node_obj["value"] = node.second.value;
		
		// Synonymous
		ofxJSON::Value synonymous;
		for (auto& synonym : node.second.synonymous)
			synonymous.append(synonym);
		node_obj["synonymous"] = synonymous;
		
		// Class
		node_obj["entity"] = node.second.entity;
		
		// Attributes
		ofxJSON::Value attributes;
		for (auto& attr : node.second.attributes)
			attributes[attr.first] = attr.second;
		node_obj["attributes"] = attributes;
		
		// Actions
		ofxJSON::Value actions;
		for (auto& action : node.second.actions)
		{
			ofxJSON::Value action_obj;
			
			action_obj["value"] = action.value;
			
			for (auto& synonym : action.synonymous)
				action_obj["synonymous"].append(synonym);
			
			action_obj["agent"] = action.agent;
			
			action_obj["object"] = action.object;
			
			actions.append(action_obj);
		}
		node_obj["actions"] = actions;
		
		array_nodes.append(node_obj);
	}
	parser["nodes"] = array_nodes;
	
	return true;
}
