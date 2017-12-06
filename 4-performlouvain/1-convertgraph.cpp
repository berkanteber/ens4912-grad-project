#include <iostream>
#include <fstream>
#include <sstream>

#include <string>
#include <vector>

using namespace std;

int main(int argc, char** argv)
{
  string rowptr_filename = argv[1];
  ifstream rowptr_in(rowptr_filename);

  string rowptr_line;
  getline(rowptr_in, rowptr_line);
  getline(rowptr_in, rowptr_line);

  vector<long long int> rowptr;
  while (getline(rowptr_in, rowptr_line))
  {
    istringstream rowptr_iss(rowptr_line);
    long long int rowptr_num;
    rowptr_iss >> rowptr_num;
    rowptr.push_back(rowptr_num);
  }
  
  rowptr_in.close();

  cout << "rowptr has been read." << endl;

  string colind_filename = argv[2];
  ifstream colind_in(colind_filename);

  string colind_line;
  getline(colind_in, colind_line);
  getline(colind_in, colind_line);

  vector<int> colind;
  while (getline(colind_in, colind_line))
  {
    istringstream colind_iss(colind_line);
    int colind_num;
    colind_iss >> colind_num;
    colind.push_back(colind_num);
  }
  
  colind_in.close();

  cout << "colind has been read." << endl;

  cout << endl;

  ofstream out("graph.txt");

  for (int node1 = 0; node1 < rowptr.size(); node1++)
    for (long long int ind = rowptr[node1]; ind < rowptr[node1 + 1]; ind++)
    {
      int node2 = colind[ind];
     
      out << node1 << " " << node2 << endl;
    }

  out.close();

  cout << "graph.txt has been written." << endl;

  return 0;
}
