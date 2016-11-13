/**
 * @file annotable_page.hpp
 * @brief Header file for the class AnnotablePage
 */

#ifndef _DPDFC_ANNOTABLE_PAGE_H_
#define _DPDFC_ANNOTABLE_PAGE_H_
namespace DirtyPDFCore{class AnnotablePage;}

#include <poppler-qt5.h>
#include <QMouseEvent>
#include "tools_manager.hpp"



namespace DirtyPDFCore{

  /**
   * @brief Poppler::Page derivated class which has propieties like to be annotated
   * with a QMouseEvent, support for not permanent annotations and to have the words in order.
   */
  class AnnotablePage : public Poppler::Page{
  private:
    ToolsManager* m_toolsManager; ///< Tool manager instance

  public:

    /**
     * @brief Write an annotation in the page depending on the QMouseEvent passed and the Tool currently selected.
     * @param mouseEvent QMouseEvent which tells how to write the annotation.
     */
    void handleMouseEvent(const QMouseEvent &mouseEvent);
  };
}
#endif
