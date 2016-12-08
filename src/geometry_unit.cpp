#include "include/geometry_unit.h"


GeometryUnitLine::GeometryUnitLine():GeometryElement()
{

}

GeometryUnitLine::GeometryUnitLine(const QVector3D &beginVerticles, const QVector3D &endVerticles):GeometryElement()
{
    setVertex(beginVerticles,0L);
    setVertex(endVerticles,1L);
    setIndex(0,0);
    setIndex(1,1);
}

GeometryUnitLine::~GeometryUnitLine()
{

}

int GeometryUnitLine::getType()
{
    return 1;
}

unsigned long GeometryUnitLine::getVSize()
{
    return 2;
}

unsigned long GeometryUnitLine::getISize()
{
    return 2;
}


int GeometryUnitLine::getGLMode()
{
    return GL_LINES;
}


GeometryUnitTriangle::GeometryUnitTriangle()
{

}

GeometryUnitTriangle::GeometryUnitTriangle(const QVector3D &beginVerticles, const QVector3D &endVerticles)
{

}

GeometryUnitTriangle::~GeometryUnitTriangle()
{

}

int GeometryUnitTriangle::getType()
{
    return 2;
}

unsigned long GeometryUnitTriangle::getVSize()
{
    return 3;
}

unsigned long GeometryUnitTriangle::getISize()
{
    return 3;
}

int GeometryUnitTriangle::getGLMode()
{
    return GL_TRIANGLES;
}
