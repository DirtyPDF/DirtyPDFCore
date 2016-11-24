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
    class PenTool : public Tool{
    protected:
      QColor m_color; ///< Color selected for the stroke
      double m_width; ///< Witdth selected for the stroke
      bool m_beautifySelected; ///< Tells if the beautification option is selected or not

    public:
      PenTool();

      /**
       * @brief Initializes the pen with the values that it needs to perform its behavior.
       * This function is called by the PensManager when it needs to create a new instance of a PenTool subclass.
       */
      void initialize(const QColor &color, double width, bool beautifySelected);
    };
}

#endif
