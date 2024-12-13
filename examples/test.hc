import Raylib;
import Math;

InitWindow(800, 800, "Window");
SetTargetFPS(60);

white = Color(255, 255, 255, 255);
red = Color(255, 0, 0, 255);

xd = 6.5;
yd = 7;

x = 100;
y = 100;

while (not WindowShouldClose()) {
    BeginDrawing();

    ClearBackground(white);

    DrawRectangle(x, y, 50, 50, red);

    x = x + xd;
    y = y + yd;

    ct = 0;

    if(x >= 750){
        xd = xd * -1;
        ct += 1;
    }

    if(y >= 750){
        yd = yd * -1;
        ct += 1;
    }

    if(x <= 0){
        xd = xd * -1;
        ct += 1;
    }
    
    if(y <= 0){
        yd = yd * -1;
        ct += 1;
    }

    if (ct == 2) {
        println("CORNER HIT!");
    }

    EndDrawing();
}

CloseWindow();