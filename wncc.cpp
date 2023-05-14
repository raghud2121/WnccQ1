#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int maxp = 0; // maxp is the global variable which contains the no.of maximum projects possible

int indexcheck(int F[][5], int a, int b, vector<int>& roll) {
    int i = 0;
    for (int index = 0; index < roll.size(); index++) {
        if (F[a][b] == roll[index]) {
            i = index;
            return i;
            if(F[a][b]==-2){return -1;}
        }
    }
}//This function returns the index of the rollno.

int checkeligibility(int F[][5], int g, int dif[][5000], vector<int>& roll) {
    for (int j = 0; j < 5; j++) {
        if (F[g][j] == -1||F[g][j]==0) {
            continue;
        }
        int i = indexcheck(F, g, j, roll);

        if (dif[g][5 * (i) + j] >= 1) {
            return 1;
        }
    }
    return 0;
}

int isprojectpossible(int a, int F[][5], int dif[][5000], vector<int>& roll) {
    int W = 0;
    for (int i = 0; i < 5; i++) {
        if (F[a][i] == -1) {
            W++;
            continue;
        }

        int in = indexcheck(F, a, i, roll);if(in==-1) break;
        if (dif[a][5 * (in) + i] < -1) {
            break;
        }
        if (F[a][i] < -1) {
            break;
        }
        if (dif[a][5 * (in) + i] >= 0) {
            W++;
            continue;
        }
        if (checkeligibility(F, a, dif, roll) == 0)
            break;
    }
    if (W == 5) {
        return 1;
    } else {
        return 0;
    }
}//This function returns 1 if the project is possible

void projectnumber(int F[][5], int dif[][5000], int B[][5], vector<int>& roll, int M, int N) {
    int Num = 0;
    for (int i = 0; i < M; i++) {
        if (isprojectpossible(i, F, dif, roll) == 1) {
            Num++;
        }
    }
    if (Num > maxp) {
        maxp = Num;}
        for(int i=0;i<M;i++)
        { for(int j=0;j<5;j++){ if(B[i][j]==0) {F[i][j]= -1;}
                else F[i][j]=0; } }
        // cout << "the no. of projects are " << Num << endl;
    }//This function stores the max no.of projects possible in maxp variable
    


void processCombination(const vector<int>& combination, int F[][5], int dif[][5000], int B[][5], vector<int>& roll, int M, int Y, int N) {

      int c = 0;
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < 5; j++) {
            if (F[i][j] == 0) {
                if (c ==
                Y) {
                    break;
                }
                F[i][j] = combination[c];
                c++;
            }
        }
    }
    projectnumber(F, dif, B, roll, M, N);
}//This function assigns the permutedrollno.s in the array F

void generateCombinations(vector<int>& elements, int F[][5], int dif[][5000], int B[][5], vector<int>& roll, int M, int Y, int N) {
    // Sort the elements in ascending order
    sort(elements.begin(), elements.end());

    // Generate all permutations and call processCombination function
    do {
        processCombination(elements, F, dif, B, roll, M, Y, N);
    } while (next_permutation(elements.begin(), elements.end()));
}//This function generates all combinations of arrangements of rollno.s 

int main() {
    int N;cout<<"Enter the no.of students";
    cin >> N;
    int A[N][5];//stores the details of students
    vector<int> roll(N);
    cout<<"Enter the details of students";
    for (int i = 0; i < N; i++) {
        cin >> roll[i];
        for (int j = 0; j < 5; j++) {
            cin >> A[i][j];
        }
    }

    int M;cout<<"Enter the no.of projects";
    cin >> M;
    string S[M];//string of project names
    int B[M][5];//stores the details of projects
    cout<<"Enter the details of the projects";
    for (int i = 0; i < M; i++) {
        cin >> S[i];
        for (int j = 0; j < 5; j++) {
            cin >> B[i][j];
        }
    }

    int Count = 0;//Count is the total no.of roles available
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < 5; j++) {
            if (B[i][j] != 0) {
                Count++;
            }
        }
    }
 
    int k = 5 * N;
    int dif[M][5000];//It stores the diiference of skill level of student and required by the project

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < k; j++) {
            int f = j / 5;
            dif[i][j] = A[f][j % 5] - B[i][j % 5];
        }
    }

    int F[M][5];//it is the array in which combinations of rollno.s will be stored 
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < 5; j++) {
            if (B[i][j] == 0) {
                F[i][j] = -1;
            } else {
                F[i][j] = 0;
            }
        }
    }
std::vector<int> elements(N);
if(Count > N){for (int i = N; i <Count; i++) {
        roll.push_back(-2);}}
//the code works if the no.of roles required is same as theno.ofstudents applied(Count=N)
//Problem arises if Count > N.
//In order to compensate for the size is increased for roll vector       
    if (Count>N){elements.resize(Count);//same is done for element vector
    for (int i=0;i<Count;i++){elements[i]=roll[i];}}
else{
    for (int i = 0; i < N; i++) {
        elements[i] = roll[i];//elements stores the rollno.s which will pass on to the function which generate combinations
    }}

    generateCombinations(elements, F, dif, B, roll, M, Count, N);if(Count==0) maxp=0;
    cout << "No. of possible projects is: " << maxp << endl;
}//*Note to do run it for large numbers size of dif array should be changed