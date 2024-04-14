#include "entite.h"
#include "projectile.h"

/* https://openclassrooms.com/forum/sujet/sdl-tracer-un-trait-entre-deux-points-49344 */

SDL_Surface *ennemi_temp_surface;

SDL_Texture *ennemi_run_right_tex;
SDL_Texture *ennemi_run_left_tex;

void chargerTexturesEnnemi(SDL_Renderer *rendu){

    ennemi_temp_surface = SDL_LoadBMP("images/necro_run_right.bmp");
    ennemi_run_right_tex = SDL_CreateTextureFromSurface(rendu, ennemi_temp_surface);
    SDL_FreeSurface(ennemi_temp_surface);
    if(ennemi_run_right_tex == NULL){
        printf("Erreur de chargement de l'image 'necro_run_right': %s\n", SDL_GetError());
    }
    else printf("Chargement de l'image 'necro_run_right' réussi\n");

    ennemi_temp_surface = SDL_LoadBMP("images/necro_run_left.bmp");
    ennemi_run_left_tex = SDL_CreateTextureFromSurface(rendu, ennemi_temp_surface);
    SDL_FreeSurface(ennemi_temp_surface);
    if(ennemi_run_left_tex == NULL){
        printf("Erreur de chargement de l'image 'necro_run_left': %s\n", SDL_GetError());
    }
    else printf("Chargement de l'image 'necro_run_left' réussi\n");
}

void initTabEnnemi(ennemi_t tabEnnemi[NB_ENNEMI]){
    
    for (int i = 0; i < NB_ENNEMI; i++){
        
        ennemi_creer(&tabEnnemi[i]);
        
    }
}

void initEnnemisVague(ennemi_t tabEnnemi[NB_ENNEMI], int nb_ennemis){
    for (int i = 0; i < nb_ennemis; i++){
        int positionRand_x = rand() % ((NB_TILE_WIDTH-2) * TILE_WIDTH);
        int positionRand_y = rand() % ((NB_TILE_HEIGHT-2) * TILE_HEIGHT);
        tabEnnemi[i].initEnnemi(&tabEnnemi[i], positionRand_x, positionRand_y, 1, 100, 10);
    }
}

void initEnnemis(
    projectiles_t projJoueur[MAX_PROJ],
    projectiles_t projEnnemi[MAX_PROJ],
    joueur_t *joueur,
    ennemi_t ennemi[NB_ENNEMI],
    SDL_Renderer *rendu
) {
    initTabProj(projJoueur);
    initTabProj(projEnnemi);
    initialiserJoueur(joueur);
    initTabEnnemi(ennemi);
    chargerTexturesEnnemi(rendu);
    chargerTexturesProj(rendu);
}

void actualisationSpriteEnnemi(int nb_sprite, int frame, int largeur, int hauteur, int direction, SDL_Rect *src, SDL_Rect *dst, SDL_Renderer *rendu){
    SDL_Texture *texSprite;
    if (direction == DROITE) { 
        texSprite = ennemi_run_right_tex;
    } else if (direction == GAUCHE) { 
        texSprite = ennemi_run_left_tex;
    }

    src->x = (frame % nb_sprite)*largeur;
    src->y = 0;
    src->w = largeur;
    src->h = hauteur;

    // On affiche les sprites  :
    SDL_RenderCopy(rendu, texSprite, src, dst);
}



/* algorithme de Bresenham */

void DessinerLigneEnnemiJoueur(point_t A, point_t B, SDL_Renderer *rendu)
{
        long xvAB = B.x - A.x; // abscisse du vecteur AB
        long absX = abs(xvAB); // abs() est une fonction de math.h
        long yvAB = B.y - A.y; // ordonnée du vecteur AB
        long absY = abs(yvAB);
        long i;

        if(absX > absY)
        {
                if(xvAB > 0)
                {
                        for(i = 0; i <= xvAB; i++)
                        {
                                SDL_RenderDrawPoint(rendu, A.x + i, A.y + yvAB * i / xvAB);
                        }
                }
                else
                {
                        for(i = 0; i >= xvAB; i--)
                        {
                                SDL_RenderDrawPoint(rendu, A.x + i, A.y + yvAB * i / xvAB);
                        }
                }
        }
        else
        {
                if(yvAB > 0)
                {
                        for(i = 0; i <= yvAB; i++)
                        {
                                SDL_RenderDrawPoint(rendu, A.x + xvAB * i / yvAB, A.y + i);
                        }
                }
                else
                {
                        for(i = 0; i >= yvAB; i--)
                        {
                                SDL_RenderDrawPoint(rendu, A.x + xvAB * i / yvAB, A.y + i);
                        }
                }
        }
} 


