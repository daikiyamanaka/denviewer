#ifndef EXPORTERMESH_HPP
#define EXPORTERMESH_HPP
#include "Mesh.hpp"
#include "string"

class Mesh;
class ExporterMesh
{
private:
    Mesh& _mesh;
public:
    ExporterMesh( Mesh &mesh );
    virtual ~ExporterMesh( void );
    virtual bool write( const std::string & filename) = 0;

protected:
   Mesh& getMesh( void );
};

#endif // EXPORTERMESH_HPP
