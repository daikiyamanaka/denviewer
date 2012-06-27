#ifndef __TOKENIZER_HPP__
#define __TOKENIZER_HPP__ 1
#include <string>
#include <vector>

class Tokenizer
{
private:
	std::vector<std::string> _token;
public:
	/**
	 * @param [in] str a string to be tokenized.
	 * @param [in] delim a delidenter
	 * @return tokenized string
	 */
	Tokenizer ( const std::string& str, const std::string delim = std::string ( " " ) ) ;
	virtual ~Tokenizer ( void ) ;
	size_t size ( void ) const ;
	std::string get ( const size_t i ) const ;
	std::vector<std::string> getAll ( void ) ;
};
#endif//__TOKENIZER_HPP__
