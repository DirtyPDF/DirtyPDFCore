#include <QtTest/QtTest>
#include <QObject>
#include "history.hpp"
using namespace DirtyPDFCore;



class TestHistory : public QObject{
  Q_OBJECT
  History* m_history;

private slots:

  void init();
  void cleanup();

};


void TestHistory::init(){
  m_history = History::Instance();
}


void TestHistory::cleanup(){
  delete m_history;
}


QTEST_MAIN(TestHistory)
#include "test_history.moc"
