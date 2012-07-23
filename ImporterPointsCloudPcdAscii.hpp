#ifndef IMPORTERPOINTSCLOUDPCDASCII_H
#define IMPORTERPOINTSCLOUDPCDASCII_H
#include "ImporterMesh.hpp"

class ImporterPointsCloudPcdAscii : public ImporterMesh
{
public:
        ImporterPointsCloudPcdAscii ( Mesh& mesh );
        virtual ~ImporterPointsCloudPcdAscii ( void );
        virtual bool read ( const std::string& filename );
};
#endif // IMPORTERPOINTSCLOUDPCDASCII_H
