#include "RenderAPI.h"
#include "Snake.h";
#include "Apple.h"

#include <unordered_map>
#include <functional>

void HandleInput(GLFWwindow* window, Renderer::Grid& grid, Snake& snake);
std::unordered_map<int, bool> keyStates;

int main() {
	Renderer::Init(800, 800, "Snake");

	Renderer::Shader shader("shader/vertex.txt", "shader/fragment.txt");

	Renderer::Grid grid = Renderer::CreateGrid(20, 20);

	Renderer::BufferManager bufferManager(grid);

	bufferManager.SetGridStandard();

	Snake snake;

	Apple apple;

	apple.SetSpot(grid, snake);

	while(!Renderer::windowShouldClose()) {

		HandleInput((GLFWwindow*)Renderer::GetRenderWindow(), grid, snake);

		//Check if apple is set, if not (when index 0 is -1) set new spot
		if (apple.GetSpot()[0] == -1) {
			apple.SetSpot(grid, snake);
		}

		//At the start of the game wait until the state changes
		if (snake.GetState() == snake.START) {
			snake.SetPixels(grid);
			Renderer::RenderGrid(grid, shader);
			continue;
		}

		//normal game loop
		if (snake.GetState() == snake.GAME) {
		snake.Move(grid);
		snake.CollisionDetect(apple);
		snake.SetPixels(grid);

		Renderer::RenderGrid(grid, shader);
		}

		//End logic (refactor so that restart occurs through InputHandler when State is END)
		if (snake.GetState() == snake.END) {
			std::cout << "Your size was: " << snake.GetPoints().size() << "\n";
			std::cout << "Press any key for restart!\n";
			std::cin.get();

			//TODO: Refactor (add clear method for grid in dll)
			for (int i = 0; i < snake.GetPoints().size(); ++i) {
				grid.UnsetPixel(std::get<0>(snake.GetPoints()[i]), std::get<1>(snake.GetPoints()[i]));
			}

			snake.GetPoints().clear();
			snake = Snake();

			grid.UnsetPixel(apple.GetSpot()[0], apple.GetSpot()[1]);
			apple.GetSpot()[0] = -1;

		}

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