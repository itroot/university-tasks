#include <scripting/system.h>

void
QSystem::
print(const QString& str) {
    emit printSignal(str);
}