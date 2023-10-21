// ImageProcessing.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "resource.h"
#include <direct.h>
#include <commdlg.h>
#include <cmath>
#include <vector>
#include <algorithm>


#define MAX_LOADSTRING 100
#define HISTOGRAMHIEGHT	150

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
void ImageHistogramShowProcessing(char*, char*, int, int);
void ImageGrayReversionProcessing(char*, int, int);
void ThresholdImage(char*, int, int);
void EqualHist(char*, int, int);
void LogTransform(char*, int, int);
void PowTransform(char*, int, int);
void Contrast(char*, int, int);
void GrayCut(char*, int, int);
void BitCut(char*, int, int);
void Noise(char*, int, int, int);
void ImageMaskProcessing(char*, char*, int, int, int*, int, int);
void Mean(char*, char*, int, int);
void GaussAvg(char*, char*, int, int);
void Median (char*, char*, int, int);
void Max(char*, char*, int, int);
void Min(char*, char*, int, int);
void Middle(char*, char*, int, int);
void Sharpen(char*, char*, int, int);
void Edge(char*, char*, int, int);
void Lapacian(char*, char*, int, int);
void Sobel(char*, char*, int, int);
void Prewitt(char*, char*, int, int);
void Roberts(char*, char*, int, int);
void Canny(char*, char*, int, int);
void MaxImageMaskProcessing(char*, char*, int, int);
void CannyImageMaskProcessing(char*, char*, int, int, int*, int, int, int*, int, int);

