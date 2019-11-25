




 -- 03_画背景图
 
 --  D:\project_c++\qt001\01_PaintEvent\widget.h

#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

protected:
    //重写绘图事件，虚函数
    //如果在窗口绘图，必须放在绘图事件里实现
    //绘图事件内部自动调用，窗口需要重绘的时候（状态改变）
    void paintEvent(QPaintEvent *);

private slots:
    void on_pushButton_clicked();

private:
    Ui::Widget *ui;
    int x;
};

#endif // WIDGET_H


-- D:\project_c++\qt001\01_PaintEvent\widget.cpp

#include "widget.h"
#include "ui_widget.h"
#include <QPainter>
#include <QPen>
#include <QBrush>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    x = 0;
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *)
{
    //QPainter p(this);

    QPainter p;//创建画家对象
    p.begin(this);//指定当前窗口为绘图设备

    //绘图操作
    //p.drawxxx();
    //画背景图
    //p.drawPixmap(0, 0, width(), height(), QPixmap("../Image/bk.png"));
    p.drawPixmap(rect(), QPixmap("../Image/bk.png"));

    //定义画笔
    QPen pen;
    pen.setWidth(5); //设置线宽
    //pen.setColor(Qt::red); //设置颜色
    pen.setColor( QColor(14, 9, 234) );//rgb设置颜色
    pen.setStyle(Qt::DashLine); //设置风格

    //把画笔交给画家
    p.setPen(pen);

    //画直线
    p.drawLine(50, 50, 150, 50);
    p.drawLine(50, 50, 50, 150);

    //创建画刷对象
    QBrush brush;
    brush.setColor(Qt::red); //设置颜色
    brush.setStyle(Qt::Dense1Pattern);//设置样式

    //把画刷交给画家
    p.setBrush(brush);


    //画矩形
    p.drawRect(150, 150, 100, 50);

    //画圆形
    p.drawEllipse(QPoint(150, 150), 50, 25);

    //画笑脸
    p.drawPixmap(x, 180, 80, 80, QPixmap("../Image/face.png"));

    p.end();
}

void Widget::on_pushButton_clicked()
{
    x += 20;
    if(x > width())
    {
        x = 0;
    }

    //刷新窗口，让窗口重绘，整个窗口都刷新
    update(); //间接调用paintEvent()
}



--   12_QFile读文件

-- D:\project_c++\qt001\07_QFile\widget.cpp

#include "widget.h"
#include "ui_widget.h"
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QDebug>
#include <QDateTime>
#include <QDataStream>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_buttonRead_clicked()
{
    QString path = QFileDialog::getOpenFileName(this,
                "open", "../", "TXT(*.txt)");
    if(path.isEmpty() == false)
    {
        //文件对象
        QFile file(path);

        //打开文件，只读方式
        bool isOk = file.open(QIODevice::ReadOnly);
        if(isOk == true)
        {
#if 0
            //读文件，默认只识别utf8编码
            QByteArray array = file.readAll();
            //显示到编辑区
            //ui->textEdit->setText(QString(array));
            ui->textEdit->setText(array);
#endif

            QByteArray array;
            while( file.atEnd() == false)
            {
                //读一行
                array += file.readLine();
            }
            ui->textEdit->setText(array);

        }

        //关闭文件
        file.close();

        //获取文件信息
        QFileInfo info(path);
        qDebug() << "文件名字：" << info.fileName().toUtf8().data();
        qDebug() << "文件后缀：" << info.suffix();
        qDebug() << "文件大小：" << info.size();
        qDebug() << "文件创建时间：" <<
         info.created().toString("yyyy-MM-dd hh:mm:ss"); //2016-01-04 15:13:00

    }


}

