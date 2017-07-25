#include <math.h>
#include "annotation_manipulator.hpp"
#include "rubber_pen_tool.hpp"
using namespace DirtyPDFCore;



RubberPenTool::RubberPenTool(){
  setWidth(0.01);
  m_annotationsSubTypes.insert(Poppler::Annotation::AInk);
}


RubberPenTool::RubberPenTool(const RubberPenTool &rubberPenTool){
  setWidth(rubberPenTool.width());
  m_annotationsSubTypes = rubberPenTool.m_annotationsSubTypes;
}


void RubberPenTool::behavior(Page* page, const QMouseEvent &mouseEvent){
  QList<Poppler::Annotation*> inkAnnotations = page->annotationsByPosition(m_annotationsSubTypes, mouseEvent.localPos(), width()); //page->annotationByPositon(mouseEvent.localPos(), m_annotationsSubTypes)
  AnnotationManipulator* manipulator;

  QList<Poppler::Annotation*>::iterator it;
  for (it = inkAnnotations.begin(); it != inkAnnotations.end(); ++it){
    page->removeAnnotation(*it);
  }
}
