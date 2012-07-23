#include "ImporterPointsCloudPcdAscii.hpp"
#include "Mesh.hpp"
#include "Tokenizer.hpp"
#include <fstream>
#include <iostream>
#include <deque>
#include <vector>


ImporterPointsCloudPcdAscii::ImporterPointsCloudPcdAscii ( Mesh& mesh ) : ImporterMesh ( mesh )
{
        return;
}

ImporterPointsCloudPcdAscii::~ImporterPointsCloudPcdAscii( void )
{
        return;
}

bool
ImporterPointsCloudPcdAscii::read ( const std::string& filename )
{
    std::ifstream fin;

    fin.open ( filename.c_str() );
    if ( !fin.is_open() ) {
            return false;
    }
    std::deque<Eigen::Vector3f> pos;
    std::deque<Eigen::Vector3f> color;//future work, ignored
    std::deque<Eigen::Vector3f> normal;//future work, ignored
    std::deque<std::vector<int> > index;//empty

    enum type{X,Y,Z,RGB,NX,NY,NZ};

    std::vector<int> type_line;

    //Header 10 lines
    std::string buf;
    for(int i = 0; i < 10; i++)
    {
        std::getline(fin,buf);
        if(fin.eof()){
            break;
        }else if(buf[0] == '#' || buf == ""){
            i--;
            continue;//comment
        }else{
            Tokenizer token(buf," ");

            if(token.get(0) == "FIELDS"){

                for(int j = 0; j < token.size(); j++)
                {
                    if(token.get(j)=="x"){
                        type_line.push_back(X);
                    }else if(token.get(j)=="y"){
                        type_line.push_back(Y);
                    }else if(token.get(j)=="z"){
                        type_line.push_back(Z);
                    }else if(token.get(j)=="rgb"){
                        type_line.push_back(RGB);
                        type_line.push_back(RGB);
                        type_line.push_back(RGB);
                    }else if(token.get(j)=="normal_x"){
                        type_line.push_back(NX);
                    }else if(token.get(j)=="normal_y"){
                        type_line.push_back(NY);
                    }else if(token.get(j)=="normal_z"){
                        type_line.push_back(NZ);
                    }
                }
            }

        }
    }

    if(type_line.empty()){
        //return false;

        fin.clear();

        fin.seekg(0,std::ios::beg);

        std::getline(fin,buf);

        Tokenizer token(buf," ");
        if(token.size() == 3){
            type_line.push_back(X);
            type_line.push_back(Y);
            type_line.push_back(Z);
        }else if(token.size() == 6){
            type_line.push_back(X);
            type_line.push_back(Y);
            type_line.push_back(Z);
            type_line.push_back(RGB);
            type_line.push_back(RGB);
            type_line.push_back(RGB);
        }
        fin.clear();
        fin.seekg(0,std::ios::beg);

    }

    while(!fin.eof())
    {
        Eigen::Vector3f p;
        for(int i = 0; i < type_line.size(); i++){
            fin >> buf;
            switch (type_line[i]){
            case X:
                p[0] = atof(buf.c_str());
                break;
            case Y:
                p[1] = atof(buf.c_str());
                break;
            case Z:
                p[2] = atof(buf.c_str());
                break;
            case RGB:
                break;
            case NX:
                  break;
            case NY:
                break;
            case NZ:
                break;
            default:
                break;

            }
        }

        pos.push_back(p);
    }

    if ( ! this->getMesh().read ( pos, index ) ) {
            return false;
    }

    return true;
}