HWND hWind;
HDC  hWinDC;
int ImageWidth, ImageHeight;
int iThreshold = 128;
char ImgDlgFileName[MAX_PATH];
char ImgDlgFileDir[MAX_PATH];
char OrgImage[1024 * 1024];
char NewImage[1024 * 1024];
double pointDrection[1024 * 1024];
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
				case IDM_HISTOGRAMSHOW:
					ImageHistogramShowProcessing(OrgImage, NewImage, IMAGEWIDTH, IMAGEHEIGHT);
					ShowImage(NewImage, IMAGEWIDTH, IMAGEHEIGHT, XPOS, YPOS + 300);
					break;
				case IDM_THRESHOLD:
					ThresholdImage(OrgImage, IMAGEWIDTH, IMAGEHEIGHT);
					ShowImage(OrgImage, IMAGEWIDTH, IMAGEHEIGHT, XPOS, YPOS + 300);    
					break;
				case IDM_Inverse:
					ImageGrayReversionProcessing(OrgImage, IMAGEWIDTH, IMAGEHEIGHT);
					ShowImage(OrgImage, IMAGEWIDTH, IMAGEHEIGHT, XPOS, YPOS + 300);
					break;
				case IDM_EqualHist:
					EqualHist(OrgImage, IMAGEWIDTH, IMAGEHEIGHT);
					ShowImage(OrgImage, IMAGEWIDTH, IMAGEHEIGHT, XPOS, YPOS + 300);
					break;
				case IDM_Log:
					LogTransform(OrgImage, IMAGEWIDTH, IMAGEHEIGHT);
					ShowImage(OrgImage, IMAGEWIDTH, IMAGEHEIGHT, XPOS, YPOS + 300);
					break;
				case IDM_Pow:
					PowTransform(OrgImage, IMAGEWIDTH, IMAGEHEIGHT);
					ShowImage(OrgImage, IMAGEWIDTH, IMAGEHEIGHT, XPOS, YPOS + 300);
					break;
				case IDM_Contrast:
					Contrast(OrgImage, IMAGEWIDTH, IMAGEHEIGHT);
					ShowImage(OrgImage, IMAGEWIDTH, IMAGEHEIGHT, XPOS, YPOS + 300);
					break;
				case IDM_GrayCut:
					GrayCut(OrgImage, IMAGEWIDTH, IMAGEHEIGHT);
					ShowImage(OrgImage, IMAGEWIDTH, IMAGEHEIGHT, XPOS, YPOS + 300);
					break;
				case IDM_BitCut:
					BitCut(OrgImage, IMAGEWIDTH, IMAGEHEIGHT);
					break;
				case IDM_SALT:
					Noise(OrgImage, IMAGEWIDTH, IMAGEHEIGHT, 1);
					ShowImage(OrgImage, IMAGEWIDTH, IMAGEHEIGHT, XPOS + 300, YPOS);
					break;
				case IDM_PEPPER:
					Noise(OrgImage, IMAGEWIDTH, IMAGEHEIGHT, 2);
					ShowImage(OrgImage, IMAGEWIDTH, IMAGEHEIGHT, XPOS, YPOS + 300);
					break;
				case IDM_SALPEP:
					Noise(OrgImage, IMAGEWIDTH, IMAGEHEIGHT, 3);
					ShowImage(OrgImage, IMAGEWIDTH, IMAGEHEIGHT, XPOS + 300, YPOS + 300);
					break;
				case IDM_MEAN:
					Mean(OrgImage, NewImage, IMAGEWIDTH, IMAGEHEIGHT);
					ShowImage(NewImage, IMAGEWIDTH, IMAGEHEIGHT, XPOS, YPOS + 300);
					break;
				case IDM_GAUSS:
					GaussAvg(OrgImage, NewImage, IMAGEWIDTH, IMAGEHEIGHT);
					ShowImage(NewImage, IMAGEWIDTH, IMAGEHEIGHT, XPOS, YPOS + 300);
					break;
				case IDM_SHARPEN:
					Sharpen(OrgImage, NewImage, IMAGEWIDTH, IMAGEHEIGHT);
					ShowImage(NewImage, IMAGEWIDTH, IMAGEHEIGHT, XPOS, YPOS + 300);
					break;
				case IDM_EDGE:
					Edge(OrgImage, NewImage, IMAGEWIDTH, IMAGEHEIGHT);
					ShowImage(NewImage, IMAGEWIDTH, IMAGEHEIGHT, XPOS, YPOS + 300);
					break;
				case IDM_MEDIAN:
					Median(OrgImage, NewImage, IMAGEWIDTH, IMAGEHEIGHT);
					ShowImage(NewImage, IMAGEWIDTH, IMAGEHEIGHT, XPOS, YPOS + 300);
					break;
				case IDM_MAX:
					Max(OrgImage, NewImage, IMAGEWIDTH, IMAGEHEIGHT);
					ShowImage(NewImage, IMAGEWIDTH, IMAGEHEIGHT, XPOS, YPOS + 300);
					break;
				case IDM_MIN:
					Min(OrgImage, NewImage, IMAGEWIDTH, IMAGEHEIGHT);
					ShowImage(NewImage, IMAGEWIDTH, IMAGEHEIGHT, XPOS, YPOS + 300);
					break;
				case IDM_LAPACIAN:
					Lapacian(OrgImage, NewImage, IMAGEWIDTH, IMAGEHEIGHT);
					ShowImage(NewImage, IMAGEWIDTH, IMAGEHEIGHT, XPOS, YPOS + 300);
					break;
				case IDM_SOBEL:
					Sobel(OrgImage, NewImage, IMAGEWIDTH, IMAGEHEIGHT);
					ShowImage(NewImage, IMAGEWIDTH, IMAGEHEIGHT, XPOS, YPOS + 300);
					break;
				case IDM_PREWITT:
					Prewitt(OrgImage, NewImage, IMAGEWIDTH, IMAGEHEIGHT);
					ShowImage(NewImage, IMAGEWIDTH, IMAGEHEIGHT, XPOS, YPOS + 300);
					break;
				case IDM_ROBERTS:
					Roberts(OrgImage, NewImage, IMAGEWIDTH, IMAGEHEIGHT);
					ShowImage(NewImage, IMAGEWIDTH, IMAGEHEIGHT, XPOS, YPOS + 300);
					break;
				case IDM_CANNY:
					Canny(OrgImage, NewImage, IMAGEWIDTH, IMAGEHEIGHT);
					ShowImage(NewImage, IMAGEWIDTH, IMAGEHEIGHT, XPOS, YPOS + 600);
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

