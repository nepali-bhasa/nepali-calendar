/**
 * transparent.h
 *
 */

#ifndef TRANSPARENT_H_
#define TRANSPARENT_H_

#include <iostream>
#include <string>
#include <gtk/gtk.h>
#include <gtkmm.h>
#include "nepalical/Ad.h"
#include "nepalical/Bs.h"
#include "nepalical/helper.h"

class WindowT : public Gtk::Window {
public:
    WindowT(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade);
    virtual ~WindowT();

protected:
    virtual bool on_draw(const ::Cairo::RefPtr< ::Cairo::Context>& cr);
    void on_screen_changed(const Glib::RefPtr<Gdk::Screen>& previous_screen);
    bool on_window_clicked(GdkEventButton* event);
    bool updateToday();
    void move_to_bottomright(gint padding);
    //void on_button_clicked();

    // Member widgets:
    Glib::RefPtr<Gtk::Builder> m_builder;

    Gtk::Box* m_complete;
    Gtk::Box* m_compact;
    // Gtk::Button _button;

private:
    bool m_supportsAlpha;
    bool m_completeShow;
};

#endif /* TRANSPARENT_H_ */
