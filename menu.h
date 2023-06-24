void addItems(void);
void item_info(void);
void searchItem(void);
void deleteItem(void);
void updateItem(void);
void sell(void);
void calculateBill(void);
void updateQuantity(int number, int quntity );
void billCreate(int number,int qun);
int itemsIdChecker(int id);
int checkItemQuantity(int id, int qun);

//Items information struct
struct items{
    char itemName[20];
    int quantity;
    int itemsPrice;
    int itemNumber;
};

//Sell item data struct
struct sell{
    char itemName[20];
    int itemNumber;
    int itemsPrice;
    int quantity;
    int itembill;};

int totalBill=0;
//temporarily buy id and quantity store struct
struct tempsell{
    int quantity;
    int itemNumber;
};

 void shop_menu(void){
     int option;
        printf("1. Sell items\n");
        printf("2. Add Items\n");
        printf("3. Items List\n");
        printf("4. Search Items\n");
        printf("5. Delete Items\n");
        printf("6. Update Items\n");
        printf("7. Close shop\n");
        printf("\nEnter your choice :");
        scanf("%d",&option);
        switch (option) {
            case 1:
                sell();
            case 2:
                addItems();
                break;
            case 3:
                item_info();
                break;
            case 4:
                searchItem();
                break;
            case 5:
                deleteItem();
                break;
            case 6:
                updateItem();
                break;
            case 7:
               {
                printf("System is closing in 5 seconds");
                sleep(5);
                system("cls");};
                break;
            default:
                shop_menu();}

            return;

            };




//function to add items
void addItems(void){
 FILE *file;
    int number = 0;
    struct items structitems;
    file= fopen("itemdata.txt","a");

    if(file==NULL){
        printf("file open fail\n");
    } else{
        printf("--------------------------------------------------------------------\n");
        printf("\nHow many items need to be added:");
        scanf("%d",&number);
        for (int i=0;i<number;++i){
            LOOP: printf("Enter item code: ");
            scanf(" %d",&structitems.itemNumber);

            // call itemsIdChecker() function user enter item code check
            int check =itemsIdChecker(structitems.itemNumber);

            if(check == 0){
                printf("Enter item name:");
                scanf(" %s",&structitems.itemName);
                printf("Enter item price:");
                scanf(" %d",&structitems.itemsPrice);
                printf("Enter item quantity:");
                scanf(" %d",&structitems.quantity);

                fwrite( &structitems,sizeof(structitems),1,file );
                printf("\nItem Added successfully\n");
            } else{
                printf("\nProduct Code is Already used please add another number and try again\n\n");
                goto LOOP;
            }
        }

    }

    fclose(file);
    shop_menu();
};



