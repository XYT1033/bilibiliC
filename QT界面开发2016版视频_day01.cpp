
 Qt资料大全   https://blog.csdn.net/liang19890820/article/details/51752029 

  
 Qt4及Qt5的下载与安装   https://www.cnblogs.com/lxmwb/archive/2017/01/26/6352220.html
 


-- 04_QT应用程序框架meiyong

--   05_项目文件 

--  06_第一个QT程序
 
 -- 07_指定父对象 
 
 
 --  D:\project_c++\qt001\03\mainwidget.cpp
 
 #include <QApplication>
#include <QWidget> //窗口控件基类
#include <QPushButton>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    QWidget w;
    w.setWindowTitle(QString("主要看气质")); //设置标题

    /*如果不指定父对象，对象和对象（窗口和窗口）没有关系，独立
     * a指定b为它的父对象，a放在b的上面
     * 指定父对象，有2种方式：
     *            1）setParent
     *            2）通过构造函数传参
     * 指定父对象，只需要父对象显示，上面的子对象自动显示
     */

    QPushButton b;
    b.setText("^_^"); //给按钮设置内容
    b.setParent(&w); //指定父对象
    b.move(100, 100); //移动坐标

    QPushButton b1(&w); //通过构造函数传参
    b1.setText("abc");

    w.show();

    app.exec();
    return 0;
}


-- 08_标准信号和槽 

--  D:\project_c++\qt001\03\mainwidget.h

#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QPushButton>


class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = 0);
    ~MainWidget();

private:
    QPushButton b1;
    QPushButton *b2;

};

#endif // MAINWIDGET_H


--  D:\project_c++\qt001\03\mainwidget.cpp

#include "mainwidget.h"
#include <QPushButton>
#include <QDebug> //打印

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{
    b1.setParent(this);
    b1.setText("close");
    b1.move(100, 100);

    b2 = new QPushButton(this);
    b2->setText("abc");

    connect(&b1, &QPushButton::pressed, this, &MainWidget::close);
    /* &b1: 信号发出者，指针类型
     * &QPushButton::pressed：处理的信号，  &发送者的类名::信号名字
     * this: 信号接收者
     * &MainWidget::close： 槽函数，信号处理函数  &接收的类名::槽函数名字
    */

    /* 自定义槽，普通函数的用法
     * Qt5：任意的成员函数，普通全局函数，静态函数
     * 槽函数需要和信号一致（参数，返回值）
     * 由于信号都是没有返回值，所以，槽函数一定没有返回值
     */

    connect(b2, &QPushButton::released, &b1, &QPushButton::hide);

}

MainWidget::~MainWidget()
{

}


--  09_自定义槽函数

-- D:\project_c++\qt001\03\mainwidget.h


#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QPushButton>

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = 0);
    ~MainWidget();
public slots:
    void mySlot();

private:
    QPushButton b1;
    QPushButton *b2;

};

#endif // MAINWIDGET_H



--  D:\project_c++\qt001\03\mainwidget.cpp

#include "mainwidget.h"
#include <QPushButton>
#include <QDebug> //打印

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{
    b1.setParent(this);
    b1.setText("b1");
    b1.move(100, 100);

    b2 = new QPushButton(this);
    b2->setText("b2");

    /* 自定义槽，普通函数的用法
     * Qt5：任意的成员函数，普通全局函数，静态函数
     * 槽函数需要和信号一致（参数，返回值）
     * 由于信号都是没有返回值，所以，槽函数一定没有返回值
     */
    connect(b2, &QPushButton::released, this, &MainWidget::mySlot);
     connect(b2, &QPushButton::released, &b1, &QPushButton::hide);
}

void MainWidget::mySlot()
{
    b2->setText("b2xxxxxxxxxx");
}

MainWidget::~MainWidget()
{

}

--  10_两个独立的窗口

--  D:\project_c++\qt001\03\subwidget.h

#ifndef SUBWIDGET_H
#define SUBWIDGET_H

#include <QWidget>
#include <QPushButton>

class SubWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SubWidget(QWidget *parent = 0);

private:
    QPushButton b;
};

#endif // SUBWIDGET_H


--  D:\project_c++\qt001\03\subwidget.cpp

#include "subwidget.h"

SubWidget::SubWidget(QWidget *parent) : QWidget(parent)
{
    this->setWindowTitle("小弟");
    b.setParent(this);
    b.setText("切换到主窗口");

}

-- D:\project_c++\qt001\03\mainwidget.h

#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QPushButton>
#include "subwidget.h" //子窗口头文件

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = 0);
    ~MainWidget();

public slots:
   void changeWin();


