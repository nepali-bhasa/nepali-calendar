/**
 * transparent.h
 *
 */

#ifndef TRANSPARENT_H_
#define TRANSPARENT_H_

#include <iostream>

#include <gtk/gtk.h>
#include <gtkmm.h>
#include <gtkmm/window.h>
#include <gtkmm/button.h>
#include <gtkmm/alignment.h>

class WindowT : public Gtk::Window {
public:
    WindowT();
    virtual ~WindowT();

protected:
    // Signal handlers:

    virtual bool on_draw(const ::Cairo::RefPtr< ::Cairo::Context>& cr);
    void on_screen_changed(const Glib::RefPtr<Gdk::Screen>& previous_screen);

    void move_to_bottomright(gint padding);

    //void on_button_clicked();
    bool on_window_clicked(GdkEventButton* event);

    // Member widgets:
    // Gtk::Button _button;

private:
    bool _SUPPORTS_ALPHA = false;
};

#endif /* TRANSPARENT_H_ */
