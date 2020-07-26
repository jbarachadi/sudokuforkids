#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>

#include "constant.h"
#include "heads.h"
#include "structures.c"


TTF_Font *primary_font;
TTF_Font *title_font;
TTF_Font *subtitle_font;
TTF_Font *correct_font;

SDL_Color bg_color = {61, 82, 122};
SDL_Color fg_color = {255, 255, 255};
SDL_Color title_color = {255, 255, 255};
SDL_Color black = {0,0,0};

SDL_Surface *uText, *pText;

SDL_Surface *loginPanel, *signinPanel, *usernamePanel, *passwordPanel, *usernameTextPanel, *passwordTextPanel, *okPanel;
SDL_Rect loginPos, signinPos, usernamePos, passwordPos, usernameTextPos, passwordTextPos, okPos;

SDL_Surface *startPanel, *importPanel, *scorePanel, *logoutPanel;
SDL_Rect startPos, importPos, scorePos, logoutPos;

SDL_Surface *easyPanel, *mediumPanel, *hardPanel;
SDL_Rect easyPos, mediumPos, hardPos;

SDL_Surface *contentPanel, *replayPanel, *checkPanel, *savePanel, *titlePanel, *subtitlePanel, *grillePanel, *correctPanel, *correctTextPanel, *incorrectPanel, *incorrectTextPanel;
SDL_Rect contentPos, replayPos, checkPos, savePos, titlePos, subtitlePos, grillePos, correctPos, correctTextPos, incorrectPos, incorrectTextPos;

int grille[4][4] = {
{0,3,2,1},{0,1,3,4},{0,4,1,2},{1,2,0,3}
};
bool state[4][4] = {false};
SDL_Surface *grillePanels[4][4];
SDL_Surface *grilleValues[4][4];
SDL_Rect grillePositions[4][4];



