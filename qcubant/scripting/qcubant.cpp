#include <scripting/qcubant.h>

using namespace CubantCore;

QScriptValue
QCubant::
createCubant(QScriptContext *ctx, QScriptEngine *engine) {
    QString value=ctx->argument(0).toString();
    QCubant* qcubant=new QCubant(value);
    return engine->newQObject(qcubant, QScriptEngine::ScriptOwnership);
}

static QScriptValue cubantHull(QScriptContext *context,
                               QScriptEngine *engine)
{
    QCubant* qcubant=dynamic_cast<QCubant*>(context->argument(1).toQObject());
    if (NULL==qcubant) {
        throw std::runtime_error("Expected cubant!");
    }
    // here we must to create an array.
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

QString
QCubant::
getString() const {
    return QString::fromStdString(cubant->toString());
}

QString
QCubant::
toString() const {
    return getString();
}



void
QCubant::
draw() {
    
}


