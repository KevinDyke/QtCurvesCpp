#include "renderarea.h"
#include <QPaintEvent>
#include <QPainter>
#include <QtMath>

RenderArea::RenderArea(QWidget *parent) : QWidget(parent),
    mBackgroundColor(QColor(0 ,0 ,255)),
    mShapeColor(255, 255, 255),
    mShape(Astroid)
{
    on_shape_changed();
}

QSize RenderArea::minimumSizeHint() const
{
    return QSize(100,100);
}

QSize RenderArea::sizeHint() const
{
    return QSize(100,100);
}

QPointF RenderArea::compute_astroid(float t)
{
    float cos_t = cos(t);
    float sin_t = sin(t);

    float x = 2 * cos_t * cos_t * cos_t; // pow(cos_t,3)
    float y = 2 * sin_t * sin_t * sin_t; // pow(sin_t,3)
    return QPointF(x,y);
}

void RenderArea::on_shape_changed()
{
    switch(mShape) {
        case Astroid:
            m_Scale = 40;
            m_IntervalLength = 2 * M_PI;
            m_StepCount = 256;
            break;

        case Cycloid:
            m_Scale = 4;
            m_IntervalLength = 4 * M_PI;
            m_StepCount = 256;
            break;

        case HuygensCycloid:
            m_Scale = 4;
            m_IntervalLength = 6 * M_PI;
            m_StepCount = 128;
            break;

        case HypoCycloid:
            m_Scale = 15;
            m_IntervalLength = 2 * M_PI;
            m_StepCount = 256;

            break;

        case FutureCurve:
            break;

        default:
            break;
    }
}

QPointF RenderArea::compute(float t)
{
    switch(mShape) {
        case Astroid:
            return compute_astroid(t);
            break;

        case Cycloid:
            return compute_cycloid(t);
            break;

        case HuygensCycloid:
            return compute_huygens(t);
            break;

        case HypoCycloid:
            return compute_hypo(t);
            break;

        case FutureCurve:
            return compute_future_curve(t);
            break;

        default:
            break;
    }
    return QPointF(0,0);
}

QPointF RenderArea::compute_cycloid(float t)
{
    return QPointF(
                1.5 * (1 - cos(t)), // X
                1.5 * (t - sin(t))  // Y
    );
}

QPointF RenderArea::compute_huygens(float t)
{
    return QPointF(
                4 * (3 * cos(t) - cos(3 * t)), // X
                4 * (3 * sin(t) - sin(3 * t))  // Y
    );
}

QPointF RenderArea::compute_hypo(float t)
{
    return QPointF(
                1.5 * (2 * cos(t) + cos(2 * t)), // X
                1.5 * (2 * sin(t) - sin(2 * t))  // Y
    );
}

QPointF RenderArea::compute_future_curve(float t)
{

}

void RenderArea::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);

    painter.setBrush(mBackgroundColor);
    painter.setPen(mShapeColor);

    // drawing area
    painter.drawRect(this->rect());

    QPoint center = this->rect().center();
    float step = m_IntervalLength / m_StepCount;
    for(float t = 0; t < m_IntervalLength; t += step){
        QPointF point = compute(t);
        QPoint pixel;
        pixel.setX(point.x() * m_Scale + center.x());
        pixel.setY(point.y() * m_Scale + center.y());

        painter.drawPoint(pixel);
    }
}

