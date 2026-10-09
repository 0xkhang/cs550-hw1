#include <GLFW/glfw3.h>

#include "mesh.h"
#include "vertex.h"
#include "edge.h"
#include "triangle.h"
#include "camera.h"

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <cstdio>

enum DisplayMode
{
	DISPLAY_WIREFRAME,
	DISPLAY_SILHOUETTE
};

static GLFWwindow *window;
static Mesh *mesh;
static Camera camera;

static glm::vec2 mouse_pos;

static DisplayMode display_mode = DISPLAY_WIREFRAME;

static void display();

static void on_resize(GLFWwindow *window, int width, int height);
static void on_key(GLFWwindow *window, int key, int scancode, int action, int mods);
static void on_mouse_motion(GLFWwindow *window, double xpos, double ypos);

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		printf("Usage: learnply2 <path>\n");
		return 1;
	}

	if (!glfwInit())
	{
		printf("glfwInit failed\n");
		return 1;
	}

	window = glfwCreateWindow(640, 480, "learnply2", nullptr, nullptr);
	if (!window)
	{
		glfwTerminate();
		printf("glfwCreateWindow failed\n");
		return 1;
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	glfwSetWindowSizeCallback(window, on_resize);
	glfwSetKeyCallback(window, on_key);
	glfwSetCursorPosCallback(window, on_mouse_motion);

	mesh = new Mesh(argv[1]);

	camera.reset();

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	camera.set_size(width, height);

	glfwShowWindow(window);
	display();
	while (!glfwWindowShouldClose(window))
		glfwWaitEvents();

	delete mesh;
	glfwTerminate();
	return 0;
}

static void display()
{
	glViewport(0, 0, camera.width(), camera.height());

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	const glm::mat4 &projection = camera.projection();
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(glm::value_ptr(projection));

	// TODO: modify the below lines to apply the mesh's model matrix to center and scale the
	// mesh to be in view
	const glm::mat4 &view = camera.view();
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(glm::value_ptr(view));

	switch (display_mode)
	{
	default:
		break;
	case DISPLAY_WIREFRAME: {
		glLineWidth(1.0f);

		glColor3f(0.0f, 0.0f, 0.0f);

		glBegin(GL_LINES);
		for (size_t i = 0; i < mesh->edges.size(); ++i)
		{
			Edge *e = mesh->edges[i];
			glVertex3fv(glm::value_ptr(e->vertices[0]->position));
			glVertex3fv(glm::value_ptr(e->vertices[1]->position));
		}
		glEnd();

		break;
	}
	case DISPLAY_SILHOUETTE: {
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);

		glColor3f(1.0f, 1.0f, 1.0f);

		// TODO: Render the mesh's triangles as solid white

		// TODO: Compute the 3x3 normal matrix
		// Hint: glm::mat3(glm::mat4) takes the 3x3 upper-left block of a 4x4 matrix
		// and glm::transpose/glm::inverse compute the transpose and inverse of a matrix, respectively

		glLineWidth(2.0f);
		glColor3f(0.0f, 0.0f, 0.0f);

		// TODO: Draw the silhouettes of the object as black lines
		// Hint: Compare the direction of view-space normals of triangles adjacent to each edge
		// w.r.t. the viewing direction (Camera::front).

		break;
	}
	}

	glfwSwapBuffers(window);
}

static void on_resize(GLFWwindow *window, int width, int height)
{
	camera.set_size(width, height);
	display();
}

static void on_key(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	switch (key)
	{
	default:
		break;
	case GLFW_KEY_ESCAPE:
		if (action == GLFW_PRESS)
			glfwSetWindowShouldClose(window, 1);
		break;
	case GLFW_KEY_R:
		if (action == GLFW_PRESS)
		{
			camera.reset();
			display();
		}
		break;
	case GLFW_KEY_1:
		if (action == GLFW_PRESS)
		{
			display_mode = DISPLAY_WIREFRAME;
			display();
		}
		break;
	case GLFW_KEY_2:
		if (action == GLFW_PRESS)
		{
			display_mode = DISPLAY_SILHOUETTE;
			display();
		}
		break;
	}
}

static void on_mouse_motion(GLFWwindow *window, double xpos, double ypos)
{
	const glm::vec2 new_pos(static_cast<float>(xpos), static_cast<float>(ypos));
	const glm::vec2 old_pos = mouse_pos;
	mouse_pos = new_pos;

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS)
	{
		camera.trackball(old_pos, new_pos);
		display();
	}
}
