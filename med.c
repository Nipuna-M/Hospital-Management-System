#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_NAME 50
#define MAX_DOCTORS 10
#define MAX_PATIENTS 100

// Structures
struct Doctor {
    char name[MAX_NAME];
    char specialization[MAX_NAME];
    int room_number;
    float consultation_fee;
};

struct Patient {
    char name[MAX_NAME];
    int age;
    char phone[15];
    char disease[100];
    char prescribed_medicines[200];
    char precautions[200];
    char next_visit[20];
    float medicine_cost;
    float total_bill;
};

struct Appointment {
    char patient_name[MAX_NAME];
    char doctor_name[MAX_NAME];
    char date[20];
    char time[10];
};

// Global variables
struct Doctor doctors[MAX_DOCTORS];
int doctor_count = 0;

// Function declarations
void loadDoctors();
void channelDoctor();
void generateBill(struct Patient *patient, float consultation_fee);
void savePrescription(struct Patient *patient, const char *doctor_name);
int getDoctorIndex(const char *doctor_name);

// Main function
int main() {
    int choice;

    // Load doctor data
    loadDoctors();

    while (1) {
        printf("\nHospital Management System\n");
        printf("1. Channel a Doctor\n");
        printf("2. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Clear input buffer

        switch (choice) {
            case 1:
                channelDoctor();
                break;
            case 2:
                printf("Thank you for using our system!\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

// Load doctor information from file
void loadDoctors() {
    // Sample data - in real implementation, this would read from a file
    strcpy(doctors[0].name, "Dr. Smith");
    strcpy(doctors[0].specialization, "Cardiologist");
    doctors[0].room_number = 101;
    doctors[0].consultation_fee = 2000.0;

    strcpy(doctors[1].name, "Dr. Johnson");
    strcpy(doctors[1].specialization, "Pediatrician");
    doctors[1].room_number = 102;
    doctors[1].consultation_fee = 1500.0;

    doctor_count = 2;
}

// Channel a doctor functionality
void channelDoctor() {
    struct Patient patient;
    struct Appointment appointment;
    int doctor_choice;

    // Display available doctors
    printf("\nAvailable Doctors:\n");
    for (int i = 0; i < doctor_count; i++) {
        printf("%d. %s - %s (Room: %d)\n",
               i + 1,
               doctors[i].name,
               doctors[i].specialization,
               doctors[i].room_number);
    }

    // Get doctor choice
    printf("Select doctor (1-%d): ", doctor_count);
    scanf("%d", &doctor_choice);
    getchar();

    if (doctor_choice < 1 || doctor_choice > doctor_count) {
        printf("Invalid doctor selection.\n");
        return;
    }

    // Get patient details
    printf("Enter patient name: ");
    fgets(patient.name, MAX_NAME, stdin);
    patient.name[strcspn(patient.name, "\n")] = 0;

    printf("Enter patient age: ");
    scanf("%d", &patient.age);
    getchar();

    printf("Enter patient phone: ");
    fgets(patient.phone, 15, stdin);
    patient.phone[strcspn(patient.phone, "\n")] = 0;

    // Generate appointment time (simplified)
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    sprintf(appointment.date, "%02d/%02d/%d",
            t->tm_mday, t->tm_mon + 1, t->tm_year + 1900);
    sprintf(appointment.time, "%02d:00", (t->tm_hour + 1) % 24);

    // Display appointment details
    printf("\nAppointment Details:\n");
    printf("Doctor: %s\n", doctors[doctor_choice-1].name);
    printf("Room Number: %d\n", doctors[doctor_choice-1].room_number);
    printf("Date: %s\n", appointment.date);
    printf("Time: %s\n", appointment.time);

    // Get consultation details
    printf("\nEnter disease/symptoms: ");
    fgets(patient.disease, 100, stdin);
    patient.disease[strcspn(patient.disease, "\n")] = 0;

    printf("Enter prescribed medicines: ");
    fgets(patient.prescribed_medicines, 200, stdin);
    patient.prescribed_medicines[strcspn(patient.prescribed_medicines, "\n")] = 0;

    printf("Enter precautions: ");
    fgets(patient.precautions, 200, stdin);
    patient.precautions[strcspn(patient.precautions, "\n")] = 0;

    printf("Enter next visit date: ");
    fgets(patient.next_visit, 20, stdin);
    patient.next_visit[strcspn(patient.next_visit, "\n")] = 0;

    printf("Enter medicine cost: ");
    scanf("%f", &patient.medicine_cost);

    // Generate and display bill
    generateBill(&patient, doctors[doctor_choice-1].consultation_fee);

    // Save prescription
    savePrescription(&patient, doctors[doctor_choice-1].name);
}

// Generate bill
void generateBill(struct Patient *patient, float consultation_fee) {
    printf("\n=== Bill ===\n");
    printf("Patient Name: %s\n", patient->name);
    printf("Consultation Fee: %.2f\n", consultation_fee);
    printf("Medicine Cost: %.2f\n", patient->medicine_cost);
    patient->total_bill = consultation_fee + patient->medicine_cost;
    printf("Total Amount: %.2f\n", patient->total_bill);
    printf("===========\n");
}

// Save prescription to file
void savePrescription(struct Patient *patient, const char *doctor_name) {
    FILE *fp = fopen("prescriptions.txt", "a");
    if (fp != NULL) {
        fprintf(fp, "\nPrescription Details:\n");
        fprintf(fp, "Patient Name: %s\n", patient->name);
        fprintf(fp, "Doctor: %s\n", doctor_name);
        fprintf(fp, "Disease: %s\n", patient->disease);
        fprintf(fp, "Medicines: %s\n", patient->prescribed_medicines);
        fprintf(fp, "Precautions: %s\n", patient->precautions);
        fprintf(fp, "Next Visit: %s\n", patient->next_visit);
        fprintf(fp, "Total Bill: %.2f\n", patient->total_bill);
        fprintf(fp, "------------------------\n");
        fclose(fp);
    }
}
