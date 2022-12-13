#include <gtk/gtk.h>

static void action_clbk ( GSimpleAction *simple_action, G_GNUC_UNUSED GVariant *parameter, G_GNUC_UNUSED gpointer *data )
{
    g_print ( "The action %s was clicked.\n", g_action_get_name ( G_ACTION ( simple_action ) ) );
}

static void activate ( GApplication *app, G_GNUC_UNUSED gpointer *data )
{
    GtkWidget *win;
    GSimpleAction *act_connect;
    GSimpleAction *act_disconnect;

    /// ***
    GMenu *menu_bar;
    GMenu *file_menu;
    GMenu *server_menu;

    /// ***
    GMenuItem *menu_item_connect;
    GMenuItem *menu_item_disconnect;

    /// *** Menu Bar
    menu_bar = g_menu_new();

    /// *** Network_Menu
    file_menu = g_menu_new();
    g_menu_append_submenu ( menu_bar, "File", G_MENU_MODEL ( file_menu ) );

    edit_menu = g_menu_new();
    g_menu_append_submenu ( menu_bar, "Edit", G_MENU_MODEL ( file_menu ) );

    view_menu = g_menu_new();
    g_menu_append_submenu ( menu_bar, "View", G_MENU_MODEL ( file_menu ) );

    /// *** Server_Menu
    server_menu = g_menu_new();
    g_menu_append_submenu ( file_menu, "Server", G_MENU_MODEL ( server_menu ) );
    /// ***
    win = gtk_application_window_new ( GTK_APPLICATION ( app ) );
    gtk_window_set_title ( GTK_WINDOW ( win ), "IRC Client" );
    gtk_window_set_default_size ( GTK_WINDOW ( win ), 400, 400 );

    /// *** Create Connect and Disconnect Actions
    act_connect    = g_simple_action_new ( "connect", NULL );
    act_disconnect = g_simple_action_new ( "disconnect", NULL );

    /// *** Add them to the ActionMap
    g_action_map_add_action ( G_ACTION_MAP ( app ), G_ACTION ( act_connect ) );
    g_action_map_add_action ( G_ACTION_MAP ( app ), G_ACTION ( act_disconnect ) );

    /// *** Connect them to the activate Signal
    g_signal_connect ( act_connect,    "activate", G_CALLBACK ( action_clbk ), NULL );
    g_signal_connect ( act_disconnect, "activate", G_CALLBACK ( action_clbk ), NULL );

    /// *** Create the Connect Item
    menu_item_connect = g_menu_item_new ( "Connect", "app.connect" );
    g_menu_append_item ( server_menu, menu_item_connect );

    /// *** Create the Disconnect Item
    menu_item_disconnect = g_menu_item_new ( "Disconnect", "app.disconnect" );
    g_menu_append_item ( server_menu, menu_item_disconnect );

    /// ***
    gtk_application_set_menubar             ( GTK_APPLICATION ( app ), G_MENU_MODEL ( menu_bar ) );
    gtk_application_window_set_show_menubar ( GTK_APPLICATION_WINDOW ( win ), TRUE );

    /// ***
    gtk_window_present ( GTK_WINDOW ( win ) );

    /// *** Clean
    g_object_unref ( act_connect );
    g_object_unref ( act_disconnect );
    g_object_unref ( menu_item_connect );
    g_object_unref ( menu_item_disconnect );
    g_object_unref ( server_menu );
    g_object_unref ( network_menu );
    g_object_unref ( menu_bar );
}

int main ( int argc, char **argv )
{
    GtkApplication *app;
    int stat;

    /// ***
    app = gtk_application_new ( "com.ircclient", G_APPLICATION_FLAGS_NONE );
    g_signal_connect ( app, "activate", G_CALLBACK ( activate ), NULL );

    /// ***
    stat = g_application_run ( G_APPLICATION ( app ), argc, argv );
    g_object_unref ( app );

    /// ***
    return stat;
}