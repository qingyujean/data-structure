#coding=utf-8
#数值转换
def conversion():
    stack = []
    n = input("请输入一个待转换的十进制数字：")
    d = input("想转化为几进制？")
    if n == 0:
        return 0
    while n:
        stack.append(n%d)
        n/=d
    """
    #打印栈内元素，从栈顶到栈底的元素依次刚好是转化后的数据
    while len(stack)!=0:
        print stack.pop(),
    """
    stack.reverse()
    return ''.join(map(str, stack))
    
def main():
    print conversion()

if __name__ == '__main__':
    main()