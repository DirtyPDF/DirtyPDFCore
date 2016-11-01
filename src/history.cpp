#include "history.hpp"
using namespace DirtyPDFCore;



History* History::m_instance = 0;


History::History(QObject* parent) : QUndoGroup(parent){}


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