void ImageHistogramShowProcessing(char* oImage, char* nImage, int wImage, int hImage){
	int i, j, Gray, MaxGrayCount;	
	int GrayCount[256];
	for (i = 0; i < 256; i++) 
		GrayCount[i] = 0;
	for (i = 0; i < wImage * hImage; i++){ 
		Gray = (BYTE)oImage[i];
		GrayCount[Gray]++; 
	}
	MaxGrayCount = GrayCount[0];
	for (i = 0; i < 256; i++) 
		if (MaxGrayCount < GrayCount[i]) 
			MaxGrayCount = GrayCount[i];
	for (i = 0; i < 256 * 256; i++) 
		nImage[i] = (BYTE)192;
	for (j = 0; j < 256; j++){
		GrayCount[j] = (int)(GrayCount[j] * HISTOGRAMHIEGHT / MaxGrayCount);
		for (i = 0; i < GrayCount[j]; i++) nImage[(255 - i) * 256 + j] = 0;
	}
}

void ImageGrayReversionProcessing(char* Image, int wImage, int hImage){
	int i;
	for (i = 0; i < wImage * hImage; i++)
		Image[i] = (BYTE)(255 - (BYTE)Image[i]);
}

void ThresholdImage(char* Image, int wImage, int hImage){
	int i;
	for (i = 0; i < wImage * hImage; i++)
		if ((BYTE)Image[i] < iThreshold) 
			Image[i] = 0;
		else 
			Image[i] = (BYTE)255;
}

void EqualHist(char* Image, int wImage, int hImage) {
	int gray[256] = { 0 };				//存储每个灰度值下的像素点
	int sum = wImage * hImage;			//总像素个数
	for (int i = 0; i < sum; i++) {		//统计每个灰度值的像素个数
		int k = (BYTE)Image[i];
		gray[k]++;
	}
	double  hs[256] = { 0 };
	for (int i = 0; i < 256; i++) {		//计算每个灰度值的密度
		hs[i] = (double(gray[i]) / sum);
	}
	double hp[256] = { 0 };
	hp[0] = hs[0];
	for (int i = 1; i < 256; i++) {		//记录灰度值的累计密度
		hp[i] = hs[i] + hp[i-1];
	}
	gray[0] = 0;
	for (int i = 1; i < 256; i++) {		//记录均衡化后的灰度值。
		gray[i] = hp[i] * 255;
	}
	for (int i = 0; i < sum; i++) {		//替换原像素点的灰度值
		Image[i] = (BYTE)(gray[(BYTE)Image[i]]);
	}
}

void LogTransform(char* Image, int wImage, int hImage) {
	int Max = -100;			//记录灰度变换后的最大灰度值
	int Min = 1000;			//记录灰度变换后的最小灰度值
	for (int i = 0; i < wImage * hImage; i++) {
		Image[i] = (BYTE)(6 * log((double)((BYTE)Image[i]) + 1));
		if ((BYTE)Image[i] > Max)
			Max = (BYTE)Image[i];
		if ((BYTE)Image[i] < Min)
			Min = (BYTE)Image[i];
	}
	for (int i = 0; i < wImage * hImage; i++) {//数据归一化处理
		Image[i] = (BYTE)(255 * ((BYTE)Image[i] - Min) / (Max - Min));
	}
}

void PowTransform(char* Image, int wImage, int hImage) {
	int Max = -100;			//记录灰度变换后的最大灰度值
	int Min = 1000;			//记录灰度变换后的最小灰度值
	for (int i = 0; i < wImage * hImage; i++) {
		Image[i] = (BYTE)(6 * pow(double((BYTE)Image[i]), 0.5));
		if ((BYTE)Image[i] > Max)
			Max = (BYTE)Image[i];
		if ((BYTE)Image[i] < Min)
			Min = (BYTE)Image[i];
	}
	for (int i = 0; i < wImage * hImage; i++) {//数据归一化处理
		Image[i] = (BYTE)(255 * ((BYTE)Image[i] - Min) / (Max - Min));
	}
}

