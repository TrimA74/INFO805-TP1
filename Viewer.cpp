/// \file Viewer.cpp
#include "Viewer.h"
#include <iterator>

using namespace std;

// Draws a tetrahedron with 4 colors.
void Viewer::draw()
{

    //const float nbSteps = 200.0;

    float colorBronzeDiff[4] = { 0.8, 0.6, 0.0, 1.0 };
    //float colorRedDiff[4]    = { 1.0, 0.0, 0.0, 1.0 };
    //float colorGreenDiff[4]  = { 0.0, 1.0, 0.0, 1.0 };
    //float colorBlueDiff[4]   = { 0.0, 0.0, 1.0, 1.0 };

    float colorBronzeSpec[4] = { 1.0, 1.0, 0.4, 1.0 };
    //float colorNull      [4] = { 0.0, 0.0, 0.0, 1.0 };
    // Draws triangles given by 3 vertices.
    glBegin(GL_TRIANGLES);
    glColor4fv(colorBronzeDiff);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, colorBronzeDiff);
    glMaterialfv(GL_FRONT, GL_SPECULAR, colorBronzeSpec);
    glMaterialf(GL_FRONT, GL_SHININESS, 20.0f );
    for ( std::vector<Triangle>::const_iterator it = this->ptrSoup->triangles.begin(), itE = this->ptrSoup->triangles.end(); it != itE; ++it ) {
      const Triangle& T = *(it);
      Vecteur n = T.normal();
      glNormal3f( n[ 0 ], n[ 1 ], n[ 2 ] );
    glVertex3f( (*it)[0][0],
                (*it)[0][1],
                (*it)[0][2]);
    glVertex3f( (*it)[1][0],
                (*it)[1][1],
                (*it)[1][2]);
    glVertex3f( (*it)[2][0],
                (*it)[2][1],
                (*it)[2][2]);
    glColor4fv(colorBronzeDiff);
    }
    glEnd();
}

qglviewer::Vec convertToVec(Vecteur& v){
    return qglviewer::Vec(v[0],v[1],v[2]);
}
void Viewer::init()
{

  Vecteur low,up;
  this->ptrSoup->boundingBox(low,up);
    camera()->setSceneBoundingBox(convertToVec(low),convertToVec(up));
  // ou camera()->setSceneRadius( ... );
  camera()->showEntireScene();

  // Restore previous viewer state.
  // restoreStateFromFile();

  // Opens help window
  help();
}




QString Viewer::helpString() const
{
  QString text("<h2>S i m p l e V i e w e r</h2>");
  text += "Use the mouse to move the camera around the object. ";
  text += "You can respectively revolve around, zoom and translate with the three mouse buttons. ";
  text += "Left and middle buttons pressed together rotate around the camera view direction axis<br><br>";
  text += "Pressing <b>Alt</b> and one of the function keys (<b>F1</b>..<b>F12</b>) defines a camera keyFrame. ";
  text += "Simply press the function key again to restore it. Several keyFrames define a ";
  text += "camera path. Paths are saved when you quit the application and restored at next start.<br><br>";
  text += "Press <b>F</b> to display the frame rate, <b>A</b> for the world axis, ";
  text += "<b>Alt+Return</b> for full screen mode and <b>Control+S</b> to save a snapshot. ";
  text += "See the <b>Keyboard</b> tab in this window for a complete shortcut list.<br><br>";
  text += "Double clicks automates single click actions: A left button double click aligns the closer axis with the camera (if close enough). ";
  text += "A middle button double click fits the zoom of the camera and the right button re-centers the scene.<br><br>";
  text += "A left button double click while holding right button pressed defines the camera <i>Revolve Around Point</i>. ";
  text += "See the <b>Mouse</b> tab and the documentation web pages for details.<br><br>";
  text += "Press <b>Escape</b> to exit the viewer.";
  return text;
}
