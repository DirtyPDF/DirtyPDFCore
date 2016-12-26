/**
 * @file colors_manager.hpp
 * @brief Header file for the class ColorsManager
 */

#ifndef _DPDFC_COLORS_MANAGER_H_
#define _DPDFC_COLORS_MANAGER_H_

#include <QObject>
#include <QColor>
#include <QVector>



namespace DirtyPDFCore{

  /**
   * @brief Singleton class which knowns what color is selected in each moment.
   */
  class ColorsManager : public QObject{
    Q_OBJECT

  private:
    static ColorsManager* m_instance; ///< Singleton instance
    QColor m_color; ///< Color currently selected

  protected:
    ColorsManager(QObject* parent=Q_NULLPTR);
    ColorsManager(const ColorsManager&);
    void operator=(const ColorsManager&);

  public:
    
    static ColorsManager* Instance();

    /**
     * @brief Returns the currently selected color.
     */
    const QColor& getCurrentColor() const;

  public slots:

    /**
     * @brief Sets the currently selected color in the system.
     * @param color QColor to set as the current color.
     */
    void setCurrentColor(const QColor &color);

  signals:

  /**
   * @brief Signal emmited when the current color changes.
   * @param oldColor The previous selected color.
   */
    void currentColorChanged(QColor oldColor);
  };
}
#endif
