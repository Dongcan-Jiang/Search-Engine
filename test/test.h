#ifndef TEST_H_INCLUDED
#define TEST_H_INCLUDED

#include <string>
#include <vector>
#include <memory>
#include <cstdlib>
#include <iostream>
using namespace std;

#include "../analyzer/Token.h"
#include "../analyzer/Analyzer.h"
#include "../analyzer/WhitespaceAnalyzer.h"
#include "../analyzer/StandardAnalyzer.h"
#include "../document/Document.h"
#include "../document/IndexSearcher.h"
#include "../document/IndexWriter.h"
#include "../document/Posting.h"
#include "../document/ScoreDoc.h"
#include "../document/StoredField.h"
#include "../document/TextField.h"
#include "../query/Query.h"
#include "../query/TermQuery.h"
#include "../query/BooleanQuery.h"
#include "../query/QueryParser.h"
#include "../query/PhraseQuery.h"
#include "../scorer/Scorer.h"
#include "../scorer/TermScorer.h"
#include "../scorer/ConjunctionScorer.h"
#include "../scorer/DisjunctionScorer.h"
#include "../scorer/ReqExclScorer.h"
#include "../scorer/ReqOptScorer.h"
#include "../scorer/PhraseScorer.h"
#include "../util/util.h"

void simpleTest();

void fileTest(char*argv[]);

#endif // TEST_H_INCLUDED
