#include "include/geometry_element.h"

GeometryElement::GeometryElement()
{
    unsigned long vs = GeometryElement::getVSize();
    unsigned long is = GeometryElement::getVSize();
    if (vs>0) {
        this->vertex = new QVector3D[vs];
        this->index = new int[is];
    }
    else this->vertex = ((QVector3D*)0);
}

GeometryElement::~GeometryElement()
{
    delete [] this->vertex;
    delete [] this->index;
}

QVector3D* GeometryElement::getVertexP()
{
    return this->vertex;
}

void GeometryElement::setVertex(const QVector3D &vertex, unsigned long numVertex)
{
    if (numVertex<getVSize()){
        this->vertex[numVertex]= vertex;
    }
}

void GeometryElement::setIndex(int index, unsigned long num)
{
    if (num<getISize()){
        this->index[num]= index;
    }
}
