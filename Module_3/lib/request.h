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
// Request struct
typedef struct REQUEST {
	char* id;
	char op;
	int number;
} request;
#pragma endregion


/// <summary>
/// Recive and execute a received request.
/// </summary>
void receive_request(request*);
#endif // !REQUEST_H
