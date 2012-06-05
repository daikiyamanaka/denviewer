#ifndef RENDERINGCOLOR_HPP
#define RENDERINGCOLOR_HPP

#include "Model.hpp"
#include <QLabel>
#include <QLineEdit>
#include <QLayout>

class RenderingColor
{
private:
        Model _model;

public:
        RenderingColor(Model& model);
};

#endif // RENDERINGCOLOR_HPP
