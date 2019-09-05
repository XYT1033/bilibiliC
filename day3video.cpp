


 vs2010打开高版本vs创建的工程 https://wenku.baidu.com/view/b3446ac7caaedd3382c4d36d.html

  怎么看vs2010版本 https://zhidao.baidu.com/question/414905817.html


error MSB8008: 指定的平台工具集(v141)未安装或无效。请确保选择受支持的 PlatformToolset 值。 https://blog.csdn.net/l609043941/article/details/37758591
 错误解决：配置属性->常规->平台工具集中把V110改为V100.
  
  
1>项目文件包含 ToolsVersion="15.0"。此工具集可能未知或缺失。在这种情况下，通过安装 MSBuild 的正确版本，  
     最简单的解决办法就是在你本机创建一个同名的mfc工程，然后把除了项目工程文件以外的其他文件拷到这个工程下，再添加到工程里。
  

  
error C2857: 在源文件中没有找到用 /YcStdAfx.h 命令行选项指定的“#include”语句	 https://zhidao.baidu.com/question/745431781712556132.html
  在cpp文件第一行加上 #include "stdafx.h"
  
  
error C2220: 警告被视为错误 - 没有生成“object”文件   https://blog.csdn.net/bagboy_taobao_com/article/details/5613625 
  
  解决方案：

1. 启动Microsoft Visual Studio 2005，文件->打开->选择该cpp，然后保存。从新打开程序文件运行，此错误不再出现。

     如果不行， 则 2

2. 如果上述不能去掉错误，还可以点击项目，右击选择属性->配置属性->c/c++->常规，将“警告视为错误”的选项改为“否”。就可以！



resource.h源文件的理解  https://blog.csdn.net/xuanyuanlei1020/article/details/61932684


_stdcall 是什么？   https://blog.csdn.net/thimin/article/details/1529386

  
-- 01_项目简介以及项目基本配置 

 新建 MFC 项目 ： SaleSystem   

在项目 -> 属性 -> C/C++->预处理器 -> 预处理器定中添加 _CRT_SECURE_NO_WARNINGS ：



    J:\czbk_c++\MFC教程视频\day3video\Day3_MFC3_Case\SaleSystem\SaleSystem\res  里 user.ico    re.ico  复制到项目中 

   re.ico 改名 ： IDI_ICON_RE 
  user.ico   改名 ：  IDI_ICON_WIN 

  
  
  -- D:\project_c++\SaleSystem\SaleSystem\MainFrm.cpp
  
int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	//设置图标，IDI_ICON_WIN为图标资源ID，此为WINAPI函数
	SetClassLong(m_hWnd, GCL_HICON, (LONG)AfxGetApp()->LoadIconW(IDI_ICON_WIN));

	//设置标题 右侧标题
	SetTitle(TEXT("2017/3/12"));

	//设置窗口大小
	MoveWindow(0, 0, 800, 500);

	//设置居中显示
	CenterWindow();

	return 0;
}

-- D:\project_c++\SaleSystem\SaleSystem\SaleSystemDoc.cpp 

BOOL CSaleSystemDoc::OnNewDocument()
{
	//CDocument 文档类简介  https://blog.csdn.net/Lirx_Tech/article/details/48660265
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)
	SetTitle(TEXT("wocao"));

	return TRUE;
}



-- 02_CInfoFile类的引入 


--  D:\project_c++\SaleSystem\SaleSystem\InfoFile.h

#pragma once

#include <list>
#include <fstream>
#include <iostream>
#include <string>

#define _F_LOGIN "./login.ini"
#define _F_STOCK "./stock.txt"

using namespace std;

struct msg
{
	int id;				//商品id
	string name;	//商品名
	int price;			//商品价格
	int num;			//商品个数
};

class CInfoFile
{
public:
	CInfoFile();
	~CInfoFile();

	//读取登陆信息
	void ReadLogin(CString &name, CString &pwd);

	//修改密码
	void WritePwd(char* name, char* pwd);

