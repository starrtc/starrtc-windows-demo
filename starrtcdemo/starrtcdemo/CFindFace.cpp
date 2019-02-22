#include "stdafx.h"
#include "CFindFace.h"

CFindFace::CFindFace()
{
	pFindFaceFunc = NULL;
	pyUserRegisterFunc = NULL;
	pModule = NULL;
	m_bInit = false;	
}


CFindFace::~CFindFace()
{
	
}
//CRITICAL_SECTION CFindFace::m_critFaceFeature = CRITICAL_SECTION();
bool CFindFace::init()
{
	char pFileName[MAX_PATH];
	int nPos = GetCurrentDirectory(MAX_PATH, pFileName);

	CString strImport = "";
	strImport.Format("sys.path.append('%s//faceFeature//')", pFileName);

	m_bInit = false;
	Py_Initialize();
	PyObject * pFunc = NULL;
	PyObject * pFunc1 = NULL;
	PyRun_SimpleString("import sys");
	PyRun_SimpleString("print '---import sys---'");
	PyRun_SimpleString(strImport);
	pModule = PyImport_ImportModule("facerecognition");//调用的Python文件名
	if (pModule == NULL)
	{
		return m_bInit;
	}
	pFindFaceFunc = PyObject_GetAttrString(pModule, "findFaceInfo1");//调用的函数名

	if (pFindFaceFunc == NULL)
	{
		finalize();
		return m_bInit;
	}

	//获取Python模块中相应的函数名
	pyUserRegisterFunc = PyObject_GetAttrString(pModule, "userRegister1");//调用的函数名

	if (pyUserRegisterFunc == NULL)
	{
		finalize();
		return m_bInit;
	}
	m_bInit = true;
	return m_bInit;
	
}

bool CFindFace::finalize()
{
	if (pFindFaceFunc != NULL)
	{
		Py_DECREF(pFindFaceFunc);
		pFindFaceFunc = NULL;
	}

	if (pyUserRegisterFunc != NULL)
	{
		Py_DECREF(pyUserRegisterFunc);
		pyUserRegisterFunc = NULL;
	}

	if (pModule != NULL)
	{
		Py_DECREF(pModule);
		pModule = NULL;
	}

	Py_Finalize();
	return true;
}
//PyObject* CFindFace::pModule = NULL;
//PyObject* CFindFace::pyClass = NULL;
//PyObject* CFindFace::pFindFaceFunc = NULL;
//PyObject* CFindFace::pyFindFaceInfoFunc = NULL;

//bool CFindFace::m_bInit = false;

vector<CFindFaceResult> CFindFace::findFace(CImage* pImage)
{
	//EnterCriticalSection(&CFindFace::m_critFaceFeature);
	
	vector<CFindFaceResult> vResult;
	if (pImage == NULL || pFindFaceFunc == NULL)
	{

		return vResult;
	}
	long t3= GetTickCount();
	static int nIndex = 1;
	nIndex++;
	PyObject *pyResult = NULL;
	CString str = _T(".\\1.jpg");
	CString path = _T(".\\1.jpg");
	path.Format(_T("%d.jpg"), 1);

	HRESULT hResult = pImage->Save(path);
	if (FAILED(hResult))
	{
		//LeaveCriticalSection(&CFindFace::m_critFaceFeature);
		return vResult;
	}	
	long t1 = GetTickCount();
	PyObject *pyArgs = PyTuple_New(1);
	//PyTuple_SetItem(pyArgs, 0, Py_BuildValue("O", pyClassInstance));
	//PyTuple_SetItem(pyArgs, 1, Py_BuildValue("O", pyClassInstance));
	PyTuple_SetItem(pyArgs, 0, Py_BuildValue("s", path));

	pyResult = PyObject_CallObject(pFindFaceFunc, pyArgs);

	Py_ssize_t size = PyList_Size(pyResult);
	for (Py_ssize_t i = 0; i < size; i++)
	{
		PyObject *pySubRet = PyList_GetItem(pyResult, i);
		PyObject *pyRetName = PyObject_GetAttrString(pySubRet, "name");
		char* pName;
		PyArg_Parse(pyRetName, "s", &pName);

		PyObject *pyRetId = PyObject_GetAttrString(pySubRet, "id");
		int nId = 0;
		PyArg_Parse(pyRetId, "i", &nId);

		PyObject *pyRetPos = PyObject_GetAttrString(pySubRet, "pos");
		Py_ssize_t sizeSub = PyList_Size(pyRetPos);
		CFindFaceResult result;
		result.name = pName;
		result.id = nId;
		for (Py_ssize_t j = 0; j < sizeSub && j<4; j++)
		{
			float nPos = 0.0f;
			PyArg_Parse(PyList_GetItem(pyRetPos, j), "f", &nPos);//i表示转换成int型变量
			result.pos[j] = nPos;
		}
		vResult.push_back(result);
	}
	long t2 = GetTickCount();
	int t21 = t2 - t1; //计算当前系统时间与时间t1的间隔
	int t23 = t2 - t3;
	str.Format("%d %d", t21, t23);
	//AfxMessageBox(str);

	if (pyArgs != NULL)
	{
		Py_DECREF(pyArgs);
		pyArgs = NULL;
	}
	if (pyResult != NULL)
	{
		Py_DECREF(pyResult);
		pyResult = NULL;
	}
	//LeaveCriticalSection(&CFindFace::m_critFaceFeature);

	return vResult;
}


void utf8ToUnicode(const string& src, wstring& result)
{
	int n = MultiByteToWideChar(CP_UTF8, 0, src.c_str(), -1, NULL, 0);
	result.resize(n);
	::MultiByteToWideChar(CP_UTF8, 0, src.c_str(), -1, (LPWSTR)result.c_str(), result.length());
}


int CFindFace::userRegister(int id, CString strName, CString path)
{
	//EnterCriticalSection(&CFindFace::m_critFaceFeature);

	if (path == "" || pyUserRegisterFunc == NULL)
	{
		return -3;
	}
	long t3 = GetTickCount();
	static int nIndex = 1;
	nIndex++;
	PyObject *pyResult = NULL;
	char* testName = "1";
	wstring retStr;
	utf8ToUnicode(testName, retStr);

	PyObject *pyArgs = PyTuple_New(3);
	//PyTuple_SetItem(pyArgs, 0, Py_BuildValue("O", pyClassInstance));
	//PyTuple_SetItem(pyArgs, 1, Py_BuildValue("O", pyClassInstance));
	PyTuple_SetItem(pyArgs, 0, Py_BuildValue("i", id));
	PyTuple_SetItem(pyArgs, 1, Py_BuildValue("s", retStr.c_str()));
	PyTuple_SetItem(pyArgs, 2, Py_BuildValue("s", path));

	pyResult = PyObject_CallObject(pyUserRegisterFunc, pyArgs);
	int nRet =  0;
	PyArg_Parse(pyResult, "i", &nRet);//i表示转换成int型变量

	if (pyArgs != NULL)
	{
		Py_DECREF(pyArgs);
		pyArgs = NULL;
	}
	if (pyResult != NULL)
	{
		Py_DECREF(pyResult);
		pyResult = NULL;
	}
	//LeaveCriticalSection(&CFindFace::m_critFaceFeature);
	return nRet;
}