void DessinerLigneEnnemiVu(point_t A, point_t B, SDL_Renderer *rendu){
    long xvAB = B.x - A.x; // abscisse du vecteur AB
    long absX = abs(xvAB); // abs() est une fonction de math.h
    long yvAB = B.y - A.y; // ordonnée du vecteur AB
    long absY = abs(yvAB);
    long i;

    if(absX > absY)
    {
            if(xvAB > 0)
            {
                    for(i = 0; i <= xvAB; i++)
                    {
                            
                            SDL_RenderDrawPoint(rendu, A.x + i, A.y + yvAB * i / xvAB);
                    }
            }
            else
            {
                    for(i = 0; i >= xvAB; i--)
                    {       
                            
                            SDL_RenderDrawPoint(rendu, A.x + i, A.y + yvAB * i / xvAB);
                    }
            }
    }
    else
    {
            if(yvAB > 0)
            {
                    for(i = 0; i <= yvAB; i++)
                    {
                            
                            SDL_RenderDrawPoint(rendu, A.x + xvAB * i / yvAB, A.y + i);
                    }
            }
            else
            {
                    for(i = 0; i >= yvAB; i--)
                    {
                            
                            SDL_RenderDrawPoint(rendu, A.x + xvAB * i / yvAB, A.y + i);
                    }
            }
    }
}



void dessinerBarreDeVie(ennemi_t *ennemi, SDL_Renderer *rendu){
    SDL_Rect barreDeVie;
    barreDeVie.x = ennemi->rect.x;
    barreDeVie.y = ennemi->rect.y - 10;
    barreDeVie.w = (ennemi->pv * DIM_SPRITE_ENNEMI_X) / ennemi->pvMax;
    barreDeVie.h = 15;
    SDL_SetRenderDrawColor(rendu, 255, 0, 0, 255);
    SDL_RenderFillRect(rendu, &barreDeVie);
}


void ennemi_creer(ennemi_t * ennemi){
    ennemi->initEnnemi = initEnnemi;
    ennemi->updateEnnemi = updateEnnemi;
    ennemi->renderEnnemi = renderEnnemi;
    ennemi->renderVecteur = renderVecteur;
}

void initialiserJoueur(joueur_t * joueur){
    joueur->attaque = 10;
    joueur->pv = 100;
    joueur->pvMax = 100;

    joueur->mana = 100;
    joueur->manaMax = 100;
    joueur->vitesse = 1;
}

/* x et y pour coordonnées, id correspond aux types de monstre cela servira pour l'affichage des sprites (si y a plusieurs monstres) */
void initEnnemi(ennemi_t * ennemi, float x, float y, int id, int pvMax, int attaque){

    ennemi->mort = 0;

    ennemi->delta = SDL_GetTicks();

    ennemi->x = x;
    ennemi->y = y;

    ennemi->vx = x;
    ennemi->vy = y;

    ennemi->rect.x = 100;
    ennemi->rect.y = 100;

    ennemi->rect.w = DIM_SPRITE_ENNEMI_X/1.5;
    ennemi->rect.h = DIM_SPRITE_ENNEMI_Y/1.5;

    ennemi->attaque = attaque;
    ennemi->id = id;
    ennemi->pvMax = pvMax;
    ennemi->pv = pvMax;

    ennemi->detection = 0;
    ennemi->vitesse = 2.5;
}

