/**
 * main.cpp
 *
 */
#include <gtkmm.h>
#include "nepalical/WindowT.h"

int main (int argc, char *argv[]) {
    Glib::RefPtr<Gtk::Application> app =
        Gtk::Application::create(argc, argv, "nepali.calendar");

    Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create();
    try {
        builder->add_from_file("/usr/share/nepalical/nepalical.glade");
    } catch(const Glib::FileError& ex) {
        std::cerr << "FileError: " << ex.what() << std::endl;
        return 1;
    } catch(const Glib::MarkupError& ex) {
        std::cerr << "MarkupError: " << ex.what() << std::endl;
        return 1;
    } catch(const Gtk::BuilderError& ex) {
        std::cerr << "BuilderError: " << ex.what() << std::endl;
        return 1;
    }

    //Get the GtkBuilder-instantiated dialog::
    WindowT* pWindow= 0;
    builder->get_widget_derived("win", pWindow);
    if(pWindow)
        app->run(*pWindow);
    delete pWindow;

    return 0;
}

