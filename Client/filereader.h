/*
 * File reader class for reading acceleration data from file.
 *
 * @author      Jukka Kurttila <jktla@suomi24.fi>
 * @copyright   (c) 2010 Speed Freak team
 * @license     http://opensource.org/licenses/gpl-license.php GNU Public License
 */
#ifndef FILEREADER_H
#define FILEREADER_H

#include <QFile>

class filereader
{
public:
    filereader();
    ~filereader();
    void ReadLine( qreal &x, qreal &y, qreal &z );
    void setFileName(QString inputFileName);

private:
    QString fileName;
    QFile file;

};

#endif // FILEREADER_H
