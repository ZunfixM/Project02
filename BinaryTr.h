// BinaryTr.h

#ifndef BINARY_TR_H
#define	BINARY_TR_H

#include <iostream>
#include <vector>
#include <string>
#include "RandomUtilities.h"
#include "BinaryTrNode.h"

using std::cin;
using std::cout;
using std::endl;
using std::to_string;
using std::string;
using std::vector;
using std::hash;

string hashImp(string input);

class BinaryTr
{
public:

	// Constructors
	BinaryTr()
	{
		buildCompleteTree(tree, currentLevel);
		populateIds();
		populateLRChildHash();
		//populateHistories();
	}

	BinaryTr(string newRaw)
	{
		buildCompleteTree(tree, currentLevel);
		populateIds();
		populateLRChildHash();
		//populateHistories();
	}

	// Destructor
	~BinaryTr()
	{
		
	}

	// Accessor function to access the tree.
	vector<BinaryTrNode> getTree()
	{
		return tree;
	}

	// Accessor function to access a node in the tree with its ID, returns the root node if the node with the specified ID was not found.
	void findNode(string ID)
	{
		bool found = false;
		int index;
		for (int i = 0; i < tree.size(); i++)
		{
			if (tree[i].id == ID)
			{
				found = true;
				index = i;
			}
		}

		if (found)
		{
			cout << "The node with an ID of " << tree[index].id << " has the contents: " << endl;
			cout << "Parent Id: " << tree[index].parentId << endl;
			cout << "Raw Event: " << tree[index].rawEvent << endl;
			cout << "Left Hash: " << tree[index].lHash << endl;
			cout << "Left History" << endl;
			for (int j = 0; j < tree[index].lHist.size(); j++)
			{
				cout << tree[index].lHist.at(j) << " ";
			}
			cout << endl;
			cout << "Right Hash: " << tree[index].rHash << endl;
			cout << "Right History: " << endl;
			for (int j = 0; j < tree[index].rHist.size(); j++)
			{
				cout << tree[index].rHist.at(j) << " ";
			}
			cout << endl;
		}
		else
		{
			cout << "The ID could not be found." << endl;
		}
	}

	// Builds the same sized complete binary tree with random nodes.
	void buildCompleteTree(vector<BinaryTrNode> &daTree, int &level);

	// Builds the same sized complete binary tree starting with a given raw event.
	void buildCompTreeRaw(vector<BinaryTrNode> &daTree, int &level, string rawEv);

	// Populates the ID and parent ID
	void populateIds();

	// Populates the left and right children
	void populateLRChildHash();

	// Populates the histories of the parents
	//void populateHistories();

	// Adds a new level to the tree
	void addLevel();

	// Inserts a new node at a specific location in the tree
	void insertNode(string id, string newRaw);

	// Checks all of the nodes and updates any that have not been updated yet.
	void updateNodes();

	// Displays all of the IDs in the order of the vector.
	void displayIds();

	// Generates a random 8 character string for an ID
	string randId();

private:
	vector<BinaryTrNode> tree;
	int currentLevel = 0;
};

void BinaryTr::buildCompleteTree(vector<BinaryTrNode> &daTree, int &level)
{
	for (int i = 0; i < 15; i++)
	{
		daTree.push_back(BinaryTrNode());
	}
	level = 3; // level is set to 3 because the building of this tree doesn't change outside of this function. It would have to be changed when the number of nodes created changes.
}

void BinaryTr::buildCompTreeRaw(vector<BinaryTrNode> &daTree, int &level, string rawEv)
{
	daTree.push_back(BinaryTrNode(rawEv));
	for (int i = 1; i < 15; i++)
	{
		daTree.push_back(BinaryTrNode());
	}
	level = 3; // same case as above.
}

void BinaryTr::populateIds()
{
	for (int i = 0; i < tree.size(); i++)
	{
		if (i > 0)
		{
			tree[i].parentId = tree[i - 1].id;
			tree[i].id = hashImp(hashImp(tree[i].rawEvent) + hashImp(tree[i].parentId)).substr(0, 8);
		}
		else
		{
			tree[i].parentId = randId();
			tree[i].id = hashImp(hashImp(tree[i].rawEvent) + hashImp(tree[i].parentId)).substr(0, 8);
		}
	}
}

