// C++ program writing parametric curves in postscript. Demo mode available
// clear && g++ -Wall main.cpp log.cpp curve.cpp postscript.cpp -o postscriptit


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <cmath>
#include <string>

#include "postscript.h"
#include "curve.h"

using namespace std;

point saisi(void){
  point p;
  cout << "x coordinates ? ";
  cin >> p.x;
  cout << "y coordinates ? ";
  cin >> p.y;
  cout << "\n";
  return p;
}

int main(int argc, char *argv[]){

  cout << "----------------------------------------\n";
  cout << "----- Set & Draw parametric curves -----\n";
  cout << "----------------------------------------\n\n";

  int c;// menu choice variable
  vector <courbe*> courbe_index;

  char tmpname[] ="aproxipi.ps";
  ofstream myfile(tmpname);
  postscript post(myfile);

  offset marge(25,25);
  offset homotetie(4);


// menu ////////////////////////////////////////////////////////////////////////

  while(1){// main processing loop

      cout << "----------------------------------------\n"
           << "1 - Bezier curve order 1 ---------------\n"
           << "2 - Bezier curve order 3 ---------------\n"
           << "3 - Hermitte curve ---------------------\n"
           << "4 - Demo mode --------------------------\n"
           << "5 - Postscript file export -------------\n"
           //<< "----------------------------------------\n"
           << "6 - Exit program -----------------------\n"
           << "----------------------------------------\n";
      cin >> c;

      if(c==4) cout << "\nDemo mode activated, three curve created\n\n";


// bezier1 curve ///////////////////////////////////////////////////////////////

      if(c==1 || c==4){
        bezier1* b1 = new bezier1();
        uint nb_point=0;
        if(c==1){
          cout << "\nHow many point for the curve ?\n";
          while(cin >> nb_point && nb_point < 2){ cout << "Incorrect value\n"; };
          for(uint i=0;i<nb_point; ++i){
            cout << "Coordinate for point n°" << i << " to add ?\n";
            point p = saisi();
            b1->addPoint(p*homotetie+marge);
          }
          cout << nb_point << " points were added to the Bezier order 1 curve\n";
        }

        else{// demo mode
          b1->addPoint(point(0,0)*homotetie+marge);
          b1->addPoint(point(50,50)*homotetie+marge);
          b1->addPoint(point(100,40)*homotetie+marge);
        }
        courbe_index.push_back(b1);
      }


// bezier3 curve ///////////////////////////////////////////////////////////////

      if(c==2 || c==4){
        bezier3* b3 = new bezier3();
        uint nb_point=0, nb_atract;
        if(c==2){
          cout << "\nHow many point for the curve ?\n";
          while(cin >> nb_point && nb_point < 2){ cout << "Incorrect value\n"; };
          for(uint i=0;i<nb_point; ++i){
            cout << "Coordinate for point n°" << i << " to add ?\n";
            point p = saisi();
            b3->addPoint(p*homotetie+marge);
          }
          cout << nb_point << " points were added to the Bezier order 3 curve\n";

          nb_atract=(nb_point-1)*2;
          for(uint i=0;i<nb_atract; ++i){
            cout << "Coordinate for attracting point n°" << i << " to add ?\n";
            point p = saisi();
            cout << floor(nb_atract/2);
            b3->addAtract(p*homotetie+marge);
          }
          cout << nb_atract << " attracting points were added to the Bezier order 3 curve\n\n";
        }

        else{// demo mode
          b3->addPoint(point(0,0)*homotetie+marge);
          b3->addPoint(point(50,50)*homotetie+marge);
          b3->addPoint(point(100,40)*homotetie+marge);
          b3->addAtract(point(30,50)*homotetie);
          b3->addAtract(point(70,-20)*homotetie);
          b3->addAtract(point(60,100)*homotetie);
          b3->addAtract(point(140,-40)*homotetie);
        }
        courbe_index.push_back(b3);
      }


// hermitte curve //////////////////////////////////////////////////////////////

      if(c==3 || c==4){
        hermitte* h = new hermitte();
        uint nb_point=0, nb_vector;
        if(c==3){
          cout << "\nHow many point for the curve ?\n";
          while(cin >> nb_point && nb_point < 2){ cout << "Incorrect value\n"; };
          for(uint i=0;i<nb_point; ++i){
            cout << "Coordinate for point n°" << i << " to add ?\n";
            point p = saisi();
            h->addPoint(p*homotetie+marge);
          }
          cout << nb_point << " points were added to the Bezier order 3 curve\n\n";

          nb_vector=nb_point;
          for(uint i=0;i<nb_vector; ++i){
            cout << "Coordinate for vector n°" << i << " to add ?\n";
            point p = saisi();
            h->addVector(p*homotetie+marge);
          }
          cout << nb_vector << " vectors were added to the Hermitte curve\n\n";
        }

        else{// demo mode
          h->addPoint(point(0,0)*homotetie+marge);
          h->addPoint(point(50,50)*homotetie+marge);
          h->addPoint(point(100,40)*homotetie+marge);
          h->addVector(point(30,50)*homotetie);
          h->addVector(point(70,-20)*homotetie);
          h->addVector(point(60,100)*homotetie);
        }
        courbe_index.push_back(h);
      }


// curves export ///////////////////////////////////////////////////////////////

      if(c==5){
        cout << "\nName of the output file ? (default is 'curve.ps')";
        string filename = "";
        cin.ignore(1);
        getline(cin, filename);
        if(filename.empty()){
          filename = "curve.ps";
        }
        cout << "Export of the file named " << filename << "\n\n";

        // postcript header
        post << "%! PS-2.0 EPSF-2.0\n" << "%%Orientation: Portrait\n"
             << "%%BoundingBox: 0 0 500 300\n" << "1 setlinecap\n";

        // draw background color
        post << "0.2 0.2 0.2 setrgbcolor clippath fill\n";

        // draw control points
        post << color(1,1,1);
        post <<  point(-15,0)+marge << " moveto " << point(500,0)+marge << " lineto stroke\n";
        post <<  point(0,-15)+marge << " moveto " << point(0,500)+marge << " lineto stroke\n";

        // draw curves
        for(uint i=0; i<courbe_index.size(); ++i){
          post << color(i-2,i-1,i);
          post << "1 setlinewidth\n";
          post << *courbe_index.at(i);

          // draw points from curves
          post << color(0.9,0.9,0.9);
          post << "3 setlinewidth\n";
          for(uint j=0; j<((*courbe_index.at(i)).courbePoint.size()); ++j){
            post << crux((*courbe_index.at(i)).courbePoint.at(j), 5);
          }
        }

        // postcript footer
        post << "showpage";

        rename( tmpname , &filename[0] );
      }


// Exit program ////////////////////////////////////////////////////////////////

      if(c==6){
        cout << "----------------------------------------\n";
        cout << "--------- Set & Draw has ended ---------\n";
        cout << "----------------------------------------\n\n";
        return 0;
      }
      /*if(c != (1 || 2 || 3 || 4 || 5 || 6)){
        cout << "Veuillez saisir un choix proposé\n\n";
      }*/

  }// End of the loop, exiting program

  return 0;
}// END

//Generateur automatique de documentation Docs => Doxygen
// /** ... µ/
// /// < (avant, par défaut après)
// export en pdf, html, man page, etc
// ex: function

/** description courte
 *
 * description longue (plusieurs lignes)
 * ...
 *
 * @param nom description
 * etc
 * @return role de la valeur produite
 */
