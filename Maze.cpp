#include <iostream>
#include <stack>
#include <vector>
#include <ctime>
using namespace std;

char c = (char)219;

bool positive = true;

stack<pair<int,int>> s;

vector<pair<int,int>> colline;
vector<pair<int,int>> rowline;

vector<pair<int,int>> visited;

vector<pair<int,int>> neighbour(int x, int y, int m , int n){
    vector<pair<int,int>> v;
    bool a = false, b = false, c = false, d = false;
    for(int i = 0;i<visited.size();i++){
        if (visited[i].first == x+1 && visited[i].second == y) {
            a = true;
        }
        else if (visited[i].first == x-1 && visited[i].second == y) {
            b = true;
        }
        else if (visited[i].first == x && visited[i].second == y+1) {
            c = true;
        }
        else if (visited[i].first == x && visited[i].second == y-1) {
            d = true;
        }    
    }
    if(!a && x+1<n){
        v.push_back({x+1,y});
    }
    if(!b && x-1>=0){
        v.push_back({x-1,y});
    }
    if(!c && y+1<m){
        v.push_back({x,y+1});
    }
    if(!d && y-1>=0){
        v.push_back({x,y-1});
    }

    return v;
}

int h = 0;
void start(int x,int y, int m , int n){

    vector<pair<int,int>> vv = neighbour(x,y,m,n);

    if (positive){
        s.push({x,y});
        visited.push_back({x,y});
    }

    if (vv.empty()){
        s.pop();
        if(s.empty()){
            return;
        }
        positive = false;



        start(s.top().first,s.top().second,m,n);
    }
    else{
        positive = true;
        int temp = rand()%vv.size();

        if (vv[temp].first - x == 1){
            colline.push_back({x,y});
        }
        else if(vv[temp].first - x == -1){
            colline.push_back({x-1,y});
        }
        else if(vv[temp].second - y == 1){
            rowline.push_back({x,y});
        }
        else if(vv[temp].second - y == -1){
            rowline.push_back({x,y-1});
        }

        x = vv[temp].first;
        y = vv[temp].second;

        start(x,y,m,n);
        
    }
}

void printmaze(int m, int n){
    vector<vector<bool>> pixelmatrix(3*m+1,vector<bool> (5*n+1,false));

    vector<pair<int,int>> negrowline;
    bool present = false;
    for(int i = 0;i<n;i++){
        for(int j =0 ;j<m;j++){
            for(int k = 0;k<rowline.size();k++){
                if(rowline[k].first == i && rowline[k].second == j){
                    present = true;
                }
            }
            if(!present){
                negrowline.push_back({i,j});
            }
            present = false;
        }
    }
    vector<pair<int,int>> negcolline;
    for(int i = 0;i<n;i++){
        for(int j =0 ;j<m;j++){
            for(int k = 0;k<colline.size();k++){
                if(colline[k].first == i && colline[k].second == j){
                    present = true;
                }
            }
            if(!present){
                negcolline.push_back({i,j});
            }
            present = false;
        }
    }

    for(int i = 0;i<negrowline.size();i++){
        int q = negrowline[i].first;
        int w = negrowline[i].second;
        for(int j = 0;j<=5;j++){
            pixelmatrix[3*w+3][5*q+j] = true;
        }
    }
    for(int i = 0;i<negcolline.size();i++){
        int q = negcolline[i].first;
        int w = negcolline[i].second;
        for(int j = 0;j<=3;j++){
            pixelmatrix[3*w+j][5*q+5] = true;
        }
    }

    for(int i = 0;i<5*n+1;i++){
        pixelmatrix[0][i] = true;
    }
    for(int i = 0;i<3*m+1;i++){
        pixelmatrix[i][0] = true;
    }


    for(int i = 0; i < 3*m+1; i++)
    {
        for(int j = 0; j < 5*n+1; j++)
        {
            if(pixelmatrix[i][j]){
                cout << c;
            }
            else{
                cout<<" ";;
            }
        }
        cout<< endl;
    }
}

int main(){

    int m, n;
    cout<<"Enter first dimension: ";
    cin>>m;
    cout<<"Enter second dimension: ";
    cin>>n;

    srand((unsigned int)time(NULL));
    start(0,0,m,n);
    printmaze(m,n);

    return 0;
}