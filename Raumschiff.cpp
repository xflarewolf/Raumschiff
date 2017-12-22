#include <iostream>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <time.h>
#include <vector>
using namespace std;

class Sterne {
    private:
        SDL_Surface *bild;
        int geschwindigkeit;
        int position;
        int position2;
    public:
        Sterne(int, int, char*);
        void zeichnen(SDL_Surface *);
        void bewegen();
};

class Raumschiff {
    protected:
        int x;
        int y;
        SDL_Surface *bild;
    public:
        Raumschiff (int, int, char *z);
        void zeichnen (SDL_Surface *);
        void oben();
        void unten();
        void links();
        void rechts();
};

class Meteorit: public Raumschiff {
    public:
        Meteorit (int, int, char *z): Raumschiff(x, y, z) {
            // srand(time(NULL));
            x = rand() %760;
            y = rand() %580;};
        void zeichnen (SDL_Surface *);
        void bewegen();
};

Sterne::Sterne(int startposition, int geschw, char *fn) {
    bild = IMG_Load(fn);
    geschwindigkeit = geschw;
    position = startposition;
    position2 = startposition + 762;
}

void Sterne::zeichnen(SDL_Surface *surf) {
    SDL_Rect sternposition;
    sternposition = {x:position, y:0, w:762, h:580};
    SDL_BlitSurface(bild, NULL, surf, &sternposition);
    sternposition = {x:position2, y:0, w:762, h:580};
    SDL_BlitSurface(bild, NULL, surf, &sternposition);
}

void Sterne::bewegen() {
    position -= geschwindigkeit;
    if (position < -762) {
        position = 768;
    }
    position2 -= geschwindigkeit;
    if (position2 < -762) {
        position2 = 768;
    }
}

Raumschiff::Raumschiff(int ax, int ay, char *z) {
    bild = IMG_Load(z);
    x = ax;
    y = ay;
}

void Raumschiff::zeichnen(SDL_Surface *surf) {
    SDL_Rect source = {x:0, y:32, w:32, h:32};
    SDL_Rect position = {x:x, y:y, w:32, h:32};
    SDL_BlitSurface(bild, &source, surf, &position);
}

void Raumschiff::oben() {
    y = y - 8;
}

void Raumschiff::unten() {
    y = y + 8;
}

void Raumschiff::links() {
    x = x - 8;
}

void Raumschiff::rechts() {
    x = x + 8;
}

void Meteorit::zeichnen(SDL_Surface *surf) {
    SDL_Rect source = {x:0, y:32, w:32, h:32};
    SDL_Rect position = {x:x, y:y, w:32, h:32};
    SDL_BlitSurface(bild, &source, surf, &position);
};

void Meteorit::bewegen() {
    x--;
    if (x > 400) {
        y++;
    }
    else {
        y--;
    }
}

int main(int a, char **b) {

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *win = SDL_CreateWindow("Raumschiffrennen", 100, 100, 760, 580, SDL_WINDOW_SHOWN);
    SDL_Surface *surf = SDL_GetWindowSurface(win);

    IMG_Init( IMG_INIT_PNG );
    SDL_Surface *background = IMG_Load("background.png");

    Sterne s1(0, 3, "stars3.png");
    Sterne s2(0, 6, "stars2.png");
    Sterne s3(0, 10, "stars1. png");

    Raumschiff r(100, 100, "raumschiffe.png");

    Meteorit *m1 = new Meteorit(0, 0, "shot.ppm");

    vector<Meteorit*> meteoriten;
    meteoriten.push_back(m1);

    for (int i=0; i<20; i++) {
        Meteorit *m1 = new Meteorit(0, 0, "shot.ppm");
        meteoriten.push_back(m1);
    }

    for (int i=0; i<10000; i++) {

        SDL_Event e;
        int taste;

            while( SDL_PollEvent( &e ) != 0 ) {

                if( e.type == SDL_KEYDOWN ) {      // Taste gedrückt
                taste = e.key.keysym.sym;      // speichern, welche Taste es war
                if (taste == SDLK_UP) {
                r.oben();}
                if (taste == SDLK_DOWN) {
                r.unten();}
                if (taste == SDLK_LEFT) {
                r.links();}
                if (taste == SDLK_RIGHT) {
                r.rechts();}
                }
            }

        SDL_BlitSurface(background, NULL, surf, NULL);
        s1.bewegen();
        s2.bewegen();
        s3.bewegen();
        s1.zeichnen(surf);
        s2.zeichnen(surf);
        s3.zeichnen(surf);
        r.zeichnen(surf);

        for (int i=0; i<meteoriten.size(); i++) {
    	meteoriten[i]->bewegen();
    	meteoriten[i]->zeichnen(surf);
    }


        SDL_UpdateWindowSurface(win);
        SDL_Delay(10);
    }

    return 0;
}
