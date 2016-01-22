/*
HW2 by Can Ince 14241
*/

#ifndef _TWODIMTREE_H
#define _TWODIMTREE_H

#include "Rectangle.h"
#include "LinkedList.h"
#include <vector>

using namespace std;

class TwoDimTree;

class TwoDimTreeNode

{
public:
	Rectangle Extent;
	List<Rectangle> Vertical, Horizontal;
	TwoDimTreeNode *TopLeft, *TopRight, *BottomLeft, *BottomRight;

	//constructor for node
	TwoDimTreeNode(){}  
	TwoDimTreeNode( const Rectangle & rect, TwoDimTreeNode *tl, TwoDimTreeNode *tr, TwoDimTreeNode *bl, TwoDimTreeNode *br)
		: Extent(rect), TopLeft(tl), TopRight(tr), BottomLeft(bl), BottomRight(br) { }
	friend class TwoDimTree;

};

class TwoDimTree
{
public:

	//Constructors
	TwoDimTree();
	TwoDimTree(const Rectangle & r);

	//Destructor
	~TwoDimTree();
	
	//Public makeEmpty(Destructor)
	void makeEmpty();

	//Quadrant Check
	bool Top_Left(const Rectangle & rect, TwoDimTreeNode * &t); 
	bool Top_Right( const Rectangle & rect, TwoDimTreeNode * t);
	bool Bottom_Left( const Rectangle & rect, TwoDimTreeNode * t);
	bool Bottom_Right( const Rectangle & rect, TwoDimTreeNode * t);

	//Valid check for the given rectangle 
	bool Comprise(const Rectangle & rect, TwoDimTreeNode * t); 
	


	//Public insert
	void insert( Rectangle & r);


	//Public search
	void search(const int x, const int y,vector<Rectangle> & str_Rec); 


private:
	TwoDimTreeNode *root;	//root of the quadtree

	//Private insert
	void insert(Rectangle & r, TwoDimTreeNode * & t );

	//Private makeEmpty(Destructor)
	void makeEmpty( TwoDimTreeNode * & t ) const;

	//Private search
	void search(const int x, const int y , vector<Rectangle> & str_Rec, TwoDimTreeNode * t); 
};

//Constructors
TwoDimTree::TwoDimTree() //Default constructor
{
	root = NULL;
}
TwoDimTree::TwoDimTree(const Rectangle & r) 
{
	root = new TwoDimTreeNode(r,NULL,NULL,NULL,NULL);

}

//Destructors
TwoDimTree::~TwoDimTree() //Public destructor
{
	makeEmpty();
}
void TwoDimTree::makeEmpty() 
{
	makeEmpty(root);
}
void TwoDimTree::makeEmpty( TwoDimTreeNode * & t ) const//Private destructor
{
	if( t != NULL ) //Recursive destruction calls untill tree is full empty
	{
		
		makeEmpty( t->TopLeft);
		makeEmpty( t->TopRight);
		makeEmpty( t->BottomLeft);
		makeEmpty( t->BottomRight);

		delete t;
	}
	t = NULL;
}

//These bool functions checks the quadrant for specified rectangle (in which one specified rectangle lies)
bool TwoDimTree::Top_Left( const Rectangle & rect, TwoDimTreeNode * & t)
{
	if (rect.bottom() <= t->Extent.CenterY() && rect.right() <= t->Extent.CenterX())
		return true;
	return false;
}

bool TwoDimTree::Top_Right(const Rectangle & rect, TwoDimTreeNode * t)
{
	if (rect.bottom() <= t->Extent.CenterY() && rect.left() > t->Extent.CenterX())
		return true;
	return false;
}

bool TwoDimTree::Bottom_Left(const Rectangle & rect, TwoDimTreeNode * t)
{
	if (rect.top() > t->Extent.CenterY() && rect.right() <= t->Extent.CenterX())
		return true;
	return false;
}

bool TwoDimTree::Bottom_Right(const Rectangle & rect, TwoDimTreeNode * t)
{
	if (rect.top() > t->Extent.CenterY() && rect.left() > t->Extent.CenterX())
		return true;
	return false;
	//Public insert function
}

bool TwoDimTree::Comprise(const Rectangle & rect, TwoDimTreeNode * t)
{
	if ((t->Extent.left() <= rect.left() )&& (t->Extent.right() >= rect.right())&&(t->Extent.top() <= rect.top()) &&  t->Extent.bottom() >=(rect.bottom() ))
		return true;
	return false;

}
//Public insert function
void TwoDimTree::insert( Rectangle & r)
{
	insert(r,  root ); 
}

