#include <iostream>
#include <fstream>
#include <sstream>

#include <string>
#include <vector>

#include <algorithm>

using namespace std;

struct hh
{
  int id;
  int h;

  bool operator<(const hh & rhs) const
  {
    return h < rhs.h;
  }
};

int main()
{
  vector<string> authors;

  ifstream author_in("../0-data/2-merged/merged_authors.txt");

  string author_line;
  getline(author_in, author_line);
  getline(author_in, author_line);

  while (getline(author_in, author_line))
  {
    authors.push_back(author_line);
  }

  author_in.close();
  cout << "merged_authors.txt has been read." << endl;

  cout << endl;

  vector<int> awp_rowptr;

  ifstream awp_rowptr_in("../0-data/3-crs/author_writes_paper_rowptr.txt");

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

  ifstream awp_colind_in("../0-data/3-crs/author_writes_paper_colind.txt");

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

  ifstream pcp_rowptr_in("../0-data/3-crs/paper_citedby_paper_rowptr.txt");

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

  cout << endl;

  vector<int> hindex;

  for (int author = 0; author < authors.size(); author++)
  {
    vector<int> citationcounts;

    for (int col = awp_rowptr[author]; col < awp_rowptr[author+1]; col++)
    {
      int paperid = awp_colind[col];
      
      int citationcount = pcp_rowptr[paperid+1] - pcp_rowptr[paperid];
      citationcounts.push_back(citationcount);
    }

    make_heap(citationcounts.begin(), citationcounts.end());

    int ctr = 1;
    while (citationcounts.size() > 0 && citationcounts.front() >= ctr)
    {
      pop_heap(citationcounts.begin(), citationcounts.end());
      citationcounts.pop_back();

      ctr++;
    }

   hindex.push_back(ctr-1);
  }

  cout << "h-indexes has been calculated." << endl;

  cout << endl; 
  
  ofstream full_out("hindexes.txt");

  full_out << hindex.size() << endl << endl;

  for (int i = 0; i < hindex.size(); i++)
    full_out << hindex[i] << endl;

  full_out.close();
  cout << "hindexes.txt has been written." << endl;


  vector<hh> hwithid;

  for (int i = 0; i < hindex.size(); i++)
  {
    hh author;

    author.id = i;
    author.h = hindex[i];

    hwithid.push_back(author);
  }

  ofstream top_out("top100.txt");

  top_out << 100 << endl;

  make_heap(hwithid.begin(), hwithid.end());

  for (int i = 1; i <= 100; i++)
  {
    top_out << endl;

    top_out << i << endl;
    top_out << hwithid.front().h << endl;
    top_out << authors[hwithid.front().id] << endl;

    pop_heap(hwithid.begin(), hwithid.end());
    hwithid.pop_back();
  }

  top_out.close();
  cout << "top100.txt has been written." << endl;

  return 0;
}
