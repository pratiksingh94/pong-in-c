#include <stddef.h>
#include <stdio.h>
#include "raylib.h"


// we are friends if you know the reference of 640x480
const size_t SCREEN_X = 640;
const size_t SCREEN_Y = 480;
const size_t SCREEN_FPS = 60;

int main()
{
  printf("Starting pong...\n");
  
  SetTargetFPS(SCREEN_FPS);
  InitWindow(SCREEN_X, SCREEN_Y, "Pong :3");

  // ball and those left and right bar positions
  Vector2 leftBarPos = { 0.0, (float)SCREEN_Y/2 - 90 };
  Vector2 rightBarPos = { (float)SCREEN_X - 20, (float)SCREEN_Y/2 - 90 };
  const Vector2 barSize = { 20.0, 180.0 };

  Vector2 ballPos = { (float)SCREEN_X/2, (float)SCREEN_Y/2 };
  int ballDX = 4;
  int ballDY = 3;

  // score and game state dead or alive
  int dead = 0;
  int score = 0;

  while (!WindowShouldClose()) {
    BeginDrawing();

    ClearBackground(BLACK);
    DrawFPS(SCREEN_X - 100, 20);

    // some texts and score display
    int titleSize = MeasureText("Pong :)", 40);
    int githubSize = MeasureText("GitHub: pratiksingh94/pong-in-c", 20);
    int scoreSize = MeasureText(TextFormat("Score: %d", score), 30);
    DrawText("Pong :)", (SCREEN_X - titleSize) / 2, 20, 40, WHITE);
    DrawText("GitHub: pratiksingh94/pong-in-c", (SCREEN_X - githubSize) / 2, SCREEN_Y - 30, 20, WHITE);
    DrawText(TextFormat("Score: %d", score), 30, 30, 30, BLUE);

    // you are doomed
    if(dead == 1) {
      int msgSize = MeasureText("This game requires one brain cell and you still", 20);
      int lostSize = MeasureText("LOST", 50);
      DrawText("This game requires one brain cell and you still", (SCREEN_X - msgSize) / 2, (SCREEN_Y/2) - 40, 20, WHITE);
      DrawText("LOST", (SCREEN_X - lostSize)/2, SCREEN_Y/2, 50, RED);
    }

    DrawRectangleV(leftBarPos, barSize, WHITE);
    DrawRectangleV(rightBarPos, barSize, WHITE);

    // handling keyboard input and clamping bars inside screen
    if (IsKeyDown(KEY_W)) leftBarPos.y -= 5.0f;
    if (IsKeyDown(KEY_S)) leftBarPos.y += 5.0f;

    if (leftBarPos.y < 0) leftBarPos.y = 0;
    if (leftBarPos.y > SCREEN_Y - barSize.y) leftBarPos.y = SCREEN_Y - barSize.y;

    if (IsKeyDown(KEY_UP)) rightBarPos.y -= 5.0f;
    if (IsKeyDown(KEY_DOWN)) rightBarPos.y += 5.0f;

    if (rightBarPos.y < 0) rightBarPos.y = 0;
    if (rightBarPos.y > SCREEN_Y - barSize.y) rightBarPos.y = SCREEN_Y - barSize.y;


    DrawCircleV(ballPos, 22, dead == 0 ? WHITE : RED);

    // ball movement and collision check
    if(dead != 1) {
      ballPos.x += ballDX;
      ballPos.y += ballDY;
    }
    if(ballPos.y <= 0 || ballPos.y >= SCREEN_Y) {
      ballDY *= -1;
    }

    Rectangle leftBar = { leftBarPos.x, leftBarPos.y, barSize.x, barSize.y };
    Rectangle rightBar = { rightBarPos.x, rightBarPos.y, barSize.x, barSize.y };
    if(dead == 0 && (CheckCollisionCircleRec(ballPos, 22, leftBar) || CheckCollisionCircleRec(ballPos, 22, rightBar))) {
      ballDX *= -1;
      score += 1;
      // printf("DX: %d, DY: %d, X: %f, Y: %f, score: %d\n", ballDX, ballDY, ballPos.x, ballPos.y, score);
    }

    if(ballPos.x <= 0 || ballPos.x >= SCREEN_X) {
      dead = 1;
    }

    EndDrawing();
  }

  CloseWindow(); // bye twin

  return 0;
}
