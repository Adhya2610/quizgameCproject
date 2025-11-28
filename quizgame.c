#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_Q 10
#define LEVELS 5
#define TIME_LIMIT 90

struct Question {
    char q[256];
    char opt[4][128];
    int correct;
};

struct Question quiz[LEVELS][MAX_Q] = {
    { 
        {"Who is known as King Khan?",{"Salman Khan","Aamir Khan","Shah Rukh Khan","Saif Ali Khan"},2},
        {"Which movie features the song 'Kal Ho Naa Ho'?",{"Kal Ho Naa Ho","Kabhi Khushi Kabhie Gham","Veer-Zaara","Dilwale"},0},
        {"Who directed 'Lagaan'?",{"Rohit Shetty","Ashutosh Gowariker","Rajkumar Hirani","Karan Johar"},1},
        {"Which actress starred in 'Queen'?",{"Alia Bhatt","Deepika Padukone","Kangana Ranaut","Kriti Sanon"},2},
        {"'3 Idiots' is based on a book by?",{"Chetan Bhagat","Amish Tripathi","Arundhati Roy","Ruskin Bond"},0},
        {"Which actor played Bajirao in Bajirao Mastani?",{"Ranveer Singh","Shahid Kapoor","Hrithik Roshan","Varun Dhawan"},0},
        {"DDLJ released in?",{"1993","1995","1997","1999"},1},
        {"Who is the music director duo 'Shankar-Ehsaan-Loy'?",{"3 people","2 people","4 people","1 person"},0},
        {"Which actress starred in 'Chennai Express'?",{"Kareena Kapoor","Katrina Kaif","Deepika Padukone","Anushka Sharma"},2},
        {"First Bollywood talkie film?",{"Lagaan","Raja Harishchandra","Alam Ara","Mother India"},2}
    },
    { 
        {"Who was the first PM of India?",{"Nehru","Gandhi","Patel","Tilak"},0},
        {"Battle of Plassey year?",{"1757","1857","1764","1799"},0},
        {"Capital of Maurya Empire?",{"Pataliputra","Delhi","Kashi","Rajgir"},0},
        {"Who built Taj Mahal?",{"Akbar","Aurangzeb","Shah Jahan","Humayun"},2},
        {"Quit India Movement year?",{"1942","1932","1947","1950"},0},
        {"Founder of Mughal Empire?",{"Babur","Akbar","Shah Jahan","Jahangir"},0},
        {"Who wrote Arthashastra?",{"Chanakya","Kalidasa","Valmiki","Aryabhata"},0},
        {"Who was known as Iron Man?",{"Gandhi","Sardar Patel","Subhash Bose","Nehru"},1},
        {"Who was the last Mughal emperor?",{"Bahadur Shah II","Akbar","Aurangzeb","Jahangir"},0},
        {"Who discovered sea route to India?",{"Columbus","Vasco da Gama","Magellan","Marco Polo"},1}
    },
    { 
        {"What has keys but can't open locks?",{"Piano","Car","Locker","Bottle"},0},
        {"What has hands but cannot clap?",{"Monkey","Clock","Robot","Statue"},1},
        {"What gets wetter as it dries?",{"Water","Towel","Sun","Air"},1},
        {"I speak without a mouth, what am I?",{"Echo","Wind","Shadow","Light"},0},
        {"What has a heart but no body?",{"Tree","Artichoke","Stone","Cloud"},1},
        {"I have branches but no fruit?",{"Bank","Tree","Library","Road"},0},
        {"I am tall when young, short when old?",{"Stick","Candle","Chair","Ruler"},1},
        {"What has a ring but no finger?",{"Phone","Bell","Planet","Clock"},0},
        {"What has a neck but no head?",{"Bottle","Snake","Shirt","Drum"},0},
        {"What has legs but cannot walk?",{"Table","Robot","Cat","Clock"},0}
    },
    {
        {"Capital of Japan?",{"Tokyo","Osaka","Kyoto","Sapporo"},0},
        {"Worlds longest river?",{"Nile","Amazon","Yangtze","Ganga"},1},
        {"Currency of UK?",{"Dollar","Euro","Pound","Franc"},2},
        {"Largest planet?",{"Earth","Mars","Jupiter","Saturn"},2},
        {"Fastest land animal?",{"Horse","Cheetah","Leopard","Tiger"},1},
        {"Human bones count?",{"206","210","198","201"},0},
        {"Hottest planet?",{"Mercury","Venus","Mars","Jupiter"},1},
        {"Which country invented paper?",{"India","China","Egypt","Greece"},1},
        {"Earths ocean count?",{"3","4","5","6"},2},
        {"Sun is a?",{"Planet","Star","Comet","Asteroid"},1}
    },
    { 
        {"Brain of computer?",{"RAM","CPU","GPU","SSD"},1},
        {"Binary of 5?",{"101","100","111","110"},0},
        {"Founder of Microsoft?",{"Jobs","Gates","Musk","Torvalds"},1},
        {"HTML stands for?",{"Hyperlinks Markup","Hypertext Markup","HighText Machine","None"},1},
        {"Python creator?",{"Guido van Rossum","Dennis Ritchie","James Gosling","Linus"},0},
        {"C was developed by?",{"Ken Thompson","Dennis Ritchie","Bjarne","Steve"},1},
        {"UNIX invented at?",{"Apple","Bell Labs","IBM","Microsoft"},1},
        {"GPU used for?",{"Graphics","Storage","Network","Input"},0},
        {"1 byte =?",{"4 bits","8 bits","16 bits","32 bits"},1},
        {"Linux kernel written in?",{"C","Java","Python","Rust"},0}
    }
};

