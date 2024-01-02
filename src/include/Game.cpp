#include "Game.h"
#include <string>
#include<cstdlib>

#include "SDL2/SDL_ttf.h"

#include <random>
#include <sstream>
#include "time.h"
#include "math.h"

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

bool Game::isRunning = false;

SDL_Rect border = {1,1,78,58};
SDL_Rect midLine = {399,20,2,560};


SDL_FRect player1 = {40,275,4,100};
SDL_FRect player2 = {758,275,4,100};

int p1Score =0;
int p2Score =0;

std::stringstream p1strm;
std::stringstream p2strm;



SDL_FRect ball = {396,296,8,8};

double ballVelX;
double ballVelY;

double p1VelY =0;
double p2VelY =0;


std::string p1ScoreText = std::to_string(p1Score);
std::string p2ScoreText = std::to_string(p2Score);


Game::Game()
{}

Game::~Game()
{}

void Game::init(const char* title, int w, int h, bool fullscreen)
{
    int flags =0;
    if(fullscreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if(SDL_Init(SDL_INIT_EVERYTHING)==0)
    {
        std::cout<<"Subsystems Initialised!..."<< std::endl;
        window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, flags);
        if(window)
        {
            std::cout<<"Window created!"<<std::endl;
        }
        renderer = SDL_CreateRenderer(window, -1, 0);

        if(renderer)
        {
            std::cout<<"Renderer created!"<<std::endl;
        }

        isRunning = true;

        std::cout << "Player 1 Score:" << p1Score << std::endl;
        std::cout << "Player 2 Score:" << p2Score << std::endl;

        ballVelX = 0.07;
        ballVelY = 0.01;

        srand(time_t());
        SDL_Delay(1000);


    }

}

void Game::handleEvents(double frameTime)
{
    SDL_PollEvent(&event);
    switch(event.type)
    {
    case SDL_QUIT:
        isRunning = false;
        break;
    default:
        break;
    }




}

void Game::update(double frameTime)
{

    if(player2.x <= ball.x+ball.w && player2.y <= ball.y && player2.y + player2.h >= ball.y + ball.h)
    {

        ballVelX *= -1;

    }
    if(player1.x + player1.w >= ball.x && player1.y <= ball.y && player1.y + player1.y + player1.h >= ball.y + ball.h)
    {

        ballVelX *= -1;

    }
    if(ball.y <= 20 || ball.y+ball.h >= 580)
    {

        ballVelY *=-1;
    }

    if(ball.x < 20 && p2Score < 10)
    {
        p2Score +=1;
        std::cout << "Player 1 Score:" << p1Score << std::endl;
        std::cout << "Player 2 Score:" << p2Score << std::endl;
        ball.x = 396;
        ball.y = 296;
        ballVelX = ((rand() % 2 + 7)/100.0) *(pow(-1,(rand()%2)));
        std::cout << ballVelX << std::endl;
        ballVelY = ((rand() % 4 + 1)/100.0) *(pow(-1,(rand()%2)));
        player1.x = 40;
        player1.y = 275;
        player2.x = 758;
        player2.y = 275;
        ball.y = rand() % 560 + 20;
        SDL_Delay(1000);


    }

    if (ball.x  + ball.w > 780 && p1Score < 10)
    {
        p1Score +=1;
        std::cout << "Player 1 Score:" << p1Score << std::endl;
        std::cout << "Player 2 Score:" << p2Score << std::endl;
        ball.x = 396;
        ball.y = 296;
        ballVelX = ((rand() % 2 + 7)/100.0) *(pow(-1,(rand()%2)));
        std::cout << ballVelX << std::endl;
        ballVelY = ((rand() % 4 + 1)/100.0) *(pow(-1,(rand()%2)));
        player1.x = 40;
        player1.y = 275;
        player2.x = 758;
        player2.y = 275;
        ball.y = rand() % 560 + 20;
        SDL_Delay(1000);

    }
    ball.x += ballVelX;
    ball.y += ballVelY;
    if(event.type == SDL_KEYDOWN)
    {
        switch(event.key.keysym.sym)
        {
        case SDLK_F1:
            if(player1.y > 20)
            {
                p1VelY = -0.1;
            }
            else{p1VelY=0;}
            break;
        case SDLK_F2:
            if((player1.y+player1.h < 580))
            {
                p1VelY = 0.1;
            }
            else{p1VelY=0;}
            break;

        case SDLK_UP:
            if(player2.y > 20)
            {
               p2VelY = -0.1;
            }
            else{p2VelY=0;}

            break;
        case SDLK_DOWN:
            if((player2.y + player2.h) < 580)
            {
                p2VelY = 0.1;
            }
            else{p2VelY=0;}
            break;
        default:
            break;

        }
    }

    if(event.type == SDL_KEYUP)
    {
        switch(event.key.keysym.sym)
        {
        case SDLK_F1:
            p1VelY =0;
            break;
        case SDLK_F2:
            p1VelY =0;
            break;
        case SDLK_UP:
            p2VelY =0;
            break;
        case SDLK_DOWN:
            p2VelY =0;
            break;

        case SDLK_ESCAPE:
            isRunning = false;
            break;
        default:
            break;

        }
    }
    player1.y += p1VelY;
    player2.y += p2VelY;

    if(p1Score == 10 || p2Score == 10)
    {
        if(p1Score == 10)
        {
            std::cout  << "Player 1 Wins!" << std::endl;
        }
        if(p2Score == 10)
        {
            std::cout  << "Player 1 Wins!" << std::endl;
        }
        SDL_Delay(1000);
        isRunning = false;
    }

}

void Game::render()
{

    p1strm << p1Score;
    p2strm << p2Score;


    SDL_SetRenderDrawColor(renderer,0,0,0,0);   //Draw Background colour
    SDL_RenderClear(renderer);      //Draws

    SDL_SetRenderDrawColor(renderer, 255,255,255,255);      //White for Objects
    SDL_RenderSetScale(renderer,10,10);     //scale for border
    SDL_RenderDrawRect(renderer,&border);   //draw border
    SDL_RenderSetScale(renderer,1,1);       //reset scale
    SDL_RenderFillRect(renderer, &midLine); //draw midLine



    SDL_RenderFillRectF(renderer, &player1);   //Draw Player 1
    SDL_RenderFillRectF(renderer, &player2);   //Draw Player 2
    SDL_RenderFillRectF(renderer, &ball);    //Draw ball



    SDL_RenderPresent(renderer);

}

void Game::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Game Cleaned!" << std::endl;
}

