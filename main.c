// Copyright 2022 Andrei-Radu Manea 313CA
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include "structs.h"

// SIDE NOTE: toate switch-urile au nume / bancnota cu o extensie "_X" deoarece primeam erori de redefinire
// daca aveam declaratii in diferite switch uri ale unor variabile cu acelasi nume.


// functie pt a extrage datele primite la input in structura data
data_structure *parameters(char *line) {
    data_structure *data = malloc(sizeof(data_structure));
    if(!data) return NULL;

    data->header = malloc(sizeof(head));
    if(!data->header) return NULL;

    data->header->len = 0;

    line = strtok(line, "\n ");
    memcpy(&data->header->type, line, sizeof(unsigned char));

    line = strtok(NULL, "\n ");
    char *nume1 = malloc(strlen(line) + 1);
    if(!nume1) return NULL;

    data->header->len += strlen(line) + 1;
    strcpy(nume1, line);

    // switch care depinde de tipul de bancnote dat si
    // lstocheaza datele in functie de dimensiune
    switch (data->header->type)
    {
    case '1':
        int8_t b1_1, b2_1;
        line = strtok(NULL, "\n ");
        b1_1 = atoi(line);

        line = strtok(NULL, "\n ");
        b2_1 = atoi(line);

        data->header->len += 2 * sizeof(int8_t);

        line = strtok(NULL, "\n ");
        char *nume2_1 = malloc(strlen(line) + 1);
        if(!nume2_1) return NULL;

        data->header->len += strlen(line) + 1;
        strcpy(nume2_1, line);

        data->data = malloc(data->header->len);
        if(!data->data) return NULL;

        memcpy(data->data, nume1, strlen(nume1) + 1);
        memcpy(data->data + strlen(nume1) + 1, &b1_1, sizeof(b1_1));
        memcpy(data->data + strlen(nume1) + 1 + sizeof(b1_1), &b2_1, sizeof(b2_1));
        memcpy(data->data + strlen(nume1) + 1 + 2 * sizeof(b1_1), nume2_1, strlen(nume2_1) + 1);
        free(nume2_1);
        break;
    
    case '2':
        int16_t b1_2;
        int32_t b2_2;
        line = strtok(NULL, "\n ");
        b1_2 = atoi(line);

        line = strtok(NULL, "\n ");
        b2_2 = atoi(line);

        data->header->len += sizeof(int16_t) + sizeof(int32_t);

        line = strtok(NULL, "\n ");
        char *nume2_2 = malloc(strlen(line) + 1);
        if(!nume2_2) return NULL;

        data->header->len += strlen(line) + 1;
        strcpy(nume2_2, line);

        data->data = malloc(data->header->len);
        if(!data->data) return NULL;

        memcpy(data->data, nume1, strlen(nume1) + 1);
        memcpy(data->data + strlen(nume1) + 1, &b1_2, sizeof(b1_2));
        memcpy(data->data + strlen(nume1) + 1 + sizeof(b1_2), &b2_2, sizeof(b2_2));
        memcpy(data->data + strlen(nume1) + 1 + sizeof(b1_2) + sizeof(b2_2), nume2_2, strlen(nume2_2) + 1);
        free(nume2_2);
        break;

    case '3':
        int32_t b1_3, b2_3;
        line = strtok(NULL, "\n ");
        b1_3 = atoi(line);

        line = strtok(NULL, "\n ");
        b2_3 = atoi(line);

        data->header->len += 2 * sizeof(int32_t);

        line = strtok(NULL, "\n ");
        char *nume2_3 = malloc(strlen(line) + 1);
        if(!nume2_3) return NULL;

        data->header->len += strlen(line) + 1;
        strcpy(nume2_3, line);

        data->data = malloc(data->header->len);
        if(!data->data) return NULL;

        memcpy(data->data, nume1, strlen(nume1) + 1);
        memcpy(data->data + strlen(nume1) + 1, &b1_3, sizeof(b1_3));
        memcpy(data->data + strlen(nume1) + 1 + sizeof(b1_3), &b2_3, sizeof(b2_3));
        memcpy(data->data + strlen(nume1) + 1 + 2 * sizeof(b1_3), nume2_3, strlen(nume2_3) + 1);
        free(nume2_3);
        break;

    default:
        break;
    }

    free(nume1);

    return data;
    
}