void Contrast(char* Image, int wImage, int hImage) {
	for (int i = 0; i < wImage * hImage; i++) {
		if ((BYTE)Image[i] < 64)
			Image[i] = (BYTE)0;
		else if ((BYTE)Image[i] > 192)
			Image[i] = (BYTE)255;
		else
			Image[i] = (BYTE)((BYTE)Image[i] * 1.25);
	}
}

void GrayCut(char* Image, int wImage, int hImage) {
	for (int i = 0; i < wImage * hImage; i++) {
		if ((BYTE)Image[i] >= 96 && (BYTE)Image[i] <= 160)
			Image[i] = (BYTE)((BYTE)Image[i]+50);
	}
}

void BitCut(char* oImage, int wImage, int hImage) {
	for (int i = 1; i <=8 ; i++) {
		int Bit = 256 / (pow(2, i));
		char* Image = new char[1024 * 1024];
		strcpy(Image, oImage);
		for (int j = 0; j < pow(2, i - 1); j++) {
			for (int m = 0; m < wImage * hImage; m++) {
				if ((BYTE)Image[m] < (BYTE)(((2 * j) + 1) * Bit) 
					&& (BYTE)Image[m] >= (BYTE)((2 * j) * Bit) 
					&& (BYTE)Image[m] != (BYTE)0 
					&& (BYTE)Image[m] != (BYTE)255) {
					Image[m] = (BYTE)0;
				}
				else if ((BYTE)Image[m] >= (BYTE)(((2 * j) + 1) * Bit) 
					&& (BYTE)Image[m] < (BYTE)(((2 * j) + 2) * Bit
					&& (BYTE)Image[m] != (BYTE)0 
					&& (BYTE)Image[m] != (BYTE)255)) {
					Image[m] = (BYTE)255;
				}
			}
		}
		ShowImage(Image, wImage, hImage, XPOS+300*(i/3), YPOS + 300*(i%3));
	}
}

void Noise(char* Image, int wImage, int hImage, int flag) {
	for (int i = 0; i < 1000; i++) {
		//int x = rand() % ((wImage * hImage) + 1);
		int x = (RAND_MAX*rand()+rand()) % ((wImage * hImage)+1);
		//扩大伪随机数的范围
		if ((BYTE)Image[x] == 255)
			i--;
		else {
			switch (flag) {
			case 1:
				Image[x] = (BYTE)255;
				break;
			case 2:
				Image[x] = (BYTE)0;
				break;
			case 3:
				int temp = rand() % 2;
				if (temp == 1)
					Image[x] = (BYTE)255;
				else
					Image[x] = (BYTE)0;
				break;
			}
		}
	}
}

void ImageMaskProcessing(char* oImage, char* nImage, int wImage, int hImage,int* Mask, int MaskWH, int MaskCoff){
	int Coff;	int i, j, m, n;	int k;
	k = (MaskWH - 1) / 2;
	for (i = k; i < hImage - k; i++) {
		for (j = k; j < wImage - k; j++) {
			Coff = 0;
			for (m = -k; m <= k; m++) {
				for (n = -k; n <= k; n++) {
					Coff += (BYTE)oImage[(i + m) * wImage + (j + n)] *
						Mask[(m + k) * MaskWH + (n + k)];
				}
			}
			nImage[i * wImage + j] = (unsigned char)(Coff / MaskCoff);
			if (Coff < 0) nImage[i * wImage + j] = 0;
		}
	}
}

void XYImageMaskProcessing(char* oImage, char* nImage, int wImage, int hImage, int* XMask, int XMaskWH, int XMaskCoff,int *YMask,int YMaskWH,int YMaskCoff) {
	int Coff;	int i, j, m, n;	int k;
	int X, Y;
	k = (XMaskWH - 1) / 2;
	for (i = k; i < hImage - k; i++) {
		for (j = k; j < wImage - k; j++) {
			X = 0; Y = 0;
			for (m = -k; m <= k; m++) {
				for (n = -k; n <= k; n++) {
					X += (BYTE)oImage[(i + m) * wImage + (j + n)] *
						XMask[(m + k) * XMaskWH + (n + k)];
					Y += (BYTE)oImage[(i + m) * wImage + (j + n)] *
						YMask[(m + k) * YMaskWH + (n + k)];
				}
			}
			Coff = sqrt(X*X + Y*Y);
			nImage[i * wImage + j] = (unsigned char)(Coff / XMaskCoff);
			if (Coff < 0) nImage[i * wImage + j] = 0;
		}
	}
}

