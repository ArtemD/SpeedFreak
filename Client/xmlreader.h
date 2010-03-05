#ifndef XMLREADER_H
#define XMLREADER_H

#include <QXmlStreamReader>
#include <QStringList>

class XmlReader : public QObject
{
public:
    XmlReader();
    ~XmlReader();
    QStringList getTop10List();
    QString getTop10AccelerationList();
    QString getTop10SpeedList();
    QString getTop10GforceList(); 

private:
    QXmlStreamReader xmlreader;
    QStringList top10List;
    QString top10AccelerationList;
    QString top10SpeedList;
    QString top10GforceList;

    QXmlStreamAttributes attr;
    QString category;
    QString unit;
    QString description;
    QString position;
    QString user;
    QString value;

public slots:
    void xmlRead(QIODevice* device);
    void xmlShow();
};

#endif // XMLREADER_H
