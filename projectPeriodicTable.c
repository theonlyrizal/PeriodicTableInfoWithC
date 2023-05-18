

// Source code Copyright - Salman Bari Rizal//


#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

typedef struct atom{
    int atmNum;
    int atmPeriod;
    int atmGroup;
    char atmSym[3];
    char atmName[15];
    float atmMass;
    char atmFact[100];
}atom;

void tableScreen();
void readData(atom*, FILE*);
void atomSearch(atom*);
void seachByNum(atom*);
void searchBySym(atom*);
void searchByName(atom*);
void searchByPG(atom*);
void editFact(atom*);
//void gotoxy(int, int);
void textcolor(int);
void fExit();




int main()
{
    int choice;
    tableScreen();
    atom molecule[118];
    FILE *atomData;
    atomData = fopen("atomData.txt", "r");
    if(atomData == NULL)
    {
        printf("\n/.../Periodic Table Data not existant\n\n");
    }
    else
    {
        printf("\n/.../Periodic Table Data found/updated\n\n");
        textcolor(2);
        printf("\n\n  ***Main Menu***\n\n");
        textcolor(7);
        readData(molecule, atomData);
        printf("  [1] Go away and come bach here again\n");
        printf("  [2] Search log (Google is Illuminati)\n");
        printf("  [3] Edit Data (Fact Only)\n");
        printf("  [0] Exit Program (You are gonna regret this) \n\n");
        printf("\n  Take Action [number] : ");
        do
        {
            scanf("%d", &choice);
            switch (choice)
            {
            case 0:
            fclose(atomData);
                fExit();
                fclose(atomData);
                getch();
                return 0;
                break;
            case 1:
                return main();
                break;
            case 2:
                atomSearch(molecule);
                break;
            case 3:
                editFact(molecule);
                break;
            }
        } while (1);
    }
    fclose(atomData);
}


void readData(atom* molecule, FILE* atomData) //Reads data from the atomData.txt file
{
    int i;
    for(i=0; i<118; i++)
    {
        fscanf(atomData, "%d %d %d %s %s %f %99[^\n]",
        &(molecule+i)->atmNum, 
        &(molecule+i)->atmPeriod,
        &(molecule+i)->atmGroup,
        (molecule+i)->atmSym,
        (molecule+i)->atmName,
        &(molecule+i)->atmMass,
        (molecule+i)->atmFact);
    }
}

void atomSearch(atom* molecule)  //Menu to search for Atom informations
{
    tableScreen();
    int choice;
    textcolor(2);
    printf("\n\n***Search Menu***\n\n");
    textcolor(7);
    printf("\n\n   [1] Search by Atomic Number\n");
    printf("   [2] Search by Atomic Symbol\n");
    printf("   [3] Search by Name\n");
    printf("   [4] Search by Period and Group\n");
    printf("   [5] Back to Main Menu");
    printf("\n\n  Enter choice : ");
    do
    {
        scanf("%d", &choice);
        if(choice>=1 && choice<=5)
        {
            switch (choice)
            {
            case 1:
                seachByNum(molecule);
                break;
            case 2:
                searchBySym(molecule);
                break;
            case 3:
                searchByName(molecule);
                break;
            case 4:
                searchByPG(molecule);
                break;
            case 5:
                main();
                break;
            }
        }
    } while (1);
}

void seachByNum(atom* molecule) //Searches the Atom by Atomic Number
{
    char decision;
    do
    {
        int num, i;
        tableScreen();
        textcolor(2);
        printf("\n\n***Search by Atomic Number***\n\n");
        textcolor(7);
        printf("\n\n  Enter Atomic Number : ");
        scanf("%d", &num);
        if (num<1 || num >118)
        {
            printf("\n  Enter a valid Number,");
        }
        else
        {
            for(i=0; i<118; i++)
            {
                if (num==(molecule[i].atmNum))
                {
                    printf("\n  Name : %s \n",molecule[i].atmName);
                    printf("  Atomic Number : %d \n",molecule[i].atmNum);
                    printf("  Period In PT : %d \n",molecule[i].atmPeriod);
                    printf("  Group in PT : %d \n",molecule[i].atmGroup);
                    printf("  Atomic Symbol : %s \n",molecule[i].atmSym);
                    printf("  Atomic Mass : %f \n",molecule[i].atmMass);
                    printf("  Fact : %s \n\n",molecule[i].atmFact);
                }
            }
        }
    printf("  Seach again?(y/n)");
    scanf(" %c", &decision);
    } while(decision=='y' || decision=='Y');
    return atomSearch(molecule);
}

