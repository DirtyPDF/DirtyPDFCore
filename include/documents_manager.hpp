/**
 * @file documents_manager.hpp
 * @brief Header file for the class DocumentsManager
 */

#ifndef _DPDFC_DOCUMENTS_MANAGER_H_
#define _DPDFC_DOCUMENTS_MANAGER_H_

#include <QHash>
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
    QHash<DocumentId, Document*> m_openedDocuments;
    DocumentId m_currentDocumentId;
    static DocumentsManager* m_instance;

    DocumentsManager();
    DocumentsManager(const DocumentsManager &dm);
    void operator=(const DocumentsManager &dm);

    DocumentId generateNewId();

  public:
    static DocumentsManager* Instance();
    ~DocumentsManager();

    /**
     * @brief Returns the id of the current document. If there is not current document
     * returns INVALID_DOCUMENT_ID
     */
    DocumentId getCurrentDocument();

    /**
     * @brief Returns a list with the id's of all documents opened.
     */
    QList<DocumentId> getOpenedDocuments();

    /**
     * @brief Returns a pointer to the Document refered by the id.
     * @remarks Use pointers to the documents managed by DocumentsManager only
     * if necesary. The rest of the time is better work with ids.
     * @warning @b NEVER delete a pointer to a document managed by DocumentsManager
     * since this will try to delete it again when the document is closed or in its destructor.
     * @param documentId Id of the document to get.
     * @return A pointer to the Document refered by documentId. @n
     * NULL if the id is invalid or the document is not stored in DocumentsManager.
     */
    Document* getDocumentById(DocumentId documentId);

    int getDocumentsNumber();

  public slots:

    /**
     * @brief Open the document in the specified path.
     * @param docUrl Path in the filesystem of the document to open.
     * @return The id of the Document created or INVALID_DOCUMENT_ID if the
     * document couldn't be opened.
     */
    DocumentId openDocument(const QUrl &docUrl);

    /**
     * @brief Close the document with the specified id. Also deletes the Document asociated.
     * @param documentId Id of the document to close. If the id is not in the DocumentsManager or
       is invalid nothing happens.
     */
    void closeDocument(const DocumentId documentId);

    /**
     * @brief Set a document as the current one.
     * @param documentId Id of the document to set as current.
     */
    void setCurrentDocument(const DocumentId documentId);

  signals:
    void documentOpened(DocumentId documentId);
    void documentClosed(DocumentId documentId);
    void currentDocumentChanged(DocumentId oldCurrentDocumentId);
  };
}
#endif
