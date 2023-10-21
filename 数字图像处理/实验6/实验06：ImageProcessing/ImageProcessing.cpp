// ImageProcessing.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "resource.h"
#include <direct.h>
#include <cmath>
#include <commdlg.h>

#define MAX_LOADSTRING 100

BOOL ReadImage(LPSTR, char*, int, int); //读取图像信息并保存在Image[][]中
void ShowImage(char*, int, int, int, int);
BOOL ReadBmpImage(LPSTR, char*);
void ShowBmpImage(char*, int, int, int, int);
void OpenImageFileDlg(char*);
void ImageTranslation(char*, char*, int, int, int, int);
void ImageScaling(char*, char*, int, int, double, double);
void ImageRotation(char*, char*, int, int, double);
void SimpleGeometricTranslation(char*, char*, int, int, double*);

HDC  hWinDC;
int ImageWidth, ImageHeight;
char ImgDlgFileName[MAX_PATH];
char ImgDlgFileDir[MAX_PATH];
char OrgImage[1024 * 1024]; 
char newImage[1024 * 1024];
#define IMAGEWIDTH	256
#define IMAGEHEIGHT	256
#define XPOS		100
#define YPOS		100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];								// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];								// The title bar text

// Foward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int       nCmdShow)
{
	// MSG.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_IMAGEPROCESSING, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_IMAGEPROCESSING);

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage is only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = (WNDPROC)WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, (LPCTSTR)IDI_IMAGEPROCESSING);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = (LPCSTR)IDC_IMAGEPROCESSING;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, (LPCTSTR)IDI_SMALL);

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HANDLE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;

	hInst = hInstance; // Store instance handle in our global variable

	hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  FUNCTION: WndProc(HWND, unsigned, WORD, LONG)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	TCHAR szHello[MAX_LOADSTRING];
	LoadString(hInst, IDS_HELLO, szHello, MAX_LOADSTRING);

	switch (message)
	{
	case WM_CREATE:
		hWinDC = GetWindowDC(hWnd);
		break;

	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_SHOWRAWIMAGE:
			OpenImageFileDlg("打开图像文件");
			ReadImage(ImgDlgFileName, OrgImage, IMAGEWIDTH, IMAGEHEIGHT);
			ShowImage(OrgImage, IMAGEWIDTH, IMAGEHEIGHT, XPOS, YPOS);
			break;
		case IDM_SHOWBMPIMAGE:
			OpenImageFileDlg("打开图像文件");
			ReadBmpImage(ImgDlgFileName, OrgImage);
			ShowBmpImage(OrgImage, ImageWidth, ImageHeight, XPOS, YPOS);
			break;
		case IDM_TRANSLATION:
			ImageTranslation(OrgImage, newImage, IMAGEWIDTH, IMAGEHEIGHT, -20, -30);
			ShowImage(newImage, IMAGEWIDTH, IMAGEHEIGHT, XPOS, YPOS + 300);
			break;
			break;
		case IDM_SCALING:
			ImageScaling(OrgImage, newImage, IMAGEWIDTH, IMAGEHEIGHT, 0.5, 0.5);
			ShowImage(newImage, IMAGEWIDTH, IMAGEHEIGHT, XPOS, YPOS + 300);
			break;
			break;
		case IDM_ROTATION:
			ImageRotation(OrgImage, newImage, IMAGEWIDTH, IMAGEHEIGHT, -45.0);
			ShowImage(newImage, IMAGEWIDTH, IMAGEHEIGHT, XPOS, YPOS + 300);
			break;
		case IDM_ABOUT:
			DialogBox(hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		RECT rt;
		GetClientRect(hWnd, &rt);
		DrawText(hdc, szHello, strlen(szHello), &rt, DT_CENTER);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Mesage handler for about box.
LRESULT CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
		return TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}
		break;
	}
	return FALSE;
}




/************************************************************************************************
*																								*
*   读无格式RAW图像文件																			*
*																								*
************************************************************************************************/
BOOL ReadImage(LPSTR ImageFileName, char* oImage, int wImage, int hImage) //读取图像信息并保存在Image[][]中
{
	OFSTRUCT of;
	HFILE Image_fp;

	Image_fp = OpenFile(ImageFileName, &of, OF_READ);
	if (Image_fp == HFILE_ERROR)
	{
		MessageBox(NULL, ImageFileName, "打开文件出错信息", MB_OK);
		return FALSE;
	}

	_lread(Image_fp, oImage, wImage * hImage);
	_lclose(Image_fp);

	return TRUE;
}

/************************************************************************************************
*																								*
*   显示RAW图像																					*
*																								*
************************************************************************************************/
void ShowImage(char* Image, int wImage, int hImage, int xPos, int yPos)
{
	for (int i = 0; i < hImage; i++) {
		for (int j = 0; j < wImage; j++) {
			SetPixel(hWinDC, j + yPos, i + xPos,
				RGB(Image[i * wImage + j],
					Image[i * wImage + j],
					Image[i * wImage + j]));
		}
	}
}


