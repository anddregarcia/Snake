/*
 * Food.h
 *
 *  Created on: 04/04/2013
 *      Author: André Garcia
 */

#ifndef FOOD_H_
#define FOOD_H_

class Food {
public:
	Food(  int _x1,
			int _y1,
			int _x2,
			int _y2,
			int _size
			);

	Food();
	virtual ~Food();

	void SetX1(int _x1);
	void SetX2(int _x2);
	void SetY1(int _y1);
	void SetY2(int _y2);
	void SetSize(int _size);

	int GetX1();
	int GetX2();
	int GetY1();
	int GetY2();
	int GetSize();

private:
	int x1;
	int x2;
	int y1;
	int y2;
	int size;
};


#endif /* FOOD_H_ */
