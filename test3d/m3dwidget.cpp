#include "m3dwidget.h"

#include "qgridlayout.h"

#include "Qt3DExtras"
#include "Qt3DRender"

M3DWidget::M3DWidget( const QString &qrc_str, int m, QWidget *parent ) : QWidget( parent ) {
    model = qrc_str;
    mode = m;

    view = new Qt3DExtras::Qt3DWindow();
    QWidget *container = QWidget::createWindowContainer( view );
    xdata = new QLabel( this );
    QSize screenSize = view->screen()->size();
    container->setMinimumSize( QSize( 200, 100 ) );
    container->setMaximumSize( screenSize );

    rootEntity = new Qt3DCore::QEntity;

    Qt3DRender::QSceneLoader *scene = new Qt3DRender::QSceneLoader;
    scene->setSource( QUrl( qrc_str ) );
    while ( scene->status() == Qt3DRender::QSceneLoader::Loading );
    if ( scene->status() == Qt3DRender::QSceneLoader::Error )
        qDebug() << "load error";
    else {
        qDebug() << "load successful";
        qDebug() << scene->status();
        qDebug() << scene->source();
        qDebug() << scene->entityNames();
    }

    Qt3DRender::QMaterial *material = new Qt3DExtras::QPhongMaterial();
    //material->setSpecular(Qt::yellow );

    Qt3DCore::QEntity *bikeEntity = new Qt3DCore::QEntity( rootEntity );
    bikeEntity->addComponent( scene );
    bikeTransform = new Qt3DCore::QTransform;
    bikeTransform->setTranslation( QVector3D( 0, 0, -50 ) );
    bikeEntity->addComponent( bikeTransform );
    bikeEntity->addComponent( material );
    Qt3DRender::QSceneLoader *scene_axis = new Qt3DRender::QSceneLoader;
    scene_axis->setSource( QUrl( "qrc:/axis_obj/axis.obj" ) );
    while ( scene_axis->status() == Qt3DRender::QSceneLoader::Loading );

    Qt3DCore::QEntity *axisEntity = new Qt3DCore::QEntity( rootEntity );
    axisEntity->addComponent( scene_axis );
    axisEntity->addComponent( bikeTransform );


    basicCamera = view->camera();
//    basicCamera->setFieldOfView(10000);
    basicCamera->setFarPlane( 10000.0f );
//    basicCamera->setNearPlane(1000.0f);
    basicCamera->setProjectionType( Qt3DRender::QCameraLens::PerspectiveProjection );
    basicCamera->setViewCenter( QVector3D( 0.0f, 0, 0 ) );
    basicCamera->setPosition( QVector3D( 0, -300, 150 ) );
    basicCamera->setUpVector( QVector3D( 0, 0, 1 ) );



    Qt3DCore::QEntity *lightEntity = new Qt3DCore::QEntity( rootEntity );
    Qt3DRender::QPointLight *light = new Qt3DRender::QPointLight( lightEntity );
    Qt3DCore::QTransform *light_transform = new Qt3DCore::QTransform( lightEntity );
    light_transform->setTranslation( QVector3D( 0, 0, 200 ) );
    light->setColor( "white" );
    light->setIntensity( 2 );
    lightEntity->addComponent( light );
    lightEntity->addComponent( light_transform );


    QGridLayout *gridlayout = new QGridLayout( this );
    gridlayout->addWidget( container, 0, 0, 9, 9 );
    xslider = new QSlider( Qt::Horizontal, this );
//    connect( xslider, &QSlider::valueChanged, this, &M3dwidget::onHorizontalSlider );
    xslider->setRange( 1, 360 );
    xslider->setValue( 180 );

    gridlayout->addWidget( xslider, 9, 0, 1, 7 );
    gridlayout->addWidget( xdata, 9, 7, 1, 2 );

    setLayout( gridlayout );

    view->setRootEntity( rootEntity );
}

void M3DWidget::xslider_change( int a ) {
    xdata->setText( QString::number( a ) );
}

void M3DWidget::setXValue( int a ) {
    xslider->setValue( a );
}

int M3DWidget::getXValue() {
    return xslider->value();
}
