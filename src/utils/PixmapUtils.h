#ifndef PIXMAPUTILS_H
#define PIXMAPUTILS_H

#include <QPixmap>
#include <QPainter>
#include <QString>
#include <QColor>

namespace PixmapUtils {
        inline QPixmap recolorPixmap(const QString &path, const QColor &color) {
            QPixmap pixmap(path);
            QPixmap colored(pixmap.size());
            colored.fill(Qt::transparent);

            QPainter painter(&colored);
            painter.setCompositionMode(QPainter::CompositionMode_Source);
            painter.drawPixmap(0, 0, pixmap);
            painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
            painter.fillRect(colored.rect(), color);
            painter.end();

            return colored;
        };

inline QPixmap createCircularPixmap(const QString &image, int size = 220) {
        QPixmap pixmap(image);
        if (pixmap.isNull()) return QPixmap();
        pixmap = pixmap.scaled(size, size, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);

        QPixmap rounded(pixmap.size());
        rounded.fill(Qt::transparent);

        QPainter painter(&rounded);
        painter.setRenderHint(QPainter::Antialiasing);
        QPainterPath path;
        path.addEllipse(0, 0, rounded.width(), rounded.height());
        painter.setClipPath(path);
        painter.drawPixmap(0, 0, pixmap);
        painter.end();

        return rounded;
    };
}

#endif // PIXMAPUTILS_H