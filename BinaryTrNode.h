// BinaryTrNode.h
// Trevor Dine, Matthew Sundberg
// COSC 2030 - 01
// Project 2
// 15 December 2018

#ifndef BINARY_TR_NODE_H
#define	BINARY_TR_NODE_H

#include <vector>
#include <string>
#include "RandomUtilities.h"

using std::vector;
using std::string;
using std::hash;
using std::to_string;

class BinaryTrNode
{
public:
	string id;
	string parentId;
	string rawEvent;
	string lHash;
	string rHash;
	vector<string> lHist;
	vector<string> rHist;

	BinaryTrNode()
	{
		rawEvent = createRandRawEvent();	
		id = "";
		parentId = "";
		lHash = "";
		rHash = "";
	}

	BinaryTrNode(string input)
	{
		if (input.size() <= 1024)
		{
			rawEvent = input;
		}
		else
		{
			rawEvent = createRandRawEvent();
		}
		id = "";
		parentId = "";
		lHash = "";
		rHash = "";
	}

	// Function to create a randomized raw event.
	string createRandRawEvent();

	// Function to set parent ID
	void setParentId(string parId);

	// Function to set the left hash
	void setLHash();

	// Function to set the right hash
	void setRHash();
};

string BinaryTrNode::createRandRawEvent()
{
	char characters[36] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	string output;

	for (int i = 0; i < randReal(8, 1024); i++)
	{
		output += characters[static_cast<int>(randReal(0, 35))];
	}

	return output;
}

#endif