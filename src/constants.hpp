#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <string>

static const int WINDOW_WIDTH = 800;        // Largo de la pantalla
static const int WINDOW_HEIGHT = 600;       // Ancho de la pantalla

// Archivo donde se encuentra el sprite de flecha
static const std::string ARROW_FILE = "content/arrow.png";
// Archivo donde se encuentra la fuente arial
static const std::string FONT_FILE = "content/arial.ttf";

static const float OUTPUT_POS_X = 30;       // Posicion x del texto de salida
static const float OUTPUT_POS_Y = 100;      // Posicion y del texto de salida
static const int OUTPUT_CHAR_SIZE = 12;     // Tamaño de fuente de la salida

static const float TITLE_POS_X = 30;        // Posicion x del texto del titulo
static const float TITLE_POS_Y = 30;        // Posicion y del texto del titulo
static const int TITLE_CHAR_SIZE = 30;      // Tamaño de fuente del titulo

// Posicion x del texto del titulo
static const float CREDITS_POS_X = WINDOW_WIDTH - 350;
// Posicion y del texto del titulo
static const float CREDITS_POS_Y = WINDOW_HEIGHT - 80;
static const int CREDITS_CHAR_SIZE = 15;    // Tamaño de fuente de los creditos

static const int RADIUS = 20;               // Radio de los vertices
static constexpr float DIST_CENTER = 200;   // Distancia desde el centro hacia los vertices
static const int CHAR_SIZE = 30;            // Tamaño de los caracteres

const double PI = 3.14159265358979323846;   // Constante del numero PI

#endif // CONSTANTS_HPP

