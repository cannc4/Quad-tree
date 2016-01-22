/*
HW2 by Can Ince 14241
*/

#ifndef _RECTANGLE_H
#define _RECTANGLE_H

class Rectangle
{
public:
	//Constructors
	Rectangle()	{}
	Rectangle(int top, int left, int bottom, int right): Top(top),Left(left),Bottom(bottom),Right(right)	{}

	//Setters
	void setTop(int s){Top = s;}
	void setLeft(int s){Left = s;}
	void setBottom(int s){Bottom = s;}
	void setRight(int s){Right = s;}

	//Centers
	int CenterX() const {
		return (Left+Right)/2;}
	int CenterY() const{
	return (Top+Bottom)/2;
	}

	//Getters
	int top() const {return Top;} 
	int left() const {return Left;}
	int bottom() const {return Bottom;}
	int right() const {return Right;}

	bool inside( int x, int y) const //checks if given point lies inside the rectangle
	{
		if (Top <= y && y < Bottom && Left <= x && x < Right){
			return true;}
		else{
			return false;}
	}


	//Operator overloadings

	//  "="
	Rectangle& operator=(Rectangle rhs)
	{
		if(this != &rhs)
		{
			Top = rhs.Top;
			Left = rhs.Left;
			Bottom = rhs.Bottom;
			Right = rhs.Right;
		}
		return *this;
	}
	
	//  "=="
	bool operator==(const Rectangle& r)
	{
		if(Top == r.Top && Left == r.Left && Bottom== r.Bottom && Right== r.Right)
			return true;
		else
			return false;
	}

	//  "!="
	bool operator!=(const Rectangle& r)
	{
		return !operator==(r);
	}


private:
	int Top;	// y coordinate of the upper edge
	int Left;	// x coordinate of the left edge
	int Bottom; // y coordinate of the bottom edge
	int Right;	// x coordinate of the right edge
};

#endif