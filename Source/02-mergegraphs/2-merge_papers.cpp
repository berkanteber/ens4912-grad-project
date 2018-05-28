#include <iostream>
#include <fstream>
#include <sstream>

#include <string>
#include <vector>
#include <set>
#include <map>

#include "json.hpp"
#include "strfunc.hpp"

using namespace std;
using json = nlohmann::json;

struct pid
{
  string aid = "#=#=#";
  string mid = "#=#=#";
};

int main(int argc, char** argv)
{
  set<string> aminer;

  string a_filename = "../0-data/aminer/aminer_papers.txt";
  ifstream a_in(a_filename);

  string a_line;
  getline(a_in, a_line);
  getline(a_in, a_line);

  while (getline(a_in, a_line))
    aminer.insert(a_line);

  a_in.close();

  cout << "aminer_papers.txt has been read." << endl;  

  set<string> mag;

  string m_filename = "../0-data/mag/mag_papers.txt";
  ifstream m_in(m_filename);

  string m_line;
  getline(m_in, m_line);
  getline(m_in, m_line);

  while (getline(m_in, m_line))
    mag.insert(m_line);

  m_in.close();

  cout << "mag_papers.txt has been read." << endl;

  cout << endl;

  map <string, string> a2m;
  map <string, string> m2a;

  ifstream inp("../../linking_relations.txt");

  int err = 0;

  string line;
  while(getline(inp, line))
  {
    istringstream iss(line);

    json j;
    iss >> j;

    string aid = j["aid"];
    string mid = j["mid"];

    if(aminer.find(beautify(aid)) != aminer.end() && mag.find(beautify(mid)) != mag.end())
    {
      a2m[beautify(aid)] = beautify(mid);
      m2a[beautify(mid)] = beautify(aid);
    }
    else err++;
  }

  inp.close();

  cout << "linking_relations.txt has been read." << " (err: " << err << ")" << endl << endl;

  vector<pid> vec;

  set<string>::iterator com_it;
  for (com_it = aminer.begin(); com_it != aminer.end(); ++com_it)
  {
    string aid = *com_it;

    if (a2m.find(aid) != a2m.end())
    {
      string mid = a2m[aid];

      pid p;

      p.aid = aid;
      p.mid = mid;

      vec.push_back(p);
    }
  }

  set<string>::iterator a_it;
  for (a_it = aminer.begin(); a_it != aminer.end(); ++a_it)
  {
    string aid = *a_it;

    if (a2m.find(aid) == a2m.end())
    {
      pid p;

      p.aid = aid;
      p.mid = "#=#=#";

      vec.push_back(p);
    }
  }

  set<string>::iterator m_it;
  for (m_it = mag.begin(); m_it != mag.end(); ++m_it)
  {
    string mid = *m_it;

    if (m2a.find(mid) == m2a.end())
    {
      pid p;

      p.aid = "#=#=#";
      p.mid = mid;

      vec.push_back(p);
    }
  }

  ofstream out("merged_papers.txt");

  out << vec.size() << endl;

  for (int i = 0; i < vec.size(); i++)
    out << endl << vec[i].aid << endl << vec[i].mid << endl;

  out.close();

  cout << endl << "merged_papers.txt has been written." << endl;

  return 0;
}
