#ifndef __MESH_HPP__
#define __MESH_HPP__ 1

#include <deque>
#include <vector>
#include <Eigen/Dense>
#include <Eigen/Geometry>

class Mesh
{
private:
        std::deque<Eigen::Vector3f> _vertex;
        std::deque<Eigen::Vector3f> _normal;
        std::deque<Eigen::Vector3f> _vnormal;
        std::deque<std::vector<int> > _index;

        Eigen::Vector3f bmin, bmax;

public:
        Mesh ( void ) ;
        virtual ~Mesh ( void ) ;
        bool read ( const std::deque<Eigen::Vector3f>& v , const std::deque<std::vector<int> >& id);
        void clear ( void );
        Eigen::Vector3f getPosition ( const int fid, const int vid ) const ;
        Eigen::Vector3f getPosition ( const int id) const ;
        Eigen::Vector3f getNormal ( const int fid ) const;
        Eigen::Vector3f getVNormal ( const int id ) const;
        std::vector<int> getIndex (const int id) const;

        bool NormalDataExists( void ) const;
        bool VNormalDataExists( void ) const;
        bool IndexDataExists( void ) const;

        int getNumFaces ( void ) const;
        int getNumVertex ( void ) const;
        void getBoundingBox ( Eigen::Vector3f& bmin, Eigen::Vector3f& bmax );

        //tool
        bool swapAxis(const int axisA, const int axisB);

};
#endif //  __MESH_HPP__
