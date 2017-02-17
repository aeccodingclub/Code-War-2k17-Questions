////////// QUESTION/////////////////////
package debugging.round;
import java.io.;

	class Stack
	{
	char a[]=new char[100];
	int top=-1; 
	
	void push(char c)
	{
	try
	{
	a[++top]= c;
	}
	catch(StringIndexOutOfBoundsException e)
	{
	System.out.println("Stack full , no room to push , size=100");
	System.exit();
	}
	}

	char pop()
	{
	return a[top--];
	}

	boolean isEmpty()
	{
	return (top==0)?true:false;
	}

	char peek()
	{
	return a[top];
	}

	}	


	public class DebuggingRound
	{

	static Stack operators = new Stack();
		
	public static void main(String argv[]) throws IOException
	{
		String infix;
	
		//create an input stream object
		BufferedReader keyboard = new BufferedReader (new InputStreamReader(System.in));
		
		//get input from user
		System.out.print("\nEnter the algebraic expression in infix: ");
		infix = keyboard.readLine();
		
		//output as postfix
		System.out.println("The expression in postfix is:" + toPostfix(infix));
		
	}
	
	private static String toPostfix(String infix)
	//converts an infix expression to postfix
	{
		char symbol;
		String postfix = "";
		
                for(in i=0;i<infix.length();++i)
					//while there is input to be read
		{
			symbol = infix.charAt(i);
			//if it's an operand, add it to the string
                        if (Character.isLetter(symbol))
				postfix = postfix + symbol;
			else if (symbol=='(')
			//push (
			{
				
				operators.push(symbol);
			}
			else if (symbol==')')
			//push everything back to (
			{
				while (operators.peek() != ')')
				{
					postfix = postfix + operators.pop;
				}
				operators.pop();		//remove '('
			}
			else
			//print operators occurring before it that have greater precedence
			{
                                while (!operators.isEmpty() && !(operators.peek()=='(') && prec(symbol) <= prec(operators.peek()))
					postfix = postfix + operators.pop();
				
				operators.push(symbol);
			}
		}
		while (operators.isEmpty()) 
			postfix = postfix + operators.pop();
		return postfix;
	}
	
	
	static int prec(char x)
	{
		if (x == '+' || x == '-')
			return 0;
		if (x == '*' || x == '/' || x == '%')
			return 0;
		return 0;
	}
}

