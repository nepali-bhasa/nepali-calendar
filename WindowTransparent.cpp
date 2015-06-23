/**
 * transparent.cpp
 *
 */
#include "WindowTransparent.h"

WindowTransparent::WindowTransparent()
//    _button("Change")
{

    // Set up the top-level window.
    set_type_hint (Gdk::WINDOW_TYPE_HINT_DOCK);
    set_title("nepali.calendar");
    set_decorated(false);
    set_keep_below (true);
    set_position(Gtk::WIN_POS_CENTER);
    set_app_paintable(true);
    stick();
    // set_default_size(100,100);

    add_events(Gdk::BUTTON_PRESS_MASK);

    // Signal handlers
    signal_draw().connect(sigc::mem_fun(*this, &WindowTransparent::on_draw));
    signal_screen_changed().connect(sigc::mem_fun(*this, &WindowTransparent::on_screen_changed));
    signal_button_press_event().connect(sigc::mem_fun(*this, &WindowTransparent::on_window_clicked));
//    _button.signal_clicked().connect(sigc::mem_fun(*this, &WindowTransparent::on_button_clicked));

    // Widgets

    Glib::RefPtr<Gtk::Builder> refBuilder = Gtk::Builder::create();
    refBuilder->add_from_file("calendar.glade");
    Gtk::Box* box= NULL;
    refBuilder->get_widget("box1", box);


    on_screen_changed(get_screen());
    add(*box);
    //add(_button);

    // Show the window and all its children.
    show_all();

}

WindowTransparent::~WindowTransparent()
{
}


/**
 * Checks to see if the display supports alpha channels
 */
void WindowTransparent::on_screen_changed(const Glib::RefPtr<Gdk::Screen>& previous_screen) {
    auto screen = get_screen();
    auto visual = screen->get_rgba_visual();
    if (visual) 
        _SUPPORTS_ALPHA = TRUE;
    gtk_widget_set_visual(GTK_WIDGET(gobj()), visual->gobj());
}


bool WindowTransparent::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
    cr->save();
    if (_SUPPORTS_ALPHA) {
        cr->set_source_rgba(0.0, 0.0, 0.0, 0.2);    // transparent
    } else {
        cr->set_source_rgb(0.5, 1.0, 0.5);          // opaque
    }
    cr->set_operator(Cairo::OPERATOR_SOURCE);
    cr->paint();
    cr->restore();

    return Gtk::Window::on_draw(cr);
}

bool WindowTransparent::on_window_clicked(GdkEventButton* event) {
    std::cout << "The window was pressed." << std::endl;
    return false;
}

/*
void WindowTransparent::on_button_clicked()
{
    std::cout << "The button was pressed." << std::endl;
}
*/
