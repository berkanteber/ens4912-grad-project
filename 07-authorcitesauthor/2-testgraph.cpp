#include <iostream>
#include <fstream>
#include <sstream>

#include <string>
#include <vector>

using namespace std;

int main()
{
  ifstream author_in("../0-data/2-merged/merged_authors.txt");

  string author_line;
  getline(author_in, author_line);
  getline(author_in, author_line);

  int kamerkaya = -1;

  vector<string> authors;

  int ctr = 0;
  while (getline(author_in, author_line))
  {
    string author = author_line;
    if (author == "Kamer Kaya") kamerkaya = ctr;
    
    authors.push_back(author);   
    ctr++;
  }

  author_in.close();

  cout << "merged_authors.txt has been read.";
  cout << "(Kamer Kaya: " << kamerkaya << ")" << endl << endl; 

  ifstream rowptr_in("author_cites_author_rowptr.txt");

  string rowptr_line;
  getline(rowptr_in, rowptr_line);
  getline(rowptr_in, rowptr_line);

  vector<long long int> rowptr;
  while (getline(rowptr_in, rowptr_line))
  {
    istringstream rowptr_iss(rowptr_line);
    long long int rowptr_num;
    rowptr_iss >> rowptr_num;
    rowptr.push_back(rowptr_num);
  }
  
  rowptr_in.close();

  cout << "author_cites_author_rowptr.txt has been read." << endl;

  ifstream colind_in("author_cites_author_colind.txt");

  string colind_line;
  getline(colind_in, colind_line);
  getline(colind_in, colind_line);

  vector<int> colind;
  while (getline(colind_in, colind_line))
  {
    istringstream colind_iss(colind_line);
    int colind_num;
    colind_iss >> colind_num;
    colind.push_back(colind_num);
  }
  
  colind_in.close();

  cout << "author_cites_author_colind.txt has been read." << endl;

  ifstream weights_in("author_cites_author_weights.txt");

  string weights_line;
  getline(weights_in, weights_line);
  getline(weights_in, weights_line);

  vector<int> weights;
  while (getline(weights_in, weights_line))
  {
    istringstream weights_iss(weights_line);
    int weights_num;
    weights_iss >> weights_num;
    weights.push_back(weights_num);
  }
  
  weights_in.close();

  cout << "author_cites_author_weights.txt has been read." << endl;

  cout << endl;

  
  ofstream out("out.txt");  

  long long int start = rowptr[kamerkaya];
  long long int end = rowptr[kamerkaya + 1];

  for (long long int i = start; i < end; i++)
    out << weights[i] << endl << authors[colind[i]] << endl << endl;

  out.close();

  cout << "out.txt has been written." << endl;

  return 0;
}
