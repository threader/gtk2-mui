/* GTK - The GIMP Toolkit
 * Copyright (C) 1995-1997 Peter Mattis, Spencer Kimball and Josh MacDonald
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

/*
 * Modified by the GTK+ Team and others 1997-2000.  See the AUTHORS
 * file for a list of people on the GTK+ Team.  See the ChangeLog
 * files for a list of changes.  These files are distributed with
 * GTK+ at ftp://ftp.gtk.org/pub/gtk/. 
 */

#ifndef __GTK_WINDOW_H__
#define __GTK_WINDOW_H__


#include <gdk/gdk.h>
#if 0
#include <gtk/gtkaccelgroup.h>
#endif
#include <gtk/gtkbin.h>
#include <gtk/gtkenums.h>
#include <gtk/gtkwidget.h>

G_BEGIN_DECLS

#define GTK_TYPE_WINDOW			(gtk_window_get_type ())
#define GTK_WINDOW(obj)			(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_WINDOW, GtkWindow))
#define GTK_WINDOW_CLASS(klass)		(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_WINDOW, GtkWindowClass))
#define GTK_IS_WINDOW(obj)		(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_WINDOW))
#define GTK_IS_WINDOW_CLASS(klass)	(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_WINDOW))
#define GTK_WINDOW_GET_CLASS(obj)       (G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_WINDOW, GtkWindowClass))


typedef struct _GtkWindow             GtkWindow;
typedef struct _GtkWindowClass        GtkWindowClass;
typedef struct _GtkWindowGeometryInfo GtkWindowGeometryInfo;
typedef struct _GtkWindowGroup        GtkWindowGroup;
typedef struct _GtkWindowGroupClass   GtkWindowGroupClass;

struct _GtkWindow {
  GtkBin bin;

  gchar *title;
  gchar *wmclass_name;
  gchar *wmclass_class;
  gchar *wm_role;

  GtkWidget *focus_widget;
  GtkWidget *default_widget;
  GtkWindow *transient_parent;
  GtkWindowGeometryInfo *geometry_info;
  GdkWindow *frame;
  GtkWindowGroup *group;

  guint16 configure_request_count;
  guint allow_shrink : 1;
  guint allow_grow : 1;
  guint configure_notify_received : 1;
  /* The following flags are initially TRUE (before a window is mapped).
   * They cause us to compute a configure request that involves
   * default-only parameters. Once mapped, we set them to FALSE.
   * Then we set them to TRUE again on unmap (for position)
   * and on unrealize (for size).
   */
  guint need_default_position : 1;
  guint need_default_size : 1;
  guint position : 3;
  guint type : 4; /* GtkWindowType */ 
  guint has_user_ref_count : 1;
  guint has_focus : 1;

  guint modal : 1;
  guint destroy_with_parent : 1;
  
  guint has_frame : 1;

  /* gtk_window_iconify() called before realization */
  guint iconify_initially : 1;
  guint stick_initially : 1;
  guint maximize_initially : 1;
  guint decorated : 1;
  
  guint type_hint : 3; /* GdkWindowTypeHint */ 
  guint gravity : 5; /* GdkGravity */

  guint is_active : 1;
  guint has_toplevel_focus : 1;
  
  guint frame_left;
  guint frame_top;
  guint frame_right;
  guint frame_bottom;

  guint keys_changed_handler;
  
  GdkModifierType mnemonic_modifier;
  GdkScreen      *screen;
};

struct _GtkWindowClass
{
  GtkBinClass parent_class;

  void     (* set_focus)   (GtkWindow *window,
			    GtkWidget *focus);
  gboolean (* frame_event) (GtkWindow *window,
			    GdkEvent  *event);

  /* G_SIGNAL_ACTION signals for keybindings */

  void     (* activate_focus)          (GtkWindow       *window);
  void     (* activate_default)        (GtkWindow       *window);
  void     (* move_focus)              (GtkWindow       *window,
                                        GtkDirectionType direction);
  
  void	   (*keys_changed)	       (GtkWindow	*window);
  
  /* Padding for future expansion */
  void (*_gtk_reserved1) (void);
  void (*_gtk_reserved2) (void);
  void (*_gtk_reserved3) (void);
  void (*_gtk_reserved4) (void);
};

