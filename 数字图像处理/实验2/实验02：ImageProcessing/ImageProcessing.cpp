// ImageProcessing.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "resource.h"
#include <direct.h>
#include <commdlg.h>

#define MAX_LOADSTRING 100

BOOL ReadImage(LPSTR, char *, int, int); //读取图像信息并保存在Image[][]中
void ShowImage(char *, int, int, int, int);
BOOL ReadBmpImage(LPSTR, char *);
void ShowBmpImage(char *, int, int, int, int);
void OpenImageFileDlg(char *);
void MTS(char*, int, int, int, int);
void STM(char*, int, int, int, int);
void MTUD(char*, int, int, int, int);
void UDTM(char*, int, int, int, int);
void LeftShow(char*, int, int, int, int);
void RightShow(char*, int, int, int, int);
void UpShow(char*, int, int, int, int);
void DownShow(char*, int, int, int, int);
void InDis(char*, int, int, int, int);
void OutDis(char*, int, int, int, int);
void BMTS(char*, int, int, int, int);
void BSTM(char*, int, int, int, int);
void BMTUD(char*, int, int, int, int);
void BUDTM(char*, int, int, int, int);
void BLeftShow(char*, int, int, int, int);
void BRightShow(char*, int, int, int, int);
void BUpShow(char*, int, int, int, int);
void BDownShow(char*, int, int, int, int);
void BInDis(char*, int, int, int, int);
void BOutDis(char*, int, int, int, int);

