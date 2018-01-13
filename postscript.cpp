#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <cmath>

#include "postscript.h"

using namespace std;

// postscript class and methods ////////////////////////////////////////////////

// postscript output
crux::crux(const point& pp, const double size) : p(pp), r(size) {};
circa::circa(const point& pp, const double rr) : p(pp), r(rr) {};
quadra::quadra(const point& aa, const point& bb) : a(aa), b(bb) {};
text::text(const string& ss, const point& pp, const double rr) : p(pp), r(rr), s(ss) {};
lwidth::lwidth(const double w) : r(w) {};
color::color(const double g) : r(g), g(g), b(g) {};//singlecolor constructor
color::color(const double rr, const double gg, const double bb) : r(rr), g(gg), b(bb) {};//tricolor constructor
postscript::postscript(ostream& s) : myfile(s) { /*myfile << "%! PS-1.0\n";*/ }
postscript::~postscript() {  /*myfile << "\n%that's all folks!";*/ }

// By mean or overload, we allow object to be wrote to the postscript stream
// ex: ps_stream << point(x,y) << "\n" << color(1,0,0);

// postscript linewidth change
postscript& operator<<(postscript& p, const lwidth& l){
    p.myfile << "\n" << l.r << " setlinewidth ";
    return p;
}

// postscript color change
postscript& operator<<(postscript& p, const color& c){
    if (c.r == c.g && c.r == c.b)
        p.myfile << "\n" << c.r << " setgray ";
    else
        p.myfile << "\n" << c.r << " " << c.g << " " << c.b << " setrgbcolor ";
    return p;
}

// postscript cross drawing
postscript& operator<<(postscript& p, const crux& c){
    // first cross line
    offset off(c.r, c.r);
    p.myfile << "\n" << c.p - off << " moveto " << c.p + off << " lineto";
    // second cross line
    off.dy = -off.dy;
    p.myfile << " " << c.p - off << " moveto " << c.p + off << " lineto";

    p.myfile << " stroke ";
    return p;
}

// postscript circle drawing
postscript& operator<<(postscript& p, const circa& c){
    p.myfile << "\n" << c.p << " " << c.r
             << " 0 360 arc closepath stroke ";
    return p;
}

// postscript square drawing
postscript& operator<<(postscript& p, const quadra& q){
    p.myfile << "\n" << q.a << " moveto"
             << " " << point(q.a.x, q.b.y) << " lineto"
             << " " << q.b << " lineto"
             << " " << point(q.b.x, q.a.y) << " lineto"
             << " closepath stroke ";
    return p;
}

// postscript text drawing
postscript& operator<<(postscript& p, const text& t){
    p.myfile << "\n/Times-Roman findfont " << t.r << " scalefont setfont"
             << " newpath " << t.p <<" moveto"
             << " (" << t.s << ") show";
    return p;
}

// postscript RAW writting to output
postscript& operator<<(postscript& p, const string& s){
    cout.clear();
    p.myfile << s;
    return p;
}

// postscript curve drawing
postscript& operator<<(postscript& p, courbe& c){
  double pas = 0.01;
  point p_A, p_B;

  for(double i=0; i<c.maxT(); i+=pas){
    p_A = c.calcul(i);
    p_B = c.calcul(i+0.01);
    p.myfile << p_A << " moveto " << p_B << " lineto stroke\n";
  }
  return p;
}

postscript& operator<<(postscript& p, point pts){
  p.myfile << pts.x << " " << pts.y;
  return p;
}
