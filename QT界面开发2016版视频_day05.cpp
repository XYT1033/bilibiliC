

-- 04_线程1_1



 --  D:\project_c++\qt001\01_QThread\mythread.h

#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>


class MyThread : public QThread
{
    Q_OBJECT
public:
    explicit MyThread(QObject *parent = 0);

protected:
    //QThread的虚函数
    //线程处理函数
    //不能直接调用，通过start()间接调用
    void run();

signals:
    void isDone();

public slots:
};

#endif // MYTHREAD_H


-- D:\project_c++\qt001\01_QThread\mythread.cpp

#include "mythread.h"

MyThread::MyThread(QObject *parent) : QThread(parent)
{

}

void MyThread::run()
{
    //很复杂的数据处理
    //需要耗时5s
    sleep(5);

    emit isDone();
}

-- D:\project_c++\qt001\01_QThread\mywidget.h 

#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QTimer> //定时器头文件
#include "mythread.h" //线程头文件

namespace Ui {
class MyWidget;
}

class MyWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MyWidget(QWidget *parent = 0);
    ~MyWidget();

    void dealTimeout(); //定时器槽函数
    void dealDone(); //线程结束槽函数
    void stopThread(); //停止线程槽函数

private slots:
    void on_pushButton_clicked();

private:
    Ui::MyWidget *ui;

    QTimer *myTimer; //声明变量
    MyThread *thread; //线程对象
};

#endif // MYWIDGET_H



--  D:\project_c++\qt001\01_QThread\mywidget.cpp

#include "mywidget.h"
#include "ui_mywidget.h"
#include <QThread>
#include <QDebug>

MyWidget::MyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyWidget)
{
    ui->setupUi(this);

    myTimer = new QTimer(this);

    //只要定时器启动，自动触发timeout()
    connect(myTimer, &QTimer::timeout, this, &MyWidget::dealTimeout);

    //分配空间
    thread = new MyThread(this);


    connect(thread, &MyThread::isDone, this, &MyWidget::dealDone);

    //当按窗口右上角x时，窗口触发destroyed()
    connect(this, &MyWidget::destroyed, this, &MyWidget::stopThread);

}

void MyWidget::stopThread()
{
    //停止线程
    thread->quit();
    //等待线程处理完手头动作
    thread->wait();
}

void MyWidget::dealDone()
{
    qDebug() << "it is over";
    myTimer->stop(); //关闭定时器
}

void MyWidget::dealTimeout()
{
    static int i = 0;
    i++;
    //设置lcd的值
    ui->lcdNumber->display(i);
}

MyWidget::~MyWidget()
{
    delete ui;
}

void MyWidget::on_pushButton_clicked()
{
    //如果定时器没有工作
    if(myTimer->isActive() == false)
    {
        myTimer->start(100);
    }

    //启动线程，处理数据
    thread->start();

}


-- 07_线程3_1
 
--   D:\project_c++\qt001\02_ThreadPro\mythread.h 

#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QObject>

class MyThread : public QObject
{
    Q_OBJECT
public:
    explicit MyThread(QObject *parent = 0);

    //线程处理函数
    void myTimeout();

    void setFlag(bool flag = true);

signals:
    void mySignal();

public slots:

private:
    bool isStop;
};

#endif // MYTHREAD_H


--  D:\project_c++\qt001\02_ThreadPro\mythread.cpp

#include "mythread.h"
#include <QThread>
#include <QDebug>
#include <QMessageBox>

MyThread::MyThread(QObject *parent) : QObject(parent)
{
    isStop = false;
}

void MyThread::myTimeout()
{
    while( !isStop )
    {

        QThread::sleep(1);
        emit mySignal();
        //QMessageBox::aboutQt(NULL);

         qDebug() << "子线程号：" << QThread::currentThread();

         if(isStop)
         {
             break;
         }
    }
}

void MyThread::setFlag(bool flag)
{
    isStop = flag;
}

--  D:\project_c++\qt001\02_ThreadPro\mywidget.h

#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include "mythread.h"
#include <QThread>

namespace Ui {
class MyWidget;
}

class MyWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MyWidget(QWidget *parent = 0);
    ~MyWidget();

    void dealSignal();
    void dealClose();

signals:
    void startThread(); //启动子线程的信号

private slots:
    void on_buttonStart_clicked();

    void on_buttonStop_clicked();

private:
    Ui::MyWidget *ui;
    MyThread *myT;
    QThread *thread;

};

#endif // MYWIDGET_H

-- D:\project_c++\qt001\02_ThreadPro\mywidget.cpp

#include "mywidget.h"
#include "ui_mywidget.h"
#include <QDebug>


