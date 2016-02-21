#coding=utf-8
def isMatch(topElem, curChar):
    matcher = {')':'(', ']':'[', '}':'{'}
    return topElem == matcher[curChar]
      
def isParenthesisMatching():
    parenthesisStr = raw_input("请输入待检验的括号串：")     
    #维护一个顺序栈stack
    stack = [] 
    for i in range(len(parenthesisStr)):
        ch = parenthesisStr[i]
        if ch == '(' or ch == '[' or ch == '{':
            stack.append(ch)
        elif ch == ')' or ch == ']' or ch == '}':
            #栈是否为空，如果为空，则右括号多余
            if len(stack) == 0:
                return False
            #与栈顶元素匹配，则出栈
            elif isMatch(stack[-1], ch):
                stack.pop()
            #与栈顶元素不匹配，则入栈
            else:
                stack.append(ch)
        #print stack
    #如果栈为空，则是完全匹配
    return len(stack) == 0
   
def main():
    print isParenthesisMatching()

if __name__ == '__main__':
    main()