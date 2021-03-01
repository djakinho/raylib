/*
TODO:
      - Make games logic insidefunctions
      - Draw player as imported sprite
      - Make player drop bombs
      - Make bombs disappear after 5 seconds
      - Make player as animated sprite

COMPILATION: $ cc bomberman.c `pkg-config --libs --cflags raylib`
*/

#define MAX_WALLS 9

#include "raylib.h"

void MovePlayer(Rectangle *player);

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------
    const int screenWidth = 602;        // 640
    const int screenHeight = 602;

    InitWindow(screenWidth, screenHeight, "raylib [Djakson] game - BomberMan");

    Rectangle player = { 43, 43, 60, 60 };  // Player's x, y, w, h

    Rectangle walls[MAX_WALLS] = { 0 };  // List of Walls to be placed

    int counter = 0;    // Walls to be placed
    for (int i = 86; i < screenWidth; i += 172)
    {
        for (int j = 86; j < screenHeight; j += 172)
        {
            walls[counter].x = i;
            walls[counter].y = j;
            walls[counter].width = 86;
            walls[counter].height = 86;
            counter++;
        }
    }

    Rectangle boxCollision = { 0 }; // Collision rectangle

    bool collision = false;     // Collision detection

    SetTargetFPS(60);           // Set our game to run at 60 framer-per-second
    //--------------------------------------------------------------------------

    // Main game loop
    //--------------------------------------------------------------------------
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //--------------------------------------------------------------------------


        // Make sure the player doesn't go off the bounds
        if ((player.x + player.width) >= GetScreenWidth()) player.x = GetScreenWidth() - player.width;
        else if (player.x <= 0) player.x = 0;

        if ((player.y + player.height) >= GetScreenHeight()) player.y = GetScreenHeight() - player.height;
        else if (player.y <= 0) player.y = 0;

        // Collision blocks loop
        //------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        for (int i = 0; i < MAX_WALLS; i++)
        {
            collision = CheckCollisionRecs(player, walls[i]);
            if (collision) boxCollision = GetCollisionRec(player, walls[i]);

            int collisionArea = (int)boxCollision.width*(int)boxCollision.height;
            // Collision Area: %i", (int)boxCollision.width*(int)boxCollision.height
            if (collision)
            {
                if (((boxCollision.width <= boxCollision.height) && boxCollision.x == walls[i].x) && ((player.x + player.width) >= walls[i].x)) player.x = walls[i].x - player.width;
                else if ((boxCollision.width <= boxCollision.height) && (player.x <= (walls[i].x + walls[i].width))) player.x = (walls[i].x + walls[i].width) + boxCollision.width;


                else if (((boxCollision.width > boxCollision.height) && boxCollision.y == walls[i].y) && ((player.y + player.height) >= walls[i].y)) player.y = walls[i].y - player.height;
                else if ((boxCollision.width > boxCollision.height) && (player.y <= (walls[i].y + walls[i].height))) player.y = (walls[i].y + walls[i].height) + boxCollision.height;
            }
        }
        //------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

        // Move the [ball] player
        MovePlayer(&player);

        //--------------------------------------------------------------------------

        // Draw
        //--------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            // Draw walls
            for (int i = 0; i < MAX_WALLS; i++) DrawRectangleRec(walls[i], MAROON);

            DrawRectangleRec(player, SKYBLUE);

            DrawText(TextFormat("boxCollision x: %.2f, boxCollision y: %.2f", boxCollision.x, boxCollision.y), 0, 0, 25, BLACK);

            // for (int i = 0; i < MAX_WALLS; i++) if (collision) DrawRectangleRec(boxCollision, LIME);

        EndDrawing();
    }

    // De-Initialization
    //--------------------------------------------------------------------------
    CloseWindow();              // close window and OpenGL context
    //--------------------------------------------------------------------------

    return 0;
}

void MovePlayer(Rectangle *player)
{
    if (IsKeyDown(KEY_LEFT)) player->x -= 4.0f;
    if (IsKeyDown(KEY_RIGHT)) player->x += 4.0f;
    if (IsKeyDown(KEY_UP)) player->y -= 4.0f;
    if (IsKeyDown(KEY_DOWN)) player->y += 4.0f;
}
