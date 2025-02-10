/** @file route_manager.c
 *  @brief A small program to analyze airline routes data.
 *  @author Mike Z.
 *  @author Felipe R.
 *  @author Hausi M.
 *  @author Jose O.
 *  @author Saasha J.
 *  @author Victoria L.
 *  @author STUDENT_NAME
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

// TODO: Make sure to adjust this based on the input files given
#define MAX_LINE_LEN 80

typedef struct {
    
    FILE* input_file;
    char question_num[10];
    char num_elements[10];
    int num_el;
    int list_size;
} strct;

/**
 * @brief Serves as an incremental counter for navigating the list.
 *
 * @param p The pointer of the node to print.
 * @param arg The pointer of the index.
 *
 */
void inccounter(node_t *p, void *arg)
{
    int *ip = (int *)arg;
    (*ip)++;
}

/**
 * @brief Allows to print out the content of a node.
 *
 * @param p The pointer of the node to print.
 * @param arg The format of the string.
 *
 */
void print_node(node_t *p, void *arg)
{
    char *fmt = (char *)arg;
    printf(fmt, p->word);
}

/**
 * @brief Allows to print each node in the list.
 *
 * @param l The first node in the list
 *
 */
void analysis(node_t *l)
{
    int len = 0;

    apply(l, inccounter, &len);
    printf("Number of words: %d\n", len);

    apply(l, print_node, "%s\n");
}

/**
 * Function: put_struct
 * --------------
 * @brief puts command line arguments into the strct for later comparison with file
 *
 * @param token holds first part of an argument value
 * @param variables the struct that will hold the arguments passed to the program's values
 * @param token2 holds second part of an arguments value
 * @return int - 0 or number of elements
 *
 */
int put_struct(char* token, char* token2, strct* variables) {
    if (strcmp(token, "--DATA") == 0) {
        variables->input_file = fopen(token2, "r");
        return 0;
    }
    else if (strcmp(token, "QUESTION") == 0) {
        strcpy(variables->question_num, token2);
    }
    else if (strcmp(token, "N") == 0) {
        strcpy(variables->num_elements, token2);
        variables->num_el = atoi(token2);
        return variables->num_el;
    }
    return 0;
}

/**
 * Function: argument_processing
 * --------------
 * @brief Obtains the arguments from the command line and
 *
 * @param argc The number of arguments passed to the program.
 * @param argv The list of arguments passed to the program.
 * @param variables the struct that will hold the arguments passed to the program's values
 * @return int - size - number of elements to output to out file
 *
 */
int argument_processing(int argc, char* argv[], strct* variables) {
    char* token = NULL;

    token = strtok(argv[1], " ");

    token = strtok(token, "=");
    char* token2;
    token2 = strtok(NULL, "=");
    put_struct(token, token2, variables);
    int size = 0;

    for (int i = 2; i < argc; i++) {
        token = strtok(argv[i], "--");
        while (token != NULL) {
            token = strtok(token, "=");
            char* token2;
            token2 = strtok(NULL, "=");
            size = put_struct(token, token2, variables);
            token = strtok(NULL, " ");
        }
    }
    return size;
}

/**
 * Function: read_fileq1
 * --------------
 * @brief reads the input file line by line for q1
 *
 * @param out the output file
 * @param variables the struct that will hold the arguments passed to the program's values
 * @param link_list the linked list that holds the appropriate input file values
 * @return node_t - the linked list
 *
 */
node_t *read_fileq1(FILE* out, strct* variables, node_t *link_list) {
    if (variables->input_file == NULL) {
        printf("Error: input_file is a null pointer.\n");
        return link_list;
    }
    char* key;
    char* value;
    char string[MAX_LINE_LEN];

    variables->list_size = 0;

    fgets(string, MAX_LINE_LEN, variables->input_file);
    key = strtok(string, ":");
    value = strtok(NULL, "\n");

    while (fgets(string, MAX_LINE_LEN, variables->input_file)) {
        key = strtok(string, ":");
        value = strtok(NULL, "\n");

        char airline[MAX_LINE_LEN];
        char airline_code[MAX_LINE_LEN];
        char bracket1[] = " (";
        char bracket2[] = ")";
        char *canada = " Canada";
        char *airline_name = "- airline_name";
        char *airline_icao_code = "  airline_icao_unique_code";
        char *to_country = "  to_airport_country";

        if (strcmp(key, airline_name) == 0) {
            value++;
            strcpy(airline, value);
        }
        if (strcmp(key, airline_icao_code) == 0) {
            value++;
            strcpy(airline_code, bracket1);
            strcat(airline_code, value);
            strcat(airline_code, bracket2);
        }
        if (strcmp(key, to_country) == 0) {
            if (strcmp(value, canada) == 0) {
                strcat(airline, airline_code);
                link_list = add_inorder(link_list, new_node(airline));
                variables->list_size++;
            }
        }
    }
    fclose(variables->input_file);
    return link_list;
}

