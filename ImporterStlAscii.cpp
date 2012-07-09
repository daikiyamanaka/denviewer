#include "ImporterStlAscii.hpp"
#include "Mesh.hpp"
#include <fstream>
#include <iostream>

ImporterStlAscii::ImporterStlAscii ( Mesh& mesh ) : ImporterMesh ( mesh )
{
    this->_count = 0;
        return;
}

ImporterStlAscii::~ImporterStlAscii ( void )
{
        return;
}

bool
ImporterStlAscii::read ( const std::string& filename )
{
    std::ifstream fin;

    fin.open ( filename.c_str(), std::ios::binary );
    if ( !fin.is_open() ) {
            return false;
    }

        std::deque<Eigen::Vector3f> vec;

        char buffer[512];
        std::string str;

        fin.getline(buffer, 512);
        str = std::string(buffer);
        if (!this->check_tag(str, std::string("solid"), true) ) {
                return false; // do nothing
        }
        std::string name = str.substr(str.find("solid")+5);
        if (name == std::string() ) {
                std::stringstream ss;
                ss<<"mesh"<<this->_count;
                this->_count ++;
                name = ss.str();
        }

        while (! fin.eof() ) {
                fin.getline(buffer, 512);
                str = std::string(buffer);
                if ( this->check_tag(str, std::string("endsolid")) )break;
                if (!this->check_tag(str, std::string("facet"), true) )  return false;
                if (!this->check_tag(str, std::string("normal") ) ) {
                        fin.getline(buffer, 512);
                        if (this->check_tag(str, std::string("normal"), true) == false) return false;
                }

                fin.getline(buffer, 512);
                str = std::string(buffer);
                if (!this->check_tag(str, std::string("outer"), true) )return false;
                if (!this->check_tag(str, std::string("loop"), true)) return false;

                for (int i = 0 ; i < 3 ; i++) {
                        fin.getline(buffer, 512);
                        str = std::string(buffer);
                        if (!this->check_tag(str, std::string("vertex"), true)) return false;
                        Eigen::Vector3f v;
                        std::stringstream is(str.c_str());
                        is>>str>>v.x()>>v.y()>>v.z();
                        vec.push_back(v);
                }
                fin.getline(buffer, 512);
                str = std::string(buffer);
                if (!this->check_tag(str, std::string("endloop"), true)) return false;

                fin.getline(buffer, 512);
                str = std::string(buffer);
                if (!this->check_tag(str, std::string("endfacet"), true)) return false;
        }
        const float error = 1.0e-14f;
        Soup s(vec);
        s.getMesh(this->getMesh(), error);
        return true;
}

bool
ImporterStlAscii::check_tag(std::string& str, std::string keyword, bool warning) {
    //warnig = false;
        if ( str.find(keyword) == std::string::npos) {
                if ( warning ) {
                        std::cerr<<"Tag("<<keyword<<") cannot found."<<std::endl;
                        std::cerr<<str<<std::endl;
                }
                return false;
        }
        return true;
}