int main(int argc, char *argv[]) {
    /*for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            grille[i][j] = 0;
        }
    }*/
    //gridGen(1);

    //srand(time(NULL));

    int correct = 0, menuJeu = 0, menuCon = 0, difficulty=1, okValue = 2, doneOK = 2;

	SDL_Init(SDL_INIT_VIDEO);
	atexit(SDL_Quit);

	TTF_Init();
	SDL_Surface *window = SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);

	primary_font = TTF_OpenFont("SHOWG.TTF", 24);
	title_font = TTF_OpenFont("SHOWG.TTF", 40);
	subtitle_font = TTF_OpenFont("SHOWG.TTF", 14);
	correct_font = TTF_OpenFont("SHOWG.TTF",42);


    contentPanel = SDL_CreateRGBSurface(SDL_SWSURFACE, WINDOW_WIDTH, WINDOW_HEIGHT, 32, rmask, gmask, bmask, amask);
    SDL_FillRect(contentPanel, NULL, SDL_MapRGB(contentPanel->format, bg_color.r, bg_color.g, bg_color.b));
    contentPos.x = contentPos.y = 0;

    loginPanel = TTF_RenderText_Solid(primary_font, "Se connecter", title_color);
    loginPos.x = WINDOW_WIDTH / 2 - loginPanel->w / 2;
    loginPos.y = WINDOW_HEIGHT / 2 - loginPanel->h / 2 - 70;

    signinPanel = TTF_RenderText_Solid(primary_font, "S'inscrire", title_color);
    signinPos.x = WINDOW_WIDTH / 2 - signinPanel->w / 2;
    signinPos.y = WINDOW_HEIGHT / 2 - signinPanel->h / 2 + 70;

    usernamePanel = TTF_RenderText_Solid(primary_font, "Pseudo :", title_color);
    usernamePos.x = WINDOW_WIDTH / 2 - usernamePanel->w / 2 - 115;
    usernamePos.y = WINDOW_HEIGHT / 2 - usernamePanel->h / 2 + - 40;

    passwordPanel = TTF_RenderText_Solid(primary_font, "Mot de passe :", title_color);
    passwordPos.x = WINDOW_WIDTH / 2 - passwordPanel->w / 2 - 150;
    passwordPos.y = WINDOW_HEIGHT / 2 - passwordPanel->h / 2 + 40;

    uText = TTF_RenderText_Solid(primary_font, "", black);

    okPanel = TTF_RenderText_Solid(primary_font, "OK", title_color);
    okPos.x = WINDOW_WIDTH / 2 - okPanel->w / 2 + 50;
    okPos.y = WINDOW_HEIGHT / 2 - okPanel->h / 2 + 80;

    startPanel = TTF_RenderText_Solid(primary_font, "Commencer une partie", title_color);
    startPos.x = WINDOW_WIDTH / 2 - startPanel->w / 2;
    startPos.y = WINDOW_HEIGHT / 2 - startPanel->h / 2 - 140;

    importPanel = TTF_RenderText_Solid(primary_font, "Charger une partie", title_color);
    importPos.x = WINDOW_WIDTH / 2 - importPanel->w / 2;
    importPos.y = WINDOW_HEIGHT / 2 - importPanel->h / 2 - 50;

    scorePanel = TTF_RenderText_Solid(primary_font, "Scores", title_color);
    scorePos.x = WINDOW_WIDTH / 2 - scorePanel->w / 2;
    scorePos.y = WINDOW_HEIGHT / 2 - scorePanel->h / 2 + 40;

    logoutPanel = TTF_RenderText_Solid(primary_font, "Se deconnecter", title_color);
    logoutPos.x = WINDOW_WIDTH / 2 - logoutPanel->w / 2;
    logoutPos.y = WINDOW_HEIGHT / 2 - logoutPanel->h / 2 + 130;

    replayPanel = TTF_RenderText_Solid(primary_font, "Recommencer", fg_color);
    replayPos.x = 30;
    replayPos.y = WINDOW_HEIGHT - 50;

    checkPanel = TTF_RenderText_Solid(primary_font, "Valider", fg_color);
    checkPos.x = WINDOW_WIDTH / 2 - 50;
    checkPos.y = WINDOW_HEIGHT - 50;

    savePanel = TTF_RenderText_Solid(primary_font, "Enregistrer", fg_color);
    savePos.x = WINDOW_WIDTH - 210;
    savePos.y = WINDOW_HEIGHT - 50;

    titlePanel = TTF_RenderText_Solid(title_font, "SUDOKU", title_color);
    titlePos.x = WINDOW_WIDTH / 2 - titlePanel->w / 2;
    titlePos.y = 10;

    subtitlePanel = TTF_RenderText_Solid(subtitle_font, "pour enfants", title_color);
    subtitlePos.x = WINDOW_WIDTH / 2 - subtitlePanel->w / 2;
    subtitlePos.y = 5 + titlePanel->h + 1;

    easyPanel = TTF_RenderText_Solid(primary_font, "Facile", title_color);
    easyPos.x = WINDOW_WIDTH / 2 - easyPanel->w / 2;
    easyPos.y = WINDOW_HEIGHT / 2 - easyPanel->h / 2 - 70;

    mediumPanel = TTF_RenderText_Solid(primary_font, "Moyen", title_color);
    mediumPos.x = WINDOW_WIDTH / 2 - mediumPanel->w / 2;
    mediumPos.y = WINDOW_HEIGHT / 2 - mediumPanel->h / 2 + 0;

    hardPanel = TTF_RenderText_Solid(primary_font, "Difficile", title_color);
    hardPos.x = WINDOW_WIDTH / 2 - hardPanel->w / 2;
    hardPos.y = WINDOW_HEIGHT / 2 - hardPanel->h / 2 + 70;

    usernameTextPanel = SDL_CreateRGBSurface(SDL_SWSURFACE, 200, 50, 32, rmask, gmask, bmask, amask);
    SDL_FillRect(usernameTextPanel, NULL, SDL_MapRGB(usernameTextPanel->format, 255, 255, 255));
    usernameTextPos.x = WINDOW_WIDTH / 2 - usernameTextPanel->w / 2 + 50;
    usernameTextPos.y = WINDOW_HEIGHT / 2 - usernameTextPanel->h / 2 - 40;

    passwordTextPanel = SDL_CreateRGBSurface(SDL_SWSURFACE, 200, 50, 32, rmask, gmask, bmask, amask);
    SDL_FillRect(passwordTextPanel, NULL, SDL_MapRGB(passwordTextPanel->format, 255, 255, 255));
    passwordTextPos.x = WINDOW_WIDTH / 2 - passwordTextPanel->w / 2 + 50;
    passwordTextPos.y = WINDOW_HEIGHT / 2 - passwordTextPanel->h / 2 + 40;

    grillePanel = SDL_CreateRGBSurface(SDL_SWSURFACE, 410, 410, 32, rmask, gmask, bmask, amask);
    SDL_FillRect(grillePanel, NULL, SDL_MapRGB(grillePanel->format, 255, 255, 255));
    grillePos.x = WINDOW_WIDTH / 2 - grillePanel->w / 2;
    grillePos.y = WINDOW_HEIGHT / 2 - grillePanel->h / 2;

    correctPanel = SDL_CreateRGBSurface(SDL_SWSURFACE, 410, 410, 32,rmask,gmask,bmask,amask);
    SDL_FillRect(correctPanel, NULL, SDL_MapRGB(correctPanel->format, 16, 255, 0));
    correctPos.x = WINDOW_WIDTH / 2 - grillePanel->w / 2;
    correctPos.y = WINDOW_HEIGHT / 2 - grillePanel->h / 2;

    correctTextPanel = TTF_RenderText_Solid(correct_font, "FELICITATIONS !!", title_color);
    correctTextPos.x = WINDOW_WIDTH / 2 - correctTextPanel->w / 2;
    correctTextPos.y = WINDOW_HEIGHT / 2 - correctTextPanel->h / 2;

    incorrectPanel = SDL_CreateRGBSurface(SDL_SWSURFACE, 410, 410, 32,rmask,gmask,bmask,amask);
    SDL_FillRect(incorrectPanel, NULL, SDL_MapRGB(incorrectPanel->format, 255, 0, 0));
    incorrectPos.x = WINDOW_WIDTH / 2 - grillePanel->w / 2;
    incorrectPos.y = WINDOW_HEIGHT / 2 - grillePanel->h / 2;

    incorrectTextPanel = TTF_RenderText_Solid(correct_font, "FAUX..", title_color);
    incorrectTextPos.x = WINDOW_WIDTH / 2 - incorrectTextPanel->w / 2;
    incorrectTextPos.y = WINDOW_HEIGHT / 2 - incorrectTextPanel->h / 2;


    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            if(grille[i][j]!=0)
            {
                state[i][j] = false;
            }
            else
            {
                state[i][j] = true;
            }
            if(i<2 && j<2)
            {
                grillePanels[i][j] = IMG_Load("bloc1.png");
                grillePositions[i][j].x = grillePos.x + j * 100;
                grillePositions[i][j].y = grillePos.y + i * 100;

                if(i>=2)
                {
                    grillePositions[i][j].y += 10;
                }
                if(j>=2)
                {
                    grillePositions[i][j].x += 10;
                }
            }
            else if(i<2 && j>=2)
            {
                grillePanels[i][j] = IMG_Load("bloc2.png");
                grillePositions[i][j].x = grillePos.x + j * 100;
                grillePositions[i][j].y = grillePos.y + i * 100;

                if(i>=2)
                {
                    grillePositions[i][j].y += 10;
                }
                if(j>=2)
                {
                    grillePositions[i][j].x += 10;
                }
            }
            else if(i>=2 && j<2)
            {
                grillePanels[i][j] = IMG_Load("bloc3.png");
                grillePositions[i][j].x = grillePos.x + j * 100;
                grillePositions[i][j].y = grillePos.y + i * 100;

                if(i>=2)
                {
                    grillePositions[i][j].y += 10;
                }
                if(j>=2)
                {
                    grillePositions[i][j].x += 10;
                }
            }
            else
            {
                grillePanels[i][j] = IMG_Load("bloc4.png");
                grillePositions[i][j].x = grillePos.x + j * 100;
                grillePositions[i][j].y = grillePos.y + i * 100;

                if(i>=2)
                {
                    grillePositions[i][j].y += 10;
                }
                if(j>=2)
                {
                    grillePositions[i][j].x += 10;
                }
            }
        }
    }


	bool done = false;
	//bool continuer = true;//care
	char usernameInput[20] = {0};
	char passwordInput[20] = {0};
	int usernameClicked = 0;
	int pwdClicked = 0;
	char typed;
	char tmp[8];
    while (!done)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                done = true;
                break;
            case SDL_KEYDOWN:
                if (usernameClicked == 1) {
                    typed = (char) event.key.keysym.sym;
                    sprintf(tmp, "%c", typed);
                    strcat(usernameInput, tmp);
                } else if (pwdClicked == 1) {
                    typed = (char) event.key.keysym.sym;
                    sprintf(tmp, "%c", typed);
                    strcat(passwordInput, tmp);
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                if(title_hover(event.button.x, event.button.y))
                {
                    menuJeu = 0;
                }
                if(login_hover(event.button.x, event.button.y) && menuCon==0)
                {
                    menuCon = 1;
                    okValue = 1;
                }
                if(signin_hover(event.button.x, event.button.y) && menuCon==0)
                {
                    menuCon = 1;
                    okValue = 0;
                }
                if(usernameText_hover(event.button.x, event.button.y) && menuCon==1)
                {
                    usernameClicked = 1;
                    pwdClicked = 0;
                    //getUsernameInput(continuer, &usernameInput[0], window);
                }
                if(passwordText_hover(event.button.x, event.button.y) && menuCon==1)
                {
                    pwdClicked = 1;
                    usernameClicked = 0;
                    //getPasswordInput(continuer, &passwordInput[0], window);
                }
                if(ok_hover(event.button.x, event.button.y) && menuCon==1)
                {
                    //menuJeu = 0;
                    menuCon = 3;
                    if(okValue == 1)
                    {
                        //login(usernameInput,passwordInput,&menuJeu,&menuCon);
                        menuJeu = 0;
                    }
                    else if(okValue == 0)
                    {
                        //createAcc(&menuCon);
                        menuJeu = 0;
                    }
                }
                if(start_hover(event.button.x, event.button.y) && menuJeu==0 && menuCon==3)
                {
                    menuJeu = 1;
                }
                else if(import_hover(event.button.x, event.button.y) && menuJeu==0 && menuCon==3)
                {
                    import();
                    menuJeu = 2;
                }
                else if(logout_hover(event.button.x, event.button.y) && menuJeu==0)
                {
                    menuCon = 0;
                }
                if(menuJeu==1)
                {
                    if(easy_hover(event.button.x, event.button.y) && menuJeu==1)
                    {
                        difficulty=1;
                        menuJeu=2;
                    }
                    else if(medium_hover(event.button.x, event.button.y) && menuJeu==1)
                    {
                        difficulty=2;
                        menuJeu=2;
                    }
                    else if(hard_hover(event.button.x, event.button.y) && menuJeu==1)
                    {
                        srand(time(NULL));
                        difficulty=3;
                        menuJeu=2;
                    }

                    gridGen(difficulty);

                    for(int i=0;i<4;i++)
                    {
                        for(int j=0;j<4;j++)
                        {
                            if(grille[i][j]!=0)
                            {
                                state[i][j] = false;
                            }
                            else
                            {
                                state[i][j] = true;
                            }
                        }
                    }
                }
                if(menuJeu == 2)
                {
                    if(replay_hover(event.button.x, event.button.y))
                    {
                        correct = 0;
                        for(int i=0;i<4;i++)
                        {
                            for(int j=0;j<4;j++)
                            {
                                if(state[i][j]==true)
                                {
                                    grille[i][j]=0;
                                }
                            }
                        }
                    }
                    else if(check_hover(event.button.x, event.button.y))
                    {
                        if(checkGrid())
                        {
                            correct = 1;
                        }
                        else
                        {
                            correct = 2;
                        }
                    }
                    else if (save_hover(event.button.x, event.button.y))
                    {
                        save();
                    }
                    else
                    {
                        int i = -1, j = -1;
                        mouseGridPosition(event.button.x, event.button.y, &i, &j);
                        if(i!=-1 && j!=-1 && state[i][j]==true)
                        {
                            grille[i][j]=(grille[i][j]+1)%5;
                        }
                    }
                }
            }
        }

        SDL_FillRect(window, 0, SDL_MapRGB(window->format, 0, 0, 0));

        SDL_BlitSurface(contentPanel, NULL, window, &contentPos);
        SDL_BlitSurface(titlePanel, NULL, window, &titlePos);
        SDL_BlitSurface(subtitlePanel, NULL, window, &subtitlePos);
        if(menuCon==0)
        {
            SDL_BlitSurface(loginPanel, NULL, window, &loginPos);
            SDL_BlitSurface(signinPanel, NULL, window, &signinPos);
        }
        else if(menuCon==1)
        {
            SDL_Surface *inputText = TTF_RenderText_Solid(primary_font, usernameInput, black);
            SDL_BlitSurface(usernamePanel, NULL, window, &usernamePos);
            SDL_Surface *passwordText = TTF_RenderText_Solid(primary_font, passwordInput, black);
            SDL_BlitSurface(passwordPanel, NULL, window, &passwordPos);
            SDL_BlitSurface(usernameTextPanel, NULL, window, &usernameTextPos);
            SDL_BlitSurface(passwordTextPanel, NULL, window, &passwordTextPos);
            SDL_BlitSurface(okPanel, NULL, window, &okPos);
            SDL_BlitSurface(inputText, NULL, window, &usernameTextPos);
            SDL_BlitSurface(passwordText, NULL, window, &passwordTextPos);
        }
        else if(doneOK==1)
        {

            SDL_Surface *inputText = TTF_RenderText_Solid(primary_font, usernameInput, black);
            SDL_BlitSurface(inputText, NULL, window, &usernameTextPos);
        }
        else if(doneOK==0)
        {
            SDL_BlitSurface(uText, NULL, window, &passwordTextPos);
        }
        else if(menuJeu==0)
        {
            SDL_BlitSurface(startPanel, NULL, window, &startPos);
            SDL_BlitSurface(importPanel, NULL, window, &importPos);
            SDL_BlitSurface(scorePanel, NULL, window, &scorePos);
            SDL_BlitSurface(logoutPanel, NULL, window, &logoutPos);
        }
        else if(menuJeu==1)
        {
            SDL_BlitSurface(easyPanel, NULL, window, &easyPos);
            SDL_BlitSurface(mediumPanel, NULL, window, &mediumPos);
            SDL_BlitSurface(hardPanel, NULL, window, &hardPos);
        }
        else if(menuJeu==2)
        {
            SDL_BlitSurface(replayPanel, NULL, window, &replayPos);
            SDL_BlitSurface(checkPanel, NULL, window, &checkPos);
            SDL_BlitSurface(savePanel, NULL, window, &savePos);
            SDL_BlitSurface(grillePanel, NULL, window, &grillePos);
            for(int i=0;i<4;i++)
            {
                for(int j=0;j<4;j++)
                {
                    SDL_BlitSurface(grillePanels[i][j], NULL, window, &grillePositions[i][j]);
                    if(grille[i][j]!=0)
                    {
                        char fileName[16];
                        sprintf(fileName,"%d.png",grille[i][j]);
                        grilleValues[i][j] = IMG_Load(fileName);
                        SDL_BlitSurface(grilleValues[i][j], NULL, window, &grillePositions[i][j]);
                    }
                }
            }
            if(correct == 1)
            {
                SDL_BlitSurface(correctPanel, NULL, window, &correctPos);
                SDL_BlitSurface(correctTextPanel, NULL, window, &correctTextPos);
            }
            else if(correct == 2)
            {
                SDL_BlitSurface(incorrectPanel, NULL, window, &incorrectPos);
                SDL_BlitSurface(incorrectTextPanel, NULL, window, &incorrectTextPos);
            }
        }
        SDL_Flip(window);
    }

  return EXIT_SUCCESS;
}

