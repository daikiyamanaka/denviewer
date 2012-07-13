#include "ImporterPointsCloudPcdAscii.hpp"
#include "Mesh.hpp"
#include <fstream>
#include <deque>


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
    std::deque<std::vector<int> > index;//empty

    //ignore first 7 lines
    std::string buf;
    for(int i = 0; i < 7; i++)
    {
        std::getline(fin,buf);
    }

    std::string bx, by, bz;

    while(!fin.eof())
    {
        fin >> bx >> by >> bz;
        Eigen::Vector3f p;
        p[0]  = (float)atof(bx.c_str());
        p[1]  = (float)atof(by.c_str());
        p[2]  = (float)atof(bz.c_str());

        pos.push_back(p);
    }

    if ( ! this->getMesh().read ( pos, index ) ) {
            return false;
    }

    return true;
}
