#include <iostream>
#include <fstream>
#include <sstream>

#include <string>
#include <vector>

#include <algorithm>

using namespace std;

struct horg
{
  int id;
  int hg;

  bool operator<(const horg & rhs) const
  {
    return hg < rhs.hg;
  }
};

struct hphp
{
  int id;
  double hp;

  bool operator<(const hphp & rhs) const
  {
    return hp < rhs.hp;
  }
};

int main()
{
  vector<horg> hws;

  ifstream hws_in("../00-data/06-hindex/hindexes-wself.txt");

  string hws_line;
  getline(hws_in, hws_line);
  getline(hws_in, hws_line);

  int hws_ctr = 0;
  while (getline(hws_in, hws_line))
  {
    istringstream iss(hws_line);
        
    horg h;
    h.id = hws_ctr++;
    iss >> h.hg;
    hws.push_back(h);
  }

  hws_in.close();
  cout << "hindexes-wself.txt has been read." << endl;

  ofstream hws_out("top1m-h-wself.txt");

  hws_out << 1000000 << endl << endl;

  make_heap(hws.begin(), hws.end());

  for (int i = 1; i <= 1000000; i++)
  {
    hws_out << hws.front().id << endl;

    pop_heap(hws.begin(), hws.end());
    hws.pop_back();
  }

  hws_out.close();
  cout << "top1m-h-wself.txt has been written." << endl;

  vector<horg> hwos;

  ifstream hwos_in("../00-data/06-hindex/hindexes-woself.txt");

  string hwos_line;
  getline(hwos_in, hwos_line);
  getline(hwos_in, hwos_line);

  int hwos_ctr = 0;
  while (getline(hwos_in, hwos_line))
  {
    istringstream iss(hwos_line);
        
    horg h;
    h.id = hwos_ctr++;
    iss >> h.hg;
    hwos.push_back(h);
  }

  hwos_in.close();
  cout << "hindexes-woself.txt has been read." << endl;

  ofstream hwos_out("top1m-h-woself.txt");

  hwos_out << 1000000 << endl << endl;

  make_heap(hwos.begin(), hwos.end());

  for (int i = 1; i <= 1000000; i++)
  {
    hwos_out << hwos.front().id << endl;

    pop_heap(hwos.begin(), hwos.end());
    hwos.pop_back();
  }

  hwos_out.close();
  cout << "top1m-h-woself.txt has been written." << endl;

  cout << endl;

  vector<horg> gws;

  ifstream gws_in("../00-data/10-otherindexes/gindexes-wself.txt");

  string gws_line;
  getline(gws_in, gws_line);
  getline(gws_in, gws_line);

  int gws_ctr = 0;
  while (getline(gws_in, gws_line))
  {
    istringstream iss(gws_line);
        
    horg g;
    g.id = gws_ctr++;
    iss >> g.hg;
    gws.push_back(g);
  }

  gws_in.close();
  cout << "gindexes-wself.txt has been read." << endl;

  ofstream gws_out("top1m-g-wself.txt");

  gws_out << 1000000 << endl << endl;

  make_heap(gws.begin(), gws.end());

  for (int i = 1; i <= 1000000; i++)
  {
    gws_out << gws.front().id << endl;

    pop_heap(gws.begin(), gws.end());
    gws.pop_back();
  }

  gws_out.close();
  cout << "top1m-g-wself.txt has been written." << endl;

  vector<horg> gwos;

  ifstream gwos_in("../00-data/10-otherindexes/gindexes-woself.txt");

  string gwos_line;
  getline(gwos_in, gwos_line);
  getline(gwos_in, gwos_line);

  int gwos_ctr = 0;
  while (getline(gwos_in, gwos_line))
  {
    istringstream iss(gwos_line);
        
    horg g;
    g.id = gwos_ctr++;
    iss >> g.hg;
    gwos.push_back(g);
  }

  gwos_in.close();
  cout << "gindexes-woself.txt has been read." << endl;

  ofstream gwos_out("top1m-g-woself.txt");

  gwos_out << 1000000 << endl << endl;

  make_heap(gwos.begin(), gwos.end());

  for (int i = 1; i <= 1000000; i++)
  {
    gwos_out << gwos.front().id << endl;

    pop_heap(gwos.begin(), gwos.end());
    gwos.pop_back();
  }

  gwos_out.close();
  cout << "top1m-g-woself.txt has been written." << endl;

  cout << endl;

  vector<hphp> hpws;

  ifstream hpws_in("../00-data/10-otherindexes/hprimes-wself.txt");

  string hpws_line;
  getline(hpws_in, hpws_line);
  getline(hpws_in, hpws_line);

  int hpws_ctr = 0;
  while (getline(hpws_in, hpws_line))
  {
    istringstream iss(hpws_line);
        
    hphp hp;
    hp.id = hpws_ctr++;
    iss >> hp.hp;
    hpws.push_back(hp);
  }

  hpws_in.close();
  cout << "hprimes-wself.txt has been read." << endl;

  ofstream hpws_out("top1m-hp-wself.txt");

  hpws_out << 1000000 << endl << endl;

  make_heap(hpws.begin(), hpws.end());

  for (int i = 1; i <= 1000000; i++)
  {
    hpws_out << hpws.front().id << endl;

    pop_heap(hpws.begin(), hpws.end());
    hpws.pop_back();
  }

  hpws_out.close();
  cout << "top1m-hp-wself.txt has been written." << endl;

  vector<hphp> hpwos;

  ifstream hpwos_in("../00-data/10-otherindexes/hprimes-woself.txt");

  string hpwos_line;
  getline(hpwos_in, hpwos_line);
  getline(hpwos_in, hpwos_line);

  int hpwos_ctr = 0;
  while (getline(hpwos_in, hpwos_line))
  {
    istringstream iss(hpwos_line);
        
    hphp hp;
    hp.id = hpwos_ctr++;
    iss >> hp.hp;
    hpwos.push_back(hp);
  }

  hpwos_in.close();
  cout << "hprimes-woself.txt has been read." << endl;

  ofstream hpwos_out("top1m-hp-woself.txt");

  hpwos_out << 1000000 << endl << endl;

  make_heap(hpwos.begin(), hpwos.end());

  for (int i = 1; i <= 1000000; i++)
  {
    hpwos_out << hpwos.front().id << endl;

    pop_heap(hpwos.begin(), hpwos.end());
    hpwos.pop_back();
  }

  hpwos_out.close();
  cout << "top1m-hp-woself.txt has been written." << endl;

  return 0;
}
