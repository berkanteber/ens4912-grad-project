#include <iostream>
#include <fstream>
#include <sstream>

#include <string>
#include <vector>
#include <set>
#include <map>

using namespace std;

struct paper
{
  set<int> references;
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

void read_into_map(string filename, map<string, int> & mp)
{
  ifstream in(filename);

  string line;
  getline(in, line);
  getline(in, line);

  int ctr = 0;
  while(getline(in, line))
    mp[line] = ctr++;

  in.close();
 
  string pretty_filename = filename.substr(filename.rfind("/") + 1);
  cout << pretty_filename << " has been read." << endl;
}

int main(int argc, char** argv)
{
  
// READ AMINER

  vector<string> aminer_papers;
  read_into_vector("../0-data/aminer/aminer_papers.txt", aminer_papers);

// READ MAG

  vector<string> mag_papers;
  read_into_vector("../0-data/mag/mag_papers.txt", mag_papers);

// READ MERGED 

  cout << endl;

  map<string, int> aminer2merged;
  map<string, int> mag2merged;

  ifstream in("../0-data/merged/merged_papers.txt");

  string line;
  getline(in, line);

  int ctr = 0;
  while(getline(in, line))
  {
    string aid;
    getline(in, aid);

    if(aid != "#=#=#")
      aminer2merged[aid] = ctr;

    string mid;
    getline(in, mid);

    if(mid != "#=#=#")
      mag2merged[mid] = ctr;

    ctr++;
  }

  in.close();
 
  paper ppr;
  vector<paper> merged(ctr, ppr);
  
  cout << "merged_papers.txt has been read." << endl;

  cout << endl;

// READ AMINER_STRUCTURED_PAPERS

  ifstream in_aminer("../0-data/aminer/aminer_structured_papers.txt");
  
  string line_aminer;
  getline(in_aminer, line_aminer);

  istringstream iss_aminer_ctr(line_aminer);

  int ctr_aminer;
  iss_aminer_ctr >> ctr_aminer;

  getline(in_aminer, line_aminer);

  for (int i = 0; i < ctr_aminer; i++)
  {
    string id = aminer_papers[i];
    int merged_id = aminer2merged[id];

    string line;

    getline(in_aminer, line);
    getline(in_aminer, line);

    int n_authors;
    getline(in_aminer, line);
    istringstream iss_n_authors(line);
    iss_n_authors >> n_authors;

    for (int j = 0; j < n_authors; j++)
    {
      string s_author, s_affil;
      
      getline(in_aminer, s_author);
      getline(in_aminer, s_affil);
    }

    int n_references;
    getline(in_aminer, line);
    istringstream iss_n_references(line);
    iss_n_references >> n_references;

    for (int j = 0; j < n_references; j++)
    {
      int reference;
      string s_reference;

      getline(in_aminer, s_reference);
      istringstream iss_reference(s_reference);
      iss_reference >> reference;

      merged[merged_id].references.insert(aminer2merged[aminer_papers[reference]]);
    }

    int n_keywords;
    getline(in_aminer, line);
    istringstream iss_n_keywords(line);
    iss_n_keywords >> n_keywords;

    for (int j = 0; j < n_keywords; j++)
    {
      string s_keyword;

      getline(in_aminer, s_keyword);
    }

    int n_fos;
    getline(in_aminer, line);
    istringstream iss_n_fos(line);
    iss_n_fos >> n_fos;

    for (int j = 0; j < n_fos; j++)
    {
      string s_fos;

      getline(in_aminer, s_fos);
    }

    getline(in_aminer, line);
  }

  in_aminer.close();

  cout << "aminer_structured_papers.txt has been read." << endl;

// READ MAG_STRUCTURED_PAPERS

  ifstream in_mag("../0-data/mag/mag_structured_papers.txt");
  
  string line_mag;
  getline(in_mag, line_mag);

  istringstream iss_mag_ctr(line_mag);

  int ctr_mag;
  iss_mag_ctr >> ctr_mag;

  getline(in_mag, line_mag);

  for (int i = 0; i < ctr_mag; i++)
  {
    string id = mag_papers[i];
    int merged_id = mag2merged[id];

    string line;

    getline(in_mag, line);
    getline(in_mag, line);

    int n_authors;
    getline(in_mag, line);
    istringstream iss_n_authors(line);
    iss_n_authors >> n_authors;

    for (int j = 0; j < n_authors; j++)
    {
      string s_author, s_affil;

      getline(in_mag, s_author);
      getline(in_mag, s_affil);
    }

    int n_references;
    getline(in_mag, line);
    istringstream iss_n_references(line);
    iss_n_references >> n_references;

    for (int j = 0; j < n_references; j++)
    {
      int reference;
      string s_reference;

      getline(in_mag, s_reference);
      istringstream iss_reference(s_reference);
      iss_reference >> reference;

      merged[merged_id].references.insert(mag2merged[mag_papers[reference]]);
    }

    int n_keywords;
    getline(in_mag, line);
    istringstream iss_n_keywords(line);
    iss_n_keywords >> n_keywords;

    for (int j = 0; j < n_keywords; j++)
    {
      string s_keyword;

      getline(in_mag, s_keyword);
    }

    int n_fos;
    getline(in_mag, line);
    istringstream iss_n_fos(line);
    iss_n_fos >> n_fos;

    for (int j = 0; j < n_fos; j++)
    {
      string s_fos;

      getline(in_mag, s_fos);
    }

    getline(in_mag, line);
  }

  in_mag.close();

  cout << "mag_structured_papers.txt has been read." << endl;

// WRITE TO FILE 

  cout << endl;

  ofstream out("merged_structured_papers_refs.txt");

  out << merged.size() << endl;

  int err = 0;
  for (int i = 0; i < merged.size(); i++)
  {
    out << endl;
    
    out << merged[i].references.size() << endl;

    set<int>::iterator it_references;
    for (it_references = merged[i].references.begin(); it_references != merged[i].references.end(); ++it_references)
      out << *it_references << endl;
  }

  out.close();

  cout << "merged_structured_papers_refs.txt has been written. (err: " << err << ")" << endl;

  return 0;
}
