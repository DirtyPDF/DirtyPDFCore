/**
 * @file page.hpp
 * @brief Header file for the class Page
 */

#ifndef _DPDFC_PAGE_H_
#define _DPDFC_PAGE_H_

#include <poppler-qt5.h>



namespace DirtyPDFCore{
  /**
   * @brief A renaming for Poppler::Page class in order to ease a redefinition
   * in a future.
   */
  typedef Poppler::Page Page;
}

#endif
