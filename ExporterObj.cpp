#include "ExporterObj.hpp"
#include "fstream"

ExporterObj::ExporterObj(Mesh &mesh ) : ExporterMesh(mesh)
{
    return;
}

ExporterObj::~ExporterObj( void )
{
    return;
}

bool
ExporterObj::write(const std::string &filename)
{
    std::ofstream fout;

    fout.open ( filename.c_str() );
    if ( !fout.is_open() ) {
            return false;
    }

    const size_t faceNum = this->getMesh().getNumFaces();
    const size_t vxNum   = this->getMesh().getNumVertex();

    for (size_t i = 0 ; i < vxNum ; i++) {
            Eigen::Vector3f v = this->getMesh().getPosition(i);
            fout<<"v "<<v.x()<<" "<<v.y()<<" "<<v.z()<<std::endl;
    }
    for (size_t i = 0 ; i < faceNum ; i++) {
            std::vector<int> idx = getMesh().getIndex(i);
            fout<<"f "<<idx[0]+1<<" "<<idx[1]+1<<" "<<idx[2]+1<<std::endl;
    }
    return true;
}

