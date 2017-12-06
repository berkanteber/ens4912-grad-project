#include <iostream>
#include <fstream>
#include <sstream>

#include <string>
#include <set>

#include "json.hpp"
#include "strfunc.hpp"

using namespace std;
using json = nlohmann::json;

int main(int argc, char** argv)
{
  set <string> files;
  set <string> authors;
  set <string> affiliations;
  set <string> keywords;
  set <string> fieldsofstudy;

  set <string> papers;

  string filename = "";

  for(int i = 1; i < argc; i++)
  {
    filename = argv[i];
    ifstream inf(filename);
    
    string pretty_filename = filename.substr(filename.rfind("/") + 1);
    
    string line;
    while(getline(inf, line))
    { 
      istringstream iss(line);
      
      json j;
      iss >> j;

      if(j.count("id") && j["id"] != NULL)
      {
        string id = j["id"];
        papers.insert(beautify(id));
      } else continue;

      if(j.count("authors"))
      {
        json j_authors = j["authors"];

        for (json::iterator it = j_authors.begin(); it != j_authors.end(); ++it) 
        {
          json j_author = *it;

          if(j_author.count("name") && j_author["name"] != NULL)
          {
            string name = j_author["name"];
            authors.insert(beautify(name));
          } 

          if(j_author.count("org") && j_author["org"] != NULL)
          {
            string org = j_author["org"];
            affiliations.insert(beautify(org));
          }
        } 
      }

      if(j.count("keywords"))
      {
        json j_keywords = j["keywords"];

        for(json::iterator it = j_keywords.begin(); it != j_keywords.end(); ++it)
        {
          if(*it != NULL)
          {
            string keyword = *it;
            keywords.insert(beautify(keyword));
          }
        }
      }

      if(j.count("fos"))
      {
        json j_fos = j["fos"];

        for(json::iterator it = j_fos.begin(); it != j_fos.end(); ++it)
        {
          if(*it != NULL)
          {
            string fos = *it;
            fieldsofstudy.insert(beautify(fos));
          }
        }
      }
    }

    files.insert(pretty_filename);
    cout << pretty_filename << " has been read." << endl;
  
    inf.close();
  }

  cout << endl;

  ofstream files_outf("files.txt");

  files_outf << files.size() << endl << endl;

  set<string>::iterator files_iter;
  for (files_iter = files.begin(); files_iter != files.end(); ++files_iter)
    files_outf << (*files_iter) << endl;
  
  files_outf.close();

  cout << "files.txt has been written." << endl;

  ofstream papers_outf("papers.txt");

  papers_outf << papers.size() << endl << endl;

  set<string>::iterator papers_iter;
  for (papers_iter = papers.begin(); papers_iter != papers.end(); ++papers_iter)
    papers_outf << (*papers_iter) << endl;

  papers_outf.close();

  cout << "papers.txt has been written." << endl;

  ofstream authors_outf("authors.txt");

  authors_outf << authors.size() << endl << endl;

  set<string>::iterator authors_iter;
  for (authors_iter = authors.begin(); authors_iter != authors.end(); ++authors_iter)
    authors_outf << (*authors_iter) << endl;

  authors_outf.close();

  cout << "authors.txt has been written." << endl;

  ofstream affils_outf("affils.txt");

  affils_outf << affiliations.size() << endl << endl;

  set<string>::iterator affils_iter;
  for (affils_iter = affiliations.begin(); affils_iter != affiliations.end(); ++affils_iter)
    affils_outf << (*affils_iter) << endl;

  affils_outf.close();

  cout << "affils.txt has been written." << endl;
  
  ofstream keywords_outf("keywords.txt");

  keywords_outf << keywords.size() << endl << endl;

  set<string>::iterator keywords_iter;
  for (keywords_iter = keywords.begin(); keywords_iter != keywords.end(); ++keywords_iter)
    keywords_outf << (*keywords_iter) << endl;  

  keywords_outf.close();

  cout << "keywords.txt has been written." << endl;

  ofstream fos_outf("fos.txt");

  fos_outf << fieldsofstudy.size() << endl << endl;

  set<string>::iterator fos_iter;
  for (fos_iter = fieldsofstudy.begin(); fos_iter != fieldsofstudy.end(); ++fos_iter)
    fos_outf << (*fos_iter) << endl;
  
  fos_outf.close();
  
  cout << "fos.txt has been written." << endl;
  
  return 0;
}
