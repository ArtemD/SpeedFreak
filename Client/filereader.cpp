/*
 * File reader class for reading acceleration data from file.
 *
 * @author      Jukka Kurttila <jktla@suomi24.fi>
 * @copyright   (c) 2010 Speed Freak team
 * @license     http://opensource.org/licenses/gpl-license.php GNU Public License
 */
#include "filereader.h"
#include <QFileDialog>

filereader::filereader()
{
}
filereader::~filereader()
{
    if(!fileName.isEmpty())
        file.close();
}

void filereader::ReadLine( qreal &x, qreal &y, qreal &z )
{
    if(fileName.isEmpty())
        return;
    QString line = file.readLine();

    //Get x

    std::string line2(line.toUtf8());

    line2.erase(0,line2.find_first_of("x"));
    line2.erase(0,3);

    std::string temp = line2.substr(0,line2.find_first_of(" "));

    QString temp2( temp.c_str() );
    x = temp2.toFloat();

    //Get y

    line2.erase(0,line2.find_first_of("y"));
    line2.erase(0,3);

    temp = line2.substr(0,line2.find_first_of(" "));

    temp2 = temp.c_str();
    y = temp2.toFloat();

    //Get z

    line2.erase(0,line2.find_first_of("z"));
    line2.erase(0,3);

    //Is there space character?
    if(line2.find_first_of(" ") != std::string::npos)
    {
        temp = line2.substr(0,line2.find_first_of(" "));
    }
    else
    {
        temp = line2;
    }

    //temp = line2.substr(0,line2.find_first_of(" "));

    temp2 = temp.c_str();
    z = temp2.toFloat();
}
void filereader::setFileName(QString inputFileName)
{
    fileName = inputFileName;
    file.setFileName(fileName);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug("File open failed.\n");
        return;
    }
    qDebug("File open Ok.\n");
}
