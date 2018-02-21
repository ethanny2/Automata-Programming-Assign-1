#ifndef NODE_H
#define NODE_H
class Node{
  public:
	 Node(){};
	 Node(int stateNumIn , bool startIn , bool acceptIn){
       	 	stateNum = stateNumIn;
        	startState = startIn;
		acceptState = acceptIn;
    	}
	int stateNum; /* 0-1000*/
	/*Both start false and set as needed */
	bool startState = false;
	bool acceptState = false;
	/*Not sure yet but using a map <int, int> 
	with <transtionSymbol,endState> */
	/*WE NEED 2 MAPS THIS ONE IS FOR INTS */
	multimap<int,int> transitionsMap; /* At most 100,000 transitions max size of map on G7 computer is 461168601842738790*/
	/* This map is for a-z lower case*/
	multimap<char,int> transitionsCharMap;
	void setTransition(int,int);
	void setTransitionChar(char,int);
	void printTransitions();
	/* Uses machine states global variable and need both functions to look
	for both chars and int*/
	/*Check if any of the nodes in machineStates have this transition RETURNS THE NEXT STATE That it transitions to */
	bool searchForTransition(int transitionNum, string currentInputString ,int);
	bool searchForTransition(char transitionChar , string currentInputString ,int);
	/* Searching for a reference to the state number*/
	Node* searchForState(int nextState);
};


#endif
