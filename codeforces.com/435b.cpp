#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;


int main(void) {
  string s; int k; cin >> s >> k;

  for (int pos1 = 0; pos1 < s.size(); ++pos1) {
    for (char which = '9'; which >= s[pos1]; --which) {
      int pos2 = s.find_first_of(which, pos1);
      if (pos2 == string::npos) continue;
      //cout << pos1 << " " << pos2 << endl;
      if (pos2 - pos1 <= k) {
        k -= (pos2 - pos1);
        rotate(s.begin() + pos1, s.begin() + pos2, s.begin() + pos2 + 1);
        //cout << s << endl;
        break;
      }
    }
  }

  cout << s << endl;
  return 0;
}
