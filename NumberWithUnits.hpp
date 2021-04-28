#include <iostream>
#include <stdexcept>
#include <fstream>
#include <sstream>
//#include "NumberWithUnits.cpp"
using namespace std;
//using namespace ariel;
namespace ariel
{
    class NumberWithUnits
    {

    private:
        string type;
        double number;

    public:
        //constructor and distuctor
        NumberWithUnits(double number, string type);
        ~NumberWithUnits(){};

        /* 6 arithmetic operations */

        // unary and binary addition
        NumberWithUnits operator+(const NumberWithUnits &num);
        NumberWithUnits operator+() const;

        // binary addition adn assigment
        NumberWithUnits &operator+=(const NumberWithUnits &num);

        // prefix and postfix addittion operator
        NumberWithUnits &operator++();
        NumberWithUnits operator++(int num);

        // unary and binary substraction
        NumberWithUnits operator-() const;
        NumberWithUnits operator-(const NumberWithUnits &num);

        // binary substraction adn assigment
        NumberWithUnits &operator-=(const NumberWithUnits &num);

        //prefix substraction  operator
        NumberWithUnits &operator--();

        // postfix substraction
        NumberWithUnits operator--(int num);

        // assigment operator
        NumberWithUnits &operator=(const NumberWithUnits &num);
        /* 6 comparission operators*/

        // equal operator
        bool operator==(const NumberWithUnits &num) const;
        // not equal operator
        bool operator!=(const NumberWithUnits &num) const;
        // grather equal operator
        bool operator>=(const NumberWithUnits &num) const;
        // smaller equal operator
        bool operator<=(const NumberWithUnits &num) const;
        // grather than operator
        bool operator>(const NumberWithUnits &num) const;
        // smaller than operator
        bool operator<(const NumberWithUnits &num) const;

        /*  multiplication operator */
        friend NumberWithUnits operator*(const NumberWithUnits &num, const double &x);
        friend NumberWithUnits operator*(const double &x, const NumberWithUnits &num);

        static void read_units(ifstream &file);

        double convert_units(const string &unit_a, const string &unit_b, double num_b) const;

        bool is_same_type(const string &a, const string &b) const;

        static void update_units(const string &unit1, const string &unit2);

        void print_map();

        // output operator
        friend ostream &operator<<(ostream &, const NumberWithUnits &num);

        // input operator
        friend istream &operator>>(istream &is, NumberWithUnits &num);
    };

}