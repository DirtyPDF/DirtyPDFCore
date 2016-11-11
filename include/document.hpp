#ifndef _DPDFC_DOCUMENT_H
#define _DPDFC_DOCUMENT_H

#include <poppler-qt5.h>
#include <QString>
#include <QByteArray>
#include <QUrl>
#include "annotable_page.hpp"



namespace DirtyPDFCore{
  class Document : public Poppler::Document{
  public:
    typedef unsigned int Id;
    static Id invalidId;

  private:
    Id m_id;
    static Id count;

    static void initializeId(Document* document);

  public:
    static Document* load(const QUrl &docUrl, const QByteArray &ownerPassword=QByteArray(),
                          const QByteArray &userPassword=QByteArray());
    static Document* loadFromData(const QByteArray &fileContents, const QByteArray
                                  &ownerPassword=QByteArray(), const QByteArray
                                  &userPassword=QByteArray());
    Id getId();

    AnnotablePage* page(int index) const;

    AnnotablePage* page(const QString &label) const;
  };
}
#endif
