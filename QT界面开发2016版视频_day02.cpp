


-- 02_设计器的使用


-- 07_Qt样式表noimportance

-- D:\project_c++\qt001\03_StyleSheet\widget.cpp

 #include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    this->setStyleSheet("QLabel{color:rgb(0, 255, 255);"
                        "background-color:red;"
                        "}");

    ui->label->setStyleSheet("QLabel{color:rgb(0, 255, 255);"
                             "background-color:blue;"
                             "border-image:url(:/new/prefix1/image/Sunny.jpg);"
                             "}");

    ui->pushButton->setStyleSheet("QPushButton{"
                                  "border-image:url(:/new/prefix1/image/Sunny.jpg);"
                                  "}"
                                  "QPushButton:hover{"
                                  "border-image:url(:/new/prefix1/image/up.png);"
                                  "}"

                                  "QPushButton:pressed{"
                                  "border-image:url(:/new/prefix1/image/Luffy.png);"
                                  "}"

                                  );


}

Widget::~Widget()
{
    delete ui;
}





-- 09_事件(上)_02

-- D:\project_c++\qt001\04_QEvent\mybutton.h

#ifndef MYBUTTON_H
#define MYBUTTON_H

#include <QPushButton>

class MyButton : public QPushButton
{
    Q_OBJECT
public:
    explicit MyButton(QWidget *parent = 0);

protected:
    void mousePressEvent(QMouseEvent *e);

signals:

public slots:
};

#endif // MYBUTTON_H


--  D:\project_c++\qt001\04_QEvent\mybutton.cpp 

#include "mybutton.h"
#include <QMouseEvent>
#include <QDebug>

MyButton::MyButton(QWidget *parent) : QPushButton(parent)
{

}

void MyButton::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
    {
        //如果是左键按下
        qDebug() << "按下的是左键";
        //事件接收后，就会往下传递


        //e->ignore(); //忽略，事件继续往下传递，给谁传递？
                     //事件传递给了父组件，不是给父类（基类）
    }
    else
    {
        //不做处理
        QPushButton::mousePressEvent(e);
        //事件的忽略，事件继续往下传递
    }
}


--  D:\project_c++\qt001\04_QEvent\mylabel.h 

#ifndef MYLABEL_H
#define MYLABEL_H

#include <QLabel>

class MyLabel : public QLabel
{
    Q_OBJECT
public:
    explicit MyLabel(QWidget *parent = 0);

protected:
    //鼠标点击事件
    void mousePressEvent(QMouseEvent *ev);
    //鼠标释放事件
    void mouseReleaseEvent(QMouseEvent *ev);
    //鼠标移动事件
    void mouseMoveEvent(QMouseEvent *ev);
    //进入窗口区域
    void enterEvent(QEvent *);
    //离开窗口区域
    void leaveEvent(QEvent *);

signals:

public slots:
};

#endif // MYLABEL_H


--  D:\project_c++\qt001\04_QEvent\mylabel.cpp 

#include "mylabel.h"
#include <QMouseEvent>
#include <QDebug>

MyLabel::MyLabel(QWidget *parent) : QLabel(parent)
{
    //设置追踪鼠标
    this->setMouseTracking(true);
}

void MyLabel::mousePressEvent(QMouseEvent *ev)
{
    int i = ev->x();
    int j = ev->y();
    //sprinf
    /*
     * QString str = QString("abc %1 ^_^ %2").arg(123).arg("mike");
     * str = abc 123 ^_^ mike
    */

    if(ev->button() == Qt::LeftButton)
    {
        qDebug() << "left";
    }
    else if(ev->button() == Qt::RightButton)
    {
        qDebug() << "right";
    }
    else if(ev->button() == Qt::MidButton)
    {
        qDebug() << "mid";
    }

    QString text = QString("<center><h1>Mouse Press: (%1, %2)</h1></center>")
            .arg(i).arg(j);

    this->setText(text);
    
}
void MyLabel::mouseReleaseEvent(QMouseEvent *ev)
{
    QString text = QString("<center><h1>Mouse Release: (%1, %2)</h1></center>")
            .arg( ev->x() ).arg( ev->y() );

    this->setText(text);
}

void MyLabel::mouseMoveEvent(QMouseEvent *ev)
{
    QString text = QString("<center><h1>Mouse move: (%1, %2)</h1></center>")
            .arg( ev->x() ).arg( ev->y() );

    //this->setText(text);
}

void MyLabel::enterEvent(QEvent *e)
{
    QString text = QString("<center><h1>Mouse enter</h1></center>");

    this->setText(text);
}

void MyLabel::leaveEvent(QEvent *e)
{
    QString text = QString("<center><h1>Mouse leave</h1></center>");

    this->setText(text);
}



-- D:\project_c++\qt001\04_QEvent\mywidget.h 

