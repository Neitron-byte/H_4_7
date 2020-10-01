#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_serial = new QSerialPort;

    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()){
        m_ListComPorts.append(info.portName());
    }

    ui->BoudrateBox_Cal->addItem(QStringLiteral("9600"));
    ui->BoudrateBox_Cal->addItem(QStringLiteral("19200"));
    ui->BoudrateBox_Cal->addItem(QStringLiteral("38400"));
    ui->BoudrateBox_Cal->addItem(QStringLiteral("115200"));

    ui->DataBitsBox_Cal->addItem(QStringLiteral("5"));
    ui->DataBitsBox_Cal->addItem(QStringLiteral("6"));
    ui->DataBitsBox_Cal->addItem(QStringLiteral("7"));
    ui->DataBitsBox_Cal->addItem(QStringLiteral("8"));

    ui->ParityBox_Cal->addItem(tr("None"));
    ui->ParityBox_Cal->addItem(tr("Even"));
    ui->ParityBox_Cal->addItem(tr("Odd"));
    ui->ParityBox_Cal->addItem(tr("Mark"));
    ui->ParityBox_Cal->addItem(tr("Space"));

    ui->StopBitsBox_Cal->addItem(QStringLiteral("1"));
    ui->StopBitsBox_Cal->addItem(QStringLiteral("1.5"));
    ui->StopBitsBox_Cal->addItem(QStringLiteral("2"));


    ui->FlowControlBox_Cal->addItem(tr("None"));
    ui->FlowControlBox_Cal->addItem(tr("RTS/CTS"));
    ui->FlowControlBox_Cal->addItem(tr("XON/XOFF"));



    if(!m_ListComPorts.isEmpty()){
    for (const auto& Com : m_ListComPorts) {
        ui->SetComBox_Cal->addItem(Com);
    }
    }
    else{
        qDebug()<< "List is Empty";
    }

    ui->groupBox_2->setEnabled(false);

}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_serial;
}


void MainWindow::on_pushButton_clicked()
{

    struct SettingsComPort {
        QString m_name;
        uint m_baudRate;
        QSerialPort::DataBits m_dataBits;
        QSerialPort::Parity m_parity;
        QSerialPort::StopBits m_stopBits;
        QSerialPort::FlowControl m_flowControl;
    };
    //текущие настройки порта
    SettingsComPort m_SettingsCom;

    m_serial->setPortName(ui->SetComBox_Cal->currentText());
    m_serial->setBaudRate(ui->BoudrateBox_Cal->itemData(ui->BoudrateBox_Cal->currentIndex()).toUInt());

    m_serial->setDataBits(static_cast<QSerialPort::DataBits>(ui->DataBitsBox_Cal->itemData(ui->DataBitsBox_Cal->currentIndex()).toUInt()));
    m_serial->setParity(static_cast<QSerialPort::Parity>(ui->ParityBox_Cal->itemData(ui->ParityBox_Cal->currentIndex()).toUInt()));
    m_serial->setStopBits(static_cast<QSerialPort::StopBits>(ui->StopBitsBox_Cal->itemData(ui->StopBitsBox_Cal->currentIndex()).toUInt()));
    m_serial->setFlowControl(static_cast<QSerialPort::FlowControl>(ui->FlowControlBox_Cal->itemData(ui->FlowControlBox_Cal->currentIndex()).toUInt()));

    qDebug()<< m_serial->portName();

    if (m_serial->open(QIODevice::ReadWrite)) {

        isOpen = true;
        ui->groupBox_2->setEnabled(true);

    } else {



    }


}
