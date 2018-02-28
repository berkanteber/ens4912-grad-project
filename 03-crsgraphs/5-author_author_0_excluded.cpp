#include <iostream>
#include <fstream>
#include <sstream>

#include <string>
#include <vector>
#include <map>

using namespace std;

struct author
{
  map<int, int> coauthors;
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
    
    vector<int> coauthors;

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
        coauthors.push_back(authorid);

      getline(in, line);
    }

    for (int i = 0; i < coauthors.size(); i++)
      for (int j = 0; j < coauthors.size(); j++)
        if (i != j)
        {
          int ai = coauthors[i];
          int aj = coauthors[j];

          if(authors[ai].coauthors.find(aj) == authors[ai].coauthors.end())
            authors[ai].coauthors[aj] = 1;
          else
            authors[ai].coauthors[aj]++;
        }

    ctr++;
  }
  
  in.close();

  cout << "merged_structured_papers_info.txt has been read." << endl;
  cout << endl;

  vector<long long int> row_ptr;
  vector<int> col_ind;
  vector<int> weights;

  long long int cntr = 0;
  row_ptr.push_back(cntr);

  for (int i = 0; i < authors.size(); i++)
  {
    author a = authors[i];

    cntr += a.coauthors.size();
    row_ptr.push_back(cntr);

    map<int, int>::iterator it;
    for(it = a.coauthors.begin(); it != a.coauthors.end(); ++it)
    {
      col_ind.push_back(it->first);
      weights.push_back(it->second);
     }
  }

  ofstream rowptr("author_collaborates_author_rowptr.txt");

  rowptr << row_ptr.size() << endl << endl;
  for (int i = 0; i < row_ptr.size(); i++)
    rowptr << row_ptr[i] << endl;

  rowptr.close();

  cout << "author_collaborates_author_rowptr.txt has been written." << endl;

  ofstream colind("author_collaborates_author_colind.txt");

  colind << col_ind.size() << endl << endl;
  for (long long int i = 0; i < col_ind.size(); i++)
    colind << col_ind[i] << endl;

  colind.close();

  cout << "author_collaborates_author_colind.txt has been written." << endl;

  ofstream w("author_collaborates_author_weights.txt");

  w << weights.size() << endl << endl;
  for (long long int i = 0; i < weights.size(); i++)
    w << weights[i] << endl;

  w.close();

  cout << "author_collaborates_author_weights.txt has been written." << endl;
 
  return 0;
}