void Mean(char* oImage, char* nImage, int wImage, int hImage) {//均值滤波
	int Mask[9] = { 1,1,1,1,1,1,1,1,1 };
	ImageMaskProcessing(oImage, nImage, wImage, hImage, Mask, 3, 9);
}

void GaussAvg(char* oImage, char* nImage,int wImage, int hImage){//高斯滤波
	int Mask[9] = { 1,2,1,2,4,2,1,2,1 };
	ImageMaskProcessing(oImage, nImage, wImage, hImage, Mask, 3, 16);
}

void Sharpen(char* oImage, char* nImage, int wImage, int hImage) {//锐化
	int Mask[9] = { 0,-1,0,-1,5,-1,0,-1,0 };
	ImageMaskProcessing(oImage, nImage, wImage, hImage, Mask, 3, 1);
}

void Edge(char* oImage, char* nImage, int wImage, int hImage) {//边缘化
	int Mask[9] = { 1,1,1,1,-8,1,1,1,1 };
	ImageMaskProcessing(oImage, nImage, wImage, hImage, Mask, 3, 1);
}

void Median(char* oImage, char* nImage, int wImage, int hImage) {//中值滤波
	int Coff = 0;
	int k = 1;
	for (int i = 1; i < hImage - k; i++) {
		for (int j = k; j < wImage - k; j++) {
			Coff = 0;
			std::vector<int>mask;
			for (int m = -k; m <= k; m++) {
				for (int n = -k; n <= k; n++) {
					mask.push_back((BYTE)oImage[(i + m) * wImage + (j + n)]);
				}
			}
			sort(mask.begin(), mask.end());
			nImage[i * wImage + j] = (unsigned char)(mask[4]);
		}
	}
}

void Lapacian(char* oImage, char* nImage, int wImage, int hImage) {
	int Mask[9] = { 0,1,0,1,-4,1,0,1,0 };
	ImageMaskProcessing(oImage, nImage, wImage, hImage, Mask, 3, 1);
}

void Sobel(char* oImage, char* nImage, int wImage, int hImage) {
	int XMask[9] = { -1,0,1,-2,0,2,-1,0,1 };
	int YMask[9] = { -1,-2,-1,0,0,0,1,2,1 };
	XYImageMaskProcessing(oImage, nImage, wImage, hImage, XMask, 3, 1, YMask, 3, 1);
}

void Prewitt(char* oImage, char* nImage, int wImage, int hImage) {
	int XMask[9] = { -1,-1,-1,0,0,0,1,1,1 };
	int YMask[9] = { -1,0,1,-1,0,1,-1,0,1 };
	XYImageMaskProcessing(oImage, nImage, wImage, hImage, XMask, 3, 1, YMask, 3, 1);
}

void Roberts(char* oImage, char* nImage, int wImage, int hImage) {
	int Coff;	int i, j, m, n;	int k;
	int X, Y;
	for (i = 1; i < hImage - 1; i++) {
		for (j = 1; j < wImage - 1; j++) {
			X = 0; Y = 0;
			X += (BYTE)oImage[(i + 1) * wImage + j + 1] - (BYTE)oImage[i * wImage + j];
			Y += (BYTE)oImage[(i + 1) * wImage + j] - (BYTE)oImage[i * wImage + j + 1];
			Coff = sqrt(X * X + Y * Y);
			nImage[i * wImage + j] = (unsigned char)Coff;
			if (Coff < 0) nImage[i * wImage + j] = 0;
		}
	}
}

