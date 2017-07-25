/**
 * @file page.hpp
 * @brief Header file for the class Page
 */

#ifndef _DPDFC_PAGE_H_
#define _DPDFC_PAGE_H_

#include <poppler-qt5.h>
#include "distances.hpp"



namespace DirtyPDFCore{

  class Page{
  private:

    Poppler::Page* m_page;

    Page();

    Page(const Page &page);

  public:

    ~Page();

    Page(Poppler::Page* page);

    operator Poppler::Page*();

    void addAnnotation(const Poppler::Annotation *ann);

    QList<Poppler::Annotation*> annotations() const;

    QList<Poppler::Annotation*> annotations(const QSet<Poppler::Annotation::SubType> &subtypes) const;

    QList<Poppler::Annotation*> annotationsByPosition(const QPointF &position, double radius=0, double (*distance)(const QPointF&, const QPointF&)=Distances::manhattan) const;

    QList<Poppler::Annotation*> annotationsByPosition(const QSet<Poppler::Annotation::SubType> &subtypes, const QPointF &position, double radius=0, double (*distance)(const QPointF&, const QPointF&)=Distances::manhattan) const;

    QSize pageSize() const;

    QSizeF pageSizeF() const;

    void removeAnnotation(const Poppler::Annotation *ann);

    QImage renderToImage(double xres=72.0, double yres=72.0, int x=-1, int y=-1, int w=-1, int h=-1, Poppler::Page::Rotation rotate=Poppler::Page::Rotate0) const;

    bool renderToPainter(QPainter *painter, double xres=72.0, double yres=72.0, int c=-1, int y=-1, int w=-1, int h=-1, Poppler::Page::Rotation rotate=Poppler::Page::Rotate0, Poppler::Page::PainterFlags flags=0) const;

    bool search(const QString &text, double &rectLeft, double &rectTop, double &rectRight, double &rectBottom, Poppler::Page::SearchDirection direction, Poppler::Page::SearchFlags flags=0, Poppler::Page::Rotation rotate=Poppler::Page::Rotate0) const;

    QList<QRectF> search(const QString &text, Poppler::Page::SearchFlags flags=0, Poppler::Page::Rotation rotate=Poppler::Page::Rotate0) const;

    QString text(const QRectF &rect, Poppler::Page::TextLayout textLayout) const;

    QString text(const QRectF &rect) const;

    QList<Poppler::TextBox*> textList(Poppler::Page::Rotation rotate=Poppler::Page::Rotate0) const;

    QImage thumbnail() const;
  };
}

#endif