// functie care adauga un element la sf. vectorului
int add_last(void **arr, int *len, data_structure *data)
{
    uint mem = 0;
    
    // se verifica daca vectorul dat este gol sau nu
    if(*len == 0)
    {
        *arr = malloc(sizeof(uchar) + sizeof(uint) + data->header->len);
        if(!*arr) return -1;
    } else
    {
        uint var = 0;

        for(int i = 0; i < *len; i++)
        {
            mem+= sizeof(uchar);
            var = *(uint*)(*arr + mem);
            mem+= sizeof(uint) + var;
        }
        *arr = realloc(*arr, mem + sizeof(uchar) + sizeof(uint) + data->header->len);
        if(!*arr) return -1;
    }

    // se adauga datele, pe rand, una dupa alta
    memcpy(*arr + mem, &data->header->type, sizeof(uchar));

    memcpy(*arr + mem + sizeof(uchar), &data->header->len, sizeof(uint));

    memcpy(*arr + mem + sizeof(uchar) + sizeof(uint), data->data, data->header->len);

    (*len)++;

    // eliberarea structurii de date primita ca parametru
    free(data->header);
    free(data->data);
    free(data);

    return 0;
}

// functie care adauga un element la indexul dat
int add_at(void **arr, int *len, data_structure *data, int index)
{
    // daca indexul dat este mai mare decat nr. de elemente,
    // aceste ia valoarea lungimii totale, iar elementul nou
    // este adaugat la final
    if(index >= *len) index = *len;

    int mem = 0, mem_index = 0;

    uint var = 0;
    uint var2 = 0;

    // vectorul este parcurs de doua ori, o data pana la final pt. realocare
    for(int i = 0; i < *len; i++)
    {
        mem += sizeof(uchar);
        var = *(uint*)(*arr + mem);
        mem += sizeof(uint) + var;
    }

    // si inca o data este parcurs pana la indexul unde vrem sa introducem noul element
    for(int i = 0; i < index; i++)
    {
        mem_index += sizeof(uchar);
        var2 = *(uint*)(*arr + mem_index);
        mem_index += sizeof(uint) + var2;
    }

    // se realoca memorie pentru a include noul element
    *arr = realloc(*arr, mem + sizeof(uchar) + sizeof(uint) + data->header->len);
    if(!*arr) return -1;
    
    // se muta datele care sunt dupa indexul dat, in functie de dimensiunea noului element
    memcpy(*arr + mem_index + sizeof(uchar) + sizeof(uint) + data->header->len, *arr + mem_index, mem - mem_index);

    // se copiaza datele noului element, pe rand, in locul ramas
    memcpy(*arr + mem_index, &data->header->type, sizeof(uchar));

    memcpy(*arr + mem_index + sizeof(uchar), &data->header->len, sizeof(uint));

    memcpy(*arr + mem_index + sizeof(uchar) + sizeof(uint), data->data, data->header->len);

    // incrementeaza lungimea vect. si se elibereaza structura de date
    (*len)++;

    free(data->header);
    free(data->data);
    free(data);

    return 0;
}


