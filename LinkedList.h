/*
HW2 by Can Ince 14241
*/

// LinkedList Class taken from lecture notes

#ifndef _LINKEDLIST_H
#define _LINKEDLIST_H
#include <iostream>

template <class Object> 
class ListNode;

template <class Object> 
class List;

template <class Object> 
class ListItr;





template <class Object>
class ListItr
{
public:
	ListItr( ) : current( NULL ) { }

	bool isPastEnd( ) const
	{ return current == NULL; }

	void advance( )
	{
		if( !isPastEnd( ) ) 
			current = current->next; }

	Object & retrieve( ) const
	{ 
		if( isPastEnd( ) )
			throw "BAD_ITERATOR";
		return current->element; 
	}
private:
	ListNode<Object> *current;   

	ListItr( ListNode<Object> *theNode )
		: current( theNode ) { }

	friend class List<Object>; // Grant access to constructor
};

template <class Object> 
class ListNode
{
public:
	ListNode( const Object & theElement = Object( ), ListNode * n = NULL ) // Constructor
		: element( theElement ), next( n ) { }

	Object   element;
	ListNode *next;
	void insert( const Object & x, const ListItr<Object> & p );
	//For accesing the member functions
	friend class List<Object>;
	friend class ListItr<Object>;
};

template <class Object>
class List
{
public:
	List( )        
	{
		header = new ListNode<Object>;
	}
	List( const List & rhs )
	{
		header = new ListNode<Object>;
		*this = rhs;  // Deep Copy
	}

	//Destructor
	~List( )
	{
		makeEmpty( );  
		delete header;
	}

	bool isEmpty( ) const
	{  		return header->next == NULL;
	}
	void makeEmpty( )
	{
		while( !isEmpty( ) )
			remove( first( ).retrieve( ) );
	}

	ListItr<Object> zeroth() const
	{
		return ListItr<Object>(header);
	}

	ListItr<Object> first( ) const
	{
		return ListItr<Object>( header->next );
	}

	void addToBeginning(const Object& x)
	{
		ListNode<Object>* first = new ListNode<Object>(x, header);
		header = first;
	}

	void insert( const Object & x, const ListItr<Object> & p )
	{
		if( p.current != NULL )
			p.current->next = new ListNode<Object>( x, p.current->next );
	}

	template <class Object>
	void insertAtEnd(const Object & x)
{
	ListItr<Object> itr = zeroth();
	while (itr.current->next != NULL){
		itr.advance();
		itr.current->next = new ListNode<Object>(x,NULL);}
}

	ListItr<Object> find( const Object & x ) const
	{
		ListNode<Object> *itr = header->next;

		while( itr != NULL && itr->element != x )
			itr = itr->next;

		return ListItr<Object>( itr );
	}
	
	ListItr<Object> findPrevious( const Object & x ) const
	{
		ListNode<Object> *itr = header;

		while( (itr->next != NULL) && itr->next->element != x )
			itr = itr->next;

		return ListItr<Object>( itr );
	}

	void remove( const Object & x )
	{
		ListItr<Object> p = findPrevious( x );

		if( p.current->next != NULL )
		{
			ListNode<Object> *oldNode = p.current->next;
			p.current->next = p.current->next->next; 
			delete oldNode;
		}
	}

	const List & operator=( const List & rhs )
	{
		if( this != &rhs )
		{
			makeEmpty( );

			ListItr<Object> ritr = rhs.first( );
			ListItr<Object> itr = zeroth( );
			for( ; !ritr.isPastEnd( ); ritr.advance( ), itr.advance( ) )
				insert( ritr.retrieve( ), itr );
		}
		return *this;
	}

private:
	ListNode<Object> *header;
};

#endif
