#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
//05190000072
char *variableList[1000]; int vIndex = 0; //declaration for every  line
int integerList[1000] = { 0 }; int iIndex = 0; //declaration for every int
char commentLine[100]; char a[100]; char b[100]; //comment line declaration


bool isKeyword(char* str) { //all given identifiers,assignments and other keywords for analysis

	if (!strcmp(str, "int") ||
		!strcmp(str, "move") || !strcmp(str, "to") || !strcmp(str, "add") ||
		!strcmp(str, "sub") || !strcmp(str, "from") ||
		!strcmp(str, "loop") || !strcmp(str, "times") ||
		!strcmp(str, "out")) {
		return true;
	}

	return false;
}

bool isInteger(char* str) { //check if Identifier is int

	int len = strlen(str);

	if (len > 100) { //int has max length 100
		return false;
	}

	for (int i = 0; i < len; i++) { //check every time and if it is not a number return false
		if (i > 0) {
			if (str[i] == '-' || len == 1) {
				return false;
			}
		}
		if (!(isdigit(str[i]) || str[i] == '-')) {
			return false;
		}
	}

	return true;
}

bool isIntegerVariable(char* str) { //check if integer assigned to any Identifier

	for (int i = 0; i < vIndex; i++) {
		if (!strcmp(str, variableList[i])) {
			return true;
		}
	}

	return false;
}

