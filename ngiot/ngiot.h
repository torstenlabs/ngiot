#ifndef NGIOT_H
#define NGIOT_H

#include <QtGlobal>
#include <QtCore>
#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>


namespace Ui {
class ngiot;
}

class ngiot : public QMainWindow
{
    Q_OBJECT

public:
    explicit ngiot(QWidget *parent = 0);
    ~ngiot();

public slots:
    void openCOMPort();
    void closeCOMPort();
    void readCOMPortData();
    void checkRadioConditions();
    void startCheckingContinously();
    void stopCheckingContinously();
    void updateTime(int time);

private:
    void findCOMPorts();
    void createConnections();
    Ui::ngiot *ui;
    QSerialPort *serial;
    QSerialPortInfo *serialPortInfo;
    QTimer *timer;
    int time =1000;

};

#endif // NGIOT_H
