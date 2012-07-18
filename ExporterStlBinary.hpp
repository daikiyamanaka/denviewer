#ifndef __EXPORTER_STL_BINARY_HPP__
#define __EXPORTER_STL_BINARY_HPP__ 1
#include <string>
#include <Eigen/Dense>
#include "Mesh.hpp"
#include "ExporterMesh.hpp"

class ExporterStlBinary : public ExporterMesh
{
public:
        ExporterStlBinary ( Mesh &mesh );
        virtual ~ExporterStlBinary ( void );
        virtual bool write ( const std::string& filename );
private:
        bool write_vec ( const Eigen::Vector3f& vec, std::ofstream& fout );
};
#endif // __ExPORTER_STL_BINARY_HPP__
