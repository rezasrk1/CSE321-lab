#include <stdio.h>

typedef struct {
    int quantity;
    float unit_price;
} Item;

int main() {
    
    Item paratha, vegetable, mineral_water;
    int number_of_people;
    float total_bill, amount_per_person;

    
    printf("Quantity Of Paratha: ");
    scanf("%d", &paratha.quantity);
    printf("Unit Price: ");
    scanf("%f", &paratha.unit_price);

    printf("Quantity Of Vegetables: ");
    scanf("%d", &vegetable.quantity);
    printf("Unit Price: ");
    scanf("%f", &vegetable.unit_price);

    printf("Quantity Of Mineral Water: ");
    scanf("%d", &mineral_water.quantity);
    printf("Unit Price: ");
    scanf("%f", &mineral_water.unit_price);

    printf("Number of People: ");
    scanf("%d", &number_of_people);

    total_bill = (paratha.quantity * paratha.unit_price) +
                 (vegetable.quantity * vegetable.unit_price) +
                 (mineral_water.quantity * mineral_water.unit_price);

    if (number_of_people > 0) {
        amount_per_person = total_bill / number_of_people;
    } else {
        printf("Error: Number of people must be greater than 0.\n");
        return 1; 
    }

    
    printf("Individual people will pay: %.2f tk\n", amount_per_person);

    return 0;
}