	// 读取商品数据
	void ReadDocline();

	//商品写入文件
	void WirteDocline();

	//添加新商品
	void Addline(CString name, int num, int price);

	list<msg> ls;	//存储商品容器
	int num;			//用来记录商品个数
};


--  D:\project_c++\SaleSystem\SaleSystem\InfoFile.cpp 

#include "stdafx.h"
#include "InfoFile.h"


CInfoFile::CInfoFile()
{
}


CInfoFile::~CInfoFile()
{
}

//读取登陆信息
void CInfoFile::ReadLogin(CString &name, CString &pwd)
{
	ifstream ifs; //创建文件输入对象
	ifs.open(_F_LOGIN); //打开文件

	char buf[1024] = { 0 };

	ifs.getline(buf, sizeof(buf)); //读取一行内容
	name = CString(buf);			 //char *转换为CString

	ifs.getline(buf, sizeof(buf));
	pwd = CString(buf);

	ifs.close(); //关闭文件
}

//修改密码
void CInfoFile::WritePwd(char* name, char* pwd)
{
	ofstream ofs;	 //创建文件输出对象
	ofs.open(_F_LOGIN); //打开文件

	ofs << name << endl; //name写入文件
	ofs << pwd << endl;	//pwd写入文件

	ofs.close();	//关闭文件
}

//读取商品信息
void CInfoFile::ReadDocline()
{
	ifstream ifs(_F_STOCK); //输入方式打开文件

	char buf[1024] = { 0 };
	num = 0;	//初始化商品数目为0
	ls.clear();
	//取出表头
	ifs.getline(buf, sizeof(buf));

	while (!ifs.eof()) //没到文件结尾
	{
		msg tmp;

		ifs.getline(buf, sizeof(buf)); //读取一行
		num++;	//商品数目加一

		//AfxMessageBox(CString(buf));
		char *sst = strtok(buf, "|"); //以“|”切割
		if (sst != NULL)
		{
			tmp.id = atoi(sst); //商品id
		}
		else
		{
			break;
		}

		sst = strtok(NULL, "|");
		tmp.name = sst;	//商品名称

		sst = strtok(NULL, "|");
		tmp.price = atoi(sst);	//商品价格

		sst = strtok(NULL, "|");
		tmp.num = atoi(sst);	//商品数目

		ls.push_back(tmp); //放在链表的后面
	}

	ifs.close(); //关闭文件
}

//商品写入文件
void CInfoFile::WirteDocline()
{
	//ifstream ofstream  https://blog.csdn.net/kingstar158/article/details/6859379/ 
	ofstream ofs(_F_STOCK);//输出方式打开文件

	if (ls.size() > 0)	//商品链表有内容才执行
	{
		ofs << "商品ID|商品名称|商品价格|库存" << endl; //写入表头

		//通过迭代器取出链表内容，写入文件，以“|”分隔，结尾加换行
		for (list<msg>::iterator it = ls.begin(); it != ls.end(); it++)
		{
			ofs << it->id << "|";		
			ofs << it->name << "|";
			ofs << it->price << "|";
			ofs << it->num << endl;
		}
	}

	ofs.close();//关闭文件
}

//添加新商品
//name:商品名称，num：库存，price：价格
void CInfoFile::Addline(CString name, int num, int price)
{
	msg tmp;

	if (ls.size() > 0)
	{
		//商品名称，库存，价格有效
		if (!name.IsEmpty() && num > 0 && price > 0)
		{
			tmp.id = ls.size() + 1;	//id自动加1
			CStringA str;
			str = name;	//CString转CStirngA
			tmp.name = str.GetBuffer(); //CStirngA转char *，商品名称
			tmp.num = num;	//库存
			tmp.price = price;	//价格

			ls.push_back(tmp);	//放在链表的后面
		}
	}
}


--  D:\project_c++\SaleSystem\SaleSystem\login.ini

斧头帮帮主
1

-- D:\project_c++\SaleSystem\SaleSystem\stock.txt

