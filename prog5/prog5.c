#include <stdio.h>

union decision {
    unsigned char flags;
    struct {
        unsigned int your_choice:1; 
        unsigned int your_mothers_choice:1;
        unsigned int your_fathers_choice:1;
        unsigned int socially_acceptable:1;
        unsigned int financially_viable:1;
        unsigned int do_you_aptitude:1;
        unsigned int do_you_likeit:1;
        unsigned int decision:1; 
    }; 
};

void make_decision(union decision *d) {
    d->your_choice = (d->do_you_aptitude && d->do_you_likeit);
    d->decision = d->your_choice;
}

void print_decision(union decision d) {
    printf("\n--- Decision Narrative ---\n");
    if (d.decision == 1) {
        printf("🚀 You are moving forward with this choice!\n");
        printf("You have the aptitude and the passion for it.\n");
        if (d.your_mothers_choice && d.your_fathers_choice) {
            printf("👪 Plus, you have your family's full support!\n");
        } else {
            printf("⚠️ You are pursuing this path even though your parents have doubts.\n");
        }
    } else {
        printf("🛑 You decided not to go through with this.\n");
        printf("Either the passion or the aptitude wasn't there.\n");
    }
}

void print_conclusion_based_on_flags(union decision d) {
    printf("\n--- Final Conclusion (Score: %d) ---\n", d.flags);
    if (d.flags >= 128) {
        printf("🏆 Verdict: SUCCESS. The final decision is a GO!\n");
    } else {
        printf("❌ Verdict: REJECTED. The final decision is a NO-GO.\n");
    }
}

int main() {
    union decision my_choice;
    
    my_choice.flags = 0; 
    
    my_choice.do_you_likeit = 1;
    my_choice.do_you_aptitude = 1;
    my_choice.your_mothers_choice = 0;
    my_choice.your_fathers_choice = 0;
    my_choice.financially_viable = 0;
    my_choice.socially_acceptable = 1;
    
    make_decision(&my_choice);

    print_decision(my_choice);
    print_conclusion_based_on_flags(my_choice);
    
    return 0;
}