HWND hWind;
HDC  hWinDC;
int ImageWidth, ImageHeight;
char ImgDlgFileName[MAX_PATH];
char ImgDlgFileDir[MAX_PATH];
char OrgImage[1024*1024];
#define GRAYCHANGENUM 5
#define SHUTTERNUM  5
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
 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_IMAGEPROCESSING, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow)) 
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

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI_IMAGEPROCESSING);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= (LPCSTR)IDC_IMAGEPROCESSING;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, (LPCTSTR)IDI_SMALL);

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
			wmId    = LOWORD(wParam); 
			wmEvent = HIWORD(wParam); 
			// Parse the menu selections:
			switch (wmId){
				case IDM_MTS:
					OpenImageFileDlg("打开图像文件");
					ReadImage(ImgDlgFileName, OrgImage, IMAGEWIDTH, IMAGEHEIGHT);
					MTS(OrgImage, IMAGEWIDTH, IMAGEHEIGHT, XPOS, YPOS);
					break;
				case IDM_STM:
					OpenImageFileDlg("打开图像文件");
					ReadImage(ImgDlgFileName, OrgImage, IMAGEWIDTH, IMAGEHEIGHT);
					STM(OrgImage, IMAGEWIDTH, IMAGEHEIGHT, XPOS, YPOS);
					break;
				case IDM_MTUD:
					OpenImageFileDlg("打开图像文件");
					ReadImage(ImgDlgFileName, OrgImage, IMAGEWIDTH, IMAGEHEIGHT);
					MTUD(OrgImage, IMAGEWIDTH, IMAGEHEIGHT, XPOS, YPOS);
					break;
				case IDM_UDTM:
					OpenImageFileDlg("打开图像文件");
					ReadImage(ImgDlgFileName, OrgImage, IMAGEWIDTH, IMAGEHEIGHT);
					UDTM(OrgImage, IMAGEWIDTH, IMAGEHEIGHT, XPOS, YPOS);
					break;
				case DShow:
					OpenImageFileDlg("打开图像文件");
					ReadImage(ImgDlgFileName, OrgImage, IMAGEWIDTH, IMAGEHEIGHT);
					DownShow(OrgImage, IMAGEWIDTH, IMAGEHEIGHT, XPOS, YPOS);
					break;
				case UShow:
					OpenImageFileDlg("打开图像文件");
					ReadImage(ImgDlgFileName, OrgImage, IMAGEWIDTH, IMAGEHEIGHT);
					UpShow(OrgImage, IMAGEWIDTH, IMAGEHEIGHT, XPOS, YPOS);
					break;
				case LShow:
					OpenImageFileDlg("打开图像文件");
					ReadImage(ImgDlgFileName, OrgImage, IMAGEWIDTH, IMAGEHEIGHT);
					LeftShow(OrgImage, IMAGEWIDTH, IMAGEHEIGHT, XPOS, YPOS);
					break;
				case RShow:
					OpenImageFileDlg("打开图像文件");
					ReadImage(ImgDlgFileName, OrgImage, IMAGEWIDTH, IMAGEHEIGHT);
					RightShow(OrgImage, IMAGEWIDTH, IMAGEHEIGHT, XPOS, YPOS);
					break;
				case InShow:
					OpenImageFileDlg("打开图像文件");
					ReadImage(ImgDlgFileName, OrgImage, IMAGEWIDTH, IMAGEHEIGHT);
					InDis(OrgImage, IMAGEWIDTH, IMAGEHEIGHT, XPOS, YPOS);
					break;
				case OutShow:
					OpenImageFileDlg("打开图像文件");
					ReadImage(ImgDlgFileName, OrgImage, IMAGEWIDTH, IMAGEHEIGHT);
					OutDis(OrgImage, IMAGEWIDTH, IMAGEHEIGHT, XPOS, YPOS);
					break;
				case BMPMTS:
					OpenImageFileDlg("打开图像文件");
					ReadBmpImage(ImgDlgFileName, OrgImage);
					BMTS(OrgImage, ImageWidth, ImageHeight, XPOS, YPOS);
					break;
				case BMPSTM:
					OpenImageFileDlg("打开图像文件");
					ReadBmpImage(ImgDlgFileName, OrgImage);
					BSTM(OrgImage, ImageWidth, ImageHeight, XPOS, YPOS);
					break;
				case BMPMTUD:
					OpenImageFileDlg("打开图像文件");
					ReadBmpImage(ImgDlgFileName, OrgImage);
					BMTUD(OrgImage, ImageWidth, ImageHeight, XPOS, YPOS);
					break;
				case BMPUDTM:
					OpenImageFileDlg("打开图像文件");
					ReadBmpImage(ImgDlgFileName, OrgImage);
					BUDTM(OrgImage, ImageWidth, ImageHeight, XPOS, YPOS);
					break;
				case BLShow:
					OpenImageFileDlg("打开图像文件");
					ReadBmpImage(ImgDlgFileName, OrgImage);
					BLeftShow(OrgImage, ImageWidth, ImageHeight, XPOS, YPOS);
					break;
				case BRShow:
					OpenImageFileDlg("打开图像文件");
					ReadBmpImage(ImgDlgFileName, OrgImage);
					BRightShow(OrgImage, ImageWidth, ImageHeight, XPOS, YPOS);
					break;
				case BUShow:
					OpenImageFileDlg("打开图像文件");
					ReadBmpImage(ImgDlgFileName, OrgImage);
					BUpShow(OrgImage, ImageWidth, ImageHeight, XPOS, YPOS);
					break;
				case BDShow:
					OpenImageFileDlg("打开图像文件");
					ReadBmpImage(ImgDlgFileName, OrgImage);
					BDownShow(OrgImage, ImageWidth, ImageHeight, XPOS, YPOS);
					break;
				case BInShow:
					OpenImageFileDlg("打开图像文件");
					ReadBmpImage(ImgDlgFileName, OrgImage);
					BInDis(OrgImage, ImageWidth, ImageHeight, XPOS, YPOS);
					break;
				case BOutShow:
					OpenImageFileDlg("打开图像文件");
					ReadBmpImage(ImgDlgFileName, OrgImage);
					BOutDis(OrgImage, ImageWidth, ImageHeight, XPOS, YPOS);
					break;
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
BOOL ReadImage(LPSTR ImageFileName, char *oImage, int wImage, int hImage) //读取图像信息并保存在Image[][]中
{
	OFSTRUCT of;
	HFILE Image_fp;

	Image_fp = OpenFile(ImageFileName, &of, OF_READ);
	if (Image_fp == HFILE_ERROR) 
	{
		MessageBox(NULL, ImageFileName, "打开文件出错信息", MB_OK);
		return FALSE;
	}

	_lread(Image_fp, oImage, wImage*hImage);
	_lclose(Image_fp);

	return TRUE;
}

/************************************************************************************************
*																								*
*   显示RAW图像																					*
*																								*
************************************************************************************************/
void ShowImage(char *Image, int wImage, int hImage, int xPos, int yPos)
{
	int i,j;

	for (i=0; i<hImage; i++) {
		for (j=0; j<wImage; j++) {
			SetPixel(hWinDC, j+yPos, i+xPos, RGB(Image[i*wImage+j],Image[i*wImage+j],Image[i*wImage+j]));
		}
	}
}

/************************************************************************************************
*																								*
*   从BMP图像中，读出图像头信息，主要包括图像长度和宽度											*
*																								*
************************************************************************************************/
BOOL ReadBmpImage(LPSTR ImageFileName, char *oImage)
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
	ImageHeight= biImage.biHeight;
	if (biImage.biBitCount != 24) {		// 24位彩色图像
		MessageBox(NULL, NULL, "不是24位bmp图像", MB_OK);
		return FALSE;
	}

	_llseek(Image_fp, bfImage.bfOffBits, 0);
	_lread(Image_fp, oImage, biImage.biWidth*biImage.biHeight*3);
	_lclose(Image_fp);

	return TRUE;
}

