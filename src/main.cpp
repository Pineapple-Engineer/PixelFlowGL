#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <thread>
#include <mutex>

#include "GLFW/glfw3.h"
#include "GL/freeglut.h"
#include "../include/objreader.h"

const float WIDTH{800.0f};
const float HEIGHT{600.0f};

int InitWindow();
void InitOpenGL();
void Display();

GLFWwindow* window;

std::list<Model> models;

int main() {
	if (InitWindow() < 0) return -1;

    // Read the .obj file
    if (!readObj(models)) {
        std::cerr << "[ERROR] Failed to read the models\n";
        glfwTerminate();
        return -1;
    }

    clock_t initialTime, finalTime;
    double timeElapsed;
    int fps{};
	do { // Main Loop
        if(fps == 0) initialTime = clock();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
        // Draws the scene
        Display();

		glfwSwapBuffers(window);
		glfwPollEvents();
        
        ++fps;
        finalTime = clock() - initialTime;
        timeElapsed += (static_cast<double>(finalTime) / CLOCKS_PER_SEC);
        if(timeElapsed > 1) {
            std::cout << "FPS: " << fps << "\n";
            fps = 0;
            timeElapsed = 0;
        }

	} while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);

	glfwTerminate();

	return 1;
}

int InitWindow(void) {
	if (!glfwInit()) {
        std::cerr << "[ERROR] Failed to initialize GLFW\n";
        getchar();
        return -1;
	}

	window = glfwCreateWindow(WIDTH, HEIGHT, "Test", nullptr, nullptr);
    if(window == nullptr) {
        std::cerr << "[ERROR] Failed to open GLFW window\n";
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
    // gluLookAt(eyex, eyey, eyez, centerx, centery, centerz, upx, upy, upz)
    gluLookAt(0.0f, 0.0f, 10.0f,   0.0f, 0.0f, 0.0f,   0.0f, 1.0f, 0.0f); // Camera control

    glEnable(GL_DEPTH_TEST);                          //! Provides depth to the drawing
}

float xCamView{0.0f};
float yCamView{0.0f};
const float zCamView{10.0f};
void Display() {
    glColor3f(0.1f, 0.2f, 0.3f); // Color Setter

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(xCamView, yCamView, zCamView,   0.0f, 0.0f, 0.0f,   0.0f, 1.0f, 0.0f);

    glBegin(GL_TRIANGLES);
    for(Model& m_it : models) {
        for(Face& c_it : m_it.faces) {
            Vertex& v1 = m_it.vertices[c_it.idx1];
            Vertex& v2 = m_it.vertices[c_it.idx2];
            Vertex& v3 = m_it.vertices[c_it.idx3];

            glVertex3f(v1.x, v1.y, v1.z);
            glVertex3f(v2.x, v2.y, v2.z);
            glVertex3f(v3.x, v3.y, v3.z);
        }
    }
    glEnd();

    xCamView -= 0.05f;
    yCamView -= 0.05f;
}