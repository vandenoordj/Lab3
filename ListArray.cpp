/*
 * ListArray.cpp
 *
 *  Created on: Feb 16, 2015
 *      Author: vandenoordj
 */

#include "ListArray.h"

template < typename DataType >
List<DataType>::List (int maxNumber ){
	maxSize = maxNumber;
	size = 0;
	cursor = -1;
	dataItems = new DataType[maxSize];
}

template < typename DataType >
List<DataType>::List ( const List& source ){
	maxSize = source.maxSize;
	size = source.size;
	cursor = source.cursor;
	dataItems = new DataType[maxSize];
	for(int i = 0 ; i < size; i++)
		dataItems[i] = source.dataItems[i];
}

template < typename DataType >
List<DataType>& List<DataType>::operator= ( const List& source ){
	maxSize = source.maxSize;
	size = source.size;
	cursor = source.cursor;
	delete [] dataItems;
	dataItems = new DataType[maxSize];
	for(int i = 0 ; i < size; i++)
		dataItems[i] = source.dataItems[i];
	return *this;
}


template < typename DataType >
List<DataType>::~List (){
	delete dataItems;
}

template < typename DataType >
void List<DataType>::insert ( const DataType& newDataItem ) throw ( logic_error ){
	if(size != maxSize){
		if(size == 0){
			dataItems[0] = newDataItem;
			cursor = 0;
		}else{
			for(int i = size+1; i > cursor; i--)
				dataItems[i] = dataItems[i-1];
			dataItems[cursor + 1] = newDataItem;
			cursor++;
		}
		size++;
	}else
		throw logic_error("Too much data");
}


template < typename DataType >
void List<DataType>::remove () throw ( logic_error ){
	if(size == 0)
		throw logic_error("no items");

	for(int i = cursor ; i < size - 1; i++)
		dataItems[i] = dataItems[i+1];

	size--;
	if(cursor >= size)
		cursor = 0;

}

template < typename DataType >
void List<DataType>::replace ( const DataType& newDataItem ) throw ( logic_error ){
	if(cursor >= 0 && cursor < size)
		dataItems[cursor] = newDataItem;
	else
		throw logic_error("cannot replace");
}

template < typename DataType >
void List<DataType>::clear(){
	size = 0;
	cursor = -1;
	delete[] dataItems;
	dataItems = new DataType[maxSize];
}

template < typename DataType >
bool List<DataType>::isEmpty() const{
	return size == 0;
}

template < typename DataType >
bool List<DataType>::isFull() const{
	return size == maxSize;
}

template < typename DataType >
void List<DataType>::gotoBeginning () throw ( logic_error ){
	if(size == 0)
		throw logic_error("no items");
	else
		cursor = 0;
}

template < typename DataType >
void List<DataType>::gotoEnd () throw ( logic_error ){
	if(size == 0)
		throw logic_error("no items");
	else
		cursor = size - 1;
}

template < typename DataType >
bool List<DataType>::gotoNext () throw ( logic_error ){
	if(size == 0)
		throw logic_error("no items");
	else
		if(cursor != size - 1){
			cursor++;
			return true;
		}else
			return false;
}

template < typename DataType >
bool List<DataType>::gotoPrior () throw ( logic_error ){
	if(size == 0)
		throw logic_error("no items");
	else
		if(cursor != 0){
			cursor--;
			return true;
		}else
			return false;
}

template < typename DataType >
DataType List<DataType>::getCursor () const throw ( logic_error ){
	if(size == 0)
		throw logic_error("no items");
	else
		return dataItems[cursor];
}
template < typename DataType >
void List<DataType>:: showStructure () const

// outputs the data items in a list. if the list is empty, outputs
// "empty list". this operation is intended for testing/debugging
// purposes only.

{
	int j;   // loop counter

	if ( size == 0 )
		cout << "empty list" << endl;
	// The Ordered List code blows up below. Since this is just debugging
	// code, we check for whether the OrderedList is defined, and if so,
	// print out the key value. If not, we try printing out the entire item.
	// Note: This assumes that you have used the double-inclusion protection
	// in your OrderedList.cpp file by doing a "#ifndef ORDEREDLIST_CPP", etc.
	// If not, you will need to comment out the code in the section under
	// the "else", otherwise the compiler will go crazy in lab 4.
	// The alternative is to overload operator<< for all data types used in
	// the ordered list.
	else
	{
		cout << "size = " << size
				<<  "   cursor = " << cursor << endl;
		for ( j = 0 ; j < maxSize ; j++ )
			cout << j << "\t";
		cout << endl;
		for ( j = 0 ; j < size ; j++ ) {
			if( j == cursor ) {
				cout << "[";
				cout << dataItems[j]
#ifdef ORDEREDLIST_CPP
								  .getKey()
#endif
								  ;
				cout << "]";
				cout << "\t";
			}
			else
				cout << dataItems[j]
#ifdef ORDEREDLIST_CPP
								  .getKey()
#endif
								  << "\t";
		}
		cout << endl;
	}
}


template < typename DataType >
void List<DataType>::moveToNth ( int n ) throw ( logic_error ){
	if(size < n + 1){
		throw logic_error("not enough items");
	}
	DataType rep = dataItems[cursor];
	this->remove();
	cursor = n - 1;
	this->insert(rep);
}

template < typename DataType >
bool List<DataType>::find ( const DataType& searchDataItem ) throw ( logic_error ){
	if(size == 0)
		throw logic_error("no items");
	for(int i = cursor; i < size; i++){
		if(dataItems[i]==searchDataItem)
			return true;

		if(cursor+1<size)
			cursor++;
	}
	return false;
}
