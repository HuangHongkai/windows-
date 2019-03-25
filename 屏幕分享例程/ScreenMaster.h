#pragma once
#include <Windows.h>
#include <stdio.h>
#include <dxgi1_6.h>

struct screen_cap_conf
{

};

struct rect_t
{
	RECT   rc;             ///�����仯�ľ��ο�
	/////
	char*  line_buffer;    ///���ο�������ʼ��ַ
	int    line_bytes;     ///ÿ�У����ο�width��Ӧ�������ݳ���
	int    line_nextpos;   ///��0��ʼ����N�е����ݵ�ַ: line_buffer + N*line_nextpos ��
	int    line_count;     ///���ھ��ο�߶� height
};

struct frame_t
{
	int        cx;          ///��Ļ���
	int        cy;          ///��Ļ�߶�
	int        line_bytes;  ///ÿ��ɨ���е�ʵ�����ݳ���
	int        line_stride; ///ÿ��ɨ���е�4�ֽڶ�������ݳ���
	int        bitcount;    ///8.16.24.32 λ���, 8λ��256��ɫ�壻 16λ��555��ʽ��ͼ��

	int        length;      ///��Ļ���ݳ��� line_stride*cy
	char*      buffer;      ///��Ļ����
	/////
	int        rc_count;    ///�仯�������
	rect_t*   rc_array;    ///�仯����

	
	LPVOID      web;   
};

typedef int (*DISPLAYCHANGE_CALLBACK)(int width, int height, int bitcount, LPVOID params);
typedef int(*FRAME_CALLBACK)(frame_t frame);

struct create_t
{
	// ��ʼ��ScreenMaster�ṹ��
	DISPLAYCHANGE_CALLBACK display_change;
	FRAME_CALLBACK frame;
	LPVOID web;
	ULONG sleep_msec;
};

struct gdi_cap_t
{
	int        cx;
	int        cy;
	int        line_bytes;
	int        line_stride;
	int        bitcount; ////
	HDC        memdc;
	HBITMAP    hbmp;
	
	byte*      buffer; ///
	byte*      back_buf; ///
};

class ScreenMaster
{
public:
	ULONG sleep_msec; // ����
	bool quit;
	bool running;
	screen_cap_conf cap_conf;
	DISPLAYCHANGE_CALLBACK display_change;
	FRAME_CALLBACK frame;
	HANDLE hthread;
	DWORD tid;
	gdi_cap_t gdi;

public:
	ScreenMaster();
	ScreenMaster(create_t *conf);
	~ScreenMaster();

private:
	static DWORD WINAPI __loop(LPVOID instance);
	static DWORD __init_gdi(LPVOID instance);
};

