#include <iostream>
#include <signal.h>
#include <cstdlib>
#include <ctime>
#include <allegro5\allegro.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_native_dialog.h>
#include <allegro5\allegro_primitives.h>

#include "..\Headers\Snake.h"
#include "..\Headers\SnakeBody.h"
#include "..\Headers\Food.h"

#include <vector>

using std::vector;
using namespace std;

bool reposition = false;
enum KEYS {UP, DOWN, LEFT, RIGHT};

bool collision(int x, int y, int tamanho, int obj_x, int obj_y, int obj_tam)
{
	if(x+tamanho > obj_x && x < obj_x+obj_tam && y+tamanho > obj_y && y < obj_y+obj_tam)
	{  return true;  }
	else
	{  return false; }
}

int randNumber()
{
	return (rand()%500) ;
}

int AllegroSnake(void)
{
	int width = 800, height = 600, pos_x = width / 2, pos_y = height / 2;
	bool done = false, foodGotten = false,  outOfScreen = false;
	bool keys[4] = {false, false, false, false};

	int newXPosition;
	int newYPosition;

	long index = 0, fullSize = 0;
	char cDirection;


	Snake snake;
	SnakeBody snakeBody( pos_x, pos_y, pos_x + 30, pos_y + 30, 30, 'R' );
	snake.vSnake.push_back(snakeBody);

	Food food( 30, 30, 45, 45, 15 );

	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;

	srand((unsigned)time(NULL));

	if(!al_init())
		return -1;

	al_init_font_addon();
	al_init_ttf_addon();
	al_init_primitives_addon();
	al_install_keyboard();

	ALLEGRO_FONT *text = al_load_font("Resources//fonts//cactus.ttf", 24, 0);

	display = al_create_display(width, height);

	if(!display)
		return -1;

	event_queue = al_create_event_queue();

	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_display_event_source(display));

	//================ Timer ================
	ALLEGRO_TIMER *timer = NULL;
	al_rest(5.0); //Timer de n segundos
	int FPS = 60;
	timer = al_create_timer(10.0 / FPS);
	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	al_start_timer(timer);
	//=======================================

	keys[RIGHT] = true;

	while(!done)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch(ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_UP:
				if (keys[DOWN]) break;
				keys[UP] = true;
				keys[DOWN] = false;
				keys[RIGHT] = false;
				keys[LEFT] = false;
				cDirection = 'U';
				break;
			case ALLEGRO_KEY_DOWN:
				if (keys[UP]) break;
				keys[UP] = false;
				keys[DOWN] = true;
				keys[RIGHT] = false;
				keys[LEFT] = false;
				cDirection = 'D';
				break;
			case ALLEGRO_KEY_RIGHT:
				if (keys[LEFT]) break;
				keys[UP] = false;
				keys[DOWN] = false;
				keys[RIGHT] = true;
				keys[LEFT] = false;
				cDirection = 'R';
				break;
			case ALLEGRO_KEY_LEFT:
				if (keys[RIGHT]) break;
				keys[UP] = false;
				keys[DOWN] = false;
				keys[RIGHT] = false;
				keys[LEFT] = true;
				cDirection = 'L';
				break;
			}
			snake.vSnake.at(0).SetDirection(cDirection);
		}

		else if(ev.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch(ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			}
		}

		else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			done = true;
		}

		else if(ev.type == ALLEGRO_EVENT_TIMER)
		{
			if (snake.GetSize() < 5) {
				pos_y -= keys[UP] * 10;
				pos_y += keys[DOWN] * 10;
				pos_x -= keys[LEFT] * 10;
				pos_x += keys[RIGHT] * 10;
			}

			//refresh the positions
			for (int i = snake.GetSize() - 1;
					i >= 0;
					--i)
			{
				if (snake.vSnake.at(i).GetDirection()=='U'){
					snake.vSnake.at(i).SetY1(pos_y + i * 30);
					snake.vSnake.at(i).SetX1(pos_x);
				}else if (snake.vSnake.at(i).GetDirection()=='D'){
					snake.vSnake.at(i).SetY1(pos_y - i * 30);
					snake.vSnake.at(i).SetX1(pos_x);
				}else if (snake.vSnake.at(i).GetDirection()=='L'){
					snake.vSnake.at(i).SetY1(pos_y);
					snake.vSnake.at(i).SetX1(pos_x + i * 30);
				}else if (snake.vSnake.at(i).GetDirection()=='R'){
					snake.vSnake.at(i).SetY1(pos_y);
					snake.vSnake.at(i).SetX1(pos_x - i * 30);
				}
			}

			al_clear_to_color(al_map_rgb(0, 0, 0)); //clear

			//draw the snake beginning by the end
			for (int i = snake.GetSize() - 1;
					i >= 0;
					--i)
			{
				al_draw_filled_rectangle(snake.vSnake.at(i).GetX1(),
						snake.vSnake.at(i).GetY1() ,
						snake.vSnake.at(i).GetX1() + snake.vSnake.at(i).GetSize(),
						snake.vSnake.at(i).GetY1() + snake.vSnake.at(i).GetSize(),
						al_map_rgb(255, 255, 0));

				if (i > 0) snake.vSnake.at(i).SetDirection(snake.vSnake.at(i - 1).GetDirection());

			}
		}

		foodGotten = collision(snake.vSnake.at(0).GetX1(),
				snake.vSnake.at(0).GetY1(),
				snake.vSnake.at(0).GetSize(), food.GetX1(), food.GetY1(), food.GetSize());

		//*******************
		//GAME OVER//
		if (snake.vSnake.at(0).GetX1() <= 0 || snake.vSnake.at(0).GetX1() >= (800 - snake.vSnake.at(0).GetSize()) )
			outOfScreen = true;

		if (snake.vSnake.at(0).GetY1() <= 0 || snake.vSnake.at(0).GetY1() >= (600 - snake.vSnake.at(0).GetSize())  )
			outOfScreen = true;

		if (outOfScreen) {
			al_draw_text(text, al_map_rgb(255, 0, 255), width / 2, height / 2, 0, "You are a joke, man!");
			done = true;
		}
		//*******************

		if (foodGotten) {
			newXPosition = randNumber();
			newYPosition = randNumber();
			food.SetX1(newXPosition);
			food.SetY1(newYPosition);
			food.SetX2(newXPosition + 15);
			food.SetY2(newYPosition + 15);

			if (keys[UP]){

				SnakeBody snakeBody (
						snake.vSnake.end()->GetX1() ,
						snake.vSnake.end()->GetY1() + 30,
						snake.vSnake.end()->GetX1() ,
						snake.vSnake.end()->GetY1() + 60,
						snake.vSnake.end()->GetSize(),
						snake.vSnake.end()->GetDirection());

			}else if (keys[DOWN]){

				SnakeBody snakeBody (
						snake.vSnake.end()->GetX1() ,
						snake.vSnake.end()->GetY1() - 30,
						snake.vSnake.end()->GetX1() ,
						snake.vSnake.end()->GetY1() - 60,
						snake.vSnake.end()->GetSize(),
						snake.vSnake.end()->GetDirection());

			}else if (keys[LEFT]){

				SnakeBody snakeBody (
						snake.vSnake.end()->GetX1() + 30,
						snake.vSnake.end()->GetY1() ,
						snake.vSnake.end()->GetX1() + 60,
						snake.vSnake.end()->GetY1() ,
						snake.vSnake.end()->GetSize(),
						snake.vSnake.end()->GetDirection());

			}else if (keys[RIGHT]){

				SnakeBody snakeBody (
						snake.vSnake.end()->GetX1() - 30,
						snake.vSnake.end()->GetY1() ,
						snake.vSnake.end()->GetX1() - 60,
						snake.vSnake.end()->GetY1() ,
						snake.vSnake.end()->GetSize(),
						snake.vSnake.end()->GetDirection());
			}

			snake.vSnake.push_back(snakeBody);
			snake.SetSize(snake.GetSize()+1);
		}

		al_draw_filled_rectangle(food.GetX1() ,
				food.GetY1() ,
				food.GetX1() + food.GetSize() ,
				food.GetY1() + food.GetSize() , al_map_rgb(0, 0, 255));

		al_flip_display();
		//al_clear_to_color(al_map_rgb(0, 0, 0)); //clear
	}

	al_destroy_event_queue(event_queue);
	al_destroy_timer(timer);
	al_destroy_display(display);

	return 0;
}

int main(void) {

	AllegroSnake();

	return 0;
}

