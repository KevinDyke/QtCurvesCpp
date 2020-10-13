#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QWidget>
#include <QColor>

class RenderArea : public QWidget
{
    Q_OBJECT
public:
    explicit RenderArea(QWidget *parent = nullptr);

    QSize minimumSizeHint() const Q_DECL_OVERRIDE;
    QSize sizeHint() const Q_DECL_OVERRIDE;

    enum ShapeType { Astroid, Cycloid, HuygensCycloid, HypoCycloid, Line };

    void setBackgroundColor(QColor color) { m_BackgroundColor = color;}
    QColor backgroundColor() const {return m_BackgroundColor;}

    void setShapeColour(QColor colour) { m_ShapeColour = colour;}
    QColor shapeColour() const { return m_ShapeColour;}

    void setShape(ShapeType shape) { m_Shape = shape; on_shape_changed(); }
    ShapeType shape() const { return m_Shape; }

    void setScale (float scale) { m_Scale = scale; repaint();}
    float scale() const { return m_Scale;}

    void setInterval(float interval) { m_IntervalLength = interval; repaint();}
    float Interval() const { return m_IntervalLength;}

    void setStepCount(int count) { m_StepCount = count; repaint();}
    int stepCount() const { return m_StepCount;}

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    void on_shape_changed();
    QColor m_BackgroundColor;
    QColor m_ShapeColour;
    ShapeType m_Shape;

    float m_IntervalLength;
    float m_Scale;
    int m_StepCount;

    QPointF compute(float t); // dispatch function based on shape type
    QPointF compute_astroid(float t);
    QPointF compute_cycloid(float t);
    QPointF compute_huygens(float t);
    QPointF compute_hypo(float t);
    QPointF compute_line(float t);

signals:

};

#endif // RENDERAREA_H
