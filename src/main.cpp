#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include "GLFW/glfw3.h"
#include "GL/freeglut.h"
#include "../include/objreader.h"
using std::cout, std::cerr;

constexpr float WIDTH{1080.0f};
constexpr float HEIGHT{720.0f};

int InitWindow();
void InitOpenGL();
void Display();
void renderText(const std::string& msg, float x, float y);

GLFWwindow* window;

std::list<Model> models;

int main() {
	if (InitWindow() < 0) return -1;

    // Read the .obj file
    if (!objr::readObj(models)) {
        cerr << "[ERROR] Failed to read the models\n";
        glfwTerminate();
        return -1;
    }

    clock_t initialTime, finalTime;
    double timeElapsed{0.0};
    std::string msg;
    int fps{};
	do {
        if(fps == 0) 
			initialTime = clock();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the screen
		
        Display();

		// Displays on the window current fps
        ++fps;
        finalTime = clock() - initialTime;
        timeElapsed += (static_cast<double>(finalTime) / CLOCKS_PER_SEC);
        if(timeElapsed >= 1) {
            msg = "FPS: " + std::to_string(fps);
            fps = 0;
            timeElapsed = 0;
        }
        renderText(msg, -0.9f, 0.9f);
        glfwSwapBuffers(window);
        glfwPollEvents();

	} while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);

	glfwTerminate();

	return 1;
}

int InitWindow(void) {
	if(!glfwInit()) {
        cerr << "[ERROR] Failed to initialize GLFW\n";
        getchar();
        return -1;
	}

	int argc = 0;
	glutInit(&argc, nullptr);

	window = glfwCreateWindow(WIDTH, HEIGHT, "Test", nullptr, nullptr);
    if(window == nullptr) {
        cerr << "[ERROR] Failed to open GLFW window\n";
        getchar();
        glfwTerminate();
        return -1;
    }
	glfwMakeContextCurrent(window);

	// glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	// glfwSetMouseButtonCallback(window, mouse_button_callback);

	InitOpenGL();

	return 1;
}

void InitOpenGL() {
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);             // RGBA: Indicates the color that will be used to clean the screen

    glMatrixMode(GL_PROJECTION);                      // Indicates which projection you are using
                                                      // GL_PROJECTION is a preconstructed projection
    glLoadIdentity();
    gluPerspective(45.0, WIDTH / HEIGHT, 0.1, 100.0); // (degrees, aspect?, startView, endView)

    glMatrixMode(GL_MODELVIEW);                       // Model & View Matrix
    glLoadIdentity();
    gluLookAt(0.0f, 0.0f, 20.0f,   0.0f, 0.0f, 0.0f,   0.0f, 1.0f, 0.0f);

    glEnable(GL_DEPTH_TEST);                          //! Provides depth to the drawing
}

float theta{};
constexpr float e{7.0f/17.0f};
constexpr float a{8.5f};
void Display() {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0f, 0.0f, 20.0f,   0.0f, 0.0f, 0.0f,   0.0f, 1.0f, 0.0f);

    glBegin(GL_TRIANGLES); // Define vertices for shapes

    Model& sphere1 = models.front();

    glColor3f(1.0f, 0.55f, 0.20f); // Color for the first sphere
    for (Face& f : sphere1.faces) {
        Vertex& v1 = sphere1.vertices[f.index1];
        Vertex& v2 = sphere1.vertices[f.index2];
        Vertex& v3 = sphere1.vertices[f.index3];
        glVertex3f(v1.x + 3.7f, v1.y, v1.z);
        glVertex3f(v2.x + 3.7f, v2.y, v2.z);
        glVertex3f(v3.x + 3.7f, v3.y, v3.z);
    }

    Model& sphere2 = models.back();

    // Orbit Calculus
    float r = (a * (1 - e * e)) / (1 + e * std::cos(theta));
    float x = r * std::cos(theta);
    float y = r * std::sin(theta);

    glColor3f(0.45f, 0.86f, 1.0f); // Color for the second sphere
    for (Face& f : sphere2.faces) {
        Vertex& v1 = sphere2.vertices[f.index1];
        Vertex& v2 = sphere2.vertices[f.index2];
        Vertex& v3 = sphere2.vertices[f.index3];
        glVertex3f(v1.x + 3 + x, v1.y + y, v1.z);
        glVertex3f(v2.x + 3 + x, v2.y + y, v2.z);
        glVertex3f(v3.x + 3 + x, v3.y + y, v3.z);
    }

    theta += 0.007f;
    if(theta > 2 * M_PI) theta -= (2 * M_PI);

    glEnd();
}

void renderText(const std::string& text, float x, float y) {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0); // Set up a 2D orthographic projection

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glColor3f(0.0f, 1.0f, 0.0f); // Set text color to green
    glRasterPos2f(x, y);         // Set the position for the text

    for (const char& c : text) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}