/**
 * Demo file for the exercise on numbers with units
 *
 * @author Amiel Lejzor
 * @since 2021
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <map>
#include <iterator>
using namespace std;
#include "NumberWithUnits.hpp"
using namespace ariel;

namespace ariel
{

  const double EPS = 0.0001;
  static map<string, map<string, double>> umap;

  NumberWithUnits::NumberWithUnits(double num, const string unit)
  {

    if (!(umap.contains(unit)))
    {
      throw "unit doesnt exists in table";
    }
    else
    {
      this->number = num;
      this->type = unit;
    }
  }

  NumberWithUnits NumberWithUnits::operator+(const NumberWithUnits &num)
  { // binary addition
    double x = this->number + convert_units(this->type, num.type, this->number, num.number);

    return NumberWithUnits{x, this->type};
  }
  NumberWithUnits NumberWithUnits::operator+() const  // unary addition
  { 
    return NumberWithUnits{this->number,this->type};
  }

  NumberWithUnits &NumberWithUnits::operator+=(const NumberWithUnits &num)
  { // binary addition adn assigment
    this->number = this->number + convert_units(this->type, num.type, this->number, num.number);
    return *this;
  }

  NumberWithUnits &NumberWithUnits::operator++()  // prefix addition operator
  { 
    this->number++;
    return *this;
  }

  NumberWithUnits NumberWithUnits::operator++(int num)  // postfix addition
  { 
    return NumberWithUnits{this->number++,this->type};
  }

  
  NumberWithUnits NumberWithUnits::operator-()const  // unary substraction
  {
    return NumberWithUnits{-(this->number),this->type};
  }

  NumberWithUnits NumberWithUnits::operator-(const NumberWithUnits &num)
  {
    double x = this->number- convert_units(this->type, num.type, this->number, (num.number));

    return NumberWithUnits{x, this->type};
  }

  NumberWithUnits &NumberWithUnits::operator--()
  { //prefix substraction  operator
    --this->number;
    return *this;
  }

  NumberWithUnits NumberWithUnits::operator--(int num)
  { // postfix substraction
    return NumberWithUnits(this->number--,this->type);
  }

  // binary substraction adn assigment
  NumberWithUnits &NumberWithUnits::operator-=(const NumberWithUnits &num)
  {
    this->number = this->number - convert_units(this->type, num.type, this->number, num.number);
    return *this;
  }

  // assigment operator
  NumberWithUnits &NumberWithUnits::operator=(const NumberWithUnits &num)
  {
    this->number = num.number;
    this->type = num.type;
    return *this;
  }

  // equal operator
  bool ariel::NumberWithUnits::operator==(const NumberWithUnits &num) const
  {
    if (is_same_type(this->type, num.type))
    {
      double x = convert_units(this->type, num.type, this->number, num.number);
      if (abs(this->number-x)<=EPS){
        return true;}
          
        
    }
    else{
      throw "cannot compare objects from diffrent types";
    }
    return false;
    
  }

  // not equal operator
  bool NumberWithUnits::operator!=(const NumberWithUnits &num) const
  {
    return !(*this == num);
  }

  // grather equal operator
  bool NumberWithUnits::operator>=(const NumberWithUnits &num) const
  {
    double x =(convert_units(this->type, num.type, this->number, num.number));
    if (!(this->number<x))
    {
      return true;
    }
    return false;
  }

  bool NumberWithUnits::operator<=(const NumberWithUnits &num) const
  { // smaller equal operator
    double x = (convert_units(this->type, num.type, this->number, num.number));
    if (!(this->number>x))
    {
      return true;
    }
    return false;
  }

  bool NumberWithUnits::operator>(const NumberWithUnits &num) const
  { // grather than operator
    double x =(convert_units(this->type, num.type, this->number, num.number));
    if (this->number>x)
    {
      return true;
    }
    return false;
  }

  bool NumberWithUnits::operator<(const NumberWithUnits &num) const
  { // smaller than operator
    double x =(convert_units(this->type, num.type, this->number, num.number));
    if (!(this->number>=x))
    {
      return true;
    }
    return false;
  }

  /*  multiplication prefix and postfix operator */

  NumberWithUnits operator*(const NumberWithUnits &num, const double &x)
  {
    return NumberWithUnits{x * num.number, num.type};
  }
  NumberWithUnits operator*(const double &x, const NumberWithUnits &num)
  {
    return NumberWithUnits{x * num.number, num.type};
  }

  /* input and output operators */

  ostream &operator<<(ostream &os, const NumberWithUnits &num)
  { // output operator
    os << num.number << "[" << num.type << "]";
    return os;
  }

  istream &operator>>(istream &is, NumberWithUnits &num)
  {  
     string temp;
     string type;
     is >> num.number>>temp;
     size_t i=0;
     while(!temp.empty()&&temp.at(temp.length()-1)!=']')
     {
       is>>type;
       temp+=type;
     }
     string unit;
     for(size_t t=0;t<temp.length();t++){
       if(temp.at(t)=='['||temp.at(t)==' '||temp.at(t)==']'){
         continue;
       }
       else{
         unit+=temp.at(t);
       }

     }
      num.type=unit;
     
     if(!umap.contains(unit)){
       throw " there is not such type in the file";
     }
     
   
     return is;
  }

  void NumberWithUnits::update_units(const string &unit1, const string &unit2)
  {

    for (auto const &[key, val] : umap[unit1])
    {
      if (!umap[unit2][key])
      {
        if (key == unit2)
        {
          continue;
        }
        else
        {
          umap[unit2][key] = umap[unit2][unit1] * umap[unit1][key];
          umap[key][unit2] = 1 / (umap[unit2][unit1] * umap[unit1][key]);
        }
      }
    }
  }

  bool NumberWithUnits::is_same_type(const string &a, const string &b) const
  {
    if (umap.at(a).contains(b))
    {
      return true;
    }
    else
    {  return false;
    }
  }

  double NumberWithUnits::convert_units(const string &unit_a, const string &unit_b, double num_a, double num_b) const
  {
     if(unit_b==unit_a){return num_b;}
    if (is_same_type(unit_a, unit_b))
    {
      return  umap[unit_b][unit_a] * num_b;
    }
    else
    {
      throw " objects are from diffrent types";
    }
  }

  void NumberWithUnits::read_units(ifstream &file)
  {

    if (!file)
    {
      throw " cant open file";
      return;
    }

    string first_unit, sec_unit, eq;
    double first_num = 0, sec_num = 0;

    while (file >> first_num >> first_unit >> eq >> sec_num >> sec_unit)
    {
      umap[first_unit][sec_unit] = sec_num;
      umap[sec_unit][first_unit] = 1 / sec_num;
      update_units(first_unit, sec_unit);
      update_units(sec_unit, first_unit);
    }
  }

  void NumberWithUnits::print_map()
  {
    map<string, map<string, double>>::iterator it;
    map<string, double>::iterator it2;
    for (it = umap.begin(); it != umap.end(); it++)
    {
      cout << it->first << ":";
      for (it2 = it->second.begin(); it2 != it->second.end(); it2++)
      {
        cout << "[" << it2->first << "]" << endl;
      }
    }
    cout << endl;
  }

};
