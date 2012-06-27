#include "ImporterMesh.hpp"
#include "Mesh.hpp"

ImporterMesh::ImporterMesh ( Mesh& mesh ) :_mesh ( mesh )
{
        return;
}
ImporterMesh::~ImporterMesh ( void )
{
        return;
}

Mesh& 
ImporterMesh::getMesh(void) {
	return this->_mesh;
}