void MaxImageMaskProcessing(char* oImage, char* nImage, int wImage, int hImage) {//极大值滤波
	int Coff = 0;
	int k = 1;
	for (int i = 1; i < hImage - k; i++) {
		for (int j = k; j < wImage - k; j++) {
			Coff = 0;
			std::vector<int>mask;
			mask.push_back((BYTE)oImage[i * wImage + j] - (BYTE)oImage[i * wImage + j - 1]);
			mask.push_back((BYTE)oImage[i * wImage + j] - (BYTE)oImage[i * (wImage - 1) + j]);
			mask.push_back((BYTE)oImage[i * wImage + j + 1] - (BYTE)oImage[i * wImage + j]);
			mask.push_back((BYTE)oImage[i * (wImage + 1) + j] - (BYTE)oImage[i * wImage + j]);
			sort(mask.begin(), mask.end());
			if (nImage[i * wImage + j] != (unsigned char)(mask[3]))
				nImage[i * wImage + j] = 0;
		}
	}
}

void Max(char* oImage, char* nImage, int wImage, int hImage){//极大值滤波
	int Coff = 0;
	int k = 1;
	for (int i = 1; i < hImage - k; i++) {
		for (int j = k; j < wImage - k; j++) {
			Coff = 0;
			std::vector<int>mask;
			for (int m = -k; m <= k; m++) {
				for (int n = -k; n <= k; n++) {
					mask.push_back((BYTE)oImage[(i + m) * wImage + (j + n)]);
				}
			}
			sort(mask.begin(), mask.end());
			nImage[i * wImage + j] = (unsigned char)(mask[8]);
		}
	}
}

void Min(char* oImage, char* nImage, int wImage, int hImage){//极小值滤波
	int Coff = 0;
	int k = 1;
	for (int i = 1; i < hImage - k; i++) {
		for (int j = k; j < wImage - k; j++) {
			Coff = 0;
			std::vector<int>mask;
			for (int m = -k; m <= k; m++) {
				for (int n = -k; n <= k; n++) {
					mask.push_back((BYTE)oImage[(i + m) * wImage + (j + n)]);
				}
			}
			sort(mask.begin(), mask.end());
			nImage[i * wImage + j] = (unsigned char)(mask[0]);
		}
	}
}

void CannyImageMaskProcessing(char* oImage, char* nImage, int wImage, int hImage, 
	int* XMask, int XMaskWH, int XMaskCoff, 
	int* YMask, int YMaskWH, int YMaskCoff) {
	const float kEps = 0.000001f;
	int Coff;	int i, j, m, n;	int k;
	int X, Y;
	k = (XMaskWH - 1) / 2;
	for (i = k; i < hImage - k; i++) {
		for (j = k; j < wImage - k; j++) {
			X = 0; Y = 0;
			for (m = -k; m <= k; m++) {
				for (n = -k; n <= k; n++) {
					X += (BYTE)oImage[(i + m) * wImage + (j + n)] *
						XMask[(m + k) * XMaskWH + (n + k)];
					Y += (BYTE)oImage[(i + m) * wImage + (j + n)] *
						YMask[(m + k) * YMaskWH + (n + k)];
				}
			}
			Coff = sqrt(X * X + Y * Y);
			nImage[i * wImage + j] = (unsigned char)(Coff / XMaskCoff);
			if (Coff < 0) nImage[i * wImage + j] = 0;
		}
	}
	k = 0;
	for (int i = 1; i < hImage - 1; i++) {
		for (int j = 1; j < wImage - 1; j++) {
			double gradY = (BYTE)nImage[(i - 1) * wImage + j + 1] + ((BYTE)nImage[i * wImage + j + 1] * 2) + (BYTE)nImage[(i + 1) * wImage + j + 1] - (BYTE)nImage[(i - 1) * wImage + j - 1] - ((BYTE)nImage[i * wImage + j - 1] * 2) - (BYTE)nImage[(i + 1) * wImage + j - 1];
			double gradX = (BYTE)nImage[(i + 1) * wImage + j - 1] + ((BYTE)nImage[(i + 1) * wImage + j] * 2) + (BYTE)nImage[(i + 1) * wImage + j + 1] - (BYTE)nImage[(i - 1) * wImage + j - 1] - ((BYTE)nImage[(i - 1) * wImage + j] * 2) - (BYTE)nImage[(i - 1) * wImage + j + 1];
			if (gradX == 0)
				gradX = 0.00000000000000000001;
			pointDrection[k] = atan(gradY / gradX) * 57.3;
			pointDrection[k] += 90;
			k++;
		}
	}
}

