#pragma once
#ifndef MATH_API
#define MATH_API _declspec(dllexport)
#endif
#include<string>
using namespace std;
enum YUV_TYPE
{
	FMT_NV12,
	FMT_NV21,
	FMT_YUV420P,
	FMT_RGB
};

class MATH_API CUtil
{
public:
	CUtil();
	~CUtil();
public:
	static string getTime();
	static long long getCurrentTime();
	static string GetLocalIpAddress();
public:
	static void init_yuv420p_table();
	static void yuv420p_to_rgb24(unsigned char* yuvbuffer, unsigned char* rgbbuffer, int width, int height);
	static void yuv420sp_to_rgb24(YUV_TYPE type, unsigned char* yuvbuffer, unsigned char* rgbbuffer, int width, int height);
};

