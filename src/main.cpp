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
	
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
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
	//printf("Using openGL version %s\n", glGetString(GL_VERSION));
}

void init() {
	g_stateManager = new StateManager();
	g_stateManager->loadNewCurrentState(new SplashScreenState());
	
	g_quit = false;
	
	loadShaders();
}

void cleanup() {
	SDL_Quit();
	SDL_DestroyWindow(g_mainWindow);
	SDL_GL_DeleteContext(g_mainContext);
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
	
	while(!g_quit) {
		while(SDL_PollEvent(&e))
			g_stateManager->getCurrentState()->handleEvent(e);
		
		if (!g_stateManager->hasState())
			break;
		
		render();
	}
}

GLchar* readShaderFile(const char* filename) {
	FILE* f;
	long fileSize;
	GLchar* buf;
	size_t nread;
	
	f = fopen(filename, "rb");
	check_error(f == NULL, "Could not open file");
	
	fseek(f, 0, SEEK_END);
	fileSize = ftell(f);
	rewind(f);
	
	buf = (GLchar*)malloc((fileSize+1) * sizeof(GLchar));
	nread = fread(buf, sizeof(GLchar), fileSize, f);
	check_error(nread != fileSize, "Could not read file");
	buf[nread] = '\0';
	
	fclose(f);
	return buf;
}

void loadShaders() {
	GLchar* vShader = readShaderFile(VERTEX_SHADER);
	GLchar* fShader = readShaderFile(FRAGMENT_SHADER);
	
	GLuint vShaderId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vShaderId, 1, (const GLchar**)(&vShader), NULL);
	glCompileShader(vShaderId);
	
	GLuint fShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fShaderId, 1, (const GLchar**)(&fShader), NULL);
	glCompileShader(fShaderId);
	
	GLuint programId = glCreateProgram();
	glAttachShader(programId, vShaderId);
	glAttachShader(programId, fShaderId);
	glLinkProgram(programId);
	glUseProgram(programId);
	
	free(vShader);
	free(fShader);
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
