/***********************
No reference: 192098777
No citations: 183778939
Disconnected: 164039047
***********************/

#include <iostream>
#include <fstream>
#include <sstream>

#include <string>
#include <vector>

using namespace std;

int main()
{
  ifstream cites_in("../0-data/3-crs/paper_cites_paper_rowptr.txt");

  string cites_line;
  getline(cites_in, cites_line);
  getline(cites_in, cites_line);

  vector<long long int> cites;
  while (getline(cites_in, cites_line))
  {
    istringstream cites_iss(cites_line);
    long long int cites_num;
    cites_iss >> cites_num;
    cites.push_back(cites_num);
  }
  
  cites_in.close();
  cout << "paper_cites_paper_rowptr.txt has been read." << endl;

  ifstream citedby_in("../0-data/3-crs/paper_citedby_paper_rowptr.txt");

  string citedby_line;
  getline(citedby_in, citedby_line);
  getline(citedby_in, citedby_line);

  vector<long long int> citedby;
  while (getline(citedby_in, citedby_line))
  {
    istringstream citedby_iss(citedby_line);
    long long int citedby_num;
    citedby_iss >> citedby_num;
    citedby.push_back(citedby_num);
  }
  
  citedby_in.close();
  cout << "paper_citedby_paper_rowptr.txt has been read." << endl;

  cout << endl;

  int norefs = 0;
  int nocite = 0;
  int noboth = 0;

  int len = -1;
  if(cites.size() == citedby.size())
    len = cites.size() - 1;

  for (int i = 0; i < len; i++)
  {
    if(cites[i] == cites[i+1])
      norefs++;
    if(citedby[i] == citedby[i+1])
      nocite++;
    if(cites[i] == cites[i+1] && citedby[i] == citedby[i+1])
      noboth++;
  }
  
  ofstream out("alone.txt");  

  out << "No reference: " << norefs << endl;
  out << "No citations: " << nocite << endl;
  out << "Disconnected: " << noboth << endl;

  out.close();

  cout << "alone.txt has been written." << endl;

  return 0;
}
