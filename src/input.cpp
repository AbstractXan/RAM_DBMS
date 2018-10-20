#include <fstream.h>
#include <iostream>

using namespace std;

int main(){
    string query;
	getline(cin, query);
	ofstream f;
	f.open("queries.txt");
	f << query;
    
    return 0;
}