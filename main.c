#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura que representa um aluno
typedef struct Student
{
    int id;                 // Identificador do aluno
    char name[50];          // Nome do aluno
    float grade;            // Nota do aluno
    struct Student *next;   // Ponteiro para o próximo aluno na lista
} Student;

// Função para criar um novo aluno
Student *create(int id, char name[], float grade)
{
    Student *newStudent = (Student *)malloc(sizeof(Student));
    if (newStudent == NULL)
    {
        printf("Erro ao alocar memória.\n");
        exit(1);
    }
    newStudent->id = id;
    strcpy(newStudent->name, name); // Copia o nome para a estrutura
    newStudent->grade = grade;
    newStudent->next = NULL;        // Inicializa o próximo como NULL
    return newStudent;
}

// Função para inserir um novo aluno no início da lista
void new(Student **head, int id, char name[], float grade)
{
    Student *newStudent = create(id, name, grade);
    newStudent->next = *head; // O próximo do novo aluno aponta para o atual início
    *head = newStudent;       // Atualiza o início da lista
    printf("Aluno inserido com sucesso!\n");
}

// Função para remover um aluno pelo ID
void delete(Student **head, int id)
{
    Student *current = *head;
    Student *previous = NULL;

    // Procura o aluno pelo ID
    while (current != NULL && current->id != id)
    {
        previous = current;
        current = current->next;
    }

    if (current == NULL)
    {
        printf("Aluno não encontrado.\n");
        return;
    }

    // Remove o aluno da lista
    if (previous == NULL)
    {
        *head = current->next; // Remove do início
    }
    else
    {
        previous->next = current->next; // Remove do meio/fim
    }

    free(current); // Libera a memória do aluno removido
    printf("Aluno removido com sucesso!\n");
}

// Função para exibir todos os alunos cadastrados
void print(Student *head)
{
    if (head == NULL)
    {
        printf("Nenhum aluno cadastrado.\n");
        return;
    }

    Student *current = head;

    // Percorre a lista e imprime os dados de cada aluno
    while (current != NULL)
    {
        printf("ID: %d\n", current->id);
        printf("Nome: %s\n", current->name);
        printf("Nota: %.2f\n", current->grade);
        printf("-----------------------\n");

        current = current->next;
    }
}

int main()
{
    Student *list = NULL; // Ponteiro para o início da lista de alunos
    int option;
    int id;
    char name[50];
    float grade;

    // Loop principal do menu
    do
    {
        printf("\n--- Sistema de Gerenciamento de Alunos ---\n");
        printf("1. Inserir aluno\n");
        printf("2. Remover aluno\n");
        printf("3. Exibir alunos\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");

        scanf("%d", &option);

        switch (option)
        {
        case 1:
            // Inserção de aluno
            printf("ID: ");
            scanf("%d", &id);
            getchar(); // Limpa o buffer do teclado
            printf("Nome: ");
            fgets(name, 50, stdin);
            name[strcspn(name, "\n")] = '\0'; // Remove o '\n' do final

            printf("Nota: ");
            scanf("%f", &grade);
            new(&list, id, name, grade);

            break;
        case 2:
            // Remoção de aluno
            printf("Informe o ID do aluno a remover: ");
            scanf("%d", &id);
            delete(&list, id);

            break;
        case 3:
            // Exibição dos alunos
            print(list);

            break;
        case 0:
            printf("Saindo...\n");

            break;
        default:
            printf("Opção inválida!\n");
        }

    } while (option != 0);

    // Libera a memória de todos os alunos antes de sair
    while (list != NULL)
    {
        Student *temp = list;
        list = list->next;
        free(temp);
    }

    return 0;
}
