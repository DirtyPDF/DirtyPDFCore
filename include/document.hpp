/**
 * @file document.hpp
 * @brief Header file for the class Document
 */

#ifndef _DPDFC_DOCUMENT_H_
#define _DPDFC_DOCUMENT_H_

#include <poppler-qt5.h>



namespace DirtyPDFCore{
  /**
   * @brief A renaming for Poppler::Document class in order to ease a redefinition
   * in a future.
   */
  typedef Poppler::Document Document;

  /**
   * @brief Type to identify documents.
   */
  typedef unsigned int DocumentId;

  /**
   * @brief Representation of an invalid document via its id.
   */
  const DocumentId INVALID_DOCUMENT_ID = 0;
}

#endif
