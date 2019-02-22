#include "stdafx.h"
#include "CUtil.h"
#include <time.h>

CUtil::CUtil()
{
}


CUtil::~CUtil()
{
}


string CUtil::getTime()
{
	time_t timep;

	struct tm t;   //tm结构指针
	time(&timep);
	localtime_s(&t, &timep);   //获取当地日期和时间

	char tmp[64];
	strftime(tmp, sizeof(tmp), "%m-%d %H:%M", &t);
	return tmp;
}


static long int crv_tab[256];
static long int cbu_tab[256];
static long int cgu_tab[256];
static long int cgv_tab[256];
static long int tab_76309[256];
static unsigned char clp[1024];   //for clip in CCIR601   

void CUtil::init_yuv420p_table()
{
	long int crv, cbu, cgu, cgv;
	int i, ind;
	static int init = 0;

	if (init == 1) return;

	crv = 104597; cbu = 132201;  /* fra matrise i global.h */
	cgu = 25675;  cgv = 53279;

	for (i = 0; i < 256; i++)
	{
		crv_tab[i] = (i - 128) * crv;
		cbu_tab[i] = (i - 128) * cbu;
		cgu_tab[i] = (i - 128) * cgu;
		cgv_tab[i] = (i - 128) * cgv;
		tab_76309[i] = 76309 * (i - 16);
	}

	for (i = 0; i < 384; i++)
		clp[i] = 0;
	ind = 384;
	for (i = 0; i < 256; i++)
		clp[ind++] = i;
	ind = 640;
	for (i = 0; i < 384; i++)
		clp[ind++] = 255;

	init = 1;
}

/**
内存分布
					w
			+--------------------+
			|Y0Y1Y2Y3...         |
			|...                 |   h
			|...                 |
			|                    |
			+--------------------+
			|U0U1      |
			|...       |   h/2
			|...       |
			|          |
			+----------+
			|V0V1      |
			|...       |  h/2
			|...       |
			|          |
			+----------+
				w/2
 */
void CUtil::yuv420p_to_rgb24(unsigned char* yuvbuffer, unsigned char* rgbbuffer, int width, int height)
{
	int y1, y2, u, v;
	unsigned char *py1, *py2;
	int i, j, c1, c2, c3, c4;
	unsigned char *d1, *d2;
	unsigned char *src_u, *src_v;
	static int init_yuv420p = 0;

	src_u = yuvbuffer + width * height;   // u
	src_v = src_u + width * height / 4;  //  v

	//if (type == FMT_YV12)
	//{
	src_v = yuvbuffer + width * height;   // v
	src_u = src_u + width * height / 4;  //  u
//}
	py1 = yuvbuffer;   // y
	py2 = py1 + width;
	d1 = rgbbuffer;
	d2 = d1 + 3 * width;

	init_yuv420p_table();

	for (j = 0; j < height; j += 2)
	{
		for (i = 0; i < width; i += 2)
		{
			u = *src_u++;
			v = *src_v++;

			c1 = crv_tab[v];
			c2 = cgu_tab[u];
			c3 = cgv_tab[v];
			c4 = cbu_tab[u];

			//up-left   
			y1 = tab_76309[*py1++];
			*d1++ = clp[384 + ((y1 + c1) >> 16)];
			*d1++ = clp[384 + ((y1 - c2 - c3) >> 16)];
			*d1++ = clp[384 + ((y1 + c4) >> 16)];

			//down-left   
			y2 = tab_76309[*py2++];
			*d2++ = clp[384 + ((y2 + c1) >> 16)];
			*d2++ = clp[384 + ((y2 - c2 - c3) >> 16)];
			*d2++ = clp[384 + ((y2 + c4) >> 16)];

			//up-right   
			y1 = tab_76309[*py1++];
			*d1++ = clp[384 + ((y1 + c1) >> 16)];
			*d1++ = clp[384 + ((y1 - c2 - c3) >> 16)];
			*d1++ = clp[384 + ((y1 + c4) >> 16)];

			//down-right   
			y2 = tab_76309[*py2++];
			*d2++ = clp[384 + ((y2 + c1) >> 16)];
			*d2++ = clp[384 + ((y2 - c2 - c3) >> 16)];
			*d2++ = clp[384 + ((y2 + c4) >> 16)];
		}
		d1 += 3 * width;
		d2 += 3 * width;
		py1 += width;
		py2 += width;
	}
}

void CUtil::yuv420sp_to_rgb24(YUV_TYPE type, unsigned char* yuvbuffer, unsigned char* rgbbuffer, int width, int height)
{
	int y1, y2, u, v;
	unsigned char *py1, *py2;
	int i, j, c1, c2, c3, c4;
	unsigned char *d1, *d2;
	unsigned char *src_u;
	static int init_yuv420p = 0;

	src_u = yuvbuffer + width * height;   // u

	py1 = yuvbuffer;   // y
	py2 = py1 + width;
	d1 = rgbbuffer;
	d2 = d1 + 3 * width;

	init_yuv420p_table();

	for (j = 0; j < height; j += 2)
	{
		for (i = 0; i < width; i += 2)
		{
			if (type == FMT_NV12)
			{
				u = *src_u++;
				v = *src_u++;      // v紧跟u，在u的下一个位置
			}
			if (type == FMT_NV21)
			{
				v = *src_u++;
				u = *src_u++;      // u紧跟v，在v的下一个位置
			}

			c1 = crv_tab[v];
			c2 = cgu_tab[u];
			c3 = cgv_tab[v];
			c4 = cbu_tab[u];

			//up-left   
			y1 = tab_76309[*py1++];
			*d1++ = clp[384 + ((y1 + c1) >> 16)];
			*d1++ = clp[384 + ((y1 - c2 - c3) >> 16)];
			*d1++ = clp[384 + ((y1 + c4) >> 16)];

			//down-left   
			y2 = tab_76309[*py2++];
			*d2++ = clp[384 + ((y2 + c1) >> 16)];
			*d2++ = clp[384 + ((y2 - c2 - c3) >> 16)];
			*d2++ = clp[384 + ((y2 + c4) >> 16)];

			//up-right   
			y1 = tab_76309[*py1++];
			*d1++ = clp[384 + ((y1 + c1) >> 16)];
			*d1++ = clp[384 + ((y1 - c2 - c3) >> 16)];
			*d1++ = clp[384 + ((y1 + c4) >> 16)];

			//down-right   
			y2 = tab_76309[*py2++];
			*d2++ = clp[384 + ((y2 + c1) >> 16)];
			*d2++ = clp[384 + ((y2 - c2 - c3) >> 16)];
			*d2++ = clp[384 + ((y2 + c4) >> 16)];
		}
		d1 += 3 * width;
		d2 += 3 * width;
		py1 += width;
		py2 += width;
	}
}
