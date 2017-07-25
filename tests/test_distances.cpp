#include <QtTest/QtTest>
#include <QObject>
#include <cmath>
#include "distances.hpp"
using namespace DirtyPDFCore;



class TestDistances : public QObject{
  Q_OBJECT
  QList<QPointF> points1;
  QList<QPointF> points2;

private slots:

  void init();
  void euclidean();
  void maximum();
  void manhattan();
  void test_distancePointToSegment();
};


void TestDistances::init(){
    points1.push_back(QPointF(0, 0));
    points2.push_back(QPointF(0, 0));

    points1.push_back(QPointF(0, 0));
    points2.push_back(QPointF(1, 1));

    points1.push_back(QPointF(-2, -1));
    points2.push_back(QPointF(1, 2));
}


void TestDistances::euclidean(){
  QCOMPARE(Distances::euclidean(points1[0], points2[0]), 0.0);
  QCOMPARE(Distances::euclidean(points1[1], points2[1]), sqrt(2));
  QCOMPARE(Distances::euclidean(points1[2], points2[2]), sqrt(18));
}


void TestDistances::maximum(){
  QCOMPARE(Distances::maximum(points1[0], points2[0]), 0.0);
  QCOMPARE(Distances::maximum(points1[1], points2[1]), 1.0);
  QCOMPARE(Distances::maximum(points1[2], points2[2]), 3.0);
}


void TestDistances::manhattan(){
  QCOMPARE(Distances::manhattan(points1[0], points2[0]), 0.0);
  QCOMPARE(Distances::manhattan(points1[1], points2[1]), 2.0);
  QCOMPARE(Distances::manhattan(points1[2], points2[2]), 6.0);
}


void TestDistances::test_distancePointToSegment(){
  const QPointF& a = points1[2];
  const QPointF& b = points2[2];

  // Using euclidean distance
  QCOMPARE(distancePointToSegment(QPointF(-3,-1), a, b, Distances::euclidean), Distances::euclidean(QPointF(-3,-1), a));
  QCOMPARE(distancePointToSegment(QPointF(-2.5,0), a, b, Distances::euclidean), Distances::euclidean(QPointF(-2.5,0), QPointF(-1.75,-0.75)));
  QCOMPARE(distancePointToSegment(a, a, b, Distances::euclidean), 0.0);
  QCOMPARE(distancePointToSegment(QPointF(-1,0), a, b, Distances::euclidean), 0.0);

  // Using maximum distance
  QCOMPARE(distancePointToSegment(QPointF(-3,-1), a, b, Distances::maximum), Distances::maximum(QPointF(-3,-1), a));
  QCOMPARE(distancePointToSegment(QPointF(-2.5,0), a, b, Distances::maximum), Distances::maximum(QPointF(-2.5,0), QPointF(-1.75,-0.75)));
  QCOMPARE(distancePointToSegment(a, a, b, Distances::maximum), 0.0);
  QCOMPARE(distancePointToSegment(QPointF(-1,0), a, b, Distances::maximum), 0.0);

  // Using manhattan distance
  QCOMPARE(distancePointToSegment(QPointF(-3,-1), a, b), Distances::manhattan(QPointF(-3,-1), a));
  QCOMPARE(distancePointToSegment(QPointF(-2.5,0), a, b), Distances::manhattan(QPointF(-2.5,0), QPointF(-1.75,-0.75)));
  QCOMPARE(distancePointToSegment(a, a, b), 0.0);
  QCOMPARE(distancePointToSegment(QPointF(-1,0), a, b), 0.0);
}


QTEST_MAIN(TestDistances)
#include "test_distances.moc"
