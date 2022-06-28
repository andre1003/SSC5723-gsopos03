#ifndef REQUEST_H
#define REQUEST_H

#pragma region Defines
#define EXEC	'P'
#define IO		'I'
#define READ	'R'
#define WRITE	'W'
#define CREATE	'C'
#pragma endregion

#pragma region Structs
typedef struct REQUEST {
	// Process ID
	char* id;

	// Process operation
	char op;

	// Number passed on op variable
	int number;
} request;
#pragma endregion


/// <summary>
/// Recive and execute a received request.
/// </summary>
/// <param name=""></param>
void receive_request(request*);
#endif // !REQUEST_H
