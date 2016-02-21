#coding=utf-8
def lineEdit():
    #利用栈stack作为一个用户数据输入缓冲区,从终端接受一行数据并传送至调用过程的数据区
    stack = []
    line = raw_input("")
    #'$'为全文结束符,line不是空串
    while len(line)!=0:
        for i in range(len(line)):
            ch = line[i]
            if ch == '$':
                break;
            elif ch == '#':
                stack.pop()
            elif ch == '@':
                #清空stack
                stack = []
            else:
                #有效字符进栈
                stack.append(ch)
        #一行输入处理完了，将从栈底到栈顶的字符传送至调用过程的数据区，该过程用打印语句代替
        print ''.join(stack)
        #清空栈
        satck = []
        #读入下一行
        line = raw_input("")
def main():
    lineEdit()

if __name__ == '__main__':
    main()

#输入：whli##ilr#e(s#*s)
#输入：outcha@puchar(*s=#++);$
