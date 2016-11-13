/**
 * @file tool.hpp
 * @brief Header file for the class Tool
 */

#ifndef _DPDFC_TOOL_H_
#define _DPDFC_TOOL_H_

#include <QMouseEvent>
#include "annotable_page.hpp"



namespace DirtyPDFCore{

  /**
   * @brief Common interface for all tools.
   */
  class Tool{
  public:

    /**
     * @breif Describes the behavior of the Tool when a QMouseEvent is triggered inside an AnnotablePage.
     * @param page AnnotablePage to change with the Tool.
     * @param mouseEvent QMouseEvent indicating how the Tool has to modify the page.
     */
    virtual void behavior(const AnnotablePage* page, const QMouseEvent &mouseEvent) = 0;
  };
}
#endif
