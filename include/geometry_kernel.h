#ifndef GEOMETRYKERNEL_H
#define GEOMETRYKERNEL_H

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QVector2D>
#include <QVector3D>

class GeometryKernel : public QOpenGLFunctions
{
public:
    GeometryKernel();
    virtual ~GeometryKernel();

    int addLine(const QVector3D &p0, const QVector3D &p1, const QString &name);
    void draw (QOpenGLShaderProgram *program);

    class Element{
    public:
        enum Type {None, Line=GL_LINE_STRIP, Polyline, Triangle} type;
        Element(int i, Type t, QVector<QVector3D> *v, const QString &n);

        int id;
        QVector<QVector3D> *verticles;
        QString name;
    };

private:
    void updateBuffer();
    QOpenGLBuffer arrayBuf;
    QOpenGLBuffer indexBuf;
    QList<Element> elementsList;
};

#endif // GEOMETRYKERNEL_H
