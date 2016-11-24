/**
 * @file shape_tool.hpp
 * @brief Header file for the class ShapeTool
 */

#ifndef _DPDFC_SHAPE_TOOL_H_
#define _DPDFC_SHAPE_TOOL_H_

#include <QColor>
#include "tool.hpp"



namespace DirtyPDFCore{

  /**
   * @brief Parent class for all Tools related with the addition of shapes in the page.
   */
  class ShapeTool : public Tool {
  protected:
    QColor m_color;
    double m_width;

  public:
    ShapeTool();

    /**
     * @brief Initializes the shape with the values that it needs to perform its behavior.
     * This function is called by the ShapesManager when it needs to create a new instance of a ShapeTool subclass.
     */
    void initialize(const QColor &color, double width);
  };
}
#endif
