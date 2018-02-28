#include <iostream>
#include <fstream>
#include <sstream>

#include <string>
#include <vector>

using namespace std;

struct paper
{
  vector<int> references;
  vector<int> citations;
};

int main(int argc, char** argv)
{
  string filename = "../0-data/2-merged/merged_structured_papers_refs.txt";
  ifstream in(filename);

  string line;
  getline(in, line);
  istringstream iss(line);
  
  int size;
  iss >> size;

  paper p;
  vector<paper> papers(size, p);  

  int ctr = 0;
  while(getline(in, line))
  {
    int n_references;
    getline(in, line);
    istringstream iss_n(line);
    iss_n >> n_references;

    for (int i = 0; i < n_references; i++)
    {
      int reference;
      getline(in, line);
      istringstream iss_reference(line);
      iss_reference >> reference;

      papers[ctr].references.push_back(reference);
      papers[reference].citations.push_back(ctr);
    }

    ctr++;
  }
  
  in.close();

  cout << "merged_structured_papers_refs.txt has been read." << endl;
  cout << endl;

  vector<int> ref_row_ptr;
  vector<int> ref_col_ind;

  long long int ref_ctr = 0;
  ref_row_ptr.push_back(ref_ctr);

  for (int i = 0; i < papers.size(); i++)
  {
    paper p = papers[i];

    ref_ctr += p.references.size();
    ref_row_ptr.push_back(ref_ctr);

    for (int j = 0; j < p.references.size(); j++)
      ref_col_ind.push_back(p.references[j]);
  }

  ofstream ref_rowptr("paper_cites_paper_rowptr.txt");

  ref_rowptr << ref_row_ptr.size() << endl << endl;
  for (int i = 0; i < ref_row_ptr.size(); i++)
    ref_rowptr << ref_row_ptr[i] << endl;

  ref_rowptr.close();

  cout << "paper_cites_paper_rowptr.txt has been written." << endl;

  ofstream ref_colind("paper_cites_paper_colind.txt");

  ref_colind << ref_col_ind.size() << endl << endl;
  for (int i = 0; i < ref_col_ind.size(); i++)
    ref_colind << ref_col_ind[i] << endl;

  ref_colind.close();

  cout << "paper_cites_paper_colind.txt has been written." << endl;

  cout << endl;

  vector<int> cite_row_ptr;
  vector<int> cite_col_ind;

  int cite_ctr = 0;
  cite_row_ptr.push_back(cite_ctr);

  for (int i = 0; i < papers.size(); i++)
  {
    paper p = papers[i];

    cite_ctr += p.citations.size();
    cite_row_ptr.push_back(cite_ctr);

    for (int j = 0; j < p.citations.size(); j++)
      cite_col_ind.push_back(p.citations[j]);
  }

  ofstream cite_rowptr("paper_citedby_paper_rowptr.txt");

  cite_rowptr << cite_row_ptr.size() << endl << endl;
  for (int i = 0; i < cite_row_ptr.size(); i++)
    cite_rowptr << cite_row_ptr[i] << endl;

  cite_rowptr.close();

  cout << "paper_citedby_paper_rowptr.txt has been written." << endl;

  ofstream cite_colind("paper_citedby_paper_colind.txt");

  cite_colind << cite_col_ind.size() << endl << endl;
  for (int i = 0; i < cite_col_ind.size(); i++)
    cite_colind << cite_col_ind[i] << endl;

  cite_colind.close();

  cout << "paper_citedby_paper_colind.txt has been written." << endl;

  return 0;
}
