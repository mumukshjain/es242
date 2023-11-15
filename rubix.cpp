#include <cstdio>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cmath>
#include "queue.hpp"
#include <string>
#include <assert.h>

using namespace std;

//To run the program, the stack size will have to be increased'

enum colour{RED, GREEN, BLUE, WHITE, YELLOW, ORANGE};
struct cube {
    colour e[6][2][2];
};

struct block{
    int face ;
    int row ;
    int column ;
};

constexpr int fact(int i)
{
    int p = 1;
    for (int j = 2; j <= i; ++j) {
        p *= j;
    }
    return p;
}

block getBlockValues(const std::string& input) {
    block result;

    if (input == "front U right") {
        result.face = 0;
        result.row = 0;
        result.column = 1;
    } else if (input == "front U left") {
        result.face = 0;
        result.row = 0;
        result.column = 0;
    } else if (input == "front L right") {
        result.face = 0;
        result.row = 1;
        result.column = 1;
    } else if (input == "front L left") {
        result.face = 0;
        result.row = 1;
        result.column = 0;
    } else if (input == "bottom U right") {
        result.face = 4;
        result.row = 0;
        result.column = 1;
    } else if (input == "bottom U left") {
        result.face = 4;
        result.row = 0;
        result.column = 0;
    } else if (input == "bottom L right") {
        result.face = 4;
        result.row = 1;
        result.column = 1;
    } else if (input == "bottom L left") {
        result.face = 4;
        result.row = 1;
        result.column = 0;
    } else if (input == "right U right") {
        result.face = 1;
        result.row = 0;
        result.column = 1;
    } else if (input == "right U left") {
        result.face = 1;
        result.row = 0;
        result.column = 0;
    } else if (input == "right L right") {
        result.face = 1;
        result.row = 1;
        result.column = 1;
    } else if (input == "right L left") {
        result.face = 1;
        result.row = 1;
        result.column = 0;
    } else if (input == "left U right") {
        result.face = 2;
        result.row = 0;
        result.column = 1;
    } else if (input == "left U left") {
        result.face = 2;
        result.row = 0;
        result.column = 0;
    } else if (input == "left L right") {
        result.face = 2;
        result.row = 1;
        result.column = 1;
    } else if (input == "left L left") {
        result.face = 2;
        result.row = 1;
        result.column = 0;
    } else if (input == "top U right") {
        result.face = 3;
        result.row = 0;
        result.column = 1;
    } else if (input == "top U left") {
        result.face = 3;
        result.row = 0;
        result.column = 0;
    } else if (input == "top L right") {
        result.face = 3;
        result.row = 1;
        result.column = 1;
    } else if (input == "top L left") {
        result.face = 3;
        result.row = 1;
        result.column = 0;
    } else if (input == "back U right") {
        result.face = 5;
        result.row = 0;
        result.column = 1;
    } else if (input == "back U left") {
        result.face = 5;
        result.row = 0;
        result.column = 0;
    } else if (input == "back L right") {
        result.face = 5;
        result.row = 1;
        result.column = 1;
    } else if (input == "back L left") {
        result.face = 5;
        result.row = 1;
        result.column = 0;
    }

    return result;
}

void print_cube(const cube& c){

    const char face_arr[6][15] = {"Front Face", "Right Face", "Left Face", "Top Face", "Bottom Face", "Back Face"};
    const char* colour_names[] = {"RED", "GREEN", "BLUE", "WHITE", "YELLOW", "ORANGE"};
    for (int face=0; face<6; ++face){
        printf("%s\n", face_arr[face]);
        for(int row=0; row<2; ++row){
            for(int col=0; col<2; ++col){
                printf("%s ", colour_names[c.e[face][row][col]]);
            }
            printf("\n");
        }
        printf("\n");

    }
}

void swap(colour &a, colour &b){
    colour temp = a;
    a = b;
    b = temp;
}


void face_cycle(int face_idx, cube& o){
    swap(o.e[face_idx][0][0], o.e[face_idx][0][1]);
    swap(o.e[face_idx][0][0], o.e[face_idx][1][0]);
    swap(o.e[face_idx][1][0], o.e[face_idx][1][1]);
}

