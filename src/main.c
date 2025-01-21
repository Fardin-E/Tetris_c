#include "header.h"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 900;
    const int screenHeight = 800;

    // Initialize window
    InitWindow(screenWidth, screenHeight, "Tetris");

    Vector2 buttonPosition = { 50.0f, 50.0f };
    Rectangle button = { buttonPosition.x, buttonPosition.y, 100.0f, 100.0f };
    int count = 0;

    SetTargetFPS(60);  // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            // Increment count when mouse button is pressed
            count++;
        }

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            // Get the current mouse position
            buttonPosition = GetMousePosition();
            button.x = buttonPosition.x - button.width / 2;
            button.y = buttonPosition.y - button.height / 2;
            //----------------------------------------------------------------------------------
        }

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);  // Clear the screen with a white color

        // Draw button and text
        DrawRectangleRec(button, RED);
        DrawRectangleLinesEx(button, 2.0f, BLACK);
        DrawText(TextFormat("Count value: %d", count), 10, 20, 20, DARKGRAY);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();  // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
