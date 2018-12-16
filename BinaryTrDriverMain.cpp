#include "BinaryTr.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

string unlovedHash(string stuff);

void getRequest(string & request)
{
	cout << "Enter request: ";
	cin >> request;
}


int main()
{
	randomizeSeed();

	BinaryTr theTree;

	string request;
	getRequest(request);

	while (request != "quit")
	{
		if (request == "change")
		{
			string id;
			cout << endl << "Please specify and id: ";
			cin >> id;
			string newRaw;
			cout << endl << "Please enter the new raw event: ";
			cin >> newRaw;
			theTree.insertNode(id, newRaw);
		}
		else if (request == "display")
		{
			theTree.displayIds();
		}
		else if (request == "find")
		{
			string tempId;
			cin >> tempId;
			theTree.findNode(tempId);
		}
		else if (request == "update")
		{
			theTree.updateNodes();
		}
		else if (request == "add")
		{
			theTree.addLevel();
		}
		else
		{
			cout << "Known requests: change <id>, add, display, find <id>, "
				<< "update, quit" << endl;
		}

		getRequest(request);
	}

	return 0;
}

// this hash == </3
string unlovedHash(string stuff)
{
	string value = "";
	for (int i = 0; i < stuff.length(); i++)
	{
		int rand = randReal(0, stuff.length());
		value += stuff.substr(rand);
	}
	return value;
}