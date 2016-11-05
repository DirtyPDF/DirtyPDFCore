#include "document.hpp"
using namespace DirtyPDFCore;



Document::Id Document::invalidId = 0;


Document::Id Document::count = 0;


Document* Document::load(const QUrl &docUrl, const QByteArray &ownerPassword, const QByteArray &userPassword){
  Document* doc = (Document*) Poppler::Document::load(docUrl.path(), ownerPassword, userPassword);
  initializeId(doc);
  return doc;
}


Document* Document::loadFromData(const QByteArray &fileContents, const QByteArray &ownerPassword, const QByteArray &userPassword){
  Document* doc = (Document*) Poppler::Document::loadFromData(fileContents, ownerPassword, userPassword);
  initializeId(doc);
  return doc;
}


void Document::initializeId(Document* doc){
  if (doc != NULL){
    count++;
    doc->m_id = count;
  }
}


Document::Id Document::getId(){
  return m_id;
}
