/*
 * Snake.h
 *
 *  Created on: 10/04/2013
 *      Author: André
 */


#ifndef SNAKE_H_
#define SNAKE_H_

#include "..\Headers\SnakeBody.h"
#include <vector>

using std::vector;

class Snake {
public:
	Snake();
	virtual ~Snake();

	vector<SnakeBody> vSnake;

	int GetSize();
	void SetSize(int _size);

private:
	int size;

};

#endif /* SNAKE_H_ */