private:
    QPushButton b1;
    QPushButton *b2;
    QPushButton b3;

    SubWidget subWin;
};

#endif // MAINWIDGET_H

-- D:\project_c++\qt001\03\mainwidget.cpp

#include "mainwidget.h"
#include <QPushButton>
#include <QDebug> //打印

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("老大");
    //this->setWindowTitle("老大");

    b3.setParent(this);
    b3.setText("切换到子窗口");
    b3.move(50, 50);

    //显示子窗口
    //subWin.show();

    connect(&b3, &QPushButton::released, this, &MainWidget::changeWin);

}

void MainWidget::changeWin()
{
    //子窗口显示
    subWin.show();
    //本窗口隐藏
    this->hide();
}

MainWidget::~MainWidget()
{

}

-- 11_自定义信号

-- D:\project_c++\qt001\03\subwidget.h

#ifndef SUBWIDGET_H
#define SUBWIDGET_H

#include <QWidget>
#include <QPushButton>

class SubWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SubWidget(QWidget *parent = 0);

    void sendSlot();

signals:
     /* 信号必须有signals关键字来声明
      * 信号没有返回值，但可以有参数
      * 信号就是函数的声明，只需声明，无需定义
      * 使用：emit mySignal();
      * 信号可以重载
     */

    void mySignal();
  

public slots:

private:
    QPushButton b;
};

#endif // SUBWIDGET_H



-- D:\project_c++\qt001\03\subwidget.cpp

#include "subwidget.h"

SubWidget::SubWidget(QWidget *parent) : QWidget(parent)
{
    this->setWindowTitle("小弟");
    b.setParent(this);
    b.setText("切换到主窗口");

    connect(&b, &QPushButton::clicked, this, &SubWidget::sendSlot);

    resize(400, 300);
}

void SubWidget::sendSlot()
{
    emit mySignal();
  
}


-- D:\project_c++\qt001\03\mainwidget.h

#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QPushButton>
#include "subwidget.h" //子窗口头文件

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = 0);
    ~MainWidget();

public slots:

    void changeWin();
    void dealSub();
    void dealSlot(int, QString);

private:

    QPushButton b3;

    SubWidget subWin;
};

#endif // MAINWIDGET_H


-- D:\project_c++\qt001\03\mainwidget.cpp

#include "mainwidget.h"
#include <QPushButton>
#include <QDebug> //打印

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{

    setWindowTitle("老大");
    //this->setWindowTitle("老大");

    b3.setParent(this);
    b3.setText("切换到子窗口");
    b3.move(50, 50);

    //显示子窗口
    //subWin.show();

    connect(&b3, &QPushButton::released, this, &MainWidget::changeWin);

    //处理子窗口的信号
    void (SubWidget::*funSignal)() = &SubWidget::mySignal;
    connect(&subWin, funSignal, this, &MainWidget::dealSub);

}

void MainWidget::dealSlot(int a, QString str)
{
    // str.toUtf8() -> 字节数组QByteArray
    // ……data()  -> QByteArray -> char *
    qDebug() << a << str.toUtf8().data();
}

void MainWidget::changeWin()
{
    //子窗口显示
    subWin.show();
    //本窗口隐藏
    this->hide();
}


void MainWidget::dealSub()
{
    //子窗口隐藏
    subWin.hide();
    //本窗口显示
    show();
}

MainWidget::~MainWidget()
{

}



-- 13_带参数的信号 

-- D:\project_c++\qt001\03\subwidget.h 

#ifndef SUBWIDGET_H
#define SUBWIDGET_H

#include <QWidget>
#include <QPushButton>

class SubWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SubWidget(QWidget *parent = 0);

    void sendSlot();

signals:
     /* 信号必须有signals关键字来声明
      * 信号没有返回值，但可以有参数
      * 信号就是函数的声明，只需声明，无需定义
      * 使用：emit mySignal();
      * 信号可以重载
     */

    void mySignal();
    void mySignal(int, QString);

public slots:

private:
    QPushButton b;
};

#endif // SUBWIDGET_H

-- D:\project_c++\qt001\03\mainwidget.cpp

#include "mainwidget.h"
#include <QPushButton>
#include <QDebug> //打印

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{

    setWindowTitle("老大");
    //this->setWindowTitle("老大");

    b3.setParent(this);
    b3.setText("切换到子窗口");
    b3.move(50, 50);

    //显示子窗口
    //subWin.show();

    connect(&b3, &QPushButton::released, this, &MainWidget::changeWin);

    //处理子窗口的信号
    void (SubWidget::*funSignal)() = &SubWidget::mySignal;
    connect(&subWin, funSignal, this, &MainWidget::dealSub);

    void (SubWidget::*testSignal)(int, QString) = &SubWidget::mySignal;
    connect(&subWin, testSignal, this, &MainWidget::dealSlot);

}

