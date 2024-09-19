#include <stdio.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>

#define Max 15
#define WageDocter 15.000
#define WageNurse 2.500

struct Patient
{
    char name[100];
    char sympton[500];
    char address[100];
    char medicamnetos[500];
    int Fone;
    int codEmployee;
};

struct Nurse
{
    char nome[100];
    float wageNurse = WageNurse;
    int codEmployee;
    Patient ListPatient;
};

struct Doctor
{
    Nurse nurse[10];
    char name[100];
    int crm;
    int codEmployee;
    float wageDocter = WageDocter;
    Patient ListPatient[Max];
};

void CheckFile()
{
    FILE *fileD;
    FILE *fileN;
    FILE *fileP;
    fileD = fopen("docter.dat", "rb");
    fileN = fopen("nurse.dat", "rb");
    fileP = fopen("patient.dat", "rb");

    if (fileD == NULL && fileN == NULL && fileP == NULL)
    {
        printf("Creating File....");
        Sleep(3000);
        system("cls");
        fileD = fopen("docter.dat", "wb");
        fileN = fopen("nurse.dat", "wb");
        fileP = fopen("patient.dat", "wb");
    }
    fclose(fileD);
    fclose(fileN);
    fclose(fileP);
    printf("Loading File....");
    Sleep(3000);
    system("cls");
}

int voidVerificD(FILE *fileD)
{
    Doctor doctor;
    fseek(fileD, 0, SEEK_SET);
    while (fread(&doctor, sizeof(Doctor), 1, fileD) == 1)
    {
        if (doctor.codEmployee == 0)
        {
            return 0;
        }
    }
    return 1;
}

int voidVerificN(FILE *fileN)
{
    Nurse nurse;
    fseek(fileN, 0, SEEK_SET);
    while (fread(&nurse, sizeof(Nurse), 1, fileN) == 1)
    {
        if (nurse.codEmployee == 0)
        {
            return 0;
        }
    }
    return 1;
}

int searchEmployee(int codEmployee)
{
    FILE *fileD = fopen("docter.dat", "rb");
    FILE *fileN = fopen("nurse.dat", "rb");
    Doctor doctor;
    Nurse nurse;
    fseek(fileD, 0, SEEK_SET);
    fseek(fileN, 0, SEEK_SET);
    while (fread(&doctor, sizeof(Doctor), 1, fileD) == 1)
    {
        if (doctor.codEmployee == codEmployee)
        {
            fclose(fileD);
            fclose(fileN);
            return 1;
        }
    }
    while (fread(&nurse, sizeof(Nurse), 1, fileN) == 1)
    {
        if (nurse.codEmployee == codEmployee)
        {
            fclose(fileD);
            fclose(fileN);
            return 1;
        }
    }
    fclose(fileD);
    fclose(fileN);
    return 0;
    
    
    

}


void login()
{
    int codEmployee;
    do{
        printf("Enter the employee code: ");
        scanf("%d", &codEmployee);
    }while

    
}
int main()
{
    CheckFile();
    login();
}
