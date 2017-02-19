#include <math.h>
#include <iostream>
#include "ink_annotation_manipulator.hpp"
using namespace DirtyPDFCore;



AnnotationManipulator* DirtyPDFCore::createAnnotationManipulator(Poppler::InkAnnotation* annotation){
  return new InkAnnotationManipulator(annotation);
}


InkAnnotationManipulator::InkAnnotationManipulator(Poppler::InkAnnotation* annotation){
  m_annotation = annotation;
}


QList<int> InkAnnotationManipulator::getSections(const QPointF& point, double radius){
  QList<int> sections;
  bool inSection;

  QList<QLinkedList<QPointF> > paths = m_annotation->inkPaths();
  QList<QLinkedList<QPointF> >::iterator it1;
  QLinkedList<QPointF>::iterator it2;
  int i=0;
  for (it1 = paths.begin(); it1 != paths.end(); i++, ++it1){
    inSection = false;
    if (it1->size() == 1){
      inSection = std::sqrt((it1->front().x() - point.x()) * (it1->front().x() - point.x()) +
                            (it1->front().y() - point.y()) * (it1->front().y() - point.y())) <= radius;
    } else {
      it2 = it1->begin();
      for (int k=1; k < it1->size() && !inSection; k++){
        QPointF point1 = *it2;
        ++it2;
        QPointF point2 = *it2;
        inSection = QVector2D(point).distanceToLine(QVector2D(point1), QVector2D(point1 - point2)) <= radius;
      }
    }
    if (inSection)
      sections.append(i);
  }
  return sections;
}


void InkAnnotationManipulator::applyTransform(const QTransform& transform){
  QList<QLinkedList<QPointF> > paths = m_annotation->inkPaths();
  QList<QLinkedList<QPointF> >::iterator it1;
  QLinkedList<QPointF>::iterator it2;
  for (it1 = paths.begin(); it1 != paths.end(); ++it1){
    for (it2 = it1->begin(); it2 != it1->end(); ++it2){
      *it2 = transform.map(*it2);
    }
  }
  m_annotation->setInkPaths(paths);
}


void InkAnnotationManipulator::applyTransformPart(const QTransform& transform, const QPointF& point, double radius){
  QList<int> sections = getSections(point, radius);

  QList<QLinkedList<QPointF> > paths = m_annotation->inkPaths();
  QList<int>::iterator it1;
  QLinkedList<QPointF>::iterator it2;
  for (it1 = sections.begin(); it1 != sections.end(); ++it1){
    for (it2 = paths[*it1].begin(); it2 != paths[*it1].end(); ++it2){
      *it2 = transform.map(*it2);
    }
  }
  m_annotation->setInkPaths(paths);
}


void InkAnnotationManipulator::erase(){
  QList<QLinkedList<QPointF> > empty_list;
  m_annotation->setInkPaths(empty_list);
}


void InkAnnotationManipulator::erasePart(const QPointF &point, double radius){
  QList<int> sections = getSections(point, radius);
  QList<QLinkedList<QPointF> > paths = m_annotation->inkPaths();
  int count = 0;
  for (QList<int>::iterator it=sections.begin(); it != sections.end(); ++it){
    paths.removeAt(*it - count);
    count++;
  }
  m_annotation->setInkPaths(paths);
}


void InkAnnotationManipulator::move(const QVector2D &vector){
  QList<QLinkedList<QPointF> >::iterator it1;
  QLinkedList<QPointF>::iterator it2;
  for (it1 = m_annotation->inkPaths().begin(); it1 != m_annotation->inkPaths().end(); ++it1){
    for (it2 = it1->begin(); it2 != it1->end(); ++it2){
      it2->setX(it2->x() + vector.x());
      it2->setY(it2->y() + vector.y());
    }
  }
}


void InkAnnotationManipulator::movePart(const QVector2D &vector, const QPointF &point){
  QList<int> sections = getSections(point);

  QList<QLinkedList<QPointF> > paths = m_annotation->inkPaths();
  QList<int>::iterator it1;
  QLinkedList<QPointF>::iterator it2;
  for (it1 = sections.begin(); it1 != sections.end(); ++it1){
    for (it2 = paths[*it1].begin(); it2 != paths[*it1].end(); ++it2){
      it2->setX(it2->x() + vector.x());
      it2->setY(it2->y() + vector.y());
    }
  }
  m_annotation->setInkPaths(paths);
}


void InkAnnotationManipulator::rotate(double angle, const QPointF &center){
  QTransform rotationTransform;
  rotationTransform.rotate(angle);

  QList<QLinkedList<QPointF> >::iterator it1;
  QLinkedList<QPointF>::iterator it2;
  for (it1 = m_annotation->inkPaths().begin(); it1 != m_annotation->inkPaths().end(); ++it1){
    for (it2 = it1->begin(); it2 != it1->end(); ++it2){
      *it2 = rotationTransform.map(*it2 - center) + center;
    }
  }
}


void InkAnnotationManipulator::rotatePart(double angle, const QPointF &center, const QPointF &point){
  QList<int> sections = getSections(point);
  QTransform rotationTransform;
  rotationTransform.rotate(angle);

  QList<QLinkedList<QPointF> > paths = m_annotation->inkPaths();
  QList<int>::iterator it1;
  QLinkedList<QPointF>::iterator it2;
  for (it1 = sections.begin(); it1 != sections.end(); ++it1){
    for (it2 = paths[*it1].begin(); it2 != paths[*it1].end(); ++it2){
      *it2 = rotationTransform.map(*it2 - center) + center;
    }
  }
  m_annotation->setInkPaths(paths);
}


void InkAnnotationManipulator::scale(double x, double y){
  QTransform scaleTransform;
  scaleTransform.scale(x, y);
  applyTransform(scaleTransform);
}


void InkAnnotationManipulator::scalePart(double x, double y, const QPointF &point){
  QTransform scaleTransform;
  scaleTransform.scale(x, y);
  applyTransformPart(scaleTransform, point);
}