void searchBySym(atom* molecule)     //Searches the Atom by Atomic Symbol
{
    char decision;
    do
    {
    char sym[3];
    int i, flag=0;
    tableScreen();
    textcolor(2);
    printf("\n\n***Search by Symbol***\n\n");
    textcolor(7);
    printf("\n\n  Enter Symbol (Case Sensitive): ");
    while (getchar() != '\n');    
    fgets(sym, 3, stdin);
    for(i=0; i<118; i++)
    {
        if (!strcmp(sym, (molecule+i)->atmSym))
        {
            printf("\n  Name : %s \n",molecule[i].atmName);
            printf("  Atomic Number : %d \n",molecule[i].atmNum);
            printf("  Period In PT : %d \n",molecule[i].atmPeriod);
            printf("  Group in PT : %d \n",molecule[i].atmGroup);
            printf("  Atomic Symbol : %s \n",molecule[i].atmSym);
            printf("  Atomic Mass : %f \n",molecule[i].atmMass);
            printf("  Fact : %s \n\n",molecule[i].atmFact);
            flag=1;
        }
    }
    if(flag!=1)
    printf("No such Atom with the symbol '%s' (Make sure of First Capital letter) ", sym);
    printf("  Seach again?(y/n)");
    scanf(" %c", &decision);
    } while(decision=='y' || decision=='Y');
    return atomSearch(molecule);
}

void searchByName(atom* molecule)  //Searches the Atom by Atomic Name, HUGE REDFLAG!! cz its case and spelling sensitive
{
    char decision;
    do
    {
    char name[15];
    int i, flag=0;
    tableScreen();
    textcolor(2);
    printf("\n\n***Search by Atom Name***\n\n");
    textcolor(7);
    printf("\n\n  Enter Atom Name (Beware of spelling and Case) : ");
    while (getchar() != '\n');    
    fgets(name, 15, stdin);
    name[strcspn(name, "\n")] = '\0';
    for(i=0; i<118; i++)
    {
        if (!strcmp(name, (molecule+i)->atmName))
        {
            printf("\n  Name : %s \n",molecule[i].atmName);
            printf("  Atomic Number : %d \n",molecule[i].atmNum);
            printf("  Period In PT : %d \n",molecule[i].atmPeriod);
            printf("  Group in PT : %d \n",molecule[i].atmGroup);
            printf("  Atomic Symbol : %s \n",molecule[i].atmSym);
            printf("  Atomic Mass : %f \n",molecule[i].atmMass);
            printf("  Fact : %s \n\n",molecule[i].atmFact);
            flag=1;
        }
    }
    if(flag!=1)
    printf("No such Atom with the symbol '%s' (Make sure of correct spelling and First Capital letter)", name);
    printf("  Seach again?(y/n)");
    scanf(" %c", &decision);
    } while(decision=='y' || decision=='Y');
    return atomSearch(molecule);
}

