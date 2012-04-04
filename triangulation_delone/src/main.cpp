#include <QApplication>
#include <cstdio> //del
#include "window/window.h"

int main(int argc, char *argv[]) {
	QApplication app(argc, argv);
  	triangle_delone_window window;
	visualization::run_viewer(&window, "Triangulation Delone");
}
  
