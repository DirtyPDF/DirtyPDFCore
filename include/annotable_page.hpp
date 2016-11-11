#ifndef _DPDFC_ANNOTABLE_PAGE_H_
#define _DPDFC_ANNOTABLE_PAGE_H_

#include <poppler-qt5.h>
#include <QMouseEvent>
#include "tools_manager.hpp"



namespace DirtyPDFCore{
  class AnnotablePage : public Poppler::Page{
  private:
    ToolsManager* m_toolsManager;

  public:
    void handleMouseEvent(const QMouseEvent &mouseEvent);
  };
}
#endif
