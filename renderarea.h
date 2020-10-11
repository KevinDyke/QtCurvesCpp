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

    enum ShapeType { Astroid, Cycloid, HuygensCycloid, HypoCycloid, FutureCurve };

    void setBackgroundColor(QColor color) { mBackgroundColor = color;}
    QColor backgroundColor() const {return mBackgroundColor;}

    void setShape(ShapeType shape) { mShape = shape; on_shape_changed(); }
    ShapeType shape() const { return mShape; }

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    void on_shape_changed();
    QColor mBackgroundColor;
    QColor mShapeColor;
    ShapeType mShape;

    float m_IntervalLength;
    float m_Scale;
    int m_StepCount;

    QPointF compute(float t); // dispatch function based on shape type
    QPointF compute_astroid(float t);
    QPointF compute_cycloid(float t);
    QPointF compute_huygens(float t);
    QPointF compute_hypo(float t);
    QPointF compute_future_curve(float t);

signals:

};

#endif // RENDERAREA_H
