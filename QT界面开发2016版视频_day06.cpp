
-- 

-- sql 

-- 创建一个名称为car的数据库。
create database car;

-- 删除数据库car
-- drop database car;

-- 使用数据库 car
use car;

-- 创建表
create table brand (id int primary key auto_increment, factory varchar(255), name varchar(255), price int, sum int, sell int, last int);

-- 删除brand表
-- drop table brand;

-- 插入数据
insert into brand(factory,name,price,sum, sell, last) values('一汽大众', '奥迪A6', 36, 50, 8, 42);
insert into brand(factory,name,price,sum, sell, last) values('一汽大众', '捷达',   10, 80, 4, 76);
insert into brand(factory,name,price,sum, sell, last) values('一汽大众', '奔驰',   83, 40, 6, 34);
insert into brand(factory,name,price,sum, sell, last) values('二汽神龙', '毕加索', 39, 50, 6, 44);
insert into brand(factory,name,price,sum, sell, last) values('二汽神龙', '富康',   28, 60, 5, 55);
insert into brand(factory,name,price,sum, sell, last) values('二汽神龙', '标致307',27, 70, 4, 66);
insert into brand(factory,name,price,sum, sell, last) values('上海大众', '桑塔纳', 25, 75, 2, 73);
insert into brand(factory,name,price,sum, sell, last) values('上海大众', '帕萨特', 27, 65, 10, 55);


-- 创建表
create table factory (id int primary key auto_increment, name varchar(255));

-- 插入数据 请选择厂家
insert into factory(name) values('请选择厂家');
insert into factory(name) values('一汽大众');
insert into factory(name) values('二汽神龙');
insert into factory(name) values('上海大众');

-- 更新数据
-- update brand set sell=5 , last=70 where factory='上海大众' and name='桑塔纳';




--  D:\project_c++\qt001\01_CarManage\CarManage.pro

#-------------------------------------------------
#
# Project created by QtCreator 2016-01-08T09:38:20
#
#-------------------------------------------------

QT       += core gui sql xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CarManage
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    domxml.cpp \
    histogram.cpp

HEADERS  += mainwindow.h \
    domxml.h \
    histogram.h

FORMS    += mainwindow.ui


--  D:\project_c++\qt001\01_CarManage\domxml.h

#ifndef DOMXML_H
#define DOMXML_H
#include <QString>
#include <QStringList>
#include <QDomDocument>
#include <QDomElement>


class DomXML
{
public:
    DomXML();

    static void createXML(QString filePath); //创建xml空文件
    //list.at(0) = 二汽神龙
    static void appendXML(QString filePath, QStringList list);
    static void writeXML(QDomDocument &doc, QDomElement &root, QStringList &list);

    static void readXML(QString filePath,
                        QStringList &fList,
                        QStringList &bList,
                        QStringList &pList,
                        QStringList &nList,
                        QStringList &tList

                        );

};

#endif // DOMXML_H



--  D:\project_c++\qt001\01_CarManage\domxml.cpp

#include "domxml.h"
#include <QFile>
#include <QDomDocument> //文件
#include <QDomProcessingInstruction> //格式头部
#include <QDomElement>  //元素
#include <QTextStream> //文件流
#include <QDebug>
#include <QDateTime>
#define cout qDebug() << "[" << __FILE__ << ":" << __LINE__ << "]"

DomXML::DomXML()
{

}

//创建xml空文件
void DomXML::createXML(QString filePath)
{
    QFile file(filePath); //关联文件名字
    if( true == file.exists() ) //如果存在不创建
    {
        cout << "文件已经存在";
        return;
    }
    else
    { //不存在才创建
        //只写方式打开文件
        bool isOk = file.open(QIODevice::WriteOnly);
        if(true == isOk)//如果打开成功
        {
            //创建xml文档对象
            QDomDocument doc;
            //创建xml头部格式 <?xml version='1.0' encoding='utf-8'?>
            QDomProcessingInstruction ins;
            ins = doc.createProcessingInstruction("xml", "version=\'1.0\' encoding=\'utf-8\'");
            //追加元素
            doc.appendChild(ins);

            //根节点元素
            QDomElement root = doc.createElement("日销售清单");
            doc.appendChild(root);

            //保存
            QTextStream stream(&file); //文本流关联文件
            doc.save(stream, 4); //4 缩进字符

            file.close(); //关闭文件

        }
        else
        {
            cout << "WriteOnly error";
            return;
        }
    }

}

