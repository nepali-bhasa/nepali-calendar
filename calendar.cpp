/**
 * main.cpp
 *
 */
#include <gtkmm.h>
#include "WindowT.h"

int main (int argc, char *argv[]) {
    Glib::RefPtr<Gtk::Application> app =
        Gtk::Application::create(argc, argv, "nepali.calendar");
    WindowT win;
    return app->run(win);
}
