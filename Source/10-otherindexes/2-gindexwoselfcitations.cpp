#include <iostream>
#include <fstream>
#include <sstream>

#include <string>
#include <vector>
#include <set>

#include <algorithm>

using namespace std;

struct gg
{
  int id;
  int g;

  bool operator<(const gg & rhs) const
  {
    return g < rhs.g;
  }
};

int main()
{
  vector<int> awp_rowptr;

  ifstream awp_rowptr_in("../00-data/03-crs/author_writes_paper_rowptr.txt");

  string awp_rowptr_line;
  getline(awp_rowptr_in, awp_rowptr_line);
  getline(awp_rowptr_in, awp_rowptr_line);

  while (getline(awp_rowptr_in, awp_rowptr_line))
  {
    istringstream iss(awp_rowptr_line);
    int num;
    iss >> num;
    awp_rowptr.push_back(num);
  }

  awp_rowptr_in.close();
  cout << "author_writes_paper_rowptr.txt has been read." << endl;

  vector<int> awp_colind;

  ifstream awp_colind_in("../00-data/03-crs/author_writes_paper_colind.txt");

  string awp_colind_line;
  getline(awp_colind_in, awp_colind_line);
  getline(awp_colind_in, awp_colind_line);

  while (getline(awp_colind_in, awp_colind_line))
  {
    istringstream iss(awp_colind_line);
    int num;
    iss >> num;
    awp_colind.push_back(num);
  }

  awp_colind_in.close();
  cout << "author_writes_paper_colind.txt has been read." << endl;

  cout << endl;

  vector<int> pcp_rowptr;

  ifstream pcp_rowptr_in("../00-data/03-crs/paper_citedby_paper_rowptr.txt");

  string pcp_rowptr_line;
  getline(pcp_rowptr_in, pcp_rowptr_line);
  getline(pcp_rowptr_in, pcp_rowptr_line);

  while (getline(pcp_rowptr_in, pcp_rowptr_line))
  {
    istringstream iss(pcp_rowptr_line);
    int num;
    iss >> num;
    pcp_rowptr.push_back(num);
  }

  pcp_rowptr_in.close();
  cout << "paper_citedby_paper_rowptr.txt has been read." << endl;

  vector<int> pcp_colind;

  ifstream pcp_colind_in("../00-data/03-crs/paper_citedby_paper_colind.txt");

  string pcp_colind_line;
  getline(pcp_colind_in, pcp_colind_line);
  getline(pcp_colind_in, pcp_colind_line);

  while (getline(pcp_colind_in, pcp_colind_line))
  {
    istringstream iss(pcp_colind_line);
    int num;
    iss >> num;
    pcp_colind.push_back(num);
  }

  pcp_colind_in.close();
  cout << "paper_citedby_paper_colind.txt has been read." << endl;

  cout << endl;

  vector<int> gindex;

  for (int author = 0; author < awp_rowptr.size() - 1; author++)
  {
    vector<int> citationcounts;

    set<int> writtenbyauthor;
    for (long long int col = awp_rowptr[author]; col < awp_rowptr[author+1]; col++)
      writtenbyauthor.insert(awp_colind[col]);

    for (set<int>::iterator it = writtenbyauthor.begin(); it != writtenbyauthor.end(); ++it)
    {
      int paperid = *it;
      
      int citationcount = 0;
      for (long long int rcol = pcp_rowptr[paperid]; rcol < pcp_rowptr[paperid+1]; rcol++)
        if (writtenbyauthor.find(pcp_colind[rcol]) == writtenbyauthor.end())
          citationcount++;

      citationcounts.push_back(citationcount);
    }

    make_heap(citationcounts.begin(), citationcounts.end());

    int ctr = 1;
    int sum = 0;
    while (citationcounts.size() > 0 && sum + citationcounts.front() >= ctr * ctr)
    {
      sum += citationcounts.front(); 

      pop_heap(citationcounts.begin(), citationcounts.end());
      citationcounts.pop_back();

      ctr++;
    }

   gindex.push_back(ctr-1);
  }

  cout << "g-indexes has been calculated." << endl;

  cout << endl; 
  
  ofstream full_out("gindexes-woself.txt");

  full_out << gindex.size() << endl << endl;

  for (int i = 0; i < gindex.size(); i++)
    full_out << gindex[i] << endl;

  full_out.close();
  cout << "gindexes-woself.txt has been written." << endl;


  vector<gg> gwithid;

  for (int i = 0; i < gindex.size(); i++)
  {
    gg author;

    author.id = i;
    author.g = gindex[i];

    gwithid.push_back(author);
  }

  ofstream top_out("top10000-g-woself.txt");

  top_out << 10000 << endl << endl;

  make_heap(gwithid.begin(), gwithid.end());

  for (int i = 1; i <= 10000; i++)
  {
    top_out << gwithid.front().id << endl;

    pop_heap(gwithid.begin(), gwithid.end());
    gwithid.pop_back();
  }

  top_out.close();
  cout << "top10000-g-woself.txt has been written." << endl;

  return 0;
}
