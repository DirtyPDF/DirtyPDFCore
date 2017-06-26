/**
 * @file document.hpp
 * @brief Header file for the class Document
 */

#ifndef _DPDFC_DOCUMENT_H_
#define _DPDFC_DOCUMENT_H_

#include <poppler-qt5.h>
#include <QUrl>
#include "page.hpp"



namespace DirtyPDFCore{

  class Document{
    friend class DocumentsManager;

  private:

    Poppler::Document* m_document;

    QUrl m_filePath;

    Document(const Document &document);


  protected:

    static Document* load(const QUrl &filePath, const QByteArray &ownerPassword=QByteArray(), const QByteArray &userPassword=QByteArray());

    static Document* loadFromData(const QByteArray &fileContents, const QByteArray &ownerPassword=QByteArray(), const QByteArray &userPassword=QByteArray());

    Document(Poppler::Document* document, const QUrl &filePath=QUrl());

    ~Document();

    Poppler::Document* toPopplerDocument();


  public:

    const QUrl& path() const;

    bool save();

    bool save(const QUrl& savePath);

    int numPages();

    Page* page(int index);

    QDomDocument* toc();
  };
}

#endif
