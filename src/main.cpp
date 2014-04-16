#include "main.h"

SDL_Window* g_mainWindow;
SDL_GLContext g_mainContext;
StateManager* g_stateManager;
int g_windowWidth;
int g_windowHeight;
bool g_quit;

void initSDL(struct config* cfg) {
	int status;
	status = SDL_Init(SDL_INIT_VIDEO);
	check_error(status != 0, SDL_GetError());
	
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	/*
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	*/
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	
	g_windowWidth = cfg->width;
	g_windowHeight = cfg->height;
	Uint32 flags = (cfg->fullscreen ? SDL_WINDOW_FULLSCREEN : 0) | (cfg->border ? 0 : SDL_WINDOW_BORDERLESS);
	
	g_mainWindow = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
		g_windowWidth, g_windowHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | flags);
	check_error(g_mainWindow == NULL, SDL_GetError());
	
	g_mainContext = SDL_GL_CreateContext(g_mainWindow);
	check_error(g_mainContext == NULL, SDL_GetError());
}

void initGLEW() {
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	glGetError(); // ignore GLEW errors?
	check_error(err != GLEW_OK, (char*)glewGetErrorString(err));
	glEnable(GL_DEPTH_TEST);
	//printf("Using openGL version %s\n", glGetString(GL_VERSION));
}

void init() {
	g_stateManager = new StateManager();
	
	GameMenu* menu = new GameMenu();
	MenuState* menuState = new MenuState(new Screen(loadTexture("./img/forest.jpg")), menu);
	
	g_stateManager->loadNewCurrentState(menuState);
	g_stateManager->loadNewCurrentState(new SplashScreenState(new Screen(loadTexture("./img/logo.tga")), 8000, 3000, 2000));
	
	g_quit = false;
}

void cleanup() {
	SDL_DestroyWindow(g_mainWindow);
	SDL_GL_DeleteContext(g_mainContext);
	SDL_Quit();
}

// TODO: REMOVE
#include "ThreeDModel.h"
ThreeDModel* model;

// Render objects onto SDL screen
void render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	g_stateManager->getCurrentState()->render();
	
	// TODO: REMOVE
	//model->draw();
	
	SDL_GL_SwapWindow(g_mainWindow);
}

// OpenGL main loop
void mainLoop() {
	SDL_Event e;
	
	GameTimer* timer = new GameTimer();
	timer->start();
	
	// TODO: REMOVE
	model = new ThreeDModel("./models/test/", "ship.obj");
	
	while(!g_quit) {
		timer->restart();
		
		while(SDL_PollEvent(&e))
			g_stateManager->getCurrentState()->handleEvent(e);
		
		if (!g_stateManager->hasState())
			break;
		
		render();
		
		//printf("%d\n", timer->getElapsedTime());
		//SDL_SetWindowTitle(g_mainWindow, fps_str);
	}
}

int main(int argc, char* argv[]) {
	struct config* cfg = getConfiguration();
	initSDL(cfg);
	
	initGLEW();
	
	init();
	mainLoop();
	
	cleanup();
	return 0;
}
