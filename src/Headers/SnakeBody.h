/*
 * SnakeBody.h
 *
 *  Created on: 03/04/2013
 *      Author: André Garcia
 */

#ifndef SnakeBody_H_
#define SnakeBody_H_

class SnakeBody {
public:

	SnakeBody(  int _x1,
			int _y1,
			int _x2,
			int _y2,
			int _size,
			char _direction
			);

	SnakeBody();
	virtual ~SnakeBody();

	virtual SnakeBody& operator=(const SnakeBody& rhs);

	void Grow(int newSize);

	void Move();

	void SetX1(int _x1);
	void SetX2(int _x2);
	void SetY1(int _y1);
	void SetY2(int _y2);
	void SetSize(int _size);
	void SetDirection(char _direction);

	int GetX1();
	int GetX2();
	int GetY1();
	int GetY2();
	int GetSize();
	char GetDirection();

private:
	int x1;
	int x2;
	int y1;
	int y2;
	int size;
	char direction;
};

#endif /* SnakeBody_H_ */
