#include<stdio.h>
#include<stdlib.h>
#include<time.h>
void singlePlayer();
void multiPlayer();
void settings();
void player(int steps,int player);
char gameplay(char *diff, char *obs, int players, int step, int random_num,int hit);
int random();
void main(){
    srand(time(NULL)); // Seed the random number generator ONCE
    //State variables and options
    int option_state=0,selection,inval=9;
    

    // Mainloop of the Game
    while(option_state==0){
    system("cls"); 
    printf("\n               Steprace                  " // Game intro screen
        "\n+------------------------------------------+"
        "\n|           1. Single Player               |"
        "\n|           2. MultiPlayer                 |"
        "\n|           3. Settings                    |"
        "\n|           4. Quit Game                   |"
        "\n+------------------------------------------+\n"
    );
    (inval==0) ? printf("Invalid option Selected\n\n") : printf("Choose a selection using Numpad keys :\n"); 
    printf("==> ");
    scanf("%d",&selection);
    switch (selection)
    {
    case 1 :
        singlePlayer();
        break;
    case 2 :
        multiPlayer();
        break;
    case 3 :
        settings();
        break;
    
    case 4 :
        option_state=1;
        break;
    
    default:
        printf("\n Invalid selection");
        inval=0;
        break;
    }
    
}
    
    
    
}


// Definition of game functions
// SinglePlayer logic
void singlePlayer(){
    system("cls");
    char *diff="False",*obs="False";
    int sel;
    int step=0;
    int roll=0;
    int random_value;
    int win;
    int random_obstacle;
    time_t time_start;
    time_t time_end;
    double best_time=0;
    int hit;
    refresh:
    printf("\n       Steprace - SinglePlayer            " // single Player logic
        "\n+------------------------------------------+"
        "\n|  1. Difficulity                    %s |"
        "\n|  2. Enable obstacles               %s |"
        "\n|  3. Return to main screen                |"
        "\n+------------------------------------------+"
        "\n|       Select 4 to Start the game         |"
        "\n+------------------------------------------+\n",
        diff,obs
    );
    scanf("%d",&sel);
    switch (sel)
    {
    case 1 :
        if(diff=="False")
            diff="True ";
        else 
            diff="False";
        system("cls");
        goto refresh;
        break;
    case 2 : 
        if(obs=="False")
            obs="True ";
        else
            obs="False";
        system("cls");
        goto refresh;
        break;
    case 4 :
            time_start=time(NULL);
            while (step<50)
            {   
              
                if (step==0)
                    system("cls");
                printf("\n Press 0 to Roll dice \n ==> ");
                scanf("%d",&roll);
                if(roll==0){
                    random_value=random();
                    
                    if(obs=="True "){
                        random_obstacle=random();

                        if(random_value==random_obstacle){
                            step-=random_value;
                            hit=1;
                        }else{
                            step+=random_value;
                            hit=0;
                            
                        }
                    }else{
                        step+=random_value;
                    }
                
                    gameplay(diff,obs,1,step,random_value,hit);
                }else{
                    printf("\n Invalid input");
                }
                
            }
                //Single player win logic
                time_end=time(NULL);
                double elapsed=difftime(time_end,time_start);
                //read last game win time
                FILE *fp=fopen("steprace_time.txt","r");
                fscanf(fp,"%lf",&best_time);
                
                if((best_time==0) || (best_time>elapsed)){
                    fclose(fp);
                printf("\n Player has won the game in %.0f seconds.\n===========================================",elapsed);
                printf("\n Press 0 to continue.\n==>");
                //Save the elapsed time of the winning game
                    FILE *fp=fopen("steprace_time.txt","w");
                    if(fp!=NULL){
                        fprintf(fp,"%.0f\n",elapsed);
                        fclose(fp);
                    }else{
                        printf("\n Error saving new score");
                    }
                }else{
                    system("cls");
                    printf("Player has lose the game.\n"
                           "========================"
                        "\nLast record : %.0fs\nCurrent score : %.0fs\nEnter any number to continue:\n==>",best_time,elapsed);
                }
                scanf("%d",&win);
            
            break;
            
    
    default:
        break;
    }
}

