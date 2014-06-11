#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "lexer.h"
using namespace std;

void lexicalOutput()
{
    int line = 0;   //line of code
    bool isComment = false;
    string str;
    ifstream ifs;
    ifs.open("main.c", ifstream::in);
    ofstream ofs;
    ofs.open("token.txt", ofstream::out);

    while(getline(ifs, str))
    {
	isComment = false;
	ofs<<"Line : "<<++line<<endl;
	stringstream ss (str);
	while(getline(ss, str, ' '))
	{
	    if(ss.fail()) break;
	    for(string::iterator it = str.begin(); it != str.end(); ++it)
		if(*it == '\t')
		    str.erase(0, 1); //if the first symbol is tab

	    switch(lexer(str))
	    {
		case 'K':
		    if(mymap.find(str)->second == "Operator")
		    ofs<<"\t"<<"  <Operator> : "<<str<<endl;
		    else if(mymap.find(str)->second == "Keyword")
		    ofs<<"\t"<<"   <Keyword> : "<<str<<endl;
		    else if(mymap.find(str)->second == "Special")
		    ofs<<"\t"<<"   <Special> : "<<str<<endl;
		    break;
		case 'D':
		    ofs<<"\t"<<"    <Number> : "<<str<<endl;
		    break;
		case 'I':
		    ofs<<"\t"<<"<Identifier> : "<<str<<endl;
		    break;
		case 'C':
		    ofs<<"\t"<<"      <Char> : "<<str<<endl;
		    break;
		case 'M':
		    isComment = true;
		    break;
		case 'E':
		    ofs<<"\t"<<"     <Error> : "<<str<<endl;
		    break;
	    }
	    if(isComment)
		break;
	}
    }
    ifs.close();
    ofs.close();
}
