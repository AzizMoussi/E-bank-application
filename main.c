#include <stdio.h>
#include <stdlib.h>
#define Dinar_TO_EUR 0.29
#define Dinar_TO_USD 0.32
#define USD_TO_EUR 0.9
int choix,b,c,d,f,nb=0,n;
typedef struct operation {
    int id_compt;
    float montan;
    char typeoperation[20];
}operation;
typedef struct Date
{
    int Jour;
    int Mois;
    int annee;
}Date;

typedef struct Clients
{
    int id_client;
    char nom[30];
    char prenom[30];
    int num_telephone;
}Clients;
typedef struct compte_epargne
{
    int id_compte_epargne;
    float sold;
    struct Date dcompte;
}compte_epargne;
typedef struct Compte
{
    int id_compte;
    int id_client;
    float solde;
    struct Date d_compte;
}compte;
struct Clients tab_client[500];
struct Compte tabcomptes[500];
struct compte_epargne tabepargne[500];
void interface(){
    printf("   [0]-Gestion des clients\n");
    printf("   [1]-Gestion des comptes\n");
    printf("   [2]-Gestion des transaction\n");
    printf("   [3]-Gestion d'un compte d'epargne(avec des interets)\n");
    printf("   [4]-Convertisseur de devise\n");
    printf("   [5]-Ttransferer d'argent d'un compte a un autre \n");
    printf("   [6]-quitter l'application\n");
    printf("choisir un numero pour acceder au menu prefere\n ");
    scanf("%d",&choix);
}
void sous_interface(int a){
    switch(a){
    case 0 :
        printf("          1-ajouter un clients\n");
        printf("          2-modifier un clients\n");
        printf("          3-supprimer un clients\n");
        printf("          4-afficher la liste des clients\n");
        printf("          5-retourner a la menu principale\n");
        printf("          choisir un numero\n ");
        scanf("%d",&b);
        if (b < 0 || b > 5){
            printf(" Veuillez choisir 0, 1 , 2 , 3 , 4 ou 5\n");
        }
        gerer_client(b);
        break;

    case 1 :
        printf("          1-creer un compte\n");
        printf("          2-mettre a jour un compte\n");
        printf("          3-supprimer un compte\n");
        printf("          4-afficher les details d un compte\n");
        printf("          5-afficher tous les comptes\n");
        printf("          6-retourner a la menu principale\n");
        printf("          choisir un numéro\n ");
        scanf("%d",&c);
        if (c < 0 || c > 6){
            printf(" Veuillez choisir 0, 1 , 2 , 3 , 4,5 ou 6\n");
        }
        gerer_compte(c);
        break;

    case 2 :
        printf("          1-faire un versement\n");
        printf("          2-faire un retrait\n");
        printf("          3-afficher les compte apres operation\n");
        printf("          4-afficher les derniers transaction d' un compte\n");
        printf("          5-afficher toutes transaction de toutes les comptes\n");
        printf("          6-retourner a la menu principale\n");
        printf("          choisir un numéro\n ");
        scanf("%d",&d);
        if (d < 0 || d > 5){
            printf(" Veuillez choisir 0, 1 , 2 , 3 , 4 ou 5\n");
        }
        gerer_operation(d);
        break;
    case 3 :
        printf("          1-creer un compte epargne\n");
        printf("          2-faire des versement\n");
        printf("          3-faire des retraits\n");
        printf("          4-calculer les interet\n");
        printf("          5-afficher les details des comptes\n");
        printf("          choisir un numéro\n ");
        scanf("%d",&f);
        if (f < 0 || f > 5){
            printf(" Veuillez choisir 0, 1 , 2 , 3,4 ou 5\n");
        }
        gerer_compte_epargne(f);
        break;
    case 4:
        printf("          1-Convert from dinar to EUR\n");
        printf("          2-Convert from EUR to dinar\n");
        printf("          3-Convert from dinar to USD(dolar)\n");
        printf("          4-Convert from USD(dolar) to dinar\n");
        printf("          5-Convert from USD(dolar) to EUR\n");
        printf("          6-Convert from EUR to USD(dolar)\n");
        printf("\nEnter your choice: ");
        scanf("%d", &n);
        gerer_conversion(n);
        break;
    case 5:
        gerer_transfer();
        break;
    case 6:
        return 0;
        break;
    default:
        printf(" essayer de choisir 0, 1 , 2 , 3 , 4 ,5  \n");
        break;
    }
}
void gerer_client(int b){
    if(b==1){
        int found=0;
        struct Clients client;
        struct Clients clientcheck;
        FILE *file;
        printf("donner un id\n");
        scanf("%d",&client.id_client);
        file=fopen("client_.txt","r");
        while(fread(&clientcheck,sizeof(struct Clients),1,file)) {
            if(clientcheck.id_client==client.id_client){
                    found=1;
            }
        }
        if(found==1){
            printf("!!!id de client existant essayer un entre id!!!\n");
            return 0;
        }
        printf("donner votre nom : \n");
        scanf("%s",&client.nom);
        printf("donner votre prenom :\n");
        scanf("%s",&client.prenom);
        printf("donner votre numéro telephone :\n");
        scanf("%d",&client.num_telephone);
        file=fopen("client_.txt","a");
        fwrite(&client,sizeof(client),1,file);
        fclose(file);
        if(fwrite!=0){
            printf("*********ajout de client avec succes*******\n");
        }
        else{
            printf("ressayer s'il vous plait\n");
        }
    }
    else if (b==2){
        struct Clients client;
        struct Clients nouv_client;
        FILE*file;
        printf("donner id  client a modifier:\n");
        scanf("%d",&nouv_client.id_client);
        file=fopen("client_.txt","r");
        int nb=0;
        int idfound=0;
        while(fread(&client,sizeof(struct Clients),1,file)){
            tab_client[nb]=client;
            nb++;
            if (client.id_client == nouv_client.id_client) {
                 idfound = 1;
           }
        }
        fclose(file);
        remove("client_.txt");
        FILE *newf;
        newf=fopen("nv.txt","a");
        if(idfound!=1){
            printf("!!!! attention l id que tu as saisie n'existe pas!!!!\n");
        }

        else{
            printf("donner le nouveau nom:\n");
            scanf("%s",&nouv_client.nom);
            printf("donner le nouveau prenom:\n");
            scanf("%s",&nouv_client.prenom);
            printf("donner le nouveau num de telephone:\n");
            scanf("%d",&nouv_client.num_telephone);
            printf("******modification effectue avec succes******\n");

        }
        for(int i=0;i<nb;i++){
            if(tab_client[i].id_client==nouv_client.id_client){
                   fwrite(&nouv_client,sizeof(tab_client[i]),1,newf);
            }
            else
                 fwrite(&tab_client[i],sizeof(tab_client[i]),1,newf);
        }
        fclose(newf);
        rename("nv.txt","client_.txt");

}

 else if (b == 3) {
    int existi = 0;
    struct Clients client;
    FILE *file;
    int code;
    printf("donner l id de client a supprimer\n");
    scanf("%d", &code);
    file = fopen("client_.txt", "r");
    int nb = 0;
    while (fread(&client, sizeof(struct Clients), 1, file)) {
        tab_client[nb] = client;
        nb++;
    }
    fclose(file);
    FILE *newf;
    newf = fopen("nv.txt", "a");
    for (int i = 0; i < nb; i++) {
        if (tab_client[i].id_client == code) {
            existi = 1;
        }
    }
    for (int i = 0; i < nb; i++) {
        if (tab_client[i].id_client != code) {
            fwrite(&tab_client[i], sizeof(tab_client[i]), 1, newf);
        }
    }
    fclose(newf);

    if (existi == 1) {
        remove("client_.txt");
        rename("nv.txt", "client_.txt");
        printf("\n*****suppression avec succes*****\n");
    } else {
        remove("nv.txt");
        printf("\n****** client inexistant*****\n");
    }
}
    else if (b == 4) {
       FILE *file;
       struct Clients client;
       file = fopen("client_.txt", "r");
       while (fread(&client, sizeof(struct Clients), 1, file)) {
            tab_client[nb] = client;
            nb++;
    }
        fclose(file);
        for (int x = 0; x < nb; x++) {
             printf("\n --id_client:%d -- ", tab_client[x].id_client);
             printf("\n* nom_client:%s %s ", tab_client[x].nom, tab_client[x].prenom);
             printf("\n**numero telephone_client:%d \n", tab_client[x].num_telephone);}
}
    else if (b==5){
        interface();
        sous_interface(choix);
    }
    getchar();

}
void gerer_compte(int c){
    if(c==1 ){
        int found=0;
        struct Compte compte;
        struct Compte comptecheck;
        FILE *file;
        printf("donner l id de compte:\n");
        scanf("%d",&compte.id_compte);
        file=fopen("lescomptes.txt","r");
        while(fread(&comptecheck,sizeof(struct Compte),1,file)) {
            if(comptecheck.id_compte==compte.id_compte){
                    found=1;}
        }
        if(found==1){
            printf("!!!compte existant essayer un entre id!!!\n");
            interface();
            sous_interface(choix);}
        file=fopen("lescomptes.txt","a");
        printf("donner l id de client:\n");
        scanf("%d",&compte.id_client);
        printf("donner le solde de base:\n");
        scanf("%f",&compte.solde);
        printf("donner le jour de creation de compte:\n");
        scanf("%d",&compte.d_compte.Jour);
        printf("donner le mois de creation de compte:\n");
        scanf("%d",&compte.d_compte.Mois);
        printf("donner l annee de creation de compte:\n");
        scanf("%d",&compte.d_compte.annee);
        fwrite(&compte,sizeof(compte),1,file);
        fclose(file);
        if(fwrite!=0){
            printf("******creation de compte avec succes******\n");}
        else{
            printf("erreur lors de creation de compte\n");}
    }
    else if (c==5){
        struct Compte compte;
        FILE *file;
        file=fopen("lescomptes.txt","r");
        while(fread(&compte,sizeof(struct Compte),1,file)) {
            printf("\n id de compte : %d",compte.id_compte);
            printf("\n id de client : %d",compte.id_client);
            printf("\n solde:%f",compte.solde);
            printf("\n Date de creation %d /%d /%d ",compte.d_compte.Jour,compte.d_compte.Mois,compte.d_compte.annee);
            printf("\n*******---------------------------******");}
        fclose(file);}
    else if(c==4){
        struct Compte compte;
        int found=0;
        FILE *file;
        file=fopen("lescomptes.txt","r");
        int code;
        printf("donner l'id de compte que te veux afficher\n");
        scanf("%d", &code);
        while(fread(&compte,sizeof(struct Compte),1,file)) {
            if(compte.id_compte==code){
                found=1 ;
                printf("\n id de compte : %d",compte.id_compte);
                printf("\n id de client : %d",compte.id_client);
                printf("\n solde:%f",compte.solde);
                printf("\n Date de creation %d /%d /%d ",compte.d_compte.Jour,compte.d_compte.Mois,compte.d_compte.annee);
                printf("\n*******---------------------------******");}
        }
        if (found==0){
            printf("!!!!!!! attention l'id de compte n'existe pas!!!!!\n");
        }
        fclose(file);
    }
     else if (c == 3) {
         int existi = 0;
         struct Compte compte;
         FILE *file;
         int code;
         printf("donner l id de compte a supprimer\n");
         scanf("%d", &code);
         file = fopen("lescomptes.txt", "r");
         int nb = 0;
         while (fread(&compte, sizeof(struct Compte), 1, file)) {
             tabcomptes[nb] = compte;
             nb++;}
        fclose(file);
        FILE *newf;
        newf = fopen("nv.txt", "a");
        for (int i = 0; i < nb; i++) {
           if (tabcomptes[i].id_compte == code) {
               existi = 1;}
    }
       for (int i = 0; i < nb; i++) {
           if (tabcomptes[i].id_compte != code) {
            -   fwrite(&tabcomptes[i], sizeof(tabcomptes[i]), 1, newf);
        }
    }
       fclose(newf);

       if (existi == 1) {
           remove("lescomptes.txt");
           rename("nv.txt", "lescomptes.txt");
           printf("\n*****suppression avec succes*****\n");
    } else {
        remove("nv.txt");
        printf("\n****** client inexistant*****\n");
    }
}
        else if(c==2){
            struct Compte compte;
            FILE *file;
            int code,nouv_solde,found=0;
            printf("donner l id de client a mettre a jour\n");
            scanf("%d",&code);
            file=fopen("lescomptes.txt","r");
            int nb=0;
            while(fread(&compte,sizeof(struct Compte),1,file)){
                tabcomptes[nb]=compte;
                nb++;
            }
             fclose(file);
             remove("lescomptes.txt");
             FILE *newc;
             newc=fopen("nv.txt","a");
             for(int i=0;i<nb;i++){
                    if(tabcomptes[i].id_compte==code){
                        printf("\ndonner le nouvel solde de compte\n");
                        scanf("%d",&nouv_solde);
                        tabcomptes[i].solde=nouv_solde;
                        found=1;
                    }
                    fwrite(&tabcomptes[i], sizeof(struct Compte), 1, newc);
              }
              fclose(newc);
              rename("nv.txt","lescomptes.txt");
              if (found==1){
                printf("****mise a jour effectuer avec succes****");
              }
              else{
                  printf("!!!!!compte inexistant!!!!!");
              }
}
      else if(c==6){
          interface();
          sous_interface(choix);
      }
      getchar();

}
void save_operation(int code, float montant, const char *operationtype) {
    struct operation op;
    FILE *file;
    file = fopen("operations.txt", "a");
    if (file != NULL) {
        op.id_compt = code;
        op.montan = montant;
        snprintf(op.typeoperation, sizeof(op.typeoperation), "%s", operationtype);
        fwrite(&op, sizeof(op), 1, file);
        fclose(file);
    } else {
        perror("Error opening file");
    }
}
void gerer_operation(int d){
    if(d==2){
            int found=0;
            struct Compte compte;
            FILE *file;
            int code;float montant;
            printf("donner l id de compte\n");
            scanf("%d",&code);
            printf("donner le montant de retrait\n");
            scanf("%f",&montant);
            file=fopen("lescomptes.txt","r");
            int nb=0;
            while(fread(&compte,sizeof(struct Compte),1,file)){
                tabcomptes[nb]=compte;
                nb++;
            }
             fclose(file);
             remove("lescomptes.txt");
             FILE *newb;
             newb=fopen("nv.txt","a");
             for(int i=0;i<nb;i++){
                if(tabcomptes[i].id_compte==code){
                    found=1;
                    if (tabcomptes[i].solde>montant){
                        tabcomptes[i].solde-=montant;
                        save_operation(code,montant,"RETRAIT");

                    }
                    else{
                        printf("!!!!!!!!Attention Solde insuffisant!!!!!!!\n");
                    }
                }
                fwrite(&tabcomptes[i],sizeof(tabcomptes[i]),1,newb);
            }
            fclose(newb);
            rename("nv.txt","lescomptes.txt");
            if(found==0){
                printf("!!!!!!!attention le compte n'existe pas!!!!!\n");
            }
            else{
                printf("*****retrait avec succes*****");

            }
    }
    if(d==1){
            int found=0;
            struct Compte compte;
            FILE *file;
            int code;float montant;
            printf("donner l id de compte\n");
            scanf("%d",&code);
            printf("donner le montant de versement\n");
            scanf("%f",&montant);
            file=fopen("lescomptes.txt","r");
            int nb=0;
            while(fread(&compte,sizeof(struct Compte),1,file)){
                tabcomptes[nb]=compte;
                nb++;
            }
             fclose(file);
             remove("lescomptes.txt");
             FILE *newc;
             newc=fopen("nv.txt","a");
             for(int i=0;i<nb;i++){
                if(tabcomptes[i].id_compte==code){
                    found=1;
                    tabcomptes[i].solde+=montant;
                    save_operation(code,montant,"VERSEMENT");
                }
                fwrite(&tabcomptes[i],sizeof(tabcomptes[i]),1,newc);
            }
            fclose(newc);
            rename("nv.txt","lescomptes.txt");
            if(found==0){
                printf("!!!!!!!!!!attention compte n'existe pas!!!!!!!\n");
            }
            else{
                printf("\n*****versement effectuer avec succes*****\n");
            }
    }
    if(d==4){
        struct operation op;
        int found=0;
        FILE *file;
        file=fopen("operations.txt","r");
        int code;
        printf("donner l'id de compte que te veux afficher l'historique de transaction\n");
        scanf("%d", &code);
        while(fread(&op,sizeof(struct operation),1,file)) {
            if(op.id_compt==code){
                found=1 ;
                printf("\n id de compte : %d",op.id_compt);
                printf("\n montan:%f",op.montan);
                printf("\n type des operation : %s",op.typeoperation);
                printf("\n*******---------------------------******");
            }
        }
        if(found==0){
            printf("!!!!!!compte inexistant!!!!!!");
        }
    }
    else if(d==5){
        struct operation op;
        FILE *file;
        file=fopen("operations.txt","r");
        while(fread(&op,sizeof(struct operation),1,file)) {
            printf("\n id de compte : %d",op.id_compt);
            printf("\n montan:%f",op.montan);
            printf("\n type des operation : %s",op.typeoperation);
            printf("\n*******---------------------------******");
        }
    }
    else if(d==3){
        struct Compte compte;
        FILE *file;
        file=fopen("lescomptes.txt","r");
        while(fread(&compte,sizeof(struct Compte),1,file)) {
            printf("\n id de compte : %d",compte.id_compte);
            printf("\n id de client : %d",compte.id_client);
            printf("\n solde:%f",compte.solde);
            printf("\n Date de creation %d /%d /%d ",compte.d_compte.Jour,compte.d_compte.Mois,compte.d_compte.annee);
            printf("\n*******---------------------------******");
        }
        fclose(file);
    }
    else if(d==6){
        interface();
        sous_interface(choix);
    }
    getchar();
}
gerer_compte_epargne(int f){
    if(f==1){
        struct compte_epargne compte;
        FILE *file;
        printf("donner l id de compte d 'epargne:\n");
        scanf("%d",&compte.id_compte_epargne);
        printf("donner le solde de base:\n");
        scanf("%f",&compte.sold);
        printf("donner le jour de creation de compte:\n");
        scanf("%d",&compte.dcompte.Jour);
        printf("donner le mois de creation de compte:\n");
        scanf("%d",&compte.dcompte.Mois);
        printf("donner l annee de creation de compte:\n");
        scanf("%d",&compte.dcompte.annee);
        file=fopen("comptes_epar.txt","a");
        fwrite(&compte,sizeof(compte),1,file);
        if(fwrite!=0){
            printf("******creation de compte d'epargne avec succes******\n");
    }
        else{
            printf("erreur lors de creation de compte\n");
        }
        fclose(file);
    }
        else if(f==2){
            int found=0;
            struct compte_epargne compte;
            FILE *file;
            int code;float montant;
            printf("donner l id de compte d'epargne\n");
            scanf("%d",&code);
            printf("donner le montant de versement\n");
            scanf("%f",&montant);
            file=fopen("comptes_epar.txt","r");
            int nb=0;
            while(fread(&compte,sizeof(struct compte_epargne),1,file)){
                tabepargne[nb]=compte;
                nb++;
            }
             fclose(file);
             remove("comptes_epar.txt");
             FILE *newc;
             newc=fopen("nv.txt","a");
             for(int i=0;i<nb;i++){
                 if(tabepargne[i].id_compte_epargne==code){
                     found=1;
                     tabepargne[i].sold+=montant;
                     printf("\n*****versement effectuer avec succes*****\n");
                }
                fwrite(&tabepargne[i],sizeof(tabepargne[i]),1,newc);
            }
            fclose(newc);
            rename("nv.txt","comptes_epar.txt");
            if(found==0){
                printf("!!!!!compte inexistant verifier votre id!!!!!!!!\n");
            }
    }
    else if (f==3){
            int found=0;
            struct compte_epargne compte;
            FILE *file;
            int code;float montant;
            printf("donner l id de compte d'epargne\n");
            scanf("%d",&code);
            printf("donner le montant de retrait\n");
            scanf("%f",&montant);
            file=fopen("comptes_epar.txt","r");
            int nb=0;
            while(fread(&compte,sizeof(struct compte_epargne),1,file)){
                tabepargne[nb]=compte;
                nb++;
            }
             fclose(file);
             remove("comptes_epar.txt");
             FILE *newc;
             newc=fopen("nv.txt","a");
             for(int i=0;i<nb;i++){
                 if(tabepargne[i].id_compte_epargne==code){
                     found=1;
                     if(tabepargne[i].sold>montant){
                        tabepargne[i].sold-=montant;
                        printf("\n*****retrait effectuer avec succes*****\n");
                     }
                     else{
                        printf("\n!!!!!!!!!solde insuffisant!!!!!!!\n");
                     }

                }
                fwrite(&tabepargne[i],sizeof(tabepargne[i]),1,newc);
            }
            fclose(newc);
            rename("nv.txt","comptes_epar.txt");
            if(found==0){
                printf("!!!!!compte inexistant verifier votre id!!!!!!!!\n");
            }
    }
    else if(f==4){
        float taux_interet=80;
        int code;float montant;
        struct compte_epargne compte;
        FILE *file;
        file=fopen("comptes_epar.txt","r");
        printf("donner l id de votre compte\n");
        scanf("%d",&code);
        while(fread(&compte,sizeof(struct compte_epargne),1,file)){
            if(compte.id_compte_epargne==code){
                montant=compte.sold;
            }
        }
        fclose(file);
        printf("%d",montant);
        float montant_apres_3_mois;
        float montant_apres_6_mois;
        float montant_apres_1_ans;
        montant_apres_3_mois = ((montant * taux_interet * 90) / 36000)+montant ;
        montant_apres_6_mois = ((montant * taux_interet * 180) / 36000)+montant ;
        montant_apres_1_ans = ((montant * taux_interet * 360) / 36000)+montant;
        ;
        printf("\n votre solde serait apres 3 mois: %f ", montant_apres_3_mois);
        printf("\n votre solde serait apres 6 mois: %f ", montant_apres_6_mois);
        printf("\n votre solde serait apres 1 an: %f ", montant_apres_1_ans);
    }
    else if (f==5){
        struct compte_epargne compte;
        FILE *file;
        file=fopen("comptes_epar.txt","r");
        while(fread(&compte,sizeof(struct compte_epargne),1,file)) {
            printf("\n id de compte : %d",compte.id_compte_epargne);
            printf("\n solde:%f",compte.sold);
            printf("\n Date de creation %d /%d /%d ",compte.dcompte.Jour,compte.dcompte.Mois,compte.dcompte.annee);
            printf("\n*******---------------------------******");
        }
        fclose(file);
    }
    getchar();
    }
