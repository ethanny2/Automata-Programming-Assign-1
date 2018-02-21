#ifndef CONFIG_H
#define CONFIG_H

class Node;
#include<string>
using namespace std;
/* Represents the configurations we need each has a CURRENT STATE THE REMAINING INPUT STRING */
class Configuration{
	public:
	/* MIGHT NOT WORK*/
	Configuration(Node *currentStateIn , string remainingInputIn){
		currentState = currentStateIn;
		remainingInput = remainingInputIn;
		accept = false;
	}
	Node *currentState;
	string remainingInput;
	/* Mark true if the input string is empty and the currentState has the boolean signifying that it is an accept state*/
	bool accept;
	/* After all configurations are processed look through the configList vector and check if it has an accept state, if so set it and print it	*/
	//void printAcceptState();
	void setBooleanAccept();
};


#endif
