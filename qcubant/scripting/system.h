#ifndef SYSTEM_H
#define SYSTEM_H


#include <QObject>
#include <QtScript>
#include <QtCore>

#include <scripting/qcubant.h>
#include <core/Cubant.hpp>


/// @todo instead of using this object we can use CViz itself.
class QSystem : public QObject {
    Q_OBJECT
    public slots:
    signals:
        void printSignal(const QString& str);
        /// @todo add native cubant drawing.
        void drawCubantSignal(const std::string& cubant);
        void setReperSizeSignal(unsigned int);
        void setPenWidthSignal(unsigned int);
        void setColorSignal(unsigned int, unsigned int, unsigned int);
        void setImageSizeSignal(unsigned int, unsigned int);
        void setCubantStartSignal(unsigned int, unsigned int);
    public slots:
        void print(const QString& str);
        void drawCubantFromString(const QString& cubant);
        void drawCubant(QCubant* cubant);
        void setReperSize(unsigned int size);
        void setPenWidth(unsigned int width);
        void setColor(unsigned int, unsigned int, unsigned int);
        void setImageSize(unsigned int, unsigned int);
        void setCubantStart(unsigned int, unsigned int);
};

#endif