MyWidget::MyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyWidget)
{
    ui->setupUi(this);

    //动态分配空间，不能指定父对象
    myT = new MyThread;

    //创建子线程
    thread = new QThread(this);

    //把自定义线程加入到子线程中
    myT->moveToThread(thread);

    connect(myT, &MyThread::mySignal, this, &MyWidget::dealSignal);

    qDebug() << "主线程号：" << QThread::currentThread();

    connect(this, &MyWidget::startThread, myT, &MyThread::myTimeout);


    connect(this, &MyWidget::destroyed, this, &MyWidget::dealClose);

    //线程处理函数内部，不允许操作图形界面


    //connect()第五个参数的作用，连接方式：默认，队列，直接
    //多线程时才有意义
    //默认的时候
    //如果是多线程，默认使用队列
    //如果是单线程， 默认使用直接方式
    //队列: 槽函数所在的线程和接收者一样
    //直接：槽函数所在线程和发送者一样


}

MyWidget::~MyWidget()
{
    delete ui;
}

void MyWidget::dealClose()
{
    on_buttonStop_clicked();
    delete myT;
}

void MyWidget::dealSignal()
{
    static int i = 0;
    i++;
    ui->lcdNumber->display(i);
}

void MyWidget::on_buttonStart_clicked()
{

    if(thread->isRunning() == true)
    {
        return;
    }

    //启动线程，但是没有启动线程处理函数
    thread->start();
    myT->setFlag(false);

    //不能直接调用线程处理函数，
    //直接调用，导致，线程处理函数和主线程是在同一个线程
    //myT->myTimeout();

    //只能通过 signal - slot 方式调用
    emit startThread();


}

void MyWidget::on_buttonStop_clicked()
{
    if(thread->isRunning() == false)
    {
        return;
    }

    myT->setFlag(true);
    thread->quit();
    thread->wait();
}



-- 09_线程3_3 

--  D:\project_c++\qt001\03_ThreadIamge\mythread.h

#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QObject>
#include <QImage>

class MyThread : public QObject
{
    Q_OBJECT
public:
    explicit MyThread(QObject *parent = 0);

    //线程处理函数
    void drawImage();

signals:
    void updateImage(QImage temp);

public slots:
};

#endif // MYTHREAD_H


--  D:\project_c++\qt001\03_ThreadIamge\mythread.cpp 

#include "mythread.h"
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QImage>

MyThread::MyThread(QObject *parent) : QObject(parent)
{

}

void MyThread::drawImage()
{
    //定义QImage绘图设备
    QImage image(500, 500, QImage::Format_ARGB32);
    //定义画家，指定绘图设备
    QPainter p(&image);


    //定义画笔对象
    QPen pen;
    pen.setWidth(5); //设置宽度
    //把画笔交给画家
    p.setPen(pen);

    //定义画刷
    QBrush brush;
    brush.setStyle(Qt::SolidPattern); //设置样式
    brush.setColor(Qt::red); //设置颜色
    //把画刷交给画家
    p.setBrush(brush);

    //定义5个点
    QPoint a[] =
    {
       QPoint(qrand()%500, qrand()%500),
       QPoint(qrand()%500, qrand()%500),
       QPoint(qrand()%500, qrand()%500),
       QPoint(qrand()%500, qrand()%500),
       QPoint(qrand()%500, qrand()%500)
    };

    p.drawPolygon(a, 5);


    //通过信号发送图片
    emit updateImage(image);

}


-- D:\project_c++\qt001\03_ThreadIamge\widget.h

#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "mythread.h"
#include <QThread>
#include <QImage>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    //重写绘图事件
    void paintEvent(QPaintEvent *);

    void getImage(QImage); //槽函数
    void dealClose(); //窗口关闭槽函数

private slots:
    void on_pushButton_clicked();
    
private:
    Ui::Widget *ui;
    QImage image;
    MyThread *myT; //自定义线程对象
    QThread *thread; //子线程
};

#endif // WIDGET_H


-- D:\project_c++\qt001\03_ThreadIamge\widget.cpp 

#include "widget.h"
#include "ui_widget.h"
#include <QPainter>
#include <QThread>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //自定义类对象，分配空间，不可以指定父对象
    myT = new MyThread;

    //创建子线程
    thread = new QThread(this);

    //把自定义模块添加到子线程
    myT->moveToThread(thread);

    //启动子线程，但是，并没有启动线程处理函数
    thread->start();

    //线程处理函数，必须通过signal - slot 调用
    connect(ui->pushButton, &QPushButton::pressed, myT, &MyThread::drawImage);
    connect(myT, &MyThread::updateImage, this, &Widget::getImage);
    
    connect(this, &Widget::destroyed, this, &Widget::dealClose);

}

Widget::~Widget()
{
    delete ui;
}

void Widget::dealClose()
{
    //退出子线程
    thread->quit();
    //回收资源
    thread->wait();
    delete myT;

}

void Widget::getImage(QImage temp)
{
    image = temp;
    update(); //更新窗口，间接调用paintEvent()
}

void Widget::paintEvent(QPaintEvent *)
{
    QPainter p(this); //创建画家，指定绘图设备为窗口
    p.drawImage(50, 50, image);
}



