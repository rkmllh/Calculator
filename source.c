#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define memzero(base, size)			\
	memset(base, 0, size)

//Language accepted
#define OPEN_BRACKET                '{'
#define OPEN_ROUND                  '('
#define OPEN_SQUARE                 '['
#define ADD                         '+'
#define MINUS                       '-'
#define CLOSE_BRACKET               '}'
#define CLOSE_ROUND                 ')'
#define CLOSE_SQUARE                ']'
#define POINT                       '.'
#define MUL                         '*'
#define DEV                         '/'
#define SPACE                       ' '

//States of autome
typedef enum _states
{
	start,
	integer_cypher,		//F
	open_bracket,
	open_round,
	open_square,
	add,
	sub,
	point,
	mul,
	dev,
	close_bracket,		//F
	close_round,		//F
	close_square,		//F
	decimal_cypher,		//F
	error_state
}states;

//Autome object
typedef struct _AUTOME
{
	states m_state;
	int m_nbracket;
	int m_nround;
	int m_nsquare;
}AUTOME, *PAUTOME;

//[@math_expression] numeric expression to analyze
states is_valid_expression(
	const char* math_expression
);

//Print and die
void usage(
	const char* process
);

//malloc wrapper
void* smart_zmalloc(
	size_t mem_size
);

//Print and die
void fatal(
	const char* what
);

int main(int argc, char** argv)
{
	int x = 2;
	char* buffer = NULL;
	states my_state;

	if (argc <= 1)
		usage(argv[0]);
	else
	{
		buffer = (char*)smart_zmalloc(strlen(argv[1]) + sizeof(char));
		memcpy(buffer, argv[1], strlen(argv[1]) * sizeof(char));

		while (x < argc)
		{
			buffer = (char*)realloc(buffer, (strlen(buffer) * sizeof(char) + strlen(argv[x]) * sizeof(char)) + sizeof(char));

			if (buffer == NULL)
				fatal("realloc");

			strcat(buffer, argv[x]);
			++x;
		}
	}

	my_state = is_valid_expression(buffer);

	if (my_state != integer_cypher
		&& my_state != close_bracket
		&& my_state != close_round
		&& my_state != close_square
		)
		printf("[-]Syntax error.\n");
	else
		printf("[!!]Computing the result..\n");

	free(buffer);
	exit(0);
}

