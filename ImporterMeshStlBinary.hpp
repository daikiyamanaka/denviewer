#ifndef __IMPORTER_MESH_STL_BINARY_HPP__
#define __IMPORTER_MESH_STL_BINARY_HPP__ 1
#include "ImporterMesh.hpp"
#include "Soup.hpp"

class ImporterMeshStlBinary : public ImporterMesh
{
public:
        ImporterMeshStlBinary ( Mesh& mesh );
        virtual ~ImporterMeshStlBinary ( void );
        virtual bool read ( const std::string& filename );
        virtual bool check( const std::string& filename );
};
#endif // __IMPORTER_MESH_STL_BINARY_HPP__