/************************************************************************************************
*																								*
*   显示BMP图像																					*
*																								*
************************************************************************************************/
void ShowBmpImage(char *Image, int wImage, int hImage, int xPos, int yPos)
{
	HWND file = GetForegroundWindow();  //窗口标识符
	HDC filehdc = GetDC(file);      //绘图标识符
	BYTE r, g, b;                   //三颜色
	int i = 0, j = 0;
	for (i = 0; i < hImage; i++) {
		for (j = 0; j < wImage; j++) {
			b = *Image++;
			g = *Image++;
			r = *Image++;           //依次遍历图片的像素点
			SetPixel(filehdc, j + yPos, hImage + xPos - i, RGB(r, g, b));
		}
	}
}

void ShowImageRect(char* Image, int wImage, int hImage,int xPos, int yPos, RECT ShowRect){
	int i, j;
	int r, g, b;
	for (i = ShowRect.top; i < ShowRect.bottom; i++) {
		for (j = ShowRect.left; j < ShowRect.right; j++) {
			r = g = b = (BYTE)Image[i * wImage + j];
			SetPixel(hWinDC, j + yPos, i + xPos, RGB(r, g, b));
		}
	}
}

void MTS(char* Image, int wImage, int hImage, int xPos, int yPos) {//中间往两边开门
	int i;
	RECT ShowRect;
	InvalidateRgn(hWind, NULL, TRUE);
	UpdateWindow(hWind);	// 清空窗口
	ShowRect.top = 0;
	ShowRect.bottom = hImage;
	for (i = 0; i < wImage / 2; i++) {
		ShowRect.left = wImage / 2 - i;
		ShowRect.right = ShowRect.left + 1;				//显示一列
		ShowImageRect(Image, wImage, hImage, xPos, yPos, ShowRect);	//左开门
		ShowRect.left = wImage / 2 + i;
		ShowRect.right = ShowRect.left + 1; 				//显示一列
		ShowImageRect(Image, wImage, hImage, xPos, yPos, ShowRect);	//右开门
		Sleep(1);
	}
}

void STM(char* Image, int wImage, int hImage, int xPos, int yPos) {//两边往中间关门
	int i;
	RECT ShowRect;
	InvalidateRgn(hWind, NULL, TRUE);
	UpdateWindow(hWind);	// 清空窗口
	ShowRect.top = 0;
	ShowRect.bottom = hImage;
	for (i = wImage / 2; i >= 0; i--) {
		ShowRect.left = wImage / 2 - i;
		ShowRect.right = ShowRect.left + 1;				//显示一列
		ShowImageRect(Image, wImage, hImage, xPos, yPos, ShowRect);	//左关门
		ShowRect.left = wImage / 2 + i;
		ShowRect.right = ShowRect.left + 1; 				//显示一列
		ShowImageRect(Image, wImage, hImage, xPos, yPos, ShowRect);	//右关门
		Sleep(1);
	}
}

