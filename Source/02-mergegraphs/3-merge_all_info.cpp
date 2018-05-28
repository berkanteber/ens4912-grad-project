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
  int a_file_id = -1;
  int m_file_id = -1;

  int a_year = -1;
  int m_year = -1;
  
  vector<int> a_authors;
  vector<int> a_affils;

  vector<int> m_authors;
  vector<int> m_affils;
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

  vector<string> aminer_authors;
  read_into_vector("../0-data/aminer/aminer_authors.txt", aminer_authors);

  vector<string> aminer_affils;
  read_into_vector("../0-data/aminer/aminer_affils.txt", aminer_affils);

  cout << endl;
  
// READ MAG

  vector<string> mag_papers;
  read_into_vector("../0-data/mag/mag_papers.txt", mag_papers);

  vector<string> mag_authors;
  read_into_vector("../0-data/mag/mag_authors.txt", mag_authors);

  vector<string> mag_affils;
  read_into_vector("../0-data/mag/mag_affils.txt", mag_affils);

  cout << endl;
 
// READ MERGED 

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

  map<string, int> merged_authors;
  read_into_map("../0-data/merged/merged_authors.txt", merged_authors);

  map<string, int> merged_affils;
  read_into_map("../0-data/merged/merged_affils.txt", merged_affils);

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
    istringstream iss_file(line);
    iss_file >> merged[merged_id].a_file_id;

    getline(in_aminer, line);
    istringstream iss_year(line);
    iss_year >> merged[merged_id].a_year;

    int n_authors;
    getline(in_aminer, line);
    istringstream iss_n_authors(line);
    iss_n_authors >> n_authors;

    for (int j = 0; j < n_authors; j++)
    {
      int author, affil;
      string s_author, s_affil;

      getline(in_aminer, s_author);
      istringstream iss_author(s_author);
      iss_author >> author;

      getline(in_aminer, s_affil);
      istringstream iss_affil(s_affil);
      iss_affil >> affil;

      merged[merged_id].a_authors.push_back(merged_authors[aminer_authors[author]]);
      
      if(affil == -1)
        merged[merged_id].a_affils.push_back(-1);
      else
        merged[merged_id].a_affils.push_back(merged_affils[aminer_affils[affil]]);
    }

    int n_references;
    getline(in_aminer, line);
    istringstream iss_n_references(line);
    iss_n_references >> n_references;

    for (int j = 0; j < n_references; j++)
    {
      string s_reference;
      getline(in_aminer, s_reference);
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
    istringstream iss_file(line);
    iss_file >> merged[merged_id].m_file_id;

    getline(in_mag, line);
    istringstream iss_year(line);
    iss_year >> merged[merged_id].m_year;

    int n_authors;
    getline(in_mag, line);
    istringstream iss_n_authors(line);
    iss_n_authors >> n_authors;

    for (int j = 0; j < n_authors; j++)
    {
      int author, affil;
      string s_author, s_affil;

      getline(in_mag, s_author);
      istringstream iss_author(s_author);
      iss_author >> author;

      getline(in_mag, s_affil);
      istringstream iss_affil(s_affil);
      iss_affil >> affil;

      merged[merged_id].m_authors.push_back(merged_authors[mag_authors[author]]);
      
      if(affil == -1)
        merged[merged_id].m_affils.push_back(-1);
      else
        merged[merged_id].m_affils.push_back(merged_affils[mag_affils[affil]]);
    }

    int n_references;
    getline(in_mag, line);
    istringstream iss_n_references(line);
    iss_n_references >> n_references;

    for (int j = 0; j < n_references; j++)
    {
      string s_reference;
      getline(in_mag, s_reference);
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

// WRITE TO FILES 

  cout << endl;

  ofstream out_aminer("merged_structured_papers_info_aminer.txt");
  ofstream out_mag("merged_structured_papers_info_mag.txt");

  out_aminer << merged.size() << endl;
  out_mag << merged.size() << endl;

  int err = 0;
  for (int i = 0; i < merged.size(); i++)
  {
    out_aminer << endl;
    out_mag << endl;

    int a_file = merged[i].a_file_id;
    int m_file = merged[i].m_file_id;

    out_aminer << a_file << endl << m_file << endl;
    out_mag << a_file << endl << m_file << endl;

    if(a_file == -1 && m_file == -1)
    {
      err++;
      continue;
    }

    else if(a_file == -1)
    {
      out_aminer << merged[i].m_year << endl;
      out_mag << merged[i].m_year << endl;

      out_aminer << merged[i].m_authors.size() << endl;
      out_mag << merged[i].m_authors.size() << endl;

      for (int j = 0; j < merged[i].m_authors.size(); j++)
      {
        out_aminer << merged[i].m_authors[j] << endl;
        out_mag << merged[i].m_authors[j] << endl;
       
        out_aminer << merged[i].m_affils[j] << endl;
        out_mag << merged[i].m_affils[j] << endl;
      }
    }

    else if(m_file == -1)
    {
      out_aminer << merged[i].a_year << endl;
      out_mag << merged[i].a_year << endl;

      out_aminer << merged[i].a_authors.size() << endl;
      out_mag << merged[i].a_authors.size() << endl;

      for (int j = 0; j < merged[i].a_authors.size(); j++)
      {
        out_aminer << merged[i].a_authors[j] << endl;
        out_mag << merged[i].a_authors[j] << endl;
       
        out_aminer << merged[i].a_affils[j] << endl;
        out_mag << merged[i].a_affils[j] << endl;
      }
    }
    
    else
    {
      out_aminer << merged[i].a_year << endl;
      out_mag << merged[i].m_year << endl;

      out_aminer << merged[i].a_authors.size() << endl;
      for (int j = 0; j < merged[i].a_authors.size(); j++)
      {
        out_aminer << merged[i].a_authors[j] << endl;
        out_aminer << merged[i].a_affils[j] << endl;
      }

      out_mag << merged[i].m_authors.size() << endl;
      for (int j = 0; j < merged[i].m_authors.size(); j++)
      {
        out_mag << merged[i].m_authors[j] << endl;
        out_mag << merged[i].m_affils[j] << endl;
      }
    }
  }

  out_aminer.close();
  out_mag.close();

  cout << "merged_structured_papers_info_aminer.txt has been written. (err: " << err << ")" << endl;
  cout << "merged_structured_papers_info_mag.txt has been written. (err: " << err << ")" << endl;

  return 0;
}
