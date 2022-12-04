#include "arduino.h"

Arduinoevent::Arduinoevent()
{
    data="";
    arduino_port_name_event="COM5";
    arduino_is_available=false;
    serial=new QSerialPort;
}
QString Arduinoevent::getarduino_port_name_event()
{
    return arduino_port_name_event;
}
QSerialPort *Arduinoevent::getserial_event()
{
   return serial;
}
int Arduinoevent::connect_arduino_event()
{   // recherche du port sur lequel la carte arduino identifée par  arduino_uno_vendor_id
    // est connectée
    foreach (const QSerialPortInfo &serial_port_info, QSerialPortInfo::availablePorts())
    {
           if(serial_port_info.hasVendorIdentifier() && serial_port_info.hasProductIdentifier()){
               if(serial_port_info.vendorIdentifier() == arduino_uno_vendor_id && serial_port_info.productIdentifier()
                       == arduino_uno_producy_id)
               {
                   arduino_is_available = true;
                   arduino_port_name_event=serial_port_info.portName();
               }
           }
    }
        qDebug() << "arduino_port_name is :" << arduino_port_name_event;
        if(arduino_is_available){
            serial->setPortName(arduino_port_name_event);
            if(serial->open(QSerialPort::ReadWrite)){
                serial->setBaudRate(QSerialPort::Baud9600); // débit : 9600 bits/s
                serial->setDataBits(QSerialPort::Data8); //Longueur des données : 8 bits,
                serial->setParity(QSerialPort::NoParity); //1 bit de parité optionnel
                serial->setStopBits(QSerialPort::OneStop); //Nombre de bits de stop : 1
                serial->setFlowControl(QSerialPort::NoFlowControl);
                return 0;
            }
            return 1;
        }
        return -1;
}
int Arduinoevent::close_arduino_event()
{
    if(serial->isOpen()){
            serial->close();
            return 0;
        }
    return 1;
}
 QByteArray Arduinoevent::read_from_arduino_event()
{
     QByteArray d=NULL;
    if(serial->isReadable()){
         data=serial->readAll(); //récupérer les données reçues

         return data;
    }
    else
        return d;
 }
int Arduinoevent::write_to_arduino_event( QByteArray d)
{
    if(serial->isWritable()){
        serial->write(d);  // envoyer des donnés vers Arduino
    }else{
        qDebug() << "Couldn't write to serial!";
    }
    return -1;
}
