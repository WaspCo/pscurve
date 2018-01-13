#ifndef CURVE_H
#define CURVE_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <cmath>

//#include "postscript.h"

using namespace std;

// point offset
struct offset
{
    double dx, dy;

    offset();
    offset(const double x);
    offset(const double x, const double y);

    offset& operator*=(const double s);
    offset operator*(const double s);
    offset& operator/=(const double s);
    offset operator/(const double s) const;

};

struct point{
  double x;
  double y;

  point();
  point(const double xx, const double yy);

  point& operator+=(const offset& o);
  point operator+(const offset& o) const;
  point& operator-=(const offset& o);
  point operator-(const offset& o) const;
  point operator*(const offset& o);

  istream& input(istream& is);
  ostream& output(ostream& os) const;
};

//offset operator*(const double s, const offset& o) { return o * s; }

istream& operator>>(istream& is, point& p);
ostream& operator<<(ostream& os, const point& p);

struct courbe{
  vector <point> courbePoint;// point list for the curve

  int maxT();
  void addPoint(point p);
  void addPoint();
  uint delPoint(point p);
  void delPoint();
  virtual point calcul(const double t) = 0;

};

struct bezier1 : public courbe{
  bezier1() : courbe(){};
  point calcul(const double t);
};

struct bezier3 : public courbe{
  //two info: I want point from x segment, and point number 0 or 1
  vector <point> courbeControle;

  bezier3() : courbe(){};
  uint addAtract(point p);
  uint addAtract();
  point calcul(const double t);
};

struct hermitte : public courbe{
  //two info: I want vector from x segment, and vector number 0 or 1
  vector <point> courbeVector;

  hermitte() : courbe(){};
  uint addVector(point p);
  uint addVector();
  point calcul(const double t);
};

#endif