void DomXML::appendXML(QString filePath, QStringList list)
{
    QFile file(filePath);
    bool isOk = file.open(QIODevice::ReadOnly);
    if(true == isOk) //打开成功
    {
        //file和xml文档对象关联
        QDomDocument doc;
        isOk = doc.setContent(&file);
        if(isOk) //如果关联成功
        {
            file.close(); //关闭文件
            //获取根节点元素
            QDomElement root = doc.documentElement();

            //获取当前时间
            QDateTime date = QDateTime::currentDateTime();
            QString dateStr = date.toString("yyyy-MM-dd"); //2016-01-08

            //判断根节点下有没有子节点
            if( root.hasChildNodes() ) //如果有子节点
            {
                //查找最后一个子节点
                QDomElement lastEmt = root.lastChildElement();
                if(lastEmt.attribute("date") == dateStr)
                {//有有当天日期
                    //写有效数据
                    writeXML(doc, lastEmt, list);

                }
                else //如果没有
                {
                    //创建日期子节点元素
                    QDomElement dateEmt = doc.createElement("日期");
                    //创建date属性
                    QDomAttr dateAttr = doc.createAttribute("date");
                    //设置属性的值
                    dateAttr.setNodeValue(dateStr);
                    //节点和属性关联
                    dateEmt.setAttributeNode(dateAttr);

                    //把日期节点追加到根节点上
                    root.appendChild(dateEmt);

                    //写有效数据
                    writeXML(doc, dateEmt, list);
                }

            }
            else //没有子节点
            {
               //创建日期子节点元素
               QDomElement dateEmt = doc.createElement("日期");
               //创建date属性
               QDomAttr dateAttr = doc.createAttribute("date");
               //设置属性的值
               dateAttr.setNodeValue(dateStr);
               //节点和属性关联
               dateEmt.setAttributeNode(dateAttr);

               //把日期节点追加到根节点上
               root.appendChild(dateEmt);

               //写有效数据
               writeXML(doc, dateEmt, list);

            }

            //保存文件
            isOk = file.open(QIODevice::WriteOnly);
            if(isOk)
            {
                QTextStream stream(&file);
                doc.save(stream, 4);
                file.close();

            }

        }
        else
        {
            cout << "setContent error";
            return;
        }


    }
    else
    {
        cout << "ReadOnly error";
    }

}

void DomXML::writeXML(QDomDocument &doc, QDomElement &root, QStringList &list)
{
    //获取当前时间
    QDateTime time = QDateTime::currentDateTime();
    QString timeStr = time.toString("hh-mm-ss"); //16:05:22

    //创建时间节点元素
    QDomElement timeEmt = doc.createElement("时间");
    //创建属性
    QDomAttr timeAttr = doc.createAttribute("time");
    //给属性设置值
    timeAttr.setNodeValue(timeStr);
    //时间节点元素和属性关联
    timeEmt.setAttributeNode(timeAttr);
    //把时间节点追击到日期节点后面
    root.appendChild(timeEmt);

    QDomElement factory = doc.createElement("厂家");
    QDomElement brand = doc.createElement("品牌");
    QDomElement price = doc.createElement("报价");
    QDomElement num = doc.createElement("数量");
    QDomElement total = doc.createElement("金额");


    QDomText text = doc.createTextNode(list.at(0));
    factory.appendChild(text);

    text = doc.createTextNode(list.at(1));
    brand.appendChild(text);

    text = doc.createTextNode(list.at(2));
    price.appendChild(text);

    text = doc.createTextNode(list.at(3));
    num.appendChild(text);

    text = doc.createTextNode(list.at(4));
    total.appendChild(text);


    timeEmt.appendChild(factory);
    timeEmt.appendChild(brand);
    timeEmt.appendChild(price);
    timeEmt.appendChild(num);
    timeEmt.appendChild(total);

}

