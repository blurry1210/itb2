#include "merkle_tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Funcție pentru a curăța șirul de caractere și a elimina ghilimelele, virgulele și spațiile în plus
void clean_string(char *str) {
    char *write = str, *read = str;
    while (*read) {
        if (*read != '\"' && *read != ',' && *read != '\n' && *read != '\r') {
            *write++ = *read;
        }
        read++;
    }
    *write = '\0'; // Termină șirul curățat
}
int main() {
    // Creează arborele Merkle
    MerkleTree *tree = create_merkle_tree();

    // Adaugă câteva frunze în arbore (exemplu)
    add_element(tree, "Abdulrahman Mohamed");
    add_element(tree, "Adriana Livadariu");
    add_element(tree, "Eric Iov");  // Adăugăm elementul pe care vrem să-l verificăm

    // Afișăm arborele Merkle
    printf("Arborele Merkle:\n");
    print_tree(tree);

    // Generare dovada
    const char *student_name = "Alex Borza";
    MerkleProof *proof = generate_proof(tree, student_name);

    if (proof != NULL) {
        printf("\nProba Merkle pentru '%s' a fost generată cu succes.\n", student_name);

        // Obținem hash-ul rădăcinii arborelui
        const unsigned char *root_hash = get_root_hash(tree);
        if (root_hash != NULL) {
            printf("Hash-ul rădăcinii: %s\n", hash_to_string(root_hash));

            // Verificăm proba folosind hash-ul rădăcinii
            bool valid = verify_proof(root_hash, student_name, proof);

            if (valid) {
                printf("Dovada este validă.\n");
            } else {
                printf("Dovada NU este validă.\n");
            }
        } else {
            printf("Nu s-a putut obține hash-ul rădăcinii.\n");
        }

        // Curățăm memoria
        free_merkle_proof(proof);
    } else {
        printf("Nu s-a putut genera dovada pentru '%s'.\n", student_name);
    }

    // Curățăm memoria arborelui
    free_merkle_tree(tree);

    return 0;
}