#define GTK_TYPE_WINDOW_GROUP             (gtk_window_group_get_type ())
#define GTK_WINDOW_GROUP(object)          (G_TYPE_CHECK_INSTANCE_CAST ((object), GTK_TYPE_WINDOW_GROUP, GtkWindowGroup))
#define GTK_WINDOW_GROUP_CLASS(klass)     (G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_WINDOW_GROUP, GtkWindowGroupClass))
#define GTK_IS_WINDOW_GROUP(object)       (G_TYPE_CHECK_INSTANCE_TYPE ((object), GTK_TYPE_WINDOW_GROUP))
#define GTK_IS_WINDOW_GROUP_CLASS(klass)  (G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_WINDOW_GROUP))
#define GTK_WINDOW_GROUP_GET_CLASS(obj)   (G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_WINDOW_GROUP, GtkWindowGroupClass))

struct _GtkWindowGroup
{
  GObject parent_instance;

  GSList *grabs;
};

struct _GtkWindowGroupClass
{
  GObjectClass parent_class;

  /* Padding for future expansion */
  void (*_gtk_reserved1) (void);
  void (*_gtk_reserved2) (void);
  void (*_gtk_reserved3) (void);
  void (*_gtk_reserved4) (void);
};

#ifdef G_OS_WIN32
/* Reserve old names for DLL ABI backward compatibility */
#define gtk_window_set_icon_from_file gtk_window_set_icon_from_file_utf8
#define gtk_window_set_default_icon_from_file gtk_window_set_default_icon_from_file_utf8
#endif

GType      gtk_window_get_type                 (void) G_GNUC_CONST;
GtkWidget* gtk_window_new                      (GtkWindowType        type);
void       gtk_window_set_title                (GtkWindow           *window,
						const gchar         *title);
G_CONST_RETURN gchar *gtk_window_get_title     (GtkWindow           *window);
void       gtk_window_set_wmclass              (GtkWindow           *window,
						const gchar         *wmclass_name,
						const gchar         *wmclass_class);
void       gtk_window_set_role                 (GtkWindow           *window,
                                                const gchar         *role);
G_CONST_RETURN gchar *gtk_window_get_role      (GtkWindow           *window);
void       gtk_window_add_accel_group          (GtkWindow           *window,
						GtkAccelGroup	    *accel_group);
#if 0
void       gtk_window_remove_accel_group       (GtkWindow           *window,
						GtkAccelGroup	    *accel_group);
#endif
void       gtk_window_set_position             (GtkWindow           *window,
						GtkWindowPosition    position);
gboolean   gtk_window_activate_focus	       (GtkWindow           *window);
void       gtk_window_set_focus                (GtkWindow           *window,
						GtkWidget           *focus);
GtkWidget *gtk_window_get_focus                (GtkWindow           *window);
void       gtk_window_set_default              (GtkWindow           *window,
						GtkWidget           *default_widget);
gboolean   gtk_window_activate_default	       (GtkWindow           *window);

void       gtk_window_set_transient_for        (GtkWindow           *window, 
						GtkWindow           *parent);
GtkWindow *gtk_window_get_transient_for        (GtkWindow           *window);
void       gtk_window_set_type_hint            (GtkWindow           *window, 
						GdkWindowTypeHint    hint);
GdkWindowTypeHint gtk_window_get_type_hint     (GtkWindow           *window);
void       gtk_window_set_skip_taskbar_hint    (GtkWindow           *window,
                                                gboolean             setting);
gboolean   gtk_window_get_skip_taskbar_hint    (GtkWindow           *window);
void       gtk_window_set_skip_pager_hint      (GtkWindow           *window,
                                                gboolean             setting);
gboolean   gtk_window_get_skip_pager_hint      (GtkWindow           *window);
void       gtk_window_set_accept_focus         (GtkWindow           *window,
                                                gboolean             setting);
gboolean   gtk_window_get_accept_focus         (GtkWindow           *window);
void       gtk_window_set_focus_on_map         (GtkWindow           *window,
                                                gboolean             setting);
