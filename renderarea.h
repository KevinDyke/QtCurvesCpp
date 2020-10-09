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

    enum ShapeType { Astroid, Cycloid, HuygensCycloid, HypoCycloid };

    void setBackgroundColor(QColor color) { mBackgroundColor = color;}
    QColor backgroundColor() const {return mBackgroundColor;}

    void setShape(ShapeType shape) { mShape = shape;}
    ShapeType shape() const { return mShape; }

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QColor mBackgroundColor;
    QColor mShapeColor;
    ShapeType mShape;
signals:

};

#endif // RENDERAREA_H