#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>

namespace Ui {
class MyWidget;
}

class MyWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MyWidget(QWidget *parent = 0);
    ~MyWidget();

protected:
    //键盘按下事件
    void keyPressEvent(QKeyEvent *);
    //计时器事件
    void timerEvent(QTimerEvent *);
    //鼠标点击事件
    void mousePressEvent(QMouseEvent *);
    //关闭事件
    void closeEvent(QCloseEvent *);

    // 重写event事件
    bool event(QEvent *);

    //事件过滤器
    bool eventFilter(QObject *obj, QEvent *e);

private:
    Ui::MyWidget *ui;

    int timerId;
    int timeId2;
};

#endif // MYWIDGET_H



-- D:\project_c++\qt001\04_QEvent\mywidget.cpp

#include "mywidget.h"
#include "ui_mywidget.h"
#include <QDebug>
#include <QKeyEvent>
#include <QCloseEvent>
#include <QMessageBox>
#include <QEvent>

MyWidget::MyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyWidget)
{
    ui->setupUi(this);

    timerId = this->startTimer(1000); //毫秒为单位 每隔1s触发一次定时器
    this->timeId2 = this->startTimer(500);


    connect(ui->pushButton, &MyButton::clicked,
            [=]()
            {
                qDebug() << "按钮被按下";
            }

            );

    //安装过滤器
    ui->label_2->installEventFilter(this);
    ui->label_2->setMouseTracking(true);
}

MyWidget::~MyWidget()
{
    delete ui;
}

void MyWidget::keyPressEvent(QKeyEvent *e)
{
    qDebug() << (char)e->key();

    if(e->key() == Qt::Key_A)
    {
        qDebug() << "Qt::Key_A";
    }
}

void MyWidget::timerEvent(QTimerEvent *e)
{
    if(e->timerId() == this->timerId)
    {
        static int sec = 0;
        ui->label->setText(
             QString("<center><h1>timer out: %1</h1></center>").arg(sec++)

                    );

        if(5 == sec)
        {
            //停止定时器
            this->killTimer(this->timerId);
        }
    }
    else if(e->timerId() == this->timeId2)
    {
        static int sec = 0;
        ui->label_2->setText(
             QString("<center><h1>timer out: %1</h1></center>").arg(sec++)

                    );
    }
}

void MyWidget::mousePressEvent(QMouseEvent *e)
{
    qDebug() << "+++++++++++++++++++++++";
}

void MyWidget::closeEvent(QCloseEvent *e)
{
    int ret = QMessageBox::question(this, "question", "是否需要关闭窗口");
    if(ret == QMessageBox::Yes)
    {
        //关闭窗口
        //处理关闭窗口事件，接收事件，事件就不会再往下传递
        e->accept();
    }
    else
    {
        //不关闭窗口
        //忽略事件，事件继续给父组件传递
        e->ignore();
    }

}

bool MyWidget::event(QEvent *e)
{
//    //事件分发
//    switch( e->type() )
//    {
//        case QEvent::Close:
//            closeEvent(e);
//        break;
//    case QEvent::MouseMove:
//        mouseMoveEvent(e);
//        break;
//        /*
//         *  ……
//        */
//    }

    if(e->type() == QEvent::Timer)
    {
        //干掉定时器
        //如果返回true，事件停止传播
        //QTimerEvent *env = static_cast<QTimerEvent *>(e);
        //timerEvent(env);
        return true;
    }
    else if(e->type() == QEvent::KeyPress)
    {
        //类型转换
        QKeyEvent *env = static_cast<QKeyEvent *>(e);
        if(env->key() == Qt::Key_B)
        {
            return QWidget::event(e);
        }
        return true;

    }
    else
    {
        return QWidget::event(e);
        //return false;
    }

}

bool MyWidget::eventFilter(QObject *obj, QEvent *e)
{
    if(obj == ui->label_2)
    {
        QMouseEvent *env = static_cast<QMouseEvent *>(e);
        //判断事件
        if(e->type() == QEvent::MouseMove)
        {
            ui->label_2->setText(QString("Mouse move:(%1, %2)").arg(env->x()).arg(env->y()));
            return true;
        }
        if(e->type() == QEvent::MouseButtonPress)
        {
            ui->label_2->setText(QString("Mouse press:(%1, %2)").arg(env->x()).arg(env->y()));
            return true;
        }
        if(e->type() == QEvent::MouseButtonRelease)
        {
            ui->label_2->setText(QString("Mouse release:(%1, %2)").arg(env->x()).arg(env->y()));
            return true;
        }
        else
        {
            return QWidget::eventFilter(obj, e);
        }
    }
    else
    {
        return QWidget::eventFilter(obj, e);
    }
    
//    if(obj == ui->pushButton)
//    {
        
//    }
}






























 