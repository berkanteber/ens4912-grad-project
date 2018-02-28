#include <iostream>
#include <fstream>
#include <sstream>

#include <string>
#include <vector>

using namespace std;

struct author
{
  vector<int> papers;
};

int main(int argc, char** argv)
{
  string a_filename = "../0-data/2-merged/merged_authors.txt";
  ifstream a_in(a_filename);

  string a_line;
  getline(a_in, a_line);
  istringstream iss(a_line);

  int size;
  iss >> size;

  a_in.close();
  
  string filename = "../0-data/2-merged/merged_structured_papers_info_mag.txt";
  ifstream in(filename);

  string line;
  getline(in, line);
  
  author a;
  vector<author> authors(size, a);  

  int ctr = 0;
  while(getline(in, line))
  {
    getline(in, line);
    getline(in, line);
    getline(in, line);
    
    int n_authors;
    getline(in, line);
    istringstream iss_n(line);
    iss_n >> n_authors;

    for (int i = 0; i < n_authors; i++)
    {
      int authorid;
      getline(in, line);
      istringstream iss_authorid(line);
      iss_authorid >> authorid;

      if(authorid != 0)
        authors[authorid].papers.push_back(ctr);

      getline(in, line);
    }

    ctr++;
  }
  
  in.close();

  cout << "merged_structured_papers_info.txt has been read." << endl;
  cout << endl;

  vector<long long int> row_ptr;
  vector<int> col_ind;

  long long int cntr = 0;
  row_ptr.push_back(cntr);

  for (int i = 0; i < authors.size(); i++)
  {
    author a = authors[i];

    cntr += a.papers.size();
    row_ptr.push_back(cntr);

    for (int j = 0; j < a.papers.size(); j++)
      col_ind.push_back(a.papers[j]);
  }

  ofstream rowptr("author_writes_paper_rowptr.txt");

  rowptr << row_ptr.size() << endl << endl;
  for (int i = 0; i < row_ptr.size(); i++)
    rowptr << row_ptr[i] << endl;

  rowptr.close();

  cout << "author_writes_paper_rowptr.txt has been written." << endl;

  ofstream colind("author_writes_paper_colind.txt");

  colind << col_ind.size() << endl << endl;
  for (int i = 0; i < col_ind.size(); i++)
    colind << col_ind[i] << endl;

  colind.close();

  cout << "author_writes_paper_colind.txt has been written." << endl;

  return 0;
}
