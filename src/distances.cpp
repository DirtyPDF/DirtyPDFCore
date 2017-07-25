#include "distances.hpp"



double DirtyPDFCore::distancePointToSegment(const QPointF& p, const QPointF& a, const QPointF& b, double (*distance)(const QPointF&, const QPointF&)){
  double u = ((p.x()-a.x()) * (b.x()-a.x()) + (p.y()-a.y()) * (b.y()-a.y()))/
             ((b.x()-a.x())*(b.x()-a.x()) + (b.y()-a.y())*(b.y()-a.y()));
  if (u <= 0){
    return distance(a, p);
  } else if (u >= 1){
    return distance(b, p);
  } else {
    // q is the orthogonal projection of p onto the segment [a, b]
    QPointF q = QPointF(a.x() + u*(b.x()-a.x()), a.y() + u*(b.y()-a.y()));
    return distance(p, q);
  }
}
