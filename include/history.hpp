/**
 * @file history.hpp
 * @brief Header file for the class History
 */

#ifndef _HISTORY_H_
#define _HISTORY_H_

#include <QObject>
#include <QUndoGroup>
#include <QUndoStack>
#include <QHash>
#include "document.hpp"



namespace DirtyPDFCore{

  /**
   * @brief Singleton class derivated from QUndoGroup which manages all the undo/redo
   * actions across the entire system.
   * Stores one QUndoStack for each @e Document opened.
   * @see Document
   */
  class History : public QUndoGroup{
    Q_OBJECT

  private:
    static History* m_instance; ///< Instance pointer
    QHash<DocumentId, QUndoStack*> m_undoStacks; ///< QUndoStacks stored by its document.

  protected:
    History(QObject* parent=Q_NULLPTR);
    History(const History &h);
    void operator=(const History &h);

  public:
    static History* Instance();

    ~History();

  public slots:

    /**
     * @brief Add an UndoStack for the document refered by documentId.
     * @param documentId Id of the document for which the UndoStack is added.
     */
    void addDocumentStack(DocumentId documentId);

    /**
     * @brief Active the UndoStack bound to the document.
     * @param documentId References the document bound to the UndoStack to activate.
     */
    void setActiveDocumentStack(DocumentId documentId);

    /**
     * @brief Remove the UndoStack bound to the document.
     * @param documentId References the document bound to the UndoStack to remove.
     */
    void removeDocumentStack(DocumentId documentId);

  private slots:

    /**
     * @brief Active the UndoStack bound to the current document in DocumentsManager.
     */
    void activeCurrentDocumentStack();

  };
}
#endif
