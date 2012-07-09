#include "ExporterStlBinary.hpp"
#include <fstream>

ExporterStlBinary::ExporterStlBinary ( Mesh &mesh ) : ExporterMesh(mesh)
{
        return;
}

ExporterStlBinary::~ExporterStlBinary ( void )
{
        return;
}

bool
ExporterStlBinary::write ( const std::string& filename )
{
        std::ofstream fout;

        fout.open ( filename.c_str(), std::ios::binary );
        if ( !fout.is_open() ) {
                return false;
        }

        char name[80];
        fout.write ( name, 80 );
        unsigned int num_triangles = static_cast<int> ( this->getMesh().getNumFaces() );
        fout.write ( ( char* ) &num_triangles, 4 );

        for ( int i = 0 ; i < this->getMesh().getNumFaces() ; i += 1 ) {
                Eigen::Vector3f v0 = this->getMesh().getPosition ( i, 0 );
                Eigen::Vector3f v1 = this->getMesh().getPosition ( i, 1 );
                Eigen::Vector3f v2 = this->getMesh().getPosition ( i, 2 );
                Eigen::Vector3f n  = this->getMesh().getNormal ( i );
                if ( !this->write_vec ( n, fout ) ) return false;
                if ( !this->write_vec ( v0,fout ) ) return false;
                if ( !this->write_vec ( v1,fout ) ) return false;
                if ( !this->write_vec ( v2,fout ) ) return false;
                unsigned short prop = 0x0000; //2byte property
                if ( !fout.write ( ( char* ) &prop, 2 )      ) return false;
        }
        return true;
}
bool
ExporterStlBinary::write_vec ( const Eigen::Vector3f& vec, std::ofstream& fout )
{
        const float x = vec.x();
        const float y = vec.y();
        const float z = vec.z();
        if ( !fout.write ( ( char* ) &x, sizeof ( float ) ) ) return false;
        if ( !fout.write ( ( char* ) &y, sizeof ( float ) ) ) return false;
        if ( !fout.write ( ( char* ) &z, sizeof ( float ) ) ) return false;
        return true;
}
