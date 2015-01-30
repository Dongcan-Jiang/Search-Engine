#ifndef TEST_H_INCLUDED
#define TEST_H_INCLUDED

#include <string>
#include <vector>
#include <memory>
#include <iostream>
using namespace std;

#include "../analyzer/Token.h"
#include "../analyzer/Analyzer.h"
#include "../analyzer/WhitespaceAnalyzer.h"
#include "../document/Document.h"
#include "../document/IndexSearcher.h"
#include "../document/IndexWriter.h"
#include "../document/Posting.h"
#include "../document/ScoreDoc.h"
#include "../document/StoredField.h"
#include "../document/TextField.h"
#include "../query/Query.h"
#include "../query/TermQuery.h"


void simpleTest();

#endif // TEST_H_INCLUDED