/************************************************************************************************
*																								*
*   从BMP图像中，读出图像头信息，主要包括图像长度和宽度											*
*																								*
************************************************************************************************/
BOOL ReadBmpImage(LPSTR ImageFileName, char* oImage)
{
	BITMAPFILEHEADER bfImage;
	BITMAPINFOHEADER biImage;

	OFSTRUCT of;
	HFILE Image_fp;

	Image_fp = OpenFile(ImageFileName, &of, OF_READ);
	if (Image_fp == HFILE_ERROR)
	{
		MessageBox(NULL, ImageFileName, "打开文件出错信息", MB_OK);
		return FALSE;
	}

	_llseek(Image_fp, 0, 0);
	_lread(Image_fp, &bfImage, sizeof(BITMAPFILEHEADER));

	if ((bfImage.bfType != 0x4d42)) {		// "BM"
		MessageBox(NULL, NULL, "打开bmp文件出错信息", MB_OK);
		return FALSE;
	}

	_lread(Image_fp, &biImage, sizeof(BITMAPINFOHEADER));

	ImageWidth = biImage.biWidth;
	ImageHeight = biImage.biHeight;
	if (biImage.biBitCount != 24) {		// 24位彩色图像
		MessageBox(NULL, NULL, "不是24位bmp图像", MB_OK);
		return FALSE;
	}

	_llseek(Image_fp, bfImage.bfOffBits, 0);
	_lread(Image_fp, oImage, biImage.biWidth * biImage.biHeight * 3);
	_lclose(Image_fp);

	return TRUE;
}

/************************************************************************************************
*																								*
*   显示BMP图像																					*
*																								*
************************************************************************************************/
void ShowBmpImage(char* Image, int wImage, int hImage, int xPos, int yPos)
{
	HWND file = GetForegroundWindow();
	HDC filehdc = GetDC(file);
	BYTE r, g, b;
	int i = 0, j = 0;
	for (i = 0; i < hImage; i++) {
		for (j = 0; j < wImage; j++) {
			b = *Image++;
			g = *Image++;
			r = *Image++;
			SetPixel(filehdc, j + yPos, hImage + xPos - i, RGB(r, g, b));
		}
	}
}

void ImageTranslation(char* oImage, char* nImage, int wImage, int hImage,
	int xPos, int yPos)
{
	double gt_Array[9] = { 1, 0, 0,
			 0, 1, 0,
			 0, 0, 1 };

	gt_Array[2] = xPos;				 //水平方向平移距离
	gt_Array[5] = yPos;				 //垂直方向平移距离

	SimpleGeometricTranslation(oImage, nImage, wImage, hImage, gt_Array);
}

void ImageScaling(char* oImage, char* nImage, int wImage, int hImage,
	double xScaling, double yScaling)
{
	double gt_Array[9] = { 0, 0, 0,
			 0, 0, 0,
			 0, 0, 1 };
	gt_Array[0] = 1.0 / xScaling;		 //水平方向放大倍数
	gt_Array[4] = 1.0 / yScaling;		 //垂直方向放大倍数
	SimpleGeometricTranslation(oImage, nImage, wImage, hImage, gt_Array);
}


void ImageRotation(char* oImage, char* nImage, int wImage, int hImage,
	double iAngle)
{
	double pi = 3.14159;
	double gt_Array[9] = { 0, 0, 0,
				 0, 0, 0,
				 0, 0, 1 };
	iAngle = (iAngle / 360) * 2 * pi;
	gt_Array[0] = cos(iAngle);
	gt_Array[1] = -sin(iAngle);
	gt_Array[3] = sin(iAngle);
	gt_Array[4] = cos(iAngle);
	SimpleGeometricTranslation(oImage, nImage, wImage, hImage, gt_Array);
}


void SimpleGeometricTranslation(char* oImage, char* nImage, int wImage, int hImage,
	double* sgt_Array)
{
	double axy, bxy;		
	int i, sx, sy, ox, oy;
	for (i = 0; i < wImage * hImage; i++) 
		nImage[i] = 0;		  //清空新图像
	for (sy = 0; sy < hImage; sy++) {
		for (sx = 0; sx < wImage; sx++) {
			ox = sx - wImage / 2;				  //以图像中心为原点
			oy = sy - hImage / 2;
			axy = sgt_Array[0] * (double)ox + sgt_Array[1] * (double)oy + sgt_Array[2];
			bxy = sgt_Array[3] * (double)ox + sgt_Array[4] * (double)oy + sgt_Array[5];
			axy += wImage / 2;				  //恢复图像原点位置
			bxy += hImage / 2;
			if ((axy < 0.0) || (axy >= wImage - 1) || (bxy < 0.0) || (bxy >= hImage - 1))
				nImage[sy * wImage + sx] = 0;			  //超出范围部分置0
			else
				nImage[sy * wImage + sx] = oImage[((int)bxy) * wImage + (int)axy];
		}
	}
}

/************************************************************************************************
*																								*
*   打开读文件名系统对话框																		*
*																								*
************************************************************************************************/
void OpenImageFileDlg(char* OPDLTitle)
{
	char FileTitle[100];
	OPENFILENAME ofn;

	memset(&ofn, 0, sizeof(ofn));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = NULL;
	ofn.hInstance = NULL;
	ofn.lpstrFilter = TEXT("raw files\0*.raw\0All File\0*.*\0\0");
	ofn.lpstrCustomFilter = NULL;
	ofn.nMaxCustFilter = 0;
	ofn.nFilterIndex = 1;
	ofn.lpstrFile = ImgDlgFileName;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrFileTitle = FileTitle;
	ofn.nMaxFileTitle = 99;
	ofn.lpstrInitialDir = ImgDlgFileDir;
	ofn.lpstrTitle = OPDLTitle;
	ofn.Flags = OFN_FILEMUSTEXIST;
	ofn.lpstrDefExt = "raw";
	ofn.lCustData = NULL;
	ofn.lpfnHook = NULL;
	ofn.lpTemplateName = NULL;
	ImgDlgFileName[0] = '\0';
	GetOpenFileName(&ofn);

	getcwd(ImgDlgFileDir, MAX_PATH);
}
