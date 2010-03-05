#ifndef XMLWRITER_H
#define XMLWRITER_H

#include "ui_carmainwindow.h"


class XmlWriter : public QObject
{
public:
    XmlWriter(Ui_CarMainWindow* myMainWindow);
    ~XmlWriter();

private:
    QXmlStreamWriter xmlwriter;
    QMap<QString, int> resultmap;
    Ui_CarMainWindow* ui;

public slots:
    bool writeXmlFile(QIODevice* device);
    void writeItems();
    void fillResultmap();
    void writeXml();
    void writeRegister();
    void serverWritesTop();

};

#endif // XMLWRITER_H
