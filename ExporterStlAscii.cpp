#include "ExporterStlAscii.hpp"
#include <fstream>

ExporterStlAscii::ExporterStlAscii(Mesh &mesh) : ExporterMesh(mesh)
{
    return;
}

ExporterStlAscii::~ExporterStlAscii( void )
{
    return;
}

bool
ExporterStlAscii::write(const std::string &filename)
{
    std::ofstream fout;

    fout.open ( filename.c_str() );
    if ( !fout.is_open() ) {
            return false;
    }

    fout<<"solid "<<"mesh"<<std::endl;
    for (size_t i = 0 ; i < this->getMesh().getNumFaces() ; i += 1) {
        Eigen::Vector3f v0 = this->getMesh().getPosition(i,0);
        Eigen::Vector3f v1 = this->getMesh().getPosition(i,1);
        Eigen::Vector3f v2 = this->getMesh().getPosition(i,2);

        Eigen::Vector3f n;
        n = this->getMesh().getNormal(i);

        if (n.norm() > 1.0e-15) { //@bug should be removed.
            n.normalize();
            fout<<"facet normal "<<n.x()<<" "<<n.y()<<" "<<n.z()<<std::endl;
            fout<<"outer loop"<<std::endl;
            fout<<"vertex "<<v0.x()<<" "<<v0.y()<<" "<<v0.z()<<std::endl;
            fout<<"vertex "<<v1.x()<<" "<<v1.y()<<" "<<v1.z()<<std::endl;
            fout<<"vertex "<<v2.x()<<" "<<v2.y()<<" "<<v2.z()<<std::endl;
            fout<<"endloop"<<std::endl;
            fout<<"endfacet"<<std::endl;
        }
    }
    fout<<"endsolid"<<std::endl;
    return true;
}
