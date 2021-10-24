# Lexical Analyzer for a custom programming language (Big-Add Language)

**Project and Design Info:**  
  Given problem is a code analysis problem. We need to analyze an input file has name “myscript.ba”. In this special case we have a custom language named as “Big Add Language” this language has classic declarations and basic addition, substraction, assignment, loop and code block conditions. This lexical analyzer problem is first phase of a compiler and going to analyze “Big Add Language”. It takes a code file (in this case named as “myscript.ba”) analysis file and shows declarations, errors, comments, data types, assignments. When analyzer found a error, program going to show this to programmer and going to go on analyze. After analysis, program going to write this analysis to a file which has custom named as “myscript.lx”. Every line going to have one condition. Lexical analysis going to analyze every line in input file and generates an output file. Firstly analyzer going to start searching for first token. If analyzer can find token and if token is valid, analyzer going to show this in a line for programmer (Can be used in compiler too). If analyzer can not find any token in line going to take a look  for whitespaces and comments. If analyzer can find any comment going to rip this out from the code and show this as a comment because comments are not going to execute in compiler. If analyzer encounter with any loop or any calculation, analyzer going to specify them as a loop or calculation. Analyzer going to do this for every line and show errors and results to programmer. To show results program going to create a “myscript.lx” file and write them into the file. After that program going to end and closes. In my design i forgot mentioning about error locations.
  
**Code Info:**  
  Code writed in Code Blocks 20.03 and used standart codeblocks compiler to compile it. In my design i forgot mentioning about error locations and code can not show error locations. That seems like the only problem code has and analysis seems true. To use program you must place a (for example “myscript.ba”) file into program folder after that you can run the program and use it.

**Tests:**

Test 1  
![Test 1](https://user-images.githubusercontent.com/53763911/138610202-b7aee3c1-7c5f-429d-9c8c-4da7cce7ec7c.png)  
Test 1 Output  
![Test 1 Output](https://user-images.githubusercontent.com/53763911/138610205-dc4d55cb-f3d7-45be-9b16-e4e8545fd0e3.png)  
Test 2  
![Test 2](https://user-images.githubusercontent.com/53763911/138610206-9c64628c-a966-4204-ac40-0b36cd26496f.png)  
Test 2 Output  
![Test 2 Output](https://user-images.githubusercontent.com/53763911/138610208-0db9a13c-a3c3-41da-a3a3-3bd384c165f8.png)  

**Check out this project second part (Lexical Analyzer with Interpreter):** https://github.com/tugcantopaloglu/big-add-analyzer-interpreter
