#include <iostream>
#include <QImage>
#include "page.hpp"
#include "annotation_manipulator.hpp"
using namespace DirtyPDFCore;



Page::Page(){}


Page::Page(const Page &page){}


Page::Page(Poppler::Page* page){
  m_page = page;
}


Page::~Page(){
  delete m_page;
}


Page::operator Poppler::Page*(){
  return m_page;
}


void Page::addAnnotation(const Poppler::Annotation *ann){
  m_page->addAnnotation(ann);
}


QList<Poppler::Annotation*> Page::annotations() const{
  return m_page->annotations();
}


QList<Poppler::Annotation*> Page::annotations(const QSet<Poppler::Annotation::SubType> &subtypes) const{
  return m_page->annotations(subtypes);
}


QList<Poppler::Annotation*> Page::annotationsByPosition(const QPointF &position, double radius, double (*distance)(const QPointF&, const QPointF&)) const{
  return annotationsByPosition(QSet<Poppler::Annotation::SubType>(), position, radius, distance);
}


QList<Poppler::Annotation*> Page::annotationsByPosition(const QSet<Poppler::Annotation::SubType> &subtypes, const QPointF &position, double radius, double (*distance)(const QPointF&, const QPointF&)) const{
  QList<Poppler::Annotation*> annList = annotations(subtypes);
  bool inside;

  for (QList<Poppler::Annotation*>::iterator it=annList.begin(); it != annList.end();){
    inside = false;
    if ((*it)->subType() == Poppler::Annotation::AInk){
      inside = InkAnnotationManipulator::isInside((Poppler::InkAnnotation*)*it, position, radius, distance);
    }
    if (!inside){
      it = annList.erase(it);
    } else {
      ++it;
    }
  }

  return annList;
}


QSize Page::pageSize() const{
  return m_page->pageSize();
}


QSizeF Page::pageSizeF() const{
  return m_page->pageSizeF();
}


void Page::removeAnnotation(const Poppler::Annotation *ann){
  m_page->removeAnnotation(ann);
}


QImage Page::renderToImage(double xres, double yres, int x, int y, int w, int h, Poppler::Page::Rotation rotate) const{
  return m_page->renderToImage(xres, yres, x, y, w, h, rotate);
}


bool Page::renderToPainter(QPainter *painter, double xres, double yres, int c, int y, int w, int h, Poppler::Page::Rotation rotate, Poppler::Page::PainterFlags flags) const{
  return m_page->renderToPainter(painter, xres, yres, c, y, w, h, rotate, flags);
}


bool Page::search(const QString &text, double &rectLeft, double &rectTop, double &rectRight, double &rectBottom, Poppler::Page::SearchDirection direction, Poppler::Page::SearchFlags flags, Poppler::Page::Rotation rotate) const{
  return m_page->search(text, rectLeft, rectTop, rectRight, rectBottom, direction, flags, rotate);
}


QList<QRectF> Page::search(const QString &text, Poppler::Page::SearchFlags flags, Poppler::Page::Rotation rotate) const{
  return m_page->search(text, flags, rotate);
}


QString Page::text(const QRectF &rect, Poppler::Page::TextLayout textLayout) const{
  return m_page->text(rect, textLayout);
}


QString Page::text(const QRectF &rect) const{
  return m_page->text(rect);
}


QList<Poppler::TextBox*> Page::textList(Poppler::Page::Rotation rotate) const{
  return m_page->textList(rotate);
}


QImage Page::thumbnail() const{
  return m_page->thumbnail();
}