void item_info(void){  //function to see all items
    FILE *file;
    struct items s;
    int items=0,qunticount=0,pri=0;
    file= fopen("itemdata.txt","r");
    if(file==NULL){
        printf("file open fail\n");
    } else{
        printf("----------------------------------------------------------------------------------------------------\n");
        printf("ItemNumber\t\tName\t\t\tPrice\t\t\tquantity\n");
        printf("----------------------------------------------------------------------------------------------------");
        while (fread(&s,sizeof (s),1,file)){
            printf("\n%d\t\t\t%s\t\t\t%d\t\t\t%d",s.itemNumber,s.itemName,s.itemsPrice,s.quantity);
            items=items+1;
            qunticount=qunticount+s.quantity;
            pri=pri+(s.itemsPrice*s.quantity);

        }
        printf("\n----------------------------------------------------------------------------------------------------\n");
        printf("Total items %d\n",items);
        printf("Total inventory %d\n",qunticount);
        printf("Total value of goods %d",pri);
        printf("\n----------------------------------------------------------------------------------------------------\n");
    }
    fclose(file);
    shop_menu();
};


 //to check if two items have the same product code
 int itemsIdChecker(int id){
     FILE *file;
    struct items s;
    int found=0;
    file= fopen("itemdata.txt","r");
    if(file==NULL){
        printf("file open fail\n");
    } else{
        while (fread(&s,sizeof (s),1,file)){
            if(s.itemNumber == id){
                found = 1;
            }
        }
    }

    fclose(file);
    return found;
    };


 void searchItem(void){
     FILE *file;
    struct items s;
    int iNumber,found=0;
    file= fopen("itemdata.txt","r");
    if(file==NULL){
        printf("file open fail\n");
    } else{
        printf("Enter item number:");
        scanf("%d",&iNumber);
        printf("\n--------------------------------------------------------------------\n");
        printf("ItemNumber\t\tName\t\tPrice\t\tquantity\n");
        printf("--------------------------------------------------------------------");
        while (fread(&s,sizeof (s),1,file)){
            if(s.itemNumber == iNumber){
                found=1;
                printf("\n%d\t\t\t%s\t\t%d\t\t%d",s.itemNumber,s.itemName,s.itemsPrice,s.quantity);
            }
        }
        printf("\n\n");
        if(found==0){
            printf("Item not found");
        }
    }
    fclose(file);
    shop_menu();
 };


 void deleteItem(void){
    FILE *file,*file1;
    struct items s;
    int iNumber,found=0;
    file= fopen("itemdata.txt","r");
    file1= fopen("temp.txt","w");
    if(file==NULL){
        printf("file open fail\n");
    } else{
        printf("\n\n");
        printf("Enter delete item number:");
        scanf("%d",&iNumber);
        while (fread(&s,sizeof (s),1,file)){
            if(s.itemNumber == iNumber){
                found=1;
            } else{
                fwrite( &s,sizeof(s),1,file1 );
            }
        }
        fclose(file);
        fclose(file1);
        if(found==0){
            printf("\nItem not found\n");
        } else{
            file1= fopen("temp.txt","r");
            file= fopen("itemdata.txt","w");

            while (fread(&s,sizeof (s),1,file1)){
                fwrite( &s,sizeof(s),1,file );
            }
            printf("\nItem Delete successful\n");
            fclose(file);
            fclose(file1);
        }
    }
    shop_menu();
 };


 void updateItem(void){
    FILE *file,*file1;
    struct items s;
    int iNumber,found=0,n;
    file= fopen("itemdata.txt","r");
    file1= fopen("temp.txt","w");
    if(file==NULL){
        printf("file open fail\n");
    } else{
        printf("Enter Update item number:");
        scanf("%d",&iNumber);
        while (fread(&s,sizeof (s),1,file)){
            if(s.itemNumber == iNumber){
                found=1;
                Loop: printf("1. Update Item name\n"
                             "2. Update Item price\n"
                             "3. Update Item quantity\n");
                scanf("%d",&n);
                if(1==n){
                    printf("Enter item name:");
                    scanf(" %s",&s.itemName);
                } else if (2 == n){
                    printf("Enter item price:");
                    scanf(" %d",&s.itemsPrice);
                } else if ( 3== n){
                    printf("Enter item quantity:");
                    scanf(" %d",&s.quantity);
                } else{
                    printf(" Invalid input \n");
                    goto Loop;
                }
            }
            fwrite( &s,sizeof(s),1,file1 );
        }
        fclose(file);
        fclose(file1);
        if(found==0){
            printf("\nItem not found");
        } else{
            file1= fopen("temp.txt","r");
            file= fopen("itemdata.txt","w");

            while (fread(&s,sizeof (s),1,file1)){
                fwrite( &s,sizeof(s),1,file );
            }

            fclose(file);
            fclose(file1);
        }
    }
    shop_menu();
 };

void sell(void){
 FILE *file,*file1;
    int check=1;
    struct items s;
    struct tempsell tb;
    file= fopen("itemdata.txt","r");
    file1= fopen("tempbuy.txt","w");
    if(file==NULL &&  file1 == NULL){
        printf("file open fail\n");
    } else{
        printf("\n--------------------------------------------------------------------\n");
        printf("ItemNumber\t\tName\t\tPrice\t\tquantity\n");
        printf("--------------------------------------------------------------------");
        while (fread(&s,sizeof (s),1,file)){
            printf("\n%d\t\t\t%s\t\t%d\t\t%d",s.itemNumber,s.itemName,s.itemsPrice,s.quantity);
        }
        fclose(file);
        printf("\n--------------------------------------------------------------------\n");
        do {
            Loop:  printf("Enter item number \n");
            scanf("%d",&tb.itemNumber);
            int check1 =itemsIdChecker(tb.itemNumber);
            if (check1 == 1){
                Loop1: printf("Enter item quantity \n");
                scanf("%d",&tb.quantity);

                // call checkItemQuantity() function, argument -- item number and quantity
                int check2 = checkItemQuantity(tb.itemNumber,tb.quantity);

                if(check2 == 1){
                    // write temporary quantity and item number
                    fwrite( &tb,sizeof(tb),1,file1);
                } else if(check2 == 2){
                    printf("This item out of stock\n\n");
                    goto Loop;
                } else{
                    printf("Your Request quantity Not available ! Try again\n\n");
                    goto Loop1;
                }
                Loop3:  printf("\n0 Proceed to pay\n" "1 Add more\n");
                scanf("%d",&check);
                if(check != 0 && check !=1 ){
                    goto Loop3;
                }
            } else{
                printf("\nWrong item number try again\n\n");
                goto Loop;
            }
        } while (check==1);
        fclose(file1);

    }
    calculateBill(); //call this function to print bill
    shop_menu();
};


