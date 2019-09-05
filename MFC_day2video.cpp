
-- 02_模态对话框

  创建 MFC应用程序 ： DialogTest   
  

  
 -- d:\project_c++\DialogTest\DialogTest\DialogTestDlg.cpp 
  
    创建对话框 ：　　CDlgExec
  
#include "DlgExec.h"


void CDialogTestDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CDlgExec dlg;
	dlg.DoModal();

}


-- 03_非模态对话框 

创建对话框 　　　　CDlgShow

-- d:\project_c++\DialogTest\DialogTest\DialogTestDlg.cpp

#include "DlgShow.h"

void CDialogTestDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	CDlgShow dlg;
	dlg.Create(IDD_SHOW);
	dlg.ShowWindow(SW_SHOWNORMAL);

}




-- 04_静态文本控件 


　无法将成员变量添加到ID为 的控件中　　　https://blog.csdn.net/i_likechard/article/details/52766407　
　　
右键你需要添加变量的控件。在其属性框中有 ID 项。在其ID后添加数字。如：以static控件为例。 更改前为：IDC_STATIC   改为 IDC_STATIC1即可。 也可以将其改为其他合理的名字。目的只是将其ID修改成不是VS默认给予的ID。




　-- d:\project_c++\02 CStaticTest\02 CStaticTest\02 CStaticTestDlg.cpp 




void CMy02CStaticTestDlg::OnBnClickedButton1() 
{
	// TODO: 在此添加控件通知处理程序代码
	m_txt.SetWindowTextW(TEXT("wocao"));  // m_txt 是 static text 添加变量
}


void CMy02CStaticTestDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;

	m_txt.GetWindowTextW(str);
	 MessageBox(str);
}


void CMy02CStaticTestDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	m_button.SetWindowTextW(TEXT("xixi"));
	//获取内容
	CString str;
	m_button.GetWindowTextW(str);
	 MessageBox(str);
	  m_button.EnableWindow(FALSE); //禁用
}



// CMy02CStaticTestDlg 消息处理程序

BOOL CMy02CStaticTestDlg::OnInitDialog()
{
	
	// TODO: 在此添加额外的初始化代码


	//用static_Text显示图片

	//设置静态控件窗口风格为位图居中显示
	m_pic.ModifyStyle(0xf, SS_BITMAP | SS_CENTERIMAGE);

	//通过路径获取bitmap句柄
#define HBMP(filepath,width,height) (HBITMAP)LoadImage(AfxGetInstanceHandle(),filepath,IMAGE_BITMAP,width,height,LR_LOADFROMFILE|LR_CREATEDIBSECTION)

	//宽高设置 应该按照 控件的大小取设置
	CRect rect;
	m_pic.GetWindowRect(rect);            // m_pic 是 static text 添加变量 

	//静态控件设置bitmap
	m_pic.SetBitmap(HBMP(TEXT("./1.bmp"), rect.Width(), rect.Height()));



	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}



--     05_编辑框使用1 

-- d:\project_c++\02 CStaticTest\03 EditCtrl\03 EditCtrlDlg.cpp

// CMy03EditCtrlDlg 消息处理程序

BOOL CMy03EditCtrlDlg::OnInitDialog()
{
	
	// TODO: 在此添加额外的初始化代码

	m_edit1.SetWindowTextW(TEXT("xx"));


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}
 

void CMy03EditCtrlDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码

	//exit(); //退出程序
	CDialog:OnOK();//退出当前对话框
}


void CMy03EditCtrlDlg::OnOK()   //重写 
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialogEx::OnOK();
}


-- 06_编辑框使用2 



void CMy03EditCtrlDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码

	//利用关联 value 方式 ，设置和改变 edit 内容

	// 设置内容
	m_txt1=TEXT("hehe");  //  m_txt1 是  edit control  添加变量 ， 类别 ： value  ,变量类型 ： CString 
	//将变量同步到控件中
	UpdateData(FALSE);
}


void CMy03EditCtrlDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	MessageBox(m_txt1);

}



-- 07_下拉框使用 


4.1属性中加入数据 data   ;进行分割
4.2默认排序 sort 修改false 不排序了
4.3type 类型 DropList 不可以编辑

