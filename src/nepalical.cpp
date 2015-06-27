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


    // calendar
    Bs bs;
    Ad ad = bs.firstday();

    std::cout << bs.year() << " " << mahina(bs.month(),Lipi::ENG) << std::endl;
    for(int i=1;i<=7;i++)
        std::cout << bar(i,Lipi::ENG)<<"\t";
    std::cout << std::endl;

    int j = 0;
    while(j++<ad.week()-1)
        std::cout << "\t";

    for(int i=1; i<= bs.daysInMonth(); i++) {
        std::cout << i << (bs.day()==i?"*":"");
        j = (j-1 +1)%7+1;
        std::cout << (j==1?"\n":"\t");
    }
    std::cout << std::endl;




    //Get the GtkBuilder-instantiated dialog::
    WindowT* pWindow= 0;
    builder->get_widget_derived("win", pWindow);
    if(pWindow)
        app->run(*pWindow);
    delete pWindow;

    return 0;
}
