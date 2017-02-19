/**
 * @file ink_pen_tool.hpp
 * @brief Header file for the class InkPenTool
 */

#ifndef _DPDFC_INK_PEN_TOOL_H_
#define _DPDFC_INK_PEN_TOOL_H_

#include "page.hpp"
#include "pen_tool.hpp"



namespace DirtyPDFCore{
  class InkPenTool : public PenTool<InkPenTool>{
  private:
    Poppler::InkAnnotation* m_annotation;

  public:
    InkPenTool();

    InkPenTool(const InkPenTool &inkPenTool);

    void behavior(Page* page, const QMouseEvent &mouseEvent);
  };
}
#endif
