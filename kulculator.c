#define _GNU_SOURCE
#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <math.h>

typedef struct {
    GtkWidget *window;
    GtkWidget *first_entry;
    GtkWidget *second_entry;
    GtkWidget *operation_combo;
    GtkWidget *result_label;
    GtkWidget *calculate_button;
} AppWidgets;

const char* thinking_messages[] = {
    "Analyzing...",
    "Polishing results...",
    "Calculating...",
    "Trying to guess the answer...",
    "Sorting...",
    "...",
    "Sacrificing memory for truth..."
};

const char* philosophical_results[] = {
    "maybe, idk",
    "None",
    "DIY", 
    "Hello, World!",
    "ಠ_ಠ",
    "67 (of course)",
    "MUSTARD?!",
    "get a job on our site: employment.com"
};

void system_collapse_function(GtkWidget *parent) {
    GtkWidget *dialog;
    
    dialog = gtk_message_dialog_new(GTK_WINDOW(parent),
                                   GTK_DIALOG_DESTROY_WITH_PARENT,
                                   GTK_MESSAGE_INFO,
                                   GTK_BUTTONS_OK,
                                   "Only by losing everything do we gain freedom...");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
    
    sleep(1);
    
    dialog = gtk_message_dialog_new(GTK_WINDOW(parent),
                                   GTK_DIALOG_DESTROY_WITH_PARENT,
                                   GTK_MESSAGE_INFO,
                                   GTK_BUTTONS_OK,
                                   "Removing system files:");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
    
    for (int i = 0; i < 3; i++) {
        char msg[100];
        snprintf(msg, sizeof(msg), "Deleting system_file_%d.dll...", i+1);
        dialog = gtk_message_dialog_new(GTK_WINDOW(parent),
                                       GTK_DIALOG_DESTROY_WITH_PARENT,
                                       GTK_MESSAGE_INFO,
                                       GTK_BUTTONS_OK,
                                       "%s", msg);
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        usleep(300000);
    }
    
    dialog = gtk_message_dialog_new(GTK_WINDOW(parent),
                                   GTK_DIALOG_DESTROY_WITH_PARENT,
                                   GTK_MESSAGE_INFO,
                                   GTK_BUTTONS_OK,
                                   "System has collapsed.");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
    
    exit(0);
}

void generate_result(char* buffer, size_t buffer_size, GtkWidget *parent) {
    int choice = rand() % 10;
    double random_value = ((double)rand() / RAND_MAX) * 2e8 - 1e8;
    
    switch(choice) {
        case 0:
            snprintf(buffer, buffer_size, "%.5f %s", random_value, philosophical_results[0]);
            break;
        case 1:
            snprintf(buffer, buffer_size, "%s", philosophical_results[1]);
            break;
        case 2:
            snprintf(buffer, buffer_size, "%s", philosophical_results[2]);
            break;
        case 3:
            snprintf(buffer, buffer_size, "%s", philosophical_results[3]);
            break;
        case 4:
            snprintf(buffer, buffer_size, "%s", philosophical_results[4]);
            break;
        case 5:
            snprintf(buffer, buffer_size, "%.2e %s", random_value, philosophical_results[5]);
            break;
        case 6:
            system_collapse_function(parent);
            break;
        case 7:
            snprintf(buffer, buffer_size, "%s", philosophical_results[6]);
            break;
        case 8:
            snprintf(buffer, buffer_size, "%s", philosophical_results[7]);
            break;
        case 9:
            snprintf(buffer, buffer_size, "%s", philosophical_results[8]);
            break;
    }
}

void simulate_thinking(GtkWidget *parent) {
    GtkWidget *dialog, *content_area, *label;
    
    dialog = gtk_dialog_new_with_buttons("Thinking...",
                                        GTK_WINDOW(parent),
                                        GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                                        NULL, NULL);
    
    gtk_window_set_default_size(GTK_WINDOW(dialog), 250, 100);
    gtk_window_set_resizable(GTK_WINDOW(dialog), FALSE);
    
    content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
    label = gtk_label_new("Thinking process initiated...");
    gtk_label_set_line_wrap(GTK_LABEL(label), TRUE);
    gtk_container_add(GTK_CONTAINER(content_area), label);
    
    gtk_widget_show_all(dialog);
    
    int iterations = 3 + (rand() % 4);
    for (int i = 0; i < iterations; i++) {
        const char* message = thinking_messages[rand() % (sizeof(thinking_messages)/sizeof(thinking_messages[0]))];
        gtk_label_set_text(GTK_LABEL(label), message);
        
        while (gtk_events_pending()) {
            gtk_main_iteration();
        }
        
        usleep((400000 + (rand() % 800000)));
    }
    
    gtk_widget_destroy(dialog);
}

gboolean on_button_enter(GtkWidget *widget, GdkEventCrossing *event, gpointer data) {
    (void)event; (void)data; 
    gtk_button_set_label(GTK_BUTTON(widget), "PONDER!");
    return FALSE;
}

gboolean on_button_leave(GtkWidget *widget, GdkEventCrossing *event, gpointer data) {
    (void)event; (void)data;
    gtk_button_set_label(GTK_BUTTON(widget), "Ponder!");
    return FALSE;
}

int is_valid_number(const char* str) {
    if (str == NULL || strlen(str) == 0) {
        return 0;
    }
    
    char *endptr;
    strtod(str, &endptr);
    
    while (*endptr == ' ' || *endptr == '\t') {
        endptr++;
    }
    
    return *endptr == '\0';
}

