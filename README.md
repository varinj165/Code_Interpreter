I have passed cout as an argument when I call my execute function in main.cpp
So, to change where the program outputs the data you can change the output
stream being passed in main.

Everything is outputted to this passed output stream.

To run do: "Make all" and then run main.cpp

Runtime Analysis:

MY GENERAL APPROACH TO THE PROGRAM:

My high-level approach is that the interpreter class first parses the whole program 
and stores it into our class structure. Each line's command object is stored in a 
vector (commandArray) in the interpreter class. I then call the execute function of 
the Interpreter class which starts an infinite while loop and all my execution is done 
inside this loop. The variable commandName is intialised to the name of the command 
at the current line. We then go into the specific if statement of the command
and execute it. The idea is to use a variable index to keep track of the command we are
at in the commandArray and change this whenever we want to jump to a line. I use a stack
to store the index of the line that I need to return to when RETURN is called. I use a map
of <string to int> to store int variables and a map of strings to maps to store arrays.
(map<string, map<int, int>>)

Part 1:

Runtime for GOTO to figure out which line to jump to: O(N) (where N = number of commands in the program)

Explaination: This is because after we get the line number that GOTO wants to jump to we then call the
findIndex() function on line 177 of interpreter.cpp. findIndex() just iterates through commandArray to
find the command with the specified line number from the GOTO command and returns the index of that line 
number. Then after index is set to the return value of findIndex(), in the next iteration of the while 
the command we execute (we access the command from commandArray using index) is the command on the specified 
line number. So worst-case runtime is O(N). 

Runtime for GOSUB to figure out which line to jump to: O(N) (where N = number of commands in the program)

Explaination: Once we get the line number for GOSUB to jump to (on line 220 of interpreter.cpp) we already
know the index of the GOSUB command as it is the current command. So, we save index + 1 (the index of the 
line to return to) in our goSubStack. The stack push() operation take constant (Theta(1)) time. We then
use the line number that GOSUB needs to jump to to find the index of the line we need to jump to using
the findIndex() function. The findIndex() function (like in the GOTO command) takes O(N) time to find
the index of the line number in the worst case. Then after index is set to the return value of findIndex(),
in the next iteration of the while the command we execute (we access the command from commandArray using index) 
is the command on the specified line number. So, the runtime for GOSUB is O(N) + O(1) = O(N)

Runtime for IF to figure out which line to jump to: O(N) (where N = number of commands in the program)

Explaination: For the IF command once we get lineToJumpTo, we again call findIndex() to actually figure out 
the index of the line number to jump to. After this, once index is set the while loop automatically goes to 
the command at the index "index" in constant time. So, the runtime for the IF command is also O(N)


Part 2:

Runtime for RETURN to figure what command it jumps to: Theta(1) (Constant)

Explaination: When execution reaches a line that contains a RETURN command we go to the if statement on
line 239 in interpreter.cpp. Here in the execute function we already have a stack that remembers which index
to go to for each GOSUB command. So in the execution of the RETURN command, we just just check if the stack
is empty (to output error message) which takes constant time (O(1)). If the stack is not empty then we use
stack's top() function to store the top index in the stack. The top() function has a constant runtime of O(1).
We then remove the top index from the stack using the pop() function which also has a constant runtime O(1).
(If stack is efficiently implemented using linked list)
After this, the index is already set and on the next iteration of the while loop the line number that RETURN 
needed to jump to is executed. So, total runtime is O(1) + O(1) + O(1) = O(1).

Part 3:

Runtime for figuring out the value of a variable or overwriting the value of a variable: Theta(log N)
(where N is the number of variables stored in arrayVariablesMap or intVariablesMap)

Explaination: Figuring out the value of a variable is done in the getValue() function of the
variableExpression class that inherits from NumericExpression. We call the getValue() function from the 
executeCommand function of the LetCommand Class (line 84 - command.cpp). We use operator[] to access the
specific variable's value from the map in getValue(). This takes Theta(log N). To access both array variables
and int variables we use operator[] so the runtime for figuring out the value of a variable is Theta(log N).

Overwriting the variables is done in the executeCommand() function of the LetCommand class. Once we have the
value we want to overwrite with we do different things for int variables and array variables. We use operator[]
to overwrite the int variable's value in the map (Theta(log N) time). For array variables, we first figure out
if there is already a variable with the same name using the find() function (takes Theta(Log N) time). If there is, 
we overwrite it using operator[] (takes Theta(Log N) time). If there isn't, we first create a new map to store a new
array and then add it to the main variables map (arrayVariablesMap) using operator[]. So, the runtime for overwriting
a variable is Theta(log N).

Part 4:

Runtime for figuring the value of an array entry: Theta(log N)
(where N is the number of variables stored in arrayVariablesMap or intVariablesMap)

Explaination: Figuring out the value is done in the getValue() function of the variableExpression class(line 249
arithmetic.cpp). The function is already passed the map of int variables and array variables (intVariablesMap,
arrayVariablesMap). To figure out the value of an array at a specified index it accesses arrayVariablesMap using
operator[] which we know has a runtime of Theta(log N). So, the runtime is Theta(log N).
