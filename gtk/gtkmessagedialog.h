/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 2 -*- */
/* GTK - The GIMP Toolkit
 * Copyright (C) 2000 Red Hat, Inc.
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
 * Modified by the GTK+ Team and others 1997-2003.  See the AUTHORS
 * file for a list of people on the GTK+ Team.  See the ChangeLog
 * files for a list of changes.  These files are distributed with
 * GTK+ at ftp://ftp.gtk.org/pub/gtk/. 
 */

#ifndef __GTK_MESSAGE_DIALOG_H__
#define __GTK_MESSAGE_DIALOG_H__

#include <gtk/gtkdialog.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef enum
{
  GTK_MESSAGE_INFO,
  GTK_MESSAGE_WARNING,
  GTK_MESSAGE_QUESTION,
  GTK_MESSAGE_ERROR
} GtkMessageType;

typedef enum
{
  GTK_BUTTONS_NONE,
  GTK_BUTTONS_OK,
  GTK_BUTTONS_CLOSE,
  GTK_BUTTONS_CANCEL,
  GTK_BUTTONS_YES_NO,
  GTK_BUTTONS_OK_CANCEL
} GtkButtonsType;

#define GTK_TYPE_MESSAGE_DIALOG                  (gtk_message_dialog_get_type ())
#define GTK_MESSAGE_DIALOG(obj)                  (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_MESSAGE_DIALOG, GtkMessageDialog))
#define GTK_MESSAGE_DIALOG_CLASS(klass)          (G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_MESSAGE_DIALOG, GtkMessageDialogClass))
#define GTK_IS_MESSAGE_DIALOG(obj)               (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_MESSAGE_DIALOG))
#define GTK_IS_MESSAGE_DIALOG_CLASS(klass)       (G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_MESSAGE_DIALOG))
#define GTK_MESSAGE_DIALOG_GET_CLASS(obj)        (G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_MESSAGE_DIALOG, GtkMessageDialogClass))

typedef struct _GtkMessageDialog        GtkMessageDialog;
typedef struct _GtkMessageDialogClass   GtkMessageDialogClass;

struct _GtkMessageDialog
{
  /*< private >*/
  
  GtkDialog parent_instance;
  
  GtkWidget *image;
  GtkWidget *label;
};

struct _GtkMessageDialogClass
{
  GtkDialogClass parent_class;

  /* Padding for future expansion */
  void (*_gtk_reserved1) (void);
  void (*_gtk_reserved2) (void);
  void (*_gtk_reserved3) (void);
  void (*_gtk_reserved4) (void);
};

GType      gtk_message_dialog_get_type (void) G_GNUC_CONST;

GtkWidget* gtk_message_dialog_new      (GtkWindow      *parent,
                                        GtkDialogFlags  flags,
                                        GtkMessageType  type,
                                        GtkButtonsType  buttons,
                                        const gchar    *message_format,
                                        ...) G_GNUC_PRINTF (5, 6);

GtkWidget* gtk_message_dialog_new_with_markup   (GtkWindow      *parent,
                                                 GtkDialogFlags  flags,
                                                 GtkMessageType  type,
                                                 GtkButtonsType  buttons,
                                                 const gchar    *message_format,
                                                 ...) G_GNUC_PRINTF (5, 6);

void       gtk_message_dialog_set_markup  (GtkMessageDialog *message_dialog,
                                           const gchar      *str);

void       gtk_message_dialog_format_secondary_text (GtkMessageDialog *message_dialog,
                                                     const gchar      *message_format,
                                                     ...) G_GNUC_PRINTF (2, 3);

void       gtk_message_dialog_format_secondary_markup (GtkMessageDialog *message_dialog,
                                                       const gchar      *message_format,
                                                       ...) G_GNUC_PRINTF (2, 3);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __GTK_MESSAGE_DIALOG_H__ */
