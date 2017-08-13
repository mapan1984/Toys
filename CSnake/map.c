#include <stdlib.h>
#include <stdio.h>
#include <curses.h>

#define EMPTY '+'
#define SNAKE 'o'
#define SNAKE_HEAD '$'
#define FRUIT '@'

#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

#define Bool int
#define False 0
#define True 1

static int gx = 15;
static int gy = 15;

typedef struct node{
    int x;
    int y;
    struct node *pre;
    struct node *next;
}snake_node;

typedef struct{
    snake_node *head;
    snake_node *tail;
    int size;
}snake;

void creat_snake(snake *s){ // 在 map 创造一个只有2个节点的蛇
    snake_node *sn2 = malloc(sizeof(snake_node));
    sn2->y = 7;
    sn2->x = 7;
    sn2->next = NULL;
    s->tail = sn2;

    snake_node *sn1 = malloc(sizeof(snake_node));
    sn1->y = 6;
    sn1->x = 7;
    sn1->next = sn2;
    sn2->pre = sn1;
    s->head = sn1;

    s->size = 2;
}

void delchunk(snake *s, char map[][gx]){ //删除蛇尾
    map[s->tail->y][s->tail->x] = EMPTY;
    s->tail = s->tail->pre;
    free(s->tail->next);
    s->tail->next = NULL;
}

void append(snake *s, int y, int x){// 增加蛇头
    snake_node *sn = malloc(sizeof(snake_node));
    sn->y = y;
    sn->x = x;
    sn->next = s->head;
    sn->next->pre = sn;
    s->head = sn;
    s->size++;
}

void spawnfruit(char map[][gx]){ // 生成随机食物
    int y = rand() % 14;
    int x = rand() % 14;
    while(map[y][x] != EMPTY){
        y = rand() % 14;
        x = rand() % 14;
    }
    map[y][x] = FRUIT;
}

void moveto(snake *s, char map[][gx], int y, int x){
    Bool fruit_flag = False;

    if(y < 0 || y >= gy || x < 0 || x >= gx){ // 超出边界
        puts("out map\n");
        exit(-1);
    }
    if(map[y][x] == SNAKE){ // 碰到自己
        puts("touch youself\n");
        exit(-1);
    }
    if(map[y][x] == FRUIT){
        fruit_flag = True;
    }

    append(s, y, x); // 增加蛇头

    if(fruit_flag){ // 吃到食物时生成新食物
        spawnfruit(map);
    }else{  // 没吃到食物时删除蛇尾
        delchunk(s, map);
    }
}

void game_controller(snake *s, char map[][gx], int pos){
    int now_y = s->head->y;
    int now_x = s->head->x;
    if(pos == UP){
        moveto(s, map, now_y - 1, now_x);
    }else if(pos == DOWN){
        moveto(s, map, now_y + 1, now_x);
    }else if(pos == LEFT){
        moveto(s, map, now_y, now_x - 1);
    }else{
        moveto(s, map, now_y, now_x + 1);
    }
}

int set_pos(int *cur_pos){ // 不能把方向变为相反的方向
    char p = getchar();
    int pos;
    if(p == 'k'){
        if(*cur_pos == DOWN){
            pos = DOWN;
        }else{
            pos = UP;
        }
    }else if(p == 'j'){
        if(*cur_pos == UP){
            pos = UP;
        }else{
            pos = DOWN;
        }
    }else if(p == 'h'){
        if(*cur_pos == RIGHT){
            pos = RIGHT;
        }else{
            pos = LEFT;
        }
    }else if(p == 'l'){
        if(*cur_pos == LEFT){
            pos = LEFT;
        }else{
            pos = RIGHT;
        }
    }
    *cur_pos = pos;
    return pos;
}

void reset_map(snake *s, char map[][gx]){
    map[s->head->y][s->head->x] = SNAKE_HEAD;
    snake_node *cur = s->head->next;
    while(cur != NULL){
        map[cur->y][cur->x] = SNAKE;
        cur = cur->next;
    }
}

void print_map(snake *s, char map[][gx]){
    refresh();
    reset_map(s, map);
    int y, x;
    for(y=0; y < 15; y++){
        for(x=0; x < 15; x++){
            putchar(map[y][x]);
        }
        putchar('\n');
    }

}

int main(){
    // 生成地图
    char map[gy][gx];
    int x, y;
    for(y=0; y < 15; y++){
        for(x=0; x < 15; x++){
            map[y][x] = EMPTY;
        }
    }

    // 生成一条蛇和一个食物
    snake *s = malloc(sizeof(snake));
    creat_snake(s);
    spawnfruit(map);

    // 打印 map
    print_map(s, map);

    int cur_pos = 1;
    for(;;){
       int pos = set_pos(&cur_pos);
       game_controller(s, map, pos);
       print_map(s, map);
    }

    return 0;
}
