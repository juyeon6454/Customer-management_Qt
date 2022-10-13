#include "clientitem.h"

#include <QLabel>
#include <iostream>

using namespace std;

ClientItem::ClientItem(int clientId, QString clientName, QString phoneNumber, QString address, QString email)
{
    setText(0, QString::number(clientId));
    setText(1, clientName);
    setText(2, phoneNumber);
    setText(3, address);
    setText(4, email);
}

QString ClientItem::getClientName() const
{
    return text(1);
}

void ClientItem::setClientName(QString& clientId)
{
    setText(1, clientId);
}

QString ClientItem::getPhoneNumber() const
{
    return text(2);
}

void ClientItem::setPhoneNumber(QString& phoneNumber)
{
    setText(2, phoneNumber);    // c_str() --> const char*
}

QString ClientItem::getAddress() const
{
    return text(3);
}

void ClientItem::setAddress(QString& address)
{
    setText(3, address);
}

QString ClientItem::getEmail() const
{
    return text(4);
}

void ClientItem::setEmail(QString& email)
{
    setText(4, email);
}


int ClientItem::ClientId() const
{
    return text(0).toInt();
}

// Define copy assignment operator.
bool ClientItem::operator==(const ClientItem &other) const {
    return (this->text(1) == other.text(1));
}
