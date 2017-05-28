// skeleton C++ file, you will need to edit this and other files to implement your enigma machine
#include <stdexcept>
#include <iostream>
#include <fstream>
#include "Mapping.hpp"
#include "Rotor.hpp"
#include "Plugboard.hpp"
#include "Reflector.hpp"
#include <fstream>
#include <string>
#include <vector>
#include <assert.h>
using namespace std;
typedef std::vector<Rotor> RotorsList;
void createRotors(RotorsList& rotorsList, int argc, char **argv);
void enigma(RotorsList& rotorsList, Plugboard& plugboard, Reflector& reflector, std::string input);
int runRotors1st(RotorsList& rotorsList, int position);
int runRotors2nd(RotorsList& rotorsList, int position);
void shiftRotors(RotorsList& rotorsList);
int numberOfRotors = 0;
int main(int argc, char **argv)
{
  assert(argc >= 2);
  //readfile for plugboard
  std::ifstream file(argv[argc-1]);
  assert(file.is_open());
  std::string str;
  std::getline(file,str);
  Plugboard plugboard(str);
  plugboard.createList();

  //initialize and readfile for rotors
  RotorsList rotorsList;
  if(argc>2) {
    numberOfRotors = argc - 2;
    createRotors(rotorsList,argc,argv);
  }


  //initialize reflector
  Reflector reflector;

  std::string input;
  std::cin >> std::ws >> input;

  enigma(rotorsList, plugboard, reflector, input);
}

void createRotors(RotorsList& rotorsList, int argc, char **argv) {
  for (int i = 1;i<argc-1;i++) {
    std::ifstream file(argv[i]);
    std::string str;
    std::getline(file,str);
    Rotor rotor(str);
    rotor.createList();
    rotorsList.push_back(rotor);
  }
}

void enigma(RotorsList& rotorsList, Plugboard& plugboard, Reflector& reflector, std::string input) {
  for(char& c : input) {
    int position = int(c) - int('A');
    assert(position>=0&&position<=25);
    //insert to plugboard
    position = plugboard.getPos(position);
    //enter the first round of rotorsList
    if(numberOfRotors > 0) {
          position = runRotors1st(rotorsList, position);
    }
    //insert to reflector
    position = reflector.getPos(position);
    //enter the second round of rotorsList
    if(numberOfRotors > 0) {
          position = runRotors2nd(rotorsList, position);
    }

    //insert to plugboard
    position = plugboard.getPos(position);
    if(numberOfRotors >0) {
          shiftRotors(rotorsList);
    }

    std::cout << static_cast<char>(position + int('A'));
  }
}

int runRotors1st(RotorsList& rotorsList, int position) {
  for (int i=0; i < rotorsList.size(); i ++) {
    position = rotorsList[i].getPos(position);
  }
  return position;
}

int runRotors2nd(RotorsList& rotorsList, int position) {
  for (int i=rotorsList.size()-1; i >= 0; i--) {
    position = rotorsList[i].getPosInvs(position);
  }
  return position;
}

void shiftRotors(RotorsList& rotorsList) {
  for(int i=0; i<rotorsList.size();i++) {
    if (i!=0) {
      if (rotorsList[i-1].finishCycle()) {
        rotorsList[i].shiftF();
      }
    } else rotorsList[i].shiftF();
  }
}