gboolean   gtk_window_get_focus_on_map         (GtkWindow           *window);
void       gtk_window_set_destroy_with_parent  (GtkWindow           *window,
                                                gboolean             setting);
gboolean   gtk_window_get_destroy_with_parent  (GtkWindow           *window);

void       gtk_window_set_resizable            (GtkWindow           *window,
                                                gboolean             resizable);
gboolean   gtk_window_get_resizable            (GtkWindow           *window);

void       gtk_window_set_gravity              (GtkWindow           *window,
                                                GdkGravity           gravity);
GdkGravity gtk_window_get_gravity              (GtkWindow           *window);


void       gtk_window_set_geometry_hints       (GtkWindow           *window,
						GtkWidget           *geometry_widget,
						GdkGeometry         *geometry,
						GdkWindowHints       geom_mask);

void	   gtk_window_set_screen	       (GtkWindow	    *window,
						GdkScreen	    *screen);
GdkScreen* gtk_window_get_screen	       (GtkWindow	    *window);

gboolean   gtk_window_is_active                (GtkWindow           *window);
gboolean   gtk_window_has_toplevel_focus       (GtkWindow           *window);



/* gtk_window_set_has_frame () must be called before realizing the window_*/
void       gtk_window_set_has_frame            (GtkWindow *window, 
						gboolean   setting);
gboolean   gtk_window_get_has_frame            (GtkWindow *window);
void       gtk_window_set_frame_dimensions     (GtkWindow *window, 
						gint       left,
						gint       top,
						gint       right,
						gint       bottom);
void       gtk_window_get_frame_dimensions     (GtkWindow *window, 
						gint      *left,
						gint      *top,
						gint      *right,
						gint      *bottom);
void       gtk_window_set_decorated            (GtkWindow *window,
                                                gboolean   setting);
gboolean   gtk_window_get_decorated            (GtkWindow *window);

void       gtk_window_set_icon_list                (GtkWindow  *window,
                                                    GList      *list);
GList*     gtk_window_get_icon_list                (GtkWindow  *window);
void       gtk_window_set_icon                     (GtkWindow  *window,
                                                    GdkPixbuf  *icon);
void       gtk_window_set_icon_name                (GtkWindow   *window,
						    const gchar *name);
gboolean   gtk_window_set_icon_from_file           (GtkWindow   *window,
						    const gchar *filename,
						    GError     **err);
GdkPixbuf* gtk_window_get_icon                     (GtkWindow  *window);
G_CONST_RETURN 
gchar     *gtk_window_get_icon_name                (GtkWindow  *window);
void       gtk_window_set_default_icon_list        (GList      *list);
GList*     gtk_window_get_default_icon_list        (void);
void       gtk_window_set_default_icon             (GdkPixbuf  *icon);
void       gtk_window_set_default_icon_name        (const gchar *name);
gboolean   gtk_window_set_default_icon_from_file   (const gchar *filename,
						    GError     **err);

void       gtk_window_set_auto_startup_notification (gboolean setting);

/* If window is set modal, input will be grabbed when show and released when hide */
void       gtk_window_set_modal      (GtkWindow *window,
				      gboolean   modal);
gboolean   gtk_window_get_modal      (GtkWindow *window);
GList*     gtk_window_list_toplevels (void);

void     gtk_window_add_mnemonic          (GtkWindow       *window,
					   guint            keyval,
					   GtkWidget       *target);
void     gtk_window_remove_mnemonic       (GtkWindow       *window,
					   guint            keyval,
					   GtkWidget       *target);
gboolean gtk_window_mnemonic_activate     (GtkWindow       *window,
					   guint            keyval,
					   GdkModifierType  modifier);
void     gtk_window_set_mnemonic_modifier (GtkWindow       *window,
					   GdkModifierType  modifier);
GdkModifierType gtk_window_get_mnemonic_modifier (GtkWindow *window);

gboolean gtk_window_activate_key          (GtkWindow        *window,
					   GdkEventKey      *event);
gboolean gtk_window_propagate_key_event   (GtkWindow        *window,
					   GdkEventKey      *event);