void MTUD(char* Image, int wImage, int hImage, int xPos, int yPos) {//中间网上下开门
	int i;
	RECT ShowRect;
	InvalidateRgn(hWind, NULL, TRUE);
	UpdateWindow(hWind);	// 清空窗口
	ShowRect.left = 0;
	ShowRect.right = wImage;
	for (i = 0; i < hImage / 2; i++) {
		ShowRect.top = hImage / 2 - i;
		ShowRect.bottom = ShowRect.top + 1;				
		ShowImageRect(Image, wImage, hImage, xPos, yPos, ShowRect);
		ShowRect.top = hImage / 2 + i;
		ShowRect.bottom = ShowRect.top + 1; 				
		ShowImageRect(Image, wImage, hImage, xPos, yPos, ShowRect);	
		Sleep(1);
	}
}

void UDTM(char* Image, int wImage, int hImage, int xPos, int yPos) {//上下往中间关门
	int i;
	RECT ShowRect;
	InvalidateRgn(hWind, NULL, TRUE);
	UpdateWindow(hWind);	// 清空窗口
	ShowRect.left = 0;
	ShowRect.right = wImage;
	for (i = hImage / 2; i >= 0; i--) {
		ShowRect.top = hImage / 2 - i;
		ShowRect.bottom = ShowRect.top + 1;
		ShowImageRect(Image, wImage, hImage, xPos, yPos, ShowRect);
		ShowRect.top = hImage / 2 + i;
		ShowRect.bottom = ShowRect.top + 1;
		ShowImageRect(Image, wImage, hImage, xPos, yPos, ShowRect);
		Sleep(1);
	}
}

void DownShow(char* Image, int wImage, int hImage, int xPos, int yPos){//向下百叶窗显示
	int i, j;
	RECT ShowRect;
	InvalidateRgn(hWind, NULL, TRUE); 
	UpdateWindow(hWind);     //清空窗口
	ShowRect.left = 0;
	ShowRect.right = hImage;
	for (i = 0; i <= wImage / SHUTTERNUM; i++) {	 //SHUTTERNUM是百叶窗格数
		for (j = 0; j < SHUTTERNUM; j++) {
			ShowRect.top = i + (j * wImage / SHUTTERNUM);
			ShowRect.bottom = ShowRect.top + 1; 	      //显示一行
			ShowImageRect(Image, wImage, hImage, xPos, yPos, ShowRect);
			Sleep(1);
		}
	}
}

void UpShow(char* Image, int wImage, int hImage, int xPos, int yPos){//向上百叶窗显示
	int i, j;
	RECT ShowRect;
	InvalidateRgn(hWind, NULL, TRUE); 
	UpdateWindow(hWind);     //清空窗口
	ShowRect.left = 0;
	ShowRect.right = hImage;
	for (i = wImage / SHUTTERNUM; i >= 0; i--) {	 //SHUTTERNUM是百叶窗格数
		for (j = 0; j < SHUTTERNUM; j++) {
			ShowRect.top = i + (j * wImage / SHUTTERNUM);
			ShowRect.bottom = ShowRect.top + 1; 	      //显示一行
			ShowImageRect(Image, wImage, hImage, xPos, yPos, ShowRect);
			Sleep(1);
		}
	}
}

void RightShow(char* Image, int wImage, int hImage, int xPos, int yPos) {//向右百叶窗显示
	int i, j;
	RECT ShowRect;
	InvalidateRgn(hWind, NULL, TRUE); 
	UpdateWindow(hWind);     //清空窗口
	ShowRect.top = 0;
	ShowRect.bottom = hImage;
	for (i = 0; i <= hImage / SHUTTERNUM; i++) {	 //SHUTTERNUM是百叶窗格数
		for (j = 0; j < SHUTTERNUM; j++) {
			ShowRect.left = i + (j * hImage / SHUTTERNUM);
			ShowRect.right = ShowRect.left + 1; 	      //显示一行
			ShowImageRect(Image, wImage, hImage, xPos, yPos, ShowRect);
			Sleep(1);
		}
	}
}

