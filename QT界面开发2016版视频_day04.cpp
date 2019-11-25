

-- 03_棋盘练习答案

--  D:\project_c++\qt001\07_ChessDemo\chesswidget.h

#ifndef CHESSWIDGET_H
#define CHESSWIDGET_H

#include <QWidget>

class ChessWidget : public QWidget
{
    Q_OBJECT

public:
    ChessWidget(QWidget *parent = 0);
    ~ChessWidget();

protected:
    //重写绘图事件
    void paintEvent(QPaintEvent *);
    //重写鼠标按下事件
    void mousePressEvent(QMouseEvent *e);

private:
    int gridW;  //棋盘水平方向一个格子的宽度
    int gridH;  //棋盘水平方向一个格子的高度
    int startX; //棋盘起点x坐标
    int startY; //棋盘起点y坐标

    int chessX, chessY; //棋盘下标

};

#endif // CHESSWIDGET_H


-- D:\project_c++\qt001\07_ChessDemo\chesswidget.cpp

#include "chesswidget.h"
#include <QPainter>
#include <QPen>
#include <QMouseEvent>
#include <QDebug>

ChessWidget::ChessWidget(QWidget *parent)
    : QWidget(parent)
{
    chessX = -1;
    chessY = -1;
}

ChessWidget::~ChessWidget()
{

}

void ChessWidget::paintEvent(QPaintEvent *)
{
    gridW = width()/10;  //窗口宽度分10份
    gridH = height()/10; //窗口高度分10份

    //棋盘起点坐标
    startX = gridW;
    startY = gridH;

    QPainter p(this); //创建画家，指定窗口为绘图设备

    //背景图
    p.drawPixmap(rect(), QPixmap(":/new/prefix1/Image/bk.jpg"));

    //设置画笔
    QPen pen;
    pen.setWidth(4); //线宽
    p.setPen(pen);  //将画笔交给画家

    //取中间8份画棋盘
    for(int i = 0; i <= 8; i++)
    {
        //横线
        p.drawLine(startX, startY+i*gridH, startX+8*gridW, startY+i*gridH);

        //竖线
        p.drawLine(startX+i*gridW, startY, startX+i*gridW, startY+8*gridH);
    }

    //画棋子
    if(chessX != -1 && chessY != -1)
    {
        p.drawPixmap(startX+chessX*gridW, startY+chessY*gridH,
                     gridW, gridH,
                     QPixmap(":/new/prefix1/Image/face.png")
                     );
    }
}

void ChessWidget::mousePressEvent(QMouseEvent *e)
{
    //获取点击的坐标
    int x = e->x();
    int y = e->y();

    // 要保证点击点在棋盘范围里面
    if(x >= startX && x <= startX+8*gridW
       && y >= startY && y <= startX+8*gridH)
    {
        // 棋盘的位置转换转换为坐标下标值
        // 类似于a[i][j]的i和j
        chessX = (x - startX)/gridW;
        chessY = (y - startY)/gridH;
        qDebug() << chessX << chessY;

        //更新窗口，间接调用paintEvent()
        update();
    }
}



--   06_TCP服务器

-- D:\project_c++\qt001\04_TCPFile\clientwidget.h

#ifndef CLIENTWIDGET_H
#define CLIENTWIDGET_H

#include <QWidget>
#include <QTcpSocket>
#include <QFile>

namespace Ui {
class ClientWidget;
}

class ClientWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ClientWidget(QWidget *parent = 0);
    ~ClientWidget();

private slots:
    void on_buttonConnect_clicked();

private:
    Ui::ClientWidget *ui;

    QTcpSocket *tcpSocket;

    QFile file; //文件对象
    QString fileName; //文件名字
    qint64 fileSize; //文件大小
    qint64 recvSize; //已经接收文件的大小

    bool isStart;   //标志位，是否为头部信息
};

#endif // CLIENTWIDGET_H



  -- D:\project_c++\qt001\04_TCPFile\clientwidget.cpp
  
  #include "clientwidget.h"
#include "ui_clientwidget.h"
#include <QDebug>
#include <QMessageBox>
#include <QHostAddress>

