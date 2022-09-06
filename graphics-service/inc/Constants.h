#include <raylib.h>

//#define MONITOR_SIZE_X 1920
//#define MONITOR_SIZE_Y 1080
#define MONITOR_SIZE_X 1536
#define MONITOR_SIZE_Y 864
#define HALF_MONITOR_X MONITOR_SIZE_X / 2
#define HALF_MONITOR_Y MONITOR_SIZE_Y / 2

// Time Widget Constants
#define TIME_W 2 * 260
#define TIME_H 2 * 100
#define TIME_X HALF_MONITOR_X - (TIME_W / 2)
#define TIME_Y HALF_MONITOR_Y - (4 * TIME_H / 2) - 5
#define CST -5


// Weather Widget Constants
#define WEATHER_W 150
#define WEATHER_H 150
#define WEATHER_X 75  
#define WEATHER_Y 75
#define AUSTIN_LATITUDE 30.2849
#define AUSTIN_LONGITUDE -97.7341
#define WEATHER_API "dfe9e7d6202c6f8719e0149ecdff6a62"

// News Widget Constants
#define NEWS_W 3 * 260
#define NEWS_H 4 * 100
#define NEWS_X HALF_MONITOR_X - (NEWS_W / 2)
#define NEWS_Y HALF_MONITOR_Y - (NEWS_H / 2)
#define POLY_MAX 180
#define POLY_MIN -180
#define POLY_SCALE POLY_MAX - POLY_MIN

//Calcuator widget Constants
#define CALC_W 200
#define CALC_H 500
#define CALC_X WEATHER_X
#define CALC_Y WEATHER_Y + WEATHER_H + 50

// Shader Information
#define GLSL_VERSION 100

// Color scheme
#define MAIN_COLOR SKYBLUE