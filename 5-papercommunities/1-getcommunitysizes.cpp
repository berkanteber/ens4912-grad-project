#include <iostream>
#include <fstream>
#include <sstream>

#include <string>
#include <vector>

using namespace std;

int main(int argc, char** argv)
{
  string filename = argv[1];
  ifstream in(filename);

  vector<int> node2comm;

  int maxcomm = -1;

  string line;
  while(getline(in, line))
  {
    istringstream iss(line);
    int node, community;
    iss >> node >> community;
    node2comm.push_back(community);

    if (community > maxcomm) maxcomm = community;
  }

  in.close();
  cout << "node2comm.txt has been read." << endl;

  vector<long long int> commsize(maxcomm + 1, 0);
  
  for (int i = 0; i < node2comm.size(); i++)
    commsize[node2comm[i]]++;

  ofstream out("commsize.txt");

  out << commsize.size() << endl << endl;
  for (int i = 0; i < commsize.size(); i++)
    out << commsize[i] << endl;

  out.close();
  cout << "commsize.txt has been written." << endl;

  return 0;
}
