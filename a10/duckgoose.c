#include <stdio.h>
#include <stdlib.h>

typedef struct Person
{
    int id;
    int speed;
    struct Person *next;
} Person;

Person updatePerson(int id, int speed)
{
    Person new_person = {id, speed, NULL};
    return new_person;
}

void addPerson(Person **start, Person *new)
{
    // Edge case for first person
    if (*start == NULL)
    {
        *start = new;
        new->next = new;
        return;
    }

    Person *prev_person = *start;
    new->next = prev_person;
    while (prev_person->next->id != (*start)->id)
    {
        prev_person = prev_person->next;
    }
    prev_person->next = new;
}

// removes person w/ given id
void removePerson(Person *start, int id)
{
    Person *curr_person = start;

    while (curr_person->next->id != id)
    {
        curr_person = curr_person->next;
    }

    Person *loser = curr_person->next;
    curr_person->next = loser->next;
    free(loser);
}

// Returns the winner
Person *play(Person *start)
{
    if (start->id == start->next->id)
    {
        printf("winner! %d\n", start->id);
        return start;
    }

    // loops n + 1 times to find goose
    Person *goose = start;
    for (int i = 0; i < start->id + 1; i++)
    {
        // Skips over active player
        if (goose->id == start->id)
        {
            goose = goose->next;
        }

        // Prints duck or goose
        if (i == start->id)
        {
            printf("%d goose! %d\n", start->id, goose->id);
            break;
        }

        printf("%d duck %d\n", start->id, goose->id);
        goose = goose->next;
    }

    // Determine winner and call play again
    if (start->speed > goose->speed)
    {
        removePerson(start, goose->id);
        return play(start);
    }
    else
    {
        removePerson(goose, start->id);
        return play(goose);
    }
}

int main(void)
{
    int p, s;

    // List of people
    Person *lop = NULL;

    // Read in participants
    while (scanf("%d %d", &p, &s) == 2)
    {
        Person *np = (Person *)malloc(sizeof(Person));
        *np = updatePerson(p, s);
        addPerson(&lop, np);
    }

    Person *winner = play(lop);
    free(winner);
}