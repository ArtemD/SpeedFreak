/*
 *  Class for moving average of acceleration data.
 *
 * @author      Kai Rasilainen
 * @copyright   (c) 2010 Speed Freak team
 * @license     http://opensource.org/licenses/gpl-license.php GNU Public License
 */

#ifndef MOVINGAVERAGE_H
#define MOVINGAVERAGE_H

#include <QQueue>

class MovingAverage
{

public:
    MovingAverage(int sizeLimit);

    double Average();
    void Resize(int sizeLimit);
    void Enqueue(double item);

private:
    int SizeLimit;
    QQueue<double> queue;
};

#endif // MOVINGAVERAGE_H
