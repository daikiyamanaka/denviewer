#ifndef EXPORTERSTLASCII_HPP
#define EXPORTERSTLASCII_HPP
#include "ExporterMesh.hpp"

class ExporterStlAscii : public ExporterMesh
{
public:
    ExporterStlAscii( Mesh &mesh );
    virtual ~ExporterStlAscii( void );
    virtual bool write(const std::string &filename);
};

#endif // EXPORTERSTLASCII_HPP
