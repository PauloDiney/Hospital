#include <stdio.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>

#define Max 15
#define WageDoctor 15000.0
#define WageNurse 2500.0

struct Patient
{
    char name[100];
    char sympton[500];
    char address[100];
    char medicamnetos[500];
    int Fone;
    int codEmployee;
    bool discharged;
};

struct Nurse
{
    char nome[100];
    float wageNurse = WageNurse;
    int codEmployee;
};

struct Doctor
{
    char name[100];
    int crm;
    int codEmployee;
    float wageDoctor = WageDoctor;
};

void createDoctorRecord()
{
    FILE *fileD = fopen("doctor.dat", "ab");
    Doctor doctor;

    printf("Enter doctor name: ");
    scanf(" %[^\n]", doctor.name);
    printf("Enter doctor CRM: ");
    scanf("%d", &doctor.crm);
    printf("Enter doctor employee code: ");
    scanf("%d", &doctor.codEmployee);

    fwrite(&doctor, sizeof(Doctor), 1, fileD);
    fclose(fileD);
    printf("Doctor record created successfully.\n");
}

void createNurseRecord()
{
    FILE *fileN = fopen("nurse.dat", "ab");
    Nurse nurse;

    printf("Enter nurse name: ");
    scanf(" %[^\n]", nurse.nome);
    printf("Enter nurse employee code: ");
    scanf("%d", &nurse.codEmployee);

    fwrite(&nurse, sizeof(Nurse), 1, fileN);
    fclose(fileN);
    printf("Nurse record created successfully.\n");
}

void CheckFile()
{
    FILE *fileD;
    FILE *fileN;
    FILE *fileP;
    fileD = fopen("doctor.dat", "rb");
    fileN = fopen("nurse.dat", "rb");
    fileP = fopen("patient.dat", "rb");

    if (fileD == NULL && fileN == NULL && fileP == NULL)
    {
        printf("Creating File....\n");
        Sleep(3000);
        system("cls");
        fileD = fopen("doctor.dat", "wb");
        fileN = fopen("nurse.dat", "wb");
        fileP = fopen("patient.dat", "wb");
    }
    fclose(fileD);
    fclose(fileN);
    fclose(fileP);

    fileD = fopen("doctor.dat", "rb");
    fileN = fopen("nurse.dat", "rb");

    fseek(fileD, 0, SEEK_END);
    fseek(fileN, 0, SEEK_END);

    if (ftell(fileD) == 0)
    {
        printf("No doctors found. Please create a doctor record.\n");
        createDoctorRecord();
    }

    if (ftell(fileN) == 0)
    {
        printf("No nurses found. Please create a nurse record.\n");
        createNurseRecord();
    }

    fclose(fileD);
    fclose(fileN);

    printf("Loading File....\n");
    Sleep(3000);
    system("cls");
}

int searchEmployee(int codEmployee, char *type)
{
    FILE *fileD = fopen("doctor.dat", "rb");
    FILE *fileN = fopen("nurse.dat", "rb");
    Doctor doctor;
    Nurse nurse;

    while (fread(&doctor, sizeof(Doctor), 1, fileD) == 1)
    {
        if (doctor.codEmployee == codEmployee)
        {
            strcpy(type, "doctor");
            fclose(fileD);
            fclose(fileN);
            return 1;
        }
    }

    while (fread(&nurse, sizeof(Nurse), 1, fileN) == 1)
    {
        if (nurse.codEmployee == codEmployee)
        {
            strcpy(type, "nurse");
            fclose(fileD);
            fclose(fileN);
            return 1;
        }
    }

    fclose(fileD);
    fclose(fileN);
    return 0;
}

void createPatientRecord(int nurseCodEmployee)
{
    FILE *fileP = fopen("patient.dat", "ab");
    Patient patient;

    printf("Enter patient name: ");
    scanf(" %[^\n]", patient.name);
    printf("Enter patient symptom: ");
    scanf(" %[^\n]", patient.sympton);
    printf("Enter patient address: ");
    scanf(" %[^\n]", patient.address);
    printf("Enter patient medications: ");
    scanf(" %[^\n]", patient.medicamnetos);
    printf("Enter patient phone: ");
    scanf("%d", &patient.Fone);
    patient.codEmployee = nurseCodEmployee;
    patient.discharged = false;

    fwrite(&patient, sizeof(Patient), 1, fileP);
    fclose(fileP);
    printf("Patient record created successfully.\n");
}

void viewPatientRecords()
{
    FILE *fileP = fopen("patient.dat", "rb");
    Patient patient;

    while (fread(&patient, sizeof(Patient), 1, fileP) == 1)
    {
        printf("Name: %s\n", patient.name);
        printf("Symptom: %s\n", patient.sympton);
        printf("Address: %s\n", patient.address);
        printf("Medications: %s\n", patient.medicamnetos);
        printf("Phone: %d\n", patient.Fone);
        printf("Discharged: %s\n", patient.discharged ? "Yes" : "No");
        printf("-----------------------------\n");
    }

    fclose(fileP);
}

void dischargePatient()
{
    FILE *fileP = fopen("patient.dat", "rb+");
    Patient patient;
    char name[100];
    int found = 0;

    printf("Enter the name of the patient to discharge: ");
    scanf(" %[^\n]", name);

    while (fread(&patient, sizeof(Patient), 1, fileP) == 1)
    {
        if (strcmp(patient.name, name) == 0)
        {
            patient.discharged = true;
            fseek(fileP, -sizeof(Patient), SEEK_CUR);
            fwrite(&patient, sizeof(Patient), 1, fileP);
            found = 1;
            break;
        }
    }

    fclose(fileP);

    if (found)
    {
        printf("Patient discharged successfully.\n");
    }
    else
    {
        printf("Patient not found.\n");
    }
}

void login()
{
    int choice;
    int codEmployee;
    char type[10];

    printf("Select your role:\n");
    printf("1. Doctor\n");
    printf("2. Nurse\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    if (choice == 1)
    {
        strcpy(type, "doctor");
    }
    else if (choice == 2)
    {
        strcpy(type, "nurse");
    }
    else
    {
        printf("Invalid choice.\n");
        return;
    }

    do
    {
        printf("Enter the employee code: ");
        scanf("%d", &codEmployee);
        if (!searchEmployee(codEmployee, type))
        {
            if (strcmp(type, "doctor") == 0)
            {
                printf("Doctor not found. Please create a doctor record.\n");
                createDoctorRecord();
            }
            else
            {
                printf("Invalid employee code. Please try again.\n");
            }
        }
    } while (!searchEmployee(codEmployee, type));

    if (strcmp(type, "nurse") == 0)
    {
        printf("Logged in as Nurse.\n");
        createPatientRecord(codEmployee);
    }
    else if (strcmp(type, "doctor") == 0)
    {
        printf("Logged in as Doctor.\n");
        viewPatientRecords();
        dischargePatient();
    }
}

int main()
{
    CheckFile();
    login();
    return 0;
}
