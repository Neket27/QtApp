#include "scaledpixmap.h"
#include <QPixmap>
#include <QtGui/QPainter>
ScaledPixmap::ScaledPixmap(QWidget *parent ):
    QLabel(parent)
{

}

void ScaledPixmap::setScaledPixmap(const QPixmap &pixmap)
{
    m_pixmap=pixmap;
    update();

}

void ScaledPixmap::loadPixmapData(const QString &path)
{

    QPixmap pixmap(path);
    const bool loaded=!pixmap.isNull();

    if(loaded)
        setScaledPixmap(pixmap);

}

void ScaledPixmap::paintEvent(QPaintEvent * const event)
{

    QPainter painter(this);

    if(!m_pixmap.isNull()){
        QPoint centerPoint(0,0);
        QSize scaledSize=size();
        QPixmap scaledPixmap=m_pixmap.scaled(scaledSize,Qt::KeepAspectRatio);
        centerPoint.setX((scaledSize.width()-scaledPixmap.width())/2);
        centerPoint.setY((scaledSize.height()-scaledPixmap.height())/2);


        painter.drawPixmap(centerPoint, scaledPixmap);
    }

    QLabel::paintEvent(event);
}
