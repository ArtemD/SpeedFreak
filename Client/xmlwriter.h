#ifndef XMLWRITER_H
#define XMLWRITER_H

#include "ui_mainwindow.h"


class XmlWriter : public QObject
{
public:
    XmlWriter(Ui_MainWindow* myMainWindow);
    ~XmlWriter();

private:
    QXmlStreamWriter xmlwriter;
    QMap<QString, int> resultmap;
    Ui_MainWindow* ui;

public slots:
    bool writeXmlFile(QIODevice* device);
    void writeItems();
    void initResultmap();
    void fillResultmap();
    void xmlWrite();

};

#endif // XMLWRITER_H
