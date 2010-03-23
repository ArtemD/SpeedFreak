/*
 *  Class for moving average of acceleration data.
 *
 * @author      Kai Rasilainen
 * @copyright   (c) 2010 Speed Freak team
 * @license     http://opensource.org/licenses/gpl-license.php GNU Public License
 */

#include "movingaverage.h"
#include <QList>

MovingAverage::MovingAverage(int sizeLimit)
{
    SizeLimit = sizeLimit;
}

double MovingAverage::Average()
{
    double sum = 0;

    if (queue.count() == 0)
        return 0;

    QList<double> temp = queue;
    foreach (double value, temp)
    {
        sum += value;
    }

    return sum / queue.count();
}

void MovingAverage::Resize(int sizeLimit)
{
    SizeLimit = sizeLimit;
    while (queue.count() > SizeLimit)
    {
        queue.dequeue();
    }
}

void MovingAverage::Enqueue(double item)
{
    queue.enqueue(item);
    if (queue.count() > SizeLimit)
        queue.dequeue();
}


