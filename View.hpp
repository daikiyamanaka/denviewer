#ifndef __VIEW_HPP__
#define __VIEW_HPP__ 1
#include "Model.hpp"
class View
{
private:
        Model& _model;
public:
        View ( Model& model );
        virtual ~View ( void );
        void init ( void );
        void render ( void );
        void resize ( const int width, const int height );
        //
        void onLight( const unsigned int number);
        void offLight( const unsigned int number);
private:
        void render_mesh ( void );
        void setLight ( const Light& light , const unsigned int number, const Eigen::Vector3f eye);
};
#endif // __VIEW_HPP__
