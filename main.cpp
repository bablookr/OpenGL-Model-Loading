#include <iostream>
#include <SDL2/SDL.h>
#include "display.h"
#include "mesh.h"
#include "shader.h"
#include "texture.h"
#include "transform.h"
#include "camera.h"

static const int DISPLAY_WIDTH = 1300;
static const int DISPLAY_HEIGHT = 700;

int main(int argc, char** argv){

	Display display(DISPLAY_WIDTH, DISPLAY_HEIGHT, "Model Loading");

	/*Vertex vertices[] = {

		Vertex(glm::vec3(-1, -1, -1), glm::vec2(1, 0), glm::vec3(0, 0, -1)),
		Vertex(glm::vec3(-1, 1, -1), glm::vec2(0, 0), glm::vec3(0, 0, -1)),
		Vertex(glm::vec3(1, 1, -1), glm::vec2(0, 1), glm::vec3(0, 0, -1)),
		Vertex(glm::vec3(1, -1, -1), glm::vec2(1, 1), glm::vec3(0, 0, -1)),

		Vertex(glm::vec3(-1, -1, 1), glm::vec2(1, 0), glm::vec3(0, 0, 1)),
		Vertex(glm::vec3(-1, 1, 1), glm::vec2(0, 0), glm::vec3(0, 0, 1)),
		Vertex(glm::vec3(1, 1, 1), glm::vec2(0, 1), glm::vec3(0, 0, 1)),
		Vertex(glm::vec3(1, -1, 1), glm::vec2(1, 1), glm::vec3(0, 0, 1)),

		Vertex(glm::vec3(-1, -1, -1), glm::vec2(0, 1), glm::vec3(0, -1, 0)),
		Vertex(glm::vec3(-1, -1, 1), glm::vec2(1, 1), glm::vec3(0, -1, 0)),
		Vertex(glm::vec3(1, -1, 1), glm::vec2(1, 0), glm::vec3(0, -1, 0)),
		Vertex(glm::vec3(1, -1, -1), glm::vec2(0, 0), glm::vec3(0, -1, 0)),

		Vertex(glm::vec3(-1, 1, -1), glm::vec2(0, 1), glm::vec3(0, 1, 0)),
		Vertex(glm::vec3(-1, 1, 1), glm::vec2(1, 1), glm::vec3(0, 1, 0)),
		Vertex(glm::vec3(1, 1, 1), glm::vec2(1, 0), glm::vec3(0, 1, 0)),
		Vertex(glm::vec3(1, 1, -1), glm::vec2(0, 0), glm::vec3(0, 1, 0)),

		Vertex(glm::vec3(-1, -1, -1), glm::vec2(1, 1), glm::vec3(-1, 0, 0)),
		Vertex(glm::vec3(-1, -1, 1), glm::vec2(1, 0), glm::vec3(-1, 0, 0)),
		Vertex(glm::vec3(-1, 1, 1), glm::vec2(0, 0), glm::vec3(-1, 0, 0)),
		Vertex(glm::vec3(-1, 1, -1), glm::vec2(0, 1), glm::vec3(-1, 0, 0)),

		Vertex(glm::vec3(1, -1, -1), glm::vec2(1, 1), glm::vec3(1, 0, 0)),
		Vertex(glm::vec3(1, -1, 1), glm::vec2(1, 0), glm::vec3(1, 0, 0)),
		Vertex(glm::vec3(1, 1, 1), glm::vec2(0, 0), glm::vec3(1, 0, 0)),
		Vertex(glm::vec3(1, 1, -1), glm::vec2(0, 1), glm::vec3(1, 0, 0)),
	};

	unsigned int indices[] = {

        0, 1, 2,
        0, 2, 3,

        6, 5, 4,
        7, 6, 4,

		10, 9, 8,
		11, 10, 8,

		12, 13, 14,
		12, 14, 15,

        16, 17, 18,
		16, 18, 19,

		22, 21, 20,
		23, 22, 20
    };

	Mesh mesh(vertices, sizeof(vertices)/sizeof(vertices[0]), indices, sizeof(indices)/sizeof(indices[0]));*/


	//Mesh mesh("./res/untitled7.obj");
	Mesh mesh("./res/monkey3.obj");
	Shader shader("./res/basicShader");
	Texture texture("./res/bricks.jpg");
	//Texture texture("./res/images.png");

    Camera camera(glm::vec3(0.0f, 0.0f, -5.0f), 70.0f, (float)DISPLAY_WIDTH/(float)DISPLAY_HEIGHT, 0.1f, 100.0f);
	Transform transform;
	SDL_Event e;
	bool isRunning = true;
	float counter = 0.0f;

	while(isRunning){
		while(SDL_PollEvent(&e)){
			if(e.type == SDL_QUIT)
				isRunning = false;
            if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_DOWN)
                transform.GetRot()->x = counter * (-10);
            if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_UP)
                transform.GetRot()->x = counter * 10;
            if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_LEFT)
                transform.GetRot()->y = counter * (-10);
            if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RIGHT)
                transform.GetRot()->y = counter * 10;
            if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_a)
                transform.GetPos()->x = counter * 0.1;
            if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_d)
                transform.GetPos()->x = counter * (-0.01);
            if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_w)
                transform.GetPos()->y = counter * 0.01;
            if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_s)
                transform.GetPos()->y = counter * (-0.01);
            if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_q)
                transform.GetPos()->z = counter * 0.01;
            if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_e)
                transform.GetPos()->z = counter * (-0.01);
		}

		display.Clear(0.0f, 0.0f, 0.0f, 1.0f);

        shader.Bind();
		texture.Bind();
		shader.Update(transform, camera);
		mesh.Draw();

		display.SwapBuffers();
		SDL_Delay(1);
		counter += 0.01f;
	}
	return 0;
}
