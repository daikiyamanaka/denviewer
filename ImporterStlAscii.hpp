#ifndef __MI_MESH_IMPORTER_STL_ASCII_HPP__
#define __MI_MESH_IMPORTER_STL_ASCII_HPP__ 1
#include "ImporterMesh.hpp"
#include "Soup.hpp"
#include <fstream>

class ImporterStlAscii : public ImporterMesh
{
private:
        int _count;
public:
        ImporterStlAscii( Mesh& data);
        virtual ~ImporterStlAscii( void );
        virtual bool read ( const std::string& filename );
        virtual bool check_tag(std::string& str, std::string keyword, bool warning = false);
};
#endif// __MI_MESH_IMPORTER_STL_ASCII_HPP__
