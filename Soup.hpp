#ifndef __MI_MESH_SOUP_HPP__
#define __MI_MESH_SOUP_HPP__ 1
#include "Mesh.hpp"
#include "Kdtree.hpp"

#include <iostream>
class Soup
{
private:
        std::deque<Eigen::Vector3f> _pos;
public:
        Soup( void );
        Soup( std::deque<Eigen::Vector3f>& pos );
        Soup( const Soup& d);
        Soup& operator = ( const Soup &d);
        virtual ~Soup( void );
        void set (const  std::deque<Eigen::Vector3f>& pos);
        bool getMesh(Mesh& mesh,  const double error = 1.0e-10);
protected :
        void copy ( const Soup& d);
};

#endif// __MI_MESH_POLYGON_SOUP_HPP__