void LeftShow(char* Image, int wImage, int hImage, int xPos, int yPos) {//向左百叶窗显示
	int i, j;
	RECT ShowRect;
	InvalidateRgn(hWind, NULL, TRUE);
	UpdateWindow(hWind);     //清空窗口
	ShowRect.top = 0;
	ShowRect.bottom = hImage;
	for (i = hImage / SHUTTERNUM; i >= 0; i--) {	 //SHUTTERNUM是百叶窗格数
		for (j = 0; j < SHUTTERNUM; j++) {
			ShowRect.left = i + (j * hImage / SHUTTERNUM);
			ShowRect.right = ShowRect.left + 1; 	      //显示一行
			ShowImageRect(Image, wImage, hImage, xPos, yPos, ShowRect);
			Sleep(1);
		}
	}
}

void InDis(char* Image, int wImage, int hImage, int xPos, int yPos){//淡入显示
	int i, j, m;		
	int r, g, b, gray;
	for (m = 1; m < GRAYCHANGENUM; m++) {
		for (i = 0; i < hImage; i++) {
			for (j = 0; j < wImage; j++) {
				gray = ((BYTE)Image[i * wImage + j]);
				r = g = b = gray * (GRAYCHANGENUM - m) / GRAYCHANGENUM;
				SetPixel(hWinDC, j + yPos, i + xPos, RGB(r, g, b));
			}
		}
	}
}

void OutDis(char* Image, int wImage, int hImage, int xPos, int yPos){//淡出显示
	int i, j, m;
	int r, g, b, gray;
	for (m = GRAYCHANGENUM; m >=1 ; m--) {
		for (i = 0; i < hImage; i++) {
			for (j = 0; j < wImage; j++) {
				gray = ((BYTE)Image[i * wImage + j]);
				r = g = b = gray * (GRAYCHANGENUM - m) / GRAYCHANGENUM;
				SetPixel(hWinDC, j + yPos, i + xPos, RGB(r, g, b));
			}
		}
	}
}

void BMPShowImageRect(char* Image, int wImage, int hImage, int xPos, int yPos, RECT ShowRect) {
	int i, j;
	BYTE r, g, b;
	HWND file = GetForegroundWindow();  //窗口标识符
	HDC filehdc = GetDC(file);
	char* p = Image;
	for (i = 0; i < hImage; i++) {
		for (j = 0; j < wImage; j++) {
			b = *p++;
			g = *p++;
			r = *p++;
			if (i >= ShowRect.top && i < ShowRect.bottom && j >= ShowRect.left && j < ShowRect.right)
				SetPixel(filehdc, j + yPos, hImage + xPos - i, RGB(r, g, b));
		}
	}
}

void BMTS(char* Image, int wImage, int hImage, int xPos, int yPos) {//中间往两边开门
	int i;
	RECT ShowRect;
	InvalidateRgn(hWind, NULL, TRUE);
	UpdateWindow(hWind);	// 清空窗口
	ShowRect.top = 0;
	ShowRect.bottom = hImage;
	for (i = 0; i < wImage / 2; i++) {
		ShowRect.left = wImage / 2 - i;
		ShowRect.right = ShowRect.left + 1;				//显示一列
		BMPShowImageRect(Image, wImage, hImage, xPos, yPos, ShowRect);	//左开门
		ShowRect.left = wImage / 2 + i;
		ShowRect.right = ShowRect.left + 1; 				//显示一列
		BMPShowImageRect(Image, wImage, hImage, xPos, yPos, ShowRect);	//右开门
		Sleep(1);
	}
}

void BSTM(char* Image, int wImage, int hImage, int xPos, int yPos) {//两边往中间关门
	int i;
	RECT ShowRect;
	InvalidateRgn(hWind, NULL, TRUE);
	UpdateWindow(hWind);	// 清空窗口
	ShowRect.top = 0;
	ShowRect.bottom = hImage;
	for (i = wImage / 2; i >= 0; i--) {
		ShowRect.left = wImage / 2 - i;
		ShowRect.right = ShowRect.left + 1;				//显示一列
		BMPShowImageRect(Image, wImage, hImage, xPos, yPos, ShowRect);	//左关门
		ShowRect.left = wImage / 2 + i;
		ShowRect.right = ShowRect.left + 1; 				//显示一列
		BMPShowImageRect(Image, wImage, hImage, xPos, yPos, ShowRect);	//右关门
		Sleep(1);
	}
}