void saveHighscore(int score){
    FILE *f=fopen("highscore.txt","w");
    if(f){fprintf(f,"%d",score);fclose(f);}
}

int loadHighscore(){
    FILE *f=fopen("highscore.txt","r");
    if(!f)return 0;
    int s; fscanf(f,"%d",&s); fclose(f); return s;
}

int ask(struct Question *q, int *skip, int *fifty, int *doublep){
    int order[4] = {0,1,2,3};

    // Shuffle options
    for(int i=3;i>0;i--){
        int j = rand() % (i+1);
        int t = order[i];
        order[i] = order[j];
        order[j] = t;
    }

    printf("%s\n", q->q);
    for(int i = 0; i < 4; i++)
        printf("%d. %s\n", i+1, q->opt[order[i]]);

    printf("Use lifeline? (y/n): ");
    char ch;
    scanf(" %c", &ch);

    int double_flag = 0;
    if(ch == 'y'){
        printf("Choose lifeline:\n1. Skip\n2. Fifty-Fifty\n3. Double Points\n");
        int choice;
        scanf("%d", &choice);
        if(choice == 1 && *skip){
            *skip = 0;
            printf("Skipped!\n");
            return 0; // no points for skip
        }
        if(choice == 3 && *doublep){
            *doublep = 0;
            double_flag = 1;
            printf("Double points active!\n");
        }
        if(choice == 2 && *fifty){
            *fifty = 0;
            // Implement fifty-fifty: show correct and one random incorrect
            int wrongs[3], idx = 0;
            for(int i = 0; i < 4; i++) if(order[i] != q->correct) wrongs[idx++] = i;
            int keep = wrongs[rand() % 3];
            printf("Fifty-Fifty applied:\n");
            printf("1. %s\n", q->opt[order[q->correct]]);
            printf("2. %s\n", q->opt[order[keep]]);
            // Get answer
            time_t start = time(NULL);
            int ans;
            printf("Answer: ");
            scanf("%d", &ans);
            if(time(NULL) - start > TIME_LIMIT){
                printf("Time Up!\n");
                exit(0);
            }
            if(ans == 1){
                printf("Correct!\n");
                return double_flag ? 2 : 1;
            } else {
                printf("Incorrect!\n");
                return 0;
            }
        }
    }

    // Normal question
    time_t start = time(NULL);
    int ans;
    printf("Answer: ");
    scanf("%d", &ans);
    if(time(NULL) - start > TIME_LIMIT){
        printf("Time Up!\n");
        exit(0);
    }
    int correct = (order[ans - 1] == q->correct);
    if(correct){
        printf("Correct!\n");
        return double_flag ? 2 : 1;
    } else {
        printf("Incorrect!\n");
        return 0;
    }
}

int main(){
    int total = 0;
    int high = loadHighscore();
    srand(time(NULL));
    printf("------------------------------------------------------------------------------------------------------------\n");
    printf("                                         THE ULTIMATE QUIZ GAME                                              \n");
    printf("--------------------------------------------------------------------------------------------------------------\n");

    char *level_names[LEVELS] = {"Bollywood Bonanza", "Echoes of INDIA (History)", "Mind Maze (Riddles)", "WorldWatch (General Knowledge)", "Code Chronicles (Computer Science)"};

    for(int lvl = 0; lvl < LEVELS; lvl++){
        int score = 0;
        int skip = 1, fifty = 1, doublep = 1;

        printf("\n--- %s ---\n", level_names[lvl]);

        for(int i = 0; i < MAX_Q; i++){
            printf("\nQ%d:\n", i + 1);
            score += ask(&quiz[lvl][i], &skip, &fifty, &doublep);
        }

        printf("Level %d score: %d\n", lvl + 1, score);
        total += score;
        printf("Total so far: %d\n", total);
    }

    printf("Total Score = %d\n", total);

    // Appreciation message
    printf("\n=====================\n");
    printf("     Appreciation\n");
    printf("=====================\n");

    if (total >= 45)
        printf("Outstanding! You're a QUIZ MASTER! \n");
    else if (total >= 35)
        printf(" Excellent job! You really know your stuff! \n");
    else if (total >= 25)
        printf(" Good effort! You have solid knowledge! \n");
    else if (total >= 15)
        printf(" Not bad! Keep practicing and you'll improve! \n");
    else
        printf(" Don't worry—every expert was once a beginner! Try again! \n");

    if(total > high){
        printf("New High Score!\n");
        saveHighscore(total);
    } else {
        printf("High Score: %d\n", high);
    }

    return 0;
}