void updateEnnemi(ennemi_t * ennemi, SDL_Rect * cameraRect, SDL_Rect * playerRect, int tabColision[NB_TILE_WIDTH][NB_TILE_HEIGHT], projectiles_t projEnnemi[MAX_PROJ], int *projNbEnnemi, int temp_vivant){
    srand(time(NULL));

    /* Si l'ennemi meurt (pv <= 0) on ne l'update plus et on le replace aléatoirement avec tous ses pv */
    if (ennemi->pv <= 0 && ennemi->mort == 0){    
        ennemi->mort = 1;
        ennemi->x = 0;
        ennemi->y = 0;
        return;
    }
    if (ennemi->pv <= 0 && ennemi->mort == 1){
        return;
    }

    /* Variable booléenne permettant de déterminer si l'ennemi est proche du joueur et ainsi qu'il s'arrete un peu avant */
    int proche = 0;

    /*Detection du joueur par l'ennemi, augmenter CHAMP_DETECTION fera detecter le joueur de plus loin */
    if (ennemi->x - cameraRect->x < playerRect->x + CHAMP_DETECTION && ennemi->x - cameraRect->x > playerRect->x - CHAMP_DETECTION && ennemi->y - cameraRect->y < playerRect->y + CHAMP_DETECTION && ennemi->y - cameraRect->y > playerRect->y - CHAMP_DETECTION){
        ennemi->detection = 1;
    }

    /* Calcul de la trajectoire de l'ennemi vers le joueur */
    float dirx = (playerRect->x + 100/2) - ennemi->rect.x ;
    float diry = (playerRect->y + 100/2) - ennemi->rect.y ;

    /* Si l'ennemi est à proximité du joueur, il s'arrête (pour éviter que l'ennemi aille directement sur le joueur à l'infini) */
    if ((dirx < 300 && dirx > -300) && (diry < 300 && diry > -300)){
        proche = 1;
    }
    else{
        proche = 0;
    }

    /* Condition permettant de déterminer si le joueur se trouve à la droite ou à la gauche de l'ennemi, sert uniquement pour l'affichage du sprite ennemi */
    if(dirx < 0){
        ennemi->gauche = 1;
        ennemi->droite = 0;
    }
   else{
        ennemi->gauche = 0;
        ennemi->droite = 1;
    }

    int colision_bas = 0;
    int colision_haut = 0;
    int colision_gauche = 0;
    int colision_droite = 0;

    /* On vérifie si l'ennemi est en collision avec les tiles de la carte */
    colision_bas = tabColision[(ennemi->rect.y + 200) / TILE_HEIGHT][(ennemi->rect.x + 300) / TILE_WIDTH];
    colision_haut = tabColision[(ennemi->rect.y + 100) / TILE_HEIGHT][(ennemi->rect.x + 300) / TILE_WIDTH];
    colision_gauche = tabColision[(ennemi->rect.y + 150) / TILE_HEIGHT][(ennemi->rect.x + 250) / TILE_WIDTH];
    colision_droite = tabColision[(ennemi->rect.y + 150) / TILE_HEIGHT][(ennemi->rect.x + 350) / TILE_WIDTH];

    /* Si l'ennemi detecte le joueur, il fonce vers lui */
    if (ennemi->detection == 1){
        if (proche == 0){
            float hyp = sqrt(dirx * dirx + diry * diry);
            dirx /= hyp;
            diry /= hyp;

            ennemi->x += dirx * ennemi->vitesse; 
            ennemi->y += diry * ennemi->vitesse;
        }

        /* temp_vivant correspond à la durée durant laquelle l'ennemi est en vit, ici toutes les deux secondes il lance un projectile */
        if (temp_vivant > 2000 ){
            ennemi->delta = SDL_GetTicks();
            projEnnemi[*projNbEnnemi].initProj(&projEnnemi[*projNbEnnemi], ennemi->rect.x + cameraRect->x, ennemi->rect.y + cameraRect->y, playerRect->x + DIM_SPRITE_PLAYER_X/2, playerRect->y + DIM_SPRITE_PLAYER_Y/2, PROJ_ENNEMI, cameraRect);
            *projNbEnnemi += 1;
        }
        
    }
    /* Actualisation des mouvements de l'ennemi*/
    ennemi->rect.x = ennemi->x - cameraRect->x;
    ennemi->rect.y = ennemi->y - cameraRect->y;
    

    
}

/* Fonction de rendu de l'ennemi, n'est pas rendu si il est mort*/
void renderEnnemi(SDL_Renderer *rendu, ennemi_t *ennemi, int frame){
    if (ennemi->pv <= 0){
        return;
    }
    //SDL_SetRenderDrawColor(rendu, 255, 0, 0, 255);
    if(ennemi->gauche){
        dessinerBarreDeVie(ennemi, rendu);
        actualisationSpriteEnnemi(4, frame, DIM_SPRITE_ENNEMI_X, DIM_SPRITE_ENNEMI_Y, GAUCHE, &ennemi->sprite, &ennemi->rect, rendu);
        //SDL_RenderFillRect(rendu, &ennemi->rect);
        
        
    }
    else if(ennemi->droite){
        dessinerBarreDeVie(ennemi, rendu);
        actualisationSpriteEnnemi(4, frame, DIM_SPRITE_ENNEMI_X, DIM_SPRITE_ENNEMI_Y, DROITE, &ennemi->sprite, &ennemi->rect, rendu);
        //SDL_RenderFillRect(rendu, &ennemi->rect);
    }
    
}

/* Fonction non utiliser dans le jeu et sert seulement à vérifier si les projectiles ont la bonne trajectoire */
void renderVecteur(SDL_Renderer *rendu, ennemi_t *ennemi, SDL_Rect * playerRect){
    point_t A;
    point_t B;
    A.x = ennemi->rect.x + ennemi->rect.w / 2;
    A.y = ennemi->rect.y + ennemi->rect.h / 2;
    B.x = playerRect->x + playerRect->w / 2;
    B.y = playerRect->y + playerRect->h / 2;
    
    DessinerLigneEnnemiVu(A, B, rendu);

}  

void renderEnemies(ennemi_t* ennemi, SDL_Renderer* rendu, int frame) {
    for (int i = 0; i < NB_ENNEMI; i++){
        ennemi[i].renderEnnemi(rendu, &ennemi[i], frame);
    }
}
