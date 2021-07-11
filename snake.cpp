#include <iostream>
#include <conio.h>
#include <ctime>

const int width = 30;
const int height = 30;
const int size = 100;

bool game_over;

int snake_x, snake_y;
int fruit_x, fruit_y;

int tail_x[size];
int tail_y[size];
int tail_size;

int step;
int score;

void set_up();
int random_number(int number);
void draw();
void logic();
void generate_tail(int x, int y);
void object_eaten();
void tail_overlap();
void tail_eaten();
void x_border_motion();
void y_border_motion();

int main() {
    set_up();

    while ( !game_over ) {
        draw();
        logic();
    }

    return 0;
}

//initial settings
void set_up() {
    game_over = false;

    snake_x = width / 2;
    snake_y = height / 2;
    tail_size = 0;

    fruit_x = random_number(width);
    fruit_y = random_number(height);

    score = 0;
    step = 1;
}

//generate numbers from 1 to width or height - 2
int random_number(int number) {
    int limit = number - 2;

    srand(time(NULL));
    int random_num = rand() % limit + 1;

    return random_num;
}

//draw map
void draw() {
    system("cls"); // clear terminal

    std::cout << "Score: " << score << std::endl;

    for ( int i = 0; i < width; i++ ) {
        std::cout << '#';
    }
    std::cout << std::endl;

    for ( int i = 1, limit = height - 1; i < limit; i++ ) {
        for ( int j = 0, border = width - 1; j < width; j++ ) {
            if ( j == 0 || j == border) {
                std::cout << '#';
            } else if ( i == snake_y && j == snake_x ) {
                std::cout << 'S';
            } else if ( i == fruit_y && j == fruit_x ) {
                std::cout << 'F';
            } else {
                bool print_tail = false;
                for ( int k = 0; k < tail_size; k++ ) {
                    if ( i == tail_y[k] && j == tail_x[k] ) {
                        print_tail = true;
                        std::cout << 'o';
                    }
                }
                if ( !print_tail ) {
                    std::cout << ' ';
                }
            }
        }
        std::cout << std::endl;
    }

    for ( int i = 0; i < width; i++ ) {
        std::cout << '#';
    }
    std::cout << std::endl;
}

//logic of the game
void logic() {
    if (_kbhit()) {
        switch (_getch()) {
        case 'a':
            snake_x -= step;
            generate_tail(snake_x + step, snake_y);
            break;
        case 'd':
            snake_x += step;
            generate_tail(snake_x - step, snake_y);
            break;
        case 'w':
            snake_y -= step;
            generate_tail(snake_x, snake_y + step);
            break;
        case 's':
            snake_y += step;
            generate_tail(snake_x, snake_y - step);
            break;
        case 'x':
            game_over = true;
            break;
        }

        object_eaten();

        tail_overlap();
        tail_eaten();

        x_border_motion();
        y_border_motion();

    }
}

void generate_tail(int x, int y) {
    int prev_x = tail_x[0];
    int prev_y = tail_y[0];
    tail_x[0] = x;
    tail_y[0] = y;

    for ( int i = 1; i < tail_size; i++ ) {
        int next_x = tail_x[i];
        int next_y = tail_y[i];
        tail_x[i] = prev_x;
        tail_y[i] = prev_y;
        prev_x = next_x;
        prev_y = next_y;
    }
}

void object_eaten() {
    if ( snake_x == fruit_x && snake_y == fruit_y ) {
        score += 10;
        fruit_x = random_number(width);
        fruit_y = random_number(height);
        tail_size += 1;
    }
}

void tail_overlap() {
    for ( int i = 0; i < tail_size; i++ ) {
        if ( tail_x[i] == fruit_x && tail_y[i] == fruit_y ) {
            fruit_x = random_number(width);
            fruit_y = random_number(height);
        }
    }
}

void tail_eaten() {
    for ( int i = 0; i < tail_size; i++ ) {
        if ( tail_x[i] == snake_x && tail_y[i] == snake_y ) {
            game_over = true;
        }
    }
}

void x_border_motion() {
    int start = 1;
    int end = width - 2;

    if ( snake_x > end ) {
        snake_x = start;
    } else if ( snake_x < start ) {
        snake_x = end;
    }
}

void y_border_motion() {
    int start = 1;
    int end = height - 2;

    if ( snake_y > end ) {
        snake_y = start;
    } else if ( snake_y < start ) {
        snake_y = end;
    }
}
