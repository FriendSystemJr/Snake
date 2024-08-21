#include "RenderAPI.h"
#include "Snake.h";

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

	while(!Renderer::windowShouldClose()) {

		HandleInput((GLFWwindow*)Renderer::GetRenderWindow(), grid, snake);
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
	//int keys[] = { Renderer::InputHandler::KEY_W }; //Refactor (maybe in DLL?) to have every key automatically

	//TODO: Add docu
	AddKeyCheck(window, Renderer::InputHandler::KEY_W, std::bind(&Snake::Move, &snake, std::placeholders::_1, std::placeholders::_2), snake.UP, grid);
	AddKeyCheck(window, Renderer::InputHandler::KEY_D, std::bind(&Snake::Move, &snake, std::placeholders::_1, std::placeholders::_2), snake.RIGHT, grid);
	AddKeyCheck(window, Renderer::InputHandler::KEY_S, std::bind(&Snake::Move, &snake, std::placeholders::_1, std::placeholders::_2), snake.DOWN, grid);
	AddKeyCheck(window, Renderer::InputHandler::KEY_A, std::bind(&Snake::Move, &snake, std::placeholders::_1, std::placeholders::_2), snake.LEFT, grid);
}