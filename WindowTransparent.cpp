/**
 * transparent.cpp
 *
 */
#include "WindowTransparent.h"

void WindowTransparent::move_to_bottomright(gint padding) {
    // Set reference to bottom right
    set_gravity(Gdk::GRAVITY_SOUTH_EAST);

    // get size of the window
    gint width=0, height=0;
    get_size(width,height);

    // get screen
    Glib::RefPtr<Gdk::Screen> screen = get_screen();

    // move to bottom right
    move(screen->get_width()-width-padding, screen->get_height()-height-padding);
}

WindowTransparent::WindowTransparent()
//: _button("Change")
{

    // Set up the top-level window.
    set_type_hint (Gdk::WINDOW_TYPE_HINT_DOCK);
    // set_default_size(90,120);
    set_title("nepali.calendar");
    set_decorated(false);
    set_keep_below (true);
    set_app_paintable(true);
    stick();
    add_events(Gdk::BUTTON_PRESS_MASK);

    // Signal handlers
    signal_draw().connect(sigc::mem_fun(*this, &WindowTransparent::on_draw));
    signal_screen_changed().connect(sigc::mem_fun(*this, &WindowTransparent::on_screen_changed));
    signal_button_press_event().connect(sigc::mem_fun(*this, &WindowTransparent::on_window_clicked));
    //_button.signal_clicked().connect(sigc::mem_fun(*this, &WindowTransparent::on_button_clicked));

    // Widgets

    // Check for screen check
    on_screen_changed(get_screen());

    // Add elements to windows

    // Get the box from glade file
    Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create();
    builder->add_from_file("calendar.glade");

    Gtk::Box* box= NULL;
    Gtk::Label* pLabelDate = 0;
    Gtk::Label* pLabelMonth= 0;

    builder->get_widget("textbox", box);
    builder->get_widget("date", pLabelDate);
    pLabelDate->set_text("10");
    builder->get_widget("month", pLabelMonth);
    pLabelMonth->set_text("2012 Jan");

    // Add widgets
    // add(_button);
    add(*box);

    // Move to bottom right of the screen
    move_to_bottomright(30);
    // Show the window and all its children.
    show_all();
}

WindowTransparent::~WindowTransparent() {
}


/**
 * Checks to see if the display supports alpha channels
 */
void WindowTransparent::on_screen_changed(const Glib::RefPtr<Gdk::Screen>& previous_screen) {
    auto visual = previous_screen->get_rgba_visual();
    if (visual)
        _SUPPORTS_ALPHA = TRUE;
    // BugProbable: visual is 0
    gtk_widget_set_visual(GTK_WIDGET(gobj()), visual->gobj());
}

/**
 * Sets the transparency if supported
 */
bool WindowTransparent::on_draw(const Cairo::RefPtr<Cairo::Context>& cr) {
    cr->save();
    if (_SUPPORTS_ALPHA)
        cr->set_source_rgba(0.0, 0.0, 0.0, 0.2);    // transparent
    else
        cr->set_source_rgb(0.5, 1.0, 0.3);          // opaque
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