void MainWidget::dealSlot(int a, QString str)
{
    // str.toUtf8() -> 字节数组QByteArray
    // ……data()  -> QByteArray -> char *
    qDebug() << a << str.toUtf8().data();
}

void MainWidget::changeWin()
{
    //子窗口显示
    subWin.show();
    //本窗口隐藏
    this->hide();
}


void MainWidget::dealSub()
{
    //子窗口隐藏
    subWin.hide();
    //本窗口显示
    show();
}

MainWidget::~MainWidget()
{

}


-- 14_Lamda表达式和再说信号的功能 

-- D:\project_c++\qt001\03\03.pro 


#-------------------------------------------------
#
# Project created by QtCreator 2015-12-30T10:49:47
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 03_SignalAndSlot
TEMPLATE = app


SOURCES += main.cpp\
        mainwidget.cpp \
    subwidget.cpp

HEADERS  += mainwidget.h \
    subwidget.h

CONFIG += C++11


--  D:\project_c++\qt001\03\mainwidget.cpp

#include "mainwidget.h"
#include <QPushButton>
#include <QDebug> //打印

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{


    setWindowTitle("老大");
    //this->setWindowTitle("老大");

    b3.setParent(this);
    b3.setText("切换到子窗口");
    b3.move(50, 50);

    //显示子窗口
    //subWin.show();

    connect(&b3, &QPushButton::released, this, &MainWidget::changeWin);

    //Qt4信号连接
    //Qt4槽函数必须有slots关键字来修饰
    connect(&subWin, SIGNAL(mySignal()), this, SLOT(dealSub()) );

    connect(&subWin, SIGNAL(mySignal(int,QString)),
            this, SLOT(dealSlot(int,QString)) );
    // SIGNAL SLOT 将函数名字 -> 字符串  不进行错误检查

    //Lambda表达式, 匿名函数对象
    //C++11增加的新特性， 项目文件： CONFIG += C++11
    //Qt配合信号一起使用，非常方便

    QPushButton *b4 = new QPushButton(this);
    b4->setText("Lambda表达式");
    b4->move(150, 150);
    int a = 10, b = 100;
    connect(b4, &QPushButton::clicked,
            // = :把外部所有局部变量、类中所有成员以值传递方式
            // this: 类中所有成员以值传递方式
            // & : 把外部所有局部变量， 引用符号
            [=](bool isCheck)
            {
                qDebug() << isCheck;
                b4->setText("xx");//如果  [=] 里不加 = 报错 ，换成 [b4] 也可以
                qDebug() << a<<b;
            }


            );


    resize(400, 300);
}

void MainWidget::dealSlot(int a, QString str)
{
    // str.toUtf8() -> 字节数组QByteArray
    // ……data()  -> QByteArray -> char *
    qDebug() << a << str.toUtf8().data();
}

void MainWidget::changeWin()
{
    //子窗口显示
    subWin.show();
    //本窗口隐藏
    this->hide();
}


void MainWidget::dealSub()
{
    //子窗口隐藏
    subWin.hide();
    //本窗口显示
    show();
}

MainWidget::~MainWidget()
{

}


--  15_坐标系统


#include "mainwidget.h"
#include <QPushButton>


MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{
    /* 对于父窗口（主窗口），坐标系统相对于屏幕
     * 原点：相对于屏幕左上角
     * x: 往右递增
     * y: 往下递增
    */
    move(100, 100);


    /* 子窗口，坐标系统相对于父窗口
     * 原点：相对于窗口空白区域左上角（不包括边框）
     * x: 往右递增
     * y: 往下递增
    */
    QPushButton *b1 = new QPushButton(this);
    b1->move(100, 100);
    b1->setText("^_^");
    b1->resize(200, 100);

    QPushButton *b2 = new QPushButton(b1);

    b2->move(10, 10);
    b2->setText("@_@");



    //1)指定父对象后  2)直接或间接继承于QObject
    //子对象如果是动态分配空间的new，不需要手动释放delete
    //系统会自动释放

}

MainWidget::~MainWidget()
{

}


-- 

--  17_菜单栏_工具栏littleSignificance

--  D:\project_c++\qt001\05_qmain\mainwindow.cpp

