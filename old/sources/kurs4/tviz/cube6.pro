TEMPLATE = app
TARGET = cube6
QT += core \
    gui \
    opengl
HEADERS += tmath/SimplexModel.h \
    tmath/Matrix3D.h \
    tmath/Rotator3D.h \
    tmath/Point3D.h \
    tmath/BitContainer.h \
    tmath/Cube3D.h \
    tmath/Vector3D.h \
    tmath/OctoCube.h \
    tmath/Line3D.h \
    tmath/EtalonDiags.h \
    visuals/VisualSimplex3D.h \
    visuals/VisualTriangle.h \
    visuals/VisualLine.h \
    visuals/VisualPoint.h \
    visuals/VisualEntity.h \
    Etc.h \
    Renderer.h \
    ChoiceDialog.h \
    MainWindowCube6.h
SOURCES += tmath/SimplexModel.cpp \
    tmath/Rotator3D.cpp \
    tmath/Point3D.cpp \
    tmath/Cube3D.cpp \
    tmath/OctoCube.cpp \
    tmath/Line3D.cpp \
    tmath/EtalonDiags.cpp \
    visuals/VisualSimplex3D.cpp \
    visuals/VisualTriangle.cpp \
    visuals/VisualLine.cpp \
    visuals/VisualPoint.cpp \
    visuals/VisualEntity.cpp \
    Etc.cpp \
    Renderer.cpp \
    ChoiceDialog.cpp \
    MainWindowCube6.cpp \
    cube6.cpp
FORMS += 
RESOURCES += 