bool isVariable(char* str) //check if string is a Identifier declaration
{
	int len = strlen(str);

	if (len > 20) {
		return false;
	}

	for (int i = 0; i < len; i++) {
		if (str[0] == '_') {
			return false;
		}
		if (!((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z') || (str[i] == '_'))) { //checking characters between A->Z ignoring Turkish chars
			return false;
		}
	}

	return true;
}

void isComment(char* str, FILE* fpout) { //checking is any comment in the lines

	bool trueComment = false;
	int j;
	for (int i = 0; i < strlen(str); i++) {
		if (str[i] == '{') {
			for (j = i; j < strlen(str); j++) {
				if (str[j] == '}') {
					substring(str, i + 1, j - i - 1, commentLine,fpout);
					fprintf(fpout, "%s %s %s", "Comment Line: ", commentLine,"\n");

					substring(str, 0, i, a,fpout);
					substring(str, j + 1, strlen(str), b,fpout);
					strcat(a, b);
					strcpy(str, a);

					trueComment = true;

					isComment(str,fpout);
				}
			}
			if (!trueComment) {
				fprintf(fpout, "%s", "Comment Line is not completed.\n");
				exit(0);
			}
		}
	}
}

void parse(char* code,FILE* fpout) { //parsing to lines and splitting every line to words
	int lineCount = 0;
	char *line[1000];
	char *splitCode = strtok(code, ".");
	while (splitCode != NULL) {
		line[lineCount++] = splitCode;
		splitCode = strtok(NULL, ".");
	}

	for (int i = 0; i < lineCount; i++) {
		int wordCount = 0;
		char *word[1000];
		char *splitLine = strtok(line[i], " \n\r[]\"");
		while (splitLine != NULL) {
			word[wordCount++] = splitLine;
			splitLine = strtok(NULL, " \n\r");
		}

		if (wordCount == 0) { return; }

		//Integer check
		if (!strcmp(word[0], "int")) {
			fprintf(fpout, "%s", "'int' is a keyword.\n");

			//while checking integers Identifier check
			if (word[1] == NULL) {
				fprintf(fpout, "%s", "Identifier is expected.\n");
				return 0;
			}
			else if (isKeyword(word[1])) {
				fprintf(fpout, "%s %s", word[1]," is a keyword. Identifier is expected.\n");
				return 0;
			}
			else if (isVariable(word[1])) {
				fprintf(fpout, "%s %s", word[1] , " is an Identifier.\n");

				variableList[vIndex++] = word[1];
				integerList[iIndex++] = 0;
			}
			else {;
				fprintf(fpout, "%s %s",word[1] ," is not an identifier. Identifier is expected.\n" );
				return 0;
			}

			//End of line
			if (wordCount == 2) {
				fprintf(fpout, "%s", "'.' End of Line.\n");
			}
			else {
				fprintf(fpout, "%s", "End of line is expected.\n");
				return 0;
			}
		}


		//Move check
		else if (!strcmp(word[0], "move")) {
			fprintf(fpout, "%s", "'move' is a keyword.\n");

			//what is moving ? -> integer or Identifier
			int moveInt = 0;
			if (word[1] == NULL) {
				fprintf(fpout, "%s", "Integer or identifier are expected.\n");
				return 0;
			}
			else if (isKeyword(word[1])) {
				fprintf(fpout, "%s %s", word[1], " is a keyword. Integer or identifier are expected.\n");
				return 0;
			}
			else if (isInteger(word[1])) {
                fprintf(fpout, "%s %s",word[1] ," is an integer.\n" );
				moveInt = atoi(word[1]);
			}
			else if (isIntegerVariable(word[1])) {
				fprintf(fpout, "%s %s", word[1] ," is an identifier.\n");

				for (int i = 0; i < vIndex; i++) {
					if (!strcmp(variableList[i], word[1])) {
						moveInt = integerList[i];
						break;
					}
				}
			}
			else {
				fprintf(fpout, "%s %s", word[1]," is not an integer or identifier. Integer or identifier are expected.\n" );
				return 0;
			}

			//move other side check -> To
			if (word[2] == NULL) {
				fprintf(fpout, "%s", "Keyword 'to' is expected.\n");
				return 0;
			}
			else if (!strcmp(word[2], "to")) {
				fprintf(fpout, "%s", "'to' is a keyword.\n");
			}
			else {
				fprintf(fpout, "%s", "Keyword 'to' is expected.\n");
				return 0;
			}

			//normal Identifier check
			if (word[3] == NULL) {
				fprintf(fpout, "%s", "Identifier is expected.\n");
				return 0;
			}
			else if (isKeyword(word[3])) {
				fprintf(fpout, "%s %s",word[3] , " is a keyword. Identifier is expected.\n");
				return 0;
			}
			else if (isIntegerVariable(word[3])) {
                fprintf(fpout, "%s %s",word[3] ," is an identifier.\n");
				for (int i = 0; i < vIndex; i++) {
					if (!strcmp(variableList[i], word[3])) {
						integerList[i] = moveInt;
						break;
					}
				}
			}
			else {
				fprintf(fpout, "%s %s", word[3] , " is not an identifier. Identifier is expected.\n");
				return 0;
			}

			//End of line
			if (wordCount == 4) {
				fprintf(fpout, "%s", "'.' End of Line.\n");
			}
			else {
				fprintf(fpout, "%s", "End of line is expected.\n");
				return 0;
			}
		}


		//Addition operation check
		else if (!strcmp(word[0], "add")) {
			fprintf(fpout, "%s", "'add' is a keyword.\n");

			//Integer or Identifier
			int addInt = 0;
			if (word[1] == NULL) {
				fprintf(fpout, "%s", "Integer or identifier are expected.\n");
				return 0;
			}
			else if (isKeyword(word[1])) {
				fprintf(fpout, "%s %s", word[1]," is a keyword. Integer or identifier are expected.\n");
				return 0;
			}
			else if (isInteger(word[1])) {
				fprintf(fpout, "%s %s", word[1] ," is an integer.\n");

				addInt = atoi(word[1]);
			}
			else if (isIntegerVariable(word[1])) {
                fprintf(fpout, "%s %s", word[1], " is an identifier.\n");
				for (int i = 0; i < vIndex; i++) {
					if (!strcmp(variableList[i], word[1])) {
						addInt = integerList[i];
						break;
					}
				}
			}
			else {
				fprintf(fpout, "%s %s", word[1] ," is not an integer or identifier. Integer or identifier are expected.\n");
				return 0;
			}

			//addition other side check -> To
			if (word[2] == NULL) {
				fprintf(fpout, "%s", "Move is given and keyword 'to' is expected.\n");
				return 0;
			}
			else if (!strcmp(word[2], "to")) {
				fprintf(fpout, "%s", "'to' is a keyword.\n");
			}
			else {
				fprintf(fpout, "%s", "Move is given and keyword 'to' is expected.\n");
				return 0;
			}

			//Identifier check
			if (word[3] == NULL) {
				fprintf(fpout, "%s", "Identifier is expected.\n");
				return 0;
			}
			else if (isKeyword(word[3])) {
				fprintf(fpout, "%s %s", word[3] ," is a keyword. Identifier is expected.\n");
				return 0;
			}
			else if (isIntegerVariable(word[3])) {
				fprintf(fpout, "%s %s", word[3]," is an identifier.\n");

				for (int i = 0; i < vIndex; i++) {
					if (!strcmp(variableList[i], word[3])) {
						integerList[i] += addInt;
						break;
					}
				}
			}
			else {
				fprintf(fpout, "%s %s",word[3]," is not an identifier. Identifier is expected.\n");
				return 0;
			}

			//End Of Line
			if (wordCount == 4) {
				fprintf(fpout, "%s", "'.' End of Line.\n");
			}
			else {
				fprintf(fpout, "%s", "End of line is expected.\n");
				return 0;
			}
		}


		//Subtraction operation check
		else if (!strcmp(word[0], "sub")) {
			fprintf(fpout, "%s", "'sub' is a keyword.\n");

			//Integer or Identifier
			int subInt = 0;
			if (word[1] == NULL) {
				fprintf(fpout, "%s", "Integer or Identifier are expected.\n");
				return 0;
			}
			else if (isKeyword(word[1])) {
				fprintf(fpout, "%s %s",word[1], " is a keyword. Integer or identifier are expected.\n");
				return 0;
			}
			else if (isInteger(word[1])) {
				fprintf(fpout, "%s %s",word[1], " is an integer.\n");

				subInt = atoi(word[1]);
			}
			else if (isIntegerVariable(word[1])) {
				fprintf(fpout, "%s %s",word[1], " is an identifier.\n");

				for (int i = 0; i < vIndex; i++) {
					if (!strcmp(variableList[i], word[1])) {
						subInt = integerList[i];
						break;
					}
				}
			}
			else {
				fprintf(fpout, "%s %s",word[1], " is not an integer or identifier. Integer or identifier are expected.\n");
				return 0;
			}

			//Substraction other side check-> To
			if (word[2] == NULL) {
				fprintf(fpout, "%s", "Keyword 'from' is expected.\n");
				return 0;
			}
			else if (!strcmp(word[2], "from")) {
				fprintf(fpout, "%s", "'to' is a keyword.\n");
			}
			else {
				fprintf(fpout, "%s", "Keyword 'from' is expected.\n");
				return 0;
			}

			//Identifier check
			if (word[3] == NULL) {
				fprintf(fpout, "%s", "Identifier is expected.\n");
				return 0;
			}
			else if (isKeyword(word[3])) {
				fprintf(fpout, "%s %s",word[3], " is a keyword. Identifier is expected.\n");
				return 0;
			}
			else if (isIntegerVariable(word[3])) {
                fprintf(fpout, "%s %s",word[3]," is an identifier.\n");
				for (int i = 0; i < vIndex; i++) {
					if (!strcmp(variableList[i], word[3])) {
						integerList[i] -= subInt;
						break;
					}
				}
			}
			else {
				fprintf(fpout, "%s %s",word[3], " is not an identifier. Identifier is expected.\n");
				return 0;
			}

			//End of line
			if (wordCount == 4) {
				fprintf(fpout, "%s", "'.' End of Line.\n");
			}
			else {
				fprintf(fpout, "%s", "End of line is expected.\n");
				return 0;
			}
		}

		//string output check -> Out
		else if (!strcmp(word[0], "out")) {
            fprintf(fpout, "%s", "'out' is a keyword.\n");
			//Integer, Variable or String
			if (word[1] == NULL) {
				fprintf(fpout, "%s", "Integer, identifier or string are expected.\n");
				return 0;
			}
			else if (isInteger(word[1])) {
				fprintf(fpout, "%s %s",word[1] ," is an integer.\n");
				fprintf(fpout, "%s %s %s", "Integer Value: ",word[1],"\n");
			}
			else if (isIntegerVariable(word[1])) {
				fprintf(fpout, "%s %s",word[1], " is an identifier.\n");

				for (int i = 0; i < vIndex; i++) {
					if (!strcmp(variableList[i], word[1])) {
						fprintf(fpout, "%s %s %d %s","'%s' Identifier value: ",word[1],integerList[i],"\n");
						break;
					}
				}
			}

			//End of line
			if (wordCount == 2) {
				fprintf(fpout, "%s","'.' End of Line.\n");
			}
			else {
				fprintf(fpout, "%s","End of line is expected.\n");
				return 0;
			}
		}

		//Loop check
		else if (!strcmp(word[0], "loop")) {
            fprintf(fpout, "%s","'loop' is a keyword.\n");
			//Integer or Identifier
			int loopInt = 0;
			if (word[1] == NULL) {
				fprintf(fpout, "%s","Integer or identifier are expected.\n");
				return 0;
			}
			else if (isKeyword(word[1])) {
				fprintf(fpout, "%s %s",word[1], " is a keyword. Integer or identifier are expected.\n");
				return 0;
			}
			else if (isInteger(word[1])) {
				fprintf(fpout, "%s %s",word[1] ," is an integer.\n");
				loopInt = atoi(word[1]);
			}
			else if (isIntegerVariable(word[1])) {
				fprintf(fpout, "%s %s",word[1], " is an identifier.\n");

				for (int i = 0; i < vIndex; i++) {
					if (!strcmp(variableList[i], word[1])) {
						loopInt = integerList[i];
						break;
					}
				}
			}
			else {
				fprintf(fpout, "%s %s %s", "Keyword 'times' is expected. ",word[1],"\n");
				return 0;
			}

			//how many times loop continiues
			if (word[2] == NULL) {
				fprintf(fpout, "%s", "Keyword 'times' is expected.\n");
				return 0;
			}
			else if (!strcmp(word[2], "times")) {
				fprintf(fpout, "%s", "'times' is a keyword.\n");
			}
			else {
				fprintf(fpout, "%s", "Keyword 'times' is expected.\n");
				return 0;
			}

			//Code
			for (int i = 0; i < loopInt; i++) {
				char newCode[100] = "";
				for (int i = 3; i < wordCount; i++) {
					strcat(newCode, " ");
					strcat(newCode, word[i]);
				}
				strcat(newCode, ".");
				parse(newCode, fpout);
			}

			//End of line
			if (wordCount > 4) {
				fprintf(fpout, "%s", "End of Line.\n");
			}
			else {
				fprintf(fpout, "%s", "End of line is expected.\n");

				return 0;
			}
		}

		else {

			fprintf(fpout, "%s %s", word[0],"\n");
		}
	}
}

int substring(char *source, int from, int n, char *target,FILE* fpout) {
	int length, i;
	for (length = 0; source[length] != '\0'; length++);
	if (from > length) {
		fprintf(fpout, "%s", "Starting index is invalid.\n");
		return 1;
	}
	if ((from + n) > length) {
		n = (length - from);
	}
	for (i = 0; i < n; i++) {
		target[i] = source[from + i];
	}
	target[i] = '\0';
	return 0;
}

int main() {
	FILE *fp; //pointing input file
	long lSize;
	char *code;
    FILE *fpout; //creating out file
    char fileName[100]; //file name declaration
    //start
    printf("Input going to take from myscript.ba file. Be sure file is in the executable folder!\n");
    printf("Please give file name with .ba extension.(Given name must have .ba extension like myscript.ba)\n");
	scanf("%s",&fileName);

	//file opening proccess
	fp = fopen(fileName, "rb");
	if (!fp) perror(fileName), exit(1);

	fseek(fp, 0L, SEEK_END);
	lSize = ftell(fp);
	rewind(fp);

    //code absolute fails
	code = calloc(1, lSize + 1);
	if (!code) fclose(fp), fputs("memory allocation fails", stderr), exit(1);

	if (1 != fread(code, lSize, 1, fp)) {
		fclose(fp), free(code), fputs("entire read fails", stderr), exit(1);
	}

    //file creating proccess
    fpout = fopen("myscript.lx", "w");
	isComment(code,fpout); //parse only comments
	parse(code,fpout); //parse code except comments
	fclose(fpout);
	//end
	printf("Output writed to myscript.lx file! Check out the file!\n");
	printf("Press 'enter' to end program.\n");
	getchar();

}
