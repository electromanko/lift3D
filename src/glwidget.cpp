/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the QtCore module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "include/glwidget.h"

#include <QMouseEvent>

#include <math.h>



GlWidget::GlWidget(QWidget *parent) :
    QOpenGLWidget(parent),
    geometries(0),
    gKernel(0),
    texture(0),
    angularSpeed(0),
    translateScene(0,0,-5.0)
{
}

GlWidget::~GlWidget()
{
    // Make sure the context is current when deleting the texture
    // and the buffers.
    makeCurrent();
    delete texture;
    delete geometries;
    delete gKernel;
    doneCurrent();
}

//! [0]
void GlWidget::mousePressEvent(QMouseEvent *e)
{
    // Save mouse press position
    mousePressPosition = QVector2D(e->localPos());
    prevRrotation = rotation;
    qDebug() << QString("Buuu!");
}

void GlWidget::wheelEvent(QWheelEvent *event){

    if (event->delta()>0){
       translateScene.setZ(translateScene.z()+0.5);

    }
    else {
        translateScene.setZ(translateScene.z()-0.5);
    }
    // Set near plane to 3.0, far plane to 7.0, field of view 45 degrees

    // Request an update
    update();
    qDebug() << QString("%1").arg(translateScene.z());
}

void GlWidget::mouseReleaseEvent(QMouseEvent *e)
{
    /*
    // Mouse release position - mouse press position
    QVector2D diff = QVector2D(e->localPos()) - mousePressPosition;

    // Rotation axis is perpendicular to the mouse position difference
    // vector
    QVector3D n = QVector3D(diff.y(), diff.x(), 0.0).normalized();

    // Accelerate angular speed relative to the length of the mouse sweep
    qreal acc = diff.length() / 100.0;

    // Calculate new rotation axis as weighted sum
    rotationAxis = (rotationAxis * angularSpeed + n * acc).normalized();

    // Increase angular speed
    angularSpeed += acc;
    rotation = QQuaternion::fromAxisAndAngle(rotationAxis, angularSpeed) * rotation;
    update();
    */

}
//! [0]
//!

void GlWidget::mouseMoveEvent (QMouseEvent *event)
//! [13] //! [14]
{
    if (event->buttons()&Qt::MidButton){
        // Mouse release position - mouse press position
        QVector2D diff = QVector2D(event->pos()) - mousePressPosition;
        // Rotation axis is perpendicular to the mouse position difference
        // vector
        QVector3D n = QVector3D(diff.y(), diff.x(), 0.0).normalized();
        // angular value relative to the length of the mouse sweep
        qreal k = diff.length() / 5.0;
        // Calculate new rotation axis as weighted sum
        rotationAxis = (rotationAxis+ n*k).normalized();
        rotation = QQuaternion::fromAxisAndAngle(rotationAxis, k) *prevRrotation;
        update();

        qDebug() << QString("%1:%2").arg( QString::number(diff.x()), QString::number(diff.y()));
    }
if (event->buttons()&Qt::LeftButton){
        GLint viewport[4];
        GLfloat winX, winY, winZ;
        glGetIntegerv( GL_VIEWPORT, viewport );
        winX = (float)event->pos().x();
        //winY = (float)viewport[3] - (float)event->pos().y();
        winY = this->height() - (float)event->pos().y();

        //glReadPixels( winX, winY, 0, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ );
        //QVector3D worldPosition0 = QVector3D(winX, winY, 0).unproject(modelViewMatrix, projectionMatrix, QRect(viewport[0], viewport[1], viewport[2], viewport[3]));
        //QVector3D worldPosition1 = QVector3D(winX, winY, 1).unproject(modelViewMatrix, projectionMatrix, QRect(viewport[0], viewport[1], viewport[2], viewport[3]));
        QVector3D worldPosition0 = QVector3D(winX, winY, 0).unproject(modelViewMatrix, projectionMatrix, this->rect());
        QVector3D worldPosition1 = QVector3D(winX, winY, 1).unproject(modelViewMatrix, projectionMatrix, this->rect());
        //qDebug()<< QString("%1,%2,%3").arg(winX).arg(winY).arg(winZ);
        //QVector3D resultRay = worldPosition1-worldPosition0;

        //gKernel->addLine(worldPosition0,worldPosition1,QString("eee"));

        //gKernel->addLine(QVector3D(-1.5f,-1.5f,-1.5f),QVector3D(1.5f,1.5f,1.5f),QString("eee"));
        int acc;
        QVector3D itsect = GeometryKernel::intersect(worldPosition0, worldPosition1, QVector3D(-1.5f,-1.5f,-1.5f),QVector3D(1.5f,1.5f,1.5f),QVector3D(0.0f,1.5f,0.0f), &acc);
        qDebug()<< QString("%1,%2,%3").arg(itsect.x()).arg(itsect.y()).arg(itsect.z());
        gKernel->addLine(worldPosition0,itsect,QString("eee"));
        QVector3D poly[]={QVector3D(-1.5f,-1.5f,-1.5f),QVector3D(1.5f,1.5f,1.5f),QVector3D(0.0f,1.5f,0.0f)};
        bool ip = GeometryKernel::insidePolygon(itsect, poly, 3);
        //qDebug()<< QString("%1,%2,%3").arg(resultRay.x()).arg(resultRay.y()).arg(resultRay.z());
        qDebug()<< QString("Inside triangle: %1").arg(ip);
    }
}

