/* Copyright (C) 2013-2018 Konrad Gräfe <konradgraefe@aol.com>
 *
 * This software may be modified and distributed under the terms
 * of the GPLv2 license. See the COPYING file for details.
 */

#include "unhighlight-system-messages.h"

#include <gtkplugin.h>
#include <version.h>
#include <gtkconv.h>

static void (*write_conv_ori)(PurpleConversation *conv, const char *name, const char *alias, const char *message, PurpleMessageFlags flags, time_t mtime);

static void write_conv(PurpleConversation *conv, const char *name, const char *alias, const char *message, PurpleMessageFlags flags, time_t mtime) {
	if((flags & PURPLE_MESSAGE_SYSTEM) && (flags & PURPLE_MESSAGE_NICK)) {
		flags &= ~PURPLE_MESSAGE_NICK;
	}

	if(write_conv_ori) {
		write_conv_ori(conv, name, alias, message, flags, mtime);
	}
}

static gboolean plugin_load(PurplePlugin *plugin) {
	PurpleConversationUiOps *ops;

	ops = pidgin_conversations_get_conv_ui_ops();
	if(!ops) {
		return FALSE;
	}

	write_conv_ori = ops->write_conv;
	ops->write_conv = write_conv;

	return TRUE;
}

static gboolean plugin_unload(PurplePlugin *plugin) {
	PurpleConversationUiOps *ops;

	ops = pidgin_conversations_get_conv_ui_ops();
	if(!ops) {
		return FALSE;
	}

	ops->write_conv = write_conv_ori;
	return TRUE;
}

static PurplePluginInfo info = {
	PURPLE_PLUGIN_MAGIC,
	PURPLE_MAJOR_VERSION,
	PURPLE_MINOR_VERSION,
	PURPLE_PLUGIN_STANDARD,			/**< type           */
	PIDGIN_PLUGIN_TYPE,					/**< ui_requirement */
	0,					/**< flags          */
	NULL,					/**< dependencies   */
	PURPLE_PRIORITY_DEFAULT,		/**< priority       */

	PLUGIN_ID,				/**< id             */
	NULL,					/**< name           */
	PLUGIN_VERSION,				/**< version        */
	NULL,					/**  summary        */
				
	NULL,					/**  description    */
	PLUGIN_AUTHOR,				/**< author         */
	PLUGIN_WEBSITE,				/**< homepage       */

	plugin_load,				/**< load           */
	plugin_unload,				/**< unload         */
	NULL,					/**< destroy        */

	NULL,					/**< ui_info        */
	NULL,					/**< extra_info     */
	NULL,					/**< prefs_info     */
	NULL,					/**< actions        */
	/* padding */
	NULL,
	NULL,
	NULL,
	NULL
};

static void init_plugin(PurplePlugin *plugin) {
	const char *str = "Unhighlight System Messages";
	gchar *plugins_locale_dir;

#ifdef ENABLE_NLS
	plugins_locale_dir = g_build_filename(purple_user_dir(), "locale", NULL);

	bindtextdomain(GETTEXT_PACKAGE, plugins_locale_dir);
	if(str == _(str)) {
		bindtextdomain(GETTEXT_PACKAGE, LOCALEDIR);
	}
	bind_textdomain_codeset(GETTEXT_PACKAGE, "UTF-8");

	g_free(plugins_locale_dir);
#endif /* ENABLE_NLS */

	info.name        = _("Unhighlight System Messages");
	info.summary     = _("This plugin removes the highlight flag from system messages.");
	info.description = _("This plugin removes the highlight flag from system messages. This works around a bug which was introduced with Pidgin 2.10.7 and leads to a highlighted IRC channel each time you join if you set the channel topic.");
}

PURPLE_INIT_PLUGIN(PLUGIN_STATIC_NAME, init_plugin, info)