商品ID|商品名称|商品价格|库存
1|商品1|123|440
2|商品2|1123|555
3|商品3|1333|541
4|商品4|144423|547
5|商品5|14423|555
6|商品6|1123|554
7|商品7|1223|544
8|商品8|1233|555
9|商品9|1234|554
10|商品10|1523|555
11|商品11|5123|555
12|商品12|133|333
13|商品13|444|444
14|商品14|1111|111
15|测试|10|8




 -- CDataExchange https://blog.csdn.net/frankiewang008/article/details/36439547


-- D:\project_c++\SaleSystem\SaleSystem\MainFrm.h

 #include "InfoFile.h"

 
  -- D:\project_c++\SaleSystem\SaleSystem\MainFrm.cpp
  

  
int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	//设置图标，IDI_ICON_WIN为图标资源ID，此为WINAPI函数
	SetClassLong(m_hWnd, GCL_HICON, (LONG)AfxGetApp()->LoadIconW(IDI_ICON_WIN));

	//设置标题 右侧标题
	SetTitle(TEXT("2017/3/12"));

	//设置窗口大小
	MoveWindow(0, 0, 800, 500);

	//设置居中显示
	CenterWindow();

	//测试CInfoFile类
	CInfoFile file;
	CString name;
	CString pwd;
	file.ReadLogin(name, pwd);

	MessageBox(name);
	MessageBox(pwd);

	//file.WritePwd("斧头帮帮主", "123");

	return 0;
}


-- 03_登陆功能实现 

  CLR20r3  devenv.exe           http://blog.sina.com.cn/s/blog_3f2ef11801013p8c.html 

 步骤1：开始-->所有程序-->Microsoft Visual Studio 2012-->Visual Studio Tools-->VS2012 开发人员命令提示（以管理员方式运行）
步骤2：运行devenv /Safemode （本人的已经能正常运行了）


VS2010 CLR20r3 devenv.exe 错误的解决   https://group.cnblogs.com/topic/55159.html 

 最近我的vs2010经常过段时间就报CLR20r3错误的解决，出现这个异常我的vs2010就要重启，很是烦人，这么搞没法干活也。

搜索了下问题，这个异常是.net遇到了不能捕获的异常而出现的问题，但我出现这个异常后vs2010还是能正常编辑，故此想，出现异常不抛出来就可以了。

修改 devenv.exe.config。

在 <runtime>配置下增加
<legacyUnhandledExceptionPolicy enabled="true" />

这样遇到没法捕获的异常也不会弹出对话框让你重启了，虽然不是根本上解决问题，但至少不影响使用了，发帖分享。



        C:\Program Files (x86)\Microsoft Visual Studio 10.0\Common7\IDE\devenv.exe.config 


--   VS2010运行出错，devenv.exe    http://blog.sina.com.cn/s/blog_70441c8e0101oa9c.html 


在win7中运行VS32010，刚开始运行没问题，后来出现新建或者打开项目错误的问题，经过一下努力：
1. 重装VS2010；开始有效果，但没多久又出现问题
2. 修复系统补丁；没效果
报的错误，是devenv.exe kernel32.dll,
最后还是在网上找到了解决方法：
在cmd中输入初始化VS2010命令：
devenv /resetsettings
或者
devenv.exe /resetuserdata
或者
工具-> 导入和导出工具->重置所有设置




  新建对话框 ：    DIALOG_LOGIN  ， 右键添加类 ： CLoginDlg  


用户名 编辑区关联 CString m_user, 密码登陆框关联 CString m_pwd 。



--  D:\project_c++\SaleSystem\SaleSystem\SaleSystem.cpp

#include "LoginDlg.h"



BOOL CSaleSystemApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	//创建登录窗口 模态
	CLoginDlg dlg;
	dlg.DoModal();


	CWinApp::InitInstance();


}


-- d:\project_c++\SaleSystem\SaleSystem\LoginDlg.cpp 

#include "InfoFile.h"

