import Raylib;
import Math;

InitWindow(800, 800, "Boids");

boidsTexture = LoadTexture("examples/boids.png");

function createBoid(x, y, xvel, yvel) {
    return {
        pos: Vector2(x, y),
        vel: Vector2(xvel, yvel)
    };
}

boidList = [];

boidList = append(boidList, createBoid(100, 100, 5, 5));

while(not WindowShouldClose()) {
    BeginDrawing();

    ClearBackground(Color(138, 192, 255, 255));

    for (i=0; i<size(boidList); i += 1;) {
        DrawTextureEx(boidsTexture, get(boidList, i).pos, 0, 0.2, WHITE);
    } 


    EndDrawing();
}

CloseWindow();