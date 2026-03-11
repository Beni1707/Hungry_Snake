#include <iostream> 
#include <raylib.h>
#include<deque>
#include <raymath.h>
using namespace std;

//Definying Colors 

Color Green ={ 173, 204, 96, 255};
Color Dark_Green={43, 51, 24, 255}; 

//Initialiser les grilles 
float cellsize = 30;
float cellcount=25; 
//Le temps de deplacement du serpent 
double lastUpdate =0; 
int offset =75; 




// La fonction booleenne qui verifier si l'element est dans la la meme position que l'une des case du corps du serpent 
bool ElementInDeque(Vector2 element , deque <Vector2>deque )
{
     for ( unsigned int i =0 ; i < deque.size (); i++ )
     {
        if ( Vector2Equals(deque[i], element ))
        {
            return true; 
        }
     }
     return false ;
}

bool eventTrigged ( double ineterval)
{
    double currentTime = GetTime();
    if ( currentTime- lastUpdate >= ineterval)
    {
        lastUpdate= currentTime; 
        return true;    
    }
    return false; 
}

//Les classes 

class Food 
{
    public : 
    Vector2 position; 
    Texture2D texture ;
    
    // Constructor 

    Food (deque<Vector2> snakeBody)
    {
        Image image = LoadImage ("apple1.png");
        texture = LoadTextureFromImage(image); 
        UnloadImage (image); 
        position =GenerateRandomPos(snakeBody); 

    }
    
    //Destructor 
    ~Food ()
    {
        UnloadTexture(texture);
    }
    
    //Les methodes 
    
    void Draw ()
    {
       DrawTexture( texture,offset+ position.x * cellsize ,offset+ position.y * cellsize , WHITE); 
    }
    //Methode qui genere la position aleatoire de la food 
    Vector2 GenerateRandomPlace()
    {
        float x = GetRandomValue (0,cellcount-1); 
        float y = GetRandomValue(0,cellcount-1); 
        return Vector2{ x,y}; 
    }
   
    //Methode qui genere des postion aleatoires differentes pour la nourriture 
    Vector2 GenerateRandomPos(deque <Vector2> snakeBody)
    {
       
        Vector2 position = GenerateRandomPlace(); 

        while (ElementInDeque (position, snakeBody))
        {
                position= GenerateRandomPlace(); 
        }
        return position ; 
    }

};

// La classe qui represente le serpent 
class Snake 
{
    public : 
        deque <Vector2> body ={ Vector2 {6,9}, Vector2{5,9}, Vector2{4,9} };
        Vector2 direction = {1,0}; 
        bool addSegment = false; 
        
        //Dessiner le serpent sur l'ecran 
        void Draw ()
        {
            for ( unsigned int i =0 ;  i < body.size(); i++)
            {
                float x = body[i]. x;
                float  y = body[i].y; 
                Rectangle segment = {offset+ x*cellsize ,offset+ y * cellsize , cellsize, cellsize };
                DrawRectangleRounded(segment , 0.5, 6 ,  Dark_Green); 
            }
        }

        //Mouvement du serpent 

        void Update ()
        {
             body.push_front(Vector2Add(body[0], direction)); 
            if (addSegment == true )
            {
               
                addSegment=false;  
            }
            else {
                 // Faire avancer le serpent en suppriment le carree qui se trouve a la queueu 
            body.pop_back();
          
            }
           
        }
        //La methode qui va reste le jeux 

        void Reset()
        {
            body= { Vector2{6,9}, Vector2{5,9}, Vector2{4,9}}; 
            direction= {1,0}; 
        }

}; 

class Game 
{
    public : 
    Food food = Food(snake.body); 
    Snake snake =Snake(); 
    bool running = true ; 
    int score=0;
    //Sound eatSound;
    //Sound WallSound; 
    
    //Game()
   //{
        //InitAudioDevice(); 
      // eatSound=LoadSound ("src/winner.mp3");
       // WallSound=LoadSound("src/GameOver.mp3");
   // }

   // ~Game()
  // {
        //UnloadSound (eatSound);
        //UnloadSound(WallSound); 
         //CloseAudioDevice(); 
   // }
  

    void Draw ()
    {
        snake.Draw();
        food.Draw(); 
    }
    
    void Update()
    {
        if (running )
        {
             snake.Update();
             ChechkCollisionWithFood(); 
             CheckCollisionWithEdge(); 
             CheckCollisionWithTail(); 

        }
       
        
    }
    
    void ChechkCollisionWithFood ()// Verifier la collision avec la nourriture 
    {
        if (Vector2Equals(snake.body[0], food.position))
        {
            food.position= food.GenerateRandomPos(snake.body); 
            snake.addSegment=true; 
            score++;
           // PlaySound(eatSound);
        }
    }
    void CheckCollisionWithEdge()
    {
        if (snake.body[0].x==cellcount|| snake.body[0].x==-1)
        {
            GameOver();
        }
        if (snake.body[0].y==cellcount || snake.body[0].y==-1)
        {
            GameOver();
        }
    }
    void CheckCollisionWithTail()
    {
        deque<Vector2>headlessBody= snake.body;
        headlessBody.pop_front();
        if (ElementInDeque(snake.body[0], headlessBody))
        {
            GameOver(); 
        }
    }
    void GameOver()
    {
        snake.Reset();
        food.position= food.GenerateRandomPos(snake.body); 
         score=0;
        //PlaySound(WallSound); 
        running = false; 
    }
}; 
//The main function 

int main ()
{
    //opening the window 
     InitWindow (2*offset + cellsize * cellcount ,2*offset +  cellsize * cellcount , "Hungry Snake"); 
    SetTargetFPS (60); 

    Game game =Game();

    //Creating the Game loop 
     while (WindowShouldClose()== false)
    {
        BeginDrawing();
      //Drawing 
        if ( eventTrigged (0.2))
        {
            game.Update(); 
        }
        //on va gerer les directions du serpent 
        
        if (IsKeyPressed(KEY_UP)&& game.snake.direction.y != 1)
        {
            game.snake.direction= {0,-1}; 
            game.running=true;
        } 
        if (IsKeyPressed(KEY_DOWN)&& game.snake.direction.y != -1)
        {
            game.snake.direction= {0,1}; 
            game.running=true;
        } 
        
        if (IsKeyPressed(KEY_RIGHT)&& game.snake.direction.x != -1)
        {
            game.snake.direction= {1,0}; 
            game.running=true;
        } 
        
        if (IsKeyPressed(KEY_LEFT)&& game.snake.direction.x != 1)
        {
            game.snake.direction= {-1,0}; 
            game.running=true;
        } 
            
        
    ClearBackground(Green); 
    DrawRectangleLinesEx(Rectangle{(float) offset-5, (float) offset -5 , (float)cellsize * cellcount+10,(float)cellsize * cellcount+10 }, 5, Dark_Green); 
    DrawText("Hungry Snake", offset-5, 20 , 40 , Dark_Green); 
    DrawText(TextFormat( "%i" ,game.score),offset-5, offset+cellsize*cellcount+10, 40, Dark_Green ) ;
     game.Draw(); 
        

        EndDrawing(); 
    }
    

    //Closing the Window
    CloseWindow(); 
   
     return 0; // returns 0 if everything is good 
    
}