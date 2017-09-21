#include "ngiot.h"
#include "ui_ngiot.h"

ngiot::ngiot(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ngiot)
{
    timer = new QTimer(this);
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
    QString myResult(readData);
    myResult.remove(QRegExp("[\\n\\t\\r]"));
    qDebug() << "Inhalt: " << myResult;
    ui->text->append(myResult);
}

void ngiot::checkRadioConditions()
{
    QString data = "AT+NUESTATS\r";
    ui->text->append("Reading radio conditions\n");
    qDebug() << "Geschrieben: " << serial->write(data.toUtf8());
}

void ngiot::startCheckingContinously()
{
    ui->text->append("Continously radion conditions Check started");
    timer->start(time);
}

void ngiot::stopCheckingContinously()
{
    timer->stop();
}

void ngiot::updateTime(int time)
{
    this->time = time;
    ui->text->append(QString("Timer updated to: %1").arg(time));
}

void ngiot::createConnections()
{
    connect(ui->buttonConnect,SIGNAL(clicked()),this,SLOT(openCOMPort()));
    connect(ui->buttonRadionConditions,SIGNAL(clicked()),this,SLOT(startCheckingContinously()));
    connect(serial, SIGNAL(readyRead()), this, SLOT(readCOMPortData()));
    connect(ui->buttonDisconnect,SIGNAL(clicked()),this,SLOT(closeCOMPort()));
    connect(timer, SIGNAL(timeout()), this, SLOT(checkRadioConditions()));
    connect(ui->buttonStopRadioConditionsCheck,SIGNAL(clicked()),this,SLOT(stopCheckingContinously()));
    connect(ui->sliderTime,SIGNAL(sliderMoved(int)),this,SLOT(updateTime(int)));
}