void face_cycle_dash(int face_idx, cube& o){
    swap(o.e[face_idx][0][1], o.e[face_idx][0][0]);
    swap(o.e[face_idx][0][1], o.e[face_idx][1][1]);
    swap(o.e[face_idx][1][1], o.e[face_idx][1][0]);
}

cube R(const cube& c){
    cube o = c;
    vector <string> L = {"front U right","top L right","top U right","back L right", "back U right", "bottom L right", "bottom U right", "front L right"};

    for (int i = 5 ; i >= 0 ; i -= 1){
        block next = getBlockValues(L[i + 2]) ;
        block prev = getBlockValues(L[i]) ;
        o.e[next.face][next.row][next.column] = o.e[prev.face][prev.row][prev.column] ;
    }
    o.e[0][0][1] = c.e[4][0][1] ;
    o.e[3][1][1] = c.e[0][1][1] ;

    face_cycle(1,o) ;
    return o;
}


cube U(const cube& c){
    cube o = c;
    vector <string> L = {"front U right","right U left","right U right","back L right","back L left","left U left","left U right","front U left"};

    for (int i = 0 ; i <= 5 ; i += 1){
        block next = getBlockValues(L[i]) ;
        block prev = getBlockValues(L[i + 2]) ;
        o.e[next.face][next.row][next.column] = o.e[prev.face][prev.row][prev.column] ;
    }
    o.e[2][0][1] = c.e[0][0][1] ;
    o.e[0][0][0] = c.e[1][0][0] ;
    face_cycle(3,o) ;
    return o;
}

cube U_dash(const cube& c){
    cube o = c;
    vector <string> L = {"front U right","right U left","right U right","back L right","back L left","left U left","left U right","front U left"};
    reverse(L.begin(),L.end()) ;
    for (int i = 0 ; i <= 5 ; i += 1){
        block next = getBlockValues(L[i]) ;
        block prev = getBlockValues(L[i + 2]) ;
        o.e[next.face][next.row][next.column] = o.e[prev.face][prev.row][prev.column] ;
    }
    o.e[0][0][1] = c.e[2][0][1] ;
    o.e[1][0][0] = c.e[0][0][0] ;
    face_cycle_dash(3,o) ;
    return o;
}

cube F(const cube& c){
    cube o = c;
    vector <string> L = {"top L right","right U left","right L left","bottom U right","bottom U left","left L right","left U right","top L left"} ;
    for (int i = 7 ; i >= 2 ; i --){
        block next = getBlockValues(L[i]) ;
        block prev = getBlockValues(L[i - 2]) ;
        o.e[next.face][next.row][next.column] = o.e[prev.face][prev.row][prev.column] ;
    }

    o.e[3][1][1] = c.e[2][0][1] ;
    o.e[1][0][0] = c.e[3][1][0] ;
    face_cycle(0,o) ;

    return o;

}

cube R_dash(const cube& c){
    cube o = c;
    vector <string> L = {"front U right","top L right","top U right","back L right", "back U right", "bottom L right", "bottom U right", "front L right"};
    reverse(L.begin(),L.end()) ;
    for (int i = 5 ; i >= 0 ; i -= 1){
        block next = getBlockValues(L[i + 2]) ;
        block prev = getBlockValues(L[i]) ;
        o.e[next.face][next.row][next.column] = o.e[prev.face][prev.row][prev.column] ;
    }
    o.e[4][0][1] = c.e[0][0][1]  ;
    o.e[0][1][1] = c.e[3][1][1] ;

    face_cycle_dash(1,o) ;
    return o;

}


cube F_dash(const cube& c){
    cube o = c;
    vector <string> L = {"top L right","right U left","right L left","bottom U right","bottom U left","left L right","left U right","top L left"} ;
    reverse(L.begin(),L.end()) ;
    for (int i = 7 ; i >= 2 ; i --){
        block next = getBlockValues(L[i]) ;
        block prev = getBlockValues(L[i - 2]) ;
        o.e[next.face][next.row][next.column] = o.e[prev.face][prev.row][prev.column] ;
    }

    o.e[2][0][1] = c.e[3][1][1] ;
    o.e[3][1][0] = c.e[1][0][0] ;
    face_cycle_dash(0,o) ;

    return o;
}

string enum_to_char(colour c){
    if (c == 0) {return "R" ;}
    if (c == 1) {return "G" ;}
    if (c == 2) {return "B" ;}
    if (c == 3) {return "W" ;}
    if (c == 4) {return "Y" ;}
    if (c == 5) {return "O" ;}
}