void     gtk_window_present       (GtkWindow *window);
void     gtk_window_iconify       (GtkWindow *window);
void     gtk_window_deiconify     (GtkWindow *window);
void     gtk_window_stick         (GtkWindow *window);
void     gtk_window_unstick       (GtkWindow *window);
void     gtk_window_maximize      (GtkWindow *window);
void     gtk_window_unmaximize    (GtkWindow *window);
void     gtk_window_fullscreen    (GtkWindow *window);
void     gtk_window_unfullscreen  (GtkWindow *window);
void     gtk_window_set_keep_above    (GtkWindow *window, gboolean setting);
void     gtk_window_set_keep_below    (GtkWindow *window, gboolean setting);

void gtk_window_begin_resize_drag (GtkWindow     *window,
                                   GdkWindowEdge  edge,
                                   gint           button,
                                   gint           root_x,
                                   gint           root_y,
                                   guint32        timestamp);
void gtk_window_begin_move_drag   (GtkWindow     *window,
                                   gint           button,
                                   gint           root_x,
                                   gint           root_y,
                                   guint32        timestamp);

#ifndef GTK_DISABLE_DEPRECATED
void       gtk_window_set_policy               (GtkWindow           *window,
						gint                 allow_shrink,
						gint                 allow_grow,
						gint                 auto_shrink);
#define	gtk_window_position			gtk_window_set_position
#endif /* GTK_DISABLE_DEPRECATED */

/* Set initial default size of the window (does not constrain user
 * resize operations)
 */
void     gtk_window_set_default_size (GtkWindow   *window,
                                      gint         width,
                                      gint         height);
void     gtk_window_get_default_size (GtkWindow   *window,
                                      gint        *width,
                                      gint        *height);
void     gtk_window_resize           (GtkWindow   *window,
                                      gint         width,
                                      gint         height);
void     gtk_window_get_size         (GtkWindow   *window,
                                      gint        *width,
                                      gint        *height);
void     gtk_window_move             (GtkWindow   *window,
                                      gint         x,
                                      gint         y);
void     gtk_window_get_position     (GtkWindow   *window,
                                      gint        *root_x,
                                      gint        *root_y);
gboolean gtk_window_parse_geometry   (GtkWindow   *window,
                                      const gchar *geometry);

/* Ignore this unless you are writing a GUI builder */
void     gtk_window_reshow_with_initial_size (GtkWindow *window);

/* Window groups
 */
GType            gtk_window_group_get_type      (void) G_GNUC_CONST;

GtkWindowGroup * gtk_window_group_new           (void);
void             gtk_window_group_add_window    (GtkWindowGroup     *window_group,
						 GtkWindow          *window);
void             gtk_window_group_remove_window (GtkWindowGroup     *window_group,
					         GtkWindow          *window);

/* --- internal functions --- */
void            _gtk_window_internal_set_focus (GtkWindow *window,
						GtkWidget *focus);
void            gtk_window_remove_embedded_xid (GtkWindow *window,
						guint      xid);
void            gtk_window_add_embedded_xid    (GtkWindow *window,
						guint      xid);
void            _gtk_window_reposition         (GtkWindow *window,
						gint       x,
						gint       y);
void            _gtk_window_constrain_size     (GtkWindow *window,
						gint       width,
						gint       height,
						gint      *new_width,
						gint      *new_height);
GtkWindowGroup *_gtk_window_get_group          (GtkWindow *window);

void            _gtk_window_set_has_toplevel_focus (GtkWindow *window,
						    gboolean   has_toplevel_focus);
void            _gtk_window_unset_focus_and_default (GtkWindow *window,
						     GtkWidget *widget);

void            _gtk_window_set_is_active          (GtkWindow *window,
						    gboolean   is_active);

typedef void (*GtkWindowKeysForeachFunc) (GtkWindow      *window,
					  guint           keyval,
					  GdkModifierType modifiers,
					  gboolean        is_mnemonic,
					  gpointer        data);

void _gtk_window_keys_foreach (GtkWindow               *window,
			       GtkWindowKeysForeachFunc func,
			       gpointer                 func_data);

/* --- internal (GtkAcceleratable) --- */
gboolean	_gtk_window_query_nonaccels	(GtkWindow	*window,
						 guint		 accel_key,
						 GdkModifierType accel_mods);

G_END_DECLS

#endif /* __GTK_WINDOW_H__ */
