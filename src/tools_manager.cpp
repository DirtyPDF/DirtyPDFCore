#include "tools_manager.hpp"
using namespace DirtyPDFCore;



ToolsManager* ToolsManager::m_instance = 0;


ToolsManager::ToolsManager(QObject* parent) : QObject(parent){
  m_currentTool = 0;
  m_oldTool = 0;
}


ToolsManager::~ToolsManager(){
  m_instance = 0;
}


ToolsManager* ToolsManager::Instance(){
  if (m_instance == 0)
    m_instance = new ToolsManager;
  return m_instance;
}


void ToolsManager::setCurrentTool(const Tool &tool){
  m_oldTool = m_currentTool;
  m_currentTool = tool.clone();
  emit currentToolChanged(*m_oldTool);
}


Tool& ToolsManager::getCurrentTool(){
  return *m_currentTool;
}


void ToolsManager::useTool(const AnnotablePage* page, const QMouseEvent &mouseEvent){
  m_currentTool->behavior(page, mouseEvent);
}
