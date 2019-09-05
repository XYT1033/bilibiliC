


-- 02_底层窗口实现（一）_WinMain入口函数 


--  D:\project_c++\Win32Project2\Win32Project2\源.c 

#include <windows.h> //底层实现窗口 的头文件

//6处理窗口过程

//CALLBACK  代表__stdcall 参数的传递顺序：从右到左 以此入栈，并且在函数返回前 清空堆栈
LRESULT CALLBACK WindowProc(
	HWND hwnd, //消息所属的窗口句柄
	UINT uMsg, //具体消息名称  WM_XXXX 消息名
	WPARAM wParam, //键盘附加消息
	LPARAM lParam  //鼠标附加消息
	)
{
	switch (uMsg)
	{
	case WM_CLOSE:
		//所有xxxWindow为结尾的方法 ，都不会进入到消息队列中，而是直接执行
		DestroyWindow(hwnd); //DestroyWindow 发送另一个消息 WM_DESTROY
		break;
	case  WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_LBUTTONDOWN: //鼠标左键按下
	{
							 int xPos = LOWORD(lParam);
							 int yPos = HIWORD(lParam);

							 char buf[1024];
							 wsprintf(buf, TEXT("x = %d,y = %d"), xPos, yPos);

							 MessageBox(hwnd, buf, TEXT("鼠标左键按下"), MB_OK);

							 break;
	}
	case WM_KEYDOWN: //键盘
		MessageBox(hwnd, TEXT("键盘按下"), TEXT("键盘按下"), MB_OK);
		break;

	case WM_PAINT: //绘图
	{
					   PAINTSTRUCT ps; //绘图结构体
					   HDC hdc = BeginPaint(hwnd, &ps);

					   TextOut(hdc, 100, 100, TEXT("HELLO"), strlen("HELLO"));

					   EndPaint(hwnd, &ps);
	}

		break;
	}




	//返回值用默认处理方式
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

//程序入口函数

//WINAPI 代表__stdcall 参数的传递顺序：从右到左 以此入栈，并且在函数返回前 清空堆栈
int WINAPI WinMain(
	HINSTANCE hInstance,  //应用程序实例句柄 
	HINSTANCE hPrevInstance, //上一个应用程序句柄，在win32环境下，参数一般为NULL，不起作用了
	LPSTR lpCmdLine, //char * argv[] 
	int nShowCmd) //显示命令 最大化、最小化 正常
{

	//1、设计窗口
	//2、注册窗口
	//3、创建窗口
	//4、显示和更新
	//5、通过循环取消息
	//6、处理消息 （窗口过程）

	//1、设计窗口
	WNDCLASS wc;
	wc.cbClsExtra = 0; //类的额外的内存 
	wc.cbWndExtra = 0; //窗口额外的内存
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //设置背景
	wc.hCursor = LoadCursor(NULL, IDC_HAND); //设置光标 如果第一个参数为NULL，代表使用系统提供的光标
	wc.hIcon = LoadIcon(NULL, IDI_ERROR); //图标   如果第一个参数为NULL，代表使用系统提供的光标
	wc.hInstance = hInstance;  //应用程序实例句柄  传入WinMain中的形参即可
	wc.lpfnWndProc = WindowProc;  //回调函数  窗口过程
	wc.lpszClassName = TEXT("WIN"); //指定窗口类名称
	wc.lpszMenuName = NULL; //菜单名称
	wc.style = 0; //显示风格 0代表默认风格

	//2、注册窗口类
	RegisterClass(&wc);

	//3、创建窗口
	/*
	lpClassName,  类名
	lpWindowName, 标题名
	dwStyle,  WS_OVERLAPPEDWINDOW 风格
	x,  显示坐标    CW_USEDEFAULT  默认值
	y,
	nWidth, 宽高
	nHeight,
	hWndParent,  父窗口 NULL
	hMenu,  菜单 NULL
	hInstance,  实例句柄 hInstance
	lpParam) 附加值 NULL
	*/

	HWND hwnd = CreateWindow(wc.lpszClassName, TEXT("WINDOWS"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

	//4、 显示和更新
	ShowWindow(hwnd, SW_SHOWNORMAL);
	UpdateWindow(hwnd);

	//5、 通过循环取消息
	/*
	HWND        hwnd; 主窗口句柄
	UINT        message; 具体消息名称
	WPARAM      wParam; 附加消息 键盘消息
	LPARAM      lParam; 附加消息 鼠标消息
	DWORD       time;  消息产生时间
	POINT       pt;    附加消息  鼠标消息  x y
	*/
	MSG msg;

	while (GetMessage(&msg, NULL, 0, 0))
	{
		/*
		_Out_ LPMSG lpMsg, 消息
		_In_opt_ HWND hWnd, 捕获窗口 填NULL代表捕获所有的窗口
		_In_ UINT wMsgFilterMin,  //最小和最大的过滤的消息  一般填入0
		_In_ UINT wMsgFilterMax)  //填0代表捕获所有消息
		*/
		//if (GetMessage(&msg, NULL, 0, 0) == FALSE)
		//{
		//	break;
		//}

		//翻译消息
		TranslateMessage(&msg);

		//不为false
		//分发消息
		DispatchMessage(&msg);

	}





	return 0;
}



 
-- 06_消息映射机制

 mfc 类库下载 ：   http://www.newxing.com/S9796F9464493/AFXV_DLL.H
 error LNK1104: 无法打开文件“mfc42ud.lib”	  http://www.newxing.com/Code/tool/1278.html


-- 无法打开 源 文件“stdafx.h”的解决方法  https://blog.csdn.net/lphbtm/article/details/50730807 
 
  在项目属性中展开C/C++，选择常规，在附加包含目录里加入“$(ProjectDir)” 



  -- D:\project_c++\mfc\mfc\mfc.h 
  
  #include <afxwin.h> //mfc头文件

class MyApp:public CWinApp //CWinApp应用程序类
{
public:
	//程序入口
	virtual BOOL InitInstance();

};


class MyFrame:public CFrameWnd //窗口框架类
{
public:
	MyFrame();

	//声明宏 提供消息映射机制
	DECLARE_MESSAGE_MAP()

	afx_msg void OnLButtonDown(UINT, CPoint);

	afx_msg void OnChar(UINT, UINT, UINT);

	afx_msg void OnPaint();
};



  
  --  D:\project_c++\mfc\mfc\mfc.cpp
  
  #include "mfc.h"

MyApp app; //全局应用程序对象，有且仅有一个

BOOL MyApp::InitInstance()
{
	//创建窗口
	MyFrame * frame = new MyFrame;

	//显示和更新
	frame->ShowWindow(SW_SHOWNORMAL);
	frame->UpdateWindow();

	m_pMainWnd = frame; //保存指向应用程序的主窗口的指针

	return TRUE; //返回正常初始化

}

//分界宏
BEGIN_MESSAGE_MAP(MyFrame, CFrameWnd)

	ON_WM_LBUTTONDOWN() //鼠标左键按下

	ON_WM_CHAR() //键盘

	ON_WM_PAINT() //绘图宏

END_MESSAGE_MAP()


MyFrame::MyFrame()
{
	Create(NULL, TEXT("mfc"));
}

void MyFrame::OnLButtonDown(UINT, CPoint point)
{

	/*TCHAR buf[1024];
	wsprintf(buf, TEXT("x = %d, y =%d"), point.x, point.y);

	MessageBox(buf);*/

	//mfc中的字符串  CString

	CString str;
	str.Format(TEXT("x = %d ,,,, y = %d "), point.x, point.y);

	MessageBox(str);

}

void MyFrame::OnChar(UINT key, UINT, UINT)
{

	CString str;
	str.Format(TEXT("按下了%c 键"), key);

	MessageBox(str);

}

void MyFrame::OnPaint()
{
	CPaintDC dc(this);  //CDC里找其他的能画的图形 

	dc.TextOutW(100, 100, TEXT("为了部落"));
	//画椭圆
	dc.Ellipse(10, 10, 100, 100);

	//多字节转为 宽字节 
	//TEXT是由自适应编码的转换
	// TCHER 自适应编码的转换
	//MessageBox(L"aaa");

	//统计字符串长度
	int num = 0;
	char * p = "aaaa";
	num = strlen(p);

	//统计宽字节的字符串长度
	wchar_t * p2 = L"bbbb";
	num = wcslen(p2);

	//char * 与 CString之间的转换   C++  string  .c_str();
	//char* -> CString
	char * p3 = "ccc";
	CString str = CString(p3);
	//CString  -> char *
	CStringA tmp;
	tmp = str;
	char * pp = tmp.GetBuffer();



}


//老外 1个字符对应1个字节 多字节
// 中文  1个字符对应多个字节  宽字节  Unicode   utf-8 3个  GBK 2个



  
  错误	1	error LNK1123: 转换到 COFF 期间失败:    https://jingyan.baidu.com/article/fc07f9891c556412ffe519fa.html
  
    https://www.cnblogs.com/croot/p/3525322.html 
  
  我的vs下面的版本号比较老，于是就把C:\Windows\Microsoft.NET\Framework\v4.0.30319\cvtres.exe拷贝到vs的\Microsoft Visual Studio 10.0\vc\bin\下，然后问题解决，谢谢
  
  
  
  
  
  -- 08_利用向导创建mfc  
  
  
  
  -- d:\project_c++\mfc_001\mfc_001\MainFrm.cpp 
  
void CMainFrame::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CFrameWnd::OnLButtonDown(nFlags, point);


	CString str;
	str.Format(TEXT("x=%d,y=%d"),point.x,point.y);
	MessageBox(str);
}

  
  -- d:\project_c++\mfc_001\mfc_001\mfc_001View.cpp 
  
  
void Cmfc_001View::OnDraw(CDC* pDC)
{
	Cmfc_001Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码

	pDC->TextOutW(100,200,TEXT("wocao"));
}


  void Cmfc_001View::OnPaint()  //干掉了 OnDraw 
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CView::OnPaint()

	dc.TextOouW(100,200,TEXT("nimei"));

}

  
  
  --  

  
  
  错误	1	error C2660: “CWnd::ShowWindow”: 函数不接受 0 个参数	d:\project_c++\dialogtest\dialogtest\dialogtestdlg.cpp	174	1	DialogTest

  
  

	
	
	
	
	

