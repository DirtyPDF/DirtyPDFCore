/**
 * @file documents_manager.hpp
 * @brief Header file for the class DocumentsManager
 */

#ifndef _DPDFC_DOCUMENTS_MANAGER_H_
#define _DPDFC_DOCUMENTS_MANAGER_H_

#include <QList>
#include <QUrl>
#include "document.hpp"



namespace DirtyPDFCore{

  /**
   * @brief Singleton class which manages all the Document creation/deletion
   * actions across the entire system.
   * @see Document
   */
  class DocumentsManager : public QObject{
    Q_OBJECT

  private:
    QList<Document*> m_openedDocuments;
    Document* m_currentDocument;
    static DocumentsManager* m_instance;

    DocumentsManager();
    DocumentsManager(const DocumentsManager &dm);
    void operator=(const DocumentsManager &dm);

  public:
    static DocumentsManager* Instance();
    ~DocumentsManager();

    /**
     * @brief Returns the id of the current document. If there is not current document
     * returns INVALID_DOCUMENT_ID
     */
    Document* currentDocument();

    /**
     * @brief Returns a list with all documents opened.
     * The list is sorted by opening order.
     */
    QList<Document*> openedDocuments();

    /**
     * @brief Returns the number of documents opened.
     */
    int numDocuments();

    /**
     * @brief Returns the ith document, sorting by opening order.
     * @warning The index of a document can be updated when other document is closed.
     * For example let document0, document1 and document2 be three documents with
     * indexes 0, 1, and 2. If document1 is closed document0 still has the index 0,
     * but document2 now has the index 1.
     * To get an updated list of the documents opened call openedDocuments()
     * @see openedDocuments
     */
    Document* document(int index);

  public slots:

    /**
     * @brief Open the document in the specified path.
     * @param docUrl Path in the filesystem of the document to open.
     * @return The Document created or null if the
     * document couldn't be opened.
     */
    Document* openDocument(const QUrl &filePath);

    /**
     * @brief Close the document. Also deletes the Document asociated.
     * @param document Document to close.
     * @return false if the document is not stored in the manager, true otherwise.
     */
    bool closeDocument(Document* document);

    /**
     * @brief Set a document as the current one.
     * @param document Document to set as current.
     * @return false if the document is not stored in the manager, true otherwise.
     */
    bool setCurrentDocument(Document* document);

  signals:
    void documentOpened(Document* document);
    void documentClosed(Document* document);
    void currentDocumentChanged(Document* oldDocument);
  };
}
#endif
