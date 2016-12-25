#include <QtTest/QtTest>
#include <QList>
#include <QLinkedList>
#include <QPointF>
#include <iostream>
#include "ink_annotation_manipulator.hpp"
using namespace DirtyPDFCore;



class TestInkAnnotationManipulator : public QObject{
  Q_OBJECT

private:

  // Four straight lines defined by the points:
  // (0, 0), (1, 0)
  // (0, 2), (1, 2)
  // (0, 4), (1, 4)
  // (0, 6), (1, 6)
  Poppler::InkAnnotation* m_annotation;
  AnnotationManipulator* m_manipulator;

private slots:

  void init();
  void cleanup();
  void applyTransform();
  void applyTransformPart();
  void erase();
  void erasePart();
  void move();
  void movePart();
  void rotate();
  void rotatePart();
  void scale();
  void scalePart();
};



void TestInkAnnotationManipulator::init(){
  QList<QLinkedList<QPointF> > paths;
  for (int i=0; i < 4; i++){
    paths.append(QLinkedList<QPointF>());
    paths[i].append(QPointF(0, 2*i));
    paths[i].append(QPointF(1, 2*i));
  }
  m_annotation = new Poppler::InkAnnotation;
  m_annotation->setInkPaths(paths);
  m_manipulator = createAnnotationManipulator(m_annotation);
}


void TestInkAnnotationManipulator::cleanup(){
  delete m_manipulator;
  delete m_annotation;
}


void TestInkAnnotationManipulator::applyTransform(){
  QTransform transform(1, 1, 1, 1, 0, 0);
  m_manipulator->applyTransform(transform);

  QList<QLinkedList<QPointF> > paths = m_annotation->inkPaths();
  QLinkedList<QPointF>::iterator it = paths[0].begin();
  QCOMPARE(*it, QPointF(0, 0));
  ++it;
  QCOMPARE(*it, QPointF(1, 1));
  it = paths[1].begin();
  QCOMPARE(*it, QPointF(2, 2));
  ++it;
  QCOMPARE(*it, QPointF(3, 3));
  it = paths[2].begin();
  QCOMPARE(*it, QPointF(4, 4));
  ++it;
  QCOMPARE(*it, QPointF(5, 5));
  it = paths[3].begin();
  QCOMPARE(*it, QPointF(6, 6));
  ++it;
  QCOMPARE(*it, QPointF(7, 7));
}


void TestInkAnnotationManipulator::applyTransformPart(){
  QTransform transform(1, 1, 1, 1, 0, 0);
  m_manipulator->applyTransformPart(transform, QPoint(1/2.0, 0));

  QList<QLinkedList<QPointF> > paths = m_annotation->inkPaths();
  QLinkedList<QPointF>::iterator it = paths[0].begin();
  QCOMPARE(*it, QPointF(0, 0));
  ++it;
  QCOMPARE(*it, QPointF(1, 1));
  it = paths[1].begin();
  QCOMPARE(*it, QPointF(0, 2));
  ++it;
  QCOMPARE(*it, QPointF(1, 2));
  it = paths[2].begin();
  QCOMPARE(*it, QPointF(0, 4));
  ++it;
  QCOMPARE(*it, QPointF(1, 4));
  it = paths[3].begin();
  QCOMPARE(*it, QPointF(0, 6));
  ++it;
  QCOMPARE(*it, QPointF(1, 6));
}


void TestInkAnnotationManipulator::erase(){
  m_manipulator->erase();
  QVERIFY(m_annotation->inkPaths().empty());
}


void TestInkAnnotationManipulator::erasePart(){
  m_manipulator->erasePart(QPointF(1/2.0, 0), 0);
  QCOMPARE(m_annotation->inkPaths().size(), 3);
  QCOMPARE(m_annotation->inkPaths()[0].front().y(), 2.0);
  m_manipulator->erasePart(QPointF(1/2.0, 3), 1.2);
  QCOMPARE(m_annotation->inkPaths().size(), 1);
  QCOMPARE(m_annotation->inkPaths()[0].front().y(), 6.0);
}


void TestInkAnnotationManipulator::move(){
  m_manipulator->move(QVector2D(1,1));

  QList<QLinkedList<QPointF> > paths = m_annotation->inkPaths();
  QLinkedList<QPointF>::iterator it = paths[0].begin();
  QCOMPARE(*it, QPointF(1, 1));
  ++it;
  QCOMPARE(*it, QPointF(2, 1));
  it = paths[1].begin();
  QCOMPARE(*it, QPointF(1, 3));
  ++it;
  QCOMPARE(*it, QPointF(2, 3));
  it = paths[2].begin();
  QCOMPARE(*it, QPointF(1, 5));
  ++it;
  QCOMPARE(*it, QPointF(2, 5));
  it = paths[3].begin();
  QCOMPARE(*it, QPointF(1, 7));
  ++it;
  QCOMPARE(*it, QPointF(2, 7));
}


