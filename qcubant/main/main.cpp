#include <QApplication>

#include <ui/cviz.h>

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    CViz cviz;
    cviz.show();
    return app.exec();
}

