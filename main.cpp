#include <qapplication.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Viewer.h"
#include "Utils.hpp"

using namespace std;
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
    input.close(); // à la fin
    viewer.show();
    // Run main loop.
    application.exec();
    return 0;
}
