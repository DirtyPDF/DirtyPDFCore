#include <QEvent>
#include "ink_pen_tool.hpp"
using namespace DirtyPDFCore;



InkPenTool::InkPenTool(){
  m_annotation = 0;
}


InkPenTool::InkPenTool(const InkPenTool &inkPenTool){
  if (inkPenTool.m_annotation == 0){
    m_annotation = 0;
  } else {
    m_annotation = new Poppler::InkAnnotation;
    m_annotation->setInkPaths(inkPenTool.m_annotation->inkPaths());
  }
}


void InkPenTool::behavior(Page* page, const QMouseEvent &mouseEvent){
  if (mouseEvent.type() == QEvent::MouseButtonPress && mouseEvent.button() == Qt::LeftButton){
    QList<QLinkedList<QPointF> > paths;
    paths.append(QLinkedList<QPointF>());
    paths[0].append(mouseEvent.localPos());
    m_annotation = new Poppler::InkAnnotation;
    m_annotation->setInkPaths(paths);
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
