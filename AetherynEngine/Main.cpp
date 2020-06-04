// GENERAL IMPORTS
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <functional>
#include <queue>
#include <vector>
#include <string>
#include <thread>

// IMPORT MESSAGE BUS CLASSES
#include "BusNode.h"
#include "MessageBus.h"

// IMPORT CONSOLE CLASSES
#include "GUICon.h"
#include "Console.h"
#include "AddTimestamp.h"

Console console;
MessageBus messageBus;

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);


// TODO: MOVE THESE #####
class ComponentA : public BusNode
{
public:
	ComponentA(MessageBus* messageBus) : BusNode(messageBus) {}

private:
	void onNotify(Message message) {
		std::cout << "A: I received: " << message.getEvent() << std::endl;
		//std::string output;
		//message.getEvent >> output;
		//printf("A: I received: %d \n", message.getEvent());

	}
};

class ComponentB : public BusNode
{
public:
	ComponentB(MessageBus* messageBus) : BusNode(messageBus) {}

	void update() {
		Message greeting("Hi!");
		send(greeting);
	}
private:
	void onNotify(Message message) {
		std::cout << "B: I received: " << message.getEvent() << std::endl;
	}
};
// #####################


// Console function to run in thread alongside main game window
void console_thread() {

	// Attach timestamps to iostream -- attaches to every newline. Only call once.
	AddTimestamp ats(std::cout);

	// RedirectIOToConsole redirects functions like printf straight to the console. Only call once.
	RedirectIOToConsole();

	// Console input -------------------------------
	while (console.isActive()) {
		std::string cmd = console.getInput();
		if (cmd != "") console.parseCommand(cmd);
	}

}

int main() {

	// START CONSOLE THREAD
	std::thread consoleObj(console_thread);

	ComponentA compA(&messageBus);
	ComponentB compB(&messageBus);

	//for (int ctr = 0; ctr < 50; ctr++) {
	compA.update();
	compB.update();
	messageBus.notify();
	//}

	// GLFW: initialize and configure ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // fix compilation on OS X
#endif

	// GLFW window creation --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Aetheryn", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	std::cout << "Successfully created GLFW window." << std::endl;
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// glad: load all OpenGL function pointers ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	

	//MAIN GAME LOOP ------------------------------
	while (!glfwWindowShouldClose(window)) {
		
		// GLFW: INPUT -----
		processInput(window);

		// GLFW: RENDER ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// GLFW: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		glfwSwapBuffers(window);
		glfwPollEvents();

		

	}

	// GLFW: terminate, clearing all previously allocated GLFW resources. ----------------------------------------
	glfwTerminate();

	return 0;
}

// Process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly ------------------------
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

// GLFW: whenever the window size changed (by OS or user resize) this callback function executes ---------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}