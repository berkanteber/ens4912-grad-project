#include <iostream>
#include <fstream>
#include <sstream>

#include <string>
#include <vector>

#include <algorithm>

using namespace std;

struct comm_size 
{
  int community;
  long long int size;    
  
  bool operator<(comm_size const& rhs) const 
  {
    return size < rhs.size;
  }
};

int main(int argc, char** argv) 
{
  ifstream in("commsize.txt");
  
  string line;
  getline(in, line);
  getline(in, line);
  
  vector<comm_size> vec;

  int ctr = 0;
  while (getline(in, line))
  {
    istringstream iss(line);

    comm_size cs;
    cs.community = ctr++;
    iss >> cs.size;

    vec.push_back(cs);
  }

  in.close();
  cout << "commsize.txt has been read." << endl;

  make_heap(vec.begin(), vec.end());

  int k = atoi(argv[1]);

  ofstream out("topkcomm.txt");

  out << k << endl << endl;
  for (int i = 0; i < k; i++)
  {
    out << vec.front().community << " " << vec.front().size <<  endl;
    
    pop_heap(vec.begin(), vec.end());
    vec.pop_back();
  }

  out.close();
  cout << "topkcomm.txt has been written." << endl;

  return 0;
}
