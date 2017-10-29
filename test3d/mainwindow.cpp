#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow( QWidget *parent ) :
    QMainWindow( parent ),
    ui( new Ui::MainWindow ) {
    ui->setupUi( this );
    myWidget = new M3DWidget( "qrc:/models/models/bike.obj", 0, this );
    setCentralWidget( myWidget );
}

MainWindow::~MainWindow() {
    delete ui;
}
