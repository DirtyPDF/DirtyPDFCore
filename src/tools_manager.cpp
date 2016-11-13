#include "tools_manager.hpp"
using namespace DirtyPDFCore;



ToolsManager* ToolsManager::m_instance = 0;


ToolsManager::ToolsManager(QObject* parent) : QObject(parent){}


ToolsManager::~ToolsManager(){
  m_instance = 0;
}


ToolsManager* ToolsManager::Instance(){
  if (m_instance == 0)
    m_instance = new ToolsManager;
  return m_instance;
}


Tool& ToolsManager::getCurrentTool(){
  return *m_currentTool;
}


void ToolsManager::useTool(const AnnotablePage* page, const QMouseEvent &mouseEvent){
  m_currentTool->behavior(page, mouseEvent);
}
