/*
Programming Assignment 1: CS 373 Simulate an (partial)NFA
*/
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <fstream>
#include <cstring>
#include <ctype.h>
using namespace std;
#define MAX_CONFIG_SIZE 1000000
#define MAX_NUMBER_STATES 2000
/* Won't be used multimap is already allocates dynamically. Its a tree*/
#define MAX_TRANSITIONS_SIZE 100000
class Node;
class Configuration;

/*Global var to hold the input string, don't know the maximum number of character(?) */
string globalInputString;
/*Nodes will also be in global list */
vector<Node> machineStates;
vector<Configuration> configList;




/* Finds the node re*/


/*As opposed to allocating a char array, use c++ [] operator on strings to index into the 
specfied character. The string is a global variable */
void parseInputString(string inputString){
	cout<<inputString<<endl;
	globalInputString = inputString;
}


/*Represents 1 node in the NFA. Making */



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
	void searchForTransition(int transitionNum, string currentInputString ,int);
	void searchForTransition(char transitionChar , string currentInputString ,int);
	/* Searching for a reference to the state number*/
	Node searchForState(int nextState);
};

/* Should only look through the current nodes list of transitions*/
void Node::searchForTransition(int transitionNum , string currentInputString , int configIndex){
	multimap<int,int>::iterator pos;
	int foundState = 0;
        if(!(this->transitionsMap.empty())){
        	for (pos = this->transitionsMap.begin(); pos != this->transitionsMap.end(); ++pos){
			if(pos->first == transitionNum && foundState == 0){
					/*Found matching state with transition num */
					cout<<"Found matching transition with SYMBOL "<< pos->first <<endl;
					foundState++;
					//Change the state of current config object at the index and reduce the input by 1
					configList[configIndex].currentState = (this->searchForState(pos->second));
					configList[configIndex].remainingInput =  currentInputString;
			}else if(pos->first == transitionNum){
				/*Create new config objects and push to list with -1 symbol input */
				  Configuration temp(this->searchForState(pos->second), currentInputString);_
                                  configList.push_back( temp );
			}
                }
        }


}

void Node::searchForTransition(char transitionChar , string currentInputString , int configIndex){
        multimap<char,int>::iterator pos;
        int i;
        for(i=0;i<machineStates.size();i++){
                if(!(this->transitionsCharMap.empty())){
                        for (pos = this->transitionsCharMap.begin(); pos != this->transitionsCharMap.end(); ++pos){
				if(pos->first == transitionChar){
					cout<<"Found matching transition with SYMBOL " << pos->first <<endl;
				}
                        }
                }
        }
}



/* Dont know if this works !!!!!!!!!!!1 it does but returns a copy*/
Node Node::searchForState(int nextState){
	int i;
	for(i=0;i<machineStates.size();i++){
		if(machineStates[i].stateNum==nextState){
			return	machineStates[i];
		}
	}
	//return
}







void Node::setTransition(int symbol , int endState){
	//cout<<"!!!!!!!"<< this->transitionsMap.max_size()<<endl;
	this->transitionsMap.insert(pair<int,int> (symbol,endState));
}


void Node::setTransitionChar(char symbol, int endState){
	this->transitionsCharMap.insert(pair<char,int> (symbol,endState));
	//this->transitionsCharMap[symbol] = endState;
}


/* For printing all transition paths (symbols + end states) for each individual Node/machine state. Returns string because it is exclusively for use with the
printMachineStates function*/
void Node::printTransitions(){
	multimap<int,int>::iterator pos;
	multimap<char,int>::iterator pos2;
	if(!(this->transitionsMap.empty())){
    		for (pos = this->transitionsMap.begin(); pos != this->transitionsMap.end(); ++pos) {
        		cout << "Symbol: \"" << pos->first << "\" "
             		<< "From State: " <<  this->stateNum <<" to "<<"To State: " << pos->second << endl;
    		}
	}
	if(!(this->transitionsCharMap.empty())){
        	for (pos2 = this->transitionsCharMap.begin(); pos2 != this->transitionsCharMap.end(); ++pos2) {
                        cout << "Symbol: \"" << pos2->first << "\" "
                        << "From State: " <<  this->stateNum <<" to "<<"To State: " << pos2->second << endl;
               }
        }

}





