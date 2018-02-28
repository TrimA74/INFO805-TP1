#include <qapplication.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Viewer.h"
#include "Utils.hpp"

using namespace std;
// int main(int argc, char** argv)
// {

//     // Read command lines arguments.
//     QApplication application(argc,argv);
//     // Instantiate the viewer.
//     Viewer viewer;
//     // Give a name
//     viewer.setWindowTitle("Viewer triangle soup");
//     // Make the viewer window visible on screen.
//     ifstream input( argv[1]); // input est un flux en entrée.
//     if ( ! input.good() ) std::cerr << "ERROR" << std::endl;
//     TriangleSoup ts;
//     ts.read(input);
//     viewer.ptrSoup = &ts;
//     input.close(); // à la fin
//     viewer.show();
//     // Run main loop.
//     application.exec();
//     return 0;
// }


int main(int argc, char** argv)
{

    if(argc<6){
        cout << "Merci de préciser tous les paramètres.\n";
        cout << "Usage : ./viewerQ2 <filename.tri> <output.tri> <index-x> <index-y> <index-z>\n";
        exit(-1);
    }

    // Read command lines arguments.
    QApplication application(argc,argv);
    // Instantiate the viewer.
    Viewer viewer;
    // Give a name
    viewer.setWindowTitle("Viewer triangle soup");
    // Make the viewer window visible on screen.
    ifstream input( argv[1]); // input est un flux en entrée.
    if ( ! input.good() ) std::cerr << "ERROR" << std::endl;
    TriangleSoup ts;
    ts.read(input);

    TriangleSoup anOutput;
    cout << "Taille entrée = " << ts.triangles.size() <<endl;

    TriangleSoupZipper tsz = TriangleSoupZipper(ts, anOutput, Index(atoi(argv[3]), atoi(argv[4]), atoi(argv[5])));
    tsz.smartZip();
    std::ofstream output( argv[2]);
    ts.triangles = tsz._anOutput.triangles;
    ts.write(output);

    viewer.ptrSoup = &tsz._anOutput;

    std::cout << "taille sortie  :  " <<  tsz._anOutput.triangles.size() << std::endl;

    //Affichage du taux de compression
    cout <<   tsz._anOutput.triangles.size()*100 / ts.triangles.size()<< "%"<<endl;
    input.close(); // à la fin
    viewer.show();
    // Run main loop.
    application.exec();
    return 0;
}

/* Q1
int main(int argc, char** argv)
{

    // Read command lines arguments.
    QApplication application(argc,argv);
    // Instantiate the viewer.
    Viewer viewer;
    // Give a name
    viewer.setWindowTitle("Viewer triangle soup");
    // Make the viewer window visible on screen.
    ifstream input( argv[1]); // input est un flux en entrée.
    if ( ! input.good() ) std::cerr << "ERROR" << std::endl;
    TriangleSoup ts;
    ts.read(input);

    viewer.ptrSoup = &ts;
    cout << "Taille entrée = " << ts.triangles.size() <<endl;
    input.close(); // à la fin
    viewer.show();
    // Run main loop.
    application.exec();
    return 0;
}*/