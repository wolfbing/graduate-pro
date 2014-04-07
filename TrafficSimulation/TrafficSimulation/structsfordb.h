
#pragma once

struct TreeInt
{
	int m1,m2,m3;
	TreeInt(){};
	TreeInt(int,int,int);
	TreeInt(const TreeInt &);
	TreeInt& operator=(const TreeInt &);
	bool operator==(const TreeInt &) const;
};



