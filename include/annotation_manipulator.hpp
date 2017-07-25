/**
 * @file annotation_manipulator.hpp
 * @brief Header file for the class AnnotationManipulator
 */

#ifndef _DPDFC_ANNOTATION_MANIPULATOR_H_
#define _DPDFC_ANNOTATION_MANIPULATOR_H_

#include <QGraphicsRotation>
#include <QGraphicsScale>
#include <QPointF>
#include <QVector2D>
#include <poppler-qt5.h>
#include "distances.hpp"



namespace DirtyPDFCore{

  /**
   * @brief Common interface for all AnnotationManipulators.
   */
  class AnnotationManipulator{
  public:

    /**
     * @brief Applies the transformation stored in the QTransform object to the annotation.
     */
    virtual void applyTransform(const QTransform& transform) = 0;

    /**
     * @brief Applies the transformation only in a part of the annotation.
     * @param transform QTransform object which stores the transformation.
     * @param point Indicates what section transform.
     * @param radius Defines an imaginary circumference, with point as center, which
     * indicates the sections to transfom.
     */
    virtual void applyTransformPart(const QTransform& transform, const QPointF& point, double radius=0) = 0;

    /**
     * @brief Completely erases the annotation visible representation (the object is not deleted).
     */
    virtual void erase() = 0;

    /**
     * @brief Erases only a part of the annotation. The part to be erased may vary depending
     * on the annotation subclass with which the AnnotationManipulator is working.
     * @param point Indicates what section erase.
     * @param radius Indicates how large the deletion must be.
     */
    virtual void erasePart(const QPointF &point, double radius) = 0;

    /**
     * @brief Moves the annotaion.
     * @param vector Vector to apply in the annotation in order to move it.
     */
    virtual void move(const QVector2D &vector) = 0;

    /**
     * @brief Moves only a part of the annotation. The part to be moved may vary dependiong
     * on the annotation subclass with which the AnnotationManipulator is working.
     * @param vector Vector to apply in the annotation section.
     * @param point Indicates what section move.
     */
    virtual void movePart(const QVector2D &vector, const QPointF &point) = 0;

    /**
     * @brief Rotates the annotation.
     * @param angle Angle of the rotation.
     * @param center Rotation center.
     */
    virtual void rotate(double angle, const QPointF &center) = 0;

    /**
     * @brief Rotates only a part of the annotation. The part to be rotated may vary dependiong
     * on the annotation subclass with which the AnnotationManipulator is working.
     * @param angle Angle of the rotation.
     * @param center Rotation center.
     * @param point Indicates which section rotate.
     */
    virtual void rotatePart(double angle, const QPointF &center, const QPointF &point) = 0;

    /**
     * @brief Scales the annotation.
     * @param x Scale factor in the x axe.
     * @param y Scale factor in the y axe.
     */
    virtual void scale(double x, double y) = 0;

    /**
     * @brief Scales only a part of the annotation. The part to be scaled may vary dependiong
     * on the annotation subclass with which the AnnotationManipulator is working.
     * @param x Scale factor in the x axe.
     * @param y Scale factor in the y axe.
     * @param point Indicates what section scale.
     */
    virtual void scalePart(double x, double y, const QPointF &point) = 0;
  };
}


#include "ink_annotation_manipulator.hpp"
#endif
