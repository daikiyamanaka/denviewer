#ifndef EXPORTEROBJ_HPP
#define EXPORTEROBJ_HPP
#include "ExporterMesh.hpp"


class ExporterObj : public ExporterMesh
{
public:
    ExporterObj(Mesh &mesh);
    virtual ~ExporterObj( void );
    virtual bool write(const std::string &filename);
};

#endif // EXPORTEROBJ_HPP
