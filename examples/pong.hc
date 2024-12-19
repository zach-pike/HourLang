import Raylib;
import Math;

windowWidth = 800;
windowHeight = 800;

paddleWidth = 10;
paddleHeight = 100;
paddleOffset = paddleHeight / 2;

InitWindow(windowWidth, windowHeight, "Pong");
SetTargetFPS(60);

player1 = 400;
player1Pts = 0;

player2 = 400;
player2Pts = 0;

ballX = 400;
ballY = 400;

ballMoveSpeed = 8;
ballSize = 10;

ballVelX = 0;
ballVelY = 0;

pongImg = LoadImage("examples/pong.png");
SetWindowIcon(pongImg);

function resetBall() {
    ballX = 400;
    ballY = 400;

    if (randInt(0, 1) == 0) {
        ballVelX = -ballMoveSpeed;
    } else {
        ballVelX = ballMoveSpeed;
    }
    ballVelY = 0.0;
}

function resetPlayers() {
    player1 = 400;
    player2 = 400;
}

resetBall();

while (not WindowShouldClose()) {
    BeginDrawing();

    ClearBackground(BLACK);

    // Player1
    DrawRectangle(0, player1 - paddleOffset, paddleWidth, paddleHeight, WHITE);
    DrawText(string(player1Pts), 50, 50, 25, WHITE);

    // player2
    DrawRectangle(windowWidth - paddleWidth, player2 - paddleOffset, paddleWidth, paddleHeight, WHITE);
    DrawText(string(player2Pts), windowWidth - 50, 50, 25, WHITE);

    // Ball
    DrawRectangle(ballX - (ballSize / 2), ballY - (ballSize / 2), ballSize, ballSize, WHITE);

    EndDrawing();

    // Set ball position
    ballX += ballVelX;
    ballY += ballVelY;

    // Player 1 movement
    if (IsKeyDown(KEY_S)) {
        player1 = min(player1 + 5, windowHeight - paddleOffset);
    }

    if (IsKeyDown(KEY_W)) {
        player1 = max(player1 - 5, paddleOffset);
    }

    // Player 2 movement
    if (ballX >= 780) {
        player2 = player2 + randInt(-10, 10);
    } else {
        if (player2 < ballY) {
            player2 = min(player2 + 5, windowHeight - paddleOffset);
        }

        if (player2 > ballY) {
            player2 = max(player2 - 5, paddleOffset);
        }
    }

    // Check collision
    if (ballX <= paddleWidth) {
        // Check that ball is within the paddles pos
        paddleMinY = player1 - paddleOffset;
        paddleMaxY = player1 + paddleOffset;

        paddleStrike = false;
        if (ballY >= paddleMinY) {
            if (ballY <= paddleMaxY) {
                // We have a paddle strike
                paddleStrike = true;

                strike = float(ballY - player1);
                strike /= paddleOffset;

                ballVelY = ballMoveSpeed * strike;
                ballVelX = sqrt((ballMoveSpeed * ballMoveSpeed) - (ballVelY * ballVelY));
            }
        }

        if (not paddleStrike) {
            player2Pts += 1;

            resetBall();
            resetPlayers();
        }
    }

    if (ballX >= (windowWidth - paddleWidth)) {
        
        // Check that ball is within the paddles pos
        paddleMinY = player2 - paddleOffset;
        paddleMaxY = player2 + paddleOffset;

        paddleStrike = false;
        if (ballY >= paddleMinY) {
            if (ballY <= paddleMaxY) {
                // We have a paddle strike
                paddleStrike = true;

                strike = float(ballY - player2);
                strike /= paddleOffset;

                ballVelY = ballMoveSpeed * strike;
                ballVelX = -sqrt((ballMoveSpeed * ballMoveSpeed) - (ballVelY * ballVelY));
            }
        }

        if (not paddleStrike) {
            player1Pts += 1;

            resetBall();
            resetPlayers();
        }
    }

    if ((ballY <= 0) || (ballY >= windowHeight)) {
        ballVelY *= -1;
    }
}

CloseWindow();