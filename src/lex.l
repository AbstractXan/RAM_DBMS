%{
	#include <bits/stdc++.h>
	vector < string > buffer;
%}

alphanum [a-zA-Z0-9]
digit [0-9]
lttr [a-zA-Z]
sp [" "]

%%

"\""({alphanum}+)?{sp}?{alphanum}+"\"" {
	string s = yytext;
	buffer.push_back(s);
}
{lttr}+ {
	string s = yytext;
	tolower(s);
	buffer.push_back(s);
}
{digit}+ {
	string s = yytext;
	buffer.push_back(s);
}
";".* ;

%%

int main(){
	yylex();
	return 0;
}
