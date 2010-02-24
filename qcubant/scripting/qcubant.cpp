#include <scripting/qcubant.h>

using namespace CubantCore;

QScriptValue
QCubant::
createCubant(QScriptContext *ctx, QScriptEngine *engine) {
    QString value=ctx->argument(0).toString();
    QCubant* qcubant=new QCubant(value);
    return engine->newQObject(qcubant, QScriptEngine::ScriptOwnership);
}

QScriptValue
QCubant::
cubantFacet(QScriptContext *context,
            QScriptEngine *engine)
{
    QCubant* qcubant=dynamic_cast<QCubant*>(context->argument(0).toQObject());
    if (NULL==qcubant) {
        throw std::runtime_error("Expected cubant!");
    }
    QScriptValue result=engine->newArray();
    cubant_t* cubant=qcubant->getCubant();
    unsigned int arrayIndex=0;
    for (size_t i=0;i<cubant->size();++i) {
        if (CubantType::Spread==(*cubant)[i].getType()) {
            cubant_t cubant0=*cubant;
            cubant_t cubant1=*cubant;
            cubant0[i].setType(CubantType::NoShift);
            cubant1[i].setType(CubantType::Shift);
            result.setProperty(arrayIndex, engine->newQObject(new QCubant(cubant0), QScriptEngine::ScriptOwnership));
            ++arrayIndex;
            result.setProperty(arrayIndex, engine->newQObject(new QCubant(cubant1), QScriptEngine::ScriptOwnership));
            ++arrayIndex;
        }
    }
    return result;
}

cubant_t*
QCubant::
getCubant() {
    return cubant;
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

QCubant::
QCubant(const cubant_t& _cubant) {
    cubant=new cubant_t(_cubant);
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

QCubant::
~QCubant() {
    delete cubant;
}



void
QCubant::
draw() {

}