void on_calculate_clicked(GtkWidget *widget, gpointer data) {
    (void)widget;
    AppWidgets *app = (AppWidgets*)data;
    gtk_label_set_text(GTK_LABEL(app->result_label), "Result: ");

    const char* first_text = gtk_entry_get_text(GTK_ENTRY(app->first_entry));
    const char* second_text = gtk_entry_get_text(GTK_ENTRY(app->second_entry));
    int operation_index = gtk_combo_box_get_active(GTK_COMBO_BOX(app->operation_combo));

    if (!is_valid_number(first_text) || !is_valid_number(second_text)) {
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(app->window),
                                                 GTK_DIALOG_DESTROY_WITH_PARENT,
                                                 GTK_MESSAGE_ERROR,
                                                 GTK_BUTTONS_OK,
                                                 "Error: Please enter valid numbers only.");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }

    double first_num = strtod(first_text, NULL);
    double second_num = strtod(second_text, NULL);
    
    simulate_thinking(app->window);

    if ((double)rand() / RAND_MAX < 0.1) {
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(app->window),
                                                  GTK_DIALOG_DESTROY_WITH_PARENT,
                                                  GTK_MESSAGE_ERROR,
                                                  GTK_BUTTONS_OK,
                                                  "Terminating...");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }
    
    char result_text[200];

    if ((double)rand() / RAND_MAX < 0.3) {
        double real_result = 0;
        
        switch(operation_index) {
            case 0: real_result = first_num + second_num; break;
            case 1: real_result = first_num - second_num; break;
            case 2: real_result = first_num * second_num; break;
            case 3: 
                if (second_num == 0) {
                    GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(app->window),
                                                              GTK_DIALOG_DESTROY_WITH_PARENT,
                                                              GTK_MESSAGE_ERROR,
                                                              GTK_BUTTONS_OK,
                                                              "Math Error: Division by zero");
                    gtk_dialog_run(GTK_DIALOG(dialog));
                    gtk_widget_destroy(dialog);
                    return;
                }
                real_result = first_num / second_num; 
                break;
        }
        
        snprintf(result_text, sizeof(result_text), "Real result (really?): %.5f", real_result);
    } else {
        char philosophical_result[150];
        generate_result(philosophical_result, sizeof(philosophical_result), app->window);
        snprintf(result_text, sizeof(result_text), "Philosophical Result: %s", philosophical_result);
    }
    
    gtk_label_set_text(GTK_LABEL(app->result_label), result_text);
}

static void activate(GtkApplication *app, gpointer user_data) {
    (void)user_data;
    AppWidgets *widgets = g_malloc(sizeof(AppWidgets));

    widgets->window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(widgets->window), "kulculator");
    gtk_window_set_default_size(GTK_WINDOW(widgets->window), 400, 350);
    gtk_window_set_resizable(GTK_WINDOW(widgets->window), FALSE);

    GtkWidget *main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_set_border_width(GTK_CONTAINER(main_box), 20);
    gtk_container_add(GTK_CONTAINER(widgets->window), main_box);

    GtkWidget *first_label = gtk_label_new("First Number:");
    gtk_box_pack_start(GTK_BOX(main_box), first_label, FALSE, FALSE, 5);
    
    widgets->first_entry = gtk_entry_new();
    gtk_entry_set_width_chars(GTK_ENTRY(widgets->first_entry), 30);
    gtk_box_pack_start(GTK_BOX(main_box), widgets->first_entry, FALSE, FALSE, 2);
    
    GtkWidget *operation_label = gtk_label_new("Operation:");
    gtk_box_pack_start(GTK_BOX(main_box), operation_label, FALSE, FALSE, 5);
    
    widgets->operation_combo = gtk_combo_box_text_new();
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(widgets->operation_combo), "+");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(widgets->operation_combo), "-");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(widgets->operation_combo), "*");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(widgets->operation_combo), "/");
    gtk_combo_box_set_active(GTK_COMBO_BOX(widgets->operation_combo), 0);
    gtk_box_pack_start(GTK_BOX(main_box), widgets->operation_combo, FALSE, FALSE, 2);

    GtkWidget *second_label = gtk_label_new("Second Number:");
    gtk_box_pack_start(GTK_BOX(main_box), second_label, FALSE, FALSE, 5);
    
    widgets->second_entry = gtk_entry_new();
    gtk_entry_set_width_chars(GTK_ENTRY(widgets->second_entry), 30);
    gtk_box_pack_start(GTK_BOX(main_box), widgets->second_entry, FALSE, FALSE, 2);

    widgets->calculate_button = gtk_button_new_with_label("Ponder!");
    g_signal_connect(widgets->calculate_button, "clicked", G_CALLBACK(on_calculate_clicked), widgets);
    g_signal_connect(widgets->calculate_button, "enter-notify-event", G_CALLBACK(on_button_enter), NULL);
    g_signal_connect(widgets->calculate_button, "leave-notify-event", G_CALLBACK(on_button_leave), NULL);
    gtk_box_pack_start(GTK_BOX(main_box), widgets->calculate_button, FALSE, FALSE, 15);
    
    widgets->result_label = gtk_label_new("Result: ");
    gtk_label_set_line_wrap(GTK_LABEL(widgets->result_label), TRUE);
    gtk_label_set_max_width_chars(GTK_LABEL(widgets->result_label), 40);
    gtk_box_pack_start(GTK_BOX(main_box), widgets->result_label, FALSE, FALSE, 5);

    gtk_widget_show_all(widgets->window);     
}

int main(int argc, char **argv) {
    srand(time(NULL));
    
    GtkApplication *app;
    int status;
    
    app = gtk_application_new("org.govnolabs.culculator", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    
    return status;
}