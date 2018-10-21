#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <string.h>
#include    <vector>
#include "handle.h"

using namespace std;

class tokenList{
    vector<string> list;

    public:
    string front();
    void append(string);
    void next();
};

string tokenList::front(){
    return list.front();
}
void tokenList::append(string str){
    list.push_back(str);
}
void tokenList::next(){
    list.erase(list.begin());
}

//Executes Query
void execQuery(tokenList tokens){

    if(tokens.front()=="create"){
        cout<< endl << "create detected " <<endl ;
        tokens.next();
    }
}

//Gets Input
void getInput(){

    string cliInput; // CLIinput
    tokenList tokens; //Output token vector

    ///TESTING///
    string temp="";
    /////////////

    getline(cin,cliInput); //get single line
 
    char * str = &cliInput[0]; //string -> char*
    char * token_pointer;   //Token
    
    token_pointer = strtok (str," "); //Tokenize against " "
    while (token_pointer != NULL)
    {
        string token = token_pointer;
        tokens.append(token);

        ////TESTING////
        temp = temp + token + " ";
        ///////////////

        cout << endl << token;

        if(token==";") //Reads only until ";"
            {
                break;
            }
        
        token_pointer = strtok (NULL, " ");
    }

    ///TESTING///
    cout << endl << "Accepted Query: \" " << temp << " \" ";
    ////////////
    execQuery(tokens);
}

