**Nume: Andrei-Radu Manea**

**Grupă: 313CA**

## Momente disperate - Tema 1 IOCLA

### Descriere:

Functionalitatea temei:
** int add_last(void **arr, int *len, data_structure *data)
- functia verifica daca exista vreun element in vector si aloca / realoca memorie in functie de conditie.
- se parcurge vectorul si se ajunge la sfarsitul datelor, apoi se aloca de la sfarsit spatiu pentru a stoca un nou element.
- se copiaza datele pe rand, se elibereaza structura din care s-au extras datele si se incrementeaza lungimea vectorului.

* int add_at(void **arr, int *len, data_structure *data, int index)
- se verifica daca indexul dat este peste lungimea vectorului, iar daca este asa, elementul se adauga la finalul vectorului.
-se parcurge vectorul de 2 ori, o data pana la finalul sau si o data pana la locul (dat de index) unde vrem sa introducem un nou element.

- se realoca memorie pentru noul element in vector; se shifteaza memoria de dupa locul unde incepe noul element, cu dimensiunea sa, apoi se introduc in spatiul ramas datele elementului.

- se elibereaza structura si se incrementeaza lungimea vect.

* void find(void *data_block, int len, int index) 
- se parcurge vectorul pana dinaintea elementului care este cautat.
-este extras tipul, iar in functie de acesta sunt extrase datele in niste variabile temporare si sunt printate.

* int delete_at(void **arr, int *len, int index)
- se parcurge iarasi vectorul de doua ori, o data pana la final si o data pana la elementul care trebuie sters.
- se muta memoria de dupa elementul sters in spate cu spatiile pe care elementul le ocupa, apoi se realoca si redimensioneaza vectorul.

* void print(void *arr, int len)
- se parcurge vectorul, citindu-se tipul si lungimea datelor, apoi in functie de tipul citit se aloca memorie diferit pentru tipul de int si sunt afisate elementele, in functie de tipul de bancnota, in formatul:
Tipul <tip>
<nume1> pentru <nume2>
<bancnota1>
<bancnota2>
<\n>
- se elibereaza bufferele si se continua printarea elementelor, pana cand toate sunt afisate.


### Resurse / Bibliografie:

1. (https://www.geeksforgeeks.org)
2. (https://www.tutorialspoint.com)
