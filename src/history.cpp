#include "history.hpp"
#include "documents_manager.hpp"
using namespace DirtyPDFCore;



History* History::m_instance = 0;


History::History(QObject* parent) : QUndoGroup(parent){
  DocumentsManager* doc_manager = DocumentsManager::Instance();
  connect(doc_manager, SIGNAL(documentOpened(DocumentId)), this, SLOT(addDocumentStack(DocumentId)));
  connect(doc_manager, SIGNAL(currentDocumentChanged(DocumentId)), this, SLOT(activeCurrentDocumentStack()));
  connect(doc_manager, SIGNAL(documentClosed(DocumentId)), this, SLOT(removeDocumentStack(DocumentId)));
}


History::~History(){
  m_instance = 0;
}


History* History::Instance(){
  if (m_instance == 0)
    m_instance = new History;

  return m_instance;
}


void History::addDocumentStack(DocumentId documentId){
  if (m_undoStacks.contains(documentId))
    QUndoGroup::removeStack(m_undoStacks[documentId]);

  QUndoStack* undoStack = new QUndoStack(this);
  m_undoStacks[documentId] = undoStack;
  QUndoGroup::addStack(undoStack);
}


void History::setActiveDocumentStack(DocumentId documentId){
  QUndoGroup::setActiveStack(m_undoStacks[documentId]);
}


void History::removeDocumentStack(DocumentId documentId){
  QUndoGroup::removeStack(m_undoStacks[documentId]);
  m_undoStacks.remove(documentId);
}


void History::activeCurrentDocumentStack(){
  DocumentsManager* doc_manager = DocumentsManager::Instance();
  setActiveDocumentStack(doc_manager->getCurrentDocument());
}