bool replay_hover(int x, int y) {
    int x0 = replayPos.x, x1 = x0 + replayPanel->w;
    int y0 = replayPos.y, y1 = y0 + replayPanel->h;
    return (x >= x0 && x <= x1 && y >= y0 && y <= y1);
}
bool check_hover(int x, int y) {
    int x0 = checkPos.x, x1 = x0 + checkPanel->w;
    int y0 = checkPos.y, y1 = y0 + checkPanel->h;
    return (x >= x0 && x <= x1 && y >= y0 && y <= y1);
}
bool save_hover(int x, int y) {
    int x0 = savePos.x, x1 = x0 + savePanel->w;
    int y0 = savePos.y, y1 = y0 + savePanel->h;
    return (x >= x0 && x <= x1 && y >= y0 && y <= y1);
}
bool login_hover(int x, int y)
{
    int x0 = loginPos.x, x1 = x0 + loginPanel->w;
    int y0 = loginPos.y, y1 = y0 + loginPanel->h;
    return (x >= x0 && x <= x1 && y >= y0 && y <= y1);
}
bool logout_hover(int x, int y)
{
    int x0 = logoutPos.x, x1 = x0 + logoutPanel->w;
    int y0 = logoutPos.y, y1 = y0 + logoutPanel->h;
    return (x >= x0 && x <= x1 && y >= y0 && y <= y1);
}
bool signin_hover(int x, int y)
{
    int x0 = signinPos.x, x1 = x0 + signinPanel->w;
    int y0 = signinPos.y, y1 = y0 + signinPanel->h;
    return (x >= x0 && x <= x1 && y >= y0 && y <= y1);
}
bool usernameText_hover(int x, int y)
{
    int x0 = usernameTextPos.x, x1 = x0 + usernameTextPanel->w;
    int y0 = usernameTextPos.y, y1 = y0 + usernameTextPanel->h;
    return (x >= x0 && x <= x1 && y >= y0 && y <= y1);
}
bool passwordText_hover(int x, int y)
{
    int x0 = passwordTextPos.x, x1 = x0 + passwordTextPanel->w;
    int y0 = passwordTextPos.y, y1 = y0 + passwordTextPanel->h;
    return (x >= x0 && x <= x1 && y >= y0 && y <= y1);
}
bool username_hover(int x, int y)
{
    int x0 = usernamePos.x, x1 = x0 + usernamePanel->w;
    int y0 = usernamePos.y, y1 = y0 + usernamePanel->h;
    return (x >= x0 && x <= x1 && y >= y0 && y <= y1);
}
bool password_hover(int x, int y)
{
    int x0 = passwordPos.x, x1 = x0 + passwordPanel->w;
    int y0 = passwordPos.y, y1 = y0 + passwordPanel->h;
    return (x >= x0 && x <= x1 && y >= y0 && y <= y1);
}
bool ok_hover(int x, int y)
{
    int x0 = okPos.x, x1 = x0 + okPanel->w;
    int y0 = okPos.y, y1 = y0 + okPanel->h;
    return (x >= x0 && x <= x1 && y >= y0 && y <= y1);
}
bool start_hover(int x, int y)
{
    int x0 = startPos.x, x1 = x0 + startPanel->w;
    int y0 = startPos.y, y1 = y0 + startPanel->h;
    return (x >= x0 && x <= x1 && y >= y0 && y <= y1);
}
bool import_hover(int x, int y)
{
    int x0 = importPos.x, x1 = x0 + importPanel->w;
    int y0 = importPos.y, y1 = y0 + importPanel->h;
    return (x >= x0 && x <= x1 && y >= y0 && y <= y1);
}
bool score_hover(int x, int y)
{
    int x0 = scorePos.x, x1 = x0 + scorePanel->w;
    int y0 = scorePos.y, y1 = y0 + scorePanel->h;
    return (x >= x0 && x <= x1 && y >= y0 && y <= y1);
}
bool title_hover(int x, int y)
{
    int x0 = titlePos.x, x1 = x0 + titlePanel->w;
    int y0 = titlePos.y, y1 = y0 + titlePanel->h;
    return (x >= x0 && x <= x1 && y >= y0 && y <= y1);
}
bool easy_hover(int x, int y)
{
    int x0 = easyPos.x, x1 = x0 + easyPanel->w;
    int y0 = easyPos.y, y1 = y0 + easyPanel->h;
    return (x >= x0 && x <= x1 && y >= y0 && y <= y1);
}
bool medium_hover(int x, int y)
{
    int x0 = mediumPos.x, x1 = x0 + mediumPanel->w;
    int y0 = mediumPos.y, y1 = y0 + mediumPanel->h;
    return (x >= x0 && x <= x1 && y >= y0 && y <= y1);
}
bool hard_hover(int x, int y)
{
    int x0 = hardPos.x, x1 = x0 + hardPanel->w;
    int y0 = hardPos.y, y1 = y0 + hardPanel->h;
    return (x >= x0 && x <= x1 && y >= y0 && y <= y1);
}