//CView CFrameWnd   https://zhidao.baidu.com/question/520393348.html 
void CLoginDlg::OnBnClickedButton1()
{
	// TODO:  在此添加控件通知处理程序代码
	//登陆按钮点击事件

	UpdateData(TRUE); 

	if (m_user.IsEmpty() || m_pwd.IsEmpty())
	{
		MessageBox(TEXT("输入内容不能为空"));
		return;
	}

	//获取正确的值
	CInfoFile file;
	CString name, pwd;
	file.ReadLogin(name, pwd);

	if (name == m_user) //用户名一致
	{
		if (pwd == m_pwd) //密码一致
		{
			//关闭当前对话框
			CDialog::OnCancel();
		}
		else
		{
			MessageBox(TEXT("密码有误"));
		}
	}
	else
	{
		MessageBox(TEXT("用户名有误"));
	}
}


BOOL CLoginDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	// 默认登陆信息
	CInfoFile file;
	CString name, pwd;
	file.ReadLogin(name, pwd);

	m_user = name;
	m_pwd = pwd;
	//  UpdateData(TRUE)和UpdateData(FALSE)  https://blog.csdn.net/thisispan/article/details/7410729 
	//同步到控件中
	UpdateData(FALSE); // 将控件的关联变量的值传给控件并改变控件状态

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}



void CLoginDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	exit(0);
}


void CLoginDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialogEx::OnOK();
}


void CLoginDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	//CDialogEx::OnClose();
	exit(0);// 退出程序 不是单纯退出当前对话框就完了
}


  UpdateData(TRUE)和UpdateData(FALSE)的区别  https://blog.csdn.net/thisispan/article/details/7410729 

当你使用了ClassWizard建立了控件和变量之间的联系后：当你修改了变量的值，而希望对话框控件更新显示，就应该在修改变量后调用UpdateData(FALSE)；如果你希望知道用户在对话框中到底输入了什么，就应该在访问变量前调用UpdateData(TRUE)。 


-- 04_静态拆分窗口 
 

   添加mfc类 ：  CSelectView   ，基类选择： CTreeView 
   添加mfc类 ：  CDisplayView   ，基类选择：  CFormView
 
 
 -- D:\project_c#\SaleSystem1\SaleSystem1\MainFrm.h
 
 private:
	CSplitterWnd m_spliter; // 切分窗口类对象
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
 
 
 -- D:\project_c#\SaleSystem1\SaleSystem1\MainFrm.cpp
 
 #include "InfoFile.h"
#include "SelectView.h"
 #include "DisplayView.h"
 
 
BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO:  在此添加专用代码和/或调用基类

	//return CFrameWnd::OnCreateClient(lpcs, pContext);

	//拆成1行两列
	m_spliter.CreateStatic(this, 1, 2);

	//左侧和右侧具体的显示内容
	m_spliter.CreateView(0, 0, RUNTIME_CLASS(CSelectView), CSize(200, 500), pContext);
	m_spliter.CreateView(0, 1, RUNTIME_CLASS(CDisplayView), CSize(600, 500), pContext);

	return TRUE; //自己拆分
}

 


-- 05_树视图功能

-- D:\project_c#\SaleSystem1\SaleSystem1\SelectView.h

 	private:
	CTreeCtrl *m_treeCtrl;	//树控件
	CImageList m_imageList;	//图标列表



--  D:\project_c#\SaleSystem1\SaleSystem1\SelectView.cpp


void CSelectView::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();

	//初始化 树视图
	//获取树控件
	m_treeCtrl = &GetTreeCtrl();

	//1、准备图片集合

	HICON icon = AfxGetApp()->LoadIconW(IDI_ICON_RE);

	m_imageList.Create(30, 30, ILC_COLOR32, 1, 1);
	m_imageList.Add(icon);

	m_treeCtrl->SetImageList(&m_imageList, TVSIL_NORMAL);

	//2、添加节点
	m_treeCtrl->InsertItem(TEXT("个人信息"), 0, 0, NULL);
	m_treeCtrl->InsertItem(TEXT("销售管理"), 0, 0, NULL);
	m_treeCtrl->InsertItem(TEXT("库存信息"), 0, 0, NULL);
	m_treeCtrl->InsertItem(TEXT("库存添加"), 0, 0, NULL);
	m_treeCtrl->InsertItem(TEXT("库存删除"), 0, 0, NULL);




	// TODO:  在此添加专用代码和/或调用基类
}



