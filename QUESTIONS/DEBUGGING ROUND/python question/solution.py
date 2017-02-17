##implements stack and its accompanying data for implementing its logic
class Stack():
    def __init__(self):
        ###Q. self is removed
        self.stack = []
        self.precedence = {'+':0,'-':0,'*':1,'/':1} #precedence
        ###Q.LOGICAL ERROR of messed up precedence 2.5
        self.parent = ['(',')'] ##parenthesis
        ###Q. SHOULD BE LIST MADE INTO DICTIONARY
        self.countRP = 0 ##Count of left parenthesis
        
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
    var=len(list(filter(lambda x: x.isalpha(),list(expression)))) ## number of the symbols
    ###Q.filter need to be casted in list
    op=len(list(filter(lambda x: x in Stack().precedence,list(expression)))) ## number of the operators
    ###Q.filter need to be casted in list
    if(var-op==1):    
        return 0
    return -1

def infixToPost( expression ):
    st=Stack()
    if(validity(expression)==-1):##valdity check for "A("
        ###Q. LOGICAL ERROR OF VALIDITY==0 2.5
        return -1
    expression=list(expression) 
    postexp=[]
    for ch in expression:
        ###Q. LOGICAL error of wrong sectional limit declaration [:] 2.5 
            print(ch, st.stack, postexp,sep="     " )
            if(not len(st.stack) and not(len(postexp))):## works when length is 0 initially
                if(ch in st.parent): ##is parenthesis
                    if ch==')':
                        return -1
                    st.push(ch)
                    st.countRP+=1
                    ###Q.LOGICAL of ADDING 2 for each parenthesis 2.5
                elif(ch in st.precedence): ##if first symbol is operator
                     return -1
                else:
                    postexp.append(ch)
            else:               ## length when is not 0 for stack
                if(ch.isalpha()): ## if variable
                    postexp.append(ch)
                elif(ch in st.parent): ##if a parenthesis
                    if( ch == st.parent[0]): ##if left parent
                        st.countRP+=1     ##increase left parent count
                        st.push(ch)
                        ###Q. should be ch being pushed
                    elif( ch == st.parent[1]):
                        if(not st.countRP):  ##if right parent is 0 and left is found
                            return -1        
                        else:
                            while(st.stacktop()!=st.parent[0]):
                                    postexp.append(st.pop())
                                   
                            st.pop()
                            st.countRP-=1
                elif(ch in st.precedence): ## check for whether in operator range
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
    if(st.countRP!=0): #check for right parenthesis count finally after operation
        return -1
    
    while(len(st.stack)): ## empty the stack
        postexp.append(st.pop())
        ###Q. st.pop is missing
        
    return "".join(postexp)
        ###Q.Wrong name   



expression = "A+(B*C-(D/E-F)*G)*H"
postf=infixToPost(expression)
if(postf==-1):
    print("Ehhhh DOC thats a wrong expression u gave for evaluation!!!!!")
else:
    print("\n",postf)

