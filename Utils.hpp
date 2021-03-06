//
// Created by trima on 13/02/18.
//

#ifndef TP1_UTILS_HPP
#define TP1_UTILS_HPP


#include <ostream>
#include <vector>
#include <iostream>
#include <sstream>
#include <cmath>


struct Vecteur {
    float xyz[ 3 ]; // les composantes
    Vecteur(){
        xyz[0] = 0;
        xyz[1] = 0;
        xyz[2] = 0;
    };
    Vecteur( float x, float y, float z ){
        xyz[0] = x;
        xyz[1] = y;
        xyz[2] = z;
    }
    float  operator[]( int i ) const{
        return xyz[i];
    }
    float& operator[]( int i ){
        return xyz[i];
    }
    Vecteur operator-(Vecteur other) const{
        return Vecteur((*this)[0] - other[0],
                       (*this)[1] - other[1],
                       (*this)[2] - other[2]
        );
    }
    Vecteur operator/(float value) const {
        return Vecteur((*this)[0] / value, (*this)[1] / value, (*this)[2] / value);
    }

    // Retourne le vecteur dont les composantes sont les minima des
    // composantes de soi-même et de other.
    Vecteur inf( const Vecteur& other ) const {
        float x,y,z;
        (xyz[0] < other.xyz[0]) ? x=xyz[0] : x = other.xyz[0];
        (xyz[1] < other.xyz[1]) ? y=xyz[1] : y = other.xyz[1];
        (xyz[2] < other.xyz[2]) ? z=xyz[2] : z = other.xyz[2];
        return Vecteur(x,y,z);
    }
    // Retourne le vecteur dont les composantes sont les maxima des
    // composantes de soi-même et de other.
    Vecteur sup( const Vecteur& other ) const{
        float x,y,z;
        (other.xyz[0] < xyz[0]) ? x=xyz[0] : x = other.xyz[0];
        (other.xyz[1] < xyz[1]) ? y=xyz[1] : y = other.xyz[1];
        (other.xyz[2] < xyz[2]) ? z=xyz[2] : z = other.xyz[2];
        return Vecteur(x,y,z);
    }
    Vecteur cross( const Vecteur& v ) const{
        return Vecteur((*this)[1] * (v[2]) - (*this)[2] * v[1],
                       (*this)[2] * v[0] - (*this)[0] * v[2],
                       (*this)[0] * v[1] - (*this)[1] * v[0]
        );
    }

    Vecteur normalize() {
        float sum = 0;
        for(int i=0; i<3; i++) {
            sum+=xyz[i] * xyz[i];
        }
        float norm = sqrt(sum);
        return Vecteur((*this)[0]/norm,(*this)[1]/norm, (*this)[2]/norm);
    }




};

inline std::ostream& operator<<( std::ostream& out, Vecteur v )
{ out << v[ 0 ] << " " << v[ 1 ] << " " << v[ 2 ]; return out;}
/*
std::istream& operator>>( std::istream& in, Vecteur& v )
{ in >> v[ 0 ] >> v[ 1 ] >> v[ 2 ]; }
*/

struct Triangle {
    Vecteur xyz[3];
    Triangle(){

    }


    Triangle(Vecteur x, Vecteur y, Vecteur z){
        xyz[0] = x;
        xyz[1] = y;
        xyz[2] = z;
    }

    Vecteur  operator[]( int i ) const{
        return xyz[i];
    }
    Vecteur& operator[]( int i ){
        return xyz[i];
    }
    Vecteur normal() const{
        Vecteur u = xyz[1] - xyz[0];
        Vecteur v = xyz[2] - xyz[0];
        return u.cross(v).normalize();
    }


};

inline std::ostream& operator<<(std::ostream& os, Triangle t)
{
    os << t.xyz[0] << ' ' << t.xyz[1] << ' ' << t.xyz[2];
    return os;
}

struct TriangleSoup {
    std::vector<Triangle> triangles; // les triangles
    TriangleSoup() {}

    void read( std::istream& input ){

        std::string str;
        std::string type;

        if ( ! input.good() ) {
            std::cerr << "Probleme !";
        }
        /***
        * Tant qu'on a des commentaires
        */
        while(str.c_str()[0] == '#'){
            std::getline(input,str);
        }
        /***
         * Tant qu'on a des lignes avec des triangles
         */
        while(std::getline(input,str)){
            if(str.c_str()[0] == '#') {std::getline(input,str);} // si on a un commentaire on skip
            else {
                float t1x,t1y,t1z,t2x,t2y,t2z,t3x,t3y,t3z;
                std::istringstream istr( str );
                istr >> t1x >> t1y >> t1z >> t2x >> t2y >> t2z >> t3x >> t3y >> t3z;
                Vecteur v1(t1x,t1y,t1z);
                Vecteur v2(t2x,t2y,t2z);
                Vecteur v3(t3x,t3y,t3z);
                Triangle t(v1,v2,v3);
                triangles.push_back(t);

            }
        }

    }

    void write(std::ostream& output){
        for ( std::vector<Triangle>::iterator it = triangles.begin(), itE = triangles.end(); it != itE; ++it ) {
            output << (*it);
            output << "\n";
        }
    }
    void boundingBox( Vecteur& low, Vecteur& up) const {
        low = triangles[0][0];
        up = triangles[0][0];

        for ( std::vector<Triangle>::const_iterator it = triangles.begin(), itE = triangles.end(); it != itE; ++it ) {
            for (int i = 0; i < 3; ++i) {
        
                low = low.inf((*it)[i]);
                up = up.sup((*it)[i]);
            }
        }
    }
};

