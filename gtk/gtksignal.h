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
 * $Id: gtksignal.h,v 1.3 2006/11/28 13:12:02 o1i Exp $
 */

#ifndef __GTK_SIGNAL_H__
#define __GTK_SIGNAL_H__


#include <gtk/gtkenums.h>
#include <gtk/gtkobject.h>
#if 0
#include <gtk/gtkmarshal.h>
#endif

G_BEGIN_DECLS
  
#ifndef GTK_DISABLE_DEPRECATED

#define	gtk_signal_default_marshaller	g_cclosure_marshal_VOID__VOID


/* --- compat defines --- */
#define GTK_SIGNAL_OFFSET	                      GTK_STRUCT_OFFSET
#define	gtk_signal_lookup(name,object_type)	                                       \
   g_signal_lookup ((name), (object_type))
#define	gtk_signal_name(signal_id)                                                     \
   g_signal_name (signal_id)
#define	gtk_signal_emit_stop(object,signal_id)                                         \
   g_signal_stop_emission ((object), (signal_id), 0)
#define	gtk_signal_connect(object,name,func,func_data)                                 \
   gtk_signal_connect_full ((object), (name), (func), 0, (func_data), 0, 0, 0)
#define	gtk_signal_connect_after(object,name,func,func_data)                           \
   gtk_signal_connect_full ((object), (name), (func), 0, (func_data), 0, 0, 1)
#define	gtk_signal_connect_object(object,name,func,slot_object)                        \
   gtk_signal_connect_full ((object), (name), (func), 0, (slot_object), 0, 1, 0)
#define	gtk_signal_connect_object_after(object,name,func,slot_object)                  \
   gtk_signal_connect_full ((object), (name), (func), 0, (slot_object), 0, 1, 1)
#define	gtk_signal_disconnect(object,handler_id)                                       \
   g_signal_handler_disconnect ((object), (handler_id))
#define	gtk_signal_handler_block(object,handler_id)                                    \
   g_signal_handler_block ((object), (handler_id))
#define	gtk_signal_handler_unblock(object,handler_id)                                  \
   g_signal_handler_unblock ((object), (handler_id))
#define	gtk_signal_disconnect_by_func(object,func,data)	                               \
   gtk_signal_compat_matched ((object), (func), (data),                                \
			      (GSignalMatchType)(G_SIGNAL_MATCH_FUNC |                 \
						 G_SIGNAL_MATCH_DATA), 0)
#define	gtk_signal_disconnect_by_data(object,data)                                     \
   gtk_signal_compat_matched ((object), 0, (data), G_SIGNAL_MATCH_DATA, 0)
#define	gtk_signal_handler_block_by_func(object,func,data)                             \
   gtk_signal_compat_matched ((object), (func), (data),                                \
			      (GSignalMatchType)(G_SIGNAL_MATCH_FUNC |                 \
						 G_SIGNAL_MATCH_DATA), 1)
#define	gtk_signal_handler_block_by_data(object,data)                                  \
   gtk_signal_compat_matched ((object), 0, (data), G_SIGNAL_MATCH_DATA, 1)
#define	gtk_signal_handler_unblock_by_func(object,func,data)                           \
   gtk_signal_compat_matched ((object), (func), (data),                                \
			      (GSignalMatchType)(G_SIGNAL_MATCH_FUNC |                 \
						 G_SIGNAL_MATCH_DATA), 2)
#define	gtk_signal_handler_unblock_by_data(object,data)                                \
   gtk_signal_compat_matched ((object), 0, (data), G_SIGNAL_MATCH_DATA, 2)
#define	gtk_signal_handler_pending(object,signal_id,may_be_blocked)                    \
   g_signal_has_handler_pending ((object), (signal_id), 0, (may_be_blocked))
#define	gtk_signal_handler_pending_by_func(object,signal_id,may_be_blocked,func,data)  \
   (g_signal_handler_find ((object),                                                             \
			   (GSignalMatchType)(G_SIGNAL_MATCH_ID |                                \
                                              G_SIGNAL_MATCH_FUNC |                              \
                                              G_SIGNAL_MATCH_DATA |                              \
                                              ((may_be_blocked) ? 0 : G_SIGNAL_MATCH_UNBLOCKED)),\
                           (signal_id), 0, 0, (func), (data)) != 0)


/* --- compat functions --- */
guint	gtk_signal_newv				(const gchar	    *name,
						 GtkSignalRunType    signal_flags,
						 GtkType	     object_type,
						 guint		     function_offset,
						 GtkSignalMarshaller marshaller,
						 GtkType	     return_val,
						 guint		     n_args,
						 GtkType	    *args);
guint	gtk_signal_new				(const gchar	    *name,
						 GtkSignalRunType    signal_flags,
						 GtkType	     object_type,
						 guint		     function_offset,
						 GtkSignalMarshaller marshaller,
						 GtkType	     return_val,
						 guint		     n_args,
						 ...);
void	gtk_signal_emit_stop_by_name		(GtkObject	    *object,
						 const gchar	    *name);
void	gtk_signal_connect_object_while_alive	(GtkObject	    *object,
						 const gchar        *name,
						 GtkSignalFunc	     func,
						 GtkObject	    *alive_object);
void	gtk_signal_connect_while_alive		(GtkObject	    *object,
						 const gchar        *name,
						 GtkSignalFunc	     func,
						 gpointer	     func_data,
						 GtkObject	    *alive_object);
gulong	gtk_signal_connect_full			(GtkObject	    *object,
						 const gchar	    *name,
						 GtkSignalFunc	     func,
						 GtkCallbackMarshal  unsupported,
						 gpointer	     data,
						 GtkDestroyNotify    destroy_func,
						 gint		     object_signal,
						 gint		     after);
void	gtk_signal_emitv			(GtkObject	    *object,
						 guint		     signal_id,
						 GtkArg		    *args);
void	gtk_signal_emit				(GtkObject	    *object,
						 guint		     signal_id,
						 ...);
void	gtk_signal_emit_by_name			(GtkObject	    *object,
						 const gchar	    *name,
						 ...);
void	gtk_signal_emitv_by_name		(GtkObject	    *object,
						 const gchar	    *name,
						 GtkArg		    *args);
void	gtk_signal_compat_matched		(GtkObject	    *object,
						 GtkSignalFunc 	     func,
						 gpointer      	     data,
						 GSignalMatchType    match,
						 guint               action);

#endif /* GTK_DISABLE_DEPRECATED */

G_END_DECLS

#endif /* __GTK_SIGNAL_H__ */
