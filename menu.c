/**
 * \file menu.c
 * \brief Programme de menu principal.
 */

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#define WINDOW_WIDTH 800 /**< Largeur de la fenêtre. */
#define WINDOW_HEIGHT 600 /**< Hauteur de la fenêtre. */
#define BUTTON_WIDTH 200 /**< Largeur des boutons. */
#define BUTTON_HEIGHT 50 /**< Hauteur des boutons. */

// Structure pour représenter un bouton
typedef struct {
    SDL_Rect rect; /**< Rectangle délimitant le bouton. */
    SDL_Texture* texture; /**< Texture du texte du bouton. */
} Button;

SDL_Surface iconSurface = SDL_LoadBMP("./menu_montagne.jpeg"); /**< Surface pour l'icône de la fenêtre. */

// Fonction pour créer un bouton
Button createButton(SDL_Renderer* renderer, const char* text, int x, int y);

// Fonction pour dessiner un bouton
void drawButton(SDL_Renderer* renderer, Button button);

/**
 * \brief Fonction principale du programme.
 * \return 0 à la fin du programme.
 */
int main() {
    SDL_Window* window; /**< Fenêtre SDL. */
    SDL_Renderer* renderer; /**< Renderer SDL. */
    SDL_Event event; /**< Événement SDL. */
    Button playButton, settingsButton, levelButton; /**< Boutons du menu. */

    // Initialisation de la SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Erreur lors de l'initialisation de la SDL : %s\n", SDL_GetError());
        return 1;
    }

    // Création de la fenêtre et du renderer
    if (SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer) != 0) {
        printf("Erreur lors de la création de la fenêtre et du renderer : %s\n", SDL_GetError());
        return 1;
    }

    // Initialisation de SDL_ttf
    if (TTF_Init() != 0) {
        printf("Erreur lors de l'initialisation de SDL_ttf : %s\n", TTF_GetError());
        return 1;
    }

    // Création des boutons
    playButton = createButton(renderer, "Jouer", (WINDOW_WIDTH - BUTTON_WIDTH) / 2, 200);
    settingsButton = createButton(renderer, "Réglages", (WINDOW_WIDTH - BUTTON_WIDTH) / 2, 300);
    levelButton = createButton(renderer, "Changer le niveau", (WINDOW_WIDTH - BUTTON_WIDTH) / 2, 400);

    // Boucle principale
    int running = 1;
    while (running) {
        // Gestion des événements
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
        }

        // Effacer l'écran
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Noir
        SDL_RenderClear(renderer);

        // Dessiner les boutons
        drawButton(renderer, playButton);
        drawButton(renderer, settingsButton);
        drawButton(renderer, levelButton);

        // Mettre à jour l'affichage
        SDL_RenderPresent(renderer);
    }

    // Libération des ressources
    SDL_DestroyTexture(playButton.texture);
    SDL_DestroyTexture(settingsButton.texture);
    SDL_DestroyTexture(levelButton.texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return 0;
}