void CannySobel(char* oImage, char* nImage, int wImage, int hImage) {
	int XMask[9] = { -1,0,1,-2,0,2,-1,0,1 };
	int YMask[9] = { -1,-2,-1,0,0,0,1,2,1 };
	CannyImageMaskProcessing(oImage, nImage, wImage, hImage, XMask, 3, 1, YMask, 3, 1);
}

void Canny(char* oImage, char* nImage, int wImage, int hImage) {
	for (int i = 0; i < hImage * wImage; i++)
		pointDrection[i] = 0;
	GaussAvg(oImage, nImage, wImage, hImage);
	for (int i = 0; i < wImage * hImage; i++)
		oImage[i] = (BYTE)nImage[i];
	memset(nImage, 0, sizeof(nImage));
	CannySobel(oImage, nImage, wImage, hImage);
	strcpy(oImage, nImage);
	for (int i = 0; i < wImage * hImage; i++)
		oImage[i] = (BYTE)nImage[i];
	ShowImage(oImage, wImage, hImage, XPOS + 300, YPOS + 300);
	int k = 0;
	for (int i = 1; i < hImage - 1; i++) {
		for (int j = 1; j < wImage - 1; j++) {
			int value00 = (BYTE)oImage[(i - 1) * wImage + j - 1];
			int value01 = (BYTE)oImage[(i - 1) * wImage + j];
			int value02 = (BYTE)oImage[(i - 1) * wImage + j + 1];
			int value10 = (BYTE)oImage[i * wImage + j - 1];
			int value11 = (BYTE)oImage[i * wImage + j];
			int value12 = (BYTE)oImage[i * wImage + j + 1];
			int value20 = (BYTE)oImage[(i + 1) * wImage + j - 1];
			int value21 = (BYTE)oImage[(i + 1) * wImage + j];
			int value22 = (BYTE)oImage[(i + 1) * wImage + j + 1];;
			if (pointDrection[k] > 0 && pointDrection[k] <= 45) {
				if (value11 <= (value12 + (value02 - value12) * tan(pointDrection[i * wImage + j])) || (value11 <= (value10 + (value20 - value10) * tan(pointDrection[i * wImage + j]))))
				{
					nImage[i + wImage + j] = (BYTE)0;
				}
			}
			if (pointDrection[k] > 45 && pointDrection[k] <= 90) {
				if (value11 <= (value01 + (value02 - value01) * tan(pointDrection[i * wImage + j])) || (value11 <= (value21 + (value20 - value21) * tan(pointDrection[i * wImage + j]))))
				{
					nImage[i + wImage + j] = (BYTE)0;
				}
			}
			if (pointDrection[k] > 90 && pointDrection[k] <= 135) {
				if (value11 <= (value01 + (value00 - value01) * tan(180 - pointDrection[i * wImage + j])) || (value11 <= (value21 + (value22 - value21) * tan(180 - pointDrection[i * wImage + j]))))
				{
					nImage[i + wImage + j] = (BYTE)0;
				}
			}
			if (pointDrection[k] > 135 && pointDrection[k] <= 180) {
				if (value11 <= (value10 + (value00 - value10) * tan(180 - pointDrection[i * wImage + j])) || (value11 <= (value12 + (value22 - value11) * tan(180 - pointDrection[i * wImage + j]))))
				{
					nImage[i + wImage + j] = (BYTE)0;
				}
			}
			k++;
		}
	}
	ShowImage(nImage, wImage, hImage, XPOS + 300, YPOS + 600);
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