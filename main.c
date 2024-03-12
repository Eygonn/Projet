#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h> 
#include <stdio.h>
#include <stdlib.h>
#include "src/fonctions.h"
#include "src/menu.h"
#include "src/entite.h"

SDL_Renderer *rendu;
SDL_Window *fenetre;

SDL_Rect pers_source, pers_destination, cameraRect;

// Alors j'ai crée un structure couleur vu qu'en C y a pas de tuple pour gérer les couleurs donc si tu dois mapper des couleurs n'hesite pas à utiliser ces constantes au lieu d'écrire (255,0,255)
const Couleur_t JAUNE = {255,255,0};
const Couleur_t BLEU = {0,0,255};
const Couleur_t ROUGE = {255,0,0};
const Couleur_t VERT = {0,255,0};
const Couleur_t NOIR = {0,0,0};
const Couleur_t BLANC = {255,255,255};
const Couleur_t ORANGE = {255,165,0};


int main() {
    int isRunning = 1;
    initialisation(&fenetre, &rendu);
    chargerTextures(rendu);

    pers_destination.y = WINDOWS_HEIGHT/ 2 - TAILLE_SPRITE_PLAYER / 2;
    pers_destination.x = WINDOWS_WIDTH / 2 - TAILLE_SPRITE_PLAYER / 2;

    entite_t joueur;
    initialiserJoueur(&joueur);

    entite_t ennemi;
    initialiserEnnemi(&ennemi);

    // Gestion des événements SDL
    SDL_Event event;
    int frame = 0;
    Uint32 temps_ancien = SDL_GetTicks();
    Uint32 temps_actuel;
    int delta_temps;

    SDL_Texture *barTextureVieMax = creationTextureBar(rendu, JAUNE);
    SDL_Texture *barTextureVie = creationTextureBar(rendu, ROUGE);

    // Initialisation de la structure barre de vie
    HealthBar healthBar;
    initHealthBar(&healthBar, 50, 50, HEALTH_BAR_WIDTH);

    // Création de deux rectangles : un pour la barre de vie fixe et l'autre pour celle qui baisse (vie restante)
    SDL_Rect healthBarMaxRect = { healthBar.x, healthBar.y, healthBar.maxWidth, HEALTH_BAR_HEIGHT };
    SDL_Rect *healthBarRect = malloc(sizeof(SDL_Rect));
    *healthBarRect = (SDL_Rect){ healthBar.x, healthBar.y, healthBar.width, HEALTH_BAR_HEIGHT };

    Button jouerButton, difficulteButton, facileButton, normalButton, difficileButton, accueilButton, gameoverButton, retryButton;

    // Création des boutons
    jouerButton = createButton(rendu, "JOUER", (WINDOWS_WIDTH - BUTTON_WIDTH) / 2, (WINDOWS_HEIGHT - BUTTON_HEIGHT) / 2, BUTTON_WIDTH, BUTTON_HEIGHT, NOIR);
    difficulteButton = createButton(rendu, "DIFFICULTE", (WINDOWS_WIDTH - BUTTON_WIDTH) / 2, (WINDOWS_HEIGHT - BUTTON_HEIGHT) / 2 + BUTTON_HEIGHT, BUTTON_WIDTH, BUTTON_HEIGHT, NOIR);

    facileButton = createButton(rendu, "FACILE", (WINDOWS_WIDTH - BUTTON_WIDTH) / 2, 250 + BUTTON_HEIGHT * 0, BUTTON_WIDTH, BUTTON_HEIGHT, VERT);
    normalButton = createButton(rendu, "NORMAL", (WINDOWS_WIDTH - BUTTON_WIDTH) / 2, 250 + BUTTON_HEIGHT * 1, BUTTON_WIDTH, BUTTON_HEIGHT, ORANGE);
    difficileButton = createButton(rendu, "DIFFICILE", (WINDOWS_WIDTH - BUTTON_WIDTH) / 2, 250 + BUTTON_HEIGHT * 2, BUTTON_WIDTH, BUTTON_HEIGHT, ROUGE);
    accueilButton = createButton(rendu, "ACCUEIL", (WINDOWS_WIDTH - BUTTON_WIDTH) / 2, 250 + BUTTON_HEIGHT * 3, BUTTON_WIDTH, BUTTON_HEIGHT, NOIR);

    gameoverButton = createButton(rendu, "GAME OVER", (WINDOWS_WIDTH - BUTTON_WIDTH) / 2, (WINDOWS_HEIGHT - BUTTON_HEIGHT) / 2, BUTTON_WIDTH, BUTTON_HEIGHT, NOIR);
    retryButton = createButton(rendu, "RETRY", (WINDOWS_WIDTH - BUTTON_WIDTH) / 2, (WINDOWS_HEIGHT - BUTTON_HEIGHT) / 2 + BUTTON_HEIGHT, BUTTON_WIDTH, BUTTON_HEIGHT, NOIR);

    // Variable temporaire
    int count = 100;

    /* Variable qui reste à 1 si le menu est encore afficher */

    /*
    * MENU =
    * 0 - Jeu
    * 1 - Page d'accueil
    * 2 - Choix de la difficulté
    * 3 - Game Over
    * */
    int menu = 1;
    
    while (isRunning) {
        while (SDL_PollEvent(&event)) {
            // Pour fermer la fenêtre 
            switch(event.type){
                case SDL_QUIT:
                    isRunning = 0;
                    break;
                
                case SDL_MOUSEBUTTONDOWN:
                    if(menu == 1 && clickButton(event, jouerButton)){
                        menu = 0;
                    }
                    
                    if(menu == 1 && clickButton(event, difficulteButton)){
                        menu = 2;
                    }

                    if(menu == 2 && clickButton(event, accueilButton)){
                        menu = 1;
                    }

                    if(menu == 3 && clickButton(event, retryButton)){
                        menu = 1;
                        joueur.pv = 100;
                    }
                    break;
                    

            }
            
            
        }

        if(menu == 1){
            SDL_RenderClear(rendu);
            affichageMenuImage(rendu);

            // Dessiner les boutons
            drawButton(rendu, jouerButton);
            drawButton(rendu, difficulteButton);

            if(mouseOnButton(jouerButton)){
                /* I want to fill the rect with transparent color */
                SDL_SetRenderDrawColor(rendu, 255, 0, 255, 100);
                SDL_RenderFillRect(rendu, &jouerButton.rect);
            }

            if(mouseOnButton(difficileButton)){
                /* I want to fill the rect with transparent color */
                SDL_SetRenderDrawColor(rendu, 0, 255, 255, 100);
                SDL_RenderFillRect(rendu, &difficileButton.rect);
            }

            SDL_RenderPresent(rendu);

            
        }
        else if(menu == 2){
            SDL_RenderClear(rendu);
            affichageMenuImage(rendu);

            // Dessiner les boutons
            drawButton(rendu, facileButton);
            drawButton(rendu, normalButton);
            drawButton(rendu, difficileButton);
            drawButton(rendu, accueilButton);

            SDL_RenderPresent(rendu);
        }
        else if(menu == 3){
            SDL_RenderClear(rendu);
            affichageMenuImage(rendu);

            // Dessiner les boutons
            drawButton(rendu, gameoverButton);
            drawButton(rendu, retryButton);
            
            SDL_RenderPresent(rendu);
        }
        else if (menu == 0){
            //calcul du temps
            temps_actuel = SDL_GetTicks();
            delta_temps += temps_actuel - temps_ancien;
            temps_ancien = temps_actuel;

            if(delta_temps >= 100){ // ms entre les images du sprite
                delta_temps = 0;
                frame = (frame + 1) % 6;
            }
            printf("PV : %d\n", joueur.pv);
            updateHealthBar(&healthBar, healthBarRect, joueur.pv);

            // Récupération de l'état du clavier : 
            const Uint8 *clavier = SDL_GetKeyboardState(NULL);
            
            if(joueur.pv <= 0){
                menu = 3;
            }
            SDL_RenderClear(rendu);

            updateCamera(&pers_destination,rendu, &cameraRect);

            action(clavier, &pers_destination, &pers_source, frame, DIM_SPRITE_PLAYER, rendu);

            // Rendu de la barre de vie
            SDL_RenderCopy(rendu, barTextureVieMax, NULL, &healthBarMaxRect);
            SDL_RenderCopy(rendu, barTextureVie, NULL, healthBarRect);

            SDL_RenderPresent(rendu);

            SDL_Delay(DELAI);
        }
    }
    free(healthBarRect);
    return fin(fenetre, rendu);
}