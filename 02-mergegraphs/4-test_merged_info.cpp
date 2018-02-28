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
  int a_file_id = -1;
  int m_file_id = -1;

  int year = -1;
  
  vector<int> authors;
  vector<int> affils;
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
// READ FILES

  vector<string> a_files;
  read_into_vector("../0-data/aminer/aminer_files.txt", a_files);

  vector<string> m_files;
  read_into_vector("../0-data/mag/mag_files.txt", m_files);

  cout << endl;

// READ MERGED

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

// AUTHORS & AFFILS

  vector<string> authors;
  read_into_vector("../0-data/merged/merged_authors.txt", authors);

  vector<string> affils;
  read_into_vector("../0-data/merged/merged_affils.txt", affils);
  
  cout << endl;

// INFO

  string filename = argv[1];
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
    getline(in, line);
    istringstream iss_a(line);
    iss_a >> papers[ctr].a_file_id;

    getline(in, line);
    istringstream iss_m(line);
    iss_m >> papers[ctr].m_file_id;

    getline(in, line);
    istringstream iss_year(line);
    iss_year >> papers[ctr].year;
    
    int n_authors;
    getline(in, line);
    istringstream iss_n(line);
    iss_n >> n_authors;

    for (int i = 0; i < n_authors; i++)
    {
      int author;
      getline(in, line);
      istringstream iss_author(line);
      iss_author >> author;

      papers[ctr].authors.push_back(author);
    
      int affil;
      getline(in, line);
      istringstream iss_affil(line);
      iss_affil >> affil;

      papers[ctr].affils.push_back(affil);
    }

    ctr++;
  }
  
  in.close();

  cout << filename << " has been read." << endl;
  cout << endl;


// TEST

  srand(time(NULL));

  ofstream out("test_results.txt");

  int lpctr = atoi(argv[2]);
  for (int i = 0; i < lpctr; i++)
  {
    int rnd = rand() % size;

    if(i == 0) rnd = 0;
    if(i == 1) rnd = 1;
    if(i == lpctr - 2) rnd = size - 2;
    if(i == lpctr - 1) rnd = size - 1;

    out << aminers[rnd] << "    ";
    if(papers[rnd].a_file_id != -1)
      out << a_files[papers[rnd].a_file_id];
    out << endl;    

    out << mags[rnd] << "    ";
    if(papers[rnd].m_file_id != -1) 
      out << m_files[papers[rnd].m_file_id];
    out << endl;

    out << papers[rnd].year << endl;

    out << papers[rnd].authors.size() << endl;

    for (int j = 0; j < papers[rnd].authors.size(); j++)
    {
      out << authors[papers[rnd].authors[j]] << endl;
      
      if(papers[rnd].affils[j] != -1)
        out << affils[papers[rnd].affils[j]] << endl;
      else
        out << "-" << endl;
    }

    out << endl;
  }

  out.close();

  cout << "test_results.txt has been written." << endl;
 
  return 0;
}
