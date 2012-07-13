#include "ImporterMeshObj.hpp"
#include "Mesh.hpp"
#include "Tokenizer.hpp"
#include <fstream>
#include <deque>
ImporterMeshObj::ImporterMeshObj ( Mesh& mesh ) : ImporterMesh ( mesh )
{
        return;
}

ImporterMeshObj::~ImporterMeshObj ( void )
{
        return;
}

bool
ImporterMeshObj::read ( const std::string& filename )
{
        std::ifstream fin;

        fin.open ( filename.c_str() );
        if ( !fin.is_open() ) {
                return false;
        }

    //std::deque<int> index;
    std::deque<std::vector<int> > index;
        std::deque<Eigen::Vector3f> vec;

	char buffer[512];
	while ( !fin.eof() ) {
		fin.getline ( buffer, sizeof ( buffer ) );
		if ( fin.eof() ) break;
		Tokenizer tokenizer ( std::string ( buffer ), std::string ( " /" ) );
		const std::vector<std::string> tok = tokenizer.getAll();
		if ( tok.at ( 0 ).compare ( "v" ) == 0 ) {
			Eigen::Vector3f v;
			v.x() = atof ( tok.at ( 1 ).c_str() );
			v.y() = atof ( tok.at ( 2 ).c_str() );
			v.z() = atof ( tok.at ( 3 ).c_str() );
			vec.push_back ( v );
		} else if ( tok.at ( 0 ).compare ( "f" ) == 0 ) {
			int id;
			std::vector<int> ind;
			Tokenizer tokenizer2 ( std::string ( buffer ), std::string ( " " ) );
			std::vector<std::string> tok2 = tokenizer2.getAll();

			const int vnum = static_cast<int> ( tok2.size() - 1 );
			// brute-force tesselation of polygons.                                    
			for ( int i = 0 ; i < vnum ; i++ ) {
				id = atoi ( tok.at ( ( tok.size() - 1 ) / vnum * i + 1 ).c_str() ) -1;
				ind.push_back ( id );
			}
			for ( int i = 0 ; i < vnum - 2 ; i++ ) {
                std::vector<int> _ind;
                _ind.push_back ( ind[0] );
                _ind.push_back ( ind[i+1] );
                _ind.push_back ( ind[i+2] );
                index.push_back(_ind);
			}
		} else {
			;
		}
	}
    /*for(size_t i = 0 ; i < index.size() ; i++) {
		pos.push_back(vec[index[i]]);
    }*/
        if ( ! this->getMesh().read ( vec, index ) ) {
                return false;
        }

        return true;
};