#include "mainwindow.h"
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QDebug>
#include <QToolBar>
#include <QPushButton>
#include <QStatusBar>
#include <QLabel>
#include <QTextEdit>
#include <QDockWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //菜单栏
    QMenuBar *mBar = menuBar();

    //添加菜单
    QMenu *pFile = mBar->addMenu("文件");

    //添加菜单项，添加动作
    QAction *pNew = pFile->addAction("新建");

    connect(pNew, &QAction::triggered,

            [=]()
            {
                qDebug() << "新建被按下";
            }

            );
    pFile->addSeparator(); //添加分割线·
    QAction *pOpen = pFile->addAction("打开");

    //工具栏，菜单项的快捷方式
    QToolBar *toolBar = addToolBar("toolBar");

    //工具栏添加快捷键
    toolBar->addAction(pNew);

    QPushButton *b = new QPushButton(this);
    b->setText("^_^");
    //添加小控件
    toolBar->addWidget(b);

    connect(b, &QPushButton::clicked,
            [=]()
            {
                b->setText("123");
            }
            );

}

MainWindow::~MainWindow()
{

}

 
-- 18_核心控件和浮动窗口littleSignificance 

--  D:\project_c++\qt001\05_qmain\mainwindow.cpp

#include "mainwindow.h"
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QDebug>
#include <QToolBar>
#include <QPushButton>
#include <QStatusBar>
#include <QLabel>
#include <QTextEdit>
#include <QDockWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    //状态栏
    QStatusBar *sBar = statusBar();
    QLabel *label = new QLabel(this);
    label->setText("rrr");
    sBar->addWidget(label);
    //addWidget 从左往右添加
    sBar->addWidget(new QLabel("xxx", this));

    // addPermanentWidget 从右往左添加
    sBar->addPermanentWidget(new QLabel("qqq", this));

    //核心控件
    QTextEdit *textEdit = new QTextEdit(this);
    setCentralWidget(textEdit);

    //浮动窗口
    QDockWidget *dock = new QDockWidget(this);
    addDockWidget(Qt::RightDockWidgetArea, dock);

    //给浮动窗口添加控件
    QTextEdit *textEdit1 = new QTextEdit(this);
    dock->setWidget(textEdit1);
}

MainWindow::~MainWindow()
{

}


--   19_模态和非模态对话框 


 
#include "mainwindow.h"
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QDialog>
#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    QMenuBar *mBar = menuBar();
    setMenuBar(mBar);
    QMenu *menu = mBar->addMenu("对话框");
    QAction *p1 = menu->addAction("模态对话框");
    connect(p1, &QAction::triggered,
            [=]()
            {
                QDialog dlg;
                dlg.exec();
                qDebug() << "111111";
            }

            );

   

}

MainWindow::~MainWindow()
{

}


-- 20_标准对话框和文件对话框

#include "mainwindow.h"
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QDialog>
#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    QMenuBar *mBar = menuBar();
    setMenuBar(mBar);
    QMenu *menu = mBar->addMenu("对话框");
    QAction *p1 = menu->addAction("模态对话框");
    connect(p1, &QAction::triggered,
            [=]()
            {
                QDialog dlg;
                dlg.exec();
                qDebug() << "111111";
            }

            );

    QAction *p2 = menu->addAction("非模态对话框");
    connect(p2, &QAction::triggered,
            [=]()
            {

//                dlg.show();
//                qDebug() << "111111";


//                QDialog *p = new QDialog(this);
//                p->show();

                 QDialog *p = new QDialog;
                 p->setAttribute(Qt::WA_DeleteOnClose);
                 p->show();
            }

            );

    QAction *p3 = menu->addAction("关于对话框");
    connect(p3, &QAction::triggered,
            [=]()
            {
               QMessageBox::about(this, "about", "关于qt");
            }

            );

    QAction *p4 = menu->addAction("问题对话框");
    connect(p4, &QAction::triggered,
            [=]()
            {
               int ret = QMessageBox::question(this,
                           "question", "Are you ok?",
                              QMessageBox::Ok |
                                QMessageBox::Cancel

                                               );
                switch(ret)
                {
                case QMessageBox::Ok:
                    qDebug() << "i am ok";
                    break;
                case QMessageBox::Cancel:
                    qDebug() << "i am bad";
                    break;
                default:
                    break;
                }
            }

            );


    QAction *p5 = menu->addAction("文件对话框");
    connect(p5, &QAction::triggered,
            [=]()
            {
               QString path = QFileDialog::getOpenFileName(
                           this,
                           "open",
                           "../",
             "souce(*.cpp *.h);;Text(*.txt);;all(*.*)"
                           );
               qDebug() << path;
            }

            );


}

MainWindow::~MainWindow()
{

}






















                     ^
