#include <QFile>
#include "document.hpp"
using namespace DirtyPDFCore;



Document* Document::load(const QUrl &filePath, const QByteArray &ownerPassword, const QByteArray &userPassword){
  Poppler::Document* document = Poppler::Document::load(filePath.toString(), ownerPassword, userPassword);

  if (document == NULL)
    return NULL;

  return new Document(document, filePath);
}


Document* Document::loadFromData(const QByteArray &fileContents, const QByteArray &ownerPassword, const QByteArray &userPassword){
  Poppler::Document* document = Poppler::Document::loadFromData(fileContents, ownerPassword, userPassword);

  if (document == NULL)
    return NULL;

  return new Document(document);
}


Document::Document(Poppler::Document* document, const QUrl &filePath){
  m_document = document;
  m_filePath = filePath;
}


Document::Document(const Document &document){}


Document::~Document(){
  delete m_document;
}


const QUrl& Document::path() const{
  return m_filePath;
}


bool Document::save(){
  return save(m_filePath);
}


bool Document::save(const QUrl& savePath){
  if (savePath.toString() == m_filePath.toString()){
    if(!QFile::remove(savePath.toString())){
      return false;
    }
  }

  bool saved;
  Poppler::PDFConverter* pdfConverter = m_document->pdfConverter();
  pdfConverter->setOutputFileName(savePath.toString());
  pdfConverter->setPDFOptions(pdfConverter->pdfOptions()|Poppler::PDFConverter::WithChanges);
  saved = pdfConverter->convert();
  delete pdfConverter;
  return saved;
}


int Document::numPages(){
  return m_document->numPages();
}


Page* Document::page(int index){
  return new Page(m_document->page(index));
}


QDomDocument* Document::toc(){
  return m_document->toc();
}
