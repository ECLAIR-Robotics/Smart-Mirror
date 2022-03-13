//#define MONITOR_SIZE_X 1920
//#define MONITOR_SIZE_Y 1080
#define MONITOR_SIZE_X 1920
#define MONITOR_SIZE_Y 1017
#define HALF_MONITOR_X MONITOR_SIZE_X / 2
#define HALF_MONITOR_Y MONITOR_SIZE_Y / 2

// Time Widget Constants
#define TIME_W 2 * 260
#define TIME_H 2 * 100
#define TIME_X HALF_MONITOR_X - (TIME_W / 2)
#define TIME_Y HALF_MONITOR_Y - (4 * TIME_H / 2) - 5
#define CST (-6)

// News Widget Constants
#define NEWS_W 3 * 260
#define NEWS_H 4 * 100
#define NEWS_X HALF_MONITOR_X - (NEWS_W / 2)
#define NEWS_Y HALF_MONITOR_Y - (NEWS_H / 2)
#define POLY_MAX 180
#define POLY_MIN -180
#define POLY_SCALE POLY_MAX - POLY_MIN