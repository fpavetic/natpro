#include <cstdio>

#include <iostream>
#include <string>
#include <map>
using namespace std;

int main(void) {
  map<int, int> num_samples;
  map<int, int> correct_samples;
  int total_num_samples = 0;
  int total_correct_samples = 0;
  for (string filename; cin >> filename; ) {
    int estimated_class; 
    cin >> estimated_class;
    int correct_class;
    sscanf(filename.c_str(), "Class%d", &correct_class);
    
    if (correct_class == estimated_class) {
      ++correct_samples[correct_class];
      ++total_correct_samples;
    }
    ++num_samples[correct_class];
    ++total_num_samples;
  }

  for (int cl = 1; cl <= 7; ++cl) {
      printf("Class %d: %d/%d (%0.4lf%%) samples correctly classified.\n",
             cl, correct_samples[cl], num_samples[cl], 
             100.0*correct_samples[cl]/num_samples[cl]);
  }
  
  puts("======================================");
  printf("%d/%d samples correctly classified.\n",
         total_correct_samples, total_num_samples);
  printf("Accuracy: %0.4lf%%\n",
         100.0 * total_correct_samples / total_num_samples);
  return 0;
}
