#include <iostream>
#include <fstream>
#include <sstream>

#include <string>
#include <vector>
#include <map>

#include <algorithm>

#include <cstdlib>
#include <cmath>

using namespace std;

struct key_fos
{
  string kf;
  double score = 1;

  bool operator<(key_fos const & rhs) const
  {
    return score < rhs.score;
  }
};

int main()
{
  ifstream mkey_in("../0-data/2-merged/merged_keywords.txt");

  string mkey_line;
  getline(mkey_in, mkey_line);
  getline(mkey_in, mkey_line);

  vector<string> m_keywords;
  while (getline(mkey_in, mkey_line))
    m_keywords.push_back(mkey_line);

  mkey_in.close();
  cout << "merged_keywords.txt has been read." << endl;

  ifstream mfos_in("../0-data/2-merged/merged_fos.txt");

  string mfos_line;
  getline(mfos_in, mfos_line);
  getline(mfos_in, mfos_line);

  vector<string> m_fos;
  while (getline(mfos_in, mfos_line))
    m_fos.push_back(mfos_line);

  mfos_in.close();
  cout << "merged_fos.txt has been read." << endl;

  cout << endl;

  ifstream in("../0-data/2-merged/merged_structured_papers_keys.txt");

  string line;
  getline(in, line);
  istringstream num_iss(line);
  
  int num_papers;
  num_iss >> num_papers;   

  vector<vector<int>> keywords;
  vector<vector<int>> fos;

  while (getline(in, line))
  {
    vector<int> keys;

    getline(in, line);
    istringstream key_num_iss(line);
    int key_num;
    key_num_iss >> key_num;

    for (int i = 0; i < key_num; i++)
    {
      getline(in, line);
      istringstream key_iss(line);
      int key_no;
      key_iss >> key_no;
      keys.push_back(key_no);
    }

    keywords.push_back(keys);
   
    vector<int> foss;

    getline(in, line);
    istringstream fos_num_iss(line);
    int fos_num;
    fos_num_iss >> fos_num;

    for (int i = 0; i < fos_num; i++)
    {
      getline(in, line);
      istringstream fos_iss(line);
      int fos_no;
      fos_iss >> fos_no;
      foss.push_back(fos_no);
    }

    fos.push_back(foss);
  } 

  in.close();
  cout << "merged_structured_papers_keys.txt has been read." << endl;

  cout << endl;

  vector<int> keywords_gdist;

  ifstream key_gdist_in("../0-data/5-papercomm/key_dist.txt");

  string key_gdist_line;
  getline(key_gdist_in, key_gdist_line);
  getline(key_gdist_in, key_gdist_line);
  
  while (getline(key_gdist_in, key_gdist_line))
  {
    istringstream key_gdist_iss(key_gdist_line);
    int key_count;
    key_gdist_iss >> key_count;
    keywords_gdist.push_back(key_count);
  }

  key_gdist_in.close();
  cout << "key_dist.txt has been read." << endl;

  vector<int> fos_gdist;

  ifstream fos_gdist_in("../0-data/5-papercomm/fos_dist.txt");

  string fos_gdist_line;
  getline(fos_gdist_in, fos_gdist_line);
  getline(fos_gdist_in, fos_gdist_line);

  while (getline(fos_gdist_in, fos_gdist_line))
  {
    istringstream fos_gdist_iss(fos_gdist_line);
    int fos_count;
    fos_gdist_iss >> fos_count;
    fos_gdist.push_back(fos_count);
  }

  fos_gdist_in.close();
  cout << "fos_dist.txt has been read." << endl;

  cout << endl;

  ifstream n2c_in("../0-data/4-louvain/citation_node2comm.txt");

  vector<int> node2comm;
  
  string n2c_line;
  while (getline(n2c_in, n2c_line))
  {
    istringstream n2c_iss(n2c_line);
    int node, comm;
    n2c_iss >> node >> comm;
    node2comm.push_back(comm);
  }

  n2c_in.close();
  cout << "citation_node2comm.txt has been read." << endl;

  ifstream kcomm_in("../0-data/5-papercomm/topkcomm.txt");

  string kcomm_line;
  getline(kcomm_in, kcomm_line);
  istringstream kcomm_iss(kcomm_line);

  int k;
  kcomm_iss >> k;

  getline(kcomm_in, kcomm_line);

  for (int i = 1; i <= 5; i++)
  {
    cout << endl;
    string ii = to_string(i);

    getline(kcomm_in, kcomm_line);
    istringstream kcomm_iss(kcomm_line);
    int comm, comm_size;
    kcomm_iss >> comm >> comm_size;

    map<int, int> keywords_cdist;
    map<int, int> fos_cdist;

    for (int node = 0; node < node2comm.size(); node++)
    {
      if (node2comm[node] != comm) continue;

      for (int j = 0; j < keywords[node].size(); j++)
      {
        int curr_key = keywords[node][j];
 
        if (keywords_cdist.find(curr_key) == keywords_cdist.end())
          keywords_cdist[curr_key] = 1;
        else
          keywords_cdist[curr_key]++;
      }

      for (int j = 0; j < fos[node].size(); j++)
      {
        int curr_fos = fos[node][j];
 
        if (fos_cdist.find(curr_fos) == fos_cdist.end())
          fos_cdist[curr_fos] = 1;
        else
          fos_cdist[curr_fos]++;
      }
    }

    for (int opt = 0; opt < 3; opt++)
    {
      char copt = '0' + opt;
      string aopt(1, copt);

      vector<key_fos> key_cdist_vec;

      map<int, int>::iterator key_it;
      for (key_it = keywords_cdist.begin(); key_it != keywords_cdist.end(); ++key_it)
      {
        key_fos kf;
        kf.kf = m_keywords[key_it->first];

        double sizeratio = (double) comm_size / (double) num_papers;
        double expected = (double) keywords_gdist[key_it->first] * sizeratio;
        double ratio = (double) (key_it->second) / expected;

        double freq = (double) (key_it->second);

        if(opt == 0)
          kf.score = ratio * freq;
        else if(opt == 1)
          kf.score = ratio * sqrt(freq);
        else if(opt == 2)
          kf.score = sqrt(ratio) * freq;
        else
          kf.score = 0;

        key_cdist_vec.push_back(kf);
      } 

      make_heap(key_cdist_vec.begin(), key_cdist_vec.end());

      string key_cdist_filename =  "top_keywords_" + ii + "_" + aopt + ".txt";
      ofstream key_cdist_out(key_cdist_filename);

      key_cdist_out << key_cdist_vec.size() << endl;
      while (key_cdist_vec.size() > 0)
      {
        key_cdist_out << endl;

        key_cdist_out << fixed;
        key_cdist_out << key_cdist_vec.front().score << endl;
        key_cdist_out << scientific;

        key_cdist_out << key_cdist_vec.front().kf << endl;

        pop_heap(key_cdist_vec.begin(), key_cdist_vec.end());
        key_cdist_vec.pop_back();
      }

      key_cdist_out.close();
      cout << key_cdist_filename << " has been written." << endl;

      vector<key_fos> fos_cdist_vec;

      map<int, int>::iterator fos_it;
      for (fos_it = fos_cdist.begin(); fos_it != fos_cdist.end(); ++fos_it)
      {
        key_fos kf;
        kf.kf = m_fos[fos_it->first];
      
        double sizeratio = (double) comm_size / (double) num_papers;
        double expected = (double) fos_gdist[fos_it->first] * sizeratio;
        double ratio = (double) (fos_it->second) / expected;
      
        double freq = (double) (fos_it->second);

        if(opt == 0)
          kf.score = ratio * freq;
        else if(opt == 1)
          kf.score = ratio * sqrt(freq);
        else if(opt == 2)
          kf.score = sqrt(ratio) * freq;
        else
          kf.score = 0;

        fos_cdist_vec.push_back(kf);
      } 

      make_heap(fos_cdist_vec.begin(), fos_cdist_vec.end());

      string fos_cdist_filename = "top_fos_" + ii + "_" + aopt + ".txt";
      ofstream fos_cdist_out(fos_cdist_filename);

      fos_cdist_out << fos_cdist_vec.size() << endl;
      while (fos_cdist_vec.size() > 0)
      {
        fos_cdist_out << endl;

        fos_cdist_out << fixed;
        fos_cdist_out << fos_cdist_vec.front().score << endl;
        fos_cdist_out << scientific;

        fos_cdist_out << fos_cdist_vec.front().kf << endl;

        pop_heap(fos_cdist_vec.begin(), fos_cdist_vec.end());
        fos_cdist_vec.pop_back();
      }

      fos_cdist_out.close();
      cout << fos_cdist_filename << " has been written." << endl;
    }
  }

  kcomm_in.close();

  return 0;
}
