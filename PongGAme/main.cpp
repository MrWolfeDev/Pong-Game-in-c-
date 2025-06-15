#include <iostream>
#include <raylib.h>

using namespace std;

// Define luxury theme colors
Color gold = { 255, 215, 0, 255 };
Color silver = { 192, 192, 192, 255 };
Color bronze = { 205, 127, 50, 255 };
Color semiTransparentWhite = { 255, 255, 255, 150 };

// Global score counters
int player_score = 0;
int AI_score = 0;

// Sound Effects
Sound paddleSound;
Sound borderSound;

// Ball class
class Ball {
public:
	float x, y;        // Ball position
	int speed_x, speed_y; // Ball speed
	int radius;        // Ball size

	// Draw the ball
	void Draw(Color color) {
		DrawCircle(x, y, radius, color);
	}

	// Update ball position and handle wall collisions
	void Update() {
		x += speed_x;
		y += speed_y;

		// If ball hits top or bottom border
		if (y + radius >= GetScreenHeight() || y - radius <= 0) {
			speed_y *= -1; // Reverse Y direction
			PlaySound(borderSound); // Play border hit sound
		}

		// Ball out of right side - AI scores
		if (x + radius >= GetScreenWidth()) {
			PlaySound(borderSound);
			AI_score++;
			ResetBall();
		}

		// Ball out of left side - Player scores
		if (x - radius <= 0) {
			PlaySound(borderSound);
			player_score++;
			ResetBall();
		}
	}

	// Reset ball to center with random direction
	void ResetBall() {
		x = GetScreenWidth() / 2;
		y = GetScreenHeight() / 2;

		int directions[2] = { -1, 1 };
		speed_x = 7 * directions[GetRandomValue(0, 1)];
		speed_y = 7 * directions[GetRandomValue(0, 1)];
	}
};

// Paddle class
class Paddle {
protected:
	// Keep paddle inside the screen
	void LimitMovement() {
		if (y + height >= GetScreenHeight()) y = GetScreenHeight() - height;
		if (y <= 0) y = 0;
	}

public:
	float x, y;         // Paddle position
	float width, height; // Paddle size
	int speed;          // Paddle speed

	// Draw the paddle with rounded corners
	void Draw(Color color) {
		DrawRectangleRounded(Rectangle{ x, y, width, height }, 0.4f, 10, color);
	}

	// Move paddle using arrow keys
	void Update() {
		if (IsKeyDown(KEY_UP)) y -= speed;
		if (IsKeyDown(KEY_DOWN)) y += speed;

		LimitMovement();
	}
};

// AI Paddle class that follows the ball
class AIPaddle : public Paddle {
public:
	void Update(int ball_y) {
		if (y + height / 2 > ball_y) y -= speed;
		if (y + height / 2 < ball_y) y += speed;

		LimitMovement();
	}
};

// Global objects
Ball ball;
Paddle player;
AIPaddle AI;

// Draw gradient background (top to bottom)
void DrawGradientBackground(Color topColor, Color bottomColor, int width, int height) {
	for (int y = 0; y < height; y++) {
		float t = (float)y / height;
		Color color = {
			(unsigned char)((1 - t) * topColor.r + t * bottomColor.r),
			(unsigned char)((1 - t) * topColor.g + t * bottomColor.g),
			(unsigned char)((1 - t) * topColor.b + t * bottomColor.b),
			255
		};
		DrawLine(0, y, width, y, color);
	}
}

int main() {
	cout << "Starting the game..." << endl;

	// Initialize game window
	const int Screen_Width = 1280;
	const int Screen_Height = 800;
	InitWindow(Screen_Width, Screen_Height, "Pong Game");
	SetTargetFPS(60);

	// Initialize ball
	ball.radius = 20;
	ball.x = Screen_Width / 2;
	ball.y = Screen_Height / 2;
	ball.speed_x = 7;
	ball.speed_y = 7;

	// Initialize player paddle
	player.width = 25;
	player.height = 120;
	player.x = Screen_Width - player.width - 10;
	player.y = Screen_Height / 2 - player.height / 2;
	player.speed = 8;

	// Initialize AI paddle
	AI.width = 25;
	AI.height = 120;
	AI.x = 10;
	AI.y = Screen_Height / 2 - AI.height / 2;
	AI.speed = 6;

	// Initialize audio
	InitAudioDevice();

	// Load background music and sound effects
	Music backgroundMusic = LoadMusicStream("assets/PongBGM.mp3");
	paddleSound = LoadSound("assets/paddle.mp3");
	borderSound = LoadSound("assets/boader.mp3");

	// Set volume: background lower, sound effects louder
	SetMusicVolume(backgroundMusic, 0.4f); // Background at 40%
	SetSoundVolume(paddleSound, 1.0f);      // Sound effects full volume
	SetSoundVolume(borderSound, 1.0f);

	PlayMusicStream(backgroundMusic); // Start background music

	// Game loop
	while (!WindowShouldClose()) {
		// Keep music playing smoothly
		UpdateMusicStream(backgroundMusic);

		// Start drawing
		BeginDrawing();

		// Check collision: ball hits player paddle
		if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, Rectangle{ player.x, player.y, player.width, player.height })) {
			ball.speed_x *= -1;
			PlaySound(paddleSound); // Play paddle hit sound
		}

		// Check collision: ball hits AI paddle
		if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, Rectangle{ AI.x, AI.y, AI.width, AI.height })) {
			ball.speed_x *= -1;
			PlaySound(paddleSound); // Play paddle hit sound
		}

		// Update game objects
		ball.Update();
		player.Update();
		AI.Update(ball.y);

		// Clear background
		ClearBackground(BLACK);

		// Draw gradient background
		DrawGradientBackground({ 10, 10, 60, 255 }, { 50, 10, 90, 255 }, Screen_Width, Screen_Height);

		// Draw center line
		DrawLine(Screen_Width / 2, 0, Screen_Width / 2, Screen_Height, semiTransparentWhite);

		// Draw objects
		ball.Draw(gold);
		AI.Draw(bronze);
		player.Draw(silver);

		// Draw scores
		DrawText(TextFormat("%i", AI_score), Screen_Width / 4 - 20, 20, 80, gold);
		DrawText(TextFormat("%i", player_score), 3 * Screen_Width / 4 - 20, 20, 80, gold);

		// Finish drawing
		EndDrawing();
	}

	// Clean up resources
	UnloadMusicStream(backgroundMusic);
	UnloadSound(paddleSound);
	UnloadSound(borderSound);
	CloseAudioDevice();

	// Close window
	CloseWindow();

	return 0;
}
