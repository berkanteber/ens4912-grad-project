#include <iostream>
#include <fstream>
#include <sstream>

#include <string>
#include <vector>

using namespace std;

struct handhp
{
  int index;
  int h;
  int hp;
};

void takecare(string wself, string woself, string out)
{
  vector<handhp> selected;

  ifstream ws_in(wself.c_str());
  ifstream wos_in(woself.c_str());

  string ws_line;
  string wos_line;

  getline(ws_in, ws_line);
  getline(ws_in, ws_line);
  
  getline(wos_in, wos_line);
  getline(wos_in, wos_line);

  int ctr = 0;
  while(getline(ws_in, ws_line))
  {
    getline(wos_in, wos_line);

    int hindex;
    istringstream ws_iss(ws_line);
    ws_iss >> hindex;

    int hpindex;
    istringstream wos_iss(wos_line);
    wos_iss >> hpindex;

    if (hindex >= 10)
    {
      handhp my;

      my.index = ctr;
      my.h = hindex;
      my.hp = hpindex;

      selected.push_back(my);
    } 

    ctr++;
  }

  ws_in.close();
  wos_in.close();

  cout << "selected" << endl;

  ofstream fs_out(out.c_str()); 

  fs_out << selected.size() << endl << endl;

  for (int i = 0; i < selected.size(); i++)
    fs_out << selected[i].index << " " << selected[i].h << " " << selected[i].hp << endl;
 
  fs_out.close();

  return;
}

int main()
{
  takecare("../00-data/06-hindex/hindexes-wself.txt", "../00-data/06-hindex/hindexes-woself.txt", "all.txt");

  takecare("../00-data/12-hindexindepth/hindexes-wself-1.txt", "../00-data/12-hindexindepth/hindexes-woself-1.txt", "1.txt");
  takecare("../00-data/12-hindexindepth/hindexes-wself-2.txt", "../00-data/12-hindexindepth/hindexes-woself-2.txt", "2.txt");
  takecare("../00-data/12-hindexindepth/hindexes-wself-3.txt", "../00-data/12-hindexindepth/hindexes-woself-3.txt", "3.txt");
  takecare("../00-data/12-hindexindepth/hindexes-wself-4.txt", "../00-data/12-hindexindepth/hindexes-woself-4.txt", "4.txt");
  takecare("../00-data/12-hindexindepth/hindexes-wself-5.txt", "../00-data/12-hindexindepth/hindexes-woself-5.txt", "5.txt");

  return 0;
}