/**
 * Function: read_fileq2
 * --------------
 * @brief reads the input file line by line for q2
 *
 * @param out the output file
 * @param variables the struct that will hold the arguments passed to the program's values
 * @param link_list the linked list that holds the appropriate input file values
 * @return node_t - the linked list
 *
 */
node_t* read_fileq2(FILE* out, strct* variables, node_t* link_list) {
    if (variables->input_file == NULL) {
        printf("Error: input_file is a null pointer.\n");
        return link_list;
    }
    char* key;
    char* value;
    char string[MAX_LINE_LEN];
    int counter = 0;

    variables->list_size = 0;

    fgets(string, MAX_LINE_LEN, variables->input_file);
    key = strtok(string, ":");
    value = strtok(NULL, "\n");

    while (fgets(string, MAX_LINE_LEN, variables->input_file)) {
        key = strtok(string, ":");
        value = strtok(NULL, "\n");

        char* to_country = "  to_airport_country";

        if (strcmp(key, to_country) == 0) {
            counter++;
            value++;
            char needle = '\'';
            if (strchr(value, needle) != NULL) {
                value++;
                value++;
                char* end = value + strlen(value) - 1;
                end--;
                *(end + 1) = '\0';
            }
            link_list = add_inorder(link_list, new_node(value));
            variables->list_size++;
        }
    }
    fclose(variables->input_file);
    return link_list;
}

/**
 * Function: read_fileq3
 * --------------
 * @brief reads the input file line by line for q3
 *
 * @param out the output file
 * @param variables the struct that will hold the arguments passed to the program's values
 * @param link_list the linked list that holds the appropriate input file values
 * @return node_t - the linked list
 *
 */
node_t* read_fileq3(FILE* out, strct* variables, node_t* link_list) {
    if (variables->input_file == NULL) {
        printf("Error: input_file is a null pointer.\n");
        return link_list;
    }
    char* key;
    char* value;
    char string[MAX_LINE_LEN];
    int counter = 0;

    variables->list_size = 0;

    fgets(string, MAX_LINE_LEN, variables->input_file);
    key = strtok(string, ":");
    value = strtok(NULL, "\n");

    while (fgets(string, MAX_LINE_LEN, variables->input_file)) {
        key = strtok(string, ":");
        value = strtok(NULL, "\n");

        char airport[MAX_LINE_LEN];
        char country[MAX_LINE_LEN];
        char airport_code[MAX_LINE_LEN];
        char bracket1[] = " (";
        char bracket2[] = "), ";
        char comma_space[] = ", ";
        char city[MAX_LINE_LEN];
        char* to_airport_city = "  to_airport_city";
        char* to_airport = "  to_airport_name";
        char* airport_icao_code = "  to_airport_icao_unique_code";
        char* to_country = "  to_airport_country";

        if (strcmp(key, to_airport) == 0) {
            value++;

            strcpy(airport, value);
        }
        if (strcmp(key, to_airport_city) == 0) {
            value++;
            strcpy(city, value);
            strcat(city, comma_space);
        }
        if (strcmp(key, to_country) == 0) {
            counter++;
            value++;

            strcpy(country, value);
            
        }
        if (strcmp(key, airport_icao_code) == 0) {
            value++;
            strcpy(airport_code, bracket1);
            strcat(airport_code, value);
            strcat(airport_code, bracket2);

            strcat(airport, airport_code);
            strcat(airport, city);
            strcat(airport, country);
            link_list = add_inorder(link_list, new_node(airport));
            variables->list_size++;
        }
    }
    fclose(variables->input_file);
    return link_list;
}

/**
 * Function: read_list1
 * --------------
 * @brief reads the first linked list and count nuber of time each value appears for q1
 *
 * @param out the output file
 * @param variables the struct that will hold the arguments passed to the program's values
 * @param link_list the linked list that holds the appropriate input file values
 * @param size the size/number of elements to print to the output file 
 * @return node_t - the linked list
 *
 */
FILE* read_list1(node_t* link_list, FILE* out, strct* variables, int size) {
    node_t* curr = NULL;
    node_t* counted_list = NULL;
    int stat = 0;
    for (curr = link_list; curr->next != NULL; curr = curr->next) {
        if (strcmp(curr->word, curr->next->word) == 0){
            stat++;
        }
        else {
            stat++;
            curr->count = stat;
            char* counted_c = curr->word;
            int counted_int = curr->count;
            counted_list = add_inorder2(counted_list, new_node2(counted_c, counted_int));
            stat = 0;
        }
        
    }
    stat++;
    curr->count = stat;
    char* counted_c = curr->word;
    int counted_int = curr->count;
    counted_list = add_inorder2(counted_list, new_node2(counted_c, counted_int));
    node_t* counted_curr = counted_list;
    fprintf(out, "subject,statistic\n");
    for (int i = 0; i < size; i++) {
        fprintf(out, "%s,%d\n", counted_curr->word, counted_curr->count);
        counted_curr = counted_curr->next;
    }
    node_t* temp_n = NULL;
    for (; counted_list != NULL; counted_list = temp_n)
    {
        temp_n = counted_list->next;
        free(counted_list->word);
        free(counted_list);
    }
    return out;
}

