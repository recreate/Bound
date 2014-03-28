#include "util.h"

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
	
	return cfg;
}
