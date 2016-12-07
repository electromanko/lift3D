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
    int addTriangle(const QVector3D &p0, const QVector3D &p1, const QVector3D &p2, const QString &name);
    static QVector3D intersect(const QVector3D &x, const QVector3D &y, const QVector3D &a, const QVector3D &b, const QVector3D &c, int *accessory);
    static float angleBetween(QVector3D &x, QVector3D &y);
    static bool insidePolygon(const QVector3D &vIntersection, QVector3D poly[], long verticeCount);
    void draw (QOpenGLShaderProgram *program);

    class Element{
    public:
        enum Type {None, Line=GL_LINE_STRIP, Polyline, Triangle=GL_TRIANGLES} type;
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
