/**
 * @file ink_annotation_manipulator.hpp
 * @brief Header file for the class InkAnnotationManipulator
 */

#ifndef _DPDFC_INK_ANNOTATION_MANIPULATOR_H_
#define _DPDFC_INK_ANNOTATION_MANIPULATOR_H_

#include <QPointF>
#include <QVector2D>
#include <poppler-qt5.h>
#include "annotation_manipulator.hpp"


namespace DirtyPDFCore{

  /**
   * @brief Common function to construct any AnnotationManipulator. This implementation
   * returns an InkAnnotationManipulator bound to an InkAnnotation.
   */
  AnnotationManipulator* createAnnotationManipulator(Poppler::InkAnnotation* annotation);

  /**
   * @brief AnnotationManipulator implementation for InkAnnotation
   */
  class InkAnnotationManipulator : public AnnotationManipulator{

  private:
    Poppler::InkAnnotation* m_annotation; ///< Annotation to manipulate

    /**
     * @brief Returns the strokes which have some of them points inside the
     * circumference with point as center and radius as radius.
     * @param point Center of the circumference.
     * @param radius Radiud of the circumference.
     * @returns A QList<int> with the indexes of the strokes in the annotation.
     * (The indexes of the QList<QLinkedList<QPointF> >).
     */
    QList<int> getSections(const QPointF& point, double radius=0);


  public:

    /**
     * @brief Creates an InkAnnotationManipulator attached to an InkAnnotation.
     * Every operation done by the manipulator will change the annotation.
     */
    InkAnnotationManipulator(Poppler::InkAnnotation* annotation);

    /**
     * @brief Applies the transformation stored in the QTransform object to the annotation.
     */
    void applyTransform(const QTransform& transform);

    /**
     * @brief Applies the transformation only in a storke of the annotation.
     * @param transform QTransform object which stores the transformation.
     * @param point Indicates what stroke transform.
     * @param radius Defines an imaginary circumference, with point as center, which
     * indicates the sections to transfom. If a stroke has some point inside the circumference
     * it will be transformated.
     */
    void applyTransformPart(const QTransform& transform, const QPointF& point, double radius=0);

    /**
     * @brief Completely erases the annotation visible representation (the object is not deleted).
     */
    void erase();

    /**
     * @brief Erases only some strokes of the annotation.
     * @param point Indicates what section erase.
     * @param radius Indicates how large the deletion must be.
     * Every stroke with points inside the circumference with center point
     * and radius radius will be erased.
     */
    void erasePart(const QPointF &point, double radius);

    /**
     * @brief Moves the annotaion.
     * @param vector Vector to apply in the annotation in order to move it.
     */
    void move(const QVector2D &vector);

    /**
     * @brief Moves the stroke that owns point .
     * @param vector Vector to apply in the annotation section.
     * @param point Indicates what stroke move.
     */
    void movePart(const QVector2D &vector, const QPointF &point);

    /**
     * @brief Rotates the annotation.
     * @param angle Angle of the rotation.
     * @param center Rotation center.
     */
    void rotate(double angle, const QPointF &center);

    /**
     * @brief Rotates the stroke that owns point.
     * @param angle Angle of the rotation.
     * @param center Rotation center.
     * @param point Indicates what section rotate.
     */
    void rotatePart(double angle, const QPointF &center, const QPointF &point);

    /**
     * @brief Scales the annotation.
     * @param x Scale factor in the x axe.
     * @param y Scale factor in the y axe.
     */
    void scale(double x, double y);

    /**
     * @brief Rotates the stroke that owns point.
     * @param x Scale factor in the x axe.
     * @param y Scale factor in the y axe.
     * @param point Indicates what section scale.
     */
    void scalePart(double x, double y, const QPointF &point);
  };
}
#endif
