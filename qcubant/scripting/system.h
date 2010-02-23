#ifndef SYSTEM_H
#define SYSTEM_H


#include <QObject>
#include <QtScript>
#include <QtCore>

#include <scripting/qcubant.h>
#include <core/Cubant.hpp>

class QSystem : public QObject {
    Q_OBJECT
    public slots:
    signals:
        void printSignal(const QString& str);
        /// @todo add native cubant drawing.
        void drawCubantSignal(const std::string& cubant);
    public slots:
        void print(const QString& str);
        void drawCubantFromString(const QString& cubant);
        void drawCubant(QCubant* cubant);
};

#endif
