#include "documents_manager.hpp"
using namespace DirtyPDFCore;



DocumentsManager* DocumentsManager::m_instance = 0;


DocumentsManager::DocumentsManager(){
  m_currentDocumentId = Document::invalidId;
}


DocumentsManager* DocumentsManager::Instance(){
  if (m_instance == 0)
    m_instance = new DocumentsManager;

  return m_instance;
}


DocumentsManager::~DocumentsManager(){
  QHash<Document::Id, Document*>::iterator it;
  for (it=m_openedDocuments.begin(); it != m_openedDocuments.end(); ++it)
    delete it.value();
  m_instance = 0;
}


Document::Id DocumentsManager::getCurrentDocument(){
  return m_currentDocumentId;
}


QList<Document::Id> DocumentsManager::getOpenedDocuments(){
  return m_openedDocuments.keys();
}


Document* DocumentsManager::getDocumentById(Document::Id documentId){
  if (documentId == Document::invalidId || !m_openedDocuments.contains(documentId))
    return NULL;
  return m_openedDocuments[documentId];
}


Document::Id DocumentsManager::openDocument(const QUrl &docUrl){
  Document* doc = Document::load(docUrl);
  if (doc == NULL)
    return Document::invalidId;

  m_openedDocuments[doc->getId()] = doc;
  emit documentOpened(doc->getId());
  return doc->getId();
}


void DocumentsManager::closeDocument(const Document::Id documentId){
  if (m_openedDocuments.contains(documentId)){
    delete m_openedDocuments[documentId];
    m_openedDocuments.remove(documentId);
    m_currentDocumentId = Document::invalidId;
    emit documentClosed(documentId);
  }
}


void DocumentsManager::setCurrentDocument(const Document::Id documentId){
  if (m_openedDocuments.contains(documentId)){
    Document::Id old = m_currentDocumentId;
    m_currentDocumentId = documentId;
    emit currentDocumentChanged(old);
  }
}
