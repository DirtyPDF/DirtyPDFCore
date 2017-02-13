#include "documents_manager.hpp"
using namespace DirtyPDFCore;



DocumentsManager* DocumentsManager::m_instance = 0;


DocumentsManager::DocumentsManager(){
  m_currentDocumentId = INVALID_DOCUMENT_ID;
}


DocumentId DocumentsManager::generateNewId(){
  static DocumentId lastId = 0;
  lastId++;
  return lastId;
}


DocumentsManager* DocumentsManager::Instance(){
  if (m_instance == 0)
    m_instance = new DocumentsManager;

  return m_instance;
}


DocumentsManager::~DocumentsManager(){
  QHash<DocumentId, Document*>::iterator it;
  for (it=m_openedDocuments.begin(); it != m_openedDocuments.end(); ++it)
    delete it.value();
  m_instance = 0;
}


int DocumentsManager::getDocumentsNumber(){
  return m_openedDocuments.size();
}


DocumentId DocumentsManager::getCurrentDocument(){
  return m_currentDocumentId;
}


QList<DocumentId> DocumentsManager::getOpenedDocuments(){
  return m_openedDocuments.keys();
}


Document* DocumentsManager::getDocumentById(DocumentId documentId){
  if (documentId == INVALID_DOCUMENT_ID || !m_openedDocuments.contains(documentId))
    return NULL;
  return m_openedDocuments[documentId];
}


DocumentId DocumentsManager::openDocument(const QUrl &docUrl){
  Document* doc = Document::load(docUrl.toString());
  if (doc == NULL)
    return INVALID_DOCUMENT_ID;

  DocumentId documentId = generateNewId();
  m_openedDocuments[documentId] = doc;
  emit documentOpened(documentId);
  return documentId;
}


void DocumentsManager::closeDocument(const DocumentId documentId){
  if (m_openedDocuments.contains(documentId)){
    delete m_openedDocuments[documentId];
    m_openedDocuments.remove(documentId);
    m_currentDocumentId = INVALID_DOCUMENT_ID;
    emit documentClosed(documentId);
  }
}


void DocumentsManager::setCurrentDocument(const DocumentId documentId){
  if (m_openedDocuments.contains(documentId)){
    DocumentId old = m_currentDocumentId;
    m_currentDocumentId = documentId;
    emit currentDocumentChanged(old);
  }
}
