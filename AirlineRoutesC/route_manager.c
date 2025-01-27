/** @file route_manager.c
 *  @brief A pipes & filters program that uses conditionals, loops, and string processing tools in C to process airline routes.
 *  @author Felipe R.
 *  @author Hausi M.
 *  @author Jose O.
 *  @author Saasha J.
 *  @author Victoria L.
 *  @author STUDENT_NAME
 *
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * Function: main
 * --------------
 * @brief The main function and entry point of the program.
 *
 * @param argc The number of arguments passed to the program.
 * @param argv The list of arguments passed to the program.
 * @return int 0: No errors; 1: Errors produced.
 *
 */

typedef struct {
	FILE *csv_file;
	char airline_icao_unique_code[100];
	char from_airport_city[100];
	char from_airport_country[100];
	char to_airport_city[100];
	char to_airport_country[100];

	char airline_name_csv[100];
	char airline_icao_unique_code_csv[100];
	char airline_country_csv[100];
	char from_airport_name_csv[100];
	char from_airport_city_csv[100];
	char from_airport_country_csv[100];
	char from_airport_icao_unique_code_csv[100];
	char from_airport_altitude_csv[100];
	char to_airport_name_csv[100];
	char to_airport_city_csv[100];
	char to_airport_country_csv[100];
	char to_airport_icao_unique_code_csv[100];
	char to_airport_altitude_csv[100];

	int result_found;
	int first;
	int use_case3;
} cat;

void argument_processing(int argc, char* argv[], cat *array);
void separate_tokens(char* token, cat* array);
void put_struct(char* token, char* token2, cat* array);
void read_file(FILE *out, cat* array);
void check_string(char string[], FILE *out, cat* array);
void compare_out(cat* array, FILE *out);

int main(int argc, char *argv[])
{
	cat array;
	FILE *out;
	out = fopen("output.txt", "w");
	if (argc < 2 || argc > 7) {
		fprintf(out, "NO RESULTS FOUND.\n");
	}
	else {
		argument_processing(argc, argv, &array);
		read_file(out, &array);
	}
	fclose(out);
    exit(0);
}

/**
 * Function: argument_processing
 * --------------
 * @brief Obtains the arguments from the command line and 
 *
 * @param argc The number of arguments passed to the program.
 * @param argv The list of arguments passed to the program.
 * @param array the struct that will hold the arguments passed to the program's values
 * @return void
 *
 */
void argument_processing(int argc, char* argv[], cat* array) {
	char* token;
	token = strtok(argv[1], " ");
	separate_tokens(token, array);
	for (int i = 2; i < argc; i++) {
		token = strtok(argv[i], "--");
		while (token != NULL) {
			separate_tokens(token, array);
			token = strtok(NULL, " ");
		}
	}
	return;
}

/**
 * Function: Separate_tokens
 * --------------
 * @brief separates the arguments passed to the command line into the correct format to work with / process
 *
 * @param token holds argument value
 * @param array the struct that will hold the arguments passed to the program's values
 * @return void
 *
 */
void separate_tokens(char* token, cat* array) {
	token = strtok(token, "=");
	char* token2;
	token2 = strtok(NULL, "=");
	put_struct(token, token2, array);
	return;
}

/**
 * Function: put_struct
 * --------------
 * @brief puts command line arguments into the strct for later comparison with file
 *
 * @param token holds first part of an argument value
 * @param array the struct that will hold the arguments passed to the program's values
 * @param token2 holds second part of an arguments value
 * @return void
 *
 */
void put_struct(char* token, char* token2, cat* array) {
	if (strcmp(token, "--DATA") == 0) {
		array->csv_file = fopen(token2, "r");
		return;
	}
	else if (strcmp(token, "SRC_CITY") == 0) {
		array->use_case3 = 1;
		strcpy(array->from_airport_city, token2);
	}
	else if (strcmp(token, "SRC_COUNTRY") == 0) {
		strcpy(array->from_airport_country, token2);
	}
	else if (strcmp(token, "DEST_CITY") == 0) {
		strcpy(array->to_airport_city, token2);
	}
	else if (strcmp(token, "DEST_COUNTRY") == 0) {
		strcpy(array->to_airport_country, token2);
	}
	else if (strcmp(token, "AIRLINE") == 0) {
		strcpy(array->airline_icao_unique_code, token2);
	}
	return;
}

/**
 * Function: read_file
 * --------------
 * @brief reads the input file line by line
 *
 * @param out the output file
 * @param array the struct that will hold the arguments passed to the program's values
 * @return void
 *
 */
void read_file(FILE *out, cat* array){
	if (array->csv_file == NULL) {
		printf("Error: csv_file is a null pointer.\n");
		return;
	}
	array->result_found = 0;
	array->first = 0;
	char string[1024];
	while (fgets(string, sizeof(string), array->csv_file)) {
		check_string(string, out, array);
	}
	if (array->result_found == 0) {
		fprintf(out, "NO RESULTS FOUND.\n");
	}
	fclose(array->csv_file);
	return;
}

