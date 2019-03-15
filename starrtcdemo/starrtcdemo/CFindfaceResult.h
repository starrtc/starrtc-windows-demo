#pragma once
#include<string>
using namespace std;
class CFindFaceResult
{
public:
	CFindFaceResult()
	{
		id = 0;
		name = "";
		memset(pos, 0, sizeof(pos));
	}
	~CFindFaceResult() {}
public:
	int id;
	int pos[8];
	string name;
};