#pragma once
enum CROP_TYPE{

	VIDEO_CROP_CONFIG_176BW_320BH_SMALL_NONE,               //0
	VIDEO_CROP_CONFIG_176BW_320BH_88SW_160SH,               //1

	VIDEO_CROP_CONFIG_240BW_320BH_SMALL_NONE,               //2
	VIDEO_CROP_CONFIG_240BW_320BH_120SW_160SH,              //3

	VIDEO_CROP_CONFIG_480BW_480BH_SMALL_NONE,               //4
	VIDEO_CROP_CONFIG_480BW_480BH_120SW_120SH,              //5
	VIDEO_CROP_CONFIG_480BW_480BH_240SW_240SH,              //6

	VIDEO_CROP_CONFIG_360BW_640BH_SMALL_NONE,               //7
	VIDEO_CROP_CONFIG_360BW_640BH_90SW_160SH,               //8
	VIDEO_CROP_CONFIG_360BW_640BH_180SW_320SH,              //9

	VIDEO_CROP_CONFIG_480BW_640BH_SMALL_NONE,               //10
	VIDEO_CROP_CONFIG_480BW_640BH_120SW_160SH,              //11
	VIDEO_CROP_CONFIG_480BW_640BH_240SW_320SH,              //12

	VIDEO_CROP_CONFIG_640BW_640BH_SMALL_NONE,               //13
	VIDEO_CROP_CONFIG_640BW_640BH_160SW_160SH,              //14
	VIDEO_CROP_CONFIG_640BW_640BH_320SW_320SH,              //15


	VIDEO_CROP_CONFIG_720BW_1280BH_SMALL_NONE,              //16
	VIDEO_CROP_CONFIG_720BW_1280BH_90SW_160SH,              //17
	VIDEO_CROP_CONFIG_720BW_1280BH_180SW_320SH,             //18
	VIDEO_CROP_CONFIG_720BW_1280BH_360SW_640SH,             //19

	VIDEO_CROP_CONFIG_1080BW_1920BH_SMALL_NONE,             //20
	VIDEO_CROP_CONFIG_1080BW_1920BH_135SW_240SH,            //21
	VIDEO_CROP_CONFIG_1080BW_1920BH_270SW_480SH,            //22
	VIDEO_CROP_CONFIG_1080BW_1920BH_540SW_960SH,            //23

	VIDEO_CROP_CONFIG_BIG_NOCROP_SMALL_NONE,                //24

};

class CPicSize
{
public:
	CPicSize()
	{
		m_nWidth = 0;
		m_nHeight = 0;
	}
public:
	int m_nWidth;
	int m_nHeight;

};
class CropTypeInfo
{
public:

