bool replay_hover(int x, int y);
bool check_hover(int x, int y);
bool save_hover(int x, int y);
bool logout_hover(int x, int y);
bool usernameText_hover(int x, int y);
bool passwordText_hover(int x, int y);
bool ok_hover(int x, int y);
bool login_hover(int x, int y);
bool signin_hover(int x, int y);
bool start_hover(int x, int y);
bool import_hover(int x, int y);
bool score_hover(int x, int y);
bool title_hover(int x, int y);
bool easy_hover(int x, int y);
bool medium_hover(int x, int y);
bool hard_hover(int x, int y);
void mouseGridPosition(int x, int y, int *l, int *r);
bool checkGrid();
void gridGen(int difficulte);
void save();
void import();
void recommencer();
void getUsernameInput(bool continuer, char input[20], SDL_Surface *window);
void getPasswordInput(bool continuer, char input[20], SDL_Surface *window);
void login(char inputU[20], char inputP[20], int *menuJeu, int *menuCon);
void createAcc(int *menuCon);