void CSelectView::OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	*pResult = 0;

	//获取当前选中项

	HTREEITEM item = m_treeCtrl->GetSelectedItem();
	//通过选中的项 获取这个项中的内容
	CString str = m_treeCtrl->GetItemText(item);

	MessageBox(str);

	

}



-- 06_个人信息界面搭建 


 添加对话框资源(ID修改为 DIALOG_USER )  在窗口属性中，Border改为None，Style改为Child：


选中对话框 -> 右击 -> 添加类 -> 类名： CUserDlg ，基类选择 CFormView


身份 编辑区关联CString m_user  ， 用户名 编辑框关联CString m_name ，
新密码 编辑框关联CString m_newPwd  ， 确定密码 编辑框关联CString m_surePwd 。



-- 07_自定义消息以及界面挂载 


-- D:\project_c#\SaleSystem1\SaleSystem1\SelectView.cpp


void CSelectView::OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	*pResult = 0;

	//获取当前选中项

	HTREEITEM item = m_treeCtrl->GetSelectedItem();
	//通过选中的项 获取这个项中的内容
	CString str = m_treeCtrl->GetItemText(item);

	//MessageBox(str);

	if (str == TEXT("个人信息"))
	{
		//需要包含框架类头文件#include "MainFrm.h" 
		//CWnd::PostMessage 将一个消息放入窗口的消息队列
		//AfxGetMainWnd()：框架窗口对象的指针
		//AfxGetMainWnd()->GetSafeHwnd()：获取返回窗口的句柄，CWnd::GetSafeHwnd
		//NM_A：发送自定义消息
		//(WPARAM)NM_A：指定了附加的消息信息
		//(LPARAM)0：指定了附加的消息信息，此参数这里没有意义
		::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_A, (WPARAM)NM_A, (LPARAM)0);
	}
	else if (str == TEXT("销售管理"))
	{
		::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_B, (WPARAM)NM_B, (LPARAM)0);
	}
	else if (str == TEXT("库存信息"))
	{
		::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_C, (WPARAM)NM_C, (LPARAM)0);
	}
	else if (str == TEXT("库存添加"))
	{
		::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_D, (WPARAM)NM_D, (LPARAM)0);
	}
	else if (str == TEXT("库存删除"))
	{
		::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_E, (WPARAM)NM_E, (LPARAM)0);
	}
	

}



--  D:\project_c#\SaleSystem1\SaleSystem1\MainFrm.h

//自定义消息
#define NM_A	(WM_USER + 100)
#define NM_B	(WM_USER + 101)
#define NM_C	(WM_USER + 102)
#define NM_D	(WM_USER + 103)
#define NM_E	(WM_USER + 104)


 private:

	afx_msg LRESULT OnMyChange(WPARAM wParam, LPARAM lParam);


-- D:\project_c#\SaleSystem1\SaleSystem1\MainFrm.cpp

#include "MainFrm.h"
 #include "InfoFile.h"
#include "SelectView.h"
#include "DisplayView.h"
#include "UserDlg.h"

