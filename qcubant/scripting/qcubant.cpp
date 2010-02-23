#include <scripting/qcubant.h>

using namespace CubantCore;

QCubant::
QCubant(const QString& value) {
    cubant=new cubant_t(value.toStdString());
}

int
QCubant::
dimension() const {
    return cubant->size();
}