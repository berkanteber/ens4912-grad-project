#include <iostream>
#include <fstream>

#include <string>
#include <set>

using namespace std;

int main(int argc, char** argv)
{
  set <string> merged;


  string filename1 = argv[1];
  ifstream in1(filename1);

  string line1;
  getline(in1, line1);
  getline(in1, line1);

  while (getline(in1, line1))
    merged.insert(line1);

  in1.close();

  string pretty_filename1 = filename1.substr(filename1.rfind("/") + 1);
  cout << pretty_filename1 << " has been read." << endl; 


  string filename2 = argv[2];
  ifstream in2(filename2);

  string line2;
  getline(in2, line2);
  getline(in2, line2);

  while (getline(in2, line2))
    merged.insert(line2);

  in2.close();

  string pretty_filename2 = filename2.substr(filename2.rfind("/") + 1);
  cout << pretty_filename2 << " has been read." << endl; 


  string filename = argv[3];
  ofstream out(filename);

  out << merged.size() << endl << endl;

  set<string>::iterator iter;
  for (iter = merged.begin(); iter != merged.end(); ++iter)
    out << (*iter) << endl;

  out.close();

  cout << endl << filename << " has been written." << endl;


  return 0;
}