int check(cube& c,int cubelet){
    cube o = c ;
    string a_ ; string b_ ; string c_ ;
    if (cubelet == 0) {
        a_ = enum_to_char(c.e[0][0][0]);
        b_ = enum_to_char(c.e[2][0][1]);
        c_ = enum_to_char(c.e[3][1][0]);
    }
    else {
        a_ = enum_to_char(c.e[2][1][0]);
        b_ = enum_to_char(c.e[4][1][0]);
        c_ = enum_to_char(c.e[5][0][0]);
    }
    string a = a_ + b_ + c_ ;

    if (a == "YRB") {return 1 ;}
    if (a == "RBY") {return 2 ;}
    if (a == "BYR") {return 3 ;}
    if (a == "GWR") {return 4 ;}
    if (a == "WRG") {return 5 ;}
    if (a == "RGW") {return 6 ;}
    if (a == "BRW") {return 7 ;}
    if (a == "RWB") {return 8 ;}
    if (a == "WBR") {return 9 ;}
    if (a == "GOW") {return 10 ;}
    if (a == "OWG") {return 11 ;}
    if (a == "WGO") {return 12 ;}
    if (a == "YBO") {return 13 ;}
    if (a == "BOY") {return 14 ;}
    if (a == "OYB") {return 15 ;}
    if (a == "OBW") {return 16 ;}
    if (a == "BWO") {return 17 ;}
    if (a == "WOB") {return 18 ;}
    if (a == "GRY") {return 19;}
    if (a == "RYG") {return 20 ;}
    if (a == "YGR") {return 21 ;}
    if (a == "OGY") {return 22 ;}
    if (a == "GYO") {return 23 ;}
    if (a == "YOG") {return 24 ;}

}

int ord(cube& c){
    cube o = c ;
    int count = 0 , figure = 0  , var ;
    long long int ans = 0 ;
    while (count <= 7){
        switch (count){
            case 0 :
                var = check(o,0) ;
                ans += var * pow(10,figure) ;
                if (var / 10 == 0) figure ++ ;
                else figure += 2 ;
                count ++ ; continue ;

            case 1 :
                o = U(o) ;
                var = check(o,0) ;
                ans += var * pow(10,figure) ;
                if (var / 10 == 0) figure ++ ;
                else figure += 2 ;
                count ++ ;
                o = U_dash(o) ;
                continue ;
            case 2 :
                o = F(o) ;
                var = check(o,0) ;
                ans += var * pow(10,figure) ;
                if (var / 10 == 0) figure ++ ;
                else figure += 2 ;
                count ++ ;
                o = F_dash(o) ;
                continue ;
            case 3 :
                o = F(o) ; o = F(o) ;
                var = check(o,0) ;
                ans += var * pow(10,figure) ;
                if (var / 10 == 0) figure ++ ;
                else figure += 2 ;
                count ++ ;
                o = F_dash(o) ;
                o = F_dash(o) ;
                continue ;
            case 4 :
                var = check(o,1) ;
                ans += var * pow(10,figure) ;
                if (var / 10 == 0) figure ++ ;
                else figure += 2 ;
                count ++ ;
                continue ;
            case 5 :
                o = R_dash(o) ;
                o = U(o) ;
                o = U(o) ;
                var = check(o,0) ;
                ans += var * pow(10,figure) ;
                if (var / 10 == 0) figure ++ ;
                else figure += 2 ;
                count ++ ;
                o = U_dash(o) ;
                o = U_dash(o) ;
                o = R(o) ;
                continue ;

            case 6 :
                o = U_dash(o) ;
                var = check(o,0) ;
                ans += var * pow(10,figure) ;
                if (var / 10 == 0) figure ++ ;
                else figure += 2 ;
                count ++ ;
                o = U(o) ;
                continue ;

            case 7 :
                o = U(o) ;
                o = U(o) ;
                var = check(o,0) ;
                ans += var * pow(10,figure) ;
                if (var / 10 == 0) figure ++ ;
                else figure += 2 ;
                //cout << ans << ' ' << figure << endl ;
                count ++ ;
                o = U_dash(o) ;
                o = U_dash(o) ;
                continue ;

        }
    }
    return ans % 360007 ;
}

