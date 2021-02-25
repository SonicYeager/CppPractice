#include "qmladapter.h"

QmlAdapter::QmlAdapter(QObject *parent) : QObject(parent)
{}

QString QmlAdapter::getData()
{
    return _data;
}

void QmlAdapter::setData(QString data)
{
    _data = data;
}