void gerer_conversion(int n) {
    double amount;
    switch (n) {
        case 1:
            printf("\nEnter the amount in dinar: ");
            scanf("%lf", &amount);
            printf("%.2f dinar is %.2f EUR\n", amount, amount * Dinar_TO_EUR);
            break;
        case 2:
            printf("\nEnter the amount in EUR: ");
            scanf("%lf", &amount);
            printf("%.2f EUR is %.2f dinar\n", amount, amount / Dinar_TO_EUR);
            break;
        case 3:
            printf("\nEnter the amount in dinar: ");
            scanf("%lf", &amount);
            printf("%.2f dinar is %.2f USD\n", amount, amount * Dinar_TO_USD);
            break;
        case 4:
            printf("\nEnter the amount in USD: ");
            scanf("%lf", &amount);
            printf("%.2f USD is %.2f dinar\n", amount, amount / Dinar_TO_USD);
            break;
        case 5:
            printf("\nEnter the amount in USD: ");
            scanf("%lf", &amount);
            printf("%.2f USD is %.2f EUR\n", amount, amount * USD_TO_EUR);
            break;
        case 6:
            printf("\nEnter the amount in EUR: ");
            scanf("%lf", &amount);
            printf("%.2f EUR is %.2f USD\n", amount, amount / USD_TO_EUR);
            break;
        default:
            printf("\nInvalid choice\n");
    }
    getchar();

}
void gerer_transfer() {
    int sender_account_id, recipient_account_id;
    float amount;
    FILE *file;
    FILE *tempFile;
    file = fopen("lescomptes.txt", "r");
    tempFile = fopen("templescomptes.txt", "w");

    if (file == NULL || tempFile == NULL) {
        perror("il n'ya aucune compte essayer de faire des compte");
        return;
    }
    struct Compte account;
    int found_sender = 0;
    int found_recipient = 0;
    printf("Enter the id of the account of sender\n");
    scanf("%d", &sender_account_id);
    printf("Enter the id of the account of recipient\n");
    scanf("%d", &recipient_account_id);
    printf("Enter the amount \n");
    scanf("%f", &amount);
    while (fread(&account, sizeof(struct Compte), 1, file)) {
        if (account.id_compte == sender_account_id) {
            found_sender = 1;
            if (account.solde >= amount) {
                account.solde -= amount;
            } else {
                printf("Le compte n'a pas un solde suffisant pour le transfert.\n");
                fclose(file);
                fclose(tempFile);
                remove("templescomptes.txt");
                return;
            }
        } else if (account.id_compte == recipient_account_id) {
            account.solde += amount;
            found_recipient = 1;
        }
        fwrite(&account, sizeof(struct Compte), 1, tempFile);
    }
    fclose(file);
    fclose(tempFile);
    if (!found_sender) {
        printf("!!!!!*Le compte expediteur n'a pas ete trouve.*!!!!!\n");
        remove("templescomptes.txt");
        return;
    }
    if (!found_recipient) {
        printf("!!!!!*Le compte beneficiaire n'a pas ete trouve!!!!!\n");
        remove("templescomptes.txt");
        return;
    }
    remove("lescomptes.txt");
    rename("templescomptes.txt", "lescomptes.txt");
    printf("********Transfert d'argent effectue avec succes.******\n");
    getchar();
}
int main(){
    printf("************************************************************\n");
    printf("*                 Welcome to my E-BANK APP               *\n");
    printf("************************************************************\n");
    printf("\n");
    interface();
    sous_interface(choix);
    getchar();
    return 0;
}
