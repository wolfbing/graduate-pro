
#pragma once

#include <QObject>

struct TreeInt
{
	int m1,m2,m3;
	TreeInt(){};
	TreeInt(int,int,int);
	TreeInt(const TreeInt &);
	TreeInt& operator=(const TreeInt &);
	bool operator==(const TreeInt &) const;
};


struct TwoInt : public QObject
{
	int m1,m2;
	TwoInt(){};
	TwoInt(int i1, int i2){m1=i1;m2=i2;};
	TwoInt(const TwoInt & obj){m1=obj.m1;m2=obj.m2;};
	TwoInt& operator=(const TwoInt & obj);
	bool operator==(const TwoInt & obj) const ;
};

inline uint qHash(TwoInt obj,uint seed=0){
	return 0;
}