// Multiplayer Logic
void multiPlayer(){
    system("cls");
    char *diff="False",*obs="False";
    char sel;
    int players=2;
    refresh_multiplayer_screen:
    printf("\n       Steprace - MultiPlayer            " // Game intro screen
        "\n+------------------------------------------+"
        "\n|  1. Difficulity                    %s |"
        "\n|  2. Enable obstacles               %s |"
        "\n|  3. Players                        - %d + |"
        "\n|  4. Return to main screen                |"
        "\n|  5. Start Game                           |"
        "\n+------------------------------------------+"
        "\n|  Use - + to increase or decrease player  |"
        "\n+------------------------------------------+\n",
        diff,obs,players
    );
    scanf(" %c",&sel);
    switch (sel)
    {
    case '1' :
        if(diff=="False")
            diff="True ";
        else 
            diff="False";
        system("cls");
        goto refresh_multiplayer_screen;
        break;
    case '2' : 
        if(obs=="False")
            obs="True ";
        else
            obs="False";
            system("cls");
        goto refresh_multiplayer_screen;
        break;
    case '+' :
            system("cls");
        if(players<3)
            players++;
        else
            printf("\n     Maximum Player limit reached");
        goto refresh_multiplayer_screen;
        break;
    case '-' : 
            system("cls");
        if(players>2)
            players--;
        else
            printf("\n     Minimum 2 Players for multiplayer");
        goto refresh_multiplayer_screen;
        break;
        case '4' : break;
        case '5' : printf("\n Game under construction \n");
                   system("pause");
                   break;
    
    default:
        multiPlayer();
        break;
    }
}
void settings(){
    char sel;
    char exit_state='0';
    while(exit_state!='1'){
    FILE *fp=fopen("steprace_time.txt","r");
    double score;
    system("cls");
    if(fp!=NULL){
        fscanf(fp,"%lf",&score);
    }else{
        printf("\n No previous records available \n");
    }
    
    fclose(fp);
    

      printf("+------------------------------------------+"
           "\n|  1. Last Score                           |"
           "\n|  2. Delete last score                    |"
           "\n|  3. Back to Main menu                    |"
           "\n+------------------------------------------+\n Select options\n==> "
    );
    sel=getchar();
    scanf("%c",&sel);
    if(sel=='1'){
        (score>0) ? printf("\n Your last highest score is %.0fs \n",score) : printf("\n No score available to fetch \n");
        system("pause");


    }else if(sel=='2'){
        fp=fopen("steprace_time.txt","w");
        if(fp!=NULL)
            fclose(fp); //deleted
            printf("\n Score deleted successfully! \n");
            system("pause");

        

    }else if(sel=='3'){
        exit_state='1';
    }
}
    
}



int random(){
    return (rand() % 6) + 1;
}


void player(int steps,int player){
    char a='-';
    int n=steps;
    for(int i=1;i<=n;i++)
        printf("%c",a);
    printf("Player|>");
}


char gameplay(char *diff, char *obs,int players, int step, int random_num, int hit){
    char *diff_state=diff;
    char *obs_state=obs;
    int player_num=players;
    int steps=step;
    int hit_obs=hit;
    system("cls");
    printf("Player %d has got %d when rolled, moving steps\n",player_num,random_num);
    printf("Track:\n"
        "+---------------------------+\n"
        "| Total Step taken: %d/50    |\n"
        "+---------------------------+\n"
        "| Difficulity : %s       |\n"
        "| Obstacle : %s          |\n"
        "| Players : %d               |\n"
        "+--------------------------+\n",
    steps,diff_state,obs_state,player_num);
    printf("\n+--------------------------------------------------------F>\n");
    player(steps,player_num);
    printf("\n+--------------------------------------------------------F>\n");
    if(hit==1)
        printf("\n\nYou got hit with an obstacle and decided to move back!\n");
    

}
