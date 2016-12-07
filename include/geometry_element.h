#ifndef GEOMETRYELEMENT_H
#define GEOMETRYELEMENT_H

#include <QString>
#include <QVector3D>



class GeometryElement
{
public:
    GeometryElement();
    ~GeometryElement();
protected:
    QString name;
    QVector3D vertex[];
};

#endif // GEOMETRYELEMENT_H
