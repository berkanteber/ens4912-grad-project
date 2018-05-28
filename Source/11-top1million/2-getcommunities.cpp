#include <iostream>
#include <fstream>
#include <sstream>

#include <vector>

using namespace std;

int main() 
{
  vector<int> n2c;
  ifstream n2c_in("../00-data/04-louvain/citation_node2comm.txt");
  
  string n2c_line;
  getline(n2c_in, n2c_line);
  getline(n2c_in, n2c_line);

  while (getline(n2c_in, n2c_line))
  {
    istringstream iss(n2c_line);
    int p, c;
    iss >> p >> c;
    n2c.push_back(c);

  }

  n2c_in.close();
  cout << "citation_node2comm.txt has been read." << endl;

  ifstream inp("commonpapers.txt");
  ofstream out("communities.txt");

  string line;
  getline(inp, line);
  int count;
  istringstream iss_count(line);
  iss_count >> count;
  out << count << endl << endl;
  getline(inp, line);

  while (getline(inp, line))
  {
    int p;
    istringstream iss(line);
    iss >> p;

    if (p >= n2c.size()) out << 0 << endl;
    else if (n2c[p] == 1485264) out << 1 << endl;
    else if (n2c[p] == 129635231) out << 2 << endl;
    else if (n2c[p] == 100137693) out << 3 << endl;
    else if (n2c[p] == 39538415) out << 4 << endl;
    else if (n2c[p] == 55833303) out << 5 << endl;
    else out << 0 << endl;  
  }

  inp.close();
  out.close();

  return 0;
}
