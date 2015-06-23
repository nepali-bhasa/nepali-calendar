/**
 * main.cpp
 *
 */
#include <gtkmm.h>
#include "WindowTransparent.h"

int main (int argc, char *argv[]) {
    Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "nepali.calendar");
    WindowTransparent transparent;
    return app->run(transparent);
}
