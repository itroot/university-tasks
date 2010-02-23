#ifndef QCUBANT_H
#define QCUBANT_H

#include <core/Cubant.hpp>

#include <QObject>
#include <QtScript>
#include <QtCore>

class QCubant : public QObject {
    Q_OBJECT
    public:
        QCubant(QObject* qObject);
        QCubant(const QString& value);
        // maybe later it will be real js constructor
        static QScriptValue createCubant(QScriptContext *context,
                                     QScriptEngine *engine);
    public slots:
        int dimension() const;
    private:
        CubantCore::cubant_t* cubant;
};

#endif
