#include <tchar.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

void classer_livre_par_faculte();
void gerer_pret_livre_option();
void supprimer_un_livre();
void ajouter_livre_par_faculte();
void modifier_info_livre();
void classer_livre_ordre_alphabetique();

TCHAR szClassName[ ] = _T("GESTION DES LIVRES");

int WINAPI WinMain (HINSTANCE hThisInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpszArgument,
                     int nCmdShow)
{
    HWND hwnd;
    MSG messages;
    WNDCLASSEX wincl;

    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;
    wincl.style = CS_DBLCLKS;
    wincl.cbSize = sizeof (WNDCLASSEX);

    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;
    wincl.cbClsExtra = 0;
    wincl.cbWndExtra = 0;
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

    if (!RegisterClassEx (&wincl))
        return 0;

    hwnd = CreateWindowEx (
           0,
           szClassName,
           _T("Haiti Développeur Windows App\n"),
           WS_OVERLAPPEDWINDOW,
           CW_USEDEFAULT,
           CW_USEDEFAULT,
           1500,
           800,
           HWND_DESKTOP,
           NULL,
           hThisInstance,
           NULL
           );
   HWND boutton = CreateWindow (TEXT ("static"),
   ":==========>>><<< G E S T I O N   D E S   L I V R E S   D A N S   U N   B I B B L I O T H È Q U E >>><<<==========:",
                                 WS_CHILD | WS_VISIBLE | SS_CENTER,
                                 150,60,
                                 1000,40,
                                 hwnd,
                                 (HMENU)0,
                                 NULL,
                                 NULL) ;
   HWND boutton1 = CreateWindow (TEXT ("button"),
                                 "Classer les livres par faculté ou par option",
                                 WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                                 150,140,
                                 1000,40,
                                 hwnd,
                                 (HMENU)1,
                                 NULL,
                                 NULL) ;
   HWND boutton2 = CreateWindow (TEXT ("button"),
                                 "Gerer le pret d'un livre par option",
                                 WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                                 150,180,
                                 1000,40,
                                 hwnd,
                                 (HMENU)2,
                                 NULL,
                                 NULL) ;
   HWND boutton3 = CreateWindow (TEXT ("button"),
                                 "Supprimmer un livre",
                                 WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                                 150,220,
                                 1000,40,
                                 hwnd,
                                 (HMENU)3,
                                 NULL,
                                 NULL) ;
   HWND boutton4 = CreateWindow (TEXT ("button"),
                                 "Ajouter des livres par options ou faculté",
                                 WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                                 150,260,
                                 1000,40,
                                 hwnd,
                                 (HMENU)4,
                                 NULL,
                                 NULL) ;
   HWND boutton5 = CreateWindow (TEXT ("button"),
                                 "Modifier les infos concernant un livre",
                                 WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                                 150,300,
                                 1000,40,
                                 hwnd,
                                 (HMENU)5,
                                 NULL,
                                 NULL) ;
   HWND boutton6 = CreateWindow (TEXT ("button"),
                                 "Classer les livres par odre alphabetiques",
                                 WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                                 150,340,
                                 1000,40,
                                 hwnd,
                                 (HMENU)6,
                                 NULL,
                                 NULL) ;

    if(!hwnd)
	return FALSE;
    ShowWindow (hwnd, nCmdShow);
    UpdateWindow(hwnd);

    while (GetMessage (&messages, NULL, 0, 0))
    {
        TranslateMessage(&messages);
        DispatchMessage(&messages);
    }

    return messages.wParam;
}



LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)                  /* handle the messages */
    {
        case WM_RBUTTONUP:
             {
             case WM_COMMAND:
                 switch(LOWORD(wParam))
                {
                    case 1: MessageBeep(MB_OK);
                            DestroyWindow(hwnd);
                            classer_livre_par_faculte();
                            //DestroyWindow(hwnd);
                        break;
                    case 2: MessageBeep(MB_OK);
                            DestroyWindow(hwnd);
                            gerer_pret_livre_option();
                        break;
                    case 3: MessageBeep(MB_OK);
                            DestroyWindow(hwnd);
                            supprimer_un_livre();
                        break;
                    case 4: MessageBeep(MB_OK);
                            DestroyWindow(hwnd);
                            ajouter_livre_par_faculte();
                        break;
                    case 5: MessageBeep(MB_OK);
                            DestroyWindow(hwnd);
                            modifier_info_livre();
                        break;
                    case 6: MessageBeep(MB_OK);
                            DestroyWindow(hwnd);
                            classer_livre_ordre_alphabetique();
                        break;
                }
            }
        case WM_CREATE:
            break;
        case WM_DESTROY:
            PostQuitMessage (0);  
                break;
        default:           
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}