void searchByPG(atom* molecule)  ////Searches the Atom by Period and Group position in the Periodic table
{
    char decision;
    do
    {
        int per, grp, i, j, flag=0;
        tableScreen();
        textcolor(2);
        printf("\n\n***Search by Period and Group***\n\n");
        textcolor(7);
        printf("\n\n  Enter Period Number : ");
        scanf("%d", &per);
        printf("\n\n  Enter Group Number : ");
        scanf("%d", &grp);
        if ((per<1 || per >7) && (grp<1 || grp>18))
        {
            printf("\n  Enter a valid Number,");
        }
        else
        {
            if(per==6 && grp==3)
            {
                printf("\n   It is the Lanthanide Series. Atomic Number 57 to 71 consist in this series, they are");
                for(i=0;i<5;i++)
                {
                    printf(".");
                    sleep(1);
                }
            }
            if(per==7 && grp==3)
            {
                printf("\n   It is the Actinide Series. Atomic Number 89 to 103 consist in this series, they are");
                for(i=0;i<5;i++)
                {
                    printf(".");
                    sleep(1);
                }
            }
            for(i=0; i<118;i++)
            {
                if (per==(molecule[i].atmPeriod) && grp==(molecule[i].atmGroup))
                {
                    printf("\n  Name : %s \n",molecule[i].atmName);
                    printf("  Atomic Number : %d \n",molecule[i].atmNum);
                    printf("  Period In PT : %d \n",molecule[i].atmPeriod);
                    printf("  Group in PT : %d \n",molecule[i].atmGroup);
                    printf("  Atomic Symbol : %s \n",molecule[i].atmSym);
                    printf("  Atomic Mass : %f \n",molecule[i].atmMass);
                    printf("  Fact : %s \n\n",molecule[i].atmFact);
                    flag=1;
                    sleep(1);
                }
            }
            if (flag==0)
            {
                printf("No Atom present in Period %d and Group %d", per, grp);
            }
            
        }
    printf("  Seach again?(y/n)");
    scanf(" %c", &decision);
    } while(decision=='y' || decision=='Y');
    atomSearch(molecule);
}

void editFact(atom* molecule)  //Edits the fact ir string of the number corresponding Atom (it's not a fact anymore)
{
    char decision;
    do
    {
        int atom, flag=0;
        tableScreen();
        textcolor(2);
        printf("\n\n***Fact Edit***\n\n");
        textcolor(7);
        printf("\n\n  Enter the Atomic Number of the Fact you want to edit : ");
        scanf("%d", &atom);
        if ((atom<1 || atom>118))
        {
            printf("\n  Enter a valid Number,");
        }
        else
        {
            while (getchar() != '\n'); 
            printf("\n   New fact of %s id - %s.\n   Provide New fact - ",molecule[atom-1].atmName, molecule[atom-1].atmFact );
            fgets(molecule[atom-1].atmFact, 99, stdin);
            printf("\n  New fact of %s id - %s.\n",molecule[atom-1].atmName, molecule[atom-1].atmFact );textcolor(6);
            printf("  Sad thing is, it may not be a FACT any more   :'(\n\n");textcolor(7);
        }
    printf("  Edit another molecule fact?(y/n)");
    scanf(" %c", &decision);
    } while(decision=='y' || decision=='Y');
    main();


}

