
-- 1 

#include <iostream>
#include<Windows.h>  //windows 头文件  

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM); //窗口回调函数   H : Handler 简写： 句柄

//实例句柄-> 记事本可以开多个 每个都是 instance   , 第二个参数 eliminate 了
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpszCmdLine,int mCmdShow) {
	
	HWND hwnd;// windows instance 
	MSG msg;
	WNDCLASS wc;//窗口类  micorsoft 已经做好了  用c 结构做的
	//1 design 窗口类
	wc.style = 0;//default style 
	wc.lpfnWndProc = (WNDPROC)WndProc;//窗口过程
	wc.cbClsExtra = 0;// 窗口类额外数据  worthless
	wc.cbWndExtra = 0;//窗口额外数据 worthless 
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL,IDI_WINLOGO);
	wc.hCursor = LoadCursor(NULL,IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wc.lpszMenuName = NULL;//菜单  这里不要 菜单
	wc.lpszClassName = "useless";

	//2 register 窗口类
	RegisterClass(&wc);
	//3 create 窗口类 
	hwnd = CreateWindow(TEXT("useless"),TEXT("hello"),WS_OVERLAPPEDWINDOW,CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL,NULL,hInstance,NULL);
	//4 show and update 窗口
	ShowWindow(hwnd, mCmdShow);
	UpdateWindow(hwnd);
	//5 消息 loop
	while (GetMessage(&msg,NULL,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg); //转发到窗口 process 
	}
	system("pause");
}
//窗口过程 对各种 message 进行 deal 
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;// DC handler     dc: device context
	RECT rect;
	switch (message)
	{
	case WM_LBUTTONDOWN:
		MessageBox(hwnd,TEXT("feng shui"),TEXT("messageU"),MB_OK);
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hwnd,&ps);
		Ellipse(hdc,0,0,200,100);
		DrawText(hdc, TEXT("sentiment"),-1,&rect,
			DT_SINGLELINE|DT_CENTER|DT_VCENTER);
		EndPaint(hwnd,&ps);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	default:
		break;
	}
	return DefWindowProc(hwnd,message,wParam,lParam); //转给 windows deal
}






 --2 
 
 
 
 
  
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 


