//Private insert function
void TwoDimTree::insert(Rectangle & sub, TwoDimTreeNode * & tree )
{
	
		if (Comprise(sub, tree))
	{
	
		if(sub.top() <= tree->Extent.CenterX() && sub.bottom() > tree->Extent.CenterY())
		{
			tree->Horizontal.addToBeginning(sub);//Adding rectangle to Horizontal List
			//cout << sub.top() << " " << sub.left() << " " << sub.bottom() << " " << sub.right() << endl;
			return;
		}

		else if(sub.left() <= tree->Extent.CenterX() && sub.right() > tree->Extent.CenterX() && !(sub.top() <= tree->Extent.CenterY() && sub.bottom() > tree->Extent.CenterY()))
		{
			tree->Vertical.addToBeginning(sub);//Adding rectangle to Vertical List
			//cout << sub.top() << " " << sub.left() << " " << sub.bottom() << " " << sub.right() << endl;
			return;
		}
		else
		{
			if (Top_Left(sub, tree)) //TopLeft quadrant
			{
				if (tree->TopLeft == NULL) //if TopLeft has not been initialized yet
				{
					Rectangle newRect(tree->Extent.top(), tree->Extent.left(), (tree->Extent.top() + tree->Extent.bottom())/2, (tree->Extent.right() + tree->Extent.left())/2);
						tree->TopLeft = new TwoDimTreeNode(newRect,NULL,NULL,NULL,NULL);
				}
				insert(sub, tree->TopLeft); 
			}

			else if (Top_Right(sub, tree)) //TopRight quadrant
			{
				if(tree->TopRight==NULL)
				{
					Rectangle newRect(tree->Extent.top(), (tree->Extent.right() + tree->Extent.left())/2+1,(tree->Extent.top() + tree->Extent.bottom())/2, tree->Extent.right());
					tree->TopRight = new TwoDimTreeNode(newRect,NULL,NULL,NULL,NULL);
				}
				insert(sub, tree->TopRight); 
			}

			else if (Bottom_Left(sub, tree)) //BottomLeft quadrant
			{
				if(tree->BottomLeft == NULL){
				
					Rectangle newRect((tree->Extent.top() + tree->Extent.bottom())/2+1, tree->Extent.left(),tree->Extent.bottom(), (tree->Extent.right() + tree->Extent.left())/2);
					tree->BottomLeft = new TwoDimTreeNode(newRect,NULL,NULL,NULL,NULL);
				}
				insert(sub, tree->BottomLeft);  // insert at bottom left
			}

			else if (Bottom_Right(sub, tree)) //BottomRight quadrant
			{
				if(tree->BottomRight == NULL){
				
					Rectangle newRect((tree->Extent.top() + tree->Extent.bottom())/2+1, (tree->Extent.right() + tree->Extent.left())/2+1,	tree->Extent.bottom(), tree->Extent.right());
					tree->BottomRight = new TwoDimTreeNode(newRect,NULL,NULL,NULL,NULL);
				}
				insert(sub,tree->BottomRight);  // insert at bottom right
			}
		}
	}
}

//Public search function
void TwoDimTree::search(const int x, const int y, vector<Rectangle> & str_Rec)
{
	if (root->Extent.left() <= x && x <= root->Extent.right()&&root->Extent.top() <= y && y <= root->Extent.bottom())
	{

		search(x, y ,str_Rec, root);
	}
	else{
		return;}



}


//Private search function
void TwoDimTree::search(const int x, const int y, vector<Rectangle> & str_Rec, TwoDimTreeNode * t)
{

	if (t == NULL)
	{
		return;
	}
	else
	{
		
		//if the point lies on vertical line
		if (!t->Vertical.isEmpty())
		{
			ListItr<Rectangle> itr = t->Vertical.first( );
			while (!itr.isPastEnd())
			{
				//cout << itr.retrieve().top()<< " "<<  itr.retrieve().left() <<" "<< itr.retrieve().bottom() <<" "<< itr.retrieve().right() << endl;
				if (itr.retrieve().inside(x,y))
				{
					str_Rec.push_back(itr.retrieve());
				}
				itr.advance();
			}
		}

		//if the point lies on horizontal line
		if (!t->Horizontal.isEmpty())
		{
			ListItr<Rectangle> itr = t->Horizontal.first();
			while (!itr.isPastEnd())
			{
				//cout << itr.retrieve().top()<<" "<<  itr.retrieve().left() <<" "<< itr.retrieve().bottom() <<" "<< itr.retrieve().right() << endl;
				if (itr.retrieve().inside(x,y))
				{
					str_Rec.push_back(itr.retrieve());
				}
				itr.advance();
			}
		}

		if (x == (t->Extent.left()+t->Extent.right())/2 || y == (t->Extent.top()+t->Extent.bottom())/2)
			return;


		//topleft quadrant
		if( t->TopLeft != NULL && t->TopLeft->Extent.top() <= y &&  y < t->TopLeft->Extent.bottom() &&
			t->TopLeft->Extent.left() <= x && x < t->TopLeft->Extent.right())

			search(x,y,str_Rec,t->TopLeft);

		//topright quadrant
		else if(t->TopRight != NULL && t->TopRight->Extent.top() <= y &&  y < t->TopRight->Extent.bottom() &&
			t->TopRight->Extent.left() <= x && x < t->TopRight->Extent.right())

			search(x,y,str_Rec,t->TopRight);

		//bottomright quadrant
		else if(t->BottomRight != NULL && t->BottomRight->Extent.top() <= y &&  y < t->BottomRight->Extent.bottom() &&
			t->BottomRight->Extent.left() <= x && x < t->BottomRight->Extent.right())
			search(x,y,str_Rec,t->BottomRight);

		//bottomleft quadrant
		else if(t->BottomLeft != NULL && t->BottomLeft->Extent.top() <= y &&  y < t->BottomLeft->Extent.bottom() &&
			t->BottomLeft->Extent.left() <= x && x < t->BottomLeft->Extent.right())
			search(x,y,str_Rec,t->BottomLeft);

	}
}

#endif