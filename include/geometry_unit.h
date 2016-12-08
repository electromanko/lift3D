#ifndef GEOMETRY_UNIT_H
#define GEOMETRY_UNIT_H

#include "include/geometry_element.h"
#include <QVector3D>
#include <QOpenGLFunctions>

class GeometryUnitLine : public GeometryElement
{

public:
    GeometryUnitLine();
    GeometryUnitLine(const QVector3D &beginVerticles, const QVector3D &endVerticles);

    virtual ~GeometryUnitLine();

    // GeometryElement interface
public:
    int getType();
    unsigned long getVSize();
    unsigned long getISize();
    int getGLMode();
};

class GeometryUnitTriangle : public GeometryElement
{

public:
    GeometryUnitTriangle();
    GeometryUnitTriangle(const QVector3D &beginVerticles, const QVector3D &endVerticles);

    virtual ~GeometryUnitTriangle();

    // GeometryElement interface
public:
    int getType();
    unsigned long getVSize();
    unsigned long getISize();
    int getGLMode();
};

#endif // GEOMETRY_UNIT_H