void mouseGridPosition(int x, int y, int *l, int *r) {
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            int x0 = grillePositions[i][j].x, x1 = x0 + 100;
            int y0 = grillePositions[i][j].y, y1 = y0 + 100;

            if(x>=x0 && x<=x1 && y>=y0 && y<=y1)
            {
                *l = i;
                *r = j;
                return;
            }
        }
    }
}

bool checkLine(int i) {
    for(int j=0;j<4;j++)
    {
        for(int k=j+1;k<4;k++)
        {
            if(grille[i][j]==grille[i][k])
            {
                return false;
            }
        }
    }
    return true;
}

bool checkColumn(int j) {
    for(int i=0;i<4;i++)
    {
        for(int k=i+1;k<4;k++)
        {
            if(grille[i][j]==grille[k][j])
            {
                return false;
            }
        }
    }
    return true;
}

bool checkBrick(int i, int j){
    int k=i-i%2,t=j-j%2;
    for(j=t;j<t+2;j++)
    {
        for(i=k;i<k+2;i++)
        {
            for(int _j=t;_j<t+2;_j++)
            {
                for(int _i=k;_i<k+2;_i++)
                {
                    if((i!=_i || j!=_j) && grille[i][j]==grille[_i][_j])
                    {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

bool checkGrid() {
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            if(grille[i][j]==0)
            {
                return false;
            }
            if(!(checkLine(i) && checkColumn(j) && checkBrick(i,j)))
            {
                return false;
            }
        }
    }
    return true;
}

int checkLigne(int c,int i)
{
    int j;
    for(j=0;j<3;j++)
    {
        if(grille[i][j]==c)
        {
            return 1;
        }
    }
    return 0;
}

int checkColonne(int c,int j)
{
    int i;
    for(i=0;i<3;i++)
    {
        if(grille[i][j]==c)
        {
            return 1;
        }
    }
    return 0;
}

int checkBloc(int c,int i,int j)
{
    int k=i-i%2,l=j-j%2;
    for(j=l;j<l+2;j++)
    {
        for(i=k;i<k+2;i++)
        {
            if(grille[i][j]==c)
            {
                return 1;
            }
        }
    }
    return 0;
}

void remplissage(int i,int j)
{
    int c;
    c=rand()%4+1;
    if(grille[i][j]==0)
    {
        if(checkLigne(c,i)==0 && checkColonne(c,j)==0 && checkBloc(c,i,j)==0)
        {
            grille[i][j]=c;
            state[i][j]=false;
        }
        else
        {
            remplissage(i,j);
        }
    }
}

void suppression(int difficulte)
{
    int i,j,c;
    for(j=0;j<4;j++)
    {
        for(i=0;i<difficulte;i++)
        {
            c=rand()%4+0;
            grille[c][j]=0;
            state[c][j]=true;
        }
    }
}

void gridGen(int difficulte)
{
    int i,j;
    for(j=0;j<4;j++)
    {
        for(i=0;i<4;i++)
        {
            remplissage(i,j);
        }
    }
    suppression(difficulte);
}

void save()
{
    int i,j;
    FILE *file=fopen("sauvegarde_grille.txt","w");
    for(j=0;j<4;j++)
    {
        for(i=0;i<4;i++)
        {
            fprintf(file,"%d\n",grille[i][j]);
        }
    }
    fclose(file);
}

void import()
{
    int i,j;
    FILE *file=fopen("sauvegarde_grille.txt","r");
    for(j=0;j<4;j++)
    {
        for(i=0;i<4;i++)
        {
            fscanf(file,"%d\n",&grille[i][j]);
        }
    }
    fclose(file);
}

void recommencer()
{
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            if(state[i][j]==true)
            {
                grille[i][j]=0;
            }
        }
    }
}

void getUsernameInput(bool continuer, char input[20], SDL_Surface *window)
{
    int i;
    while(continuer)
        {
        SDL_Event _event;
        while(SDL_PollEvent(&_event))
        {
            switch(_event.type)
            {
            case SDLK_RETURN:
                continuer = false;
                break;
            case SDLK_BACKSPACE:
                if(i>0)
                {
                    i--;
                    input[i] = ' ';
                }
                break;
            case SDLK_SPACE:
                if((i+1)<20)
                {
                    input[i] = ' ';
                    i++;
                }
                break;
            case SDLK_DELETE:
                for(int j=i;j<19;j++)
                {
                    if(input[i+1] != '\0')
                    {
                        input[j] = input[j+1];
                    }
                    else
                    {
                        input[j] = ' ';
                    }
                }
                break;
            default:
                char caractere = (char)_event.key.keysym.sym;
                if((i+1)<20)
                {
                    input[i] = caractere;
                    i++;
                }
                break;
            }
            break;
        }
        //text = TTF_RenderText_Blended(primary_font, input, black);
    }
}

void getPasswordInput(bool continuer, char input[20], SDL_Surface *window)
{
    int i;
    while(continuer)
        {
        SDL_Event _event;
        while(SDL_PollEvent(&_event))
        {
            switch(_event.type)
            {
            case SDLK_RETURN:
                continuer = false;
                break;
            case SDLK_BACKSPACE:
                if(i>0)
                {
                    i--;
                    input[i] = ' ';
                }
                break;
            case SDLK_SPACE:
                if((i+1)<20)
                {
                    input[i] = ' ';
                    i++;
                }
                break;
            case SDLK_DELETE:
                for(int j=i;j<19;j++)
                {
                    if(input[i+1] != '\0')
                    {
                        input[j] = input[j+1];
                    }
                    else
                    {
                        input[j] = ' ';
                    }
                }
                break;
            default:
                char caractere = (char)_event.key.keysym.sym;
                if((i+1)<20)
                {
                    input[i] = caractere;
                    i++;
                }

                break;
                continuer = false;
            }
            break;
        }
        //text = TTF_RenderText_Blended(primary_font, input, black);
    }
}

/*void login(char inputU[20], char inputP[20], int *menuJeu, int *menuCon)
{
    int found=0,uLine=0,pLine=0;
    char enom[20],emdp[20];
    FILE *uFile=fopen("noms_joueurs.txt","r+");
    FILE *pFile=fopen("mdps_joueurs.txt","r+");
    while(!feof(uFile))
    {
        fscanf(uFile,"%s",enom);
        if(!strcmp(inputU,enom))
        {
            found=1;
            break;
        }
        else
        {
            uLine++;
        }
    }
    if(found==0)
    {
        uLine=0;
        createAcc(menuCon);
    }
    else
    {
        found=0;
        while(!feof(pFile))
        {
            fscanf(pFile,"%s",emdp);
            if(pLine==uLine)
            {
                if(!strcmp(inputP,emdp))
                {
                    found=1;
                    break;
                }
                else
                {
                    break;
                }
            }
            else
            {
                pLine++;
            }
        }
    }
    if(found!=0)
    {
        menuJeu = 0;
    }
    fclose(uFile);
    fclose(pFile);
}

void createAcc(int *menuCon)
{
    char enom[20],emdp[20];
    players *nJ=(players*)malloc(sizeof(players));
    FILE *userFile=fopen("noms_joueurs.txt","a+");
    FILE *passFile=fopen("mdps_joueurs.txt","a+");
    while(!feof(userFile))
    {
        fscanf(userFile,"%s",enom);
        if(!strcmp(nJ->name,enom))
        {
            createAcc(menuCon);
        }
    }
    fprintf(userFile,"%s\n",nJ->name);
    fprintf(passFile,"%s\n",nJ->password);
    fclose(userFile);
    fclose(passFile);
    menuCon = 0;
}*/
