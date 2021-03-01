/*
TODO:
      - Draw player as imported sprite
      - Make player drop bombs
      - Make bombs disappear after 5 seconds
      - Make player as animated sprite

COMPILATION: $ cc spriteMovement.c `pkg-config --libs --cflags raylib`
*/

#define MAX_WALLS 9

#include "raylib.h"

#define MAX_FRAME_SPEED 15
#define MIN_FRAME_SPEED 1

void PlayerMovement(int *framesCounter, Vector2 *position, int moveX, int moveY, int *framesSpeed, int *currentFrame, Rectangle *frameRec, Texture2D *playerTexture);

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------

    int currentFrame = 0;

    // This makes the walking animation possible
    int framesCounter = 0;
    int framesSpeed = 16;        // Number of spritesheet frames shown by second

    const int screenWidth = 602;
    const int screenHeight = 602;

    int playerX = 350;
    int playerY = 280;
    int moveX = 5;
    int moveY = 5;

    InitWindow(screenWidth, screenHeight, "raylib [texture] example - texture rectangle");
    Vector2 position = { playerX, playerY };
    Texture2D playerTexture = LoadTexture("golden_player.png");


    // This hides the other frames inside of my animation sprite sheet so that
    // our character won't look weird. Otherwise, we'd have more than one Henry on screen
    // and instead of animation, we'd be moving one big spritesheet.
    Rectangle frameRec = { 0.0f, 0.0f, (float)playerTexture.width/9, (float)playerTexture.height/4 };

    SetTargetFPS(60);           // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------

    // Main game loop
    //--------------------------------------------------------------------------
    while(!WindowShouldClose())        // Detect window close button or ESC key
    {
        // This makes the walking animation possible
        //--------------------------------------------------------------------------
        PlayerMovement(&framesCounter, &position, moveX, moveY, &framesSpeed, &currentFrame, &frameRec, &playerTexture);
        //--------------------------------------------------------------------------

        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawTextureRec(playerTexture, frameRec, position, WHITE);

        EndDrawing();
        //----------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------
    UnloadTexture(playerTexture);      // Texture unloading

    CloseWindow();              // Close window and OpenGL context
    //--------------------------------------------------------------------------

    return 0;
}

void PlayerMovement(int *framesCounter, Vector2 *position, int moveX, int moveY, int *framesSpeed, int *currentFrame, Rectangle *frameRec, Texture2D *playerTexture)
{
    (*framesCounter)++;
    if (IsKeyDown(KEY_RIGHT))
    {
        position->x += moveX;
        if (*framesCounter >= (60/(*framesSpeed)))
        {
            *framesCounter = 0;
            (*currentFrame)++;

            if ((*currentFrame) > 8) (*currentFrame) = 0;

            // This (for me) looks like an rectangle that acts like as
            // a magnifier.

            frameRec->x = (float)(*currentFrame)*(float)playerTexture->width/9;
            frameRec->y = 3.0f*(float)playerTexture->height/4;
        }
    }

    if (IsKeyDown(KEY_LEFT))
    {
        position->x -= moveX;
        if ((*framesCounter) >= (60/(*framesSpeed)))
        {
            *framesCounter = 0;
            (*currentFrame)++;

            if ((*currentFrame) > 8) (*currentFrame) = 0;

            frameRec->x = (float)(*currentFrame)*(float)playerTexture->width/9;
            frameRec->y = 1.0f*(float)playerTexture->height/4;
        }
    }

    if (IsKeyDown(KEY_UP))
    {
        position->y -= moveY;
        if ((*framesCounter) >= (60/(*framesSpeed)))
        {
            *framesCounter = 0;
            (*currentFrame)++;

            if ((*currentFrame) > 8) (*currentFrame) = 0;

            frameRec->x = (float)(*currentFrame)*(float)playerTexture->width/9;
            frameRec->y = 0.0f;
        }
    }

    if (IsKeyDown(KEY_DOWN))
    {
        position->y += moveY;
        if ((*framesCounter) >= (60/(*framesSpeed)))
        {
            *framesCounter = 0;
            (*currentFrame)++;

            if ((*currentFrame) > 8) (*currentFrame) = 0;

            frameRec->x = (float)(*currentFrame)*(float)playerTexture->width/9;
            frameRec->y = 2.0f*(float)playerTexture->height/4;
        }
    }
}
