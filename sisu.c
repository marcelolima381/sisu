//
// Created by marcelo on 21/04/19.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sisu.h"
#include "course.h"
#include "student.h"

void showSisuResult(Course *courses, Student *students, int numberOfStudents) {
	int i;
	int firstOption;
	int secondOption;
	float score;

	for (i = 0; i < numberOfStudents; i++) {
		firstOption = students[i].firstOption;
		secondOption = students[i].secondOption;
		score = students[i].score;

//		Checa primeira opcao
		Node *node = courses[firstOption].vacancies;
		Node *last = NULL;
		int size = 0;

//		Pega tamanho da lista de aprovados no curso
		while (node != NULL) {
			size++;
			last = node;
			node = node->next;
		}

		if (size != 0) {
			if (size == courses[firstOption].numberOfVacancies) {
				if (last->student->score > score) {
//				TODO: implementar segunda opcao de curso
//				segundaOpcao();
					printf("segunda opcao");
				} else {
					node = courses[firstOption].vacancies;
					while (node != NULL) {
						if (node->student->score < score) {
							insertAfterNode(node->previous, &students[i]);
							last->previous->next = NULL;
//						segundaOpcao();
							printf("segunda opcao");
							break;
						}
						node = node->next;
					}
				}
			} else if (size < courses[firstOption].numberOfVacancies) {
				node = courses[firstOption].vacancies;
				while (node != NULL) {
					if (node->student->score < score) {
//						printf("Node: %s\n", node->student->name);
//						Node *temp = node;
						if (node->previous != NULL) {
//							insertBeforeNode(&node, node->next, &students[i]);
							Node *newNode = (Node *) malloc (sizeof(Node));
							Node *prev = (Node *) malloc (sizeof(Node));
							newNode->student = &students[i];
							Node *temp = node;
							prev = node->previous;
							node = newNode;
							node->next = temp;
							node->previous = prev;
							node->previous->next = node;
							node->next->previous = node;

						} else {
							Node *newNode = (Node *) malloc (sizeof(Node));
							newNode->student = &students[i];
							Node *temp = node;
							node = newNode;
							node->next = temp;
							node->next->previous = node;
						}
						courses[firstOption].vacancies = node;
						break;
					} else if (node->student->score > score && node->next == NULL) {
						insertAtEnd(&courses[firstOption].vacancies, &students[i]);
						break;
					}
					node = node->next;
				}
			} else {
				printf("PROBLEMA!\n");
			}
		} else {
			insertAtBeginning(&courses[firstOption].vacancies, &students[i]);
		}

		while (courses[firstOption].vacancies->previous != NULL) {
			last = courses[firstOption].vacancies;
			courses[firstOption].vacancies = courses[firstOption].vacancies->previous;
		}

	}

	printList(courses[0].vacancies);

}