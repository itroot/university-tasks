#ifndef QCUBANT_H
#define QCUBANT_H

#include <core/Cubant.hpp>

#include <QObject>

#include <QtCore>

class QCubant : public QObject {
    Q_OBJECT
    public:
        QCubant(const QString& value);
    public slots:
        int dimension() const;
    private:
        CubantCore::cubant_t* cubant;
};

#endif
