#ifndef _DPDFC_DOCUMENT_H
#define _DPDFC_DOCUMENT_H

#include <poppler-qt5.h>
#include <QString>
#include <QByteArray>



namespace DirtyPDFCore{
  class Document : Poppler::Document{
  public:
    typedef unsigned int Id;
    
  private:
    Id m_id;
    static Id count;

    static void initializeId(Document* document);

  public:
    static Document* load(const QString &filePath, const QByteArray &ownerPassword=QByteArray(),
                          const QByteArray &userPassword=QByteArray());
    static Document* loadFromData(const QByteArray &fileContents, const QByteArray
                                  &ownerPassword=QByteArray(), const QByteArray
                                  &userPassword=QByteArray());
    Id getId();
  };
}
#endif
