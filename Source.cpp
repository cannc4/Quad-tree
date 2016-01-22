#include "TwoDimTree.h"
#include "LinkedList.h"
#include "Rectangle.h"
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>


using namespace std;


int main(){


	ifstream file;
	file.open("rectdb.txt");//Opening of file
	if(file.fail())	{
		cout << "Can't read input file... Exiting..." << endl; 
		system("pause"); 
		return 0; 
	}
	string line;
	getline(file,line);	//Input of big rectangle

	int t, l, b, r;
	istringstream iss(line);
	iss >> t >> l >> b >> r;

	cout << t << " " << l << " " << b << " " << r << endl;

	Rectangle bigExtent(t, l, b, r);
	TwoDimTree tree(bigExtent); // Main tree 
	
	
	int x=0;
	int y= 0;
	//struct to keep track of found rectangles and x,y point
	struct DB
	{
		DB(int x_, int y_){
			x = x_; y=y_;}
		int x;
		int y;
		vector <Rectangle> str_Rec;
	};

	vector<DB> resultList; //a list to hold the rectangles containing the points

	cout <<"Reading the database..." << endl;

	file >> t;
	while(getline(file, line))
	{
		//cout << line << endl;
		istringstream iss2(line);
		iss2 >> t;
		if(t!=-1)
		{
		iss2 >> l >> b >> r;
		tree.insert(Rectangle(t,l,b,r));	//Inserting rectangles with recurssion calls
		}
		else
			break;
	}
	
	cout <<"Enter input coordinates" << endl;
	x=0;
	while(x!=-1){
	cin >> x >> y;
		if(x != -1)
		{
			DB data(x,y);
			tree.search(x,y,data.str_Rec); //Searching tree for the given input
			resultList.push_back(data); //Pushing it into result vector
		}
	}

	//Printing resultList (Output)
	for(int i = 0; i < resultList.size(); i++)
	{
		cout << endl;
		cout << resultList[i].x << " " << resultList[i].y << endl;
		cout << resultList[i].str_Rec.size() << endl;
		for(int j = 0; j < resultList[i].str_Rec.size(); j++)
			cout << resultList[i].str_Rec[j].top() <<" "<< resultList[i].str_Rec[j].left() <<" "<< resultList[i].str_Rec[j].bottom() <<" "<< resultList[i].str_Rec[j].right() << endl;
	}

	tree.makeEmpty();//destructor


system("pause");
cin.get();
cin.ignore();
return 0;
}