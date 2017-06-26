#include "documents_manager.hpp"
using namespace DirtyPDFCore;



DocumentsManager* DocumentsManager::m_instance = NULL;


DocumentsManager::DocumentsManager(){
  m_currentDocument = NULL;
}


DocumentsManager* DocumentsManager::Instance(){
  if (m_instance == 0)
    m_instance = new DocumentsManager;

  return m_instance;
}


DocumentsManager::~DocumentsManager(){
  QList<Document*>::iterator it;
  for (it=m_openedDocuments.begin(); it != m_openedDocuments.end(); ++it)
    delete *it;
  m_instance = NULL;
}


Document* DocumentsManager::currentDocument(){
  return m_currentDocument;
}


QList<Document*> DocumentsManager::openedDocuments(){
  return m_openedDocuments;
}


int DocumentsManager::numDocuments(){
  return m_openedDocuments.size();
}


Document* DocumentsManager::document(int index){
  if (index >= 0 && index < numDocuments())
    return m_openedDocuments[index];

  return NULL;
}


Document* DocumentsManager::openDocument(const QUrl &filePath){
  Document* doc = Document::load(filePath);

  if (doc == NULL)
    return NULL;

  m_openedDocuments.append(doc);
  emit documentOpened(doc);
  return doc;
}


bool DocumentsManager::closeDocument(Document* document){
  int index = m_openedDocuments.indexOf(document);
  if (index == -1)
    return false;

  m_openedDocuments.removeAt(index);
  delete document;
  if (document == m_currentDocument)
    m_currentDocument = NULL;

  emit documentClosed(document);
  return true;
}


bool DocumentsManager::setCurrentDocument(Document* document){
  if (!m_openedDocuments.contains(document))
    return false;

  Document* old = m_currentDocument;
  m_currentDocument = document;
  emit currentDocumentChanged(old);
  return true;
}