void BMTUD(char* Image, int wImage, int hImage, int xPos, int yPos) {//中间网上下开门
	int i;
	RECT ShowRect;
	InvalidateRgn(hWind, NULL, TRUE);
	UpdateWindow(hWind);	// 清空窗口
	ShowRect.left = 0;
	ShowRect.right = wImage;
	for (i = 0; i < hImage / 2; i++) {
		ShowRect.top = hImage / 2 - i;
		ShowRect.bottom = ShowRect.top + 1;
		BMPShowImageRect(Image, wImage, hImage, xPos, yPos, ShowRect);
		ShowRect.top = hImage / 2 + i;
		ShowRect.bottom = ShowRect.top + 1;
		BMPShowImageRect(Image, wImage, hImage, xPos, yPos, ShowRect);
		Sleep(1);
	}
}

void BUDTM(char* Image, int wImage, int hImage, int xPos, int yPos) {//上下往中间关门
	int i;
	RECT ShowRect;
	InvalidateRgn(hWind, NULL, TRUE);
	UpdateWindow(hWind);	// 清空窗口
	ShowRect.left = 0;
	ShowRect.right = wImage;
	for (i = hImage / 2; i >= 0; i--) {
		ShowRect.top = hImage / 2 - i;
		ShowRect.bottom = ShowRect.top + 1;
		BMPShowImageRect(Image, wImage, hImage, xPos, yPos, ShowRect);
		ShowRect.top = hImage / 2 + i;
		ShowRect.bottom = ShowRect.top + 1;
		BMPShowImageRect(Image, wImage, hImage, xPos, yPos, ShowRect);
		Sleep(1);
	}
}

void BDownShow(char* Image, int wImage, int hImage, int xPos, int yPos) {//向下百叶窗显示
	int i, j;
	RECT ShowRect;
	InvalidateRgn(hWind, NULL, TRUE);
	UpdateWindow(hWind);     //清空窗口
	ShowRect.left = 0;
	ShowRect.right = wImage;
	for (i = 0; i < hImage / SHUTTERNUM; i++) {	 //SHUTTERNUM是百叶窗格数
		for (j = 0; j < SHUTTERNUM; j++) {
			ShowRect.top = i + (j * hImage / SHUTTERNUM);
			ShowRect.bottom = ShowRect.top + 1; 	      //显示一行
			BMPShowImageRect(Image, wImage, hImage, xPos, yPos, ShowRect);
			Sleep(1);
		}
	}
}

void BUpShow(char* Image, int wImage, int hImage, int xPos, int yPos) {//向上百叶窗显示
	int i, j;
	RECT ShowRect;
	InvalidateRgn(hWind, NULL, TRUE);
	UpdateWindow(hWind);     //清空窗口
	ShowRect.left = 0;
	ShowRect.right = wImage;
	for (i = hImage / SHUTTERNUM; i >= 0; i--) {	 //SHUTTERNUM是百叶窗格数
		for (j = 0; j < SHUTTERNUM; j++) {
			ShowRect.top = i + (j * hImage / SHUTTERNUM);
			ShowRect.bottom = ShowRect.top + 1; 	      //显示一行
			BMPShowImageRect(Image, wImage, hImage, xPos, yPos, ShowRect);
			Sleep(1);
		}
	}
}

void BRightShow(char* Image, int wImage, int hImage, int xPos, int yPos) {//向右百叶窗显示
	int i, j;
	RECT ShowRect;
	InvalidateRgn(hWind, NULL, TRUE);
	UpdateWindow(hWind);     //清空窗口
	ShowRect.top = 0;
	ShowRect.bottom = hImage;
	for (i = 0; i < wImage / SHUTTERNUM; i++) {	 //SHUTTERNUM是百叶窗格数
		for (j = 0; j < SHUTTERNUM; j++) {
			ShowRect.left = i + (j * wImage / SHUTTERNUM);
			ShowRect.right = ShowRect.left + 1; 	      //显示一行
			BMPShowImageRect(Image, wImage, hImage, xPos, yPos, ShowRect);
			Sleep(1);
		}
	}
}

