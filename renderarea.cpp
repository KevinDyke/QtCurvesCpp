#include "renderarea.h"
#include <QPaintEvent>
#include <QPainter>
#include <QtMath>

RenderArea::RenderArea(QWidget *parent) : QWidget(parent),
    m_BackgroundColor(QColor(0 ,0 ,255)),
    m_Pen(Qt::white),
    m_Shape(Astroid)
{
    m_Pen.setWidth(2);
    on_shape_changed();
}

QSize RenderArea::minimumSizeHint() const
{
    return QSize(400,400);
}

QSize RenderArea::sizeHint() const
{
    return QSize(400,400);
}

void RenderArea::on_shape_changed()
{
    switch(m_Shape) {
        case Astroid:
            m_Scale = 90;
            m_IntervalLength = 2 * M_PI;
            m_StepCount = 256;
            break;

        case Cycloid:
            m_Scale = 10;
            m_IntervalLength = 4 * M_PI;
            m_StepCount = 256;
            break;

        case HuygensCycloid:
            m_Scale = 4;
            m_IntervalLength = 6 * M_PI;
            m_StepCount = 128;
            break;

        case HypoCycloid:
            m_Scale = 40;
            m_IntervalLength = 2 * M_PI;
            m_StepCount = 256;
            break;

        case Line:
            m_Scale = 100;
            m_IntervalLength = 2;
            m_StepCount = 128;
            break;

        case Circle:
            m_Scale = 165;
            m_IntervalLength = 2 * M_PI;
            m_StepCount = 128;
            break;

        case Ellipse:
            m_Scale = 75;
            m_IntervalLength = 2 * M_PI;
            m_StepCount = 256;
            break;

        case Fancy:
            m_Scale = 10;
            m_IntervalLength = 12 * M_PI;
            m_StepCount = 512;
            break;

        case Starfish:
            m_Scale = 25;
            m_IntervalLength = 6 * M_PI;
            m_StepCount = 256;
            break;

        case Cloud_1:
            m_Scale = 10;
            m_IntervalLength = 28 * M_PI;
            m_StepCount = 128;
            break;

        case Cloud_2:
            m_Scale = 10;
            m_IntervalLength = 28 * M_PI;
            m_StepCount = 128;
            break;

        default:
            break;
    }
}

QPointF RenderArea::compute(float t)
{
    switch(m_Shape) {
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

        case Line:
            return compute_line(t);
            break;

        case Circle:
            return compute_circle(t);
            break;

        case Ellipse:
            return compute_ellipse(t);

        case Fancy:
            return compute_fancy(t);

        case Starfish:
            return compute_starfish(t);

        case Cloud_1:
            return compute_cloud_one(t);

        case Cloud_2:
            return compute_cloud_two(t);

        default:
            break;
    }
    return QPointF(0,0);
}

QPointF RenderArea::compute_astroid(float t)
{
    float cos_t = cos(t);
    float sin_t = sin(t);

    float x = 2 * cos_t * cos_t * cos_t; // pow(cos_t,3)
    float y = 2 * sin_t * sin_t * sin_t; // pow(sin_t,3)
    return QPointF(x,y);
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

QPointF RenderArea::compute_line(float t)
{
    return QPointF(1 - t, 1 - t);
}

QPointF RenderArea::compute_circle(float t)
{
    return QPointF(
                cos(t), // X
                sin(t)  // Y
    );
}

QPointF RenderArea::compute_ellipse(float t)
{
    float a = 2.0f;
    float b = 1.1f;
    return QPointF(
                a * cos(t), // X
                b * sin(t)  // Y
    );
}

QPointF RenderArea::compute_fancy(float t)
{
    const float c1 = 11.0f;
    const float c2 =  6.0f;

    return QPointF(
                c1 * cos(t) - c2 * cos( c1 / c2 * t), // X
                c1 * sin(t) - c2 * sin( c1 / c2 * t)  // Y
    );
}

QPointF RenderArea::compute_starfish(float t)
{
    const float R = 5.0f;
    const float r = 3.0f;
    const float d = 5.0f;

    return QPointF(
                ( R - r) * cos(t) + d * cos(t * ( (R - r) / r) ), // X
                ( R - r) * sin(t) - d * sin(t * ( (R - r) / r) )  // Y
    );
}

QPointF RenderArea::compute_cloud_one(float t)
{
    return compute_cloud_with_sign(t, -1.0f);
}

QPointF RenderArea::compute_cloud_two(float t)
{
    return compute_cloud_with_sign(t, 1.0f);
}

QPointF RenderArea::compute_cloud_with_sign(float t, float sign)
{
    const float a = 14.0f;
    const float b =  1.0f;

    return QPointF(
                ( a + b) * cos( t * ( b / a )) + sign * b * cos( t * ( a + b) / a), // X
                ( a + b) * sin( t * ( b / a )) - b * sin( t * ( a + b) / a)  // Y
    );
}

void RenderArea::paintEvent(QPaintEvent *event)
{
    Q_UNUSED( event )

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);

    painter.setBrush(m_BackgroundColor);
    painter.setPen(m_Pen);

    // drawing area
    painter.drawRect(this->rect());

    QPoint center = this->rect().center();

    QPointF prevPoint = compute(0);
    QPoint prevPixel;
    prevPixel.setX(prevPoint.x() * m_Scale + center.x());
    prevPixel.setY(prevPoint.y() * m_Scale + center.y());

    float step = m_IntervalLength / m_StepCount;
    for(float t = 0; t < m_IntervalLength; t += step){
        QPointF point = compute(t);
        QPoint pixel;
        pixel.setX(point.x() * m_Scale + center.x());
        pixel.setY(point.y() * m_Scale + center.y());

        painter.drawLine(pixel, prevPixel);
        prevPixel = pixel;
    }

    QPointF point = compute(m_IntervalLength);
    QPoint pixel;
    pixel.setX(point.x() * m_Scale + center.x());
    pixel.setY(point.y() * m_Scale + center.y());

    painter.drawLine(pixel, prevPixel);
}