ClientWidget::ClientWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientWidget)
{
    ui->setupUi(this);

    tcpSocket = new QTcpSocket(this);

    isStart = true;

    ui->progressBar->setValue(0); //当前值

    setWindowTitle("客户端");

    connect(tcpSocket, &QTcpSocket::readyRead,
    [=]()
    {
        //取出接收的内容
        QByteArray buf = tcpSocket->readAll();

        if(true == isStart)
        {//接收头
            isStart = false;
            //解析头部信息 QString buf = "hello##1024"
            //                    QString str = "hello##1024#mike";
            //                            str.section("##", 0, 0)

            //初始化
            //文件名
            fileName = QString(buf).section("##", 0, 0);
            //文件大小
            fileSize = QString(buf).section("##", 1, 1).toInt();
            recvSize = 0;   //已经接收文件大小

            //打开文件
            //关联文件名字
            file.setFileName(fileName);

            //只写方式方式，打开文件
            bool isOk = file.open(QIODevice::WriteOnly);
            if(false == isOk)
            {
                qDebug() << "WriteOnly error 49";

                tcpSocket->disconnectFromHost(); //断开连接
                tcpSocket->close(); //关闭套接字

                return; //如果打开文件失败，中断函数
            }

            //弹出对话框，显示接收文件的信息
            QString str = QString("接收的文件: [%1: %2kb]").arg(fileName).arg(fileSize/1024);
            QMessageBox::information(this, "文件信息", str);

            //设置进度条
            ui->progressBar->setMinimum(0); //最小值
            ui->progressBar->setMaximum(fileSize/1024); //最大值
            ui->progressBar->setValue(0); //当前值

        }
        else //文件信息
        {
            qint64 len = file.write(buf);
            if(len >0) //接收数据大于0
            {
                recvSize += len; //累计接收大小
                qDebug() << len;
            }

            //更新进度条
            ui->progressBar->setValue(recvSize/1024);

            if(recvSize == fileSize) //文件接收完毕
            {

                //先给服务发送(接收文件完成的信息)
                tcpSocket->write("file done");

                QMessageBox::information(this, "完成", "文件接收完成");
                file.close(); //关闭文件
                //断开连接
                tcpSocket->disconnectFromHost();
                tcpSocket->close();

            }
        }

        }

    );

}

ClientWidget::~ClientWidget()
{
    delete ui;
}

void ClientWidget::on_buttonConnect_clicked()
{
    //获取服务器的ip和端口
    QString ip = ui->lineEditIP->text();
    quint16 port = ui->lineEditPort->text().toInt();

    //主动和服务器连接
    tcpSocket->connectToHost(QHostAddress(ip), port);

    isStart = true;

    //设置进度条
    ui->progressBar->setValue(0);
}


-- D:\project_c++\qt001\04_TCPFile\serverwidget.h

#ifndef SERVERWIDGET_H
#define SERVERWIDGET_H

#include <QWidget>
#include <QTcpServer> //监听套接字
#include <QTcpSocket> //通信套接字
#include <QFile>
#include <QTimer>

namespace Ui {
class ServerWidget;
}

class ServerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ServerWidget(QWidget *parent = 0);
    ~ServerWidget();

    void sendData(); //发送文件数据

private slots:
    void on_buttonFile_clicked();

    void on_buttonSend_clicked();

private:
    Ui::ServerWidget *ui;

    QTcpServer *tcpServer; //监听套接字
    QTcpSocket *tcpSocket; //通信套接字

    QFile file; //文件对象
    QString fileName; //文件名字
    qint64 fileSize; //文件大小
    qint64 sendSize; //已经发送文件的大小

    QTimer timer; //定时器





};

#endif // SERVERWIDGET_H


-- D:\project_c++\qt001\04_TCPFile\serverwidget.cpp 

#include "serverwidget.h"
#include "ui_serverwidget.h"
#include <QFileDialog>
#include <QDebug>
#include <QFileInfo>

