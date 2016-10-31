#include "history.hpp"
using namespace DirtyPDFCore;



History* History::m_instance = 0;


History::History(QObject* parent) : QUndoGroup(parent){}


History* History::Instance(){
  if (m_instance == 0)
    m_instance = new History;

  return m_instance;
}
