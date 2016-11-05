#include <QtTest/QtTest>
#include <QObject>
#include <algorithm>
#include <iostream>
#include "documents_manager.hpp"
#include "document.hpp"
using namespace DirtyPDFCore;
using namespace std;



class TestDocumentsManager : public QObject{
  Q_OBJECT
  DocumentsManager* m_manager;

  static const int m_docsNum = 3;
  Document::Id m_docs[m_docsNum];
  Document::Id m_invalidDoc;

private slots:

  void init();
  void cleanup();
  void setCurrentDocument();
  void getOpenedDocuments();
  void getDocumentById();
};


void TestDocumentsManager::init(){
  m_manager = DocumentsManager::Instance();
  QUrl validDocUrl(TESTFILES "/empty.pdf");
  QUrl invalidDocUrl(TESTFILES "/not_exist.pdf");
  for (int i=0; i < m_docsNum; i++){
    m_docs[i] = m_manager->openDocument(validDocUrl);
    QVERIFY(m_docs[i] != Document::invalidId);
  }
  m_invalidDoc = m_manager->openDocument(invalidDocUrl);
  QCOMPARE(m_invalidDoc, Document::invalidId);
}


void TestDocumentsManager::cleanup(){
  delete m_manager;
}


void TestDocumentsManager::setCurrentDocument(){
  QCOMPARE(m_manager->getCurrentDocument(), Document::invalidId);
  m_manager->setCurrentDocument(m_docs[0]);
  QCOMPARE(m_manager->getCurrentDocument(), m_docs[0]);
  m_manager->closeDocument(m_docs[0]);
  QCOMPARE(m_manager->getCurrentDocument(), Document::invalidId);
  m_manager->setCurrentDocument(m_docs[0]);
  QCOMPARE(m_manager->getCurrentDocument(), Document::invalidId);
}


void TestDocumentsManager::getOpenedDocuments(){
  QList<Document::Id> open_docs = m_manager->getOpenedDocuments();
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
  QVERIFY(m_docs[0] == doc->getId());
  m_manager->closeDocument(m_docs[0]);
  doc = m_manager->getDocumentById(m_docs[0]);
  QVERIFY(doc == NULL);
}




QTEST_MAIN(TestDocumentsManager)
#include "test_documents_manager.moc"
