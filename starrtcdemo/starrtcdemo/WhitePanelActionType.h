#pragma once


enum WHITE_PANEL_ACTION {
	WHITE_PANEL_EMPTY,          //0 无
	WHITE_PANEL_START,          //1 笔画起点
	WHITE_PANEL_MOVE,           //2 笔画移动
	WHITE_PANEL_END,            //3 笔画终点
	WHITE_PANEL_REVOKE,         //4 撤销
	WHITE_PANEL_SERIAL,         //5
	WHITE_PANEL_CLEAR,          //6 清除
	WHITE_PANEL_CLEAR_ACK,      //7 清除反馈
	WHITE_PANEL_SYNC_REQUEST,   //8 同步请求
	WHITE_PANEL_SYNC,           //9 同步
	WHITE_PANEL_SYNC_PREPARE,   //10 同步准备
	WHITE_PANEL_SYNC_PREPARE_ACK,//11 同步准备反馈
	WHITE_PANEL_LASER_PEN,      //12 激光笔
	WHITE_PANEL_LASER_PEN_END,  //13 激光笔结束
	WHITE_PANEL_FILE            //14 文件
};
