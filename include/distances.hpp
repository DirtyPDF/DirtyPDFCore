#ifndef _DPDFC_DISTANCES_H_
#define _DPDFC_DISTANCES_H_

#include <cmath>
#include <QPointF>



namespace DirtyPDFCore{
  namespace Distances{

    inline double euclidean(const QPointF& p1, const QPointF& p2){
      return sqrt((p1.x()-p2.x())*((p1.x()-p2.x())) + (p1.y()-p2.y())*((p1.y()-p2.y())));
    }

    inline double maximum(const QPointF& p1, const QPointF& p2){
      return fmax(abs(p1.x() - p2.x()), abs(p1.y() - p2.y()));
    }

    inline double manhattan(const QPointF&p1, const QPointF& p2){
      return (p1-p2).manhattanLength();
    }
  }

  double distancePointToSegment(const QPointF& point, const QPointF& segmentPoint1, const QPointF& segmentPoint2, double (*distance)(const QPointF&, const QPointF&)=Distances::manhattan);
}
#endif
