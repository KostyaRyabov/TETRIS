#pragma once

class Point {
public:
	short x, y;

	Point();
	Point(short nx, short ny);
	void setPos(short nx, short ny);

	void swap();

	void operator = (Point A);
};


class object
{
public:
	short size, dist;
	Point *pos, *Start_pos;
	~object();

	

	void reset();
};





class rect_1x1: public object{
public:rect_1x1();
};

class rect_1x2 : public object {
public:rect_1x2();
};

class rect_2x2 : public object {
public:rect_2x2();
};

class rect_1x3 : public object {
public:rect_1x3();
};

class rect_1x4 : public object {
public:rect_1x4();
};

class ladder_1 : public object {
public:ladder_1();
};

class ladder_2 : public object {
public:ladder_2();
};

class ladder_3 : public object {
public:ladder_3();
};