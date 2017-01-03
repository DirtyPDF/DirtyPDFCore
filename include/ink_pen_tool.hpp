/**
 * @file ink_pen_tool.hpp
 * @brief Header file for the class InkPenTool
 */

#ifndef _DPDFC_INK_PEN_TOOL_H_
#define _DPDFC_INK_PEN_TOOL_H_

#include <poppler-qt5.h>
#include "tool.hpp"



namespace DirtyPDFCore{
  class InkPenTool : public ToolCRTP<InkPenTool>{
  private:
    Poppler::InkAnnotation* m_annotation;

  public:
    InkPenTool();

    InkPenTool(const InkPenTool &inkPenTool);

    void behavior(AnnotablePage* page, const QMouseEvent &mouseEvent);
  };
}
#endif
