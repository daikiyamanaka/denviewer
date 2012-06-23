#include "ImporterMesh.hpp"
#include "Mesh.hpp"
#include <fstream>

ImporterMesh::ImporterMesh ( Mesh& mesh ) :_mesh ( mesh )
{
        return;
}
ImporterMesh::~ImporterMesh ( void )
{
        return;
}

bool
ImporterMesh::read ( const std::string& filename )
{
        std::ifstream fin;

        //determine extension
        int dot_id = filename.find_last_of(".");
        std::string file_type = filename.substr(dot_id+1);

        std::deque<Eigen::Vector3f> vec;
        std::deque<std::vector<int> > index;

        if(file_type == "stl"){

            fin.open ( filename.c_str(), std::ios::binary );
            if ( !fin.is_open() ) {
                    return false;
            }

            char buf[80];
            fin.read ( ( char* ) &buf, 80 );

            std::string name ( buf );
            if ( name.empty() ) name = std::string ( "mesh" );

            int fsize;
            fin.read ( ( char* ) &fsize, sizeof ( unsigned int ) );

            for ( int i = 0 ; i < fsize ; i+=1 ) {
                    if ( fin.bad() ) return false;
                    float nx, ny, nz;
                    fin.read ( ( char* ) & ( nx ), sizeof ( float ) );
                    fin.read ( ( char* ) & ( ny ), sizeof ( float ) );
                    fin.read ( ( char* ) & ( nz ), sizeof ( float ) );
                    for ( int j = 0 ; j < 3 ; j+=1 ) {
                            float x, y, z;
                            fin.read ( ( char* ) &x, sizeof ( float ) );
                            fin.read ( ( char* ) &y, sizeof ( float ) );
                            fin.read ( ( char* ) &z, sizeof ( float ) );
                            Eigen::Vector3f v ( x,y,z );
                            vec.push_back ( v );
                    }
                    std::vector<int> id;
                    id.resize(3);
                    id[0] = (3*i);
                    id[1] = (3*i+1);
                    id[2] = (3*i+2);
                    index.push_back(id);

                    char buf[2];
                    fin.read ( buf, 2 );
            }
        }else if(file_type == "obj"){

            fin.open ( filename.c_str() );
            if ( !fin.is_open() ) {
                    return false;
            }

            std::string buf, bx,by,bz;
            while(!fin.eof()){
                fin >> buf;
                if(buf == "v"){
                    fin >> bx >> by >> bz;
                    Eigen::Vector3f v ( atof(bx.c_str()),atof(by.c_str()),atof(bz.c_str()) );
                    vec.push_back ( v );
                }else if(buf == "f"){
                    fin >> bx >> by >> bz;
                    std::vector<int> id;
                    id.resize(3);
                    id[0] = atoi(bx.c_str());
                    id[1] = atoi(by.c_str());
                    id[2] = atoi(bz.c_str());
                    index.push_back(id);
                }
            }

        }else{
            return false;
        }


        fin.close();

        if ( ! this->_mesh.read ( vec, index ) ) {
                return false;
        }

        return true;
};
