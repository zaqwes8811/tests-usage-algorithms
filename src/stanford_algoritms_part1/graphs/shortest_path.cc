
// C
#include <cassert>

// C++
#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <fstream>
#include <algorithm>
#include <sstream>

// http://www.onlamp.com/pub/a/onlamp/2006/04/06/boostregex.html?page=3
//#include <boost/regex.hpp>  // too hard
#include "boost/lexical_cast.hpp"  // не то, что нужно

using namespace std;

static stringstream ss;  // он тяжелый!!!

// TODO: Возвращаемое значение не всегда копируется?
vector<int> process_data_line(const string& line) {
  // 0\t8,89\t...  source sink, weight ... -> 0,8,89 - 
  vector<int> result;
  result.reserve(100);  // защита от лишний аллокаций 
  const char kSplitter = ',';
  
  string line_copy = line;  // TODO: slow
  
  // trim
  // http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
  line_copy.erase(line_copy.find_last_not_of(" \n\r\t")+1);
  
  // http://stackoverflow.com/questions/2896600/how-to-replace-all-occurrences-of-a-character-in-string
  // возможно можно исключить
  replace(line_copy.begin(), line_copy.end(), '\t', kSplitter);  // заменяем символы, а не строки
  
  cout << line_copy << endl;
  // можно разбивать на части
  // stringstream - http://habrahabr.ru/post/131977/
  // http://stackoverflow.com/questions/1894886/parsing-a-comma-delimited-stdstring 
  // Try reload
  ss.str(line_copy); 
  ss.seekp(0);

  for (int i = 0; ss >> i; ) {
      result.push_back(i);
      if (ss.peek() == kSplitter)
	  ss.ignore();
  }
  
  // postcondition
  if (result.size() % 2 == 0)
    throw invalid_argument("Error: brocked file format.");
  
  return result;  // сразу не поставил а gcc не отловил - в итоге дамп памяти
}

int main() {
  string test_line("0\t8,89\t9,90\t\n");
  
  try {
    for (int i = 1; i < 4; ++i) {
      vector<int> processed = process_data_line(test_line);
      assert(processed.size() == 5);
    }
  
  } catch (const exception& e) {
    cout << e.what() << endl;
    //throw;    
  }  
  return 0;
}