std::ostream &operator<<(std::ostream &os, Node const &node){
	string temp;
	if(node.startState){
		temp = "Start Node";
	}else if(node.acceptState){
		temp = "Accept Node";
	} 
    	return os<<"State#: "<<node.stateNum<<" , "<<temp<<endl;
}














/* Prints all State details from the machine including each states number, weather or not it is a start or accept state 
and the number of transitions starting from the speicifed state*/
void printMachineStates(){
	int i;
	for(i=0;i<machineStates.size();i++){
		cout<<machineStates[i];
		cout<<"Printing transitions"<<endl;
		machineStates[i].printTransitions();
		cout<<"*************************************************************"<<endl;

	}
}

/*First traverse the existing list to see if the start state Exists  */
void addState(int stateNumIn , int transitionInt , char transitionChar , int endState){
	int i;
	bool nodeExists;
        for(i=0;i<machineStates.size();i++){
                if(machineStates[i].stateNum ==stateNumIn){
			/* Node already exists set transtion*/
			//cout<<"Node exists"<<endl;
			if(transitionInt==-1){
				/* set char Map*/
				machineStates[i].setTransitionChar(transitionChar,endState);
			}else{
				/* Set int map*/
				machineStates[i].setTransition(transitionInt, endState);
			}
			nodeExists = true;
			break;
		}
	}
	/*This is a new node append to list and add transitions*/
	if(!nodeExists){
		Node temp = Node(stateNumIn,false,false);
		//cout<<"Creating new node"<<endl;
		if(transitionInt==-1){
        		/* set char Map*/
			//cout<<transitionChar<<endl;
                	temp.setTransitionChar(transitionChar , endState);
        	}else{
                	/* Set int map*/
                	temp.setTransition(transitionInt, endState);
        	}
		machineStates.push_back(temp);
	}
}


/* Parses input.txt file to create machine layout */
void  createMachineLayout(char * fileName){
	ifstream infile;
	string curLine;
	infile.open(fileName);
	if(!infile){
		cout<<"Error reading input file"<<endl;
		exit(0);
	}
	while(getline(infile,curLine)){
		//cout<<curLine<<endl;
		/*If the string contains "state" then parse one way */
		if (curLine.find("state") != string::npos){
			string str1 = "start";
			string str2 = "accept";
			const char * temp1 = str1.c_str(); //start
			const char * temp2 = str2.c_str(); //accept
    			//cout << "Parsing 'state' lines" << endl;
			/* Strip the word state and \t from the string*/
			curLine.replace(0, 6, "");
			string delimiter = "\t";
			string token = curLine.substr(0, curLine.find(delimiter));
			//cout<<token<<endl;
			int stateNum = stoi(token);
			//Check if it is an accept or start state
			curLine = curLine.replace(0,curLine.find("\t") +1,"");
			//cout<<curLine<<endl;
			const char * cString = curLine.c_str();
			if(strcmp(cString, temp1)==0){
				/* This a start node*/
				Node temp(stateNum,true,false);
				/*ALSO PUT THIS START INTO THE FIRST CONFIG*/
				//Configuration configObj(temp,globalInputString);
				//configList.push_back(configObj);
				machineStates.push_back(temp);
			}else if(strcmp(cString,temp2)==0){
				Node temp(stateNum,false,true);
				machineStates.push_back(temp);
			}
		}else if(curLine.find("transition")!= string::npos){
			int transitionInt = -1;
			int startStateNum = -1;
			int endStateNum = -1;
			char transitionChar;
			/*strip word "transition" + \t for the tab to get the numbers*/
			curLine.erase(0,11);
			//cout<<curLine<<endl;
                        string delimiter = "\t";
                        string token = curLine.substr(0, curLine.find(delimiter));
                         startStateNum = stoi(token); //Works on all numbers 0-1000
			/* remove the starting state num*/
			curLine = curLine.replace(0,curLine.find("\t") +1,"");
			token = curLine.substr(0, curLine.find(delimiter));
			/*try stoi if it fails this is a char*/
			try{
				transitionInt = stoi(token);
			}
			catch(const invalid_argument&){
				//cout<<"Transition symbol was a char"<<endl;
				transitionInt = -1;
				const char* temp = token.c_str();
				transitionChar = token[0];
				//cout<<transitionChar<<endl;
			}
			/* Remove symbol and tab from string*/
			 curLine = curLine.replace(0,curLine.find("\t") +1,"");
			 endStateNum = stoi(curLine);
			// cout<<endStateNum<<"!!!"<<endl;

			/* Pass all vars into addState() it will append a new node if needed or update
			the transitions of another node automatically*/
			addState(startStateNum, transitionInt, transitionChar , endStateNum);
		}
		/*Else if string contains "transition" then do something else */
	}

	/*Check nodes*/
	printMachineStates();

}



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
	void printAcceptState();
	void setBooleanAccept();
};

