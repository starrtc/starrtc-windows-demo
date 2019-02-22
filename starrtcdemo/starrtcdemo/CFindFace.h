#pragma once
#include<string>
#include<vector>
#include <Python.h> 
#include <numpy/Ndarrayobject.h>
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
class CFindFace
{
public:
	CFindFace();
	~CFindFace();
	bool init();
	bool finalize();
	vector<CFindFaceResult> findFace(CImage* pImage);
	int userRegister(int id, CString strName, CString path);
public:
	PyObject * pFindFaceFunc;
	PyObject * pyUserRegisterFunc;
	PyObject * pModule;
	bool m_bInit;

	CRITICAL_SECTION m_critFaceFeature;
	PyObject *pyClassInstance;
};

