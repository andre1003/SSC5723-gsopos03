#include "input.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "request.h"
#include "ctype.h"


#define MAX_ROW	200




void read_file(void) {
	char line[MAX_ROW];
	FILE* file;

	// Open config.txt file on read mode
	file = fopen("config.txt", "r");

	// If fail, show error message
	if(file == NULL) {
		perror("Failed to open file!");
		return;
	}

	// While file has line to read
	while(fgets(line, MAX_ROW, file) != NULL) {
		// If line starts with alphabetic letter
		if(isalpha(line[0])) {
			printf("\n%s\n", line);
			// Substitute first \n for \0, if there is any
			if(strstr(line, "\n") != NULL) {
				*strstr(line, "\n") = '\0';
			}

			// Variables init
			int count = 0;
			int number;
			char* id = NULL;
			char* ptr = strtok(line, " ()\r");
			char op;
			
			//// While ptr exists
			//while(ptr != NULL) {
			//	// Switch count variable
			//	switch(count) {
			//		case 0:
			//			id = malloc(strlen(ptr) * sizeof(char) + 1);
			//			strcpy(id, ptr);
			//			break;

			//		case 1:
			//			op = ptr[0];
			//			break;

			//		case 2:
			//			number = atoi(ptr);
			//			break;
			//	}

			//	count++;
			//	ptr = strtok(NULL, " ()\r");
			//}

			// While ptr exists
			for(count = 0; ptr != NULL; count++, ptr = strtok(NULL, " ()\r")) {
				// Switch count variable
				switch(count) {
					case 0: // Get id
						id = malloc(strlen(ptr) * sizeof(char) + 1);
						strcpy(id, ptr);
						break;

					case 1: // Get op
						op = ptr[0];
						break;

					case 2: // Get number
						number = atoi(ptr);
						break;
				}
			}

			// Create request
			request* req = malloc(sizeof(request));
			req->id = id;
			req->op = op;
			req->number = number;

			// Send request
			receive_request(req);
		}
	}
}
