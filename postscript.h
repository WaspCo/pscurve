#ifndef POSTSCRIPT_H
#define POSTSCRIPT_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <cmath>

#include "curve.h"

using namespace std;

struct crux {
  point p;
  double r;
  explicit crux(const point& pp=point(), const double size=5);
};

struct circa {
  point p;
  double r;
  explicit circa(const point& pp=point(), const double rr=1);
};

struct quadra {
  point a, b;
  explicit quadra(const point& aa=point(), const point& bb=point());
};

struct text {
  point p;
  double r;
  string s;
  text(const string& ss, const point& pp=point(), const double rr=18);
};

struct lwidth {
  double r;
  lwidth(const double w=1.0);
};

struct color
{
    double r, g, b;
    color(const double g=0);
    color(const double rr, const double gg, const double bb);
};

struct postscript
{
    ostream& myfile;
    postscript(ostream& s);
    ~postscript();
};

postscript& operator<<(postscript& p, const lwidth& l);
postscript& operator<<(postscript& p, const color& c);
postscript& operator<<(postscript& p, const crux& c);
postscript& operator<<(postscript& p, const circa& c);
postscript& operator<<(postscript& p, const quadra& q);
postscript& operator<<(postscript& p, const text& t);
postscript& operator<<(postscript& p, const string& s);
postscript& operator<<(postscript& p, courbe& c);
postscript& operator<<(postscript& p, point pts);

#endif