LRESULT CMainFrame::OnMyChange(WPARAM wParam, LPARAM lParam)
{
	CCreateContext   Context;
	if (wParam == NM_A)
	{
		//MessageBox(TEXT("个人信息界面挂载！"));
		//挂载界面
		Context.m_pNewViewClass = RUNTIME_CLASS(CUserDlg);
		Context.m_pCurrentFrame = this;
		Context.m_pLastView = (CFormView *)m_spliter.GetPane(0, 1);
		m_spliter.DeleteView(0, 1);
		m_spliter.CreateView(0, 1, RUNTIME_CLASS(CUserDlg), CSize(600, 500), &Context);
		CUserDlg *pNewView = (CUserDlg *)m_spliter.GetPane(0, 1);
		m_spliter.RecalcLayout();
		pNewView->OnInitialUpdate();
		m_spliter.SetActivePane(0, 1);
	}
	else if (wParam == NM_B)
	{
		//MessageBox(TEXT("销售管理界面挂载！"));
		/*Context.m_pNewViewClass = RUNTIME_CLASS(CSellDlg);
		Context.m_pCurrentFrame = this;
		Context.m_pLastView = (CFormView *)m_spliter.GetPane(0, 1);
		m_spliter.DeleteView(0, 1);
		m_spliter.CreateView(0, 1, RUNTIME_CLASS(CSellDlg), CSize(600, 500), &Context);
		CSellDlg *pNewView = (CSellDlg *)m_spliter.GetPane(0, 1);
		m_spliter.RecalcLayout();
		pNewView->OnInitialUpdate();
		m_spliter.SetActivePane(0, 1);*/
	}
	else if (wParam == NM_D)
	{
		
	/*	Context.m_pNewViewClass = RUNTIME_CLASS(CAddDlg);
		Context.m_pCurrentFrame = this;
		Context.m_pLastView = (CFormView *)m_spliter.GetPane(0, 1);
		m_spliter.DeleteView(0, 1);
		m_spliter.CreateView(0, 1, RUNTIME_CLASS(CAddDlg), CSize(600, 500), &Context);
		CAddDlg *pNewView = (CAddDlg *)m_spliter.GetPane(0, 1);
		m_spliter.RecalcLayout();
		pNewView->OnInitialUpdate();
		m_spliter.SetActivePane(0, 1);*/
	}
	return 0;
}


-- 08_个人信息功能完善 


-- D:\project_c#\SaleSystem1\SaleSystem1\UserDlg.cpp

#include "InfoFile.h"
 
void CUserDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	//初始化
	m_user = TEXT("销售员");

	CInfoFile file;
	CString name, pwd;
	file.ReadLogin(name, pwd);

	m_name = name;

	UpdateData(FALSE);

	// TODO:  在此添加专用代码和/或调用基类

}


void CUserDlg::OnBnClickedButton1()
{
	// TODO:  在此添加控件通知处理程序代码
	//修改密码功能

	UpdateData(TRUE); //拿到最新值

	if (m_newPwd.IsEmpty() || m_surePwd.IsEmpty())
	{
		MessageBox(TEXT("输入内容不能为空！"));
		return;
	}

	//新密码和确定密码要一致
	if (m_newPwd != m_surePwd)
	{
		MessageBox(TEXT("新密码与确定密码要一致！"));
		return;
	}

	//新密码与旧密码不能一致
	CInfoFile file;
	CString name, pwd;
	file.ReadLogin(name, pwd);
	if (pwd == m_newPwd)
	{
		MessageBox(TEXT("新密码与旧密码不能一致！"));
		return;
	}

	//CString 转  char *
	CStringA tmp;
	CStringA tmp2;
	tmp = name;
	tmp2 = m_newPwd;
	file.WritePwd(tmp.GetBuffer(), tmp2.GetBuffer());
	MessageBox(TEXT("修改成功"));

	//清空内容
	m_newPwd.Empty();
	m_surePwd.Empty();
	UpdateData(FALSE);
}





-- 09_销售管理功能实现 


 添加对话框资源(ID修改为 DIALOG_SELL )，添加所需控件。
在窗口属性中，Border改为None，Style改为Child：


选中对话框 -> 右击 -> 添加类 -> 类名： CSellDlg ，基类选择   CFormView



商品名组合框关联 CComboBox  m_combo ，单价编辑框关联int  m_price ，

  库存 ： m_left
 个数编辑框关联 int m_num ，销售信息编辑框关联CString  m_sellInfo 。



 
