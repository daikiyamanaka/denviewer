#include "Tokenizer.hpp"
	Tokenizer::Tokenizer ( const std::string& str, const std::string delim ) {
		std::string::size_type end;
		std::string line = str;
		
		for ( ; ; ) {
			end = line.find_first_of ( delim );
			if ( line.substr ( 0, end ).length() > 0 ) this->_token.push_back ( line.substr ( 0, end ) );
			if ( std::string::npos == end ) break;
			line = line.substr ( end + 1 );
		}
		return;
	};
	
	Tokenizer::~Tokenizer ( void ) {
		return;
	}
	
	size_t 
	Tokenizer::size ( void ) const {
		return this->_token.size();
	}
	
	std::string 
	Tokenizer::get ( const size_t i ) const {
		return this->_token.at ( i );
	}
	
	std::vector<std::string> 
	Tokenizer::getAll ( void ) {
		std::vector<std::string> result;
		result.insert ( result.end(), this->_token.begin(), this->_token.end() );
		return result;
	}
