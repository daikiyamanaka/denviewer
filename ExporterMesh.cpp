#include "ExporterMesh.hpp"

ExporterMesh::ExporterMesh(Mesh &mesh) :_mesh ( mesh )
{
    return;
}

ExporterMesh::~ExporterMesh( void )
{
    return;
}

Mesh&
ExporterMesh::getMesh( void )
{
    return this->_mesh;
}