//! [1]
void GlWidget::timerEvent(QTimerEvent *)
{
    /*
    // Decrease angular speed (friction)
    angularSpeed *= 0.99;

    // Stop rotation when speed goes below threshold
    if (angularSpeed < 0.01) {
        angularSpeed = 0.0;
    } else {
        // Update rotation
        rotation = QQuaternion::fromAxisAndAngle(rotationAxis, angularSpeed) * rotation;

        // Request an update
        update();
    }*/
}
//! [1]

void GlWidget::initializeGL()
{
    initializeOpenGLFunctions();

    glClearColor(0, 0, 0, 1);

    initShaders();
    initTextures();

//! [2]
    // Enable depth buffer
    glEnable(GL_DEPTH_TEST);

    // Enable back face culling
    glEnable(GL_CULL_FACE);
//! [2]

    geometries = new GeometryEngine;
    gKernel = new GeometryKernel;

    // Use QBasicTimer because its faster than QTimer
    timer.start(12, this);

    gKernel->addTriangle(QVector3D(-1.5f,-1.5f,-1.5f),QVector3D(1.5f,1.5f,1.5f),QVector3D(0.0f,1.5f,0.0f),QString("eee"));
}

//! [3]
void GlWidget::initShaders()
{
    // Compile vertex shader
    if (!program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vshader.glsl"))
        close();

    // Compile fragment shader
    if (!program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fshader.glsl"))
        close();

    // Link shader pipeline
    if (!program.link())
        close();

    // Bind shader pipeline for use
    if (!program.bind())
        close();
}
//! [3]

//! [4]
void GlWidget::initTextures()
{
    // Load cube.png image
    texture = new QOpenGLTexture(QImage(":/cube.png").mirrored());

    // Set nearest filtering mode for texture minification
    texture->setMinificationFilter(QOpenGLTexture::Nearest);

    // Set bilinear filtering mode for texture magnification
    texture->setMagnificationFilter(QOpenGLTexture::Linear);

    // Wrap texture coordinates by repeating
    // f.ex. texture coordinate (1.1, 1.2) is same as (0.1, 0.2)
    texture->setWrapMode(QOpenGLTexture::Repeat);
}
//! [4]

//! [5]
void GlWidget::resizeGL(int w, int h)
{
    // Calculate aspect ratio
    aspectScene = qreal(w) / qreal(h ? h : 1);

    // Set near plane to 3.0, far plane to 7.0, field of view 45 degrees
    const qreal zNear = 1.0, zFar = 40.0, fov = 45.0;

    // Reset projection
    projectionMatrix.setToIdentity();

    // Set perspective projection

    projectionMatrix.perspective(fov, aspectScene, zNear, zFar);
}
//! [5]

void GlWidget::paintGL()
{
    // Clear color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    texture->bind();

//! [6]
    // Calculate model view transformation
    modelViewMatrix.setToIdentity();
    //modelViewMatrix.translate(0.0, 0.0, -5.0);
    modelViewMatrix.translate(translateScene);
    modelViewMatrix.rotate(rotation);

    // Set modelview-projection matrix
    program.setUniformValue("mvp_matrix", projectionMatrix * modelViewMatrix);
//! [6]

    // Use texture unit 0 which contains cube.png
    program.setUniformValue("texture", 0);

    // Draw cube geometry
    geometries->drawCubeGeometry(&program);
    gKernel->draw(&program);

}
