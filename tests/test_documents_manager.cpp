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
  Document* m_docs[m_docsNum];
  Document* m_invalidDoc;
  QUrl m_validDocUrl;
  QUrl m_invalidDocUrl;

private slots:

  void init();
  void cleanup();
  void openDocument();
  void setCurrentDocument();
  void closeDocument();
  void openedDocuments();
  void document();
};


void TestDocumentsManager::init(){
  m_manager = DocumentsManager::Instance();
  m_validDocUrl = QUrl(TESTFILES "/empty.pdf");
  m_invalidDocUrl = QUrl(TESTFILES "/not_exist.pdf");
  for (int i=0; i < m_docsNum; i++){
    m_docs[i] = m_manager->openDocument(m_validDocUrl);
    QVERIFY(m_docs[i] != 0);
  }
  m_invalidDoc = m_manager->openDocument(m_invalidDocUrl);
  QVERIFY(m_invalidDoc == NULL);
}


void TestDocumentsManager::cleanup(){
  delete m_manager;
}


void TestDocumentsManager::openDocument(){
  QSignalSpy spy(m_manager, SIGNAL(documentOpened(Document*)));

  m_manager->openDocument(m_invalidDocUrl);
  QCOMPARE(spy.count(), 0);

  m_manager->openDocument(m_validDocUrl);
  QCOMPARE(spy.count(), 1);
}


void TestDocumentsManager::setCurrentDocument(){
  QSignalSpy spy(m_manager, SIGNAL(currentDocumentChanged(Document*)));

  QVERIFY(m_manager->currentDocument() == NULL);
  m_manager->setCurrentDocument(m_docs[0]);
  QCOMPARE(spy.count(), 1);
  QCOMPARE(m_manager->currentDocument(), m_docs[0]);
  m_manager->closeDocument(m_docs[0]);
  QVERIFY(m_manager->currentDocument() == NULL);
  m_manager->setCurrentDocument(m_docs[0]);
  QCOMPARE(spy.count(), 1);
  QVERIFY(m_manager->currentDocument() == NULL);
}


void TestDocumentsManager::closeDocument(){
  QSignalSpy spy(m_manager, SIGNAL(documentClosed(Document*)));
  bool closed;

  closed = m_manager->closeDocument(m_invalidDoc);
  QCOMPARE(closed, false);
  QCOMPARE(spy.count(), 0);

  closed = m_manager->closeDocument(m_docs[0]);
  QCOMPARE(closed, true);
  QCOMPARE(spy.count(), 1);
}


void TestDocumentsManager::openedDocuments(){
  QList<Document*> open_docs = m_manager->openedDocuments();

  for (int i=0; i < m_docsNum; i++){
    QVERIFY(open_docs[i] == m_docs[i]);
  }
}


void TestDocumentsManager::document(){
  int invalid_index = 4;
  Document* doc = m_manager->document(invalid_index);
  QVERIFY(doc == NULL);
  doc = m_manager->document(0);
  QVERIFY(doc == m_docs[0]);
  m_manager->closeDocument(m_docs[0]);
  doc = m_manager->document(0);
  QVERIFY(doc == m_docs[1]);
}




QTEST_MAIN(TestDocumentsManager)
#include "test_documents_manager.moc"
