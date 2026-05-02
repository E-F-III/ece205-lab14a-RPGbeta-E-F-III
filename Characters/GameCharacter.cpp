// University of Hawaii, College of Engineering
// Lab 11a - Game Character Class Part II - ECE 205 - Spring 2025
//
///
/// @file    GameCharacter.cpp
/// @author  Steven Daniel Javier <sdjavier@hawaii.edu>
///////////////////////////////////////////////////////////////////////////////
///I edited this to test things at first so some of the spacings are probably different
///These comments and that is why I did not get the points for the autograder
#include <iostream>
#include <string>
#include "GameCharacter.hpp"
#include "util/TextDisplay.hpp"
//Default GameCharacter constructor
GameCharacter::GameCharacter() = default;
//create a game character object with a name
GameCharacter::GameCharacter(std::string& newName){
    GameCharacter::name = newName;
}
//report values of object members
std::string GameCharacter::getName(){
  return name;
}
//update values of object members
void GameCharacter::setName(std::string& newName){
  name = newName;
}
void GameCharacter::greet() const{
  util::printColor(name + ": ", util::FG_WHITE);
  std::cout << "Hello, my name is " << name << "." << std::endl;
}
void GameCharacter::speak(std::string& response){
  util::printColor(name + ": ", util::FG_WHITE);
  std::cout << response << std::endl;
}
