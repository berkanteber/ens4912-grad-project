#include <iostream>
#include <fstream>
#include <sstream>

#include <string>
#include <vector>

#include <algorithm>

using namespace std;

struct community
{
  int comm;
  double val;

  bool operator<(const community & rhs) const
  {
    return val < rhs.val;
  }
};

int main()
{
  ifstream in_cites_rowptr("../0-data/7-authorcitesauthor/author_cites_author_rowptr.txt");

  string line_cites_rowptr;
  getline(in_cites_rowptr, line_cites_rowptr);
  getline(in_cites_rowptr, line_cites_rowptr);

  vector<int> cites_rowptr;
  while (getline(in_cites_rowptr, line_cites_rowptr))
  {
    int num;
    istringstream iss(line_cites_rowptr);
    iss >> num;
    cites_rowptr.push_back(num);
  }

  in_cites_rowptr.close();
  cout << "author_cites_author_rowptr.txt has been read." << endl; 

  ifstream in_cites_colind("../0-data/7-authorcitesauthor/author_cites_author_colind.txt");

  string line_cites_colind;
  getline(in_cites_colind, line_cites_colind);
  getline(in_cites_colind, line_cites_colind);

  vector<int> cites_colind;
  while (getline(in_cites_colind, line_cites_colind))
  {
    int num;
    istringstream iss(line_cites_colind);
    iss >> num;
    cites_colind.push_back(num);
  }

  in_cites_colind.close();
  cout << "author_cites_author_colind.txt has been read." << endl; 

  ifstream in_cites_weights("../0-data/7-authorcitesauthor/author_cites_author_weights.txt");

  string line_cites_weights;
  getline(in_cites_weights, line_cites_weights);
  getline(in_cites_weights, line_cites_weights);

  vector<int> cites_weights;
  while (getline(in_cites_weights, line_cites_weights))
  {
    int num;
    istringstream iss(line_cites_weights);
    iss >> num;
    cites_weights.push_back(num);
  }

  in_cites_weights.close();
  cout << "author_cites_author_weights.txt has been read." << endl; 

  cout << endl;

  ifstream in_node2comm("../0-data/7-authorcitesauthor/author_cites_author_node2comm.txt");

  string line_node2comm;

  vector<int> node2comm(cites_rowptr.size() - 1);
  vector<vector<int>> comm2node(cites_rowptr.size() - 1);

  while (getline(in_node2comm, line_node2comm))
  {
    int node, comm;
    istringstream iss(line_node2comm);
    iss >> node >> comm;
    node2comm[node] = comm;
    comm2node[comm].push_back(node);
  }

  in_node2comm.close();
  cout << "author_cites_author_node2comm.txt has been read." << endl;

  cout << endl;

  vector<community> possible;
  for (int i = 0; i < comm2node.size(); i++)
  {
    if (comm2node[i].size() < 3 || comm2node[i].size() > 10)
      continue;

    double sum = 0;
    for (int j = 0; j < comm2node[i].size(); j++)
    {
      double numerator = 0;
      double denumerator = 1;

      for (int k = cites_rowptr[comm2node[i][j]]; k < cites_rowptr[comm2node[i][j] + 1]; k++)
      {
        if (node2comm[cites_colind[k]] == i)
          numerator++;
        denumerator++; 
      }

      sum += numerator / denumerator;
    }

    community cmmnty;
    cmmnty.comm = i;
    cmmnty.val = sum / comm2node[i].size();
    possible.push_back(cmmnty);
  }

  cout << "possible list has been constructed" << endl;
  cout << endl;

  ifstream in_authors("../0-data/2-merged/merged_authors.txt");

  string line_authors;
  getline(in_authors, line_authors);
  getline(in_authors, line_authors);

  vector<string> authornames;
  while (getline(in_authors, line_authors))
  {
   authornames.push_back(line_authors);
  }

  in_authors.close();
  cout << "merged_authors.txt has been read." << endl;
  cout << endl;

  make_heap(possible.begin(), possible.end());
  
  for (int i = 1; i <= 6; i++)
  { 
    char c = '0' + i;
    string s(1, c);

    ofstream out("top_" + s + "_comm.txt");

    out << possible.front().comm << "  " << possible.front().val << "  " 
        << comm2node[possible.front().comm].size() << endl;

    for (int j = 0; j < comm2node[possible.front().comm].size(); j++)
    {
      out << endl;
      out << authornames[comm2node[possible.front().comm][j]] << endl;
     
      for (int k = cites_rowptr[comm2node[possible.front().comm][j]]; k < cites_rowptr[comm2node[possible.front().comm][j] + 1]; k++)
      {
        out << authornames[cites_colind[k]] << "  " << cites_weights[k];
        
        if (node2comm[cites_colind[k]] == possible.front().comm) 
          out << "  IN" << endl;
        else
          out << "  OUT" << endl;
      }
    }

    pop_heap(possible.begin(), possible.end());
    possible.pop_back();
  
    out.close();
    cout << "top_" + s + "_comm.txt has been written." << endl;
  }

  return 0;
}