void DomXML::readXML(QString filePath, QStringList &fList, QStringList &bList, QStringList &pList, QStringList &nList, QStringList &tList)
{
    QFile file(filePath);
    bool isOk = file.open(QIODevice::ReadOnly);
    if(true == isOk) //打开成功
    {
        //file和xml文档对象关联
        QDomDocument doc;
        isOk = doc.setContent(&file);

        if(isOk) //如果关联成功
        {
            //获取根节点
            QDomElement root = doc.documentElement();
            file.close();

            QDateTime date = QDateTime::currentDateTime();
            QString dateStr = date.toString("yyyy-MM-dd");


            if(root.hasChildNodes()) //有没有子节点
            {
                //找最后一个节点元素
                QDomElement lastEmt = root.lastChildElement();
                if(lastEmt.attribute("date") == dateStr)//判断有没有当天日期
                {
                    //找出当前日期下所有时间子节点
                    QDomNodeList list = lastEmt.childNodes();
                    for(int i = 0; i < list.size(); i++)
                    {
                        //list.at(0).toElement();
                        //转换为元素，找到时间节点下的所有子节点
                        QDomNodeList subList = list.at(i).toElement().childNodes();
                        //厂家
                        QString factory = subList.at(0).toElement().text();
                        fList.append(factory);

                        QString brand = subList.at(1).toElement().text();
                        bList.append(brand);

                        QString price = subList.at(2).toElement().text();
                        pList.append(price);

                        QString num = subList.at(3).toElement().text();
                        nList.append(num);

                        QString total = subList.at(4).toElement().text();
                        tList.append(total);
                    }


                }
                else
                {
                    cout << "没有当天日期";
                    return;
                }


            }
            else
            {
                cout << "没有子节点";
                return;
            }


        }
        else
        {
            cout << "setContent error";
            return;
        }
    }
    else
    {
        cout << "ReadOnly error";
        return;
    }

}




-- D:\project_c++\qt001\01_CarManage\histogram.h

#ifndef HISTOGRAM_H
#define HISTOGRAM_H

// Histogram.h 柱状图类的声明
// 名词解释：Histogram 柱状图
// pillar 柱子

#include <QVector>
#include <QWidget>

// 前向声明
QT_BEGIN_NAMESPACE
class QColor;
class QRect;
class QString;
class QPaintDevice;
QT_END_NAMESPACE

class HistogramItem
{
public:
	QString m_Name;
	qreal	m_Value;
	QColor	m_PillarColor;
	QRect	m_PillarRect;
};

class Histogram : public QWidget
{
public:
    Histogram( QWidget* parent = 0 );
	void AddItem( QString name, qreal value,
                  QColor pillarColor = QColor( qrand()%255, qrand()%255, qrand()%255 ));
	void SetMaxValue( quint32 maxValue );	// 设置最大值，以便绘图
	void Paint( QPaintDevice* pDevice );	// 绘图
    void Clear();   // 清空所有已添加的Item

protected:
    void paintEvent(QPaintEvent *);

private:
    void DrawAxis( QPaintDevice* pDevice, QPainter* pPainter );     // 绘制坐标轴
	void DrawPillars( QPaintDevice* pDevice, QPainter* pPainter );	// 绘制柱子
	void DrawText( QPainter *pPainter );		// 绘制文字
	void DrawScale( QPaintDevice* pDevice, QPainter* pPainter );	// 绘制刻度

	enum HistogramOptions
	{
		blankWidth		= 64,		// 两个柱子间的空格大小
		pillarIndent	= 0,		// 首个柱子缩进的大小
		xAxisOffset		= 16,		// X轴的偏移（相对于左边界）
		yAxisOffset		= 16,		// Y轴的偏移（相对于下边界）
		textRectHeight	= 32		// 文字矩形框的高
    };

	qreal							m_MaxValue;
	QVector<HistogramItem>			m_VecItems;
};

#endif // HISTOGRAM_H


-- D:\project_c++\qt001\01_CarManage\histogram.cpp

#include <QtGui>
#include "histogram.h"