void Widget::on_buttonWrite_clicked()
{
    QString path = QFileDialog::getSaveFileName(this, "save", "../", "TXT(*.txt)");
    if(path.isEmpty() == false)
    {
        QFile file; //创建文件对象
        //关联文件名字
        file.setFileName(path);

        //打开文件，只写方式
        bool isOk = file.open(QIODevice::WriteOnly);
        if(isOk == true)
        {
            //获取编辑区内容
            QString str = ui->textEdit->toPlainText();
            //写文件
            // QString -> QByteArray
            //file.write(str.toUtf8());

            //QString -> c++ string -> char *
            //file.write(str.toStdString().data());

            //转换为本地平台编码
            file.write(str.toLocal8Bit());


            //QString -> QByteArray
            QString buf = "123";
            QByteArray a = buf.toUtf8(); //中文
            a = buf.toLocal8Bit(); //本地编码

            //QByteArray -> char *
            char *b = a.data();

            //char * -> QString
            char *p = "abc";
            QString c = QString(p);


        }

        file.close();

    }




}


--   15_QDataStream读写文件 

-- D:\project_c++\qt001\08_QDataStream\widget.cpp 

#include "widget.h"
#include "ui_widget.h"
#include <QDataStream>
#include <QTextStream>
#include <QFile>
#include <QDebug>
#define cout qDebug() << "[" << __FILE__ <<":" << __LINE__ << "]"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    writeData();
    readData();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::writeData()
{
    //创建文件对象
    QFile file("../test.txt");

    //打开文件， 只写方式打开
    bool isOk = file.open(QIODevice::WriteOnly);
    if(true == isOk)
    {
        //创建数据流，和file文件关联
        //往数据流中写数据，相当于往文件里写数据
        QDataStream stream(&file);

        stream << QString("主要看气质") << 250;

        file.close();

    }

}

void Widget::readData()
{
    //创建文件对象
    QFile file("../test.txt");

    //打开文件， 只读方式打开
    bool isOk = file.open(QIODevice::ReadOnly);
    if(true == isOk)
    {
        //创建数据流，和file文件关联
        //往数据流中读数据，相当于往文件里读数据
        QDataStream stream(&file);
        //读的时候，按写的顺序取数据
        QString str;
        int a;
        stream >> str >> a;
        //qDebug() << str.toUtf8().data() << a;
        cout << str.toUtf8().data() << a;

        file.close();

    }
}


--  17_QBuffer 

-- D:\project_c++\qt001\09_QTextStream\widget.cpp

#include "widget.h"
#include "ui_widget.h"
#include <QTextStream>
#include <QFile>
#include <QDebug>
#include <QFileDialog>
#include <QBuffer>
#define cout qDebug() << "[" << __FILE__ <<":" << __LINE__ << "]"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    writeData();

    readData();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::writeData()
{
    QFile file;
    file.setFileName("../demo.txt");

    bool isOk = file.open(QIODevice::WriteOnly);
    if(true == isOk)
    {
        QTextStream stream(&file);
        //指定编码
        stream.setCodec("UTF-8");

        stream << QString("主要看气质") << 250;

        file.close();
    }
}

void Widget::readData()
{
    QFile file;
    file.setFileName("../demo.txt");

    bool isOk = file.open(QIODevice::ReadOnly);
    if(true == isOk)
    {
        QTextStream stream(&file);
        //指定编码
        stream.setCodec("UTF-8");
        QString str;
        int a;
        stream >> str >> a;

        cout << str.toUtf8().data() << a;

        file.close();

    }
}

void Widget::on_pushButton_clicked()
{
    QString path = QFileDialog::getOpenFileName(this,
             "open", "../"  );
    if(false == path.isEmpty())
    {
        QFile file;
        file.setFileName(path);

        bool isOk = file.open(QIODevice::ReadOnly);
        if(true == isOk)
        {
            QTextStream stream(&file);
            //指定编码
            stream.setCodec("UTF-8");

            QString str = stream.readAll();
            ui->textEdit->setText(str);

            file.close();
        }

    }


}











