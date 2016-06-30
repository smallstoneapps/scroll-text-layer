#include <pebble.h>
#include <@smallstoneapps/scroll-text-layer/scroll-text-layer.h>

static void init(void);
static void deinit(void);
static void window_load(Window* window);
static void window_unload(Window* window);
static void click_config_provider(void *context);
static void select_click_handler(ClickRecognizerRef recognizer, void *context);

static Window *window;
static ScrollTextLayer* layer;

#define NUM_FONTS 6

static char* fonts[6] = {
  FONT_KEY_GOTHIC_18,
  FONT_KEY_GOTHIC_18_BOLD,
  FONT_KEY_GOTHIC_24,
  FONT_KEY_GOTHIC_24_BOLD,
  FONT_KEY_GOTHIC_28,
  FONT_KEY_GOTHIC_28_BOLD,
};

uint8_t font = 0;

static char* text = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed quis nisi eget mauris vulputate interdum et at libero. Integer scelerisque, metus a cursus viverra, justo dui volutpat quam, ac bibendum orci lectus sed tellus. Maecenas congue quis sapien sit amet sodales. Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac turpis egestas. Etiam non neque eget augue scelerisque posuere. Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac turpis egestas. Proin euismod dui eget convallis fermentum. Praesent vitae aliquet libero. Maecenas pulvinar, est at elementum laoreet, sem metus ullamcorper tortor, laoreet lacinia nibh massa at sapien. Phasellus placerat elementum malesuada. Aenean convallis odio dui, id consequat turpis aliquam eget. Donec auctor odio ac laoreet ornare.";

int main(void) {
  init();
  app_event_loop();
  deinit();
}

static void init(void) {
  window = window_create();
  window_set_window_handlers(window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload,
  });
  window_stack_push(window, true);
}

static void deinit(void) {
  window_destroy(window);
}

static void window_load(Window *window) {
  layer = scroll_text_layer_create_fullscreen(window);
  scroll_text_layer_set_text(layer, text);
  scroll_text_layer_set_system_font(layer, fonts[font]);
  scroll_text_layer_add_to_window(layer, window);
  scroll_text_layer_set_callbacks(layer, (ScrollLayerCallbacks) {
    .click_config_provider = click_config_provider
  });
}

static void window_unload(Window *window) {
  scroll_text_layer_destroy(layer);
}

static void click_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
}

static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
  font += 1;
  if (font >= NUM_FONTS) {
    font = 0;
  }
  scroll_text_layer_set_system_font(layer, fonts[font]);
}
