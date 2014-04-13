#pragma once
class TurnRestrict
{
public:
	TurnRestrict(void);
	~TurnRestrict(void);

	// set
	TurnRestrict & setCurrentNodeNo(int);
	TurnRestrict & setFromNodeNo(int);
	TurnRestrict & setToNodeNo(int);

	// get
	int currentNodeNo();
	int fromNodeNo();
	int toNodeNo();

private:
	int mCurrentNodeNo;
	int mFromNodeNo;
	int mToNodeNo;


};

