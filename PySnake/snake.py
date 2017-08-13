import threading
import tkinter
import random
import time
'''主要分为3个部分：
•用一个线程控制游戏的逻辑（如何移动蛇、何时会输等）
•用GUI库把当前局面输出到屏幕上
•想办法把用户的输入传递到控制线程上
'''

#第一部分：贪吃蛇游戏的逻辑
#首先，如何存储游戏的局面呢？
#贪吃蛇的整个盘面是一个含有gy*gx个网格的棋盘，其中每个网格可能有蛇的身体（图中黄色）、食物（图中绿色）、啥都没有（图中蓝色）三种状态。用Python描述就是这样：


gx, gy = 15, 15 #棋盘大小
#EMPTY, SNAKE, FRUIT = 1,2,3 #网格状态
EMPTY='#0000FF'  #蓝
SNAKE='#FFFF00'  #黄
FRUIT='#00FF00'  #绿
g = [[EMPTY for x in range(gx)] for y in range(gy)] #棋盘

#我们可以把蛇存成一个队列（或者列表，毕竟queue.Queue()的性能不太好）：
snake = []
#列表中每一个 (y,x) 二元组表示蛇的身体在坐标 (y,x) 中
#snake[0]是蛇尾，snake[-1]是蛇头


#于是逻辑代码就能写出来了：

UP, DOWN, LEFT, RIGHT = 1,2,3,4
position = DOWN

class Die(Exception): #死了的时候抛出这个异常
    pass

def spawnfruit(): #生成一个食物
    available = [(y,x) for y in range(gy) for x in range(gx) if g[y][x]==EMPTY] #所有空的网格
    if available:
        y, x = random.choice(available) #任选一个放置食物
        g[y][x] = FRUIT
        labels[y][x]['background'] = FRUIT
    else:  #这种情况应该不会发生……
        raise Die

def delchunk(): #删除蛇尾
    y, x = snake[0]
    g[y][x] = EMPTY
    labels[y][x]['background'] = EMPTY
    del snake[0]

def moveto(y, x): #把蛇移动到 (y,x) 位置
    fruit_flag = False #碰到食物的flag

    if not ((0<=y<gy) and (0<=x<gx)): #碰到边界就会死
        raise Die()
    if g[y][x]==SNAKE: #碰到自己就会死
        raise Die()
    if g[y][x]==FRUIT:
        fruit_flag = True

    snake.append((y,x))
    g[y][x] = SNAKE
    labels[y][x]['background'] = SNAKE

    if fruit_flag:
        spawnfruit() #吃到食物时生成新的
    else:
        delchunk() #没吃到食物时蛇尾往前缩

def push(): #蛇头往当前方向增长一格
    now_y, now_x = snake[-1] #蛇头原本的位置
    if position==UP:
        moveto(now_y-1, now_x)
    elif position==DOWN:
        moveto(now_y+1, now_x)
    elif position==LEFT:
        moveto(now_y, now_x-1)
    else: #position==RIGHT
        moveto(now_y, now_x+1)

def init_(): #初始化
    #清空棋盘
    while snake:
        delchunk()
    print('no snake')
    for y in range(gy):
        for x in range(gx):
            g[y][x] = EMPTY
            labels[y][x]['background'] = EMPTY
    print('g is empty')

    #生成一条蛇和一个食物
    for y, x in [(1,0),(2,0),(3,0)]:
        snake.append((y,x))
        g[y][x] = SNAKE
        labels[y][x]['background'] = SNAKE
    print('have a snake')
    spawnfruit()
    print('init end')

def game_controller(): #整个游戏的流程
    init_()
    while True:
        try:
            push()
            time.sleep(.5)
        except Die:
            init_()

#只要调用game_controller，一个没有UI、用户也没法操作的贪吃蛇就诞生了！


#第二部分：GUI
#用的是tkinter，棋盘上每个网格都用一个Label表示：
#（其实可以用Canvas，这代码是之前写的懒得改了）

EMPTY='#0000FF'
SNAKE='#FFFF00'
FRUIT='#00FF00'

tk = tkinter.Tk()

labels = [[None for x in range(gx)] for y in range(gy)]
for y in range(gy):
    for x in range(gx):
        labels[y][x] = tkinter.Label(tk,text='  ',font='-size 10',background=EMPTY)
        labels[y][x].grid(row=y,column=x)

#在逻辑代码里修改g[y][x]的地方顺便修改对应Label的颜色：

#g[y][x] = something
#labels[y][x]['background'] = something

#于是你的游戏就可供人类观赏了！（虽然还是没法控制，一步步来嘛）


#第三部分：用户操作
#贪吃蛇能让用户操作的地方只有改变方向一点：

def setposition(pos):
    global position

    #不能把方向变成相反的
    if position==UP and pos==DOWN:
        return
    if position==DOWN and pos==UP:
        return
    if position==LEFT and pos==RIGHT:
        return
    if position==RIGHT and pos==LEFT:
        return

    position=pos
    print(position)


tk.bind('<Up>',lambda _: setposition(UP))
tk.bind('<Down>',lambda _: setposition(DOWN))
tk.bind('<Left>',lambda _: setposition(LEFT))
tk.bind('<Right>',lambda _: setposition(RIGHT))



#总结
#把这些代码拼起来，然后 threading.Thread(target=game_controller).start()，你就拥有一个很简陋但能玩的贪吃蛇了
if __name__ == '__main__':
    #game_controller()
    threading.Thread(target=game_controller).start()

#如果你想改进这个程序，可以从这几个角度入手：
# •如果在一帧里用户多次改变方向，如何处理？
# •如果电脑突然卡了一下，如何尽量保持帧率稳定？
# •用户关闭窗口时如何正常结束game_controller线程而不是让线程自然崩溃退出？