int similar_strings(string s1, string s2) {
    vector<int> L(256,0);
    vector<int> M(256,0);

    for (int i = 0; i < 3; i++) {
        L[s1[i]]++ ; M[s2[i]]++;
    }
    for (int i = 0; i < 256; i++) {
        if (L[i] != M[i]) {
            return false;
        }
    }
    return true;
}

vector<vector<vector<char>>> solved_cube = {{{'W','G','O'},{'W','O','B'},{'W','B','R'},{'W','R','G'}},
                                            {{'Y','B','O'},{'Y','O','G'},{'Y','G','R'},{'Y','R','B'}}
};

int is_valid(cube& c){
    cube o = c ;
    vector<vector<vector<string>>> L = {{{"front U left", "left U right", "top L left"},{"front U right", "top L right", "right U left"},{"front L right", "right L left", "bottom U right"},{"front L left", "bottom U left", "left L right"}},
                                        {{"back L right", "right U right", "top U right"},{"back L left", "top U left", "left U left"},{"back U left", "left L left","bottom L left"},{"back U right","bottom L right","right L right"}}};
    vector<vector<vector<char>>> orientation = {{{},{},{},{}},{{},{},{},{}}};
    for (int i = 0 ; i < 2 ; i ++){
        for (int j = 0 ; j < 4 ; j ++){
            for (int k = 0 ; k < 3 ; k ++){
                block a = getBlockValues(L[i][j][k]) ;
                colour b = c.e[a.face][a.row][a.column] ;
                if (b == RED) orientation[i][j].push_back('R') ;
                if (b == GREEN) orientation[i][j].push_back('G') ;
                if (b == BLUE) orientation[i][j].push_back('B') ;
                if (b == WHITE) orientation[i][j].push_back('W') ;
                if (b == ORANGE) orientation[i][j].push_back('O') ;
                if (b == YELLOW) orientation[i][j].push_back('Y') ;

            }
        }
    }
    int sum = 0 ;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 4; j++) {
            string cubelet = "" ;
            for (int k = 0; k < 3; k ++) {
                cubelet += orientation[i][j][k];
            }
            for (int k = 0; k < 2; ++k) {
                for (int l = 0; l < 4; ++l) {
                    string cubelet_in_solved = "";
                    for (int m = 0; m < 3; ++m) { cubelet_in_solved += solved_cube[k][l][m]; }
                    if (similar_strings(cubelet, cubelet_in_solved))
                    {
                        if (cubelet[0] == cubelet_in_solved[2]){ sum += 1 ;}
                        else if (cubelet[1] == cubelet_in_solved[2]){ sum += 2; }
                    }
                }
            }
        }
    }
    return sum % 3 == 0;
}

int is_solved(cube& o){
    for(size_t face=0; face<6; face++){
        colour sample = o.e[face][0][0];
        for(size_t row=0; row<2; row++){
            for(size_t col=0; col<2; col++){
                if(o.e[face][row][col] !=  sample){
                    return 0;
                }
            }
        }
    }
    return 1;
}

int is_it_same(const cube& a, cube& b){
    for (int i = 0 ; i < 6 ; i ++){
        for (int j = 0 ; j < 2 ; j ++){
            for (int k = 0 ; k < 2 ; k ++){
                if (a.e[i][j][k] != b.e[i][j][k]) return 0 ;
            }
        }
    }
    return 1 ;
}

int are_they_same(cube a, cube b){
    for (int i = 0 ; i < 6 ; i ++){
        for (int j = 0 ; j < 2 ; j ++){
            for (int k = 0 ; k < 2 ; k ++){
                if (a.e[i][j][k] != b.e[i][j][k]) return 0 ;
            }
        }
    }
    return 1 ;
}

struct cube_info{
    cube parent ;
    string move ;
    int visited = 0 ;
    int ord_ = -1;
    cube state ;
};

cube def = {{{{RED, RED}, {RED, RED}}, {{RED, RED}, {RED, RED}}, {{RED, RED}, {RED, RED}},
             {{RED, RED}, {RED, RED}}, {{RED, RED}, { RED,RED}}, {{RED, RED},{ RED, RED}}}};

vector<vector<cube_info>> hash_table(360010) ;

