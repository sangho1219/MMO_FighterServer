#pragma once 
#define MAX_X 6400
#define MAX_Y 6400
#define SECTOR_X 40
#define SECTOR_Y 40

struct SECTOR_POS
{
    int x;
    int y;
};
struct SECTOR_AROUND
{
    int count;
    SECTOR_POS Around[9];
};



void SetCurSector(unsigned short x, unsigned short y, SECTOR_POS* arg);
void GetAround(const SECTOR_POS* pos, SECTOR_AROUND* around);
void SetCurSector(unsigned short x, unsigned short y, SECTOR_POS* arg)
{
    arg->x = x / SECTOR_X;
    arg->y = y / SECTOR_Y;
}
void GetAround(const SECTOR_POS* pos, SECTOR_AROUND* around)
{
    SECTOR_POS temp;
    around->count = 0;

    temp.x = pos->x;
    temp.y = pos->y;
    around->Around[around->count] = temp;
    around->count++;

    if (pos->x != 0)
    {
        temp.x = pos->x - 1;
        temp.y = pos->y;
        around->Around[around->count] = temp;
        around->count++;
    }
    if (pos->x != 6400)
    {
        temp.x = pos->x + 1;
        temp.y = pos->y;
        around->Around[around->count] = temp;
        around->count++;
    }
    if (pos->y != 0)
    {
        temp.x = pos->x;
        temp.y = pos->y - 1;
        around->Around[around->count] = temp;
        around->count++;
    }
    if (pos->y != 6400)
    {
        temp.x = pos->x;
        temp.y = pos->y + 1;
        around->Around[around->count] = temp;
        around->count++;
    }
    if (pos->x != 0 && pos->y != 0)
    {
        temp.x = pos->x - 1;
        temp.y = pos->y - 1;
        around->Around[around->count] = temp;
        around->count++;
    }
    if (pos->x != 6400 && pos->y != 6400)
    {
        temp.x = pos->x + 1;
        temp.y = pos->y + 1;
        around->Around[around->count] = temp;
        around->count++;
    }
    if (pos->x != 0 && pos->y != 6400)
    {
        temp.x = pos->x - 1;
        temp.y = pos->y + 1;
        around->Around[around->count] = temp;
        around->count++;
    }
    if (pos->x != 6400 && pos->y != 0)
    {
        temp.x = pos->x + 1;
        temp.y = pos->y - 1;
        around->Around[around->count] = temp;
        around->count++;
    }
}
