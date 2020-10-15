#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QWidget>
#include <QColor>
#include <QPen>

class RenderArea : public QWidget
{
    Q_OBJECT
public:
    explicit RenderArea(QWidget *parent = nullptr);

    QSize minimumSizeHint() const Q_DECL_OVERRIDE;
    QSize sizeHint() const Q_DECL_OVERRIDE;

    enum ShapeType { Astroid,
                     Cycloid,
                     HuygensCycloid,
                     HypoCycloid,
                     Line,
                     Circle,
                     Ellipse,
                     Fancy,
                     Starfish,
                     Cloud_1,
                     Cloud_2
    };

    void setBackgroundColor(QColor color) { m_BackgroundColor = color;}
    QColor backgroundColor() const {return m_BackgroundColor;}

    void setShapeColour(QColor colour) { m_Pen.setColor(colour);}
    QColor shapeColour() const { return m_Pen.color();}

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
    QPen m_Pen;
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
    QPointF compute_circle(float t);
    QPointF compute_ellipse(float t);
    QPointF compute_fancy(float t);
    QPointF compute_starfish(float t);
    QPointF compute_cloud_one(float t);
    QPointF compute_cloud_two(float t);
    QPointF compute_cloud_with_sign(float t, float sign);

signals:

};

#endif // RENDERAREA_H