MFC消息映射BEGIN_MESSAGE_MAP详解   https://blog.csdn.net/luoti784600/article/details/10070939
 
 
 
 
--  D:\project_c#\SaleSystem1\SaleSystem1\SellDlg.cpp
 
 #include "InfoFile.h"


void CSellDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO:  在此添加专用代码和/或调用基类
	//初始化消息订单窗口

	//初始化下拉框
	
	CInfoFile file;
	//把商品读到file对象中
	file.ReadDocline();

	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{
		//遍历商品容器  把容器名称放到下拉框中

		//it->name 是 string  AddString(CString )
		// string  -> CString

		m_combo.AddString(CString(it->name.c_str()));
	}

	//默认选中第一个商品
	m_combo.SetCurSel(0);

	OnCbnSelchangeCombo1();//更新第一个商品里的数据

}



void CSellDlg::OnCbnSelchangeCombo1()
{
	// TODO:  在此添加控件通知处理程序代码
	//切换商品 触发的事件


	//先获取到商品的名称

	int index = m_combo.GetCurSel();
	//根据索引获取到具体内容
	CString name;
	m_combo.GetLBText(index, name);

	//根据商品名称获取到该商品的价格和库存 并且显示到控件中
	CInfoFile file;
	file.ReadDocline();
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{
		if ((CString)it->name.c_str() == name)
		{
			m_price = it->price;
			m_num = it->num; // old : m_left = it->num; 
			//同步到控件上
			UpdateData(FALSE);
		}
	}

}


void CSellDlg::OnCbnSelchangeCombo2()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CSellDlg::OnBnClickedButton1()
{
	UpdateData(TRUE);
	// TODO:  在此添加控件通知处理程序代码
	//购买的功能实现
	if (m_num <= 0)
	{
		MessageBox(TEXT("购买数量要大于0"));
		return;
	}
	//购买的数量 不能大于库存
	if (m_num > m_left)
	{
		MessageBox(TEXT("购买数量不能大于库存量"));
		return;
	}

	//购买
	//获取到具体要买的商品名称
	int index = m_combo.GetCurSel();
	CString name;
	m_combo.GetLBText(index, name);

	CInfoFile file;
	file.ReadDocline();
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{
		if ( (CString)it->name.c_str() == name)
		{
			//同步库存量
			it->num -= m_num;
			m_left = it->num; //控件上的库存量
			//告诉用户具体的购买信息

			CString str;
			str.Format(_T("商品：%s \r\n单价：%d \r\n个数：%d \r\n总价：%d"), name, m_price, m_num, m_price*m_num);
			m_sellInfo = str;
			UpdateData(FALSE);
			MessageBox(TEXT("购买成功"));
		}
	}
	
	//把最新的数据写到文件中
	file.WirteDocline();

	//清空数据
	m_num = 0;
	m_sellInfo.Empty();
	UpdateData(FALSE);

}

 
 
 
 --  10_添加商品个数功能实现
 
 
  添加对话框 ： DIALOG_ADD  , 添加类 ： CAddDlg  
 
 
 // AddDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SaleSystem.h"
#include "AddDlg.h"
#include "InfoFile.h"

// CAddDlg

IMPLEMENT_DYNCREATE(CAddDlg, CFormView)

CAddDlg::CAddDlg()
	: CFormView(CAddDlg::IDD)
	, m_price1(0)
	, m_num1(0)
	, m_name2(_T(""))
	, m_price2(0)
	, m_num2(0)
{

}

CAddDlg::~CAddDlg()
{
}

void CAddDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_combo);
	DDX_Text(pDX, IDC_EDIT1, m_price1);
	DDX_Text(pDX, IDC_EDIT2, m_num1);
	DDX_Text(pDX, IDC_EDIT5, m_name2);
	DDX_Text(pDX, IDC_EDIT6, m_price2);
	DDX_Text(pDX, IDC_EDIT7, m_num2);
}

