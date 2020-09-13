#ifndef PERVERTT_MAIN_FRAME_H
#define PERVERTT_MAIN_FRAME_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class PERVERTT_MAIN_FRAME; }
QT_END_NAMESPACE

class PERVERTT_MAIN_FRAME : public QMainWindow
{
    Q_OBJECT

public:
    PERVERTT_MAIN_FRAME(QWidget *parent = nullptr);
    ~PERVERTT_MAIN_FRAME();

private:
    Ui::PERVERTT_MAIN_FRAME *ui;
};
#endif // PERVERTT_MAIN_FRAME_H