states is_valid_expression(
	const char* math_expression
)
{
	AUTOME autome_obj;
	const char* pointer = math_expression;
	memzero(&autome_obj, sizeof(AUTOME));
	
	while(*pointer && autome_obj.m_state != error_state)
	{
		if (*pointer != SPACE)
		{
			switch (autome_obj.m_state)
			{
			case start:
			{
				switch (*pointer)
				{

				case '0':
				case '1':
				case '2':
				case '3':
				case '4':
				case '5':
				case '6':
				case '7':
				case '8':
				case '9':
					autome_obj.m_state = integer_cypher;
					break;

				case OPEN_BRACKET:
					autome_obj.m_state = open_bracket;
					++autome_obj.m_nbracket;
					break;

				case OPEN_ROUND:
					autome_obj.m_state = open_round;
					++autome_obj.m_nround;
					break;

				case OPEN_SQUARE:
					autome_obj.m_state = open_square;
					++autome_obj.m_nsquare;
					break;

				case ADD:
					autome_obj.m_state = add;
					break;

				case MINUS:
					autome_obj.m_state = sub;
					break;

				default:
					autome_obj.m_state = error_state;		//Report an error
					break;
				}

				break;
			}

			case integer_cypher:
			{
				switch (*pointer)
				{
				case '0':
				case '1':
				case '2':
				case '3':
				case '4':
				case '5':
				case '6':
				case '7':
				case '8':
				case '9':
					autome_obj.m_state = integer_cypher;
					break;

				case CLOSE_BRACKET:
					autome_obj.m_state = close_bracket;
					--autome_obj.m_nbracket;
					break;

				case CLOSE_ROUND:
					autome_obj.m_state = close_round;
					--autome_obj.m_nround;
					break;

				case CLOSE_SQUARE:
					autome_obj.m_state = close_square;
					--autome_obj.m_nsquare;
					break;

				case ADD:
					autome_obj.m_state = add;
					break;

				case MINUS:
					autome_obj.m_state = sub;
					break;

				case POINT:
					autome_obj.m_state = point;
					break;

				case MUL:
					autome_obj.m_state = mul;
					break;

				case DEV:
					autome_obj.m_state = dev;
					break;

				default:
					autome_obj.m_state = error_state;
					break;
				}

				break;
			}

			case open_bracket:
			case open_round:
			case open_square:
			{
				switch (*pointer)
				{
				case '0':
				case '1':
				case '2':
				case '3':
				case '4':
				case '5':
				case '6':
				case '7':
				case '8':
				case '9':
					autome_obj.m_state = integer_cypher;
					break;

				case OPEN_BRACKET:
					autome_obj.m_state = open_bracket;
					++autome_obj.m_nbracket;
					break;

				case OPEN_ROUND:
					autome_obj.m_state = open_round;
					++autome_obj.m_nround;
					break;

				case OPEN_SQUARE:
					autome_obj.m_state = open_square;
					++autome_obj.m_nsquare;
					break;

				case ADD:
					autome_obj.m_state = add;
					break;

				case MINUS:
					autome_obj.m_state = sub;
					break;

				default:
					autome_obj.m_state = error_state;		//Report an error
					break;
				}
				break;
			}

			case add:
			case sub:
			case mul:
			case dev:
			{
				switch (*pointer)
				{
				case '0':
				case '1':
				case '2':
				case '3':
				case '4':
				case '5':
				case '6':
				case '7':
				case '8':
				case '9':
					autome_obj.m_state = integer_cypher;
					break;

				case OPEN_BRACKET:
					autome_obj.m_state = open_bracket;
					++autome_obj.m_nbracket;
					break;

				case OPEN_ROUND:
					autome_obj.m_state = open_round;
					++autome_obj.m_nround;
					break;

				case OPEN_SQUARE:
					autome_obj.m_state = open_square;
					++autome_obj.m_nsquare;
					break;

				default:
					autome_obj.m_state = error_state;
					break;
				}

				break;
			}

			case point:
			{
				switch (*pointer)
				{
				case '0':
				case '1':
				case '2':
				case '3':
				case '4':
				case '5':
				case '6':
				case '7':
				case '8':
				case '9':
					autome_obj.m_state = decimal_cypher;
					break;

				default:
					autome_obj.m_state = error_state;
					break;
				}

				break;
			}

			case close_bracket:
			case close_round:
			case close_square:
			{
				switch (*pointer)
				{
				case CLOSE_BRACKET:
					autome_obj.m_state = close_bracket;
					--autome_obj.m_nbracket;
					break;

				case CLOSE_ROUND:
					autome_obj.m_state = close_round;
					--autome_obj.m_nround;
					break;

				case CLOSE_SQUARE:
					autome_obj.m_state = close_square;
					--autome_obj.m_nsquare;
					break;

				case ADD:
					autome_obj.m_state = add;
					break;

				case MINUS:
					autome_obj.m_state = sub;
					break;

				case MUL:
					autome_obj.m_state = mul;
					break;

				case DEV:
					autome_obj.m_state = dev;
					break;

				default:
					autome_obj.m_state = error_state;
					break;
				}

				break;
			}

			case decimal_cypher:
			{
				switch (*pointer)
				{
				case '0':
				case '1':
				case '2':
				case '3':
				case '4':
				case '5':
				case '6':
				case '7':
				case '8':
				case '9':
					autome_obj.m_state = decimal_cypher;
					break;

				case CLOSE_BRACKET:
					autome_obj.m_state = close_bracket;
					--autome_obj.m_nbracket;
					break;

				case CLOSE_ROUND:
					autome_obj.m_state = close_round;
					--autome_obj.m_nround;
					break;

				case CLOSE_SQUARE:
					autome_obj.m_state = close_square;
					--autome_obj.m_nsquare;
					break;

				case ADD:
					autome_obj.m_state = add;
					break;

				case MINUS:
					autome_obj.m_state = sub;
					break;

				case MUL:
					autome_obj.m_state = mul;
					break;

				case DEV:
					autome_obj.m_state = dev;
					break;

				default:
					autome_obj.m_state = error_state;
					break;
				}

				break;
			}

			default:
				break;
			}
		}
		++pointer;
	}

	//Report an error
	if (autome_obj.m_nbracket != 0 ||
		autome_obj.m_nround != 0 ||
		autome_obj.m_nsquare != 0)
		autome_obj.m_state = error_state;

	return autome_obj.m_state;
}

void* smart_zmalloc(
	size_t mem_size
)
{
	void* mem_block = malloc(mem_size);
	if (mem_block == NULL)
		fatal("malloc");

	memzero(mem_block, mem_size);
	return mem_block;
}

void usage(
	const char* process
)
{
	printf("usage: <%s> <expression>\n\tExample: ({32 * 65} + 12 / 6)\n", process);
	exit(1);
}

void fatal(
	const char* what
)
{
	fprintf(stderr, "fatal in %s\n", what);
	exit(1);
}
