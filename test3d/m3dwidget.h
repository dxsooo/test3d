#ifndef M3DWIDGET_H
#define M3DWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QSlider>

#include <Qt3DExtras/Qt3DWindow>
#include <Qt3DCore/QTransform>

class M3DWidget : public QWidget {
    Q_OBJECT
  public:
    explicit M3DWidget( const QString &, int, QWidget *parent = nullptr );

  public:
    void setXValue( int );
    int getXValue();

  private slots:
    void xslider_change( int );

  private:
    Qt3DExtras::Qt3DWindow *view;
    Qt3DRender::QCamera *basicCamera;
    Qt3DCore::QTransform *bikeTransform;
    Qt3DCore::QEntity *rootEntity;
//    QWidget *container;
    QLabel *xdata;
    QSlider *xslider;

    QString model;
    int mode;
};

#endif // M3DWIDGET_H
