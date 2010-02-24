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

void
QSystem::
setPenWidth(unsigned int width) {
    emit setPenWidthSignal(width);
}

void
QSystem::
setColor(unsigned int R, unsigned int G, unsigned int B) {
    emit setColorSignal(R,G,B);
}

void
QSystem::
setImageSize(unsigned int x, unsigned int y) {
    emit setImageSizeSignal(x,y);
}

void
QSystem::
setCubantStart(unsigned int x, unsigned int y) {
    emit setCubantStartSignal(x,y);
}

void
QSystem::
setReper2DVector(unsigned int num, int x, int y) {
    emit setReper2DVectorSignal(num, x, y);
}