void tableScreen() //A fancy ASCII style periodic table to show-off my noob coding skill
{
    system("cls");

    textcolor(2);
    printf("\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\BY - SALMAN BARI RIZAL\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\");
    printf("\n\n\n\n\n                                              Welcome to Modern Periodic Table\n");
    textcolor(6);
    printf("                       <----------------------------------------------------------------------->\n");
    printf("                       | 1 |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   | 2 |\n");
    printf("                       | H |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   | He|\n");
    printf("                       |-----------------------------------------------------------------------|\n");
    printf("                       | 3 | 4 |   |   |   |   |   |   |   |   |   |   | 5 | 6 | 7 | 8 | 9 | 10|\n");
    printf("                       | Li| Be|   |   |   |   |   |   |   |   |   |   | B | C | N | O | F | Ne|\n");
    printf("                       |------------------------------------------------------------------------\n");
    printf("                       | 11| 12|   |   |   |   |   |   |   |   |   |   | 13| 14| 15| 16| 17| 18|\n");
    printf("                       | Na| Mg|   |   |   |   |   |   |   |   |   |   | Al| Si| P | S | Cl| Ar|\n");
    printf("                       |-----------------------------------------------------------------------|\n");
    printf("                       | 19| 20| 21| 22| 23| 24| 25| 26| 27| 28| 29| 30| 31| 32| 33| 34| 35| 36|\n");
    printf("                       | K | Ca| Sc| Ti| V | Cr| Mn| Fe| Co| Ni| Cu| Zn| Ga| Ge| As| Se| Br| He|\n");
    printf("                       |-----------------------------------------------------------------------|\n");
    printf("                       | 37| 38| 39| 40| 41| 42| 43| 44| 45| 46| 47| 48| 49| 50| 51| 52| 53| 54|\n");
    printf("                       | Rb| Sr| Y | Zr| Nb| Mo| Tc| Ru| Rh| Pd| Ag| Cd| In| Sn| Sb| Te| I | Xe|\n");
    printf("                       |-----------------------------------------------------------------------|\n");
    printf("                       | 55| 56| 71| 72| 73| 74| 75| 76| 77| 78| 79| 80| 81| 82| 83| 84| 85| 86|\n");
    printf("                       | Cs| Ba|*Lu| Hf| Ta| W | Re| Os| Ir| Pt| Au| Hg| Ti| Pb| Bi| Po| At| Rn|\n");
    printf("                       |-----------------------------------------------------------------------|\n");
    printf("                       | 87| 88|103|104|105|106|107|108|109|110|111|112|113|114|115|116|117|118|\n");
    printf("                       | Fr| Ra|^Lr| Rf| Db| Sg| Bh| Hs| Mt| Ds| Rg| Cn| Nh| Fl| Mc| Lv| Ts| Og|\n");
    printf("                       |=======================================================================|\n");
    printf("                       |   |   |*57| 58| 59| 60| 61| 62| 63| 64| 65| 66| 67| 68| 69| 70|   |   |\n");
    printf("                       |   |   |*La| Ce| Pr| Nd| Pm| Sm| Eu| Gd| Tb| Dy| Ho| Er| Tm| Yb|   |   |\n");
    printf("                       |-----------------------------------------------------------------------|\n");
    printf("                       |   |   |^89| 90| 91| 92| 93| 94| 95| 96| 97| 98| 99|100|101|102|   |   |\n");
    printf("                       |   |   |^Ac| Th| Pa| U | Np| Pu| Am| Cm| Bk| Cf| Es| Fm| Md| No|   |   |\n");
    printf("                       <----------------------------------------------------------------------->\n");
    textcolor(7);

}

void fExit()          //Why not a Dramatic Extro?
{
    int r;
    char author[25]="Salman Bari Rizal  :)";
    system("cls");
    printf("\n\n\n\n\n");
    textcolor(2);

    printf("                 -----------     |       |       ^        \\       |       |       /\n");usleep(250000);
    printf("                      |          |       |       /\\       |\\      |       |      / \n");usleep(250000);
    printf("                      |          |       |      /  \\      | \\     |       |     /  \n");usleep(250000);
    printf("                      |          |-------|     /    \\     |  \\    |       |    /   \n");usleep(250000);
    printf("                      |          |       |    /------\\    |   \\   |       |   /\\  \n");usleep(250000);
    printf("                      |          |       |   /        \\   |    \\  |       |  /  \\ \n");usleep(250000);
    printf("                      |          |       |  /          \\  |     \\ |       | /    \\\n");usleep(250000);
    printf("\n\n");
    printf("                             \\       /     /--------\\    |         | \n");usleep(250000);
    printf("                              \\     /      |\\        |   |         | \n");usleep(250000);
    printf("                               \\   /       | \\       |   |         | \n");usleep(250000);
    printf("                                \\ /        |  \\      |   |         | \n");usleep(250000);
    printf("                                 |         |   \\     |   |         | \n");usleep(250000);
    printf("                                 |         |    \\    |   |         | \n");usleep(250000);
    printf("                                 |         |     \\   |   |         | \n");usleep(250000);
    printf("                                ---        \\______\\__/   \\________/ \n");usleep(250000);textcolor(7);
    printf("                                     from  ");textcolor(6);
    for(r=0;author[r]!='\0';r++)
    {
        printf("%c",author[r]);
        usleep(100000);
    }
    textcolor(7);
}

// void gotoxy(int x, int y)
// {
//     HANDLE coutput=GetStdHandle(STD_OUTPUT_HANDLE); 
//     COORD pos={x, y};
//     SetConsoleCursorPosition(coutput , pos);
// }

void textcolor(int color)
{
    HANDLE h = GetStdHandle ( STD_OUTPUT_HANDLE );
    SetConsoleTextAttribute (h, color);
}
// BYE :)