-- d:\project_c++\02 CStaticTest\04 ComboxCtrl\04 ComboxCtrlDlg.cpp 
 
BOOL CMy04ComboxCtrlDlg::OnInitDialog()
{
	
	// TODO: 在此添加额外的初始化代码

	m_conbox.AddString(TEXT("tangsheng"));	
	m_conbox.AddString(TEXT("tangsheng1"));	
	m_conbox.AddString(TEXT("tangsheng2"));	
	m_conbox.AddString(TEXT("tangsheng3"));	

	//设置默认选项
	m_conbox.SetCurSel(2); //索引

	m_conbox.InsertString(3,TEXT("bailongma"));
	//m_conbox.DeleteString(2);//删除

	//获取索引具体类容
	CString str;
	m_conbox.GetLBText(1,str);
	MessageBox(str);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}
 

-- d:\project_c++\02 CStaticTest\04 ComboxCtrl\04 ComboxCtrlDlg.cpp

void CMy04ComboxCtrlDlg::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码

	//拿到索引的位置
 int index=	m_conbox.GetCurSel();
 CString str;
 m_conbox.GetLBText(index,str);
 MessageBox(str);
}




-- 08_列表控件 


 5.1view  报表模式 Report
5.2添加表头 InsertCol
5.3添加正文 从0索引
5.4添加第一行第一列 InsertItem(0, “张三”);
5.5添加第一行的其他列  setItemText( 行，列，具体内容)
5.6设置风格  整行选中 网格显示
5.7m_list.SetExtendedStyle(m_list.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);



  CListCtrl::SetExtendedStyle


-- D:\project_c++\02 CStaticTest\05 ListCtrl\05 ListCtrlDlg.cpp

// CMy05ListCtrlDlg 消息处理程序

