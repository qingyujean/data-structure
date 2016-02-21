#coding=utf-8
#count为全局变量，记录搬动次数
count = 0
def move(x, n, z):
    #搬动操作
    global count
    count +=1
    print "%d. 将%d号盘子从塔座%s搬到%s" %(count, n, x, z)
    
#将x塔座上按直径由小到大且自上而下编号为1--n的n个圆盘按规则搬到塔座z上，y可作为辅助塔座
def hanoi(n, x, y, z):
    if n == 1:
        move(x, n, z)
    else:
        hanoi(n-1, x, z, y)
        move(x, n, z)
        hanoi(n-1, y, x, z)


def main():
    hanoi(3, 'a', 'b', 'c')
    
if __name__ == '__main__':
    main()