#include <iostream>
#include <fstream>
#include <sstream>

#include <string>
#include <vector>
#include <map>

using namespace std;

int main(int argc, char** argv)
{
  string info_filename = "../0-data/2-merged/merged_structured_papers_info_mag.txt";
  ifstream info_in(info_filename);

  string info_line;
  getline(info_in, info_line);

  vector<vector<int>> paper_authors;

  while(getline(info_in, info_line))
  {
    getline(info_in, info_line);
    getline(info_in, info_line);
    getline(info_in, info_line);

    vector<int> authors;

    int n_authors;
    getline(info_in, info_line);
    istringstream iss_n(info_line);
    iss_n >> n_authors;

    for (int i = 0; i < n_authors; i++)
    {
      int authorid;
      getline(info_in, info_line);
      istringstream iss_authorid(info_line);
      iss_authorid >> authorid;

      if(authorid != 0)
        authors.push_back(authorid);

      getline(info_in, info_line);
    }

    paper_authors.push_back(authors);
  }

  info_in.close();
  cout << "merged_structured_papers_info.txt has been read." << endl;
  cout << endl;

  string ref_filename = "../0-data/2-merged/merged_structured_papers_refs.txt";
  ifstream ref_in(ref_filename);

  string ref_line;
  getline(ref_in, ref_line);

  vector<vector<int>> paper_refs;  

  while(getline(ref_in, ref_line))
  {
    vector<int> references;    

    int n_references;
    getline(ref_in, ref_line);
    istringstream iss_n(ref_line);
    iss_n >> n_references;

    for (int i = 0; i < n_references; i++)
    {
      int reference;
      getline(ref_in, ref_line);
      istringstream iss_reference(ref_line);
      iss_reference >> reference;

      references.push_back(reference);
    }
    
    paper_refs.push_back(references);
  }

  ref_in.close();

  cout << "merged_structured_papers_refs.txt has been read." << endl;
  cout << endl;

  ofstream rowptr("author_cites_author_rowptr.txt");
  ofstream colind("author_cites_author_colind.txt");
  ofstream weights("author_cites_author_weights.txt");

  ifstream awp_rowptr("../0-data/3-crs/author_writes_paper_rowptr.txt");
  ifstream awp_colind("../0-data/3-crs/author_writes_paper_colind.txt");

  string row_line;
  getline(awp_rowptr, row_line);
  getline(awp_rowptr, row_line);
  getline(awp_rowptr, row_line);  

  string col_line;
  getline(awp_colind, col_line);
  getline(awp_colind, col_line);

  long long int rowptr_ctr = 0;
  long long int rowptr_start = 0;
  rowptr << rowptr_ctr << endl;

  ofstream progress("progress.txt");

  int ctr = 0;
  while(getline(awp_rowptr, row_line))
  {
    if (ctr % 1000000 == 0)
      progress << ctr << endl;

    long long int rowptr_end;
    istringstream iss_row(row_line);
    iss_row >> rowptr_end;
    
    map<int, int> cited;

    for (long long int i = rowptr_start; i < rowptr_end; i++)
    {
      int paper;
      getline(awp_colind, col_line);
      istringstream iss_col(col_line);
      iss_col >> paper;

      for (int j = 0; j < paper_refs[paper].size(); j++)
        for (int k = 0; k < paper_authors[paper_refs[paper][j]].size(); k++)
        {
          int author = paper_authors[paper_refs[paper][j]][k];

          if (cited.find(author) == cited.end())
            cited[author] = 1;
          else
            cited[author]++;
        }
    }

    for (map<int, int>::iterator it = cited.begin(); it != cited.end(); ++it)
    {
      if (it->second < 3) continue;

      colind << it->first << endl;
      weights << it->second << endl;
   
      rowptr_ctr++;
    }

    rowptr << rowptr_ctr << endl;
    
    rowptr_start = rowptr_end;

    ctr++;
  }

  progress.close();

  awp_rowptr.close();
  awp_colind.close();

  rowptr.close();
  colind.close();
  weights.close();

  cout << "author_cites_author_rowptr.txt has been written." << endl;
  cout << "author_cites_author_colind.txt has been written." << endl;
  cout << "author_cites_author_weights.txt has been written." << endl;
 
  return 0;
}
