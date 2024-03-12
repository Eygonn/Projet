#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "fonctions.h"
#include <stdbool.h>

SDL_Surface *temp_surface;

int vrai = 1;
int direction = 0;

SDL_Texture *run_front_tex;
SDL_Texture *run_back_tex;
SDL_Texture *run_right_tex;
SDL_Texture *run_left_tex;
SDL_Texture *menu_tex;

SDL_Texture *fond_tex;


int initialisation(SDL_Window **fenetre, SDL_Renderer **rendu) {

    // Initialisation de la bibliothèque SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("Problème d'initialisation de la bibliothèque SDL : %s\n", SDL_GetError());
        return 0;
    }

     // Initialisation de la SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Erreur lors de l'initialisation de la SDL : %s\n", SDL_GetError());
        return 1;
    }

    // Création de la fenêtre et du renderer
    *fenetre = SDL_CreateWindow("test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOWS_WIDTH, WINDOWS_HEIGHT, SDL_WINDOW_OPENGL);

    // Initialisation de SDL_ttf
    if (TTF_Init() != 0) {
        printf("Erreur lors de l'initialisation de SDL_ttf : %s\n", TTF_GetError());
        return 1;
    }

    // Création de la fenêtre et du rendu
    *rendu = SDL_CreateRenderer(*fenetre, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawColor(*rendu, 255, 255, 255, 255);

    if (*fenetre != NULL && *rendu != NULL) {
        return 1;
    } else {
        printf("Problème de création de la fenêtre : %s\n", SDL_GetError());
        return 0;
    }
}

void chargerTextures(SDL_Renderer *rendu) {
    temp_surface = SDL_LoadBMP("images/run_front.bmp");
    run_front_tex = SDL_CreateTextureFromSurface(rendu, temp_surface);
    SDL_FreeSurface(temp_surface);
    if(run_front_tex == NULL){
        printf("Erreur de chargement de l'image 'run_front': %s\n", SDL_GetError());
    }
    else printf("Chargement de l'image 'run_front' réussi\n");

    temp_surface = SDL_LoadBMP("images/run_back.bmp");
    run_back_tex = SDL_CreateTextureFromSurface(rendu, temp_surface);
    SDL_FreeSurface(temp_surface);
    if(run_back_tex == NULL){
        printf("Erreur de chargement de l'image 'run_back': %s\n", SDL_GetError());
    }
    else printf("Chargement de l'image 'run_back' réussi\n");

    temp_surface = SDL_LoadBMP("images/run_right.bmp");
    run_right_tex = SDL_CreateTextureFromSurface(rendu, temp_surface);
    SDL_FreeSurface(temp_surface);
    if(run_right_tex == NULL){
        printf("Erreur de chargement de l'image 'run_right': %s\n", SDL_GetError());
    }
    else printf("Chargement de l'image 'run_right' réussi\n");

    temp_surface = SDL_LoadBMP("images/run_left.bmp");
    run_left_tex = SDL_CreateTextureFromSurface(rendu, temp_surface);
    SDL_FreeSurface(temp_surface);
    if(run_left_tex == NULL){
        printf("Erreur de chargement de l'image 'run_left': %s\n", SDL_GetError());
    }
    else printf("Chargement de l'image 'run_left' réussi\n");

    temp_surface = IMG_Load("images/backround.png");
    fond_tex = SDL_CreateTextureFromSurface(rendu, temp_surface);
    SDL_FreeSurface(temp_surface);
    if(fond_tex == NULL){
        printf("Erreur de chargement du fond: %s\n", SDL_GetError());
    }
    else printf("Chargement du fond réussi\n");

    temp_surface = SDL_LoadBMP("images/background2.bmp");
    menu_tex = SDL_CreateTextureFromSurface(rendu, temp_surface);
    if( menu_tex == NULL){
        printf("Erreur de chargement de l'image du menu: %s\n", SDL_GetError());
    }
    else printf("Chargement du fond du menu réussi\n");
    SDL_FreeSurface(temp_surface);

}

int fin(SDL_Window *fenetre, SDL_Renderer *rendu) {
    SDL_DestroyRenderer(rendu);
    SDL_DestroyWindow(fenetre);
    SDL_Quit();
    return 0;
}

void affichageMenuImage(SDL_Renderer *rendu){
    SDL_RenderCopy(rendu, menu_tex, 0, 0);
}

int getMousePositionDirection(SDL_Rect *pers_destination){
    int direction = BAS;
    int x_joueur = pers_destination->x;
    int y_joueur = pers_destination->y;
    int x, y;
    SDL_GetMouseState(&x, &y);
    int x_relatif, y_relatif;
    x_relatif = x - x_joueur;
    y_relatif = -(y - y_joueur);


    int diag1_x, diag1_y, diag2_x, diag2_y;

    diag1_x = (x_joueur + x_relatif);
    diag1_y = (y_joueur - y_relatif);

    diag2_x = (x_joueur - x_relatif);
    diag2_y = (y_joueur + y_relatif);

    bool is_above_diag1 = y < diag1_y;
    bool is_above_diag2 = y < diag2_y;

    printf("x = %d, y = %d\n", x_relatif, y_relatif);

    if (!is_above_diag1 && !is_above_diag2) {
        direction = HAUT;
    } else if (is_above_diag1 && !is_above_diag2) {
        direction = DROITE;
    } else if (!is_above_diag1 && is_above_diag2) {
        direction = GAUCHE;
    } else {
        direction = BAS;
    }
    return direction;
}

void actualisationSprite(int nb_sprite, int frame, int largeur, int hauteur, int direction, SDL_Rect *src, SDL_Rect *dst, SDL_Renderer *rendu){
    SDL_Texture *texSprite;
    if (direction == HAUT) { 
        texSprite = run_front_tex;
    } else if (direction == BAS) { 
        texSprite = run_back_tex;
    } else if (direction == DROITE) { 
        texSprite = run_right_tex;
    } else if (direction == GAUCHE) { 
        texSprite = run_left_tex;
    }

    src->x = (frame % nb_sprite)*largeur;
    src->y = 0;
    src->w = largeur;
    src->h = hauteur;
    dst->w = TAILLE_SPRITE_PLAYER;
    dst->h = TAILLE_SPRITE_PLAYER;

    // On affiche les sprites  :
    SDL_RenderCopy(rendu, texSprite, src, dst);
}

void action(const Uint8 *clavier, SDL_Rect *pers_destination, SDL_Rect *pers_source, int frame, int DIM_SPRITE, SDL_Renderer *rendu) {
    int direction = 0;

    if (clavier[SDL_SCANCODE_W] && pers_destination->y > 0) {
        pers_destination->y -= VITESSE_JOUEUR;
    }
    if (clavier[SDL_SCANCODE_S] && pers_destination->y < WINDOWS_HEIGHT - DIM_SPRITE) {
        pers_destination->y += VITESSE_JOUEUR;
    }
    if (clavier[SDL_SCANCODE_A] && pers_destination->x > 0) {
        pers_destination->x -= VITESSE_JOUEUR;
    }
    if (clavier[SDL_SCANCODE_D] && pers_destination->x < WINDOWS_WIDTH - DIM_SPRITE) {
        pers_destination->x += VITESSE_JOUEUR;
    }

    direction = getMousePositionDirection(pers_destination);

    actualisationSprite(6, frame, DIM_SPRITE, DIM_SPRITE, direction, pers_source, pers_destination, rendu);
    
}

void renduFond(SDL_Renderer *rendu, SDL_Rect *cameraRect) {
    SDL_RenderCopy(rendu, fond_tex, cameraRect, NULL);
}

void updateCamera(SDL_Rect *pers_destination, SDL_Renderer *rendu, SDL_Rect *cameraRect) {
    // Facteur d'interpolation
    float interpolationFactor = 0.3;

    // Calcul de la nouvelle position en utilisant l'interpolation linéaire
    cameraRect->x = (1.0 - interpolationFactor) * cameraRect->x + interpolationFactor * pers_destination->x;
    cameraRect->y = (1.0 - interpolationFactor) * cameraRect->y + interpolationFactor * pers_destination->y;

    cameraRect->w = WINDOWS_WIDTH;
    cameraRect->h = WINDOWS_HEIGHT;

    // Debug
    //printf("Position sprite -> x: %d, y: %d \n", pers_destination->x, pers_destination->y);
    //printf("Camera x: %d, y: %d \n", cameraRect->x, cameraRect->y);

    // Rendu du fond
    SDL_RenderCopy(rendu, fond_tex, cameraRect, NULL);
}

SDL_Texture *creationTextureBar(SDL_Renderer *rendu, Couleur_t couleur){
    SDL_Surface *barSurface = SDL_CreateRGBSurface(0, HEALTH_BAR_WIDTH, HEALTH_BAR_HEIGHT, 32, 0, 0, 0, 0);
    SDL_FillRect(barSurface, NULL, SDL_MapRGB(barSurface->format, couleur.red, couleur.green, couleur.blue));
    SDL_Texture *barTexture = SDL_CreateTextureFromSurface(rendu, barSurface);
    SDL_FreeSurface(barSurface);
    return barTexture;


}

// Initialise la barre de vie du joueur au max
void initHealthBar(HealthBar *healthBar, int x, int y, int maxWidth) {
    healthBar -> x = x;
    healthBar -> y = y;
    healthBar -> width = maxWidth;
    healthBar -> maxWidth = maxWidth;
}

// Met à jour la barre de vie du joueur (currentHealth prend un pourcentage)
void updateHealthBar(HealthBar *healthBar, SDL_Rect *healthBarRect, int currentHealth) {
    healthBarRect->w = (currentHealth * healthBar->maxWidth) / 100;
}

