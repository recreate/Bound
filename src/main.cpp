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
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//printf("Using openGL version %s\n", glGetString(GL_VERSION));
}

void init() {
	g_stateManager = new StateManager();
	
	// Options menu
	GameMenu* optionsMenu = new GameMenu(loadTexture("./img/menubackground.png"), 4, 2);
	
	MenuButton* controlsButton = new MenuButton(loadTexture("./img/optionsmenu_controls.png"));
	MenuButton* gamplayButton = new MenuButton(loadTexture("./img/optionsmenu_gameplay.png"));
	MenuButton* audioButton = new MenuButton(loadTexture("./img/optionsmenu_audio.png"));
	MenuButton* graphicsButton = new MenuButton(loadTexture("./img/optionsmenu_graphics.png"));
	MenuButton* backButton = new MenuButton(loadTexture("./img/optionsmenu_back.png"));
	
	backButton->setTransitionState(NULL);
	
	optionsMenu->addMenuOption(controlsButton, 0, 1);
	optionsMenu->addMenuOption(gamplayButton, 1, 1);
	optionsMenu->addMenuOption(audioButton, 0, 2);
	optionsMenu->addMenuOption(graphicsButton, 1, 2);
	optionsMenu->addMenuOption(backButton, 1, 3);
	
	MenuState* optionsMenuState = new MenuState(loadTexture("./img/back.jpg"), optionsMenu);
	
	// Main menu
	GameMenu* startMenu = new GameMenu(loadTexture("./img/menubackground.png"), 4, 1);
	
	MenuButton* startButton = new MenuButton(loadTexture("./img/menubutton_start.png"));
	MenuButton* optionsButton = new MenuButton(loadTexture("./img/menubutton_options.png"));
	MenuButton* exitButton = new MenuButton(loadTexture("./img/menubutton_exit.png"));
	
	startButton->setTransitionState(NULL);
	optionsButton->setTransitionState(optionsMenuState);
	exitButton->setTransitionState(NULL);
	
	startMenu->addMenuOption(startButton, 0, 1);
	startMenu->addMenuOption(optionsButton, 0, 2);
	startMenu->addMenuOption(exitButton, 0, 3);
	
	MenuState* startMenuState = new MenuState(loadTexture("./img/back.jpg"), startMenu);
	
	SplashScreenState* splashScreen = new SplashScreenState(loadTexture("./img/logo.tga"), 8000, 3000, 2000);
	
	g_stateManager->registerState(startMenuState);
	g_stateManager->registerState(optionsMenuState);
	g_stateManager->registerState(splashScreen);
	g_stateManager->loadNewCurrentState(startMenuState);
	g_stateManager->loadNewCurrentState(splashScreen);
	
	g_quit = false;
}

void cleanup() {
	SDL_DestroyWindow(g_mainWindow);
	SDL_GL_DeleteContext(g_mainContext);
	SDL_Quit();
	
	delete g_stateManager;
}

// Render objects onto SDL screen
void render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	g_stateManager->getCurrentState()->render();
	
	SDL_GL_SwapWindow(g_mainWindow);
}

// OpenGL main loop
void mainLoop() {
	SDL_Event e;
	
	GameTimer* timer = new GameTimer();
	timer->start();
	
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
	
	delete timer;
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
