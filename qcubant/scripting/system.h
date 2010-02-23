#ifndef SYSTEM_H
#define SYSTEM_H


#include <QObject>
#include <QtCore>

#include <scripting/qcubant.h>
#include <core/Cubant.hpp>

class QSystem : public QObject {
    Q_OBJECT
    signals:
        void printSignal(const QString& str);
        /// @todo add native cubant drawing.
        void drawCubantSignal(const std::string& cubant);
    public slots:
        void print(const QString& str);
        void drawCubant(const QString& cubant);
};

#endif
