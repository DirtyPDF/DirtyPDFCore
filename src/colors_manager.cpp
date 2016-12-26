#include "colors_manager.hpp"
using namespace DirtyPDFCore;



ColorsManager* ColorsManager::m_instance = 0;


ColorsManager::ColorsManager(QObject* parent) : QObject(parent){
  m_color = QColor(0, 0, 0);
}


ColorsManager* ColorsManager::Instance(){
  if (m_instance == 0)
    m_instance = new ColorsManager;
  return m_instance;
}


void ColorsManager::setCurrentColor(const QColor &color){
  QColor oldColor = m_color;
  m_color = color;
  emit currentColorChanged(oldColor);
}


const QColor& ColorsManager::getCurrentColor() const{
  return m_color;
}
