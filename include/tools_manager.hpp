/**
 * @file tools_manager.hpp
 * @brief Header file for the class ToolsManager
 */

#ifndef _DPDFC_TOOLS_MANAGER_H_
#define _DPDFC_TOOLS_MANAGER_H_
namespace DirtyPDFCore{class ToolsManager;}

#include <QObject>
#include <QMouseEvent>
#include <memory>
#include "page.hpp"
#include "tool.hpp"



namespace DirtyPDFCore{

  /**
   * @brief Singleton class which controls the selection and use of tools.
   * @see Tool
   */
  class ToolsManager : public QObject{
    Q_OBJECT

  private:
    static ToolsManager* m_instance; ///< Singleton instance
    std::shared_ptr<Tool> m_currentTool; ///< Tool currently selected
    std::shared_ptr<Tool> m_oldTool; ///< Tool selected before m_currentTool

  protected:
    ToolsManager(QObject* parent=Q_NULLPTR);
    ToolsManager(const ToolsManager&);
    void operator=(const ToolsManager&);

  public:
    ~ToolsManager();

    static ToolsManager* Instance();

    /**
     * @brief Return the Tool currently selected in the system
     */
    Tool& getCurrentTool();

    /**
     * @brief Sets the Tool currently selected in the system.
     * @param tool Concrete Tool subclass to set as the current tool.
     */
    void setCurrentTool(const Tool &tool);

  public slots:

    /**
     * @brief Uses the current Tool to write an annotation in a Page depending
     * on a QMouseEvent.
     * @param page Page in which write the annotation.
     * @param mouseEvent QMouseEvent which tells how to write the annotation.
     */
    void useTool(Page* page, const QMouseEvent &mouseEvent);

  signals:

    /**
     * @brief Signal emmited when the current Tool changes.
     * @param oldTool The previous current Tool.
     */
    void currentToolChanged(Tool &oldTool);

  };
}

#endif
