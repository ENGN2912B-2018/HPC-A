#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QtWidgets>
#include<QApplication>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

        QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
        QToolBar *fileToolBar = addToolBar(tr("File"));
        const QIcon newIcon = QIcon::fromTheme("document-save", QIcon(":/images/save.png"));
        QAction *newAct = new QAction(newIcon, tr("&Save"), this);
        newAct->setShortcuts(QKeySequence::New);
        newAct->setStatusTip(tr("Save a file"));
        //connect(newAct, &QAction::triggered, this, &MainWindow::newFile);
        fileMenu->addAction(newAct);
        fileToolBar->addAction(newAct);
        //QMainWindow *view=

}
/*void MainWindow::newFile()
//! [5] //! [6]
{
    if (maybeSave()) {
        textEdit->clear();
        setCurrentFile(QString());
    }
}*/

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_quit_clicked()
{
    QApplication::quit();
}

void MainWindow::on_start_clicked()
{
    ;
}


void MainWindow::on_open_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this);
    if (!fileName.isEmpty())
        loadFile(fileName);
}


void MainWindow::loadFile(const QString &fileName)
//! [42] //! [43]
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Application"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(QDir::toNativeSeparators(fileName), file.errorString()));
        return;
    }

    QTextStream in(&file);
/*#ifndef QT_NO_CURSOR
    QApplication::setOverrideCursor(Qt::WaitCursor);
#endif
    textEdit->setPlainText(in.readAll());
#ifndef QT_NO_CURSOR
    QApplication::restoreOverrideCursor();
#endif*/

    //setCurrentFile(fileName);
    statusBar()->showMessage(tr("File loaded"), 2000);
}
//! [43]

void MainWindow::on_view_rubberBandChanged(const QRect &viewportRect, const QPointF &fromScenePoint, const QPointF &toScenePoint)
{
    QMainWindow::resize(40,40);
}