cube_info hash_function(int ord_a,const cube& c) {
    auto a = hash_table[ord_a];

    for (int i = 0 ; i < a.size() ; i ++){
        if (are_they_same(c,a[i].state)){return a[i] ;}
    }

    return {def,"", 0, -1};
}

vector<string> solve(const cube& unsolved){
    queue<cube, fact(10)> q ;
    cube c = unsolved ;
    enqueue(q, c) ;
    int c_ord = ord(c) ;
    hash_table[c_ord].push_back(cube_info{c, "", 1,c_ord,c}) ;

    while (!is_queue_empty(q)) {
        cube u = dequeue(q);
        if (is_solved(u)){
            vector<string> moves ;
            cube c_ = u ;
            int c_s = ord(c_) ;
            auto store = hash_function(c_s,c_) ;
            while (!is_it_same(unsolved,c_)){
                moves.push_back(store.move) ;
                c_ = store.parent ;
                c_s = ord(c_) ;
                store = hash_function(c_s,c_) ;
            }
            reverse(moves.begin(),moves.end()) ;
            return moves ;

        }
        cube R_ed = R(u) ;
        cube U_ed = U(u) ;
        cube F_ed = F(u) ;
        cube R_dash_ed = R_dash(u) ;
        cube U_dash_ed = U_dash(u) ;
        cube F_dash_ed = F_dash(u) ;
        cube R2_ed = R(R(u)) ;
        cube F2_ed = F(F(u)) ;
        cube U2_ed = U(U(u)) ;

        int s_R_ed = ord(R_ed) ;
        int s_U_ed = ord(U_ed) ;
        int s_F_ed = ord(F_ed) ;
        int s_R_dash_ed = ord(R_dash_ed) ;
        int s_U_dash_ed = ord(U_dash_ed) ;
        int s_F_dash_ed = ord(F_dash_ed) ;
        int s_R2_ed = ord(R2_ed) ;
        int s_U2_ed = ord(U2_ed) ;
        int s_F2_ed = ord(F2_ed) ;

        if (!hash_function(s_R_ed,R_ed).visited){
            hash_table[s_R_ed].push_back(cube_info{u, "R", 1,s_R_ed,R_ed}) ;
            enqueue(q, R_ed);
        }

        if (!hash_function(s_U_ed,U_ed).visited){
            hash_table[s_U_ed].push_back(cube_info{u, "U", 1,s_U_ed,U_ed}) ;
            enqueue(q, U_ed);
        }

        if (!hash_function(s_F_ed,F_ed).visited){
            hash_table[s_F_ed].push_back(cube_info{u, "F", 1,s_F_ed,F_ed}) ;
            enqueue(q, F_ed);
        }

        if (!hash_function(s_R_dash_ed,R_dash_ed).visited){
            hash_table[s_R_dash_ed].push_back(cube_info{u, "R'", 1,s_R_dash_ed,R_dash_ed}) ;
            enqueue(q, R_dash_ed);
        }

        if (!hash_function(s_U_dash_ed,U_dash_ed).visited){
            hash_table[s_U_dash_ed].push_back(cube_info{u, "U'", 1,s_U_dash_ed,U_dash_ed}) ;
            enqueue(q, U_dash_ed);
        }

        if (!hash_function(s_F_dash_ed,F_dash_ed).visited){
            hash_table[s_F_dash_ed].push_back(cube_info{u, "F'", 1,s_F_dash_ed,F_dash_ed}) ;
            enqueue(q, F_dash_ed);
        }


    }

    assert(0) ;
}


int main(){

    cube rubix2 = {{{{BLUE, YELLOW}, {YELLOW, GREEN}}, {{RED,ORANGE}, {WHITE,BLUE}}, {{GREEN,RED}, {ORANGE, BLUE}},
                    {{WHITE, GREEN}, {WHITE, GREEN}}, {{RED , RED}, { YELLOW,ORANGE}}, {{ BLUE,WHITE},{ ORANGE,YELLOW}}}};
    print_cube(rubix2) ;
    for (int i = 0; i < 360011; i++) {
        hash_table[i] = {};
    }
    if (!is_valid(rubix2)) {cout << "The cube is not solvable" ; return 0 ;}
    cout << "The cube is solvable" << endl ;
    vector<string> moves = solve(rubix2);
    for (auto& i : moves){cout << i << ' ' ;}

    return 0;
}