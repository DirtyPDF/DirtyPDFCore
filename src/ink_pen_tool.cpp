#include <QEvent>
#include <poppler-qt5.h>
#include "ink_pen_tool.hpp"
using namespace DirtyPDFCore;



InkPenTool::InkPenTool() : PenTool(){
  m_annotation = 0;
  setColor(QColor(235, 99, 98));
  setWidth(1);
}


InkPenTool::InkPenTool(const InkPenTool &inkPenTool){
  if (inkPenTool.m_annotation == 0){
    m_annotation = 0;
  } else {
    m_annotation = new Poppler::InkAnnotation;
    m_annotation->setInkPaths(inkPenTool.m_annotation->inkPaths());
  }

  setColor(inkPenTool.color());
  setWidth(inkPenTool.width());
}


void InkPenTool::behavior(Page* page, const QMouseEvent &mouseEvent){
  if (mouseEvent.type() == QEvent::MouseButtonPress && mouseEvent.button() == Qt::LeftButton){
    QList<QLinkedList<QPointF> > paths;
    paths.append(QLinkedList<QPointF>());
    paths[0].append(mouseEvent.localPos());
    m_annotation = new Poppler::InkAnnotation;
    m_annotation->setInkPaths(paths);
    Poppler::Annotation::Style style;
    style.setColor(color());
    style.setWidth(width());
    m_annotation->setStyle(style);
    page->addAnnotation(m_annotation);

  } else if (mouseEvent.type() == QEvent::MouseMove && m_annotation != 0){
    QList<QLinkedList<QPointF> > paths = m_annotation->inkPaths();
    paths[0].append(mouseEvent.localPos());
    m_annotation->setInkPaths(paths);

  } else if (mouseEvent.type() == QEvent::MouseButtonRelease && mouseEvent.button() == Qt::LeftButton){
    delete m_annotation;
    m_annotation = 0;
  }
}
