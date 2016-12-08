#ifndef GEOMETRYELEMENT_H
#define GEOMETRYELEMENT_H

#include <QString>
#include <QVector3D>
#include <QOpenGLFunctions>

class GeometryElement
{
    friend class  GeometryKernel;
public:
    GeometryElement();
    virtual ~GeometryElement();

    virtual int getType(){return 0;}
    virtual unsigned long getVSize(){return 0;}
    virtual unsigned long getISize(){return 0;}
    virtual int getGLMode(){return 0;}
    int id;
    QString name;

protected:

    QVector3D *vertex;
    int *index;

    void setVertex(const QVector3D &vertex, unsigned long numVertex);
    void setIndex(int index, unsigned long num);
    QVector3D getVertex(long count);

    QVector3D* getVertexP();
};

#endif // GEOMETRYELEMENT_H
