/**
 * @file rubber_pen_tool.hpp
 * @brief Header file for the class RubberPenTool
 */

#ifndef _DPDFC_RUBBER_PEN_TOOL_H_
#define _DPDFC_RUBBER_PEN_TOOL_H_

#include "page.hpp"
#include "pen_tool.hpp"



namespace DirtyPDFCore{
  class RubberPenTool : public PenTool<RubberPenTool>{
  private:
    QSet<Poppler::Annotation::SubType> m_annotationsSubTypes;

  public:
    RubberPenTool();

    RubberPenTool(const RubberPenTool &rubberPenTool);

    void behavior(Page* page, const QMouseEvent &mouseEvent);
  };
}
#endif
