#include "shape_tool.hpp"
using namespace DirtyPDFCore;



ShapeTool::ShapeTool(){}


void ShapeTool::initialize(const QColor &color, double width){
  m_color = color;
  m_width = width;
}
