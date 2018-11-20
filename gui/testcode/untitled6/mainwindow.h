#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
class QPushButton;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void loadFile(const QString &fileName);
private slots:
    //void on_open_clicked();

    void on_start_clicked();

    void on_quit_clicked();

    void on_open_clicked();

    void on_view_rubberBandChanged(const QRect &viewportRect, const QPointF &fromScenePoint, const QPointF &toScenePoint);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
