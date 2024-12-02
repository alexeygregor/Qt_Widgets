#include <QApplication>
#include <QPixmap>
#include <QPainter>
#include <QSlider>
#include <QPaintEvent>
#include <QWidget>

class ColorfulCircle : public QWidget
{
    Q_OBJECT
public:
    ColorfulCircle() = default;
    ColorfulCircle(QWidget *parent);
    void paintEvent(QPaintEvent *e) override;
    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

public slots:
    void setGreen();
    void setYellow();
    void setRed();

private:
    QPixmap mCurrentCircle;
    QPixmap mGreenCircle;
    QPixmap mYellowCircle;
    QPixmap mRedCircle;
};

ColorfulCircle::ColorfulCircle(QWidget *parent)
{
    setParent(parent);
    setToolTip("GreenCircle");
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    mGreenCircle = QPixmap("C://ColorfulCircle//GreenCircle.png");
    mYellowCircle = QPixmap("C://ColorfulCircle//YellowCircle.png");
    mRedCircle = QPixmap("C://ColorfulCircle//RedCircle.png");
    mCurrentCircle = mGreenCircle;
    setGeometry(mCurrentCircle.rect());
}

void ColorfulCircle::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.drawPixmap(e->rect(), mCurrentCircle);
}

QSize ColorfulCircle::sizeHint() const
{
    return QSize(100, 100);
}

QSize ColorfulCircle::minimumSizeHint() const
{
    return sizeHint();
}

void ColorfulCircle::setGreen()
{
    setToolTip("GreenCircle");
    mCurrentCircle = mGreenCircle;
    update();
}

void ColorfulCircle::setYellow()
{
    setToolTip("YellowCircle");
    mCurrentCircle = mYellowCircle;
    update();
}

void ColorfulCircle::setRed()
{
    setToolTip("RedCirle");
    mCurrentCircle = mRedCircle;
    update();
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QWidget *window = new QWidget;

    ColorfulCircle circle(window);
    circle.setFixedSize(150, 150);

    auto *slider = new QSlider(Qt::Horizontal, window);
    slider->setMinimum(0);
    slider->setMaximum(100);
    slider->move(30, 150);

    QObject::connect(slider, &QSlider::valueChanged, [&slider, &circle](int newValue)
    {
        if(newValue < 33)
            circle.setGreen();
        else if(newValue > 33 && newValue < 66)
            circle.setYellow();
        else if(newValue > 65)
            circle.setRed();
    });

    window->show();
    return a.exec();
}

#include <main.moc>