/// Définit un index sur 3 entiers. Toutes les opérations usuelles
/// sont surchargées (accès, comparaisons, égalité).
struct Index {
    int idx[ 3 ];
    Index() {}
    Index( int i0, int i1, int i2 )
    {
        idx[ 0 ] = i0;
        idx[ 1 ] = i1;
        idx[ 2 ] = i2;
    }
    Index( int indices[] )
    {
        idx[ 0 ] = indices[ 0 ];
        idx[ 1 ] = indices[ 1 ];
        idx[ 2 ] = indices[ 2 ];
    }
    int  operator[]( int i ) const { return idx[ i ]; }
    int& operator[]( int i )       { return idx[ i ]; }
    bool operator<( const Index& other ) const
    {
        return ( idx[ 0 ] < other.idx[ 0 ] )
               || ( ( idx[ 0 ] == other.idx[ 0 ] )
                    && ( ( idx[ 1 ] < other.idx[ 1 ] )
                         || ( ( idx[ 1 ] == other.idx[ 1 ] )
                              && ( idx[ 2 ] < other.idx[ 2 ] ) ) ) );
    }
    bool operator==(const Index& other) const {
        return ( idx[ 0 ] == other.idx[ 0 ] )
                    && ( ( idx[ 1 ] == other.idx[ 1 ] )
                              && ( idx[ 2 ] ==other.idx[ 2 ] ) );
    }
};




// Structure pour calculer le barycentre d'un ensemble de points.
struct CellData {
  Vecteur acc;
  int nb;
  // Crée un accumulateur vide.
  CellData(): acc(), nb(0) {}
  // Ajoute le point v à l'accumulateur.
  void add( const Vecteur& v ){
    acc.xyz[0] += v.xyz[0];
    acc.xyz[1] += v.xyz[1];
    acc.xyz[2] += v.xyz[2];

    nb++;

  }
  // Retourne le barycentre de tous les points ajoutés.
  Vecteur barycenter() const{
    return acc / nb;
  }
};

struct TriangleSoupZipper {
    TriangleSoup _anInput;
    TriangleSoup _anOutput;
    Index size;
    Vecteur low;
    Vecteur cellSize;
    Vecteur up;
    // Stocke pour chaque cellule son barycentre.
    std::map<Index, CellData> index2data;


    // Construit le zipper avec une soupe de triangle en entrée \a
    // anInput, une soupe de triangle en sortie \a anOutput, et un index \a size
    // qui est le nombre de cellules de la boîte découpée selon les 3 directions.
    TriangleSoupZipper( const TriangleSoup& anInput,
                        TriangleSoup& anOuput,
                        Index size ) {
        this->_anInput = anInput;
        this->_anOutput = anOuput;
        this->size = size;
        this->low = Vecteur();
        this->up = Vecteur();
        this->_anInput.boundingBox(this->low,this->up);
        this->index2data = std::map<Index, CellData>();
        this->cellSize = Vecteur((up[0] - low[0])/size[0],
                                 (up[1] - low[1])/size[1],
                                 (up[2] - low[2])/size[2]
        );



    }

    /// @return l'index de la cellule dans laquelle tombe \a p.
    Index index( const Vecteur& p) const {
        //formule : (index - debut ) / ((fin-debut)/distance-grille)
        Index i;
        
        i.idx[0] = (int)(p.xyz[0] - low[0]) / cellSize[0];
        i.idx[1] = (int)(p.xyz[1] - low[1]) / cellSize[1];
        i.idx[2] = (int)(p.xyz[2] - low[2]) / cellSize[2];

        return i;
    } 

    /// @return le centroïde de la cellule d'index \a idx (son "centre").
    Vecteur centroid( const Index& idx ) const {
        Vecteur v;
        
        //calcul du centroid
        v.xyz[0] = idx.idx[0]*cellSize[0]+(cellSize[0]/2)+low[0];
        v.xyz[1] = idx.idx[1]*cellSize[1]+(cellSize[1]/2)+low[1];
        v.xyz[2] = idx.idx[2]*cellSize[2]+(cellSize[2]/2)+low[2];

        return v;
    }

    void zip(){
    

        for ( std::vector<Triangle>::const_iterator it = this->_anInput.triangles.begin(), itE = this->_anInput.triangles.end(); it != itE; ++it )
        {

            Index idx[3];

            for (int i = 0; i < 3; ++i) {
                idx[i] = index((*it)[i]);
                index2data[idx[i]].add((*it)[i]);
            }

            if(!(idx[0] == idx[1] || idx[0] == idx[2] || idx[1] == idx[2]))
            {
                Triangle newT;
                for (int i = 0; i < 3; ++i) {
                    newT[i] = centroid(idx[i]);
                }


                //on l'ajoute
                this->_anOutput.triangles.push_back(newT);
            }
        }
    }

     void smartZip(){
    
        index2data.clear();

        this->zip();

        for ( std::vector<Triangle>::iterator it = this->_anOutput.triangles.begin(), itE = this->_anOutput.triangles.end(); it != itE; ++it )
        {

            for (int j = 0; j < 3; ++j) {

                (*it).xyz[j] = index2data[index((*it).xyz[j])].barycenter();
            }
        }

    }

};








#endif //TP1_UTILS_HPP
