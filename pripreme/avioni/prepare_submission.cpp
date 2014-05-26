#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

void outputFile(const string& filename) {
  ifstream in(filename.c_str());
  for (string line; getline(in, line); ) {
    cout << line << endl;
  }
}

int main(int argc, char* argv[]) {
  if (argc != 2) {
    puts("prepare_submission <input source file>");
    exit(1);
  }

  ifstream in(argv[1]);
  bool prepare_header = false;

  for (string line; getline(in, line); ) {
    if (line == "//PREPARE_SUBMISSION_HEADER") {
      prepare_header = true;
      continue;
    }
    if (line.find("#include") != string::npos) {
      int first = line.find_first_of("\"")+1;
      int last = line.find_last_of("\"")-1;
      string filename = line.substr(first, last-first+1);

      //cout << filename << endl;
      if (prepare_header) {
        outputFile(filename);
        prepare_header = false;
      } else {
        cout << line << endl;
      }
    } else {
      cout << line << endl;
    }
  }
  return 0;
}
