#include <scripting/system.h>

using namespace CubantCore;

void
QSystem::
print(const QString& str) {
    emit printSignal(str);
}

void
QSystem::
drawCubant(const QString& cubant) {
    emit drawCubantSignal(cubant.toStdString());
}

