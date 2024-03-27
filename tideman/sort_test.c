#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);
            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if(strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    int voted[candidate_count]; //candidates who have already voted
    for (int i = 0; i < candidate_count; i++) //Populate the array with placeholder numbers
    {
        voted[i] = -5;
    }

    for (int i = 0; i < candidate_count; i++) //Populate the preferences array
    {
        int mvpc = (candidate_count - 1) - i; //Max Votes Per Candidate

        for (int j = 0; j < candidate_count || mvpc != 0; j++)
        {
            if(ranks[i] != j && mvpc > 0 && voted[j] != j)
            {
                preferences[ranks[i]][j]++;
                mvpc--;
            }
        }
        voted[i] = ranks[i]; //Save the candidate who voted
    }

    //Debug
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            printf("[%i]", preferences[i][j]);
        }
        printf("\n");
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if(preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
        }
    }

    //Debug
    printf("Número de pares: %i\n", pair_count);

    printf("\nWinners: ");
    for (int i = 0; i < pair_count; i++)
    {
        printf("[%i]", pairs[i].winner);
    }
    printf("\nLosers:  ");
    for (int i = 0; i < pair_count; i++)
    {
        printf("[%i]", pairs[i].loser);
    }
    printf("\n\n");

    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{

    for (int i = 0; i < pair_count; i++)
    {
        pair strenght;
        strenght = pairs[i];

        for (int j = 0; j < pair_count; j++)
        {
            if(preferences[pairs[i].winner][pairs[i].loser] > preferences[pairs[j].winner][pairs[j].loser])
            {
                pairs[i] = pairs[j];
                pairs[j] = strenght;
                strenght = pairs[i];
            }
        }
    }

    //Debug
    printf("\nSort Winners: ");
    for (int i = 0; i < pair_count; i++)
    {
        printf("[%i]", pairs[i].winner);
    }
    printf("\nSort Losers:  ");
    for (int i = 0; i < pair_count; i++)
    {
        printf("[%i]", pairs[i].loser);
    }
    printf("\n\n");

    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        int l = 0;
        locked[pairs[i].winner][pairs[i].loser] = true;
        for (int j = 0; j < candidate_count; j++)
        {
            for (int k = 0; k < candidate_count; k++)
            {
                if(locked[k][j])
                {
                    l++;
                    break;
                }
            }
        }
        if(l == candidate_count)
        {
            locked[pairs[i].winner][pairs[i].loser] = false;
        }
    }

    //Debug
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if(locked[i][j])
            {
                printf("[TRUE]");
            }
            if(!locked[i][j])
            {
                printf("[FAKE]");
            }
        }
        printf("\n");
    }
    printf("\n\n");

    return;
}

// Print the winner of the election
void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        int k = 0;
        for (int j = 0; j < candidate_count; j++)
        {
            if(!locked[j][i])
            {
                k++;
            }
        }

        if(k == candidate_count)
        {
            printf("True winner: %s\n", candidates[i]);
        }
    }
    return;
}