/**
 * Function: read_list2
 * --------------
 * @brief reads the first linked list and count nuber of time each value appears for q2
 *
 * @param out the output file
 * @param variables the struct that will hold the arguments passed to the program's values
 * @param link_list the linked list that holds the appropriate input file values
 * @param size the size/number of elements to print to the output file
 * @return node_t - the linked list
 *
 */
FILE* read_list2(node_t* link_list, FILE* out, strct* variables, int size) {
    node_t* curr = NULL;
    node_t* counted_list = NULL;
    int stat = 0;
    for (curr = link_list; curr->next != NULL; curr = curr->next) {
        if (strcmp(curr->word, curr->next->word) == 0) {
            stat++;
        }
        else {
            stat++;
            curr->count = stat;
            char* counted_c = curr->word;
            int counted_int = curr->count;
            counted_list = add_inorder3(counted_list, new_node2(counted_c, counted_int));
            stat = 0;
        }

    }
    stat++;
    curr->count = stat;
    char* counted_c = curr->word;
    int counted_int = curr->count;
    counted_list = add_inorder3(counted_list, new_node2(counted_c, counted_int));
    node_t* counted_curr = counted_list;
    fprintf(out, "subject,statistic\n");
    for (int i = 0; i < size; i++) {
        fprintf(out, "%s,%d\n", counted_curr->word, counted_curr->count);
        counted_curr = counted_curr->next;
    }
    node_t* temp_n = NULL;
    for (; counted_list != NULL; counted_list = temp_n)
    {
        temp_n = counted_list->next;
        free(counted_list->word);
        free(counted_list);
    }
    return out;
}

/**
 * Function: read_list3
 * --------------
 * @brief reads the first linked list and count nuber of time each value appears for q3
 *
 * @param out the output file
 * @param variables the struct that will hold the arguments passed to the program's values
 * @param link_list the linked list that holds the appropriate input file values
 * @param size the size/number of elements to print to the output file
 * @return node_t - the linked list
 *
 */
FILE* read_list3(node_t* link_list, FILE* out, strct* variables, int size) {
    node_t* curr = NULL;
    node_t* counted_list = NULL;
    int stat = 0;
    for (curr = link_list; curr->next != NULL; curr = curr->next) {
        if (strcmp(curr->word, curr->next->word) == 0) {
            stat++;
        }
        else {
            stat++;
            curr->count = stat;
            char* counted_c = curr->word;
            int counted_int = curr->count;
            counted_list = add_inorder2(counted_list, new_node2(counted_c, counted_int));
            stat = 0;
        }

    }
    stat++;
    curr->count = stat;
    char* counted_c = curr->word;
    int counted_int = curr->count;
    counted_list = add_inorder2(counted_list, new_node2(counted_c, counted_int));
    node_t* counted_curr = counted_list;
    fprintf(out, "subject,statistic\n");
    for (int i = 0; i < size; i++) {
        fprintf(out, "\"%s\",%d\n", counted_curr->word, counted_curr->count);
        counted_curr = counted_curr->next;
    }
    node_t* temp_n = NULL;
    for (; counted_list != NULL; counted_list = temp_n)
    {
        temp_n = counted_list->next;
        free(counted_list->word);
        free(counted_list);
    }
    return out;
}

/**
 * @brief The main function and entry point of the program.
 *
 * @param argc The number of arguments passed to the program.
 * @param argv The list of arguments passed to the program.
 * @return int 0: No errors; 1: Errors produced.
 *
 */
int main(int argc, char *argv[])
{
    strct variables;
    int size = argument_processing(argc, argv, &variables);
    FILE* out;
    out = fopen("output.csv", "w");
    node_t *link_list = NULL;
    char *q1 = "1";
    char *q2 = "2";
    char *q3 = "3";
    if(strcmp(variables.question_num, q1) == 0) {
        link_list = read_fileq1(out, &variables, link_list);
        out = read_list1(link_list, out, &variables, size);
    }else if (strcmp(variables.question_num, q2) == 0) {
        link_list = read_fileq2(out, &variables, link_list);
        out = read_list2(link_list, out, &variables, size);
    }else if(strcmp(variables.question_num, q3) == 0) {
        link_list = read_fileq3(out, &variables, link_list);
        out = read_list3(link_list, out, &variables, size);
    }
    fclose(out);
    node_t* temp_n = NULL;
    for (; link_list != NULL; link_list = temp_n)
    {
        temp_n = link_list->next;
        free(link_list->word);
        free(link_list);
    }

    exit(0);
}
