//
// Created by trima on 13/02/18.
//

#ifndef TP1_UTILS_HPP
#define TP1_UTILS_HPP


#include <ostream>
#include <vector>
#include <iostream>
#include <sstream>


struct Vecteur {
    float xyz[ 3 ]; // les composantes
    Vecteur(){};
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

    // Retourne le vecteur dont les composantes sont les minima des
    // composantes de soi-même et de other.
    Vecteur inf( const Vecteur& other ) const {
        float x,y,z;
        (xyz[0] < other.xyz[0]) ? x=xyz[0] : x = other.xyz[0];
        (xyz[0] < other.xyz[0]) ? y=xyz[1] : y = other.xyz[1];
        (xyz[0] < other.xyz[0]) ? z=xyz[2] : z = other.xyz[2];
        return Vecteur(x,y,z);
    }
    // Retourne le vecteur dont les composantes sont les maxima des
    // composantes de soi-même et de other.
    Vecteur sup( const Vecteur& other ) const{
        float x,y,z;
        (other.xyz[0] < xyz[0]) ? x=xyz[0] : x = other.xyz[0];
        (other.xyz[0] < xyz[0]) ? y=xyz[1] : y = other.xyz[1];
        (other.xyz[0] < xyz[0]) ? z=xyz[2] : z = other.xyz[2];
        return Vecteur(x,y,z);
    }
    Vecteur cross( const Vecteur& v ) const{
        return Vecteur (
                ((*this)[1] * v[2]) - ((*this)[2] * v[1]),
                ((*this)[2] * v[0]) - ((*this)[0] * v[2]),
                ((*this)[0] * v[1]) - ((*this)[1] * v[0])
        );
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

};

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
    void boundingBox( Vecteur& low, Vecteur& up) const {
        for ( std::vector<Triangle>::const_iterator it = triangles.begin(), itE = triangles.end(); it != itE; ++it ) {
            for (int i = 0; i < 3; ++i) {
                low = low.inf((*it)[i]);
                up = low.sup((*it)[i]);
            }
        }
    }
};





#endif //TP1_UTILS_HPP