/*
void Configuration::setBooleanAccept(){
	if(currentState.acceptState){
		accept = true;
	}
}

void Configuration::printAcceptState(){
	int i;
	int acceptConfigFound = false;
	string acceptString = "accept";
	string rejectString = "reject";
	//if there ois at least 1 accept value, don't print the reject values
	for(i=0;i<configList.size();i++){
		//set the correct value
		configList[i].setBooleanAccept();
		if(configList[i].accept){
			acceptString += " "+(configList[i].currentState.stateNum);
			acceptConfigFound = true;
		}else{
			rejectString+= " "+(configList[i].currentState.stateNum);
		}
	}
	if(acceptConfigFound){
		cout<<acceptString<<endl;
	}else{
		cout<<rejectString<<endl;
	}
}
*/




/*Inserts the start state and the full input string into the configList */
void initializeConfigList(){
        int i;
        for(i=0;i<machineStates.size();i++){
                if(machineStates[i].startState){
                        Configuration object = Configuration(&machineStates[i] , globalInputString);
                        configList.push_back(object);
                        cout<<"Set first config"<<endl;
                }
        }
}


/*Executes the input string on every config in the program e.g. runs the program */

/* Loop throuigh*/
void runMainLoop(){
	int i;
	int j;
	char curChar;
	int curInt;
	for(i=0;i<configList.size();i++){
	//	configList[i].currentState->searchForTransition(test
		for(j=0;j<globalInputString.length();j++){
			if(isdigit(globalInputString[j])){
				curInt  = atoi(globalInputString[j]);
				cout<<"CurrInt at index "<<j<<" is "<<curInt<<endl;
			}else{
				/* The symbol is a char*/
				curChar = globalInputString[j];
				cout<<"CurrCar at index "<<j<<" is " << curChar<<endl;

			}
		}
	}



}

int main(int argc, char* argv[]) {
	if (argc!=3){
		cout<<"Incorrect format"<<'\n'<<"Correct format is --> [machine_config.txt] [inputString]"<<endl;
		exit(1);
	}else{
		machineStates.reserve(MAX_NUMBER_STATES);
		configList.reserve(MAX_CONFIG_SIZE);
		string myInput(argv[2]);
		parseInputString(myInput);
		/* Successfully parsed file*/
		createMachineLayout(argv[1]);
		/* Set current State to the start state*/
		//currentState = machineStates.front();
		/* Next create configuration class for start*/
		initializeConfigList();
		/* Test looking for transitions on a config node*/
	//	cout<<configList[0].currentState<<endl;
		configList[0].currentState->printTransitions();
//		int test = 0;
//		configList[0].currentState->searchForTransition(test,configList[0].remainingInput);
		/*Needs to find and add */
	}
 	return 0;
}