//Donnee pour les fichiers
typedef struct
{
  char Titre[50];
  char Auteur[50];
  char ISBN[50];
  char Faculte[50];
}Livre;
Livre liv;
//Livre z;
typedef struct
{
	char nom[50];
	char prenom[50];
	char code[20];
	char fac[50];
}Personne;
Personne pers;

typedef struct
{
	int jours[10];
	int mois[10];
	int annee[10];
}Date;
Date dat;

char filename[]=("livre.txt");
char filename1[]=("livre1.txt");
char filename2[]=("preterLiv.txt");
int i=0, j, test=0;

//Debut classer livre par faculté ou option
void classer_livre_par_faculte()
{
	FILE *fichier, *fichier1;
    char facLiv[50],titLiv[50];
    char choix1;
    int trouver=0;
    system("cls");
    fichier = fopen("livre.txt","r");
    printf("\n\t\tEntrer la facult%c ou option du livre que vous voulez Classer: ",130);
    scanf("%s",facLiv);

    do
	{
	  if(fread(&liv, sizeof(Livre),1, fichier) !=NULL)
           if (strcmp(facLiv, liv.Faculte)==0)
           {
               trouver=1;
               printf("\n\t\t\t\t\tTitre    : %s",liv.Titre);
               printf("\n\t\t\t\t\tAuteur   : %s",liv.Auteur);
               printf("\n\t\t\t\t\tISBN     : %s",liv.ISBN);
               printf("\n\t\t\t\t\tFacult%c  : %s\n",130,liv.Faculte);
               i++;
           }

    }while (!feof(fichier));
    fclose(fichier);
    
    if(!trouver)
    {
        printf("\n\t\t\t\tLe nom de la facult%c est incorrect",130);
        getch();
        classer_livre_par_faculte();
	}
}
//Fin Donnée classer livre par faculté

