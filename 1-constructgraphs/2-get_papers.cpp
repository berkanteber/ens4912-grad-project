#include <iostream>
#include <fstream>
#include <sstream>

#include <string>
#include <vector>
#include <map>

#include "json.hpp"
#include "strfunc.hpp"

using namespace std;
using json = nlohmann::json;

struct paper
{
  int file_id = -1;
  int year = -1;

  int n_authors = 0;
  vector <int> authors;
  vector <int> affils;

  int n_references = 0;
  vector <int> references;

  int n_keywords = 0;
  vector <int> keywords;

  int n_fos = 0;
  vector <int> fos;
};

void read_and_map(map <string, int> & tobemapped, string filename)
{
  ifstream inf(filename);

  string line;
  getline(inf, line);
  getline(inf, line);

  int count = 0;
  while(getline(inf, line))
    tobemapped[line] = count++;

  inf.close();

  cout << filename << " has been read." << endl;

  return;
}

int main(int argc, char** argv)
{
  map <string, int> papers;
  read_and_map(papers, "papers.txt");

  map <string, int> files;
  read_and_map(files, "files.txt");

  map <string, int> authors;
  read_and_map(authors, "authors.txt");

  map <string, int> affils;
  read_and_map(affils, "affils.txt");

  map <string, int> keywords;
  read_and_map(keywords, "keywords.txt");

  map <string, int> fieldsofstudy;
  read_and_map(fieldsofstudy, "fos.txt");

  paper p;
  vector <paper> str_papers(papers.size(), p);

  cout << endl;

  int err_id = 0;
  int err_file = 0;
  int err_author = 0;
  int err_affil = 0;
  int err_reference = 0;
  int err_keyword = 0;
  int err_fos = 0;

  string filename = "";
  for(int i = 1; i < argc; i++)
  {
    filename = argv[i];
   
    ifstream in(filename);

    string pretty_filename = filename.substr(filename.rfind("/") + 1);
    
    int file_id = -1;
    if(files.find(pretty_filename) != files.end()) 
      file_id = files[pretty_filename];
    else
      err_file++;

    string line;
    while(getline(in, line))
    {
      istringstream iss(line);

      json j;
      iss >> j;      

      string id;
     
      if(j.count("id") && j["id"] != NULL)
        id = j["id"];
      else
        continue;

      string b_id = beautify(id);

      int n_id = -1;
      if(papers.find(b_id) != papers.end())
        n_id = papers[b_id];
      else
      {
        err_id++;
        continue;
      }

      paper pap;
      pap.file_id = file_id;

      if(j.count("year") && j["year"] != NULL)
        pap.year = j["year"];
      
      if(j.count("authors"))
      {
        json j_authors = j["authors"];

        for (json::iterator it = j_authors.begin(); it != j_authors.end(); ++it)
        {
          json j_author = *it;

          if(j_author.count("name") && j_author["name"] != NULL)
          {
            string name = j_author["name"];
            string b_name = beautify(name);

            int n_name = -1;
            if(authors.find(b_name) != authors.end())
              n_name = authors[b_name];
            else
            {
              err_author++;
              continue;
            }

            pap.authors.push_back(n_name);
            pap.n_authors++;
             
            int n_org = -1;
            if(j_author.count("org") && j_author["org"] != NULL)
            {
              string org = j_author["org"];
              string b_org = beautify(org);
              
              if(affils.find(b_org) != affils.end())
                  n_org = affils[b_org];
              else
                  err_affil++;              
            }
            
            pap.affils.push_back(n_org);
          }
        }
      }

      if(j.count("references"))
      {
        json j_references = j["references"];

        for (json::iterator it = j_references.begin(); it != j_references.end(); ++it)
        {
          if(*it != NULL)
          {
            string reference = *it;
            string b_reference = beautify(reference);

            int n_reference = -1;
            if(papers.find(b_reference) != papers.end()) 
              n_reference = papers[b_reference];
            else
            {
              err_reference++;
              continue;
            }
              
            pap.references.push_back(n_reference);
            pap.n_references++;
          }
        }
      }

      if(j.count("keywords"))
      {
        json j_keywords = j["keywords"];

        for (json::iterator it = j_keywords.begin(); it != j_keywords.end(); ++it)
        {
          if(*it != NULL)
          {
            string keyword = *it;
            string b_keyword = beautify(keyword);

            int n_keyword = -1;
            if(keywords.find(b_keyword) != keywords.end())
              n_keyword = keywords[b_keyword];
            else
            {
              err_keyword++;
              continue;
            }
              
            pap.keywords.push_back(n_keyword);
            pap.n_keywords++;
          }
        }
      }

      if(j.count("fos"))
      {
        json j_fos = j["fos"];

        for (json::iterator it = j_fos.begin(); it != j_fos.end(); ++it)
        {
          if(*it != NULL)
          {
            string field = *it;
            string b_field = beautify(field);

            int n_field = -1;
            if(fieldsofstudy.find(b_field) != fieldsofstudy.end())
              n_field = fieldsofstudy[b_field];
            else
            {
              err_fos++;
              continue;
            }            

            pap.fos.push_back(n_field);
            pap.n_fos++;
          }
        }
      }
      
      if(n_id != -1 && n_id < str_papers.size())
        str_papers[n_id] = pap;
    }

    in.close();
  
    cout << pretty_filename << " has been read." << endl;
  }

  cout << endl;

  cout << "err_id: " << err_id << endl
       << "err_file: " << err_file << endl
       << "err_author: " << err_author << endl
       << "err_affil: " << err_affil << endl
       << "err_reference: " << err_reference << endl
       << "err_keyword: " << err_keyword << endl
       << "err_fos: " << err_fos << endl;

  ofstream out("structured_papers.txt");  

  out << str_papers.size() << endl << endl;

  int err = 0;
  for (int i = 0; i < str_papers.size(); i++)
  {
    paper pap = str_papers[i];

    if(pap.file_id == -1)
    {
      out << -1 << endl << endl;
      err += 1;
      continue;
    }

    out << pap.file_id << endl;
    out << pap.year << endl;

    out << pap.n_authors << endl;
    for (int j = 0; j < pap.n_authors; j++)
      out << pap.authors[j] << endl << pap.affils[j] << endl;

    out << pap.n_references << endl;
    for (int j = 0; j < pap.n_references; j++)
      out << pap.references[j] << endl;

    out << pap.n_keywords << endl;
    for (int j = 0; j < pap.n_keywords; j++)
      out << pap.keywords[j] << endl;

    out << pap.n_fos << endl;
    for (int j = 0; j < pap.n_fos; j++)
      out << pap.fos[j] << endl;
  
    out << endl;
  }

  out.close();

  cout << endl;
  cout << "err: " << err << endl;
  cout << "structured_papers.txt has been written." << endl;

  return 0;
}
