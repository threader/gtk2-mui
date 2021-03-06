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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the GNU
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
 * $Id: gtkadjustment.h,v 1.4 2006/11/28 13:12:02 o1i Exp $
 */

#ifndef __GTK_ADJUSTMENT_H__
#define __GTK_ADJUSTMENT_H__

#include <gdk/gdk.h>
#include <gtk/gtkobject.h>

/*
#include <gtk/gtk.h>  
*/

#ifndef P_
/* TODO: remove me */
#define P_(String) (String)
#endif

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


#define GTK_TYPE_ADJUSTMENT                  (gtk_adjustment_get_type ())
#define GTK_ADJUSTMENT(obj)                  (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_ADJUSTMENT, GtkAdjustment))
#define GTK_ADJUSTMENT_CLASS(klass)          (G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_ADJUSTMENT, GtkAdjustmentClass))
#define GTK_IS_ADJUSTMENT(obj)               (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_ADJUSTMENT))
#define GTK_IS_ADJUSTMENT_CLASS(klass)       (G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_ADJUSTMENT))
#define GTK_ADJUSTMENT_GET_CLASS(obj)        (G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_ADJUSTMENT, GtkAdjustmentClass))


typedef struct _GtkAdjustmentClass  GtkAdjustmentClass;

typedef struct _GtkAdjustment	    GtkAdjustment;

struct _GtkAdjustment { 
  GtkObject parent_instance;

  gdouble lower;
  gdouble upper;
  gdouble value;
  gdouble step_increment;
  gdouble page_increment;
  gdouble page_size;
};

struct _GtkAdjustmentClass
{
  GtkObjectClass parent_class;
  
  void (* changed)	 (GtkAdjustment *adjustment);
  void (* value_changed) (GtkAdjustment *adjustment);
  
  /* Padding for future expansion */
  void (*_gtk_reserved1) (void);
  void (*_gtk_reserved2) (void);
  void (*_gtk_reserved3) (void);
  void (*_gtk_reserved4) (void);
};


GType	   gtk_adjustment_get_type		(void) G_GNUC_CONST;

/* o1i: should this be: GtkObject *gtk_.. ?? */
GtkAdjustment *gtk_adjustment_new			(gdouble	  value,
						 gdouble	  lower,
						 gdouble	  upper,
						 gdouble	  step_increment,
						 gdouble	  page_increment,
						 gdouble	  page_size);
void	   gtk_adjustment_changed		(GtkAdjustment	 *adjustment);
void	   gtk_adjustment_value_changed		(GtkAdjustment	 *adjustment);
void	   gtk_adjustment_clamp_page		(GtkAdjustment	 *adjustment,
						 gdouble	  lower,
						 gdouble	  upper);
gdouble	   gtk_adjustment_get_value		(GtkAdjustment   *adjustment);
void	   gtk_adjustment_set_value		(GtkAdjustment	 *adjustment,
						 gdouble	  value);

#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /* __GTK_ADJUSTMENT_H__ */
