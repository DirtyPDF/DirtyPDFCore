#include "pen_tool.hpp"
using namespace DirtyPDFCore;



PenTool::PenTool(){}


void PenTool::initialize(const QColor &color, double width, bool beautifySelected){
  m_color = color;
  m_width = width;
  m_beautifySelected = beautifySelected;
}
