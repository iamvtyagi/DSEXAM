#include <stdio.h>
#include <stdlib.h>

// Structure for polynomial term
struct Term {
    int coefficient;
    int exponent;
    struct Term* next;
};

// Function to create a new term
struct Term* createTerm(int coeff, int exp) {
    struct Term* newTerm = (struct Term*)malloc(sizeof(struct Term));
    newTerm->coefficient = coeff;
    newTerm->exponent = exp;
    newTerm->next = NULL;
    return newTerm; 
}

// Function to insert a term into polynomial (in descending order of exponents)
void insertTerm(struct Term** poly, int coeff, int exp) {
    struct Term* newTerm = createTerm(coeff, exp);
    
    // If list is empty or new term has higher exponent than first term
    if (*poly == NULL || exp > (*poly)->exponent) {
        newTerm->next = *poly;
        *poly = newTerm;
        return;
    }
    
    // Find position to insert
    struct Term* current = *poly;
    while (current->next != NULL && current->next->exponent > exp) {
        current = current->next;
    }
    
    // If term with same exponent exists, add coefficients
    if (current->exponent == exp) {
        current->coefficient += coeff;
        free(newTerm);
        return;
    }
    
    newTerm->next = current->next;
    current->next = newTerm;
}

// Function to display polynomial
void displayPolynomial(struct Term* poly) {
    if (poly == NULL) {
        printf("0\n");
        return;
    }
    
    struct Term* current = poly;
    while (current != NULL) {
        if (current->coefficient != 0) {
            if (current != poly && current->coefficient > 0) {
                printf("+");
            }
            
            if (current->coefficient == -1 && current->exponent != 0) {
                printf("-");
            } else if (current->coefficient != 1 || current->exponent == 0) {
                printf("%d", current->coefficient);
            }
            
            if (current->exponent > 0) {
                printf("x");
                if (current->exponent > 1) {
                    printf("^%d", current->exponent);
                }
            }
        }
        current = current->next;
    }
    printf("\n");
}

// Function to add two polynomials
struct Term* addPolynomials(struct Term* poly1, struct Term* poly2) {
    struct Term* result = NULL;
    struct Term *p1 = poly1, *p2 = poly2;
    
    // Add terms while both polynomials have terms
    while (p1 != NULL && p2 != NULL) {
        if (p1->exponent > p2->exponent) {
            insertTerm(&result, p1->coefficient, p1->exponent);
            p1 = p1->next;
        } else if (p2->exponent > p1->exponent) {
            insertTerm(&result, p2->coefficient, p2->exponent);
            p2 = p2->next;
        } else {
            // Same exponents, add coefficients
            int sum = p1->coefficient + p2->coefficient;
            if (sum != 0) {
                insertTerm(&result, sum, p1->exponent);
            }
            p1 = p1->next;
            p2 = p2->next;
        }
    }
    
    // Add remaining terms from poly1
    while (p1 != NULL) {
        insertTerm(&result, p1->coefficient, p1->exponent);
        p1 = p1->next;
    }
    
    // Add remaining terms from poly2
    while (p2 != NULL) {
        insertTerm(&result, p2->coefficient, p2->exponent);
        p2 = p2->next;
    }
    
    return result;
}

// Function to multiply two polynomials
struct Term* multiplyPolynomials(struct Term* poly1, struct Term* poly2) {
    struct Term* result = NULL;
    struct Term* p1 = poly1;
    
    // Multiply each term of poly1 with each term of poly2
    while (p1 != NULL) {
        struct Term* p2 = poly2;
        while (p2 != NULL) {
            int coeff = p1->coefficient * p2->coefficient;
            int exp = p1->exponent + p2->exponent;
            insertTerm(&result, coeff, exp);
            p2 = p2->next;
        }
        p1 = p1->next;
    }
    
    return result;
}

int main() {
    struct Term *poly1 = NULL, *poly2 = NULL;
    
    // Create first polynomial: 3x^2 + 2x + 1
    insertTerm(&poly1, 3, 2);
    insertTerm(&poly1, 2, 1);
    insertTerm(&poly1, 1, 0);
    
    // Create second polynomial: 2x^2 - x + 3
    insertTerm(&poly2, 2, 2);
    insertTerm(&poly2, -1, 1);
    insertTerm(&poly2, 3, 0);
    
    printf("First Polynomial: ");
    displayPolynomial(poly1);
    printf("Second Polynomial: ");
    displayPolynomial(poly2);
    
    // Add polynomials
    struct Term* sum = addPolynomials(poly1, poly2);
    printf("Sum of polynomials: ");
    displayPolynomial(sum);
    
    // Multiply polynomials
    struct Term* product = multiplyPolynomials(poly1, poly2);
    printf("Product of polynomials: ");
    displayPolynomial(product);
    
    return 0;
}