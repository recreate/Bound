#include "util.h"

float g_horizontalPlusScale;

void check_error(int condition, const char* msg) {
	if (condition) {
		fprintf(stderr, "Error: %s\n", msg);
		exit(1);
	}
}

struct config* getConfiguration() {
	FILE* f;
	int height, width, fullscreen, border = -1;
	f = fopen(CONFIGURATION_FILE, "r");
	
	SDL_DisplayMode mode;
	SDL_GetDesktopDisplayMode(0, &mode);
	
	if (f == NULL) {
		f = fopen(CONFIGURATION_FILE, "w");
		width = mode.w;
		height = mode.h;
		fullscreen = DEFAULT_FULLSCREEN;
		border = DEFAULT_BORDER;
		
		fprintf(f,
			"width=%d\n"\
			"height=%d\n"\
			"fullscreen=%d\n"\
			"border=%d",
			height, width, fullscreen, border);
	} else {
		//std::regex comments("#.*");
		//std::regex fullscreen("fullscreen[\\s]*=[\\s]*(.*)");
		int value;
		int maxLineSize = 80;
		char* line = (char*)malloc(maxLineSize * sizeof(char));
		char* sp = (char*)malloc(sizeof(char));
		
		while (!feof(f)) {
			fgets(line, maxLineSize, f);
			
			char* comment = strchr(line, '#');
			if (comment != NULL)
				line[comment - line] = '\0';
			
			if (sscanf(line, "width=%d", &value))
				width = value;
			else if (sscanf(line, "height=%d", &value))
				height = value;
			else if (sscanf(line, "fullscreen=%d", &value))
				fullscreen = value;
			else if (sscanf(line, "border=%d", &value))
				border = value;
		}
		
		width = width == -1 ? mode.w : width;
		height = height == -1 ? mode.h : height;
		fullscreen = fullscreen == -1 ? DEFAULT_FULLSCREEN : fullscreen;
		border = border == -1 ? DEFAULT_BORDER : border;
	}
	
	struct config* cfg = (struct config*)malloc(sizeof(struct config));
	cfg->width = width;
	cfg->height = height;
	cfg->fullscreen = fullscreen;
	cfg->border = border;
	
	g_horizontalPlusScale = cfg->height < ASPECT_RATIO_HEIGHT ? (float)(cfg->height)/ASPECT_RATIO_HEIGHT : 1.0f;
	printf("%f\n", g_horizontalPlusScale);
	
	return cfg;
}

/*
 * Loads an image into an SDL_Surface optimized for the game window (user's display) and flips the image vertically
 * to match openGL texture coordinates.
*/
SDL_Surface* loadTexture(const char* filename) {
	int windowHeight, windowWidth;
	SDL_GetWindowSize(g_mainWindow, &windowWidth, &windowHeight);
	SDL_Surface* rgbaSurface = SDL_CreateRGBSurface(0, windowWidth, windowHeight, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
	
	SDL_Surface* textureImage = IMG_Load(filename);
	SDL_Surface* optimizedSurface = SDL_ConvertSurface(textureImage, rgbaSurface->format, 0);
	SDL_FreeSurface(textureImage);
	SDL_FreeSurface(rgbaSurface);

	// Flip image
	int numComponents = optimizedSurface->format->BytesPerPixel;
	unsigned char temp;
	unsigned int width = optimizedSurface->w;
	unsigned int height = optimizedSurface->h;
	unsigned char* pixels = (unsigned char*)(optimizedSurface->pixels);
	for (int i = 0; i < height/2; i++) {
		for (int j = 0; j < width * numComponents; j++) {
			temp = pixels[(i * width*numComponents) + j];
			pixels[(i * width*numComponents) + j] = pixels[(height-1 - i) * (width*numComponents) + j];
			pixels[(height-1 - i) * (width*numComponents) + j] = temp;
		}
	}
	
	return optimizedSurface;
}

/**/
void printMat4(glm::mat4 matrix) {
	printf("%f %f %f %f\n%f %f %f %f\n%f %f %f %f\n%f %f %f %f\n", 
		matrix[0][0], matrix[1][0], matrix[2][0], matrix[3][0],
		matrix[0][1], matrix[1][1], matrix[2][1], matrix[3][1],
		matrix[0][2], matrix[1][2], matrix[2][2], matrix[3][2],
		matrix[0][3], matrix[1][3], matrix[2][3], matrix[3][3]
	);
}
/**/
