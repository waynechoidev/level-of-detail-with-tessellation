#define STB_IMAGE_IMPLEMENTATION
#include <filesystem>
#include "stb_image.h"

#include "window.h"
#include "gui.h"
#include "program.h"
#include "sphere.h"
#include "texture.h"
#include "camera.h"

int main()
{
	Window mainWindow = Window(1920, 1080);
	mainWindow.initialise();

	Gui gui = Gui();
	gui.initialise(mainWindow.getWindow());

	Sphere sphere = Sphere(1.0f, 20, 20);
	sphere.initialise();

	std::filesystem::path currentDir = std::filesystem::path(__FILE__).parent_path();

	Program mainProgram = Program();
	mainProgram.createFromFiles(currentDir / "shaders/vert.glsl", currentDir / "shaders/tess-control.glsl",
								currentDir / "shaders/tess-evaluation.glsl", currentDir / "shaders/frag.glsl");
	mainProgram.genVertexBuffers();
	mainProgram.genFragmentBuffers();

	Texture earthTexture = Texture();
	earthTexture.initialise(currentDir / "textures/map.jpg");

	// Model
	glm::vec3 translation = glm::vec3(0.0f);
	glm::vec3 scaling = glm::vec3(0.7f);
	glm::vec3 rotation = {0.4f, 2.5f, 0.0f};

	// Projection
	float aspectRatio = (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight();
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 100.0f);

	Camera camera = Camera(glm::vec3(0.0f, 0.0f, 2.5f), glm::vec3{0.0f, 1.0f, 0.0f}, glm::vec3(0.0f, 0.0f, -1.0f));

	// Material
	Material material;
	material.ambient = 0.1f;
	material.shininess = 1.0f;
	material.diffuse = 1.0f;
	material.specular = 1.0f;

	// Light
	Light light;
	light.position = {0.0f, 0.0f, 2.0f};
	light.direction = {0.0f, 0.0f, -1.0f};
	light.strength = 1.0;
	light.fallOffStart = 0.0f;
	light.fallOffEnd = 10.0f;
	light.spotPower = 1.0f;
	light.isDirectional = 1;
	light.isPoint = 0;
	light.isSpot = 0;
	light.useBlinnPhong = true;

	// Control
	bool useTexture = true;
	bool wireFrame = true;

	while (!mainWindow.getShouldClose())
	{
		glfwPollEvents();

		gui.update(useTexture, wireFrame, translation.x, scaling.x, rotation.x, material, light);

		mainWindow.clear(0.0f, 0.0f, 0.0f, 1.0f);

		glPolygonMode(GL_FRONT_AND_BACK, wireFrame ? GL_LINE : GL_FILL);

		// Model
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(translation.x, translation.y, translation.z));
		model = glm::scale(model, scaling);
		model = glm::rotate(model, rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));

		mainProgram.use();
		mainProgram.bindVertexBuffers(model, projection, camera.calculateViewMatrix());
		mainProgram.bindFragmentBuffers(useTexture, camera.getPosition(), translation.z, material, light);
		earthTexture.use();
		sphere.draw();
		gui.render();

		glUseProgram(0);

		mainWindow.swapBuffers();
	}

	return 0;
}