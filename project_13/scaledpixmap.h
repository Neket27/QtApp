#ifndef SCALEDPIXMAP_H
#define SCALEDPIXMAP_H
#include <QtWidgets/QLabel>

QT_FORWARD_DECLARE_CLASS(QPaintEvent)

class ScaledPixmap : public QLabel
{
public:
    ScaledPixmap(QWidget *parent = Q_NULLPTR);


public slots:
void setScaledPixmap(const QPixmap& pixmap);
void loadPixmapData(const QString& path);

protected:
    void paintEvent(QPaintEvent *);

private:
    QPixmap m_pixmap;


};




#endif // SCALEDPIXMAP_H
