#include <iostream>
#include <fstream>
#include <sstream>

#include <string>
#include <vector>

#include <cstdlib>
#include <ctime>

using namespace std;

struct paper
{
  vector<int> references;
};

void read_into_vector(string filename, vector<string> & vec)
{
  ifstream in(filename);

  string line;
  getline(in, line);
  getline(in, line);

  while(getline(in, line))
    vec.push_back(line);

  in.close();
 
  string pretty_filename = filename.substr(filename.rfind("/") + 1);
  cout << pretty_filename << " has been read." << endl;
}

int main(int argc, char** argv)
{
// PAPERS

  vector<string> aminers;
  vector<string> mags;

  ifstream in_merged("../0-data/merged/merged_papers.txt");
  
  string line_merged;
  getline(in_merged, line_merged);

  while(getline(in_merged, line_merged))
  {
    getline(in_merged, line_merged);
    aminers.push_back(line_merged);

    getline(in_merged, line_merged);
    mags.push_back(line_merged);
  }

  in_merged.close();

  cout << "merged_papers.txt has been read." << endl;

// REFERENCES

  string filename = "merged_structured_papers_refs.txt";
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
    }

    ctr++;
  }
  
  in.close();

  cout << filename << " has been read." << endl;
  cout << endl;


// TEST

  srand(time(NULL));

  ofstream out("test_results.txt");

  int lpctr = atoi(argv[1]);
  for (int i = 0; i < lpctr; i++)
  {
    int rnd = rand() % size;

    if(i == 0) rnd = 0;
    if(i == 1) rnd = 1;
    if(i == lpctr - 2) rnd = size - 2;
    if(i == lpctr - 1) rnd = size - 1;

    out << aminers[rnd];
    out << endl;    

    out << mags[rnd];
    out << endl;

    out << papers[rnd].references.size() << endl;

    for (int j = 0; j < papers[rnd].references.size(); j++)
    {
      out << aminers[papers[rnd].references[j]] << "  ";
      out << mags[papers[rnd].references[j]] << endl;
    }

    out << endl;
  }

  out.close();

  cout << "test_results.txt has been written." << endl;
 
  return 0;
}