	static void getCropSize(CROP_TYPE type, CPicSize& bigSize, CPicSize& smallSize)
	{
		switch (type)
		{
			case VIDEO_CROP_CONFIG_176BW_320BH_SMALL_NONE:
			{
				bigSize.m_nWidth = 176;
				bigSize.m_nHeight = 320;
			}
				break;             
			case VIDEO_CROP_CONFIG_176BW_320BH_88SW_160SH:
			{
				bigSize.m_nWidth = 176;
				bigSize.m_nHeight = 320;
				smallSize.m_nWidth = 88;
				smallSize.m_nHeight = 160;
			}
				break;            

			case VIDEO_CROP_CONFIG_240BW_320BH_SMALL_NONE:
			{
				bigSize.m_nWidth = 240;
				bigSize.m_nHeight = 320;
			}
				break;               //2
			case VIDEO_CROP_CONFIG_240BW_320BH_120SW_160SH:
			{
				bigSize.m_nWidth = 240;
				bigSize.m_nHeight = 320;
				smallSize.m_nWidth = 120;
				smallSize.m_nHeight = 160;
			}
				break;              //3

			case VIDEO_CROP_CONFIG_480BW_480BH_SMALL_NONE:
			{
				bigSize.m_nWidth = 480;
				bigSize.m_nHeight = 480;
			}
				break;               //4
			case VIDEO_CROP_CONFIG_480BW_480BH_120SW_120SH:
			{
				bigSize.m_nWidth = 480;
				bigSize.m_nHeight = 480;
				smallSize.m_nWidth = 120;
				smallSize.m_nHeight = 120;
			}
				break;              //5
			case VIDEO_CROP_CONFIG_480BW_480BH_240SW_240SH:
			{
				bigSize.m_nWidth = 480;
				bigSize.m_nHeight = 480;
				smallSize.m_nWidth = 240;
				smallSize.m_nHeight = 240;
			}
				break;              //6

			case VIDEO_CROP_CONFIG_360BW_640BH_SMALL_NONE:
			{
				bigSize.m_nWidth = 360;
				bigSize.m_nHeight = 640;
			}
				break;               //7
			case VIDEO_CROP_CONFIG_360BW_640BH_90SW_160SH:
			{
				bigSize.m_nWidth = 360;
				bigSize.m_nHeight = 640;
				smallSize.m_nWidth = 90;
				smallSize.m_nHeight = 160;
			}
				break;               //8
			case VIDEO_CROP_CONFIG_360BW_640BH_180SW_320SH:
			{
				bigSize.m_nWidth = 360;
				bigSize.m_nHeight = 640;
				smallSize.m_nWidth = 180;
				smallSize.m_nHeight = 320;
			}
				break;              //9

			case VIDEO_CROP_CONFIG_480BW_640BH_SMALL_NONE:
			{
				bigSize.m_nWidth = 480;
				bigSize.m_nHeight = 640;
			}
				break;               //10
			case VIDEO_CROP_CONFIG_480BW_640BH_120SW_160SH:
			{
				bigSize.m_nWidth = 480;
				bigSize.m_nHeight = 640;
				smallSize.m_nWidth = 120;
				smallSize.m_nHeight = 160;
			}
				break;              //11
			case VIDEO_CROP_CONFIG_480BW_640BH_240SW_320SH:
			{
				bigSize.m_nWidth = 480;
				bigSize.m_nHeight = 640;
				smallSize.m_nWidth = 240;
				smallSize.m_nHeight = 320;
			}
				break;              //12

			case VIDEO_CROP_CONFIG_640BW_640BH_SMALL_NONE:
			{
				bigSize.m_nWidth = 640;
				bigSize.m_nHeight = 640;
			}
				break;               //13
			case VIDEO_CROP_CONFIG_640BW_640BH_160SW_160SH:
			{
				bigSize.m_nWidth = 640;
				bigSize.m_nHeight = 640;
				smallSize.m_nWidth = 160;
				smallSize.m_nHeight = 160;
			}
				break;              //14
			case VIDEO_CROP_CONFIG_640BW_640BH_320SW_320SH:
			{
				bigSize.m_nWidth = 640;
				bigSize.m_nHeight = 640;
				smallSize.m_nWidth = 320;
				smallSize.m_nHeight = 320;
			}
				break;              //15
			case VIDEO_CROP_CONFIG_720BW_1280BH_SMALL_NONE:
			{
				bigSize.m_nWidth = 720;
				bigSize.m_nHeight = 1280;
			}
				break;              //16
			case VIDEO_CROP_CONFIG_720BW_1280BH_90SW_160SH:
			{
				bigSize.m_nWidth = 720;
				bigSize.m_nHeight = 1280;
				smallSize.m_nWidth = 90;
				smallSize.m_nHeight = 160;
			}
				break;              //17
			case VIDEO_CROP_CONFIG_720BW_1280BH_180SW_320SH:
			{
				bigSize.m_nWidth = 720;
				bigSize.m_nHeight = 1280;
				smallSize.m_nWidth = 180;
				smallSize.m_nHeight = 320;
			}
				break;             //18
			case VIDEO_CROP_CONFIG_720BW_1280BH_360SW_640SH:
			{
				bigSize.m_nWidth = 720;
				bigSize.m_nHeight = 1280;
				smallSize.m_nWidth = 360;
				smallSize.m_nHeight = 640;
			}
				break;             //19

			case VIDEO_CROP_CONFIG_1080BW_1920BH_SMALL_NONE:
			{
				bigSize.m_nWidth = 1080;
				bigSize.m_nHeight = 1920;
			}
				break;             //20
			case VIDEO_CROP_CONFIG_1080BW_1920BH_135SW_240SH:
			{
				bigSize.m_nWidth = 1080;
				bigSize.m_nHeight = 1920;
				smallSize.m_nWidth = 135;
				smallSize.m_nHeight = 240;
			}
				break;            //21
			case VIDEO_CROP_CONFIG_1080BW_1920BH_270SW_480SH:
			{
				bigSize.m_nWidth = 1080;
				bigSize.m_nHeight = 1920;
				smallSize.m_nWidth = 270;
				smallSize.m_nHeight = 480;
			}
				break;            //22
			case VIDEO_CROP_CONFIG_1080BW_1920BH_540SW_960SH:
			{
				bigSize.m_nWidth = 1080;
				bigSize.m_nHeight = 1920;
				smallSize.m_nWidth = 540;
				smallSize.m_nHeight = 960;
			}
				break;            //23
			case VIDEO_CROP_CONFIG_BIG_NOCROP_SMALL_NONE:
			{
			}
				break;                //24
			default:
				break;
		}
	}
	static string getCropTypeDescribe(CROP_TYPE type)
	{
		string strRet = "";
		if (type == VIDEO_CROP_CONFIG_BIG_NOCROP_SMALL_NONE)
		{
			strRet = "大图:特殊制定|小图:无";
			return strRet;
		}
		CPicSize bigSize;
		CPicSize smallSize;
		getCropSize(type, bigSize, smallSize);
		strRet = "大图:";
		char buf[255] = { 0 };
		if (bigSize.m_nWidth > 0 && bigSize.m_nHeight > 0)
		{	
			memset(buf, 0, sizeof(buf));
			_itoa_s(bigSize.m_nWidth, buf, sizeof(buf), 10);
			strRet += buf;
			strRet += "*"; 
			memset(buf, 0, sizeof(buf));
			_itoa_s(bigSize.m_nHeight, buf, sizeof(buf), 10);
			strRet += buf;
		}
		else
		{
			strRet += "无";
		}
		strRet += "|小图:";

		if (smallSize.m_nWidth > 0 && smallSize.m_nHeight > 0)
		{
			memset(buf, 0, sizeof(buf));
			_itoa_s(smallSize.m_nWidth, buf, sizeof(buf), 10);
			strRet += buf;
			strRet += "*";
			memset(buf, 0, sizeof(buf));
			_itoa_s(smallSize.m_nHeight, buf, sizeof(buf), 10);
			strRet += buf;
		}
		else
		{
			strRet += "无";
		}
		return strRet;
	}
};
