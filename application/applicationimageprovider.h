#ifndef APPLICATIONIMAGEPROVIDER_H
#define APPLICATIONIMAGEPROVIDER_H

#include <QQuickImageProvider>

class ApplicationImageProvider : public QQuickImageProvider
{
public:
    ApplicationImageProvider();

    virtual QImage requestImage(const QString& id, QSize* size, const QSize& requestedSize) override;
    int addImage(QImage image); // returns index to be used as id for requestImage

private:
    QVector<QImage> images_;
};

#endif // APPLICATIONIMAGEPROVIDER_H
