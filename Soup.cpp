#ifndef __MI_MESH_SOUP_CPP__
#define __MI_MESH_SOUP_CPP__ 1
#include "Soup.hpp"

Soup::Soup( void ) {

}

Soup::Soup( std::deque<Eigen::Vector3f>& pos ) {
        this->set(pos);
        return;
}

Soup::Soup( const Soup& d) {
        this->copy(d);
        return;
}

Soup&
Soup::operator = ( const Soup &d) {
        this->copy(d);
        return *this;
}

Soup::~Soup( void ) {
        return;
}

void
Soup::set (const  std::deque<Eigen::Vector3f>& pos) {
        this->_pos.clear();
        this->_pos.insert( this->_pos.end(), pos.begin(), pos.end());
        return;
}

bool
Soup::getMesh(Mesh& mesh,  const double error) {
        typedef Kdtree<Eigen::Vector3f>::Vector kd_vector;
        std::vector<kd_vector> kvec;
        kvec.reserve(this->_pos.size());
        for (size_t i = 0 ; i < this->_pos.size() ; i++) {
                kvec.push_back(kd_vector( this->_pos.at(i), static_cast<int>(i) ) );
        }
        Kdtree<kd_vector> tree(kvec);

        std::vector<int> index( this->_pos.size(), -1);
        std::deque<Eigen::Vector3f> vertex;
        int vidseq = 0;
        for (size_t i = 0 ; i < this->_pos.size(); i++) {
                if (index.at(i) != -1) continue;
                std::list<kd_vector> neighbor;
                tree.find( kd_vector(this->_pos.at(i), 0), error, neighbor, false);
                std::vector<int> id;
                for (std::list<kd_vector>::iterator iter = neighbor.begin() ; iter != neighbor.end() ; iter ++ ) {
                        id.push_back(iter->id());
                        index.at(iter->id()) = vidseq;
                }
                ++vidseq;
                std::vector<int>::iterator miniter = std::min_element(id.begin(), id.end());
                vertex.push_back( this->_pos.at(*miniter) );
        }
        std::deque< std::vector<int> > face;
        face.assign( index.size()/3 , std::vector<int>() );
        for( size_t i = 0 ; i < face.size() ; i++ ){
            face.at(i).assign( 3 , 0 );
            face.at(i).at(0) = index.at(i*3 + 0);
            face.at(i).at(1) = index.at(i*3 + 1);
            face.at(i).at(2) = index.at(i*3 + 2);
        }
        return mesh.read(vertex, face);
}

void
Soup::copy ( const Soup& d) {
        this->set(d._pos);
        return;
}

#endif// __MI_MESH_POLYGON_SOUP_HPP__