Histogram::Histogram( QWidget* parent ) : QWidget(parent)
{
	m_VecItems.clear( );
}

void Histogram::AddItem( QString name, qreal value,
						 QColor pillarColor )
{
	HistogramItem item;
	item.m_Name			= name;
	item.m_Value		= value;
	item.m_PillarColor	= pillarColor;
	item.m_PillarRect	= QRect( );
	m_VecItems.push_back( item );

    this->update();
}

void Histogram::SetMaxValue( quint32 maxValue )
{
	m_MaxValue = maxValue;
}

void Histogram::Paint( QPaintDevice* pDevice )
{
	QPainter painter( pDevice );
	DrawAxis( pDevice, &painter );
	DrawPillars( pDevice, &painter );
	DrawText( &painter );
	DrawScale( pDevice, &painter );
}

void Histogram::DrawAxis( QPaintDevice* pDevice, QPainter* pPainter )
{
	pPainter->drawLine( yAxisOffset, 0, yAxisOffset, pDevice->height( ) );
	pPainter->drawLine( 0, pDevice->height( ) - xAxisOffset,
						pDevice->width( ), pDevice->height( ) - xAxisOffset );
}

void Histogram::DrawPillars( QPaintDevice* pDevice, QPainter* pPainter )	// 绘制柱子
{
	if ( m_VecItems.size( ) == 0 ) return;

	//const quint32 blankWidth = 64;		// 柱子间空格宽
	quint32 pillarWidth = ( pDevice->width( ) - yAxisOffset - pillarIndent
							- quint32( m_VecItems.size( ) - 1 ) * blankWidth )
			/ m_VecItems.size( );		// 柱子的宽

	// 绘制因子。绘制因子在绘制柱子的时候起着重要作用。
	// 根据比例公式：
	// pDevice->width( ) - xAxisOffset         pillarHeight
	// --------------------------------- = --------------------
	//              MaxValue                m_VecItem[0].value
	// 求出pillarHeight的值，但是左边的部分我们可以看作是一个绘制因子heightFact记录下来。
	// 计算时可以节约时间。
	qreal heightFact = qreal( pDevice->height( ) - xAxisOffset ) / m_MaxValue;

	for ( int i = 0; i < m_VecItems.size( ); ++i )
	{
		quint32 pillarHeight = m_VecItems[i].m_Value * heightFact;
		int leftUpX = yAxisOffset + pillarIndent + i * ( pillarWidth + blankWidth );
		int leftUpY = pDevice->height( ) - xAxisOffset - pillarHeight;
		QRect& rect = m_VecItems[i].m_PillarRect;

		rect.setRect( leftUpX, leftUpY, pillarWidth, pillarHeight );
		pPainter->setPen( QPen( m_VecItems[i].m_PillarColor ) );
		pPainter->setBrush( QBrush( m_VecItems[i].m_PillarColor ) );
		pPainter->drawRect( rect );
	}
}

void Histogram::DrawText( QPainter* pPainter )		// 绘制文字
{
	// 已经可以保证m_VecItems.[i].m_Rect.isNull( )为假
	// 即柱子所在的矩形框是一个有效的矩形框
	pPainter->setPen( QPen( QColor( 0, 0, 0 ) ) );
	for ( int i = 0; i < m_VecItems.size( ); ++i )
	{
		QRect rect( m_VecItems[i].m_PillarRect.left( ) - blankWidth / 2,
					m_VecItems[i].m_PillarRect.top( ) - textRectHeight,
					m_VecItems[i].m_PillarRect.width( ) + blankWidth,
					textRectHeight );

		const QString& text = QString( "%1(%2)" )
				.arg( m_VecItems[i].m_Name ).arg( m_VecItems[i].m_Value );
		pPainter->drawText( rect, Qt::AlignCenter, text );
	}
}