void calculateBill(void){
  FILE *file;
    struct tempsell tb;
    file= fopen("tempbuy.txt","r");
    printf("                             === Hitagi Stationery Shop ===                                         \n");
    printf("----------------------------------------------------------------------------------------------------\n");
    printf("----------------------------------------------------------------------------------------------------\n");
    printf("ItemNumber\t\tName\t\tPrice\t\tQuantity\t\tAmount");
    while (fread(&tb,sizeof (tb),1,file)){
        billCreate(tb.itemNumber,tb.quantity);
    }
    printf("\n----------------------------------------------------------------------------------------------------\n");
    printf("TOTAL : %d\n",totalBill);
    printf("----------------------------------------------------------------------------------------------------\n");
    printf("                             ===== Thank you come Again =====\n");
    fclose(file);
};


int checkItemQuantity(int id, int qun){
    FILE *file;
    struct items s;
    int check=0;
    file= fopen("itemdata.txt","r");
    if(file==NULL){
        printf("file open fail\n");
    } else{
        while (fread(&s,sizeof (s),1,file)){
            if(s.itemNumber == id){
                if(s.quantity == 0){
                    check = 2;
                } else{
                    if(s.quantity >= qun ){
                        check= 1;
                    }
                }
            }
        }
    }
    fclose(file);
    return check;
}


void billCreate(int number,int qun){
    FILE *file,*file1;
    struct items s;
    struct sell by;
    int found=0,bill;


    file= fopen("itemdata.txt","r");
    file1= fopen("billdata.txt","a");

    if(file==NULL && file1==NULL){
        printf("file open fail\n");
    } else{
        while (fread(&s,sizeof (s),1,file)){
            if(s.itemNumber == number){
                bill=qun*s.itemsPrice;
                totalBill=totalBill+bill;
                found=1;
                printf("\n%d\t\t\t%s\t\t%d\t\t%d\t\t\t%d",s.itemNumber,s.itemName,s.itemsPrice,qun,bill);

                // call updateQuantity functions to change stock amount
                updateQuantity(s.itemNumber, qun);

                strncpy(by.itemName, s.itemName, 20);
                by.itemNumber = s.itemNumber;
                by.quantity = qun;
                by.itemsPrice = s.itemsPrice;
                by.itembill=bill;

                fwrite( &by,sizeof(by),1,file1);
            }
        }
        if(found==0){
            printf("\nItem not found");
        }
    }
    fclose(file);
    fclose(file1);
}

//Removes sold items
void updateQuantity(int number, int quntity ){
    FILE *file,*file1;
    struct items s;
    int found=0;
    file= fopen("itemdata.txt","r");
    file1= fopen("temp.txt","w");
    if(file==NULL){
        printf("file open fail\n");
    } else{
        while (fread(&s,sizeof (s),1,file)){
            if(s.itemNumber == number){
                found=1;
                s.quantity=s.quantity-quntity;
            }
            fwrite( &s,sizeof(s),1,file1 );
        }
        fclose(file);
        fclose(file1);
        if(found==0){
            printf("\n item not found and not Update");
        } else{
            file1= fopen("temp.txt","r");
            file= fopen("itemdata.txt","w");

            while (fread(&s,sizeof (s),1,file1)){
                fwrite( &s,sizeof(s),1,file );
            }

            fclose(file);
            fclose(file1);
        }
    }
}
