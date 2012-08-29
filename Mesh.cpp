#include "Mesh.hpp"
#include "iostream"

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
        const int numVertexs = this->getNumVertex();
        Eigen::Vector3f vn(1,0,0);
        this->_vnormal.resize(numVertexs,vn);
        for ( int i = 0 ; i < numFaces ; i+=1 ) {
            for ( int j = 0 ; j < 3 ; j+=1 ) {
                this->_vnormal[this->_index[i][j]] += this->_normal[i];
            }
        }
        for ( int i = 0 ; i < this->_vnormal.size() ; i+=1 ) {
            this->_vnormal[i].normalize();
        }

        //compute bounding box;
        //const int numVertexs = this->_vertex.size();
        bmin = this->getPosition(0);
        bmax = bmin;
        for ( int i = 1 ; i < numVertexs ; i+=1 ) {
                const Eigen::Vector3f& p = this->getPosition ( i );
                if ( bmin.x() > p.x() ) bmin.x()  = p.x();
                if ( bmax.x() < p.x() ) bmax.x()  = p.x();
                if ( bmin.y() > p.y() ) bmin.y()  = p.y();
                if ( bmax.y() < p.y() ) bmax.y()  = p.y();
                if ( bmin.z() > p.z() ) bmin.z()  = p.z();
                if ( bmax.z() < p.z() ) bmax.z()  = p.z();
        }
        return true;
}
void
Mesh::clear ( void )
{
        this->_vertex.clear();
        this->_normal.clear();
        this->_vnormal.clear();
        this->_index.clear();
        return;
}
Eigen::Vector3f
Mesh::getPosition ( const int fid, const int vid ) const
{
        return this->_vertex.at ( this->_index[fid][vid] );
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

bool
Mesh::NormalDataExists(void) const
{
    return !this->_normal.empty();
}

bool
Mesh::VNormalDataExists(void) const
{
    return !this->_vnormal.empty();
}

bool
Mesh::IndexDataExists(void) const
{
    return !this->_index.empty();
}

int
Mesh::getNumFaces ( void ) const
{
        return this->_index.size();
}

int
Mesh::getNumVertex( void ) const
{
    return this->_vertex.size();
}

void
Mesh::getBoundingBox ( Eigen::Vector3f& _bmin, Eigen::Vector3f& _bmax )
{
        _bmin = bmin;
        _bmax = bmax;

        return;
}

bool
Mesh::swapAxis( const int axisA, const int axisB )
{
    if(axisA*axisB < 0 || axisA > 2 || axisB > 2){
        return false;
    }

    float x;
    int vnum = this->getNumVertex();
    for(int i = 0; i < vnum; i++)
    {
        x = this->_vertex[i][axisA];
        this->_vertex[i][axisA] = this->_vertex[i][axisB];
        this->_vertex[i][axisB] = x;
        x = this->_normal[i].x();
        this->_normal[i][axisA] = this->_vertex[i][axisB];
        this->_normal[i][axisB] = x;
        x = this->_vnormal[i].x();
        this->_vnormal[i][axisA] = this->_vnormal[i][axisB];
        this->_vnormal[i][axisB] = x;
    }

    int fnum = this->getNumFaces();
    for(int i = 0; i < fnum; i++)
    {
        int i0 = this->_index[i][0];
        int i2 = this->_index[i][2];

        this->_index[i][0] = i2;
        this->_index[i][2] = i0;
    }
    x = this->bmax[axisA];
    this->bmax[axisA] =  this->bmax[axisB];
    this->bmax[axisB] = x;
    x = this->bmin[axisA];
    this->bmin[axisA] =  this->bmin[axisB];
    this->bmin[axisB] = x;
    return true;
}
