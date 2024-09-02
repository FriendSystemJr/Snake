#include "RenderAPI.h"
#include "Snake.h";
#include "Apple.h"

#include <unordered_map>
#include <functional>

void HandleInput(GLFWwindow* window, Renderer::Grid& grid, Snake& snake);
std::unordered_map<int, bool> keyStates;

enum GameState {
	START,
	GAME,
	END,
};

int main() {
	Renderer::Init(800, 800, "Snake");

	Renderer::Shader shader("shader/vertex.txt", "shader/fragment.txt");

	Renderer::Grid grid = Renderer::CreateGrid(20, 20);

	Renderer::BufferManager bufferManager(grid);

	bufferManager.SetGridStandard();

	Snake snake;

	Apple apple;
	
	bool test = false;

	apple.SetSpot(grid, snake);

	while(!Renderer::windowShouldClose()) {

		HandleInput((GLFWwindow*)Renderer::GetRenderWindow(), grid, snake);

		if (apple.GetSpot()[0] == -1) {
			apple.SetSpot(grid, snake);
		}

		snake.Move(grid);
		snake.CollisionDetect(apple);
		snake.SetPixels(grid);

		Renderer::RenderGrid(grid, shader);
	}
	
}

template<typename Func, typename... Args>
void AddKeyCheck(GLFWwindow* window, Renderer::InputHandler::KeyCode key, Func func, Args&&... args) {
	if (Renderer::InputHandler::GetKey(window, key) == Renderer::InputHandler::KEY_PRESSED) {
		if (!keyStates[key]) {
			func(std::forward<Args>(args)...);
			keyStates[key] = true;
		}
	} else if (Renderer::InputHandler::GetKey(window, key) == Renderer::InputHandler::KEY_RELEASED) {
		keyStates[key] = false;
	}
}

void HandleInput(GLFWwindow* window, Renderer::Grid& grid, Snake& snake) {

	//TODO: Add docu
	AddKeyCheck(window, Renderer::InputHandler::KEY_W, std::bind(&Snake::SetDirection, &snake, std::placeholders::_1), snake.UP);

	AddKeyCheck(window, Renderer::InputHandler::KEY_D, std::bind(&Snake::SetDirection, &snake, std::placeholders::_1), snake.RIGHT);

	AddKeyCheck(window, Renderer::InputHandler::KEY_S, std::bind(&Snake::SetDirection, &snake, std::placeholders::_1), snake.DOWN);

	AddKeyCheck(window, Renderer::InputHandler::KEY_A, std::bind(&Snake::SetDirection, &snake, std::placeholders::_1), snake.LEFT);
}