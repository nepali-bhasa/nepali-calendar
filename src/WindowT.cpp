/**
 * transparent.cpp
 *
 */
#include "../include/WindowT.h"

WindowT::WindowT(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade) :
    Gtk::Window(cobject),
    m_builder(refGlade),
    m_box(NULL),
    m_labelDate(NULL),
    m_labelMonth(NULL),
    m_supportsAlpha(false)
{
    // Widgets
    m_builder->get_widget("box", m_box);
    m_builder->get_widget("date", m_labelDate);
    m_builder->get_widget("month", m_labelMonth);

    // Set up the top-level window.
    add_events(Gdk::BUTTON_PRESS_MASK);
    set_keep_below (true);
    set_app_paintable(true);
    stick();

    // Signal handlers
    signal_draw().connect(sigc::mem_fun(*this, &WindowT::on_draw));
    signal_screen_changed().connect(sigc::mem_fun(*this, &WindowT::on_screen_changed));
    signal_button_press_event().connect(sigc::mem_fun(*this, &WindowT::on_window_clicked));
    //_button.signal_clicked().connect(sigc::mem_fun(*this, &WindowT::on_button_clicked));


    // Get system date;
    time_t rawtime = time(NULL);
    struct tm * timeinfo = localtime(&rawtime);

    // Create an Ad object using system date and Bs object from Ad
    Ad ad(timeinfo->tm_year + 1900, timeinfo->tm_mon + 1, timeinfo->tm_mday);
    Bs bs(ad);

    // Modifiy content
    m_labelDate->set_text(anka(bs.day(),UNI));
    m_labelMonth->set_text(anka(bs.year(),UNI)+" "+mahina(bs.month(),UNI));

    // Move to bottom right of the screen
    move_to_bottomright(30);
    // Check for screen check
    on_screen_changed(get_screen());
    // Show the window and all its children.
    show_all();
}

WindowT::~WindowT() {
}

void WindowT::move_to_bottomright(gint padding) {
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


/**
 * Checks to see if the display supports alpha channels
 */
void WindowT::on_screen_changed(const Glib::RefPtr<Gdk::Screen>& previous_screen) {
    auto screen = get_screen();
    auto visual = screen->get_rgba_visual();
    if (visual)
        m_supportsAlpha = TRUE;
    // BugProbable: visual is 0
    gtk_widget_set_visual(GTK_WIDGET(gobj()), visual->gobj());
}

/**
 * Sets the transparency if supported
 */
bool WindowT::on_draw(const Cairo::RefPtr<Cairo::Context>& cr) {
    cr->save();
    if (m_supportsAlpha)
        cr->set_source_rgba(0.0, 0.0, 0.0, 0.2);    // transparent
    else
        cr->set_source_rgb(0.5, 1.0, 0.3);          // opaque
    cr->set_operator(Cairo::OPERATOR_SOURCE);
    cr->paint();
    cr->restore();

    return Gtk::Window::on_draw(cr);
}

bool WindowT::on_window_clicked(GdkEventButton* event) {
    std::cout << "The window was pressed." << std::endl;
    return false;
}

/*
void WindowT::on_button_clicked() {
    std::cout << "The button was pressed." << std::endl;
}
*/
