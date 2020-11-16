#include <string>
#include <algorithm>
#include <map>

using namespace std;

class Soundex {
public:
  Soundex() {
  }
  std::string encode(const std::string cword) const {
    string word(cword);
    this->tolower(word);
    this->remove_non_alphabets(word);
    this->replace_vowels(word);
    this->remove_adjacent(word);
    for(string::iterator it=word.begin();it!=word.end();it++) {
      //retain finnnrst char
      if (it==word.begin())
        continue;
      for (auto pair:code) {
        if (pair.first.find(*it)!=string::npos) {
          *it=pair.second;
          break;
        }
      }
    }   
    this->remove_vowels(word);
    word=this->zeropad_or_trim(word);
    return word;
  }
private:
  const string ALPHABET = "abcdefghijklmnopqrstuvwxyz";
  const string VOWELS = "aeiouwyh";
  const char ZERO = '0';
  const string Gb = "bfpv"; //1
  const string Gc = "cszxjkgq"; //2
  const string Gd = "dt"; // 3
  const string Gl = "l"; //4
  const string Gm = "mn";
  const string Gr = "r";
  const map<string, int> code = {{Gb, 0x31},
                                 {Gc, 0x32},
                                 {Gd, 0x33},
                                 {Gl, 0x34},
                                 {Gm, 0x35},
                                 {Gr, 0x36}};
  void tolower(string &word) const {
    transform(word.begin(), word.end(), word.begin(),
              [](unsigned char w) { return std::tolower(w); } );
  }
  void remove_non_alphabets(string &word) const {
    
    for(string::iterator it=word.begin();it!=word.end();it++) {
      if (ALPHABET.find(*it)==string::npos) {
        word.erase(it);
        it--;
      }
    }
  }
  void remove_adjacent(string &word) const {
    for(string::iterator it=word.begin();it!=word.end();it++) {
      if (it!=word.end()-2) {
        for (auto pair : code) {
          if (pair.first.find(*it)!=string::npos and
              pair.first.find(*(it+1))!=string::npos) {
            word.erase(it-word.begin()+1, 1);
            it--;
            break;
          }
        }
      }
    }
  }
  void replace_vowels(string &word) const {
    for(string::iterator it=word.begin();it!=word.end();it++) {
      if (it==word.begin()) //retainFirstChar
        continue;
      if(VOWELS.find(*it)!=string::npos) {
        *it=ZERO;
        continue;
      }
    }
  }
  void remove_vowels(string &word) const {
    for(string::iterator it=word.begin();it!=word.end();it++) {
      if(*it==ZERO) {
        word.erase(it-word.begin(), 1);
        it--;
      }
    }
  }
  string zeropad_or_trim(string &word) const {
    if (word.size()==0)
      return word;
    if (word.size()<4)
      word.append(4-word.size(), ZERO);
    return word.substr(0, 4);
  }
};
