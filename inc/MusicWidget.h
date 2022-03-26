//#include <iostream>
//#include <string>

#define MAX_CIRCLES  64
#define MAX_RECTANGLES  16

#include <cstring>
#include <string>
#include "Widget.h"
#include <raylib.h>
#include <iostream>
#include "Constants.h"
#include <vector>

typedef struct {
    Vector2 position;
    float radius;
    float alpha;
    float speed;
    Color color;
} CircleWave;

typedef struct {
    Vector2 position;
    float alpha;
    int height;
    float speed;
} RecWave;

typedef struct {
    
} CurrentRecPos;


class MusicWidget : public Widget {

public:
    MusicWidget(uint32_t x, uint32_t y, uint32_t w, uint32_t h, string n) :
        Widget (x, y, w, h, n) {
        // Calls widget's constructor
        //render = false;
        
    }
    
    void draw() override {
        const int screenWidth = 800;
    const int screenHeight = 450;

    SetConfigFlags(FLAG_MSAA_4X_HINT);  // NOTE: Try to enable MSAA 4X

    InitWindow(screenWidth, screenHeight, "raylib [audio] example - module playing (streaming)");

    InitAudioDevice();                  // Initialize audio device

    Color colors[7] = { BLUE, VIOLET, LIGHTGRAY, DARKBLUE, SKYBLUE, PURPLE, DARKPURPLE };
                         

    // Creates some circles for visual effect
    CircleWave circles[MAX_CIRCLES] = { 0 };

    for (int i = MAX_CIRCLES - 1; i >= 0; i--)
    {
        circles[i].alpha = 0.0f;
        circles[i].radius = (float)GetRandomValue(10, 40);
        circles[i].position.x = (float)GetRandomValue((int)circles[i].radius, (int)(screenWidth - circles[i].radius));
        circles[i].position.y = (float)GetRandomValue((int)circles[i].radius, (int)(screenHeight - circles[i].radius));
        circles[i].speed = (float)GetRandomValue(1, 100)/2000.0f;
        circles[i].color = colors[GetRandomValue(0, 6)];
    }
    
    // Rectangles for visual effect
    RecWave rectangles[MAX_RECTANGLES] = { 0 };
    RecWave storedRectangles[MAX_RECTANGLES] = { 0 };
    
    int x_int = 5;
    for (int i = MAX_RECTANGLES - 1; i >= 0; i--) {
    //int posX, int posY, int width, int height, Color color1, Color color2
        rectangles[i].alpha= 0.0f;
        rectangles[i].position.x = x_int;
        rectangles[i].position.y = (float) GetRandomValue(0, 430);
        rectangles[i].height = 430 - rectangles[i].position.y;
        rectangles[i].speed = (float)GetRandomValue(1, 100)/2000.0f;
        x_int += 50;
    }

    //std::string m = " "; 
    //cout << "Type a music choice (country.mp3, mini1111.xm: ";
    //cin >> m; // Get user input from the keyboard
    //cout << "Your number is: " << x; // Display the input value
    
    Music music = LoadMusicStream("resources/mini1111.xm");
    music.looping = false;
    float pitch = 1.0f;

    PlayMusicStream(music);

    float timePlayed = 0.0f;
    bool pause = false;
    
    int count = 0;

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        UpdateMusicStream(music);      // Update music buffer with new stream data

        // Restart music playing (stop and play)
        if (IsKeyPressed(KEY_SPACE))
        {
            StopMusicStream(music);
            PlayMusicStream(music);
        }

        // Pause/Resume music playing
        if (IsKeyPressed(KEY_P))
        {
            pause = !pause;

            if (pause) PauseMusicStream(music);
            else ResumeMusicStream(music);
        }

        if (IsKeyDown(KEY_DOWN)) {
            pitch -= 0.01f;
            
        }
        else if (IsKeyDown(KEY_UP)) {
            pitch += 0.01f;
        }

        SetMusicPitch(music, pitch);

        // Get timePlayed scaled to bar dimensions
        timePlayed = GetMusicTimePlayed(music)/GetMusicTimeLength(music)*(screenWidth - 40);

        // Color circles animation
        for (int i = MAX_CIRCLES - 1; (i >= 0) && !pause; i--)
        {
            circles[i].alpha += circles[i].speed;
            circles[i].radius += circles[i].speed*10.0f;

            if (circles[i].alpha > 1.0f) circles[i].speed *= -1;

            if (circles[i].alpha <= 0.0f)
            {
                circles[i].alpha = 0.0f;
                circles[i].radius = (float)GetRandomValue(10, 40);
                circles[i].position.x = (float)GetRandomValue((int)circles[i].radius, (int)(screenWidth - circles[i].radius));
                circles[i].position.y = (float)GetRandomValue((int)circles[i].radius, (int)(screenHeight - circles[i].radius));
                circles[i].color = colors[GetRandomValue(0, 6)];
                circles[i].speed = (float)GetRandomValue(1, 100)/2000.0f;
            }
        }

        // Color rectangles animation
         for (int i = MAX_RECTANGLES - 1; (i >= 0) && !pause; i--)
        {
            rectangles[i].alpha = rectangles[i].speed;
            // ypos + height = 430
            rectangles[i].position.y = GetRandomValue(200, 390);//rectangles[i].speed*10.0f;
            rectangles[i].height = 430 - rectangles[i].position.y;
           

            if (rectangles[i].alpha > 1.0f) rectangles[i].speed *= -1;

            if (rectangles[i].alpha <= 0.0f)
            {
                rectangles[i].alpha= 0.0f;
                rectangles[i].position.y = (float) GetRandomValue(0, 430);
                rectangles[i].height = 430 - rectangles[i].position.y;
                rectangles[i].speed = (float) GetRandomValue(1, 2)/100000.0f;
                rectangles[i].position.x = x_int;
                x_int += 50;
            }
            
        }
        //----------------------------------------------------------------------------------
       

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(BLACK);

            // Draw Circles
            for (int i = MAX_CIRCLES - 1; i >= 0; i--)
            {
                DrawCircleLines(circles[i].position.x, circles[i].position.y, circles[i].radius, Fade(circles[i].color, circles[i].alpha));
            }
            
            
            // Draw Rectangles 
            if (count % 5 == 0) {
                for (int i = MAX_RECTANGLES - 1; i >= 0; i--) {
                    DrawRectangleGradientV(rectangles[i].position.x, rectangles[i].position.y, screenWidth/20, rectangles[i].height, PURPLE, DARKBLUE);
                }
            } else {
                // store and use previous values
                
                }
            }
            
            count++;
            
            

            // Draw time bar
            DrawRectangle(20, screenHeight - 20 - 12, screenWidth - 40, 12, WHITE);
            DrawRectangle(20, screenHeight - 20 - 12, (int)timePlayed, 12, MAROON);
            DrawRectangleLines(20, screenHeight - 20 - 12, screenWidth - 40, 12, BLACK);
           

        EndDrawing();
        
    


    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadMusicStream(music);          // Unload music stream buffers from RAM

    CloseAudioDevice();     // Close audio device (music streaming is automatically stopped)

    CloseWindow();          // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    
    }

private:
   
};
