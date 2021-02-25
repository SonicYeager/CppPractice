#ifndef QMLADAPTER_H
#define QMLADAPTER_H
#endif // QMLADAPTER_H

#include <QObject>
#include <QAbstractListModel>

class QmlAdapter : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString data              READ getData                WRITE setData                NOTIFY dataChanged)
public:
    explicit QmlAdapter(QObject *parent = nullptr);

    //any specific backendtrigger

    QString getData();

    void setData(QString data);

public slots:

    //anything the ui asks for or triggers (interactions with backend process)

signals:
    void dataChanged();

private:
    QString _data = "";

};
