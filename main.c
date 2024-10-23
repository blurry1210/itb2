#include "merkle_tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void linie(char *str) {
    char *write = str, *read = str;
    while (*read) {
        if (*read != '\"' && *read != ',' && *read != '\n') {
            *write++ = *read;
        }
        read++;
    }
    *write = '\0';
}

int main() {
    MerkleTree *tree = create_merkle_tree();
    
    FILE *file = fopen("students.txt", "r");
    
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        linie(line);

        add_element(tree, line);
    }

    fclose(file);
   // print_tree(tree);

    const char *student_name = "Alex Borza";
    MerkleProof *proof = generate_proof(tree, student_name);

    const unsigned char *root_hash = get_root_hash(tree);
    bool valid = verify_proof(root_hash, student_name, proof);

            if (valid) {
                printf("proof valid.\n");
            } else {
                printf("proof invalid.\n");
            }
    free_merkle_tree(tree);
    

    return 0;
}