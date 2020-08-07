
#include "GameApp.h"
#include "raylib.h"

GameApp::GameApp() : m_screenWidth(), m_screenHeight(), m_tileWidth(), m_tileHeight(), m_pacPos(), m_pacDir(), m_pacSpeed()
{

}
GameApp::~GameApp()
{

}

void GameApp::Startup()
{
    InitWindow(m_screenWidth, m_screenHeight, "raylib [core] example - basic window");
    SetTargetFPS(60);

    CloseWindow();
}

void GameApp::Run()
{
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        Update();
        Draw();
    }
}

void GameApp::Update()
{
    //if (IsKeyPressed(KEY_UP))
    //{
    //    m_pacDir = { 0, -1 };

    //}
    //if (IsKeyPressed(KEY_DOWN))
    //{
    //    m_pacDir = { 0, 1 };
    //}
    //if (IsKeyPressed(KEY_LEFT))
    //{
    //    m_pacDir = { -1, 0 };
    //}
    //if (IsKeyPressed(KEY_RIGHT))
    //{
    //    m_pacDir = { 1, 0 };
    //}
}
void GameApp::Draw()
{
    BeginDrawing();

    ClearBackground(BLACK);

    // DrawRectangle(100, 100, 100, 100, Color({ 0, 0, 0, 255 }));
    EndDrawing();
}

