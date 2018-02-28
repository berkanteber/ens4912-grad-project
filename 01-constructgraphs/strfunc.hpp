#include <string>
#include "string/unidecode.cxx"

using namespace std;

string replace_nl(string str)
{
  for(int i = 0; i < str.length(); i++)
    if(str[i] == '\n')
      str[i] = ' ';
  return str;
}

string reduce_sp(string str)
{
  if(str.length() == 0)
    return "";

  if(str.length() == 1 && str[0] == ' ')
    return "";

  string s = "";
  s += str[0];

  for(int i = 1; i < str.length(); i++)
  {
    if(str[i] != ' ')
      s += str[i];
    else
    {
      if(str[i-1] != ' ')
        s += str[i];
      else
        continue;
    }
  }

  return s;
}

string trim(string str)
{
  if(str.length() == 0) 
    return "";

  if(str.length() == 1 && str[0] == ' ') 
    return "";

  if(str.length() == 1 && str[0] != ' ') 
    return str;

  if(str[0] == ' ' && str[str.length() - 1] == ' ') 
    return str.substr(1, str.length() - 2);
  else if(str[0] == ' ') 
    return str.substr(1, str.length() - 1);
  else if(str[str.length() - 1] == ' ') 
    return str.substr(0, str.length() - 1);
  else 
    return str;
}

string beautify(string in)
{
  string out;
  unidecode(&in, &out);
  out = out.c_str(); 

  return trim(reduce_sp(replace_nl(out)));
}
