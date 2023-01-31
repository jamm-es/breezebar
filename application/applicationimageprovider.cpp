#include "applicationimageprovider.h"

ApplicationImageProvider::ApplicationImageProvider() :
    QQuickImageProvider(QQuickImageProvider::Image)
{

}

QImage ApplicationImageProvider::requestImage(const QString& id, QSize* size, const QSize& requestedSize)
{
    int index = id.toInt();
    QImage icon = images_.at(index);
    *size = icon.size();
    return icon;
}

int ApplicationImageProvider::addImage(QImage image)
{
    images_.push_back(image);
    return images_.size()-1;
}


