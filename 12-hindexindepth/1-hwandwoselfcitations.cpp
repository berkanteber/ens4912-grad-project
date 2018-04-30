#include <iostream>
#include <fstream>
#include <sstream>

#include <string>
#include <vector>
#include <set>

#include <algorithm>

using namespace std;

int main()
{
  vector<int> awp_rowptr;

  ifstream awp_rowptr_in("../00-data/03-crs/author_writes_paper_rowptr.txt");

  string awp_rowptr_line;
  getline(awp_rowptr_in, awp_rowptr_line);
  getline(awp_rowptr_in, awp_rowptr_line);

  while (getline(awp_rowptr_in, awp_rowptr_line))
  {
    istringstream iss(awp_rowptr_line);
    int num;
    iss >> num;
    awp_rowptr.push_back(num);
  }

  awp_rowptr_in.close();
  cout << "author_writes_paper_rowptr.txt has been read." << endl;

  vector<int> awp_colind;

  ifstream awp_colind_in("../00-data/03-crs/author_writes_paper_colind.txt");

  string awp_colind_line;
  getline(awp_colind_in, awp_colind_line);
  getline(awp_colind_in, awp_colind_line);

  while (getline(awp_colind_in, awp_colind_line))
  {
    istringstream iss(awp_colind_line);
    int num;
    iss >> num;
    awp_colind.push_back(num);
  }

  awp_colind_in.close();
  cout << "author_writes_paper_colind.txt has been read." << endl;

  cout << endl;

  vector<int> pcp_rowptr_1;

  ifstream pcp_rowptr_in_1("../00-data/09-communitygraphs/isolated_1485264_citedby_rowptr.txt");

  string pcp_rowptr_line_1;
  getline(pcp_rowptr_in_1, pcp_rowptr_line_1);
  getline(pcp_rowptr_in_1, pcp_rowptr_line_1);

  while (getline(pcp_rowptr_in_1, pcp_rowptr_line_1))
  {
    istringstream iss(pcp_rowptr_line_1);
    int num;
    iss >> num;
    pcp_rowptr_1.push_back(num);
  }

  pcp_rowptr_in_1.close();
  cout << "paper_citedby_paper_rowptr.txt has been read." << endl;

  vector<int> pcp_colind_1;

  ifstream pcp_colind_in_1("../00-data/09-communitygraphs/isolated_1485264_citedby_colind.txt");

  string pcp_colind_line_1;
  getline(pcp_colind_in_1, pcp_colind_line_1);
  getline(pcp_colind_in_1, pcp_colind_line_1);

  while (getline(pcp_colind_in_1, pcp_colind_line_1))
  {
    istringstream iss(pcp_colind_line_1);
    int num;
    iss >> num;
    pcp_colind_1.push_back(num);
  }

  pcp_colind_in_1.close();
  cout << "paper_citedby_paper_colind.txt has been read." << endl;

  cout << endl;

  vector<int> hindexw_1;
  vector<int> hindexwo_1;

  for (int author = 0; author < awp_rowptr.size() - 1; author++)
  {
    vector<int> citationcounts_w;

    set<int> writtenbyauthor_w;
    for (long long int col = awp_rowptr[author]; col < awp_rowptr[author+1]; col++)
      writtenbyauthor_w.insert(awp_colind[col]);

    for (set<int>::iterator it = writtenbyauthor_w.begin(); it != writtenbyauthor_w.end(); ++it)
    {
      int paperid = *it;
       
      int citationcount = 0;
      for (long long int rcol = pcp_rowptr_1[paperid]; rcol < pcp_rowptr_1[paperid+1]; rcol++)
        citationcount++;

      citationcounts_w.push_back(citationcount);
    }

    make_heap(citationcounts_w.begin(), citationcounts_w.end());

    int ctr_w = 1;
    while (citationcounts_w.size() > 0 && citationcounts_w.front() >= ctr_w)
    {
      pop_heap(citationcounts_w.begin(), citationcounts_w.end());
      citationcounts_w.pop_back();

      ctr_w++;
    }

    hindexw_1.push_back(ctr_w-1);
    
    vector<int> citationcounts_wo;

    set<int> writtenbyauthor_wo;
    for (long long int col = awp_rowptr[author]; col < awp_rowptr[author+1]; col++)
      writtenbyauthor_wo.insert(awp_colind[col]);

    for (set<int>::iterator it = writtenbyauthor_wo.begin(); it != writtenbyauthor_wo.end(); ++it)
    {
      int paperid = *it;
       
      int citationcount = 0;
      for (long long int rcol = pcp_rowptr_1[paperid]; rcol < pcp_rowptr_1[paperid+1]; rcol++)
        if (writtenbyauthor_wo.find(pcp_colind_1[rcol]) == writtenbyauthor_wo.end())
          citationcount++;

      citationcounts_wo.push_back(citationcount);
    }

    make_heap(citationcounts_wo.begin(), citationcounts_wo.end());

    int ctr_wo = 1;
    while (citationcounts_wo.size() > 0 && citationcounts_wo.front() >= ctr_wo)
    {
      pop_heap(citationcounts_wo.begin(), citationcounts_wo.end());
      citationcounts_wo.pop_back();
 
      ctr_wo++;
    }
 
    hindexwo_1.push_back(ctr_wo-1);
  }

  cout << "h-indexes has been calculated." << endl;

  cout << endl; 
  
  ofstream w_1("hindexes-wself-1.txt");

  w_1 << hindexw_1.size() << endl << endl;

  for (int i = 0; i < hindexw_1.size(); i++)
    w_1 << hindexw_1[i] << endl;

  w_1.close();
  cout << "hindexes-wself.txt has been written." << endl;

  ofstream wo_1("hindexes-woself-1.txt");

  wo_1 << hindexwo_1.size() << endl << endl;

  for (int i = 0; i < hindexwo_1.size(); i++)
    wo_1 << hindexwo_1[i] << endl;

  wo_1.close();
  cout << "hindexes-woself.txt has been written." << endl;
  
  cout << endl;

  vector<int> pcp_rowptr_2;

  ifstream pcp_rowptr_in_2("../00-data/09-communitygraphs/isolated_129635231_citedby_rowptr.txt");

  string pcp_rowptr_line_2;
  getline(pcp_rowptr_in_2, pcp_rowptr_line_2);
  getline(pcp_rowptr_in_2, pcp_rowptr_line_2);

  while (getline(pcp_rowptr_in_2, pcp_rowptr_line_2))
  {
    istringstream iss(pcp_rowptr_line_2);
    int num;
    iss >> num;
    pcp_rowptr_2.push_back(num);
  }

  pcp_rowptr_in_2.close();
  cout << "paper_citedby_paper_rowptr.txt has been read." << endl;

  vector<int> pcp_colind_2;

  ifstream pcp_colind_in_2("../00-data/09-communitygraphs/isolated_129635231_citedby_colind.txt");

  string pcp_colind_line_2;
  getline(pcp_colind_in_2, pcp_colind_line_2);
  getline(pcp_colind_in_2, pcp_colind_line_2);

  while (getline(pcp_colind_in_2, pcp_colind_line_2))
  {
    istringstream iss(pcp_colind_line_2);
    int num;
    iss >> num;
    pcp_colind_2.push_back(num);
  }

  pcp_colind_in_2.close();
  cout << "paper_citedby_paper_colind.txt has been read." << endl;

  cout << endl;

  vector<int> hindexw_2;
  vector<int> hindexwo_2;

  for (int author = 0; author < awp_rowptr.size() - 1; author++)
  {
    vector<int> citationcounts_w;

    set<int> writtenbyauthor_w;
    for (long long int col = awp_rowptr[author]; col < awp_rowptr[author+1]; col++)
      writtenbyauthor_w.insert(awp_colind[col]);

    for (set<int>::iterator it = writtenbyauthor_w.begin(); it != writtenbyauthor_w.end(); ++it)
    {
      int paperid = *it;
      
      int citationcount = 0;
      for (long long int rcol = pcp_rowptr_2[paperid]; rcol < pcp_rowptr_2[paperid+1]; rcol++)
        citationcount++;

      citationcounts_w.push_back(citationcount);
    }

    make_heap(citationcounts_w.begin(), citationcounts_w.end());

    int ctr_w = 1;
    while (citationcounts_w.size() > 0 && citationcounts_w.front() >= ctr_w)
    {
      pop_heap(citationcounts_w.begin(), citationcounts_w.end());
      citationcounts_w.pop_back();

      ctr_w++;
    }

    hindexw_2.push_back(ctr_w-1);
    
    vector<int> citationcounts_wo;

    set<int> writtenbyauthor_wo;
    for (long long int col = awp_rowptr[author]; col < awp_rowptr[author+1]; col++)
      writtenbyauthor_wo.insert(awp_colind[col]);

    for (set<int>::iterator it = writtenbyauthor_wo.begin(); it != writtenbyauthor_wo.end(); ++it)
    {
      int paperid = *it;
       
      int citationcount = 0;
      for (long long int rcol = pcp_rowptr_2[paperid]; rcol < pcp_rowptr_2[paperid+1]; rcol++)
        if (writtenbyauthor_wo.find(pcp_colind_2[rcol]) == writtenbyauthor_wo.end())
          citationcount++;

      citationcounts_wo.push_back(citationcount);
    }

    make_heap(citationcounts_wo.begin(), citationcounts_wo.end());

    int ctr_wo = 1;
    while (citationcounts_wo.size() > 0 && citationcounts_wo.front() >= ctr_wo)
    {
      pop_heap(citationcounts_wo.begin(), citationcounts_wo.end());
      citationcounts_wo.pop_back();
 
      ctr_wo++;
    }
 
    hindexwo_2.push_back(ctr_wo-1);
  }

  cout << "h-indexes has been calculated." << endl;

  cout << endl; 
  
  ofstream w_2("hindexes-wself-2.txt");

  w_2 << hindexw_2.size() << endl << endl;

  for (int i = 0; i < hindexw_2.size(); i++)
    w_2 << hindexw_2[i] << endl;

  w_2.close();
  cout << "hindexes-wself.txt has been written." << endl;

  ofstream wo_2("hindexes-woself-2.txt");

  wo_2 << hindexwo_2.size() << endl << endl;

  for (int i = 0; i < hindexwo_2.size(); i++)
    wo_2 << hindexwo_2[i] << endl;

  wo_2.close();
  cout << "hindexes-woself.txt has been written." << endl;
  
  cout << endl;

  vector<int> pcp_rowptr_3;

  ifstream pcp_rowptr_in_3("../00-data/09-communitygraphs/isolated_100137693_citedby_rowptr.txt");

  string pcp_rowptr_line_3;
  getline(pcp_rowptr_in_3, pcp_rowptr_line_3);
  getline(pcp_rowptr_in_3, pcp_rowptr_line_3);

  while (getline(pcp_rowptr_in_3, pcp_rowptr_line_3))
  {
    istringstream iss(pcp_rowptr_line_3);
    int num;
    iss >> num;
    pcp_rowptr_3.push_back(num);
  }

  pcp_rowptr_in_3.close();
  cout << "paper_citedby_paper_rowptr.txt has been read." << endl;

  vector<int> pcp_colind_3;

  ifstream pcp_colind_in_3("../00-data/09-communitygraphs/isolated_100137693_citedby_colind.txt");

  string pcp_colind_line_3;
  getline(pcp_colind_in_3, pcp_colind_line_3);
  getline(pcp_colind_in_3, pcp_colind_line_3);

  while (getline(pcp_colind_in_3, pcp_colind_line_3))
  {
    istringstream iss(pcp_colind_line_3);
    int num;
    iss >> num;
    pcp_colind_3.push_back(num);
  }

  pcp_colind_in_3.close();
  cout << "paper_citedby_paper_colind.txt has been read." << endl;

  cout << endl;

  vector<int> hindexw_3;
  vector<int> hindexwo_3;

  for (int author = 0; author < awp_rowptr.size() - 1; author++)
  {
    vector<int> citationcounts_w;

    set<int> writtenbyauthor_w;
    for (long long int col = awp_rowptr[author]; col < awp_rowptr[author+1]; col++)
      writtenbyauthor_w.insert(awp_colind[col]);

    for (set<int>::iterator it = writtenbyauthor_w.begin(); it != writtenbyauthor_w.end(); ++it)
    {
      int paperid = *it;
      
      int citationcount = 0;
      for (long long int rcol = pcp_rowptr_3[paperid]; rcol < pcp_rowptr_3[paperid+1]; rcol++)
        citationcount++;

      citationcounts_w.push_back(citationcount);
    }

    make_heap(citationcounts_w.begin(), citationcounts_w.end());

    int ctr_w = 1;
    while (citationcounts_w.size() > 0 && citationcounts_w.front() >= ctr_w)
    {
      pop_heap(citationcounts_w.begin(), citationcounts_w.end());
      citationcounts_w.pop_back();

      ctr_w++;
    }

    hindexw_3.push_back(ctr_w-1);
    
    vector<int> citationcounts_wo;

    set<int> writtenbyauthor_wo;
    for (long long int col = awp_rowptr[author]; col < awp_rowptr[author+1]; col++)
      writtenbyauthor_wo.insert(awp_colind[col]);

    for (set<int>::iterator it = writtenbyauthor_wo.begin(); it != writtenbyauthor_wo.end(); ++it)
    {
      int paperid = *it;
       
      int citationcount = 0;
      for (long long int rcol = pcp_rowptr_3[paperid]; rcol < pcp_rowptr_3[paperid+1]; rcol++)
        if (writtenbyauthor_wo.find(pcp_colind_3[rcol]) == writtenbyauthor_wo.end())
          citationcount++;

      citationcounts_wo.push_back(citationcount);
    }

    make_heap(citationcounts_wo.begin(), citationcounts_wo.end());

    int ctr_wo = 1;
    while (citationcounts_wo.size() > 0 && citationcounts_wo.front() >= ctr_wo)
    {
      pop_heap(citationcounts_wo.begin(), citationcounts_wo.end());
      citationcounts_wo.pop_back();
 
      ctr_wo++;
    }
 
    hindexwo_3.push_back(ctr_wo-1);
  }

  cout << "h-indexes has been calculated." << endl;

  cout << endl; 
  
  ofstream w_3("hindexes-wself-3.txt");

  w_3 << hindexw_3.size() << endl << endl;

  for (int i = 0; i < hindexw_3.size(); i++)
    w_3 << hindexw_3[i] << endl;

  w_3.close();
  cout << "hindexes-wself.txt has been written." << endl;

  ofstream wo_3("hindexes-woself-3.txt");

  wo_3 << hindexwo_3.size() << endl << endl;

  for (int i = 0; i < hindexwo_3.size(); i++)
    wo_3 << hindexwo_3[i] << endl;

  wo_3.close();
  cout << "hindexes-woself.txt has been written." << endl;
  
  cout << endl;

  vector<int> pcp_rowptr_4;

  ifstream pcp_rowptr_in_4("../00-data/09-communitygraphs/isolated_39538415_citedby_rowptr.txt");

  string pcp_rowptr_line_4;
  getline(pcp_rowptr_in_4, pcp_rowptr_line_4);
  getline(pcp_rowptr_in_4, pcp_rowptr_line_4);

  while (getline(pcp_rowptr_in_4, pcp_rowptr_line_4))
  {
    istringstream iss(pcp_rowptr_line_4);
    int num;
    iss >> num;
    pcp_rowptr_4.push_back(num);
  }

  pcp_rowptr_in_4.close();
  cout << "paper_citedby_paper_rowptr.txt has been read." << endl;

  vector<int> pcp_colind_4;

  ifstream pcp_colind_in_4("../00-data/09-communitygraphs/isolated_39538415_citedby_colind.txt");

  string pcp_colind_line_4;
  getline(pcp_colind_in_4, pcp_colind_line_4);
  getline(pcp_colind_in_4, pcp_colind_line_4);

  while (getline(pcp_colind_in_4, pcp_colind_line_4))
  {
    istringstream iss(pcp_colind_line_4);
    int num;
    iss >> num;
    pcp_colind_4.push_back(num);
  }

  pcp_colind_in_4.close();
  cout << "paper_citedby_paper_colind.txt has been read." << endl;

  cout << endl;

  vector<int> hindexw_4;
  vector<int> hindexwo_4;

  for (int author = 0; author < awp_rowptr.size() - 1; author++)
  {
    vector<int> citationcounts_w;

    set<int> writtenbyauthor_w;
    for (long long int col = awp_rowptr[author]; col < awp_rowptr[author+1]; col++)
      writtenbyauthor_w.insert(awp_colind[col]);

    for (set<int>::iterator it = writtenbyauthor_w.begin(); it != writtenbyauthor_w.end(); ++it)
    {
      int paperid = *it;
      
      int citationcount = 0;
      for (long long int rcol = pcp_rowptr_4[paperid]; rcol < pcp_rowptr_4[paperid+1]; rcol++)
        citationcount++;

      citationcounts_w.push_back(citationcount);
    }

    make_heap(citationcounts_w.begin(), citationcounts_w.end());

    int ctr_w = 1;
    while (citationcounts_w.size() > 0 && citationcounts_w.front() >= ctr_w)
    {
      pop_heap(citationcounts_w.begin(), citationcounts_w.end());
      citationcounts_w.pop_back();

      ctr_w++;
    }

    hindexw_4.push_back(ctr_w-1);
    
    vector<int> citationcounts_wo;

    set<int> writtenbyauthor_wo;
    for (long long int col = awp_rowptr[author]; col < awp_rowptr[author+1]; col++)
      writtenbyauthor_wo.insert(awp_colind[col]);

    for (set<int>::iterator it = writtenbyauthor_wo.begin(); it != writtenbyauthor_wo.end(); ++it)
    {
      int paperid = *it;
       
      int citationcount = 0;
      for (long long int rcol = pcp_rowptr_4[paperid]; rcol < pcp_rowptr_4[paperid+1]; rcol++)
        if (writtenbyauthor_wo.find(pcp_colind_4[rcol]) == writtenbyauthor_wo.end())
          citationcount++;

      citationcounts_wo.push_back(citationcount);
    }

    make_heap(citationcounts_wo.begin(), citationcounts_wo.end());

    int ctr_wo = 1;
    while (citationcounts_wo.size() > 0 && citationcounts_wo.front() >= ctr_wo)
    {
      pop_heap(citationcounts_wo.begin(), citationcounts_wo.end());
      citationcounts_wo.pop_back();
 
      ctr_wo++;
    }
 
    hindexwo_4.push_back(ctr_wo-1);
  }

  cout << "h-indexes has been calculated." << endl;

  cout << endl; 
  
  ofstream w_4("hindexes-wself-4.txt");

  w_4 << hindexw_4.size() << endl << endl;

  for (int i = 0; i < hindexw_4.size(); i++)
    w_4 << hindexw_4[i] << endl;

  w_4.close();
  cout << "hindexes-wself.txt has been written." << endl;

  ofstream wo_4("hindexes-woself-4.txt");

  wo_4 << hindexwo_4.size() << endl << endl;

  for (int i = 0; i < hindexwo_4.size(); i++)
    wo_4 << hindexwo_4[i] << endl;

  wo_4.close();
  cout << "hindexes-woself.txt has been written." << endl;
  
  cout << endl;

  vector<int> pcp_rowptr_5;

  ifstream pcp_rowptr_in_5("../00-data/09-communitygraphs/isolated_55833303_citedby_rowptr.txt");

  string pcp_rowptr_line_5;
  getline(pcp_rowptr_in_5, pcp_rowptr_line_5);
  getline(pcp_rowptr_in_5, pcp_rowptr_line_5);

  while (getline(pcp_rowptr_in_5, pcp_rowptr_line_5))
  {
    istringstream iss(pcp_rowptr_line_5);
    int num;
    iss >> num;
    pcp_rowptr_5.push_back(num);
  }

  pcp_rowptr_in_5.close();
  cout << "paper_citedby_paper_rowptr.txt has been read." << endl;

  vector<int> pcp_colind_5;

  ifstream pcp_colind_in_5("../00-data/09-communitygraphs/isolated_55833303_citedby_colind.txt");

  string pcp_colind_line_5;
  getline(pcp_colind_in_5, pcp_colind_line_5);
  getline(pcp_colind_in_5, pcp_colind_line_5);

  while (getline(pcp_colind_in_5, pcp_colind_line_5))
  {
    istringstream iss(pcp_colind_line_5);
    int num;
    iss >> num;
    pcp_colind_5.push_back(num);
  }

  pcp_colind_in_5.close();
  cout << "paper_citedby_paper_colind.txt has been read." << endl;

  cout << endl;

  vector<int> hindexw_5;
  vector<int> hindexwo_5;

  for (int author = 0; author < awp_rowptr.size() - 1; author++)
  {
    vector<int> citationcounts_w;

    set<int> writtenbyauthor_w;
    for (long long int col = awp_rowptr[author]; col < awp_rowptr[author+1]; col++)
      writtenbyauthor_w.insert(awp_colind[col]);

    for (set<int>::iterator it = writtenbyauthor_w.begin(); it != writtenbyauthor_w.end(); ++it)
    {
      int paperid = *it;
      
      int citationcount = 0;
      for (long long int rcol = pcp_rowptr_5[paperid]; rcol < pcp_rowptr_5[paperid+1]; rcol++)
        citationcount++;

      citationcounts_w.push_back(citationcount);
    }

    make_heap(citationcounts_w.begin(), citationcounts_w.end());

    int ctr_w = 1;
    while (citationcounts_w.size() > 0 && citationcounts_w.front() >= ctr_w)
    {
      pop_heap(citationcounts_w.begin(), citationcounts_w.end());
      citationcounts_w.pop_back();

      ctr_w++;
    }

    hindexw_5.push_back(ctr_w-1);
    
    vector<int> citationcounts_wo;

    set<int> writtenbyauthor_wo;
    for (long long int col = awp_rowptr[author]; col < awp_rowptr[author+1]; col++)
      writtenbyauthor_wo.insert(awp_colind[col]);

    for (set<int>::iterator it = writtenbyauthor_wo.begin(); it != writtenbyauthor_wo.end(); ++it)
    {
      int paperid = *it;
       
      int citationcount = 0;
      for (long long int rcol = pcp_rowptr_5[paperid]; rcol < pcp_rowptr_5[paperid+1]; rcol++)
        if (writtenbyauthor_wo.find(pcp_colind_5[rcol]) == writtenbyauthor_wo.end())
          citationcount++;

      citationcounts_wo.push_back(citationcount);
    }

    make_heap(citationcounts_wo.begin(), citationcounts_wo.end());

    int ctr_wo = 1;
    while (citationcounts_wo.size() > 0 && citationcounts_wo.front() >= ctr_wo)
    {
      pop_heap(citationcounts_wo.begin(), citationcounts_wo.end());
      citationcounts_wo.pop_back();
 
      ctr_wo++;
    }
 
    hindexwo_5.push_back(ctr_wo-1);
  }

  cout << "h-indexes has been calculated." << endl;

  cout << endl; 
  
  ofstream w_5("hindexes-wself-5.txt");

  w_5 << hindexw_5.size() << endl << endl;

  for (int i = 0; i < hindexw_5.size(); i++)
    w_5 << hindexw_5[i] << endl;

  w_5.close();
  cout << "hindexes-wself.txt has been written." << endl;

  ofstream wo_5("hindexes-woself-5.txt");

  wo_5 << hindexwo_5.size() << endl << endl;

  for (int i = 0; i < hindexwo_5.size(); i++)
    wo_5 << hindexwo_5[i] << endl;

  wo_5.close();
  cout << "hindexes-woself.txt has been written." << endl;
  
  cout << endl;

  return 0;
}
