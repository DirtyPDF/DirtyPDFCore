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


void History::addDocumentStack(Document* document){
  if (m_undoStacks.contains(document))
    return;

  QUndoStack* undoStack = new QUndoStack(this);
  m_undoStacks[document] = undoStack;
  QUndoGroup::addStack(undoStack);
}


void History::setActiveDocumentStack(Document* document){
  if (!m_undoStacks.contains(document))
    return;

  QUndoGroup::setActiveStack(m_undoStacks[document]);
}


void History::removeDocumentStack(Document* document){
  if (!m_undoStacks.contains(document))
    return;

  QUndoGroup::removeStack(m_undoStacks[document]);
  m_undoStacks.remove(document);
}


void History::activeCurrentDocumentStack(){
  DocumentsManager* doc_manager = DocumentsManager::Instance();
  setActiveDocumentStack(doc_manager->currentDocument());
}
