#pragma once

#include <iostream>
#include <stdlib.h>
#include <map>
#include <fstream>

namespace tkutil {

  class Property {
  public:
    Property();
  };

  template<typename T>
  class _Property: public Property {
  private:
    T value;
  public:
    _Property(): Property(){};

    _Property(T _value): Property() { 
      this->value=_value; 
    }

    void setValue(T _value){ 
      this->value = _value; 
    }
  };

  class Config {
  private:
   std::map<std::string, Property> dict;

  public:
    Config() {};
    Config(std::string configFileName);
    bool loadConfigFromFile(std::string fileName);
  };
}
