#ifndef __IMPORTER_MESH_OBJ_HPP__
#define __IMPORTER_MESH_OBJ_HPP__ 1
#include "ImporterMEsh.hpp"

class ImporterMeshObj : public ImporterMesh
{
public:
        ImporterMeshObj ( Mesh& mesh );
        virtual ~ImporterMeshObj ( void );
        virtual bool read ( const std::string& filename );
};
#endif // __IMPORTER_MESH_OBJ_HPP__
