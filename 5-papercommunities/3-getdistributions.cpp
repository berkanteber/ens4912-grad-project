#include <iostream>
#include <fstream>
#include <sstream>

#include <string>
#include <vector>

using namespace std;

int main()
{
  ifstream key_in("../0-data/2-merged/merged_keywords.txt");
  
  string key_line;
  getline(key_in, key_line);
  istringstream key_iss(key_line);
  
  int key_num;
  key_iss >> key_num;

  key_in.close();
  cout << "merged_keywords.txt has been read." << endl;

  ifstream fos_in("../0-data/2-merged/merged_fos.txt");
  
  string fos_line;
  getline(fos_in, fos_line);
  istringstream fos_iss(fos_line);
  
  int fos_num;
  fos_iss >> fos_num;

  fos_in.close();
  cout << "merged_fos.txt has been read." << endl;

  cout << endl;

  vector<int> keydist(key_num, 0);
  vector<int> fosdist(fos_num, 0);

  ifstream in("../0-data/2-merged/merged_structured_papers_keys.txt");

  string line;
  getline(in, line);
  
  while (getline(in, line))
  {
    getline(in, line);
    istringstream key_num_iss(line);
    int key_num;
    key_num_iss >> key_num;

    for (int i = 0; i < key_num; i++)
    {
      getline(in, line);
      istringstream key_iss(line);
      int key;
      key_iss >> key;
      keydist[key]++;
    }
   
    getline(in, line);
    istringstream fos_num_iss(line);
    int fos_num;
    fos_num_iss >> fos_num;

    for (int i = 0; i < fos_num; i++)
    {
      getline(in, line);
      istringstream fos_iss(line);
      int fos;
      fos_iss >> fos;
      fosdist[fos]++;
    }
  } 

  in.close();
  cout << "merged_structured_papers_keys.txt has been read." << endl;

  cout << endl;

  ofstream key_out("key_dist.txt");

  key_out << keydist.size() << endl << endl;
  for (int i = 0; i < keydist.size(); i++)
    key_out << keydist[i] << endl;

  key_out.close();
  cout << "key_dist.txt has been written." << endl;

  ofstream fos_out("fos_dist.txt");

  fos_out << fosdist.size() << endl << endl;
  for (int i = 0; i < fosdist.size(); i++)
    fos_out << fosdist[i] << endl;

  fos_out.close();
  cout << "fos_dist.txt has been written." << endl;

  return 0;
}
