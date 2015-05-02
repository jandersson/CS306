#include <iostream>
#include <string>
#include <stdlib.h>
using namespace std;

int main(int argc, char * argv[]){
  cout << "Please enter your phone number: \n";
  string userInput = "";
  int phoneNumer = 1234;
  cout << isdigit(1234) << endl;
  userInput = "123";
  cout << atoi(userInput.c_str()) << endl;
  //cout << userInput << endl;
  cout << "Is userInput a digit?" << endl;
  cout << isdigit(atoi(userInput)) << endl;
  cout << "Is 1234 a digit?" << endl;
  cout << isdigit(49) << endl;
  cout << "is abc a digit?" << endl;
  cout << isdigit('abc') << endl;

  return 0;
}