void BLeftShow(char* Image, int wImage, int hImage, int xPos, int yPos) {//向左百叶窗显示
	int i, j;
	RECT ShowRect;
	InvalidateRgn(hWind, NULL, TRUE);
	UpdateWindow(hWind);     //清空窗口
	ShowRect.top = 0;
	ShowRect.bottom = hImage;
	for (i = wImage / SHUTTERNUM; i >= 0; i--) {	 //SHUTTERNUM是百叶窗格数
		for (j = 0; j < SHUTTERNUM; j++) {
			ShowRect.left = i + (j * wImage / SHUTTERNUM);
			ShowRect.right = ShowRect.left + 1; 	      //显示一行
			BMPShowImageRect(Image, wImage, hImage, xPos, yPos, ShowRect);
			Sleep(1);
		}
	}
}

void BInDis(char* Image, int wImage, int hImage, int xPos, int yPos) {//淡入显示
	int i, j, m;
	BYTE r, g, b, gray;
	for (m = 1; m < GRAYCHANGENUM; m++) {
		for (i = 0; i < hImage; i++) {
			for (j = 0; j < wImage; j++) {
				gray = ((BYTE)Image[(i * wImage + j) * 3]);
				gray++;
				b = gray * (GRAYCHANGENUM - m) / GRAYCHANGENUM;
				gray++;
				g = gray* (GRAYCHANGENUM - m) / GRAYCHANGENUM;
				gray++;
				r = gray * (GRAYCHANGENUM - m) / GRAYCHANGENUM;
				SetPixel(hWinDC, j + yPos, xPos + hImage - i, RGB(r, g, b));
			}
		}
	}
}

void BOutDis(char* Image, int wImage, int hImage, int xPos, int yPos) {//淡出显示
	int i, j, m;
	BYTE r, g, b, gray;
	for (m = GRAYCHANGENUM; m >= 1; m--) {
		for (i = 0; i < hImage; i++) {
			for (j = 0; j < wImage; j++) {
				gray = ((BYTE)Image[(i * wImage + j) * 3]);
				gray++;
				b = gray * (GRAYCHANGENUM - m) / GRAYCHANGENUM;
				gray++;
				g = gray * (GRAYCHANGENUM - m) / GRAYCHANGENUM;
				gray++;
				r = gray * (GRAYCHANGENUM - m) / GRAYCHANGENUM;
				SetPixel(hWinDC, j + yPos, xPos + hImage - i, RGB(r, g, b));
			}
		}
	}
}
/************************************************************************************************
*																								*
*   打开读文件名系统对话框																		*
*																								*
************************************************************************************************/
void OpenImageFileDlg(char *OPDLTitle)
{
	char FileTitle[100];
	OPENFILENAME ofn;

	memset(&ofn,0,sizeof(ofn));
	ofn.lStructSize=sizeof(OPENFILENAME);
	ofn.hwndOwner=NULL;
	ofn.hInstance=NULL;
	ofn.lpstrFilter=TEXT("raw files\0*.raw\0All File\0*.*\0\0");
	ofn.lpstrCustomFilter=NULL;
	ofn.nMaxCustFilter=0;
	ofn.nFilterIndex=1;
	ofn.lpstrFile=ImgDlgFileName;
	ofn.nMaxFile=MAX_PATH;
	ofn.lpstrFileTitle=FileTitle;
	ofn.nMaxFileTitle=99;
	ofn.lpstrInitialDir=ImgDlgFileDir;
	ofn.lpstrTitle=OPDLTitle;
	ofn.Flags=OFN_FILEMUSTEXIST;
	ofn.lpstrDefExt="raw";
	ofn.lCustData=NULL;
	ofn.lpfnHook=NULL;
	ofn.lpTemplateName=NULL;
	ImgDlgFileName[0]='\0';
	GetOpenFileName(&ofn); 

	getcwd(ImgDlgFileDir, MAX_PATH);
}