BEGIN_MESSAGE_MAP(CAddDlg, CFormView)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CAddDlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON3, &CAddDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CAddDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CAddDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CAddDlg::OnBnClickedButton6)
END_MESSAGE_MAP()


// CAddDlg 诊断

#ifdef _DEBUG
void CAddDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CAddDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CAddDlg 消息处理程序


void CAddDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	CInfoFile file;
	//把商品读到file对象中
	file.ReadDocline();

	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{
		//遍历商品容器  把容器名称放到下拉框中

		//it->name 是 string  AddString(CString )
		// string  -> CString

		m_combo.AddString(CString(it->name.c_str()));
	}

	//默认选中第一个商品
	m_combo.SetCurSel(0);

	OnCbnSelchangeCombo1();//更新第一个商品里的数据

	// TODO:  在此添加专用代码和/或调用基类
}


void CAddDlg::OnCbnSelchangeCombo1()
{
	// TODO:  在此添加控件通知处理程序代码
	//先获取到商品的名称

	int index = m_combo.GetCurSel();
	//根据索引获取到具体内容
	CString name;
	m_combo.GetLBText(index, name);

	//根据商品名称获取到该商品的价格和库存 并且显示到控件中
	CInfoFile file;
	file.ReadDocline();
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{
		if ((CString)it->name.c_str() == name)
		{
			m_price1 = it->price;
			//同步到控件上
			UpdateData(FALSE);
		}
	}

}


void CAddDlg::OnBnClickedButton3()
{
	// TODO:  在此添加控件通知处理程序代码

	//添加商品按钮功能实现
	//拿到最新数据
	UpdateData(TRUE);

	if (m_num1 <= 0)
	{
		MessageBox(TEXT("添加的数量要大于0"));
		return;
	}


	//获取到你要添加的商品名称
	int index = m_combo.GetCurSel();
	CString name;
	m_combo.GetLBText(index, name);
	CInfoFile file;
	file.ReadDocline();
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{
		if (CString(it->name.c_str()) == name)
		{
			//添加库存
			it->num += m_num1;
			m_num1 = 0;
			UpdateData(FALSE);
			MessageBox(TEXT("添加成功"));

		}

	}
	//把商品同步到文件
	file.WirteDocline();




}


void CAddDlg::OnBnClickedButton4()
{
	// TODO:  在此添加控件通知处理程序代码
	m_num1 = 0;
	UpdateData(FALSE);
	m_combo.SetCurSel(0);
	OnCbnSelchangeCombo1();
}


void CAddDlg::OnBnClickedButton5()
{
	//拿到最新的数据
	UpdateData(TRUE);

	// TODO:  在此添加控件通知处理程序代码
	//添加新商品
	//验证数据的有效性
	if (m_name2.IsEmpty() || m_num2 <= 0 || m_price2 <= 0)
	{
		MessageBox(TEXT("输入信息有误"));
		return;
	}

	CInfoFile file;
	file.ReadDocline();

	file.Addline(m_name2, m_num2, m_price2);
	file.WirteDocline();
	MessageBox(TEXT("新商品添加成功"));


	//同步左侧下拉框中
	m_combo.InsertString(0, m_name2);
	m_combo.SetCurSel(0);
	OnCbnSelchangeCombo1();

	//清空添加的新数据
	m_name2.Empty();
	m_num2 = 0; 
	m_price2 = 0;
	UpdateData(FALSE);


}


void CAddDlg::OnBnClickedButton6()
{
	// TODO:  在此添加控件通知处理程序代码
	//取消添加新商品按钮事件
	//清空添加的新数据
	m_name2.Empty();
	m_num2 = 0;
	m_price2 = 0;
	UpdateData(FALSE);
}

 
 
 
 -- 11_添加新商品 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 -- tagINITCOMMONCONTROLSEX  https://blog.csdn.net/evkj2013/article/details/43600977 


 
 
 
 
 
 
 
 
 
 
 
 
 
 