// functie care primeste ca parametru un index si afiseaza elementul de la indexul respectiv
void find(void *data_block, int len, int index) 
{
    uint mem_index = 0;
    uint var2;

    // se parcurge vectorul pana dinaintea acelui element
    for(int i = 0; i < index; i++)
    {
        mem_index += sizeof(uchar);
        var2 = *(uint*)(data_block + mem_index);
        mem_index += sizeof(uint) + var2;
    }

    uchar tip;

    memcpy(&tip, data_block + mem_index, sizeof(tip));
    mem_index += sizeof(tip);

    unsigned int dlen;
    memcpy(&dlen, data_block + mem_index, sizeof(dlen));
    mem_index += sizeof(dlen);

    // lungimea numelui, fara type / len.
    int nume_len = strlen(data_block + mem_index) + 1;

    char *nume1 = malloc(nume_len);
    if(!nume1) return; 

    memcpy(nume1, data_block + mem_index, nume_len);
    mem_index += nume_len;

    // intra intr-un switch care depinde de tipul de bancnota si afiseaza elementul gasit
    switch (tip)
    {
    case '1':
        int8_t b1_1, b2_1;
        memcpy(&b1_1, data_block + mem_index, sizeof(b1_1));
        mem_index += sizeof(b1_1);

        memcpy(&b2_1, data_block + mem_index, sizeof(b2_1));
        mem_index += sizeof(b2_1);

        nume_len = strlen(data_block + mem_index) + 1;

        char *nume2_1 = malloc(nume_len);
        if(!nume2_1) return;
         
        memcpy(nume2_1, data_block + mem_index, nume_len);
        mem_index += nume_len;

        printf("Tipul %c\n", tip);
        printf("%s pentru %s\n", nume1, nume2_1);
        printf("%"PRId8"\n%"PRId8"\n", b1_1, b2_1);

        free(nume2_1);
        break;
    
    case '2':
        int16_t b1_2;
        int32_t b2_2;
        memcpy(&b1_2, data_block + mem_index, sizeof(b1_2));
        mem_index += sizeof(b1_2);

        memcpy(&b2_2, data_block + mem_index, sizeof(b2_2));
        mem_index += sizeof(b2_2);

        nume_len = strlen(data_block + mem_index) + 1;

        char *nume2_2 = malloc(nume_len);
        if(!nume2_2) return;

        memcpy(nume2_2, data_block + mem_index, nume_len);
        mem_index += nume_len;

        printf("Tipul %c\n", tip);
        printf("%s pentru %s\n", nume1, nume2_2);
        printf("%"PRId8"\n%"PRId8"\n", b1_2, b2_2);
        
        free(nume2_2);
        break;

    case '3':
        int32_t b1_3;
        int32_t b2_3;
        memcpy(&b1_3, data_block + mem_index, sizeof(b1_3));
        mem_index += sizeof(b1_3);

        memcpy(&b2_3, data_block + mem_index, sizeof(b2_3));
        mem_index += sizeof(b2_3);

        nume_len = strlen(data_block + mem_index) + 1;

        char *nume2_3 = malloc(nume_len);
        if(!nume2_3) return;

        memcpy(nume2_3, data_block + mem_index, nume_len);
        mem_index += nume_len;

        printf("Tipul %c\n", tip);
        printf("%s pentru %s\n", nume1, nume2_3);
        printf("%"PRId8"\n%"PRId8"\n", b1_3, b2_3);

        free(nume2_3);
        break;

    default:
        break;
    }

    free(nume1);
    printf("\n");
}

// functie care primeste ca parametru un index si sterge elementul de pe pozitia respectiva;
// aceasta muta zona de memorie de dupa element, pe pozitia de unde elementul respectiv incepe (dat de mem_index in acest caz)
// apoi, vectorul este realocat cu dimensiunea totala, scazand dimensiunea elementului sters.
int delete_at(void **arr, int *len, int index)
{
    int mem = 0, mem_index = 0;

    uint var = 0;
    uint var2 = 0;

    for(int i = 0; i < *len; i++)
    {
        mem += sizeof(uchar);
        var = *(uint*)(*arr + mem);
        mem += sizeof(uint) + var;
    }

    for(int i = 0; i < index; i++)
    {
        mem_index += sizeof(uchar);
        var2 = *(uint*)(*arr + mem_index);
        mem_index += sizeof(uint) + var2;
    }

    uint rem_len;
    memcpy(&rem_len, *arr + mem_index + sizeof(uchar), sizeof(uint));
    memcpy(*arr + mem_index, *arr + mem_index + sizeof(uchar) + sizeof(uint) + rem_len, mem - mem_index - (sizeof(uchar) + sizeof(uint) + rem_len));\

    *arr = realloc(*arr, mem - (sizeof(uchar) + sizeof(uint) + rem_len));
    if(!arr) return -1;
    (*len)--;

    return 0;
}