void Histogram::DrawScale( QPaintDevice *pDevice, QPainter *pPainter )		// 绘制刻度
{
	// 名词解释 MSWidth = Marked Scale Width，刻度宽
	// MSHeight = Marked Scale Height 刻度高
	const quint32 MSWidth			= 100;
	const quint32 MSHeight			= textRectHeight;
	const quint32 heightInterval
			= ( pDevice->height( ) - xAxisOffset ) / 4;

	for ( int i = 0; i < 4; ++i )
	{
		QRect rect( 0,
					i * heightInterval,
					MSWidth,
					MSHeight );
		pPainter->drawLine( yAxisOffset - 2,
							i * heightInterval,
							yAxisOffset + 2,
							i * heightInterval );
		pPainter->drawText(
					rect, Qt::AlignLeft, QString( "%1" )
					.arg( m_MaxValue * ( 4 - i ) / 4 ) );
	}

}

void Histogram::Clear()
{
    m_VecItems.clear();
}

void Histogram::paintEvent(QPaintEvent *)
{
    Paint(this);
}



-- D:\project_c++\qt001\01_CarManage\mainwindow.h

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void connectDB(); //连接数据库
    void initData(); //初始化

private slots:
    void on_actionCar_triggered();

    void on_actionCalc_triggered();

    void on_comboBoxFactory_currentIndexChanged(const QString &arg1);

    void on_comboBoxBrand_currentIndexChanged(const QString &arg1);

    void on_spinBox_valueChanged(int arg1);

    void on_buttonCancel_clicked();

    void on_buttonSure_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H



--  D:\project_c++\qt001\01_CarManage\mainwindow.cpp


#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QDebug>
#include "domxml.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //开始 车辆管理页面
    on_actionCar_triggered();

    //打开数据库
    connectDB();

    //初始化数据
    initData();

    DomXML::createXML("../demo.xml"); //创建空的xml文件

    ui->widgetH->AddItem("大众", 8);
    ui->widgetH->AddItem("奥丁", 9);
    ui->widgetH->AddItem("测试", 10);
     ui->widgetH->SetMaxValue(50);


}

MainWindow::~MainWindow()
{
    delete ui;
}

//车辆管理菜单
void MainWindow::on_actionCar_triggered()
{
    //切换到车辆管理页面
    ui->stackedWidget->setCurrentWidget(ui->car);
    ui->label->setText("车辆管理");
}

//销售统计菜单
void MainWindow::on_actionCalc_triggered()
{
    //切换到销售统计页面
    ui->stackedWidget->setCurrentWidget(ui->calc);
    ui->label->setText("销售统计");
}

//连接数据库
void MainWindow::connectDB()
{
    //添加数据库
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setUserName("root");
    db.setPassword("1");
    db.setDatabaseName("car");

    //打开数据库
    if(!db.open())
    {
        QMessageBox::warning(this, "数据库打开失败", db.lastError().text());
        return;
    }
}

//初始化数据
void MainWindow::initData()
{
    QSqlQueryModel *queryModel = new QSqlQueryModel(this); //新建模型
    queryModel->setQuery("select name from factory"); //sql语句

    ui->comboBoxFactory->setModel(queryModel);


    ui->labelLast->setText("0"); //剩余数量
    ui->lineEditTotal->setEnabled(false); //金额

}

//厂家下拉框槽函数
void MainWindow::on_comboBoxFactory_currentIndexChanged(const QString &arg1)
{
    if(arg1 == "请选择厂家")
    { //内容清空
        ui->comboBoxBrand->clear(); //品牌下拉框情况
        ui->lineEditPrice->clear(); //报价清空
        ui->labelLast->setText("0"); //剩余数量
        ui->lineEditTotal->clear(); //金额清空
        ui->spinBox->setValue(0);   //数量选择框
        ui->spinBox->setEnabled(false);
        ui->buttonSure->setEnabled(false);
    }
    else
    {
        ui->comboBoxBrand->clear(); //先清空
        QSqlQuery query;
        QString sql = QString("select name from brand where factory = '%1'").arg(arg1);
        //select name from brand where factory = '一汽大众'
        //执行sql语句
        query.exec(sql);

        //获取内容
        while( query.next() )
        {
            QString name = query.value(0).toString();
            ui->comboBoxBrand->addItem(name);
        }
        ui->spinBox->setEnabled(true);

    }

}

