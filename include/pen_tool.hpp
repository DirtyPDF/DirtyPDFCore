/**
 * @file pen_tool.hpp
 * @brief Header file for the class PenTool
 */

#ifndef _DPDFC_PEN_TOOL_H_
#define _DPDFC_PEN_TOOL_H_

#include <QColor>
#include "tool.hpp"



namespace DirtyPDFCore{
    /**
     * @brief Parent class for all Tools related with the draw or erase of strokes in the page.
     */
    template<typename DerivedPenTool>
    class PenTool : public ToolCRTP<DerivedPenTool>{
    private:
      QColor m_color; ///< Color selected for the stroke
      double m_width; ///< Width selected for the stroke

    public:
      PenTool(){
        setColor(QColor(235, 99, 98));
        setWidth(5);
      }

      /**
       * @brief Sets the color of the pen.
       * @param color Color of the pen.
       */
      void setColor(const QColor &color){
        m_color = color;
      }

      /**
       * @brief Returns the color of the pen.
       */
      const QColor& color() const{
        return m_color;
      }

      /**
       * @brief Sets the width of the pen
       * @param width Width of the pen
       */
      void setWidth(double width){
          m_width = width;
      }

      /**
       * @brief Returns the width of the pen.
       */
      double width() const{
        return m_width;
      }
    };
}

#endif
