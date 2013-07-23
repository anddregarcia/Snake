/*
 * SnakeBody.cpp
 *
 *  Created on: 03/04/2013
 *      Author: André Garcia
 */

#include <cstdlib>
#include "..\Headers\SnakeBody.h"


SnakeBody::SnakeBody() {
	// TODO Auto-generated constructor stub
}

SnakeBody::SnakeBody(int _x1,
		int _y1,
		int _x2,
		int _y2,
		int _size,
		char _direction) {

	x1= _x1;
	x2= _x2;
	y1= _y1;
	y2= _y2;
	size = _size;
	direction = _direction;
}


SnakeBody::~SnakeBody() {
	// TODO Auto-generated destructor stub
}

void SnakeBody::SetX1(int _x1){
	x1 = _x1;
}
void SnakeBody::SetX2(int _x2){
	x2 = _x2;
}
void SnakeBody::SetY1(int _y1){
	y1 = _y1;
}
void SnakeBody::SetY2(int _y2){
	y2 = _y2;
}
void SnakeBody::SetSize(int _size){
	size = _size;
}
void SnakeBody::SetDirection(char _direction){
	direction = _direction;
}

int SnakeBody::GetX1(){
	return x1;
}
int SnakeBody::GetX2(){
	return x2;
}
int SnakeBody::GetY1(){
	return y1;
}
int SnakeBody::GetY2(){
	return y2;
}
int SnakeBody::GetSize(){
	return size;
}
char SnakeBody::GetDirection(){
	return direction;
}

SnakeBody& SnakeBody::operator=(const SnakeBody& rhs){
   const SnakeBody *obj = dynamic_cast<const SnakeBody *>(&rhs);
  	if (obj != NULL){
  		SnakeBody::operator=(rhs);
           this->y1 = obj->y1;
           this->x1 = obj->x1;
           this->y2 = obj->y2;
           this->x2 = obj->x2;
           this->size = obj->size;

  	}
    return *this;
}