void MainWindow::on_comboBoxBrand_currentIndexChanged(const QString &arg1)
{

    QSqlQuery query;
    QString sql = QString("select price, last from brand where factory = '%1' and name = '%2'")
            .arg(ui->comboBoxFactory->currentText()) //厂家下拉框当前选中内容
            .arg(arg1);
    //select price, last from brand where factory = '一汽大众' and name = '奥迪A6';
    //执行sql语句
    query.exec(sql);

    //获取内容
    while( query.next() )
    {
        //报价
        int price = query.value("price").toInt();
        //剩余数
        int last = query.value("last").toInt();

        //更新到对应的空间
        ui->lineEditPrice->setText( QString::number(price) );
        ui->labelLast->setText( QString::number(last)  );

    }
}

//数据选择框槽函数
void MainWindow::on_spinBox_valueChanged(int arg1)
{
    //更新剩余数量
    //1)厂家
    QString factoryStr = ui->comboBoxFactory->currentText();
    //2)品牌
    QString brandStr = ui->comboBoxBrand->currentText();

    if(0 == arg1)
    {
        ui->buttonSure->setEnabled(false);
    }
    else
    {
        ui->buttonSure->setEnabled(true);
    }


    //获取数据库剩余数量
    QSqlQuery query;
    QString sql = QString("select last from brand where factory = '%1' and name = '%2'")
            .arg(factoryStr)
            .arg(brandStr);
    //执行数据库
    query.exec(sql);

    int last;
    while(query.next())
    {
        last = query.value("last").toInt(); //剩余
    }

    if(arg1 > last) //如果选择的数目大小，剩余数据，中断程序
    {
        ui->spinBox->setValue(last);
        return;
    }

    int tempNum = last - arg1;
    ui->labelLast->setText(  QString::number(tempNum)  ); //剩余数量
     //qDebug() << QString::number(tempNum);

    //金额
    int price = ui->lineEditPrice->text().toInt(); //报价
    int sum = price * arg1;
    ui->lineEditTotal->setText( QString::number(sum) );

}

void MainWindow::on_buttonCancel_clicked()
{
    //on_comboBoxFactory_currentIndexChanged("请选择厂家");
    ui->comboBoxFactory->setCurrentIndex(0);

    ui->labelLast->setText("0");

}

void MainWindow::on_buttonSure_clicked()
{


    //获取信息
    //1）销售数据
    int num = ui->spinBox->value();
    //2)剩余
    int last = ui->labelLast->text().toInt();

    //获取数据库的销量
    QSqlQuery query;
    QString sql = QString("select sell from brand where factory = '%1' and name = '%2'")
            .arg( ui->comboBoxFactory->currentText() )
            .arg( ui->comboBoxBrand->currentText() );
    //执行数据库
    query.exec(sql);

    int sell;
    while(query.next() )
    {
        sell = query.value("sell").toInt();
    }

    //更新数据库，剩余数量， 销售总量
    sell += num;

    sql = QString("update brand set sell = %1, last = %2 where factory = '%3' and name = '%4'")
                .arg(sell)
                .arg(last)
                .arg( ui->comboBoxFactory->currentText() )
                .arg( ui->comboBoxBrand->currentText() );

    query.exec(sql);

    //把确认后的数据，更新到xml中
    QStringList list;
    list << ui->comboBoxFactory->currentText()
         << ui->comboBoxBrand->currentText()
         << ui->lineEditPrice->text()
         << QString::number(num)
         << ui->lineEditTotal->text();
    DomXML::appendXML("../demo.xml", list);

    QStringList fList;
    QStringList bList;
    QStringList pList;
    QStringList nList;
    QStringList tList;
    DomXML::readXML("../demo.xml", fList, bList, pList, nList, tList);
    for(int i = 0; i < fList.size(); i++)
    {
        QString str = QString("%1:%2:卖出了%3,单价：%4, 总价: %5")
                .arg(fList.at(i))
                .arg(bList.at(i))
                .arg(nList.at(i))
                .arg(pList.at(i))
                .arg(tList.at(i));

        ui->textEdit->append(str);
        qDebug() << str.toUtf8().data();
    }

    ui->buttonSure->setEnabled(false);
    on_buttonCancel_clicked();

}


















