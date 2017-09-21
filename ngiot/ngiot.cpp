#include "ngiot.h"
#include "ui_ngiot.h"

ngiot::ngiot(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ngiot)
{

    serial = new QSerialPort(this);
    serialPortInfo = new QSerialPortInfo();
    ui->setupUi(this);
    createConnections();
    findCOMPorts();
}

ngiot::~ngiot()
{
    delete ui;
}

void ngiot::findCOMPorts()
{
    foreach (QSerialPortInfo portInfo, serialPortInfo->availablePorts()) {
           ui->comboBoxCOMPorts->addItem(portInfo.portName());
    }

}

void ngiot::openCOMPort()
{
    QString selection;
    selection = ui->comboBoxCOMPorts->currentText();
    foreach(QSerialPortInfo portInfo,serialPortInfo->availablePorts())
    {
        if(portInfo.portName().contains(selection))
        {
            serial->setBaudRate(QSerialPort::Baud9600);
            serial->setPortName(selection);
            qDebug() <<__FUNCTION__<< "Rückgabe: " << serial->open(QIODevice::ReadWrite);

        }
    }


}

void ngiot::closeCOMPort()
{
   serial->close();
}

void ngiot::readCOMPortData()
{
    qDebug() << __FUNCTION__ << "called";
    QByteArray readData = serial->readAll();
    qDebug() << "Inhalt: " << QTextCodec::codecForMib(1015)->toUnicode(readData);
}

void ngiot::checkRadioConditions()
{
    QString data = "AT\n\r";
    qDebug() << "Geschrieben: " << serial->write(data.toUtf8());
}

void ngiot::createConnections()
{
    connect(ui->buttonConnect,SIGNAL(clicked()),this,SLOT(openCOMPort()));
    connect(ui->buttonRadionConditions,SIGNAL(clicked()),this,SLOT(checkRadioConditions()));
    connect(serial, SIGNAL(readyRead()), this, SLOT(readCOMPortData()));
    connect(ui->buttonDisconnect,SIGNAL(clicked()),this,SLOT(closeCOMPort()));
}
