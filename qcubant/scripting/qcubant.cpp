#include <scripting/qcubant.h>

using namespace CubantCore;

QScriptValue
QCubant::
createCubant(QScriptContext *ctx, QScriptEngine *engine) {
    QString value=ctx->argument(0).toString();
    QCubant* qcubant=new QCubant(value);
    return engine->newQObject(qcubant, QScriptEngine::ScriptOwnership);
}

QCubant::
QCubant(QObject* qObject)
    : QObject(qObject)
{
    cubant=new cubant_t();
}


QCubant::
QCubant(const QString& value) {
    cubant=new cubant_t(value.toStdString());
}

int
QCubant::
dimension() const {
    return cubant->size();
}