/**
 * Function: check_string
 * --------------
 * @brief separates and puts the elements of the line from the file into the struct
 *
 * @param string the string read from the input file
 * @param out the output file
 * @param array the struct that will hold the arguments passed to the program's values
 * @return void
 *
 */
void check_string(char string[], FILE *out, cat* array) {
	char* token;
	char string2[1024];
	int count2 = 1;
	strcpy(string2, string);
	token = strtok(string2, ",");
	while (token != NULL) {
		if (count2==1) {
			strcpy(array->airline_name_csv, token);
		}
		else if (count2 == 2) {
			strcpy(array->airline_icao_unique_code_csv, token);
		}
		else if (count2 == 3) {
			strcpy(array->airline_country_csv, token);
		}
		else if (count2 == 4) {
			strcpy(array->from_airport_name_csv, token);
		}
		else if (count2 == 5) {
			strcpy(array->from_airport_city_csv, token);
		}
		else if (count2 == 6) {
			strcpy(array->from_airport_country_csv, token);
		}
		else if (count2 == 7) {
			strcpy(array->from_airport_icao_unique_code_csv, token);
		}
		else if (count2 == 8) {
			strcpy(array->from_airport_altitude_csv, token);
		}
		else if (count2 == 9) {
			strcpy(array->to_airport_name_csv, token);
		}
		else if (count2 == 10) {
			strcpy(array->to_airport_city_csv, token);
		}
		else if (count2 == 11) {
			strcpy(array->to_airport_country_csv, token);
		}
		else if (count2 == 12) {
			strcpy(array->to_airport_icao_unique_code_csv, token);
		}
		else if (count2 == 13) {
			strcpy(array->to_airport_altitude_csv, token);
		}
		count2++;

		token = strtok(NULL, ",");
	}
	compare_out(array, out);
	return;
}

/**
 * Function: compare_out
 * --------------
 * @brief compares the command line arguments with the line from the file and writes output to output file if comparison is true
 *
 * @param out the output file
 * @param array the struct that will hold the arguments passed to the program's values
 * @return void
 *
 */
void compare_out(cat* array, FILE *out) { 
	if (strcmp(array->airline_icao_unique_code, array->airline_icao_unique_code_csv) == 0 && strcmp(array->to_airport_country, array->to_airport_country_csv) == 0) {
		array->result_found = 1;
		if (array->first == 0) {
			fprintf(out, "FLIGHTS TO %s BY %s (%s):\n", array->to_airport_country, array->airline_name_csv, array->airline_icao_unique_code);
			array->first = 1;
		}
		if (array->first == 1) {
			fprintf(out, "FROM: %s, %s, %s TO: %s (%s), %s\n", array->from_airport_icao_unique_code_csv, array->from_airport_city_csv, array->from_airport_country_csv, array->to_airport_name_csv, array->to_airport_icao_unique_code_csv, array->to_airport_city_csv);
		}
	}
	if (strcmp(array->from_airport_country, array->from_airport_country_csv) == 0 && strcmp(array->to_airport_city, array->to_airport_city_csv) == 0 && strcmp(array->to_airport_country, array->to_airport_country_csv) == 0 && array->use_case3 != 1) {
		array->result_found = 1;
		if (array->first == 0) {
			fprintf(out, "FLIGHTS FROM %s TO %s, %s:\n", array->from_airport_country, array->to_airport_city, array->to_airport_country);
			array->first = 1;
		}
		if (array->first == 1) {
			fprintf(out, "AIRLINE: %s (%s) ORIGIN: %s (%s), %s\n", array->airline_name_csv, array->airline_icao_unique_code_csv, array->from_airport_name_csv, array->from_airport_icao_unique_code_csv, array->from_airport_city_csv);
		}
	}
	if (strcmp(array->from_airport_city, array->from_airport_city_csv) == 0 && strcmp(array->from_airport_country, array->from_airport_country_csv) == 0 && strcmp(array->to_airport_city, array->to_airport_city_csv) == 0 && strcmp(array->to_airport_country, array->to_airport_country_csv) == 0) {
		array->result_found = 1;
		if (array->first == 0) {
			fprintf(out, "FLIGHTS FROM %s, %s TO %s, %s:\n", array->from_airport_city, array->from_airport_country, array->to_airport_city, array->to_airport_country);
			array->first = 1;
		}
		if (array->first == 1) {
			fprintf(out, "AIRLINE: %s (%s) ROUTE: %s-%s\n", array->airline_name_csv, array->airline_icao_unique_code_csv, array->from_airport_icao_unique_code_csv, array->to_airport_icao_unique_code_csv);
		}
	}
	return;
}