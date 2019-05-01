#include "object.h"

Point::Point(short nx, short ny) {
	x = nx;
	y = ny;
}

void Point::setPos(short nx, short ny) {
	x = nx;
	y = ny;
}

void Point::operator = (Point A)
{
	this->x = A.x;
	this->y = A.y;
}

void Point::swap()
{
	short temp = x;
	x = y;
	y = temp;
}


void object::reset() { 
	for (short i = 0; i < size; i++) {
		pos[i].x = Start_pos[i].x;
		pos[i].y = Start_pos[i].y;
	}
}

object::~object() {
	//delete(pos);
	//delete(Start_pos);
}

rect_1x1::rect_1x1(){
	size = 1;
	dist = 0;

	pos = new Point{ Point(3, -1) };
	Start_pos = new Point{ Point(3, -1)};
};

rect_1x2::rect_1x2(){
	size = 2;
	dist = 1;
	
	pos = new Point[2]{ Point(3, -1), Point(4, -1) };
	Start_pos = new Point[2]{ Point(3, -1), Point(4, -1) };
};

rect_2x2::rect_2x2(){
	size = 4;
	dist = 1;

	pos = new Point[4]{ Point(3, -1), Point(4, -1), Point(3, 0), Point(4, 0) };
	Start_pos = new Point[4]{ Point(3, -1), Point(4, -1), Point(3, 0), Point(4, 0) };
};

rect_1x3::rect_1x3(){
	size = 3;
	dist = 1;

	pos = new Point[3]{ Point(3, -1), Point(4, -1), Point(5, -1) };
	Start_pos = new Point[3]{ Point(3, -1), Point(4, -1), Point(5, -1)};
};

rect_1x4::rect_1x4(){
	size = 4;
	dist = 2;

	pos = new Point[4]{ Point(2, -1), Point(3, -1), Point(4, -1), Point(5, -1) };
	Start_pos = new Point[4]{ Point(2, -1), Point(3, -1), Point(4, -1), Point(5, -1) };
};

ladder_1::ladder_1(){
	size = 4;
	dist = 1;

	pos = new Point[4]{ Point(3, 0), Point(4, 0), Point(5, -1), Point(4, -1) };
	Start_pos = new Point[4]{ Point(3, 0), Point(4, 0), Point(5, -1), Point(4, -1) };
};

ladder_2::ladder_2(){
	size = 4;
	dist = 1;

	pos = new Point[4]{ Point(5, 0), Point(4, 0), Point(3, -1), Point(4, -1) };
	Start_pos = new Point[4]{ Point(5, 0), Point(4, 0), Point(3, -1), Point(4, -1) };
};

ladder_3::ladder_3(){
	size = 3;
	dist = 1;

	pos = new Point[3]{ Point(4, 0), Point(3, 0), Point(4, -1)};
	Start_pos = new Point[3]{ Point(4, 0), Point(3, 0), Point(4, -1) };
};