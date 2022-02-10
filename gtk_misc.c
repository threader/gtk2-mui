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

/*
 * Modified by the GTK-MUI Team 2006
 *
 * $Id: gtk_misc.c,v 1.4 2007/06/19 13:33:17 o1i Exp $
 */

#include <config.h>
#include "gtk/gtk.h"
#include "gtk/gtkcontainer.h"
#include "gtk/gtkmisc.h"
#if 0
#include "gtkintl.h"
#include "gtkalias.h"
#endif

#include "mui.h"
#include "gtk_globals.h"
#include "classes/classes.h"
#include "debug.h"


enum {
  PROP_0,
  PROP_XALIGN,
  PROP_YALIGN,
  PROP_XPAD,
  PROP_YPAD
};

static void gtk_misc_class_init   (GtkMiscClass *klass);
static void gtk_misc_init         (GtkMisc      *misc);
static void gtk_misc_realize      (GtkWidget    *widget);
static void gtk_misc_set_property (GObject         *object,
				   guint            prop_id,
				   const GValue    *value,
				   GParamSpec      *pspec);
static void gtk_misc_get_property (GObject         *object,
				   guint            prop_id,
				   GValue          *value,
				   GParamSpec      *pspec);


GType gtk_misc_get_type (void) {

  static GType misc_type = 0;

  DebOut("gtk_misc_get_type()\n");

  if (!misc_type) {
      static const GTypeInfo misc_info = {
        sizeof (GtkMiscClass),
        NULL,		/* base_init */
        NULL,		/* base_finalize */
        (GClassInitFunc) gtk_misc_class_init,
        NULL,		/* class_finalize */
        NULL,		/* class_data */
        sizeof (GtkMisc),
        0,		/* n_preallocs */
        (GInstanceInitFunc) gtk_misc_init,
        NULL,		/* value_table */
      };

      misc_type = g_type_register_static (GTK_TYPE_WIDGET, "GtkMisc",
					  &misc_info, G_TYPE_FLAG_ABSTRACT);
    }

  return misc_type;
}

static void gtk_misc_class_init (GtkMiscClass *class) {

  GObjectClass   *gobject_class;
  GtkWidgetClass *widget_class;

  DebOut("gtk_misc_class_init(%lx)\n",class);

  gobject_class = G_OBJECT_CLASS (class);
  widget_class = (GtkWidgetClass*) class;

  gobject_class->set_property = gtk_misc_set_property;
  gobject_class->get_property = gtk_misc_get_property;
  
  widget_class->realize = gtk_misc_realize;

  g_object_class_install_property (gobject_class,
                                   PROP_XALIGN,
                                   g_param_spec_float ("xalign",
						       P_("X align"),
						       P_("The horizontal alignment, from 0 (left) to 1 (right). Reversed for RTL layouts."),
						       0.0,
						       1.0,
						       0.5,
						       G_PARAM_READWRITE));

  g_object_class_install_property (gobject_class,
                                   PROP_YALIGN,
                                   g_param_spec_float ("yalign",
						       P_("Y align"),
						       P_("The vertical alignment, from 0 (top) to 1 (bottom)"),
						       0.0,
						       1.0,
						       0.5,
						       G_PARAM_READWRITE));

  g_object_class_install_property (gobject_class,
                                   PROP_XPAD,
                                   g_param_spec_int ("xpad",
						     P_("X pad"),
						     P_("The amount of space to add on the left and right of the widget, in pixels"),
						     0,
						     G_MAXINT,
						     0,
						     G_PARAM_READWRITE));

  g_object_class_install_property (gobject_class,
                                   PROP_YPAD,
                                   g_param_spec_int ("ypad",
						     P_("Y pad"),
						     P_("The amount of space to add on the top and bottom of the widget, in pixels"),
						     0,
						     G_MAXINT,
						     0,
						     G_PARAM_READWRITE));
}