void gerer_pret_livre_option()
{
	FILE *fichier, *fichier1, *fichier2;
    char nomLiv[50], titLiv[50], choix, nomResp[50];
    int trouver=0,jrs,mois,ann;
    system("cls");
    printf("\n\t\tEntrer le Titre du livre que vous voulez emprunter: ");
    gets(nomLiv);
    fichier = fopen("livre.txt","r");
    fichier1 = fopen("livre1.txt","w");
    do
	{
      if(fread(&liv, sizeof(liv),1, fichier) !=NULL)
        if (strcmp(nomLiv, liv.Titre)==0)
        {
                trouver=1;
    	        system("cls");
                printf("\n\n\t\t\t\t=====>< Information du Livre ><=====");
                printf("\n\t\t\t\t\tTitre: %s",liv.Titre);
                printf("\n\t\t\t\t\tAuteur: %s",liv.Auteur);
                printf("\n\t\t\t\t\tISBN: %s",liv.ISBN);
                printf("\n\t\t\t\t\tFacult%c: %s\n",130,liv.Faculte);
                printf("\t\t\t\tVoulez-vous emprunter ce livre (O/N)\n");
                choix=getch();
            if(choix=='o'||choix=='O')
            {       
                    system("cls");
                	printf("\n\t\t\t    Entrer le Nom de l'emprunteur: ");
                	gets(pers.nom);
                	printf("\t\t\t    Entrer le Pr%cnom de l'emprunteur: ",130);
                	gets(pers.prenom);
                	printf("\t\t\t    Entrer le Code de l'emprunteur: ");
                	gets(pers.code);
                	printf("\t\t\t    Entrer la Facult%c de l'emprunteur: ",130);
                	gets(pers.fac);
                	printf("\t\t\t    Entrer la Signature du responsable d'emprunt: ");
                	gets(nomResp);
                 	printf("\t\t--><  Entrer la date de l'emprunt ( format: jj/mm/aaaa )><--\n");
                 	do{
                 		printf("\t\t\t\t\t   Jours: ");
                 	    scanf("%d",&dat.jours[10]);
					 }while(dat.jours[10]>31||dat.jours[10]<1);
                 	do{
                 		printf("\t\t\t\t\t   Mois: ");
                 	    scanf("%d",&dat.mois[10]);
					 }while(dat.mois[10]>12||dat.mois[10]<1);
                 	do{
                 		printf("\t\t\t\t\t   Ann%ce: ",130);
                 	    scanf("%d",&dat.annee[10]);
					 }while(dat.annee[10]<2020);
                        jrs=dat.jours[10]+7;
                 	    mois=dat.mois[10];
                 	    ann=dat.annee[10];
                 	 system("cls");
                 	 printf("\n\t\t\t     :::=========>< FICHE D'EMPRUNT ><=========:::\n");
                 	 printf("\n\t\t\t     =====>< Information du Livre emprunt%c ><=====",130);
                     printf("\n\t\t\t\t\tTitre: %s",liv.Titre);
                     printf("\n\t\t\t\t\tAuteur: %s",liv.Auteur);
                     printf("\n\t\t\t\t\tISBN: %s",liv.ISBN);
                     printf("\n\t\t\t\t\tFacult%c: %s",130,liv.Faculte);
					 printf("\n\n\t\t\t      =====>< Information de l'emprunteur ><=====");
                     printf("\n\t\t\t\t       Nom de l'emprunteur: %s",pers.nom);
                     printf("\n\t\t\t\t       Pr%cnom de l'emprunteur: %s",130,pers.prenom);
                     printf("\n\t\t\t\t       Code de l'emprunteur: %s",pers.code);
                     printf("\n\t\t\t\t       Facult%c de l'emprunteur: %s",130,pers.fac);
					 printf("\n\t\t\t\t       Date d'emprunt: %d / %d / %d",dat.jours[10],dat.mois[10],dat.annee[10]);
					 printf("\n\t\t\t\t       Date remise: %d / %d / %d",jrs,mois,ann);
					 printf("\n\t\t\t     Signature du responsable d'emprunt: %s",nomResp);
                 	 do
                 	 {
                 	     printf("\n\n\t\t\t Etes-vous vraiment impatient d'emprunter ce livre (O/N)");
                 	     choix=getch();
					 }while((choix!='n')&&(choix!='N') && (choix!='o')&&(choix!='O'));

						 if ((choix=='n')  || (choix=='N'))
                         fwrite(&liv, sizeof(liv),1, fichier1);

            }else if(choix=='n'||choix=='N')
				{
					system("cls");
					printf("\n\n\n\t\t\t\t\t\tDesol%c\n\n\n",130);
					exit(0);
				}
        }
        else
        {
            fwrite(&liv, sizeof(liv),1, fichier1);
                     //printf("Livre a %ct%c supprimer avec succ%cs dans le fichier \"%s\" ",130,130,138,filename);
        }

					 /*if(choix=='o'||choix=='O')
                 	{
                 		 //fichier2=fopen("preterLiv.txt","a");
						 system("cls");
                         printf("=>< Information du livre emprunte ><=\nTitre  livre: %s\nAuteur livre: %s\nISBN livre: %s\nFaculte livre: %s\n==>< Information de l'emprunteur ><==\nNom: %s\nPrenom: %s\nCode: %s\nFaculte: %s\nDate d'Emprunt: %d/ %d/ %d\nDate remise: %d/ %d/ %d\nSignature Resp: %s", liv.Titre, liv.Auteur, liv.ISBN, liv.Faculte, pers.nom, pers.prenom, pers.code, pers.fac, dat.jours[10], dat.mois[10], dat.annee[10], jrs, mois, ann, nomResp);

					     //fclose(fichier2);
					 }
					 else if(choix=='n'||choix=='N')
				     {
				     	 system("cls");
				         printf("Desol%c",130);
				      	 exit(0);
					 }*/
    }while (!feof(fichier));
    fclose(fichier);
    fclose(fichier1);
    remove("livre.txt");
    rename("livre1.txt","livre.txt");

    if (!trouver)
	{
            printf("\n\t\t\t\t\tLivre introuvable");
            getch();
            gerer_pret_livre_option();
    }
}

//Debut Donnée Supprimer un livre
void supprimer_un_livre()
{
    FILE *fichier, *fichier1;
    char nomLiv[50], titLiv[5];
    char choix;0;
    int trouver=0;
    system("cls");
    printf("\n\t\t   Entrer le Titre du livre que vous voulez Supprimer: ");
    gets(nomLiv);
    fichier = fopen("livre.txt","r");
    fichier1 = fopen("livre1.txt","w");
    do
	{
      if(fread(&liv, sizeof(liv),1, fichier) !=NULL)
           if (strcmp(nomLiv, liv.Titre)==0)
           {
                trouver=1;
    	        system("cls");
                printf("\n\n\t\t\t\t=====>< Information du Livre ><=====");
                printf("\n\t\t\t\t\tTitre: %s",liv.Titre);
                printf("\n\t\t\t\t\tAuteur: %s",liv.Auteur);
                printf("\n\t\t\t\t\tISBN: %s",liv.ISBN);
                printf("\n\t\t\t\t\tFacult%c: %s\n",130,liv.Faculte);
                do
			    {
                     printf("\n\t\t\t    Voulez-vous vraiment supprimer le livre(O/N) ?\n");
                     choix=getch();
                } while ((choix!='n')&&(choix!='N') && (choix!='o')&&(choix!='O'));
                
                if ((choix=='n')  || (choix=='N'))
                {
                	fwrite(&liv, sizeof(liv),1, fichier1);
				}          
           }
           else
           {
                fwrite(&liv, sizeof(liv),1, fichier1);
                //printf("Livre a %ct%c supprimer avec succ%cs dans le fichier \"%s\" ",130,130,138,filename);
           }

    }while (!feof(fichier));
    fclose(fichier);
    fclose(fichier1);
    remove("livre.txt");
    rename("livre1.txt","livre.txt");

    if (!trouver)
	{
            printf("\n\t\t\t\t\tLivre introuvable");
            getch();
            supprimer_un_livre();
    }
}
//Fin Donnée Supprimer un livre


