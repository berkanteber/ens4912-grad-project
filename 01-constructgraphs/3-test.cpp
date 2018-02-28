#include <iostream>
#include <fstream>
#include <sstream>

#include <string>
#include <vector>

#include <cstdlib>
#include <ctime>

using namespace std;

void read_into_vector(string filename, vector<string> & vec)
{
  ifstream in(filename);

  string line;
  getline(in, line);
  getline(in, line);

  while(getline(in, line))
    vec.push_back(line);

  in.close();
 
  string pretty_filename = filename.substr(filename.rfind("/") + 1);
  cout << pretty_filename << " has been read." << endl;
}

int main(int argc, char** argv)
{
// READ LISTS

  vector<string> files;
  read_into_vector("../0-data/mag/mag_files.txt", files);

  vector<string> papers;
  read_into_vector("../0-data/mag/mag_papers.txt", papers);

  cout << endl;

// READ PAPERS

  string filename = "../0-data/mag/mag_structured_papers.txt";
  ifstream in(filename);

  string line;
  getline(in, line);
  istringstream iss(line);
  
  int size;
  iss >> size;

  vector<int> file_ids;  

  while(getline(in, line))
  {
    int id;
    getline(in, line);
    istringstream iss_id(line);
    iss_id >> id;
    file_ids.push_back(id);

    getline(in, line);

    int n;

    getline(in, line);
    istringstream iss_author(line);
    iss_author >> n;
    
    for (int i = 0; i < n; i++)
    {
      getline(in, line);
      getline(in, line); 
    }

    getline(in, line);
    istringstream iss_ref(line);
    iss_ref >> n;
    
    for (int i = 0; i < n; i++)
      getline(in, line);

    getline(in, line);
    istringstream iss_key(line);
    iss_key >> n;
    
    for (int i = 0; i < n; i++)
      getline(in, line);

    getline(in, line);
    istringstream iss_fos(line);
    iss_fos >> n;
    
    for (int i = 0; i < n; i++)
      getline(in, line);
  }
  
  in.close();

  cout << filename << " has been read." << endl;
  cout << endl;


// TEST
  
  if (papers.size() != file_ids.size() - 1) cout << papers.size() << " " << file_ids.size() << endl;

  else
  {
    for (int i = 0; i < papers.size(); i++)
      if(papers[i] == "e4f3dddf-33d8-41fe-9479-16423dbef0c2")
      {
        cout << file_ids[i] << endl;
        if(file_ids[i] != -1)
          cout << files[file_ids[i]] << endl;
      }
  }

  return 0;
}
