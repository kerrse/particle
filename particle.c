#include <string.h>
#include <unistd.h>

#include <ncurses.h>

int main(int argc, char *argv[]) {
    typedef struct postion {
        int x;
        int y;
    } Pos;

    typedef struct velocity {
        int x;
        int y;
    } Vel;

    typedef struct acceleration {
        int x;
        int y;
    } Acc;

    Pos t = { 1, 1 }; // position
    Vel dt = { 1, 1 }; // velocity
    Acc dv = { 1, 1 }; // acceleration
    int max_x, max_y; // screen boundaries

    initscr();
    noecho();
    curs_set(FALSE);

    // get screen size
    getmaxyx(stdscr, max_y, max_x);

    while (1) {
        clear(); // clear previous frame
        mvaddch(t.y, t.x, '.'); // draw particle
        refresh(); // show frame

        // move particle
        t.x += dt.x;
        t.y += dt.y;
        
        // acceleration from wall collision
        if (t.x <= 0 || t.x >= max_x - 1) {
            if (argc > 1 && strcmp(argv[1], "superbounce") == 0) {
                if (dt.x > 0) {
                    dt.x += dv.x;
                } else {
                    dt.x -= dv.x;
                }
            }
            
            // default behavior
            dt.x = -dt.x; // reverse direction
        }

        if (t.y <= 0 || t.y >= max_y - 1) {
            if (argc > 1 && strcmp(argv[1], "superbounce") == 0) {
                if (dt.x > 0) {
                    dt.x += dv.x;
                } else {
                    dt.x -= dv.x;
                }
            }
            
            // default behavior
            dt.y = -dt.y; // reverse direction
        }

        usleep(10000); // update particle every 0.01s
    }

    endwin();
    return 0;
}