//Debut Donnée Ajouter un livre par faculté
void ajouter_livre_par_faculte()
{
	char choix;
    FILE *fichier;
    fichier = fopen("livre.txt","a");
    do
	{
         system("cls");
         printf("\n\n\n\n\n\t\t\t\tEntrer le Titre du livre: ");
         gets(liv.Titre);
         printf("\t\t\t\tEntrer l'Auteur du livre: ");
         gets(liv.Auteur);
         printf("\t\t\t\tEntrer l'ISBN: ");
         gets(liv.ISBN);
         printf("\t\t\t\tEntrer l'Option du livre: ");
         gets(liv.Faculte);
         fwrite(&liv, sizeof(liv),1, fichier);
         i++;
         printf("\t\t\tLivre enregistrer avec succ%cs dans le fichier \"%s\"",138,filename);
         printf("\n\n\t\t\t\t   Voulez vous continuer(O/N) ?");
         choix=getch();
         //fflush(stdin);
         if(choix=='n'||choix=='N')
         exit(0);
    }  while ((choix!='n'||choix!='N'));
    fclose(fichier);

}
//Fin Donnée Ajouter un livre par faculté

void modifier_info_livre()
{
	FILE *fichier, *fichier1;
    char nomLiv[50],titLiv[50];
    char choix;
    int trouver=0;
    system("cls");
    printf("\n\t\t   Entrer le Titre du livre que vous voulez Modifier: ");
    gets(nomLiv);
    fichier = fopen("livre.txt","r");
    fichier1 = fopen("livre1.txt","w");
    while(trouver==0 && !feof(fichier))
    {
    	if (strcmp(nomLiv, liv.Titre)==0)
    	{
	        trouver=1;
    	    system("cls");
            printf("\n\n\t\t\t\t=====>< Information du Livre ><=====");
            printf("\n\t\t\t\t\tTitre: %s",liv.Titre);
            printf("\n\t\t\t\t\tAuteur: %s",liv.Auteur);
            printf("\n\t\t\t\t\tISBN: %s",liv.ISBN);
            printf("\n\t\t\t\t\tFacult%c: %s\n",130,liv.Faculte);
            i++;
        }
        else
    	{
    	    fwrite(&liv, sizeof(liv),1, fichier1);
    	    fread(&liv, sizeof(liv),1, fichier);
		}
    }
    if(trouver==1)
    {
            printf("\n\t\t\t    Voulez-vous vraiment modifier ce livre (O/N)\n");
    	    choix=getch();
    	    if(choix=='O'||choix=='o')
    	    {
    	        printf("\n\t\t\t     =====>< Nouvel information du livre ><=====\n");
		        printf("\t\t\t\t   Nouveau Titre: ");
		        gets(liv.Titre);
		        printf("\t\t\t\t   Nouveau Auteur: ");
		        gets(liv.Auteur);
		        printf("\t\t\t\t   Nouveau ISBN: ");
		        gets(liv.ISBN);
		        printf("\t\t\t\t   Nouveau Facult%c: ",130);
		        gets(liv.Faculte);
                printf("\t\t\tModification r%cussi avec succ%cs dans le fichier \"%s\"",130,138,filename);
    	        while(!feof(fichier))
    	        {
    		        fwrite(&liv, sizeof(liv),1, fichier1);
    	            fread(&liv, sizeof(liv),1, fichier);
		        }
		    }
		    else if(choix=='n'||choix=='N')
		    {
			   system("cls");
			   printf("\n\n\n\t\t\t\t\t\tDesol%c",130);
			   exit(0);
		    }

    }
    fclose(fichier);
    fclose(fichier1);
    remove("livre.txt");
    rename("livre1.txt","livre.txt");

    if (!trouver)
	{
            printf("\n\t\t\t\tLivre introuvable");
            getchar();
            modifier_info_livre();
    }

}

void classer_livre_ordre_alphabetique()
{
	FILE *fichier;
    char nomLiv[50],titLiv[50];
    char choix;
    int trouver=0;
    fichier = fopen("livre.txt","r");
    

    fclose(fichier);
}

