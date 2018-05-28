#include <iostream>
#include <fstream>
#include <sstream>

#include <string>

using namespace std;

int main(int argc, char** argv)
{
  ifstream in("../0-data/7-authorcitesauthor/author_cites_author_graph.txt");
  ofstream out("graph.txt");
 
  string line;
  while(getline(in, line))
  {
    int src, dst, w;
    istringstream iss(line);
    iss >> src >> dst >> w;
    out << src << " " << dst << " " << w * w << endl;
  }
 
  in.close();
  out.close();

  cout << "Conversion has been completed." << endl;

  return 0;
}
