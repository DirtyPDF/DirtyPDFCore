#include <QtTest/QtTest>
#include <QObject>
#include <QSignalSpy>
#include <algorithm>
#include <iostream>
#include "documents_manager.hpp"
using namespace DirtyPDFCore;
using namespace std;



class TestDocumentsManager : public QObject{
  Q_OBJECT
  DocumentsManager* m_manager;

  static const int m_docsNum = 3;
  DocumentId m_docs[m_docsNum];
  DocumentId m_invalidDoc;
  QUrl m_validDocUrl;
  QUrl m_invalidDocUrl;

private slots:

  void initTestCase();
  void init();
  void cleanup();
  void openDocument();
  void setCurrentDocument();
  void closeDocument();
  void getOpenedDocuments();
  void getDocumentById();
};


void TestDocumentsManager::initTestCase(){
  qRegisterMetaType<DocumentId>("DocumentId");
}


void TestDocumentsManager::init(){
  m_manager = DocumentsManager::Instance();
  m_validDocUrl = QUrl(TESTFILES "/empty.pdf");
  m_invalidDocUrl = QUrl(TESTFILES "/not_exist.pdf");
  for (int i=0; i < m_docsNum; i++){
    m_docs[i] = m_manager->openDocument(m_validDocUrl);
    QVERIFY(m_docs[i] != INVALID_DOCUMENT_ID);
  }
  m_invalidDoc = m_manager->openDocument(m_invalidDocUrl);
  QCOMPARE(m_invalidDoc, INVALID_DOCUMENT_ID);
}


void TestDocumentsManager::cleanup(){
  delete m_manager;
}


void TestDocumentsManager::openDocument(){
  QSignalSpy spy(m_manager, SIGNAL(documentOpened(DocumentId)));

  m_manager->openDocument(m_invalidDocUrl);
  QCOMPARE(spy.count(), 0);

  m_manager->openDocument(m_validDocUrl);
  QCOMPARE(spy.count(), 1);
}


void TestDocumentsManager::setCurrentDocument(){
  QSignalSpy spy(m_manager, SIGNAL(currentDocumentChanged(DocumentId)));

  QCOMPARE(m_manager->getCurrentDocument(), INVALID_DOCUMENT_ID);
  m_manager->setCurrentDocument(m_docs[0]);
  QCOMPARE(spy.count(), 1);
  QCOMPARE(m_manager->getCurrentDocument(), m_docs[0]);
  m_manager->closeDocument(m_docs[0]);
  QCOMPARE(m_manager->getCurrentDocument(), INVALID_DOCUMENT_ID);
  m_manager->setCurrentDocument(m_docs[0]);
  QCOMPARE(spy.count(), 1);
  QCOMPARE(m_manager->getCurrentDocument(), INVALID_DOCUMENT_ID);
}


void TestDocumentsManager::closeDocument(){
  QSignalSpy spy(m_manager, SIGNAL(documentClosed(DocumentId)));

  m_manager->closeDocument(m_invalidDoc);
  QCOMPARE(spy.count(), 0);

  m_manager->closeDocument(m_docs[0]);
  QCOMPARE(spy.count(), 1);
}


void TestDocumentsManager::getOpenedDocuments(){
  QList<DocumentId> open_docs = m_manager->getOpenedDocuments();
  std::sort(open_docs.begin(), open_docs.end());
  std::sort(m_docs, m_docs + m_docsNum);

  for (int i=0; i < m_docsNum; i++){
    QCOMPARE(open_docs[i], m_docs[i]);
  }
}


void TestDocumentsManager::getDocumentById(){
  Document* doc = m_manager->getDocumentById(m_invalidDoc);
  QVERIFY(doc == NULL);
  doc = m_manager->getDocumentById(m_docs[0]);
  QVERIFY(doc != NULL);
  m_manager->closeDocument(m_docs[0]);
  doc = m_manager->getDocumentById(m_docs[0]);
  QVERIFY(doc == NULL);
}




QTEST_MAIN(TestDocumentsManager)
#include "test_documents_manager.moc"
