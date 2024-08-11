#include <stdio.h>
#include <stdbool.h>

#define MAX_VARS 100

int n;  // Number of variables
int m;  // Number of clauses
int literals[MAX_VARS * 2];  // Variables and their negations
int implication[MAX_VARS * 2][2];  // Implication graph

bool visited[MAX_VARS * 2];
bool value[MAX_VARS * 2];
int stack[MAX_VARS * 2];
int top;

int negate(int var) {
    return (var + n) % (n * 2);
}

bool is_satisfiable() {
    // Initialize variables
    for (int i = 0; i < n * 2; i++) {
        visited[i] = false;
        value[i] = false;
    }
    top = 0;

    // Perform Depth-First Search (DFS) to find strongly connected components
    for (int i = 0; i < n * 2; i++) {
        if (!visited[i]) {
            stack[top++] = i;
            visited[i] = true;
            while (top > 0) {
                int current = stack[--top];
                for (int j = 0; j < 2; j++) {
                    int next = implication[current][j];
                    if (!visited[next]) {
                        stack[top++] = next;
                        visited[next] = true;
                    }
                }
            }
        }
    }

    // Check for unsatisfiability (i.e., variable and its negation in the same SCC)
    for (int i = 0; i < n; i++) {
        if (visited[i] && visited[negate(i)]) {
            return false;  // Unsatisfiable
        }
    }

    // Determine variable assignments
    for (int i = n * 2 - 1; i >= 0; i--) {
        if (!visited[i]) {
            int current = i;
            while (top > 0) {
                int next = stack[--top];
                visited[next] = true;
                value[next] = (current < n) ? true : false;
                current = implication[next][1];
            }
        }
    }

    return true;  // Satisfiable
}

int main() {
    // Input: Read the number of variables and clauses, and clause information
    printf("Enter number of variables and clauses: ");
    scanf("%d %d", &n, &m);
    printf("For every line, enter 2 numbers separated by a space\n");
    printf("The number should be the subscript of the variable you want the clause to conatin\n");
    printf("For eg, if clause contains x5, enter 5\n");
    printf("If the clause contains a negation, enter negative of the subscript\n");
    printf("For eg, ~x3 would be -3\n");
    printf("Sample clause (x4 V ~x7) would be input as: 4 -7\n\n");

    for (int i = 0; i < m; i++) 
    {
        int a, b;
        scanf("%d %d", &a, &b);
        // Map variables to their indices (1 to n) and negations to (n+1 to 2n)
        if (a < 0) 
            a = -a + n;
        if (b < 0) 
            b = -b + n;
        implication[negate(a)][0] = b;  // a implies b
        implication[negate(b)][0] = a;  // b implies a
    }

    // Check and print the result
    if (is_satisfiable()) {
        printf("Satisfying assignment:\n");
        for (int i = 1; i <= n; i++) {
            printf("x%d is %s\n", i, value[i] ? "True" : "False");
        }
    } else {
        printf("The 2-CNF formula is unsatisfiable.\n");
    }

    return 0;
}