void BinaryTr::populateLRChildHash()
{
	for (int i = tree.size() - 1; i >= 0; i--)
	{
		if (((i * 2) + 1) >= tree.size())
		{
			tree[i].lHash = "";
			tree[i].rHash = "";
		}
		else
		{
			int leftChLoc = (i * 2) + 1;
			int rightChLoc = (i * 2) + 2;
			// hash all the stuff from the children together...
			tree[i].lHash = hashImp(hashImp(tree[leftChLoc].id) + hashImp(tree[leftChLoc].parentId) + hashImp(tree[leftChLoc].rawEvent) + hashImp(tree[leftChLoc].lHash) + hashImp(tree[leftChLoc].rHash)).substr(0, 8);
			tree[i].rHash = hashImp(hashImp(tree[rightChLoc].id) + hashImp(tree[rightChLoc].parentId) + hashImp(tree[rightChLoc].rawEvent) + hashImp(tree[rightChLoc].lHash) + hashImp(tree[rightChLoc].rHash)).substr(0, 8);;
		}
	}
}
/*
void BinaryTr::populateHistories()
{
	for (int i = 0; i < tree.size(); i++)
	{
		if (((i * 2) + 1) < tree.size())
		{
			tree[i].lHist.push_back(tree[i].lHash);
			tree[i].rHist.push_back(tree[i].rHash);
		}
	}
}*/

void BinaryTr::addLevel()
{
	int tempVal = 2;
	int startTreeSize = tree.size();
	for (int x = 0; x < currentLevel; x++)
	{
		tempVal = tempVal * 2;
	}

	for (int i = 0; i <= tempVal; i++)
	{
		int currIndex = i + startTreeSize - 1;
		tree.push_back(BinaryTrNode());
		if (currIndex % 2 == 0)
		{
			tree[currIndex].parentId = tree[(currIndex - 2) / 2].id;
		}
		else
		{
			tree[currIndex].parentId = tree[(currIndex - 1) / 2].id;
		}
		tree[currIndex].id = hashImp(hashImp(tree[currIndex].rawEvent) + hashImp(tree[currIndex].parentId)).substr(0, 8);
	}
	currentLevel++;
	// Update all of the nodes above
	updateNodes();
}

void BinaryTr::insertNode(string id, string newRaw)
{
	for (int i = 0; i < tree.size(); i++)
	{
		if (tree[i].id.compare(id) == 0)
		{
			tree[i].rawEvent = newRaw;
			tree[i].id = hashImp(hashImp(tree[i].rawEvent) + hashImp(tree[i].parentId)).substr(0, 8);
		}
	}
	
	// Update all other nodes
	updateNodes();
}

void BinaryTr::updateNodes()
{
	for (int i = tree.size() - 1; i > 0; i--)
	{
		string childHash = hashImp(hashImp(tree[i].id) + hashImp(tree[i].parentId) + hashImp(tree[i].rawEvent) + hashImp(tree[i].lHash) + hashImp(tree[i].rHash)).substr(0, 8);
		if (i % 2 == 0)
		{
			int parentLocation = (i - 2) / 2;
			string parentRightHash = tree[parentLocation].rHash;
			if (childHash != parentRightHash)
			{
				tree[parentLocation].rHist.push_back(parentRightHash);
				tree[parentLocation].rHash = childHash;
			}
		}
		else
		{
			int parentLocation = (i - 1) / 2;
			string parentLeftHash = tree[parentLocation].lHash;
			if (childHash != parentLeftHash)
			{
				tree[parentLocation].lHist.push_back(parentLeftHash);
				tree[parentLocation].lHash = childHash;
			}
		}
	}
}

void BinaryTr::displayIds()
{
	cout << "All IDs displayed in the ordered vector." << endl;
	for (int i = 0; i < tree.size(); i++)
	{
		cout << tree[i].id << endl;
	}
}

string BinaryTr::randId()
{
	char characters[36] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	string output;

	for (int i = 0; i < 8; i++)
	{
		output += characters[static_cast<int>(randReal(0, 35))];
	}

	return output;
}

// Function implementing the standard template library hash function.
string hashImp(string input)
{
	hash<string> newVal;
	size_t sizeVal = newVal(input);
	int hashInt = static_cast<int>(sizeVal);
	return to_string(hashInt);
}

#endif