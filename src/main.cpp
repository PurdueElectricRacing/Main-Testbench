#include "pervertt_main_frame.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PERVERTT_MAIN_FRAME w;
    w.show();
    return a.exec();
}
