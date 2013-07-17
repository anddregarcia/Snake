/*
 * Snake.cpp
 *
 *  Created on: 10/04/2013
 *      Author: André
 */

#include "..\Headers\Snake.h"

Snake::Snake() {
	// TODO Auto-generated constructor stub
	size = 1;
}

Snake::~Snake() {
	// TODO Auto-generated destructor stub
}

void Snake::SetSize(int _size){
	size = _size;
}

int Snake::GetSize(){
	return size;
}
