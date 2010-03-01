#ifndef XMLREADER_H
#define XMLREADER_H

#include "ui_mainwindow.h"


class XmlReader : public QObject
{
public:
    XmlReader(Ui_MainWindow* myMainWindow);
    ~XmlReader();
    QString errorString() const;

private:
    QXmlStreamReader xmlreader;
    Ui_MainWindow* ui;

public slots:
    //void xmlRead(QNetworkReply *device);
    void xmlRead(QIODevice* device);
    void xmlShow();

};

#endif // XMLREADER_H