-- 14_数据库连接


 将  libmysql.dll   放到 ：  D:\c++_tool\qt\5.6\mingw49_32\bin
 
 
 -- sql :
 
 -- 创建一个名称为info的数据库。
create database info;

-- 删除数据库info
-- drop database info;

-- 使用数据库 info
use info;

-- 创建表
-- create table student(id int primary key auto_increment, name varchar(255), age int, score int);
create table student(id int primary key, name varchar(255), age int, score int);

-- 删除student表
-- drop table student;

-- 插入数据
insert into student(id, name, age) values(1, 'mike', 18);
insert into student(id, name, age, score) values(2, 'lucy', 22, 90);
insert into student(id, name, age, score) values(3, 'Tom', 20, 78);

-- 更新数据
update student set score = 90 where id = 3;

-- 查找数据
select * from student;
select score from student where name = 'mike';

-- 删除数据库
delete from student where name = 'mike';



--  D:\project_c++\qt001\04_Database\widget.cpp

#include "widget.h"
#include "ui_widget.h"
#include <QSqlDatabase>
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>
#include <QVariantList>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //打印Qt支持的数据库驱动
    qDebug() << QSqlDatabase::drivers();

    //添加MySql数据库
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");

    //连接数据库
    db.setHostName("127.0.0.1"); //数据库服务器IP
    db.setUserName("root"); //数据库用户名
    db.setPassword("1"); //密码
    db.setDatabaseName("info"); //使用哪个数据库


    //打开数据库
    if( !db.open() ) //数据库打开失败
    {
        QMessageBox::warning(this, "错误", db.lastError().text());
        return;
    }

    QSqlQuery query;
    query.exec("select * from student");

    while(query.next()) //一行一行遍历
    {
        //取出当前行的内容
        qDebug() << query.value(0).toInt()
                 << query.value(1).toString()
                 << query.value("age").toInt()
                 << query.value("score").toInt();
    }


}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_buttonDel_clicked()
{
    //获取行编辑内容
    QString name = ui->lineEdit->text();


    QString sql = QString("delete from student where name = '%1'").arg(name);

    //开启一个事务
    QSqlDatabase::database().transaction();
    QSqlQuery query;
    query.exec(sql);

}

void Widget::on_buttonSure_clicked()
{
    //确定删除
    QSqlDatabase::database().commit();
}

void Widget::on_buttonCancel_clicked()
{
    //回滚，撤销
     QSqlDatabase::database().rollback();
}




--  18_可视化操作数据库

-- D:\project_c++\qt001\06_ModelView\widget.h

#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QSqlTableModel>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_buttonAdd_clicked();

    void on_buttonSure_clicked();

    void on_buttonCancel_clicked();

    void on_buttonDel_clicked();

    void on_buttonFind_clicked();

private:
    Ui::Widget *ui;
    QSqlTableModel *model;
};

#endif // WIDGET_H




--  D:\project_c++\qt001\06_ModelView\widget.cpp

#include "widget.h"
#include "ui_widget.h"
#include <QSqlDatabase>
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlTableModel>
#include <QSqlRecord>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //打印Qt支持的数据库驱动
    qDebug() << QSqlDatabase::drivers();

    //添加MySql数据库
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");

    //连接数据库
    db.setHostName("127.0.0.1"); //数据库服务器IP
    db.setUserName("root"); //数据库用户名
    db.setPassword("1"); //密码
    db.setDatabaseName("info"); //使用哪个数据库


    //打开数据库
    if( !db.open() ) //数据库打开失败
    {
        QMessageBox::warning(this, "错误", db.lastError().text());
        return;
    }

    //设置模型
    model = new QSqlTableModel(this);
    model->setTable("student");//制定使用哪个表

    //把model放在view
    ui->tableView->setModel(model);

    //显示model里的数据
    model->select();

    model->setHeaderData(0, Qt::Horizontal, "学号");

    //设置model的编辑模式，手动提交修改
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    //设置view中的数据库不允许修改
    //ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_buttonAdd_clicked()
{
    //添加空记录
    QSqlRecord record = model->record(); //获取空记录
    //获取行号
    int row = model->rowCount();
    model->insertRecord(row, record);


}

void Widget::on_buttonSure_clicked()
{
    model->submitAll(); //提交动作
}

void Widget::on_buttonCancel_clicked()
{
    model->revertAll(); //取消所用动作
    model->submitAll(); //提交动作
}

void Widget::on_buttonDel_clicked()
{
    //获取选中的模型
    QItemSelectionModel *sModel =ui->tableView->selectionModel();
    //取出模型中的索引
    QModelIndexList list = sModel->selectedRows();
    //删除所有选中的行
    for(int i = 0; i < list.size(); i++)
    {
        model->removeRow( list.at(i).row() );
    }

}

void Widget::on_buttonFind_clicked()
{
    QString name = ui->lineEdit->text();
    QString str = QString("name = '%1'").arg(name);

    model->setFilter(str);
    model->select();

}





