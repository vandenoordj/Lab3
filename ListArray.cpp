/*
 * ListArray.cpp
 *
 *  Created on: Feb 16, 2015
 *      Author: vandenoordj
 */

#include "ListArray.h"

template < typename DataType >
List<DataType>::List (int maxNumber ){
	maxSize=maxNumber;
	size=0;
	cursor=-1;
	dataItems=new DataType[maxSize];
}

template < typename DataType >
List<DataType>::List ( const List& source ){
	maxSize=source.maxSize;
	size=source.size;
	cursor=source.cursor;
	dataItems=source.dataItems;
}

template < typename DataType >
List& List<DataType>::operator= ( const List& source ){
	maxSize=source.maxSize;
	size=source.size;
	cursor=source.cursor;
	dataItems=source.dataItems;
	return *this;
}


template < typename DataType >
virtual List<DataType>::~List (){
	delete dataItems;
	delete maxSize;
	delete size;
	delete cursor;
}

template < typename DataType >
virtual void List<DataType>::insert ( const DataType& newDataItem ) throw ( logic_error ){
	if(cursor+1!=size){
		if(size==0){
			dataItems[0]=newDataItem;
			size++;
			cursor=0;
		}else{
			dataItems[cursor+1]=newDataItem;
			size++;
			cursor++;
		}
	}else
		throw logic_error("Too much data");
}


template < typename DataType >
void List<DataType>::remove () throw ( logic_error ){
	dataItems[cursor]=dataItems[size];
	bool end=size==cursor;
	if(size!=0){
		cursor++;
	}
	if(end){
		cursor=0;
	}

	size--;
}

template < typename DataType >
virtual void List<DataType>::replace ( const DataType& newDataItem ) throw ( logic_error ){
	if(cursor>0&&cursor<size)
	dataItems[cursor]=newDataItem;
	else
		throw logic_error("cannot replace")
}