void TestInkAnnotationManipulator::movePart(){
  m_manipulator->movePart(QVector2D(1,1), QPointF(1/2.0, 2));

  QList<QLinkedList<QPointF> > paths = m_annotation->inkPaths();
  QLinkedList<QPointF>::iterator it = paths[0].begin();
  QCOMPARE(*it, QPointF(0, 0));
  ++it;
  QCOMPARE(*it, QPointF(1, 0));
  it = paths[1].begin();
  QCOMPARE(*it, QPointF(1, 3));
  ++it;
  QCOMPARE(*it, QPointF(2, 3));
  it = paths[2].begin();
  QCOMPARE(*it, QPointF(0, 4));
  ++it;
  QCOMPARE(*it, QPointF(1, 4));
  it = paths[3].begin();
  QCOMPARE(*it, QPointF(0, 6));
  ++it;
  QCOMPARE(*it, QPointF(1, 6));
}


void TestInkAnnotationManipulator::rotate(){
  m_manipulator->rotate(90, QPointF(0, 0));

  QList<QLinkedList<QPointF> > paths = m_annotation->inkPaths();
  QLinkedList<QPointF>::iterator it = paths[0].begin();
  QCOMPARE(*it, QPointF(0, 0));
  ++it;
  QCOMPARE(*it, QPointF(0, 1));
  it = paths[1].begin();
  QCOMPARE(*it, QPointF(-2, 0));
  ++it;
  QCOMPARE(*it, QPointF(-2, 1));
  it = paths[2].begin();
  QCOMPARE(*it, QPointF(-4, 0));
  ++it;
  QCOMPARE(*it, QPointF(-4, 1));
  it = paths[3].begin();
  QCOMPARE(*it, QPointF(-6, 0));
  ++it;
  QCOMPARE(*it, QPointF(-6, 1));
}


void TestInkAnnotationManipulator::rotatePart(){
  m_manipulator->rotatePart(90, QPointF(0, 0), QPointF(1/2.0, 4));

  QList<QLinkedList<QPointF> > paths = m_annotation->inkPaths();
  QLinkedList<QPointF>::iterator it = paths[0].begin();
  QCOMPARE(*it, QPointF(0, 0));
  ++it;
  QCOMPARE(*it, QPointF(1, 0));
  it = paths[1].begin();
  QCOMPARE(*it, QPointF(0, 2));
  ++it;
  QCOMPARE(*it, QPointF(1, 2));
  it = paths[2].begin();
  QCOMPARE(*it, QPointF(-4, 0));
  ++it;
  QCOMPARE(*it, QPointF(-4, 1));
  it = paths[3].begin();
  QCOMPARE(*it, QPointF(0, 6));
  ++it;
  QCOMPARE(*it, QPointF(1, 6));
}


void TestInkAnnotationManipulator::scale(){
  m_manipulator->scale(3, 2);

  QList<QLinkedList<QPointF> > paths = m_annotation->inkPaths();
  QLinkedList<QPointF>::iterator it = paths[0].begin();
  QCOMPARE(*it, QPointF(0, 0));
  ++it;
  QCOMPARE(*it, QPointF(3, 0));
  it = paths[1].begin();
  QCOMPARE(*it, QPointF(0, 4));
  ++it;
  QCOMPARE(*it, QPointF(3, 4));
  it = paths[2].begin();
  QCOMPARE(*it, QPointF(0, 8));
  ++it;
  QCOMPARE(*it, QPointF(3, 8));
  it = paths[3].begin();
  QCOMPARE(*it, QPointF(0, 12));
  ++it;
  QCOMPARE(*it, QPointF(3, 12));
}


void TestInkAnnotationManipulator::scalePart(){
  m_manipulator->scalePart(3, 2, QPointF(1/2.0, 6));

  QList<QLinkedList<QPointF> > paths = m_annotation->inkPaths();
  QLinkedList<QPointF>::iterator it = paths[0].begin();
  QCOMPARE(*it, QPointF(0, 0));
  ++it;
  QCOMPARE(*it, QPointF(1, 0));
  it = paths[1].begin();
  QCOMPARE(*it, QPointF(0, 2));
  ++it;
  QCOMPARE(*it, QPointF(1, 2));
  it = paths[2].begin();
  QCOMPARE(*it, QPointF(0, 4));
  ++it;
  QCOMPARE(*it, QPointF(1, 4));
  it = paths[3].begin();
  QCOMPARE(*it, QPointF(0, 12));
  ++it;
  QCOMPARE(*it, QPointF(3, 12));
}


QTEST_MAIN(TestInkAnnotationManipulator)
#include "test_ink_annotation_manipulator.moc"
