/**
 * transparent.cpp
 *
 */
#include "nepalical/WindowT.h"

/**
 * Constructor
 */
WindowT::WindowT(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade) :
    Gtk::Window(cobject),
    m_builder(refGlade),
    m_compact(NULL),
    m_complete(NULL),
    m_supportsAlpha(false),
    m_completeShow(false)
{

    // Widgets
    m_builder->get_widget("compact", m_compact);
    m_builder->get_widget("complete", m_complete);
    m_complete->hide();

    // Set up the top-level window.
    add_events(Gdk::BUTTON_PRESS_MASK);
    set_keep_below (true);
    set_app_paintable(true);
    stick();

    // Signal handlers
    //_button.signal_clicked().connect(sigc::mem_fun(*this, &WindowT::on_button_clicked));
    signal_draw().connect(sigc::mem_fun(*this, &WindowT::on_draw));
    signal_screen_changed().connect(sigc::mem_fun(*this, &WindowT::on_screen_changed));
    signal_button_press_event().connect(sigc::mem_fun(*this, &WindowT::on_window_clicked));
    Glib::signal_timeout().connect(mem_fun(*this, &WindowT::updateToday), 60*1000); // A minute

    // Modify
    updateToday();

    // Move to bottom right of the screen
    move_to_bottomright(30);
    // Check for screen check
    on_screen_changed(get_screen());

    // Show the window and all its children.
    //show_all();
}

/**
 * Destructor
 */
WindowT::~WindowT() {
}


/**
 * Updates the labels with current Bs date
 */
bool WindowT::updateToday() {
    Bs bs;
    Ad ad = bs.firstday();

    // Compact
    Gtk::Label* m_labelDate = NULL;
    Gtk::Label* m_labelMix = NULL;
    m_builder->get_widget("compact.date", m_labelDate);
    m_builder->get_widget("compact.month", m_labelMix);
    m_labelDate->set_text(anka(bs.day(),UNI));
    m_labelMix->set_text(anka(bs.year(),UNI)+" "+mahina(bs.month(),UNI));

    // Complete
    Gtk::Label* m_labelYear = NULL;
    Gtk::Label* m_labelMonth = NULL;
    m_builder->get_widget("complete.year", m_labelYear);
    m_builder->get_widget("complete.month", m_labelMonth);
    m_labelYear->set_text(anka(bs.year(),UNI));
    m_labelMonth->set_text(mahina(bs.month(),UNI));

    Gtk::Label* m_labelNep= NULL;

    // get week of first date (intial offset)
    int j=ad.week()-1;

    // Clear all the pre-boxes
    for(int i=1;i<=j;i++){
        m_builder->get_widget("complete.nep"+std::to_string(i), m_labelNep);
        m_labelNep->set_text("");
    }

    // Fill the required boxes
    for(int i=0, k=ad.day(); i<bs.daysInMonth(); i++, k++){
        m_builder->get_widget("complete.nep"+std::to_string((j+i)%35+1), m_labelNep);

        // Make sure english day doesn't cross its month
        if(k>ad.daysInMonth())
            k = 1;
        // Get different color for today
        std::string color = (i+1)==bs.day()?"#fcfcafaf3e3e":"white";
        // Set the value for the box
        m_labelNep->set_markup(
                " <span font='14' fgcolor='"+color+"'><b>"+anka(i+1,Lipi::UNI)+" </b></span>"
                "<span font='8' fgcolor='"+color+"'><sub>"+std::to_string(k)+"</sub></span>"
                );
    }

    // Clear all the post-boxes
    for(int i=bs.daysInMonth()+j+1;i<=35;i++){
        m_builder->get_widget("complete.nep"+std::to_string(i), m_labelNep);
        m_labelNep->set_text("");
    }

    return true;
}

/**
 * Moves the window to bottom right with certain padding
 */
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
    if (m_completeShow){
        m_complete->hide();
        m_compact->show();
        m_completeShow = false;
    } else {
        m_compact->hide();
        m_complete->show();
        m_completeShow = true;
    }
    return false;
}

/*
void WindowT::on_button_clicked() {
    std::cout << "The button was pressed." << std::endl;
}
*/

