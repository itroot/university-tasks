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
        QCubant(const CubantCore::cubant_t& cubant);
        ~QCubant();
        // maybe later it will be real js constructor
        // maybe we need to move this into qsystem
        static QScriptValue createCubant(QScriptContext *context,
                                         QScriptEngine *engine);
        static QScriptValue cubantFacet(QScriptContext *context,
                                        QScriptEngine *engine);
        CubantCore::cubant_t* getCubant();
    public slots:
        int dimension() const;
        void draw();
        QString getString() const;
        QString toString() const;
    private:
        CubantCore::cubant_t* cubant;
};

#endif
