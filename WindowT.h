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
    WindowT(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade);
    virtual ~WindowT();

protected:
    virtual bool on_draw(const ::Cairo::RefPtr< ::Cairo::Context>& cr);
    void on_screen_changed(const Glib::RefPtr<Gdk::Screen>& previous_screen);
    void move_to_bottomright(gint padding);
    bool on_window_clicked(GdkEventButton* event);
    //void on_button_clicked();

    // Member widgets:
    Glib::RefPtr<Gtk::Builder> m_builder;
    Gtk::Box* m_box;
    Gtk::Label* m_labelDate;
    Gtk::Label* m_labelMonth;
    // Gtk::Button _button;

private:
    bool m_supportsAlpha;
};

#endif /* TRANSPARENT_H_ */
