/*
 * Food.cpp
 *
 *  Created on: 04/04/2013
 *      Author: André
 */

#include "..\Headers\Food.h"

Food::Food() {
	// TODO Auto-generated constructor stub

}

Food::~Food() {
	// TODO Auto-generated destructor stub
}

Food::Food(int _x1,
		int _y1,
		int _x2,
		int _y2,
		int _size) {

	x1= _x1;
	x2= _x2;
	y1= _y1;
	y2= _y2;
	size= _size;
}

void Food::SetX1(int _x1){
	x1 = _x1;
}
void Food::SetX2(int _x2){
	x2 = _x2;
}
void Food::SetY1(int _y1){
	y1 = _y1;
}
void Food::SetY2(int _y2){
	y2 = _y2;
}
void Food::SetSize(int _size){
	size = _size;
}

int Food::GetX1(){
	return x1;
}
int Food::GetX2(){
	return x2;
}
int Food::GetY1(){
	return y1;
}
int Food::GetY2(){
	return y2;
}
int Food::GetSize(){
	return size;
}