static void gtk_misc_init (GtkMisc *misc) {

  DebOut("gtk_misc_init(%lx)\n");

  misc->xalign = 0.5;
  misc->yalign = 0.5;
  misc->xpad = 0;
  misc->ypad = 0;

  GtkSetObj(GTK_WIDGET(misc), NewObject(CL_Custom->mcc_Class, NULL,MA_Widget,(ULONG) misc,TAG_DONE));

  DebOut("  misc obj: %lx\n",GtkObj(misc));

  GTK_MUI(misc)->mainclass=CL_AREA;

  /* create a window ..                               */
  /* calling sth like gdk_window_new would be nicer.. */
  GTK_WIDGET(misc)->window=g_new0(GdkWindow,1);

  /* the only interesting thing in a window is the mgtk_widget pointer (hopefully) */
  GTK_WIDGET(misc)->window->mgtk_widget=(APTR) misc;
}

static void gtk_misc_set_property (GObject      *object,
		       guint         prop_id,
		       const GValue *value,
		       GParamSpec   *pspec) {
  GtkMisc *misc;

  DebOut("gtk_misc_set_property(%lx,%d,..)\n",object,prop_id);


  misc = GTK_MISC (object);

  switch (prop_id) {
    case PROP_XALIGN:
      gtk_misc_set_alignment (misc, g_value_get_float (value), misc->yalign);
      break;
    case PROP_YALIGN:
      gtk_misc_set_alignment (misc, misc->xalign, g_value_get_float (value));
      break;
    case PROP_XPAD:
      gtk_misc_set_padding (misc, g_value_get_int (value), misc->ypad);
      break;
    case PROP_YPAD:
      gtk_misc_set_padding (misc, misc->xpad, g_value_get_int (value));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

static void gtk_misc_get_property (GObject      *object,
		       guint         prop_id,
		       GValue       *value,
		       GParamSpec   *pspec) {

  GtkMisc *misc;

  DebOut("gtk_misc_get_property(%lx,%d,..)\n",object,prop_id);

  misc = GTK_MISC (object);

  switch (prop_id) {
    case PROP_XALIGN:
      g_value_set_float (value, misc->xalign);
      break;
    case PROP_YALIGN:
      g_value_set_float (value, misc->yalign);
      break;
    case PROP_XPAD:
      g_value_set_int (value, misc->xpad);
      break;
    case PROP_YPAD:
      g_value_set_int (value, misc->ypad);
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

void gtk_misc_set_alignment (GtkMisc *misc,
			gfloat   xalign,
			gfloat   yalign) {

  g_return_if_fail (GTK_IS_MISC (misc));

  DebOut("gtk_misc_set_alignment(%lx,..)\n",xalign,yalign);

  if (xalign < 0.0)
    xalign = 0.0;
  else if (xalign > 1.0)
    xalign = 1.0;

  if (yalign < 0.0)
    yalign = 0.0;
  else if (yalign > 1.0)
    yalign = 1.0;

  if ((xalign != misc->xalign) || (yalign != misc->yalign)) {
    misc->xalign = xalign;
    misc->yalign = yalign;
    
    /* clear the area that was allocated before the change
      */
    if (GTK_WIDGET_DRAWABLE (misc)) {
      GtkWidget *widget;
  
      widget = GTK_WIDGET (misc);
      gtk_widget_queue_draw (widget);
      }

    g_object_freeze_notify (G_OBJECT (misc));
    if (xalign != misc->xalign)
      g_object_notify (G_OBJECT (misc), "xalign");

    if (yalign != misc->yalign)
      g_object_notify (G_OBJECT (misc), "yalign");
    g_object_thaw_notify (G_OBJECT (misc));
  }
}

/**
 * gtk_misc_get_alignment:
 * @misc: a #GtkMisc
 * @xalign: location to store X alignment of @misc, or %NULL
 * @yalign: location to store Y alignment of @misc, or %NULL
 *
 * Gets the X and Y alignment of the widget within its allocation. See
 * gtk_misc_set_alignment().
 **/
void gtk_misc_get_alignment (GtkMisc *misc,
		        gfloat  *xalign,
			gfloat  *yalign) {

  g_return_if_fail (GTK_IS_MISC (misc));

  DebOut("gtk_misc_get_alignment(%lx,..)\n",misc);

  if (xalign)
    *xalign = misc->xalign;
  if (yalign)
    *yalign = misc->yalign;
}

void gtk_misc_set_padding (GtkMisc *misc,
		      gint     xpad,
		      gint     ypad) {

  GtkRequisition *requisition;

  DebOut("gtk_misc_set_padding(%lx,%d,%d)",misc,xpad,ypad);
  
  g_return_if_fail (GTK_IS_MISC (misc));
  
  if (xpad < 0)
    xpad = 0;
  if (ypad < 0)
    ypad = 0;
  
  if ((xpad != misc->xpad) || (ypad != misc->ypad)) {
    requisition = &(GTK_WIDGET (misc)->requisition);
    requisition->width -= misc->xpad * 2;
    requisition->height -= misc->ypad * 2;
    
    misc->xpad = xpad;
    misc->ypad = ypad;
    
    requisition->width += misc->xpad * 2;
    requisition->height += misc->ypad * 2;
    
    if (GTK_WIDGET_DRAWABLE (misc))
      gtk_widget_queue_resize (GTK_WIDGET (misc));

    g_object_freeze_notify (G_OBJECT (misc));
    if (xpad != misc->xpad)
      g_object_notify (G_OBJECT (misc), "xpad");

    if (ypad != misc->ypad)
      g_object_notify (G_OBJECT (misc), "ypad");
    g_object_thaw_notify (G_OBJECT (misc));
  }
}

/**
 * gtk_misc_get_padding:
 * @misc: a #GtkMisc
 * @xpad: location to store padding in the X direction, or %NULL
 * @ypad: location to store padding in the Y direction, or %NULL
 *
 * Gets the padding in the X and Y directions of the widget. See gtk_misc_set_padding().
 **/
void gtk_misc_get_padding (GtkMisc *misc,
		      gint    *xpad,
		      gint    *ypad) {

  g_return_if_fail (GTK_IS_MISC (misc));

  DebOut("gtk_misc_get_padding(%lx,..)\n",misc);

  if (xpad)
    *xpad = misc->xpad;
  if (ypad)
    *ypad = misc->ypad;
}

static void gtk_misc_realize (GtkWidget *widget) {

  GtkMisc *misc;
  GdkWindowAttr attributes;
  gint attributes_mask;

  g_return_if_fail (GTK_IS_MISC (widget));

  DebOut("gtk_misc_realize(%lx)\n");

  GTK_WIDGET_SET_FLAGS (widget, GTK_REALIZED);
  misc = GTK_MISC (widget);

  if (GTK_WIDGET_NO_WINDOW (widget))
    {
      widget->window = gtk_widget_get_parent_window (widget);
      g_object_ref (widget->window);
      widget->style = gtk_style_attach (widget->style, widget->window);
    }
  else
    {
      attributes.window_type = GDK_WINDOW_CHILD;
      attributes.x = widget->allocation.x;
      attributes.y = widget->allocation.y;
      attributes.width = widget->allocation.width;
      attributes.height = widget->allocation.height;
      attributes.wclass = GDK_INPUT_OUTPUT;
      attributes.visual = gtk_widget_get_visual (widget);
      attributes.colormap = gtk_widget_get_colormap (widget);
      attributes.event_mask = gtk_widget_get_events (widget) | GDK_EXPOSURE_MASK;
      attributes_mask = GDK_WA_X | GDK_WA_Y | GDK_WA_VISUAL | GDK_WA_COLORMAP;

      widget->window = gdk_window_new (gtk_widget_get_parent_window (widget), &attributes, attributes_mask);
      gdk_window_set_user_data (widget->window, widget);

      widget->style = gtk_style_attach (widget->style, widget->window);
#if 0
      gdk_window_set_back_pixmap (widget->window, NULL, TRUE);
#endif
    }
}

#define __GTK_MISC_C__