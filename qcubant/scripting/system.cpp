#include <scripting/system.h>

using namespace CubantCore;

void
QSystem::
print(const QString& str) {
    emit printSignal(str);
}

void
QSystem::
drawCubantFromString(const QString& cubant) {
    emit drawCubantSignal(cubant.toStdString());
}

void
QSystem::
drawCubant(QCubant* cubant) {
    //QCubant* cubant=qscriptvalue_cast<QCubant*>(ctx->argument(0));
    //cubant->draw();
    //return QScriptValue();
    drawCubantFromString(cubant->getString());
}

void
QSystem::
setReperSize(unsigned int size) {
    emit setReperSizeSignal(size);
}
