#include "history.hpp"
#include "documents_manager.hpp"
using namespace DirtyPDFCore;



History* History::m_instance = 0;


History::History(QObject* parent) : QUndoGroup(parent){
  DocumentsManager* doc_manager = DocumentsManager::Instance();
  connect(doc_manager, SIGNAL(documentOpened(Document::Id)), this, SLOT(addDocumentStack(Document::Id)));
  connect(doc_manager, SIGNAL(currentDocumentChanged(Document::Id)), this, SLOT(activeCurrentDocumentStack()));
  connect(doc_manager, SIGNAL(documentClosed(Document::Id)), this, SLOT(removeDocumentStack(Document::Id)));
}


History::~History(){
  m_instance = 0;
}


History* History::Instance(){
  if (m_instance == 0)
    m_instance = new History;

  return m_instance;
}


void History::addDocumentStack(Document::Id documentId){
  if (m_undoStacks.contains(documentId))
    QUndoGroup::removeStack(m_undoStacks[documentId]);

  QUndoStack* undoStack = new QUndoStack(this);
  m_undoStacks[documentId] = undoStack;
  QUndoGroup::addStack(undoStack);
}


void History::setActiveDocumentStack(Document::Id documentId){
  QUndoGroup::setActiveStack(m_undoStacks[documentId]);
}


void History::removeDocumentStack(Document::Id documentId){
  QUndoGroup::removeStack(m_undoStacks[documentId]);
  m_undoStacks.remove(documentId);
}


void History::activeCurrentDocumentStack(){
  DocumentsManager* doc_manager = DocumentsManager::Instance();
  setActiveDocumentStack(doc_manager->getCurrentDocument());
}
