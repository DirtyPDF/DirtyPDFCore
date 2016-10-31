/**
 * @file history.hpp
 * @brief Header file for the class History
 */

#ifndef _HISTORY_H_
#define _HISTORY_H_

#include <QObject>
#include <QUndoGroup>



namespace DirtyPDFCore{

  /**
   * @brief Singleton class derivated from QUndoGroup witch manages all the undo/redo
   * actions across the entire system.
   */
  class History : public QUndoGroup{
    Q_OBJECT

  private:
    static History* m_instance; ///< Instance pointer

  protected:
    History(QObject* parent=Q_NULLPTR);
    History(const History &h);
    void operator=(const History &h);

  public:
    static History* Instance();
  };
}
#endif
