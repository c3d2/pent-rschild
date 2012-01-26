#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <time.h>
#include <SDL/SDL.h>

#include "main.h"
#include "sdl_draw/SDL_draw.h"

#define ZOOM_X 28
#define ZOOM_Y 16

int leds[LED_HEIGHT][LED_WIDTH];
int interval;


tick_fun tick_fp;

void setLedXY(uint8_t x, uint8_t y, uint8_t b) {
	assert(x < LED_WIDTH);
	assert(y < LED_HEIGHT);
	assert(b < 2);
	leds[y][x] = b;
}

void registerAnimation(tick_fun tick, uint16_t t, uint16_t ignore)
{
	tick_fp = tick;

	assert(t > 0);
	interval = t;
}


int main(int argc, char *argv[]) {
	srand(time(NULL));

	SDL_Surface* screen = SDL_SetVideoMode(LED_WIDTH * ZOOM_X, LED_HEIGHT * ZOOM_Y,
		32, SDL_SWSURFACE | SDL_DOUBLEBUF);

	SDL_Rect rect = { 0, 0, LED_WIDTH*ZOOM_X, LED_HEIGHT*ZOOM_Y };
	SDL_FillRect(screen, &rect, SDL_MapRGB(screen->format, 0x00,0x00,0x00));

	unsigned int color[] = {
		SDL_MapRGB(screen->format, 0x57,0x10,0x10),
		SDL_MapRGB(screen->format, 0xff,0x80,0x80)
	};

	int running = 1;
	while(running) {
		SDL_Event ev;
		while(SDL_PollEvent(&ev)) {
            switch(ev.type) {
	            case SDL_QUIT:
    	            running = 0;
        	        break;
            	case SDL_KEYUP:
	            case SDL_KEYDOWN:
					switch(ev.key.keysym.sym) {
						case SDLK_ESCAPE:
							running = 0;
							break;

						default: break;
					}
				default: break;
			}
		}

		running &= !tick_fp();

		int x, y;
		for(x = 0; x < LED_WIDTH; x++) {
			for(y = 0; y < LED_HEIGHT; y++) {
				Draw_FillCircle(screen, ZOOM_X*x+(ZOOM_X/2),ZOOM_Y*y+(ZOOM_Y/2), (ZOOM_Y*0.4),color[leds[y][x]]);
			}
		}
		SDL_Flip(screen);

		usleep(interval*1000);
	}

	SDL_Quit();
	return 0;
}

