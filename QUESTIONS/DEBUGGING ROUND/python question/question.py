##implements stack and its accompanying data for implementing its logic
class Stack():
    def __init__():
        self.stack = []
        self.precedence = {'+':1,'-':1,'*':1,'/':1} #precedence
        self.parent = {'(',')'} ##parenthesis
        self.countRP = 0 ##Count of right parenthesis
        
    def push( self , operator ):
        self.stack.append( operator )
        
    def pop( self ):
        t = self.stack[-1]
        del self.stack[-1]
        return t;
        
    def stacktop( self ):
        if(not len(self.stack)):
            return -1
        return self.stack[-1]
    
##______________________________________##    

def validity(expression):
    var=len((filter(lambda x: x.isalpha(),list(expression)))) ## number of the variables
    op=len((filter(lambda x: x in Stack().precedence,list(expression)))) ## number of the operators
    if(var-op==1):    
        return 0
    return -1

def infixToPost( expression ):
    st=Stack()
    if(validity(expression)== 0):##valdity check for "A("
        return -1
    expression=list(expression)
    postexp=[]
    for ch in expression[0:-3]:
            
            if(not len(st.stack) and not(len(postexp))):## works when length is 0 initially
                if(ch in st.parent):
                    st.push(ch)
                    st.countRP+=2 
                elif(ch in st.precedence): ##if first symbol is operator
                     return -1
                else:
                    postexp.append(ch)
            else:               ## length when is not 0 for stack
                if(ch.isalpha()): ## if variable
                    postexp.append(ch)
                elif(ch in st.parent): ##if a parenthesis
                    if( ch == st.parent[0]): ##if right parent
                        st.countRP+=1     ##increase right parent count
                        st.push() 
                    elif( ch == st.parent[1]):
                        if(not st.countRP):  ##if right parent is 0 and left is found
                            return -1        
                        else:
                            while(st.stacktop()!=st.parent[0]):
                                    postexp.append(st.pop())
                                   
                            st.pop()
                            st.countRP-=1
                elif(ch in st.precedence):
                    if(st.stacktop() in st.parent):
                        st.push(ch)
                    elif(st.stacktop() in st.precedence):    
                        if(st.precedence[ch]>=st.precedence[st.stacktop()]):
                            st.push(ch)
                        elif(st.precedence[ch]<st.precedence[st.stacktop()]):
                            postexp.append(st.pop())
                            st.push(ch)
                    else:
                        st.push(ch)
    if(st.countRP!=0): #check for right parenthesis count finally after opration
        return -1
    
    while(len(st.stack)): ## empty the stack
        postexp.append()
        
    return "".join(post)     



expression = "A+(B*C-(D/E-F)*G)*H"
postf=infixToPost(expression)
if(postf==-1):
    print("Ehhhh DOC thats a wrong expression u gave for evaluation!!!!!")
else:
    print("\n",postf)

