#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <cmath>

#include "curve.h"

using namespace std;

int verbose = 0;


//Struct offset ////////////////////////////////////////////////////////////////

offset::offset(){// pour decaler les points
  dx=0;
  dy=0;
}
offset::offset(const double x){
  dx=x;
  dy=x;
}
offset::offset(const double x, const double y){
  dx=x;
  dy=y;
}


//Struct point /////////////////////////////////////////////////////////////////

point::point(double xx, double yy){
  x=xx;
  y=yy;
}
point::point(){
  x=0;
  y=0;
}


//Struct courbe /////////////////////////////////////////////////////////////////

int courbe::maxT(){
  //cout << courbePoint.size();
  return courbePoint.size()-1;
}

void courbe::addPoint(point p){
  courbePoint.push_back(p);
  if(verbose) cout << "new point " << p.x << " " << p.y << " added to the curve" << endl;
}

void courbe::addPoint(){
  point p;
  cout << "Coordonné x ? ";
  cin >> p.x;
  cout << "Coordonné y ? ";
  cin >> p.y;
  cout << "\n";
  courbePoint.push_back(p);

  if(verbose) cout << "new point added to the curve" << endl;
}

uint courbe::delPoint(point p){//seek and destroy point
  int r = 0;
  for(uint i=0; i<courbePoint.size();++i){
    if(courbePoint[i].x == p.x && courbePoint[i].y == p.y ){
      courbePoint.erase(courbePoint.begin()+i);
      r=1;//erase successfull
    }
  }
  return r;
}

void courbe::delPoint(){
  courbePoint.clear();
}


// bezier1 /////////////////////////////////////////////////////////////////////

point bezier1::calcul(const double t){
    double p_A, p_B, t_rel;
    point p;

    if(t>1){//get segment points from t and relative t inside (p)
      p_A = floor(t);
      p_B = ceil(t);
      t_rel = t-p_A;
    }
    else{
      p_A = 0;
      p_B = 1;
      t_rel = t;
    }

    p.x = ( courbePoint[p_A].x*(1-t_rel) + courbePoint[p_B].x*t_rel );
    p.y = ( courbePoint[p_A].y*(1-t_rel) + courbePoint[p_B].y*t_rel );

    return p;
}


// bezier3 /////////////////////////////////////////////////////////////////////

uint bezier3::addAtract(point p){

    if(courbeControle.size()<=(courbePoint.size()-1)*2){
      courbeControle.push_back(p);
    }
    else {
      cout << "Nombre maximale de point de contrôle atteint !" << endl;
      return 0;
    }
    if(verbose) cout << "new controle point " << p.x << " " << p.y << " added to the curve" << endl;
    return 1;
}

uint bezier3::addAtract(){
    point p;
    if(courbeControle.size()<=(courbePoint.size()-1)*2){
      courbeControle.push_back(p);
    }
    else {
      cout << "Nombre maximale de point de contrôle atteint !" << endl;
      return 0;
    }
    cout << "addAtract y ? ";
    cin >> p.y;
    cout << "addAtract y ? ";
    cin >> p.y;
    if(verbose) cout << "new controle point " << p.x << " " << p.y << " added to the curve" << endl;
    return 1;
}

point bezier3::calcul(const double t){
  double p_A, p_B, t_rel;
  point p;
  if(t>1){//get segment points from t and relative t inside (p)
    p_A = floor(t);
    p_B = ceil(t);
    t_rel = t-p_A;
  }
  else{
    p_A = 0;
    p_B = 1;
    t_rel = t;
  }
  p.x = courbePoint[p_A].x*pow(1-t_rel, 3) +
        courbeControle[p_A*2].x*3*t_rel*pow(1-t_rel,2) +
        courbeControle[p_A*2+1].x*3*pow(t_rel,2)*(1-t_rel) +
        courbePoint[p_B].x*pow(t_rel, 3);

  p.y = courbePoint[p_A].y*pow(1-t_rel, 3) +
        courbeControle[p_A*2].y*3*t_rel*pow(1-t_rel,2) +
        courbeControle[p_A*2+1].y*3*pow(t_rel,2)*(1-t_rel) +
        courbePoint[p_B].y*pow(t_rel, 3);

  return p;
}


// hermitte ////////////////////////////////////////////////////////////////////

uint hermitte::addVector(point p){
  if(courbeVector.size()>=courbePoint.size()){
    cout << "La courbe comporte déjà le nombre maximal de vecteur" << endl;
    return 0;
  }
  courbeVector.push_back(p);
  if(verbose) cout << "new vector " << p.x << " " << p.y << " added to the curve" << endl;
  return 1;
}

uint hermitte::addVector(){
  point p;
  if(courbeVector.size()>=courbePoint.size()){
    cout << "La courbe comporte déjà le nombre maximal de vecteur" << endl;
    return 0;
  }
  cout << "AddVector y ? ";
  cin >> p.y;
  cout << "AddVector y ? ";
  cin >> p.y;
  courbeVector.push_back(p);
  if(verbose) cout << "new vector " << p.x << " " << p.y << " added to the curve" << endl;
  return 1;
}

point hermitte::calcul(const double t){
    double p_A, p_B, t_rel;
    point p;

    if(t>1){//get segment points from t and relative t inside (p)
      p_A = floor(t);
      p_B = ceil(t);
      t_rel = t-p_A;
    }
    else{
      p_A = 0;
      p_B = 1;
      t_rel = t;
    }
    double hp1 = 2*pow(t_rel,3) - 3*t_rel*t_rel + 1;
    double ht1 = pow(t_rel,3) - 2*t_rel*t_rel + t_rel;
    double hp2 = -2*pow(t_rel,3) + 3*t_rel*t_rel;
    double ht2 = pow(t_rel,3) - t_rel*t_rel;

    p.x = courbePoint[p_A].x*hp1 +
          courbeVector[p_A].x*ht1 +
          courbeVector[p_A].x*ht2 +
          courbePoint[p_B].x*hp2;

    p.y = courbePoint[p_A].y*hp1 +
          courbeVector[p_A].y*ht1 +
          courbeVector[p_B].y*ht2 +
          courbePoint[p_B].y*hp2;

    return p;
}


//Overload /////////////////////////////////////////////////////////////////////

//offset overload
offset& offset::operator*=(const double s) { dx *= s; dy *= s; return *this; }
offset offset::operator*(const double s) { return offset(*this) *= s; }
offset& offset::operator/=(const double s) { dx /= s; dy /= s; return *this; }
offset offset::operator/(const double s) const { return offset(*this) /= s; }

//point overload
point& point::operator+=(const offset& o) { x += o.dx; y += o.dy; return *this; }
point point::operator+(const offset& o) const { return point(*this) += o; }
point& point::operator-=(const offset& o) { x -= o.dx; y -= o.dy; return *this; }
point point::operator-(const offset& o) const{ return point(*this) -= o; }
point point::operator*(const offset& o) { x*= o.dx; y*= o.dy; return *this;};
//point point::operator==(const point& p) const{ return (p.x==this->x) && (p.y==this.y) ? 1 : 0; }
//point point::operator!=(const point& p) const{ return (p.x==this->x) && (p.y==this.y) ? 1 : 0; }

//stream overload
istream& point::input(istream& is) { return is >> x >> y; }
ostream& point::output(ostream& os) const { return os << x << " " << y; }
istream& operator>>(istream& is, point& p) { return p.input(is); }
ostream& operator<<(ostream& os, const point& p) { return p.output(os); }