BOOL CMy05ListCtrlDlg::OnInitDialog()
{
	// TODO: 在此添加额外的初始化代码
	CString str[]={TEXT("name"),TEXT("sex"),TEXT("age")};
	for(int i=0;i<3;i++)
	{
		//设置表头
		m_list.InsertColumn(i,str[i], LVCFMT_LEFT,100 );
	}
	//索引从0开始
	m_list.InsertItem(0,TEXT("zhangsan"));
	m_list.SetItemText(0,1,TEXT("nan"));
	m_list.SetItemText(0,2,TEXT("12"));

	int j;
	for(int i=0;i<10;i++)
	{
		j=0;
		CString name;
		name.Format(TEXT("xuyitao_%d"),1);
		m_list.InsertItem(i,name);

		m_list.SetItemText(i,++j,TEXT("nan"));
		m_list.SetItemText(i,++j,TEXT("56"));

	}
	//设置属性 整行选中 https://blog.csdn.net/holandstone/article/details/7473198
	m_list.SetExtendedStyle(m_list.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}



--  09_树控件使用

6.1设置属性  设置线、按钮
6.2设置图片集合
6.2.1setImageList（CImageList* list , 正常显示的宏）
6.2.1.1list准备  create(30,30, 32位色，4,4)
6.2.1.2add （HICON）
6.3添加节点
6.3.1InsertItem( 节点名称，显示图片，选中后显示的图，父节点)
6.4设置默认节点
6.4.1selectItem
6.5节点间切换 触发事件OnTvnSelchangedTree1
6.5.1获取当前项  item =  getSelectItem
6.5.2CString str =  getItemText(item)

 
 



-- d:\project_c++\02 CStaticTest\06 TreeCtrl\06 TreeCtrlDlg.cpp 

BOOL CMy06TreeCtrlDlg::OnInitDialog()
{
	
	// TODO: 在此添加额外的初始化代码
	//树控件使用

	//1 、设置图标

	//准备HICON图标
	HICON icons[4];
	icons[0] = AfxGetApp()->LoadIconW(IDI_ICON1);
	icons[1] = AfxGetApp()->LoadIconW(IDI_ICON2);
	icons[2] = AfxGetApp()->LoadIconW(IDI_ICON3);
	icons[3] = AfxGetApp()->LoadIconW(IDI_ICON4);

	// CImageList list; //必须保存住这个集合 写到.h做成员属性

	//创建图片集合
	list.Create(30, 30, ILC_COLOR32, 4, 4);
	//添加具体的图片
	for (int i = 0; i < 4;i++)
	{
		list.Add(icons[i]);
	}
	m_tree.SetImageList(&list, TVSIL_NORMAL);


	//2 、设置节点
	HTREEITEM root = m_tree.InsertItem(TEXT("根节点"), 0, 0, NULL);
	HTREEITEM parent = m_tree.InsertItem(TEXT("父节点"), 1, 1, root);
	HTREEITEM sub1 = m_tree.InsertItem(TEXT("子节点1"), 2, 2, parent);
	HTREEITEM sub2 = m_tree.InsertItem(TEXT("子节点2"), 3, 3, parent);

	//设置默认选项
	m_tree.SelectItem(sub1);


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMy06TreeCtrlDlg::OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	HTREEITEM item= m_tree.GetSelectedItem();
	CString str= m_tree.GetItemText(item);
	MessageBox(str);
}



-- D:\project_c++\02 CStaticTest\06 TreeCtrl\06 TreeCtrlDlg.h 

public:
	CTreeCtrl m_tree;

	CImageList list;





--  10_标签页的使用 



--  D:\project_c++\02 CStaticTest\07 CTabCtrl\TabSheet.h 
 
#if !defined(AFX_TABSHEET_H__42EE262D_D15F_46D5_8F26_28FD049E99F4__INCLUDED_)
#define AFX_TABSHEET_H__42EE262D_D15F_46D5_8F26_28FD049E99F4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TabSheet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTabSheet window
#define MAXPAGE 16

class CTabSheet : public CTabCtrl
{
	// Construction
public:
	CTabSheet();
	
	// Attributes
public:
	
	// Operations
public:
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTabSheet)
	//}}AFX_VIRTUAL
	
	// Implementation
public:
	int GetCurSel();
	int SetCurSel(int nItem);
	void Show();
	void SetRect();
	BOOL AddPage(LPCTSTR title, CDialog *pDialog, UINT ID);
	virtual ~CTabSheet();
	
	// Generated message map functions
protected:
	LPCTSTR m_Title[MAXPAGE];
	UINT m_IDD[MAXPAGE];
	CDialog* m_pPages[MAXPAGE];
	int m_nNumOfPages;
	int m_nCurrentPage;
	//{{AFX_MSG(CTabSheet)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
	
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TABSHEET_H__42EE262D_D15F_46D5_8F26_28FD049E99F4__INCLUDED_)



--  D:\project_c++\02 CStaticTest\07 CTabCtrl\07 CTabCtrlDlg.cpp

// 07 CTabCtrlDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "07 CTabCtrl.h"
#include "07 CTabCtrlDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMy07CTabCtrlDlg 对话框




CMy07CTabCtrlDlg::CMy07CTabCtrlDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMy07CTabCtrlDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy07CTabCtrlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMy07CTabCtrlDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// CMy07CTabCtrlDlg 消息处理程序

BOOL CMy07CTabCtrlDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMy07CTabCtrlDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMy07CTabCtrlDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMy07CTabCtrlDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



-- D:\project_c++\02 CStaticTest\07 CTabCtrl\07 CTabCtrlDlg.h

#include "Dlg1.h"
#include "Dlg2.h"


private:
	CTabSheet m_tab;

	CDlg1 dlg1;
	CDlg2 dlg2;


--   D:\project_c++\02 CStaticTest\07 CTabCtrl\07 CTabCtrlDlg.cpp 
 
#include "Dlg1.h"
#include "Dlg2.h"


// CMy07CTabCtrlDlg 消息处理程序

BOOL CMy07CTabCtrlDlg::OnInitDialog()
{
	
	// TODO: 在此添加额外的初始化代码

	m_tab.AddPage(TEXT("系统设置"),&dlg1,IDD_DIALOG1);
	m_tab.AddPage(TEXT("系统设置ee"),&dlg2,IDD_DIALOG2);

	m_tab.Show();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}



--  






















