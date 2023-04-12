#include "settingimageprovider.h"
#include <QPainter>
#include <QIcon>
#include <QGraphicsColorizeEffect>

SettingImageProvider::SettingImageProvider() :
    QQuickImageProvider(QQuickImageProvider::Image)
{

}

// id should be name of the icon in qrc:/breezebar/resources/icons
// "inherent size" should be 80
QImage SettingImageProvider::requestImage(const QString& id, QSize* size, const QSize& requestedSize)
{
    *size = QSize(80, 80);

    // create pixmap with icon
    QIcon icon(":/breezebar/resources/icons/" + id + ".svg");
    QImage output = icon.pixmap(80, 80).toImage();

    // iter through pixels and recolor to textColor (#F9F9F9)
    QColor newColor = QColor::fromString("#F9F9F9");
    for (int y = 0; y < output.height(); ++y) {
        QRgb *line = reinterpret_cast<QRgb*>(output.scanLine(y));
        for (int x = 0; x < output.width(); ++x) {
            QRgb &rgb = line[x];

            // optimize for most cases when alpha is 0 or 255 (reduces unnecessary multiplication)
            // this is all necessary as output's format is premultiplied alpha.
            if(qAlpha(rgb) == 0) {
                rgb = qRgba(0, 0, 0, 0);
            }
            else if(qAlpha(rgb) == 255) {
                rgb = qRgba(newColor.red(), newColor.green(), newColor.blue(), 255);
            }
            else {
                double alphaScale = qAlpha(rgb)/255.0;
                rgb = qRgba(
                    static_cast<int>(newColor.red()*alphaScale),
                    static_cast<int>(newColor.green()*alphaScale),
                    static_cast<int>(newColor.blue()*alphaScale),
                    qAlpha(rgb)
                );
            }
        }
    }

    return output;
}


