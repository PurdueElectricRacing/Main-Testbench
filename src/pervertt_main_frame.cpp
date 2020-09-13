#include "pervertt_main_frame.h"
#include "ui_pervertt_main_frame.h"

PERVERTT_MAIN_FRAME::PERVERTT_MAIN_FRAME(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::PERVERTT_MAIN_FRAME)
{
    ui->setupUi(this);
}

PERVERTT_MAIN_FRAME::~PERVERTT_MAIN_FRAME()
{
    delete ui;
}

