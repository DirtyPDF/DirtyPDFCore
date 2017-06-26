#include <QtTest/QtTest>
#include <QObject>
#include "document.hpp"
using namespace DirtyPDFCore;



class TestDocument : public QObject{
  Q_OBJECT
  Document* m_document;

private slots:

  void init();
  void cleanup();
  void path();
  void save();
};


void TestDocument::init(){
  m_document = Document::load(QUrl(TESTFILES "/empty.pdf"));
}


void TestDocument::cleanup(){
  delete m_document;
}


void TestDocument::path(){
  QCOMPARE(m_document->path(), QUrl(TESTFILES "/empty.pdf"));
}


void TestDocument::save(){
  QUrl invalid_url("/document.pdf");
  bool saved = m_document->save(invalid_url);
  QCOMPARE(saved, false);
  saved = m_document->save(QUrl(TESTFILES "/saved.pdf"));
  QCOMPARE(saved, true);
  saved = m_document->save();
  QCOMPARE(saved, true);
}

QTEST_MAIN(TestDocument)
#include "test_document.moc"
