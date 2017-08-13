import os
import random
import time
import msvcrt

gx, gy = 15, 15 #地图大小
EMPTY, SNAKE, SNAKE_HEAD, FRUIT = '+ ','o ', '$ ', '@ ' #网格状态
g = [[EMPTY for x in range(gx)] for y in range(gy)] #初始地图

#把蛇存成一个队列
#列表中每一个 (y,x) 二元组表示蛇的身体在坐标 (y,x) 中
#snake[0]是蛇尾，snake[-1]是蛇头
snake = []

UP, DOWN, LEFT, RIGHT = b'k', b'j', b'h', b'l'

class Die(Exception):
    """死了的时候抛出这个异常"""
    pass

def spawnfruit():
    """生成一个食物"""
    #所有空的网格
    available = [(y,x) for y in range(gy)
                       for x in range(gx) if g[y][x] == EMPTY]
    if available:
        y, x = random.choice(available)
        g[y][x] = FRUIT
    else:
        raise Die

def delchunk():
    """删除蛇尾"""
    y, x = snake[0]
    g[y][x] = EMPTY
    del snake[0]

def moveto(y, x):
    """把蛇移动到 (y,x) 位置"""
    fruit_flag = False    #碰到食物的flag

    if not ((0 <= y < gy) and (0 <= x < gx)):   #超出边界就会死
        raise Die()
    if g[y][x] == SNAKE:     #碰到自己就会死
        raise Die()
    if g[y][x] == FRUIT:
        fruit_flag = True

    snake.append((y,x))
    g[y][x] = SNAKE_HEAD     #重置蛇头
    y, x = snake[-2]
    g[y][x] = SNAKE     #原蛇头重置为蛇身

    if fruit_flag:
        spawnfruit()    #吃到食物时生成新的
    else:
        delchunk()    #没吃到食物时蛇尾往前缩

def init():
    #清空棋盘
    while snake:
        delchunk()
    for y in range(gy):
        for x in range(gx):
            g[y][x] = EMPTY

    #生成一条蛇和一个食物
    for y, x in [(1,0),(2,0),(3,0)]:
        snake.append((y,x))
        g[y][x] = SNAKE
    y, x = snake[-1]
    g[y][x] = SNAKE_HEAD
    spawnfruit()
    for i in range(gx):      #打印整个地图状态
        print("".join(g[i]))

def game_controller():
    """整个游戏的流程"""
    init()
    position = DOWN  #默认向下
    while True:
        try:
            # 让蛇朝方向移动
            now_y, now_x = snake[-1] #蛇头原本的位置
            position = yield position
            #print("position: %s" % position)
            if position==UP:
                moveto(now_y - 1, now_x)
            elif position==DOWN:
                moveto(now_y + 1, now_x)
            elif position==LEFT:
                moveto(now_y, now_x - 1)
            else: #position==RIGHT
                moveto(now_y, now_x + 1)

            #第二部分：GUI
            # 绘制地图与蛇
            os.system('cls')
            for i in range(gx):
                print("".join(g[i]))

            #time.sleep(.5)
        except Die:
            choice = \
                  input("game over!!! do you want to play again? input y/n: ")
            if choice == 'y':
                init()
            else:
                exit()

def setposition(p):
    """第三部分：用户操作"""
    position = p.send(None) #接收当前方向，第一次为DOWN
    while True:
        # 读取键盘
        pos = msvcrt.getch()
        # print(pos)
        #不能把方向变成相反的
        if position==UP and pos==DOWN:
            pos = UP
        if position==DOWN and pos==UP:
            pos = DOWN
        if position==LEFT and pos==RIGHT:
            pos = LEFT
        if position==RIGHT and pos==LEFT:
            pos = RIGHT
        position = p.send(pos)
    p.close()

if __name__ == '__main__':
    p = game_controller()
    setposition(p)
