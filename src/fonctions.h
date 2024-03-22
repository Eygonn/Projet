#ifndef FONCTIONS_H
#define FONCTIONS_H

#include "carte.h"

#define WINDOWS_WIDTH 1080
#define WINDOWS_HEIGHT 720

#define HEALTH_BAR_WIDTH 300
#define HEALTH_BAR_HEIGHT 20

#define TAILLE_SPRITE_PLAYER 160
#define DIM_SPRITE_PLAYER 160
#define FPS 60
#define DELAI 1000 / FPS
#define VITESSE_JOUEUR_X 4
#define VITESSE_JOUEUR_Y 4

#define HAUT 0
#define BAS 1
#define DROITE 2
#define GAUCHE 3

#define LARGEUR_FOND NB_TILE_WIDTH*TILE_WIDTH
#define HAUTEUR_FOND NB_TILE_HEIGHT*TILE_HEIGT

#define CAMERA_WIDTH 1080
#define CAMERA_HEIGHT 720

typedef struct {
    float x;
    float y;
} Camera_t;

// Structure pour représenter une couleur en RGB
typedef struct {
    int red;
    int green;
    int blue;
} Couleur_t;

// Structure pour représenter la barre de vie
typedef struct {
    int x, y;     // Position de la barre de vie
    int width;    // Largeur initiale de la barre de vie
    int maxWidth; // Largeur maximale de la barre de vie (pleine vie)
} HealthBar;


SDL_Texture *creationTextureBar(SDL_Renderer *rendu, Couleur_t couleur);
void initHealthBar(HealthBar *healthBar, int x, int y, int maxWidth);
void updateHealthBar(HealthBar *healthBar, SDL_Rect *healthBarRect, int currentHealth);
int initialisation(SDL_Window **fenetre, SDL_Renderer **rendu);
void chargerTextures(SDL_Renderer *rendu, SDL_Texture * tabTile[5]);
int fin(SDL_Window *fenetre, SDL_Renderer *rendu);
void actualisationSprite(int nb_sprite, int frame, int largeur, int hauteur, int direction, SDL_Rect *src, SDL_Rect *dst, SDL_Renderer *rendu);
void action(const Uint8 *clavier, SDL_Rect *pers_destination, SDL_Rect *pers_source, int frame, int DIM_SPRITE, SDL_Renderer *rendu);
void renduFond(SDL_Renderer *rendu, SDL_Rect *cameraRect);
void updateCamera(SDL_Rect *pers_destination, SDL_Renderer *rendu, SDL_Rect *cameraRect, int tab[NB_TILE_HEIGHT][NB_TILE_WIDTH], SDL_Texture *tabTile[5]);
int tabInit(SDL_Texture *tab[5], SDL_Renderer* rendu);
#endif