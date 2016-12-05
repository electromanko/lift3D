#include "include/geometry_kernel.h"
#include <QVector2D>
#include <QVector3D>

struct VertexData
{
    QVector3D position;
    QVector2D texCoord;
};

GeometryKernel::GeometryKernel()
    : indexBuf(QOpenGLBuffer::IndexBuffer)
{
    initializeOpenGLFunctions();

    // Generate 2 VBOs
    arrayBuf.create();
    indexBuf.create();

}

GeometryKernel::~GeometryKernel()
{
    arrayBuf.destroy();
    indexBuf.destroy();
}

int GeometryKernel::addLine(const QVector3D &p0, const QVector3D &p1, const QString &name)
{
    QVector<QVector3D> *vert= new QVector<QVector3D>();
    vert->append(QVector3D(p0));
    vert->append(QVector3D(p1));
    this->elementsList.append(Element(0,Element::Type::Line, vert, name));
    updateBuffer();
    return 0;
}

void GeometryKernel::updateBuffer()
{
    QList<Element>::iterator i;
    int sizeVerticles=0;
    int bufOffset=0;
    VertexData vd;

    // Transfer vertex data to VBO 0
    arrayBuf.bind();
    //arrayBuf.allocate(vertices, 24 * sizeof(VertexData));


    for (i = elementsList.begin(); i != elementsList.end(); ++i){

        Element e = *i;
        sizeVerticles += e.verticles->size();
    }
    arrayBuf.allocate( sizeVerticles * sizeof(VertexData));
    for (i = elementsList.begin(); i != elementsList.end(); ++i){
        Element e = *i;
        QVector<QVector3D>::iterator iv;
        for (iv = e.verticles->begin(); iv != e.verticles->end(); ++iv){
            vd.position=*iv;
            vd.texCoord[0]=vd.texCoord[1]=0;
            arrayBuf.write(bufOffset, &vd,1*sizeof(VertexData));
            bufOffset+=sizeof(VertexData);
        }
    }
    // Transfer index data to VBO 1
    //indexBuf.bind();
    //indexBuf.allocate(indices, 34 * sizeof(GLushort));
}

void GeometryKernel::draw(QOpenGLShaderProgram *program)
{
    // Tell OpenGL which VBOs to use
    arrayBuf.bind();
    //indexBuf.bind();
    int vertOffset=0;

    // Offset for position
    quintptr offset = 0;

    // Tell OpenGL programmable pipeline how to locate vertex position data
    int vertexLocation = program->attributeLocation("a_position");
    program->enableAttributeArray(vertexLocation);
    program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(VertexData));

    // Offset for texture coordinate
    offset += sizeof(QVector3D);

    // Tell OpenGL programmable pipeline how to locate vertex texture coordinate data
    int texcoordLocation = program->attributeLocation("a_texcoord");
    program->enableAttributeArray(texcoordLocation);
    program->setAttributeBuffer(texcoordLocation, GL_FLOAT, offset, 2, sizeof(VertexData));

    // Draw cube geometry using indices from VBO 1
    //glDrawElements(GL_TRIANGLE_STRIP, 34, GL_UNSIGNED_SHORT, 0);
    QList<Element>::iterator i;
    for (i = elementsList.begin(); i != elementsList.end(); ++i){
        Element e = *i;
        glDrawArrays(e.type, vertOffset, e.verticles->length());
        vertOffset+=e.verticles->length();
    }
}

GeometryKernel::Element::Element(int i, GeometryKernel::Element::Type t, QVector<QVector3D> *v, const QString &n)
{
    this->id=i;
    this->type=t;
    this->verticles= v;
    this->name= n;
}