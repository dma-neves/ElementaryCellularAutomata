#include "CA.h"

#include <stdbool.h>
#include <stdio.h>

#define HEIGHT 80
#define WIDTH 80

int cg_line = 0; //Current generation line
bool grid[HEIGHT][WIDTH];

bool ruleset[8];

void CA_init(int ruleNumber)
{
    for(int i = 0; i < 8; i++)
    {
        ruleset[i] = ruleNumber & (1 << i);
    }

    for(int i = 0; i < WIDTH; i++)
        grid[cg_line][i] = 0;

    grid[cg_line][WIDTH/2] = 1;
}

static int newCell(int left, int me, int right)
{
    int index = (left << 2) | (me << 1) | right;

    return ruleset[index];
}

void CA_generate()
{
    int og_line = cg_line; //Old gen line

    if(cg_line == HEIGHT-1)
    {
        for(int y = 0; y < HEIGHT-1; y++)
        {
            for(int x = 0; x < WIDTH; x++)
                grid[y][x] = grid[y+1][x];
        }
    }
    else cg_line++;

    int nextgen[WIDTH];
    for(int x = 0; x < WIDTH; x++)
    {
        bool left = x == 0 ? grid[og_line][WIDTH-1] : grid[og_line][x-1];
        bool me = grid[og_line][x];
        bool right = x == WIDTH-1 ? grid[og_line][0]  : grid[og_line][x+1];

        nextgen[x] = newCell(left, me, right);
    }

    for(int x = 0; x < WIDTH; x++)
        grid[cg_line][x] = nextgen[x];
}

void CA_render(sfRenderWindow* window)
{
    sfRectangleShape* rect = sfRectangleShape_create();
    sfVector2f size;
    size.x = sfRenderWindow_getSize(window).x / WIDTH;
    size.y = sfRenderWindow_getSize(window).y / HEIGHT;
    sfRectangleShape_setSize(rect, size);
    sfRectangleShape_setFillColor(rect, sfColor_fromRGB(255,255,255));

    for(int y = 0; y <= cg_line; y++)
    {
        for(int x = 0; x < WIDTH; x++)
        {
            if(grid[y][x])
            {
                sfVector2f pos;
                pos.x = size.x * x;
                pos.y = size.y * y;
                sfRectangleShape_setPosition(rect, pos);

                sfRenderWindow_drawRectangleShape(window, rect, NULL);
            }
        }
    }

    sfRectangleShape_destroy(rect);
}