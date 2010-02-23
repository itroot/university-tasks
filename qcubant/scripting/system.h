#ifndef SYSTEM_H
#define SYSTEM_H


#include <QObject>
#include <QtCore>

class QSystem : public QObject {
    Q_OBJECT
    signals:
        void printSignal(const QString& str);
    public slots:
        void print(const QString& str);
};

#endif
