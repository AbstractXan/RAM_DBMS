%{
	#include <bits/stdc++.h>
	#include "handle.h"
	
	using namespace std;
%}

alphanum [a-zA-Z0-9]
digit [0-9]
lttr [a-zA-Z]
sp [" "]

%%

"," {
	string s = ",";
	tokenBuffer.push_back(s);
}
"\""(({alphanum}+)?{sp}?)*{alphanum}+"\"" {
	string s = yytext;
	tokenBuffer.push_back(s);
}
{lttr}+ {
	string s = yytext;
	for(int i=0; i<s.length(); i++)
		tolower(s[i]);
	if(!s.compare("varchar")){
		s = "string";
	}
	tokenBuffer.push_back(s);
}
{digit}+ {
	string s = yytext;
	tokenBuffer.push_back(s);
}
"\("{digit}+"\)" ;
"\("|"\)"|{sp} ;
";".*

%%

int yywrap(){
	return 1;
}

int main(){
	ofstream fptr;
	fptr.open("queries.txt");
	string s;
	getline(cin, s);
	fptr << s;
	fptr.close();
	yyin = fopen("queries.txt", "r");
	yylex();
	for(int i=0; i<tokenBuffer.size(); i++){
		cout<<tokenBuffer[i]<<" ";
	}
}