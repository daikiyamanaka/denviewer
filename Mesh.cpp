#include "Mesh.hpp"

Mesh::Mesh ( void )
{
        return;
}

Mesh::~Mesh ( void )
{
        this->clear();
        return;
}
bool
Mesh::read ( const std::deque<Eigen::Vector3f>& v , const std::deque<std::vector<int> >& id)
{
        //if ( v.size() % 3 != 0 ) {
                //return false; // 頂点数が不正
        //}
        this->clear();
        this->_vertex.insert ( this->_vertex.end(), v.begin(), v.end() );
        this->_index.insert( this->_index.end(), id.begin(), id.end());

        // compute face normal
        const int numFaces = this->getNumFaces();
        for ( int i = 0 ; i < numFaces ; i+=1 ) {
                const Eigen::Vector3f v1 = this->getPosition ( this->_index[i][1] ) - this->getPosition ( this->_index[i][0] ) ;
                const Eigen::Vector3f v2 = this->getPosition ( this->_index[i][2] ) - this->getPosition ( this->_index[i][0] ) ;
                this->_normal.push_back ( v1.cross ( v2 ).normalized() );
        }

        //compute vertex normal
        const int numVertexs = this->_vertex.size();
        for ( int i = 0 ; i < numVertexs ; i+=1 ) {
            Eigen::Vector3f vn(0,0,0);
            int neighbor_count = 0;
            for (int j = 0; j < this->_index.size(); j++){
                if(this->_index[j][0] == i || this->_index[j][1] == i || this->_index[j][2] == i ){
                    vn += this->_normal[j];
                    neighbor_count++;
                }
            }
            this->_vnormal.push_back(vn.normalized());
        }

        return true;
}
void
Mesh::clear ( void )
{
        this->_vertex.clear();
        this->_normal.clear();
        this->_index.clear();
        return;
}
Eigen::Vector3f
Mesh::getPosition ( const int fid, const int vid ) const
{
        return this->_vertex.at ( fid * 3 + vid );
}

Eigen::Vector3f
Mesh::getPosition ( const int id ) const
{
        return this->_vertex.at ( id );
}

Eigen::Vector3f
Mesh::getNormal ( const int fid ) const
{
        return this->_normal.at ( fid );
}

Eigen::Vector3f
Mesh::getVNormal ( const int id ) const
{
        return this->_vnormal.at ( id );
}

std::vector<int>
Mesh::getIndex( const int id) const
{
    return this->_index.at (id);
}

int
Mesh::getNumFaces ( void ) const
{
        return this->_index.size();
}
void
Mesh::getBoundingBox ( Eigen::Vector3f& bmin, Eigen::Vector3f& bmax )
{
        bmin = this->getPosition ( 0, 0 );
        bmax = bmin;

        /*const int numFaces = this->getNumFaces();
        for ( int i = 0 ; i < numFaces ; i+=1 ) {
                for ( int j = 0 ; j < 3 ; j+=1 ) {
                        const Eigen::Vector3f& p = this->getPosition ( i,j );
                        if ( bmin.x() > p.x() ) bmin.x()  = p.x();
                        if ( bmax.x() < p.x() ) bmax.x()  = p.x();
                        if ( bmin.y() > p.y() ) bmin.y()  = p.y();
                        if ( bmax.y() < p.y() ) bmax.y()  = p.y();
                        if ( bmin.z() > p.z() ) bmin.z()  = p.z();
                        if ( bmax.z() < p.z() ) bmax.z()  = p.z();
                }
        }*/

        const int numVertexs = this->_vertex.size();
                for ( int i = 0 ; i < numVertexs ; i+=1 ) {
                        const Eigen::Vector3f& p = this->getPosition ( i );
                        if ( bmin.x() > p.x() ) bmin.x()  = p.x();
                        if ( bmax.x() < p.x() ) bmax.x()  = p.x();
                        if ( bmin.y() > p.y() ) bmin.y()  = p.y();
                        if ( bmax.y() < p.y() ) bmax.y()  = p.y();
                        if ( bmin.z() > p.z() ) bmin.z()  = p.z();
                        if ( bmax.z() < p.z() ) bmax.z()  = p.z();
                }
        return;
}

