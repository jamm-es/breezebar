#ifndef SETTINGIMAGEPROVIDER_H
#define SETTINGIMAGEPROVIDER_H

#include <QQuickImageProvider>

class SettingImageProvider : public QQuickImageProvider
{
public:
    SettingImageProvider();

    virtual QImage requestImage(const QString& id, QSize* size, const QSize& requestedSize) override;
};

#endif // SETTINGIMAGEPROVIDER_H