ServerWidget::ServerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ServerWidget)
{
    ui->setupUi(this);

    //监听套接字
    tcpServer = new QTcpServer(this);

    //监听
    tcpServer->listen(QHostAddress::Any, 8888);
    setWindowTitle("服务器端口为：8888");

    //两个按钮都不能按
    ui->buttonFile->setEnabled(false);
    ui->buttonSend->setEnabled(false);

    //如果客户端成功和服务器连接
    //tcpServer会自动触发 newConnection()
    connect(tcpServer, &QTcpServer::newConnection,
    [=]()
    {
        //取出建立好连接的套接字
        tcpSocket = tcpServer->nextPendingConnection();
        //获取对方的ip和端口
        QString ip = tcpSocket->peerAddress().toString();
        quint16 port = tcpSocket->peerPort();

        QString str = QString("[%1:%2] 成功连接").arg(ip).arg(port);
        ui->textEdit->setText(str); //显示到编辑区

        //成功连接后，才能按选择文件
        ui->buttonFile->setEnabled(true);

        connect(tcpSocket, &QTcpSocket::readyRead,
                [=]()
                {
                    //取客户端的信息
                    QByteArray buf = tcpSocket->readAll();
                    if(QString(buf) == "file done")
                    {//文件接收完毕
                         ui->textEdit->append("文件发送完毕");
                         file.close();

                         //断开客户端端口
                         tcpSocket->disconnectFromHost();
                         tcpSocket->close();
                    }

                }

                );

    }
    );

    connect(&timer, &QTimer::timeout,
            [=]()
            {
                //关闭定时器
                timer.stop();

                //发送文件
                sendData();
            }

            );

}

ServerWidget::~ServerWidget()
{
    delete ui;
}

//选择文件的按钮
void ServerWidget::on_buttonFile_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, "open", "../");
    if(false == filePath.isEmpty()) //如果选择文件路径有效
    {
        fileName.clear();
        fileSize = 0;

        //获取文件信息
        QFileInfo info(filePath);
        fileName = info.fileName(); //获取文件名字
        fileSize = info.size(); //获取文件大小

        sendSize = 0; //发送文件的大小

        //只读方式打开文件
        //指定文件的名字
        file.setFileName(filePath);

        //打开文件
        bool isOk = file.open(QIODevice::ReadOnly);
        if(false == isOk)
        {
            qDebug() << "只读方式打开文件失败 106";
        }

        //提示打开文件的路径
        ui->textEdit->append(filePath);

        ui->buttonFile->setEnabled(false);
        ui->buttonSend->setEnabled(true);

    }
    else
    {
        qDebug() << "选择文件路径出错 118";
    }

}
//发送文件按钮
void ServerWidget::on_buttonSend_clicked()
{
    ui->buttonSend->setEnabled(false);

    //先发送文件头信息  文件名##文件大小
    QString head = QString("%1##%2").arg(fileName).arg(fileSize);
    //发送头部信息
    qint64 len = tcpSocket->write( head.toUtf8() );
    if(len > 0)//头部信息发送成功
    {
        //发送真正的文件信息
        //防止TCP黏包
        //需要通过定时器延时 20 ms
        timer.start(20);


    }
    else
    {
        qDebug() << "头部信息发送失败 142";
        file.close();
        ui->buttonFile->setEnabled(true);
        ui->buttonSend->setEnabled(false);
    }
}

void ServerWidget::sendData()
{
    ui->textEdit->append("正在发送文件……");
     qint64 len = 0;
     do
     {
        //每次发送数据的大小
        char buf[4*1024] = {0};
        len = 0;

        //往文件中读数据
        len = file.read(buf, sizeof(buf));
        //发送数据，读多少，发多少
        len = tcpSocket->write(buf, len);

        //发送的数据需要累积
        sendSize += len;

     }while(len > 0);


//     //是否发送文件完毕
//     if(sendSize == fileSize)
//     {
//         ui->textEdit->append("文件发送完毕");
//         file.close();

//         //把客户端端口
//         tcpSocket->disconnectFromHost();
//         tcpSocket->close();
//     }


}




-- 07_TCP服务器2 






-- 



























 