// functie care afiseaza toate elementele din vectorul dat
void print(void *arr, int len) {
    unsigned char tip;
    int index = 0;
    
    for(uint i = 0; i < len; i++)
    {
        memcpy(&tip, arr + index, sizeof(tip));
        index += sizeof(tip);

        unsigned int dlen;
        memcpy(&dlen, arr + index, sizeof(dlen));
        index += sizeof(dlen);

        int nume_len = strlen(arr + index) + 1;

        char *nume1 = malloc(nume_len);
        if(!nume1) return;

        // se extrage primul nume din vector intr-un buffer
        memcpy(nume1, arr + index, nume_len);
        index += nume_len;

        // iarasi un switch care depinde de tipul bancnotelor
        switch (tip)
        {
        case '1':
            int8_t b1_1, b2_1;
            memcpy(&b1_1, arr + index, sizeof(b1_1));
            index += sizeof(b1_1);

            memcpy(&b2_1, arr + index, sizeof(b2_1));
            index += sizeof(b2_1);

            nume_len = strlen(arr + index) + 1;

            char *nume2_1 = malloc(nume_len);
            if(!nume2_1) return;

            memcpy(nume2_1, arr + index, nume_len);
            index += nume_len;

            printf("Tipul %c\n", tip);
            printf("%s pentru %s\n", nume1, nume2_1);
            printf("%"PRId8"\n%"PRId8"\n", b1_1, b2_1);
            free(nume2_1);
            break;
        
        case '2':
            int16_t b1_2;
            int32_t b2_2;
            memcpy(&b1_2, arr + index, sizeof(b1_2));
            index += sizeof(b1_2);

            memcpy(&b2_2, arr + index, sizeof(b2_2));
            index += sizeof(b2_2);

            nume_len = strlen(arr + index) + 1;

            char *nume2_2 = malloc(nume_len);
            if(!nume2_2) return;

            memcpy(nume2_2, arr + index, nume_len);
            index += nume_len;

            printf("Tipul %c\n", tip);
            printf("%s pentru %s\n", nume1, nume2_2);
            printf("%"PRId8"\n%"PRId8"\n", b1_2, b2_2);
            free(nume2_2);
            break;

        case '3':
            int32_t b1_3;
            int32_t b2_3;
            memcpy(&b1_3, arr + index, sizeof(b1_3));
            index += sizeof(b1_3);

            memcpy(&b2_3, arr + index, sizeof(b2_3));
            index += sizeof(b2_3);

            nume_len = strlen(arr + index) + 1;

            char *nume2_3 = malloc(nume_len);
            if(!nume2_3) return;

            memcpy(nume2_3, arr + index, nume_len);
            index += nume_len;

            printf("Tipul %c\n", tip);
            printf("%s pentru %s\n", nume1, nume2_3);
            printf("%"PRId8"\n%"PRId8"\n", b1_3, b2_3);
            free(nume2_3);
            break;

        default:
            break;
        }
        printf("\n");
        free(nume1);
    }
    
}


int main() {
    // the vector of bytes u have to work with
    // good luck :)
    void *arr = NULL;
    int len = 0;

    char* command = malloc(256 * sizeof(char));
    // verifica malloc uri
    char *line = malloc(256 * sizeof(char));

    // parser pentru comenzi
    while(1)
    {
        scanf("%s", command);

        if(strcmp(command, "insert") == 0)
        {
            fgets(line, 256, stdin);
            data_structure *new_data = parameters(line);
            add_last(&arr, &len, new_data);
        }
        else if(strcmp(command, "insert_at") == 0)
        {
            int idx;
            scanf("%d", &idx);
            fgets(line, 256, stdin);
            data_structure *new_data = parameters(line);
            add_at(&arr, &len, new_data, idx);
        }
        else if(strcmp(command, "delete_at") == 0)
        {
            int idx;
            scanf("%d", &idx);
            delete_at(&arr, &len, idx);
        }
        else if(strcmp(command, "find") == 0)
        {
            int idx;
            scanf("%d", &idx);
            find(arr, len, idx);
        }
        else if(strcmp(command, "print") == 0)
        {
            print(arr, len);
        }
        else if(strcmp(command, "exit") == 0)
        {
              break;
        }
    }

    // free line, command and array
    free(command);
    free(line);
    free(arr);

    return 0;
}