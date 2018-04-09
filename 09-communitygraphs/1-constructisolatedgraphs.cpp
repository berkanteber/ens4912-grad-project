#include <iostream>
#include <fstream>
#include <sstream>

#include <string>
#include <vector>

using namespace std;

int main()
{
  vector<long long int> rowptr;

  ifstream rowptr_in("../00-data/03-crs/paper_cites_paper_rowptr.txt");

  string rowptr_line;
  getline(rowptr_in, rowptr_line);
  getline(rowptr_in, rowptr_line);

  while (getline(rowptr_in, rowptr_line))
  {
    istringstream iss(rowptr_line);
    long long int num;
    iss >> num;
    rowptr.push_back(num);
  }

  rowptr_in.close();
  cout << "paper_cites_paper_rowptr.txt has been read." << endl;

  vector<int> colind;

  ifstream colind_in("../00-data/03-crs/paper_cites_paper_colind.txt");

  string colind_line;
  getline(colind_in, colind_line);
  getline(colind_in, colind_line);

  while (getline(colind_in, colind_line))
  {
    istringstream iss(colind_line);
    int num;
    iss >> num;
    colind.push_back(num);
  }

  colind_in.close();
  cout << "paper_cites_paper_colind.txt has been read." << endl;

  cout << endl;

  vector<int> node2comm;

  ifstream n2c_in("../00-data/04-louvain/citation_node2comm.txt");

  string n2c_line;

  while (getline(n2c_in, n2c_line))
  {
    istringstream iss(n2c_line);
    int v, c;
    iss >> v >> c;
    node2comm.push_back(c);
  }

  n2c_in.close();
  cout << "citation_node2comm.txt has been read." << endl;

  cout << endl;

  while (node2comm.size() < rowptr.size() - 1)
  {
    node2comm.push_back(-1);
  }

  ofstream out_1485264_r("isolated_1485264_rowptr.txt");
  ofstream out_129635231_r("isolated_129635231_rowptr.txt");
  ofstream out_100137693_r("isolated_100137693_rowptr.txt");
  ofstream out_39538415_r("isolated_39538415_rowptr.txt");
  ofstream out_55833303_r("isolated_55833303_rowptr.txt");
  ofstream out_1485264_c("isolated_1485264_colind.txt");
  ofstream out_129635231_c("isolated_129635231_colind.txt");
  ofstream out_100137693_c("isolated_100137693_colind.txt");
  ofstream out_39538415_c("isolated_39538415_colind.txt");
  ofstream out_55833303_c("isolated_55833303_colind.txt");

  out_1485264_r << 0 << endl;
  out_129635231_r << 0 << endl;
  out_100137693_r << 0 << endl;
  out_39538415_r << 0 << endl;
  out_55833303_r << 0 << endl;

  long long int ctr_1485264 = 0;
  long long int ctr_129635231 = 0;
  long long int ctr_100137693 = 0;
  long long int ctr_39538415 = 0;
  long long int ctr_55833303 = 0;

  for (int i = 0; i < rowptr.size() - 1; i++)
  {
    if (node2comm[i] == 1485264)
      for (int j = rowptr[i]; j < rowptr[i + 1]; j++)
        if (node2comm[colind[j]] == 1485264)
        {
          out_1485264_c << colind[j] << endl;
          ctr_1485264 += 1;
        }
    
    if (node2comm[i] == 129635231)
      for (int j = rowptr[i]; j < rowptr[i + 1]; j++)
        if (node2comm[colind[j]] == 129635231)
        {
          out_129635231_c << colind[j] << endl;
          ctr_129635231 += 1;
        }
    
    if (node2comm[i] == 100137693)
      for (int j = rowptr[i]; j < rowptr[i + 1]; j++)
        if (node2comm[colind[j]] == 100137693)
        {
          out_100137693_c << colind[j] << endl;
          ctr_100137693 += 1;
        }
    
    if (node2comm[i] == 39538415)
      for (int j = rowptr[i]; j < rowptr[i + 1]; j++)
        if (node2comm[colind[j]] == 39538415)
        {
          out_39538415_c << colind[j] << endl;
          ctr_39538415 += 1;
        }
    
    if (node2comm[i] == 55833303)
      for (int j = rowptr[i]; j < rowptr[i + 1]; j++)
        if (node2comm[colind[j]] == 55833303)
        {
          out_55833303_c << colind[j] << endl;
          ctr_55833303 += 1;
        }

    out_1485264_r << ctr_1485264 << endl;
    out_129635231_r << ctr_129635231 << endl;
    out_100137693_r << ctr_100137693 << endl;
    out_39538415_r << ctr_39538415 << endl;
    out_55833303_r << ctr_55833303 << endl;
  }

  out_1485264_r.close();
  out_129635231_r.close();
  out_100137693_r.close();
  out_39538415_r.close();
  out_55833303_r.close();
  out_1485264_c.close();
  out_129635231_c.close();
  out_100137693_c.close();
  out_39538415_c.close();
  out_55833303_c.close();

  return 0;
}
