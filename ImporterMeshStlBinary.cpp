#include "ImporterMeshStlBinary.hpp"
#include "Mesh.hpp"
#include <fstream>

ImporterMeshStlBinary::ImporterMeshStlBinary ( Mesh& mesh ) : ImporterMesh ( mesh )
{
        return;
}

ImporterMeshStlBinary::~ImporterMeshStlBinary ( void )
{
        return;
}

bool
ImporterMeshStlBinary::read ( const std::string& filename )
{
        std::ifstream fin;

        fin.open ( filename.c_str(), std::ios::binary );
        if ( !fin.is_open() ) {
                return false;
        }

        std::deque<Eigen::Vector3f> vec;
        std::deque<std::vector<int> > index;
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
        fin.close();

        if ( ! this->getMesh().read ( vec , index) ) {
                return false;
        }

        return true;
};
