#include <iostream>
#include <bits/stdc++.h>
#include <string>
#include <fstream>
#include <stdio.h>
#include <windows.h>
using namespace std;


#define address_lb "./Leaderboard.txt"  // address leaderboar file
#define address_help "./Help.txt"      // address help file

#define changeinp true
// true  ---> movements of players are applied according to their position
// false ---> movements of players are applied according to position of player 1


// for games classic2x and daliz2x
int nutP1 = 0, nutP2 = 0;  
// for games classic(4p) and daliz(4p)
int out_player = 1, rank1 = 1, rank2 = 1;
string name1th = " ", name2th = " ";   
// for games classic tournament and daliz tournament
int win_team1 = 0, win_team2 = 0, nut_team1 = 0, nut_team2 = 0, mood = 0, exit_tournament = false;   


void change_array(short* place, short x, short y, short number)
// change all elements of a array to a special value (short)
{
    for (int i = 0; i < y; i++)
        for (int j = 0; j < x; j++)
            place[i * x + j] = number;
}


bool check_input(string arr[], short number, string input)
// check input equal with any words in array (arr)
{
    for (int i = 0; i < number; i++)
        if (arr[i] == input)
            return true;

    return false;
}


string change_input(string move, short n, short np)
// input players 2-3-4 change to same input player 1
{
    if ((np == 2 && n == 2) || (np == 2 && n == 4)) // change input nut2 and nut4 when exist 2 players
    {
        if (move == "front" || move == "f")
            move = "b";
        else if (move == "back" || move == "b")
            move = "f";
        else if (move == "right" || move == "r")
            move = "l";
        else if (move == "left" || move == "l")
            move = "r";

        if (move == "ofrontright" || move == "ofr")
            move = "obl";
        else if (move == "ofrontleft" || move == "ofl")
            move = "obr";
        else if (move == "obackright" || move == "obr")
            move = "ofl";
        else if (move == "obackleft" || move == "obl")
            move = "ofr";
        else if (move == "orightfront" || move == "orf")
            move = "olb";
        else if (move == "orightback" || move == "orb")
            move = "olf";
        else if (move == "oleftfront" || move == "olf")
            move = "orb";
        else if (move == "oleftback" || move == "olb")
            move = "orf";
    }

    else if (n == 2)  // change input nut2 when exist 3-4 players
    {
        if (move == "front" || move == "f")
            move = "l";
        else if (move == "back" || move == "b")
            move = "r";
        else if (move == "right" || move == "r")
            move = "f";
        else if (move == "left" || move == "l")
            move = "b";

        else if (move == "ofrontright" || move == "ofr")
            move = "olf";
        else if (move == "ofrontleft" || move == "ofl")
            move = "olb";
        else if (move == "obackright" || move == "obr")
            move = "orf";
        else if (move == "obackleft" || move == "obl")
            move = "orb";
        else if (move == "orightfront" || move == "orf")
            move = "ofl";
        else if (move == "orightback" || move == "orb")
            move = "ofr";
        else if (move == "oleftfront" || move == "olf")
            move = "obl";
        else if (move == "oleftback" || move == "olb")
            move = "obr";
    }

    else if (n == 3 && np != 2)  // change input nut3 when exist 3-4 players
    {
        if (move == "front" || move == "f")
            move = "b";
        else if (move == "back" || move == "b")
            move = "f";
        else if (move == "right" || move == "r")
            move = "l";
        else if (move == "left" || move == "l")
            move = "r";

        if (move == "ofrontright" || move == "ofr")
            move = "obl";
        else if (move == "ofrontleft" || move == "ofl")
            move = "obr";
        else if (move == "obackright" || move == "obr")
            move = "ofl";
        else if (move == "obackleft" || move == "obl")
            move = "ofr";
        else if (move == "orightfront" || move == "orf")
            move = "olb";
        else if (move == "orightback" || move == "orb")
            move = "olf";
        else if (move == "oleftfront" || move == "olf")
            move = "orb";
        else if (move == "oleftback" || move == "olb")
            move = "orf";
    }
    
    else if (n == 4)  // change input nut4 when exist 4 players
    {
        if (move == "front" || move == "f")
            move = "r";
        else if (move == "back" || move == "b")
            move = "l";
        else if (move == "r" || move == "r")
            move = "b";
        else if (move == "left" || move == "l")
            move = "f";
    
        if (move == "ofrontright" || move == "ofr")
            move = "orb";
        else if (move == "ofrontleft" || move == "ofl")
            move = "orf";
        else if (move == "obackright" || move == "obr")
            move = "olb";
        else if (move == "obackleft" || move == "obl")
            move = "olf";
        else if (move == "orightfront" || move == "orf")
            move = "obr";
        else if (move == "orightback" || move == "orb")
            move = "obl";
        else if (move == "oleftfront" || move == "olf")
            move = "ofr";
        else if (move == "oleftback" || move == "olb")
            move = "ofl";
    }

    return move;
}


bool check_input_wall(string move, short type)
// check input for put wall in correct [type=1 horizontal , type=2 vertical]
{
    if ((type == 1 && move[0]  == 95) || (type == 2 && move[0] == 124))
    {
        if (move[1] <= 57 && move[1] >= 49 && 
            move[2] <= 57 && move[2] >= 49 &&
            move[3] <= 105 && move[3] >= 97 && 
            move[4] <= 105 && move[4] >= 97 &&
            move[1] + 1 == move[2] &&
            move[3] + 1 == move[4] &&
            move.length() == 5)
        {
            return true;
        }

        else if (move[1] <= 105 && move[1] >= 97 && 
                move[2] <= 105 && move[2] >= 97 &&
                move[3] <= 57 && move[3] >= 49 && 
                move[4] <= 57 && move[4] >= 49 && 
                move[1] + 1 == move[2] &&
                move[3] + 1 == move[4] &&
                move.length() == 5)
        {
            return true;
        }
    }

    return false;
}


bool check_not_wall(short m, short x, short y, short* place)
// check not exist wall front=1 , back=2 , right=3 , left=4 nut while move 
{
    if (m == 1)  // front
    {
        if (y != 16 && place[(y+1) * 17 + x] == 0)
            return true;
    }
    if (m == 2)  // back
    {
        if (y != 0 && place[(y-1) * 17 + x] == 0)
            return true;
    }
    if (m == 3)  // right
    {
        if (x != 16 && place[y * 17 + x+1] == 0)
            return true;
    }
    if (m == 4)  // left
    {
        if (x != 0 && place[y * 17 + x-1] == 0)
            return true;
    }
    return false;
}


bool check_put_wall(short* place, short x, short y, short type)
// check not exist wall in place we want put a new wall [type=1 horizontal , type=2 vertical]
{
    if (type == 1 && place[y * 17 + x] != -1 && place[y * 17 + (x + 2)] != -1)  // horizontal
        return true;
    else if (type == 2 && place[y * 17 + x] != -1 && place[(y + 2) * 17 + x] != -1)  // ventical
        return true;
    return false;
}


bool check_close_wall(short* placee, short n, short np, short inx, short iny, short types)
// check new wall donn't close players' ways to reach end board or flag [type=1 horizontal , type=2 vertical]
{   
    short x = 20, y = 20, xp = 20, yp = 20;
    short place[289];
    for (int i1 = 0; i1 < 17; i1++)  // copy board game and find place nut and flag
        for (int i2 = 0; i2 < 17; i2++)
        { 
            place[i1 * 17 + i2] = placee[i1 * 17 + i2];
            if (place[i1 * 17 + i2] == n)
            {
                x = i2;
                y = i1;
            }
            if (place[i1 * 17 + i2] == 88)
            {
                xp = i2;
                yp = i1;
            }
        }

    for (int j = 0; j < 289; j += 2)  // delet nuts of players and flag in board
    {
        if (place[j] == 1)
            place[j] = 0;
        if (place[j] == 2)
            place[j] = 0;
        if (place[j] == 3)
            place[j] = 0;
        if (place[j] == 4)
            place[j] = 0;
        if (place[j] == 88)
            place[j] = 0;
    }

    if (types == 1)  // put a new wall horizontal
    { 
        place[iny * 17 + inx] = -1;
        place[iny * 17 + (inx + 2)] = -1;
    }
    else if (types == 2)  // put a new wall vertical
    {
        place[iny * 17 + inx] = -1;
        place[(iny + 2) * 17 + inx] = -1;
    }

    if (x == 20)
        return false;

    short len = 2, m, len1;
    short arr1[200] = {x, y};
    short arr[200];
    while (true)
    {
        m = 0; 
        len1 = 0;
        for (int k = 0; k < 200; k++)
            arr[k] = arr1[k];

        for (int l = 0; l < len; l += 2)
        {
            x = arr[l];
            y = arr[l+1];

            if (np == 2 && n == 1 && y == 16)
                return false;
            else if (np == 2 && n == 3 && y == 16)
                return false;
            else if (np == 2 && n == 2 && y == 0)
                return false;
            else if (np == 2 && n == 4 && y == 0)
                return false;
            else if (np == 2 && x == xp && y == yp)
                return false;
            else if (np == 3 && x == xp && y == yp)
                return false;
            else if (np == 4 && n == 1 && y == 16)
                return false;
            else if (np == 4 && n == 2 && x == 0)
                return false;
            else if (np == 4 && n == 3 && y == 0)
                return false;
            else if (np == 4 && n == 4 && x == 16)
                return false;
            else if (np == 4 && x == xp && y == yp)
                return false;
                
            if (check_not_wall(1, x, y, place) && place[(y + 2) * 17 + x] == 0)  // front
            {
                arr1[m++] = x;
                arr1[m++] = y + 2;
                len1 += 2;
                place[(y + 2) * 17 + x] = 1;
            }
            if (check_not_wall(2, x, y, place) && place[(y - 2) * 17 + x] == 0)  // back
            {
                arr1[m++] = x;
                arr1[m++] = y - 2;
                len1 += 2;
                place[(y - 2) * 17 + x] = 1;
            }
            if (check_not_wall(3, x, y, place) && x != 16 && place[y * 17 + (x + 2)] == 0)  // right
            {
                arr1[m++] = x + 2;
                arr1[m++] = y;
                len1 += 2;
                place[y * 17 + (x + 2)] = 1;
            }
            if (check_not_wall(4, x, y, place) && x != 0 && place[y * 17 + (x - 2)] == 0)  // left
            {
                arr1[m++] = x - 2;
                arr1[m++] = y;
                len1 += 2;
                place[y * 17 + (x - 2)] = 1;
            }
        }

        if (len1 == 0)
            break;
        len = len1;
    }

    return true;
}


void show_map(short* place)
// show the board game
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    short z = 9;

    SetConsoleTextAttribute(h, 11);
    cout << "------------------------------------|" << endl;
    SetConsoleTextAttribute(h, 7);
    for (int i = 16; i >= 0; i--)
    {
        if (i % 2 == 0)
        {
            SetConsoleTextAttribute(h, 11);
            cout << "|   ";
            SetConsoleTextAttribute(h, 7);
        }
        for (int j = 0; j < 17; j++)
        {
            SetConsoleTextAttribute(h, 14);
            if (place[i * 17 + j] == 1)  // show place player1
                cout << "\b\b1 ";
            if (place[i * 17 + j] == 2)  // show place player2
                cout << "\b\b2 ";
            if (place[i * 17 + j] == 3)  // show place player3
                cout << "\b\b3 ";
            if (place[i * 17 + j] == 4)  // show place player4
                cout << "\b\b4 ";
            SetConsoleTextAttribute(h, 7);

            if (place[i * 17 + j] == 88)  // show flag
            { 
                SetConsoleTextAttribute(h, 2);  
                cout << "\b\bX ";
                SetConsoleTextAttribute(h, 7);
            }

            if (place[i * 17 + j] == 0)  // show white walls (open)
            {
                if (i % 2 == 1 && j % 2 == 0)
                    cout << "****";
                else if (i % 2 == 0 && j % 2 == 1)
                    cout << "|   ";
            }
            if (place[i * 17 + j] == -1)  // show red walls (close)
            {
                 if (i % 2 == 1 && j % 2 == 0)
                {
                    SetConsoleTextAttribute(h, 4);
                    cout << "****";
                    SetConsoleTextAttribute(h, 7);
                }
                else if (i % 2 == 0 && j % 2 == 1)
                {
                    SetConsoleTextAttribute(h, 4);
                    cout << "|   ";
                    SetConsoleTextAttribute(h, 7);
                }
            } 
        }
        SetConsoleTextAttribute(h, 11);
        if (i % 2 == 0)
            cout << "| " << z-- << endl;
        else
            cout << "|---" << endl;
        SetConsoleTextAttribute(h, 7);
    }
    SetConsoleTextAttribute(h,11);
    cout << "------------------------------------|" << endl;
    cout << "  a | b | c | d | e | f | g | h | i  " << endl << endl;
    SetConsoleTextAttribute(h, 7);
}


bool move_normal_jumping(short* place, short np, short n, short* px, short* py, string move)
// save movements normal or jumping in board game and check these movements can be done
{
    short y1 = 0, y2 = 0, y3 = 0, y4 = 0, x1 = 0, x2 = 0, x3 = 0, x4 = 0, side;
    short py_first = *py, px_first = *px;

    if (move == "front" || move == "f")
    {
        side = 1;
        y1 = 2;
        y2 = 4;
        y3 = 6;
        y4 = 8;
    }
    else if (move == "back" || move == "b")
    {
        side = 2;
        y1 = -2;
        y2 = -4;
        y3 = -6;
        y4 = -8;
    }
    else if (move == "right" || move == "r")
    {
        side = 3;
        x1 = 2;
        x2 = 4;
        x3 = 6;
        x4 = 8;
    }
    else if (move == "left" || move == "l")
    {
        side = 4;
        x1 = -2;
        x2 = -4;
        x3 = -6;
        x4 = -8;
    }

    if (check_not_wall(side, *px, *py, place))
    {
        if (place[(*py + y1) * 17 + (*px + x1)] == 0)  // normal
        {
            place[*py * 17 + *px] = 0;
            place[(*py += y1) * 17 + (*px += x1)] = n;
        }
        else if (check_not_wall(side, *px+x1, *py+y1, place))
        {
            if (place[(*py + y2) * 17 + (*px + x2)] == 0)  // jumping 1
            {
                place[*py * 17 + *px] = 0;
                place[(*py += y2) * 17 + (*px += x2)] = n;
            }
            else if (check_not_wall(side, *px+x2, *py+y2, place))
            {
                if (place[(*py + y3) * 17 + (*px + x3)] == 0)  // jumping 2
                {
                    place[*py * 17 + *px] = 0;
                    place[(*py += y3) * 17 + (*px += x3)] = n;
                }
                else if (check_not_wall(side, *px+x3, *py+y3, place))
                {
                    if (place[(*py + y4) * 17 + (*px + x4)] == 0)  // jumping 3
                    {
                        place[*py * 17 + *px] = 0;
                        place[(*py += y4) * 17 + (*px += x4)] = n;
                    }
                }

                // reach to end board with jumping 3
                else if (n == 1 && side == 1 && *py == 10)
                {
                    place[*py * 17 + *px] = 0;
                    *py = 18;  
                } 
                else if (n == 2 && np == 2 && side == 2 && *py == 6)
                {
                    place[*py * 17 + *px] = 0;
                    *py = -2;  
                }
                else if (n == 2 && np != 2 && side == 4 && *px == 6)
                {
                    place[*py * 17 + *px] = 0;
                    *px = -2;
                }  
                else if (n == 3 && np == 2 && side == 1 && *py == 10)
                {
                    place[*py * 17 + *px] = 0;
                    *py = 18;  
                }
                else if (n == 4 && np == 2 && side == 2 && *py == 6)
                {
                    place[*py * 17 + *px] = 0;
                    *py = -2;  
                }
                else if (n == 4 && np != 2 && side == 3 && *px == 10)
                {
                    place[*py * 17 + *px] = 0;
                    *px = 18;  
                }
            }

            // reach to end board with jumping 2
            else if (n == 1 && side == 1 && *py == 12)
            {
                place[*py * 17 + *px] = 0;
                *py = 18;  
            } 
            else if (n == 2 && np == 2 && side == 2 && *py == 4)
            {
                place[*py * 17 + *px] = 0;
                *py = -2;  
            }
            else if (n == 2 && np != 2 && side == 4 && *px == 4)
            {
                place[*py * 17 + *px] = 0;
                *px = -2;
            }  
            else if (n == 3 && np == 2 && side == 1 && *py == 12)
            {
                place[*py * 17 + *px] = 0;
                *py = 18;  
            }
            else if (n == 3 && np != 2 && side == 2 && *py == 4)
            {
                place[*py * 17 + *px] = 0;
                *py = -2;  
            }
            else if (n == 4 && np == 2 && side == 2 && *py == 4)
            {
                place[*py * 17 + *px] = 0;
                *py = -2;  
            }
            else if (n == 4 && np != 2 && side == 3 && *px == 12)
            {
                place[*py * 17 + *px] = 0;
                *px = 18;  
            }
        }

        // reach to end board with jumping 1
        else if (n == 1 && side == 1 && *py == 14)
        {
            place[*py * 17 + *px] = 0;
            *py = 18;  
        }
        else if (n == 2 && np == 2 && side == 2 && *py == 2)
        {
            place[*py * 17 + *px] = 0;
            *py = -2;  
        }
        else if (n == 2 && np != 2 && side == 4 && *px == 2)
        {
            place[*py * 17 + *px] = 0;
            *px = -2;
        }  
        else if (n == 3 && np == 2 && side == 1 && *py == 14)
        {
            place[*py * 17 + *px] = 0;
            *py = 18;  
        }
        else if (n == 3 && np != 2 && side == 2 && *py == 2)
        {
            place[*py * 17 + *px] = 0;
            *py = -2;  
        }
        else if (n == 4 && np == 2 && side == 2 && *py == 2)
        {
            place[*py * 17 + *px] = 0;
            *py = -2;  
        }
        else if (n == 4 && np != 2 && side == 3 && *px == 14)
        {
            place[*py * 17 + *px] = 0;
            *px = 18;  
        }
    }
    else
    {
        cout << "You Cann't This Move ! TryAgain" << endl;
        return false;
    }

    if (*py != py_first || *px != px_first)
        return true;
    
    return false;
}


bool move_diagonal(short* place, short np, short n, short* px, short* py, string move)
// save movements diagonal in board game and check these movements can be done
{
    short x1 = 0, x2 = 0, x3 = 0, y1 = 0, y2 = 0, y3 = 0, side1, side2, m1, m2, m3, n1, n2, n3;

    if (move == "ofr"  || move == "ofrontright")
        side1 = 1, side2 = 3, y1 = 2, y2 = 4, y3 = 6, n1 = 2, n2 = 4, n3 = 6, m1 = 2, m2 = 2, m3 = 2;   
    else if (move == "ofl"  || move == "ofrontleft")
        side1 = 1, side2 = 4, y1 = 2, y2 = 4, y3 = 6, n1 = 2, n2 = 4, n3 = 6, m1 = -2, m2 = -2, m3 = -2;
    else if (move == "obr"  || move == "obackright")
        side1 = 2, side2 = 3, y1 = -2, y2 = -4, y3 = -6, n1 = -2, n2 = -4, n3 = -6, m1 = 2, m2 = 2, m3 = 2;
    else if (move == "obl"  || move == "obackleft")
        side1 = 2, side2 = 4, y1 = -2, y2 = -4, y3 = -6, n1 = -2, n2 = -4, n3 = -6, m1 = -2, m2 = -2, m3 = -2;
    else if (move == "orf"  || move == "orightfront")
        side1 = 3, side2 = 1, x1 = 2, x2 = 4, x3 = 6, n1 = 2, n2 = 2, n3 = 2, m1 = 2, m2 = 4, m3 = 6;
    else if (move == "orb"  || move == "orightback")
        side1 = 3, side2 = 2, x1 = 2, x2 = 4, x3 = 6, n1 = -2, n2 = -2, n3 = -2, m1 = 2, m2 = 4, m3 = 6;
    else if (move == "olf"  || move == "oleftfront")
        side1 = 4, side2 = 1, x1 = -2, x2 = -4, x3 = -6, n1 = 2, n2 = 2, n3 = 2, m1 = -2, m2 = -4, m3 = -6;
    else if (move == "olb"  || move == "oleftback")
        side1 = 4, side2 = 2, x1 = -2, x2 = -4, x3 = -6, n1 = -2, n2 = -2, n3 = -2, m1 = -2, m2 = -4, m3 = -6;


    if (check_not_wall(side1, *px, *py, place) &&
        place[(*py + y1) * 17 + (*px + x1)] != 0)
    {
        if (!check_not_wall(side1, *px+x1, *py+y1, place))
        {
            if (check_not_wall(side2, *px+x1, *py+y1, place))  // 2 nuts together
            {
                place[*py * 17 + *px] = 0;
                place[(*py += n1) * 17 + (*px += m1)] = n;
                return true;
            }
            else
            {
                cout << "You Cann't This Move ! TryAgain" << endl;
                return false;
            }
        }
        else if (place[(*py + y2) * 17 + (*px + x2)] != 0)
        {
            if (!check_not_wall(side1, *px+x2, *py+y2, place))
            {
                if ((check_not_wall(side2, *px+x2, *py+y2, place)) &&  // 3 nuts toghether
                    (place[(*py + n2) * 17 + (*px + m2)] == 0))  
                {
                    place[*py * 17 + *px] = 0;
                    place[(*py += n2) * 17 + (*px += m2)] = n;
                    return true;
                }
                else
                {
                    cout << "You Cann't This Move ! TryAgain" << endl;
                    return false;
                }
            }
            else if (place[(*py + y3) * 17 + (*px + x3)] != 0)
            {
                if (!check_not_wall(side1, *px+x3, *py+y3, place))
                {
                    if ((check_not_wall(side2, *px+x3, *py+y3, place)) &&  // 4 nuts toghether
                        (place[(*py + n3) * 17 + (*px + m3)] == 0))  
                    {
                        place[*py * 17 + *px] = 0;
                        place[(*py += n3) * 17 + (*px += m3)] = n;
                        return true;
                    }
                    else
                    {
                        cout << "You Cann't This Move ! TryAgain" << endl;
                        return false;
                    } 
                }
                else
                {
                    cout << "You Cann't This Move ! TryAgain" << endl;
                    return false;
                }
            }
            else
            {
                cout << "You Cann't This Move ! TryAgain" << endl;
                return false;
            }
        }
        else
        {
            cout << "You Cann't This Move ! TryAgain" << endl;
            return false;
        }
    }
    else
    {
        cout << "You Cann't This Move ! TryAgain" << endl;
        return false;
    } 
        
    return false;
}


bool put_wall(short* place, short np, short type, short* number_wall, string move)
// put a wall in board game [type=1 horizontal and type=2 vertical]
{
    short index_wall_x, index_wall_y;

    if (type == 1)
    {
        if (move[1] <= 57 && move[0] >= 49)  // firs number
        {
            index_wall_x = ((move[3] - 97) * 2);
            index_wall_y = (((move[1] - 49) * 2) + 1);
        }
        else  // first char
        {
            index_wall_x = ((move[1] - 97) * 2);
            index_wall_y = (((move[3] - 49) * 2) + 1);
        }

        if (*number_wall == 0)  // check exist wall for player
        {
            cout << "Your Walls Is Over !" << endl;
            return false;
        }
        else if (!check_put_wall(place, index_wall_x, index_wall_y, 1))
        {
            cout << "There Is A Wall This Place ! TryAgain" << endl;
            return false;
        }
        else if (check_close_wall(place, 1, np, index_wall_x, index_wall_y, 1) ||
                check_close_wall(place, 2, np, index_wall_x, index_wall_y, 1) ||
                check_close_wall(place, 3, np, index_wall_x, index_wall_y, 1) ||
                check_close_wall(place, 4, np, index_wall_x, index_wall_y, 1))
        {
            cout << "You Close The Way ! TryAgain" << endl;
            return false;
        }
        
        place[index_wall_y * 17 + index_wall_x] = -1;
        place[index_wall_y * 17 + (index_wall_x + 2)] = -1;
        *number_wall -= 1;
        return true; 
    }

    else if (type == 2)
    {
        if (move[1] <= 57 && move[0] >= 49)  // first number
        {
            index_wall_x = (((move[3] - 97) * 2) + 1);
            index_wall_y = ((move[1] - 49) * 2);
        }
        else  // first char
        {
            index_wall_x = (((move[1] - 97) * 2) + 1);
            index_wall_y = ((move[3] - 49) * 2);
        }

        if (*number_wall == 0)  // check exist wall for player
        {
            cout << "Your Walls Is Over !" << endl;
            return false;
        }
        else if (!check_put_wall(place, index_wall_x, index_wall_y, 2))
        {
            cout << "There Is A Wall This Place ! TryAgain" << endl;
            return false;
        }
        else if (check_close_wall(place, 1, np, index_wall_x, index_wall_y, 2) ||
                check_close_wall(place, 2, np, index_wall_x, index_wall_y, 2) ||
                check_close_wall(place, 3, np, index_wall_x, index_wall_y, 2) ||
                check_close_wall(place, 4, np, index_wall_x, index_wall_y, 2))
        {
            cout << "You Close The Way ! TryAgain" << endl;
            return false;
        }
            
        place[index_wall_y * 17 + index_wall_x] = -1;
        place[(index_wall_y + 2) * 17 + index_wall_x] = -1;
        *number_wall -= 1;
        return true;
    }

    return false;
}


bool check_name(string name, int len)
// check name of player is correct [name must have maximum of 20 char and donn't have any char (a-b) (0-9) ( _ ) ]
{
    char n;
    if (len <= 20 && name[0] <= 90 && name[0] >= 65)
    {
        for (int i = 1; i < len; i++)
        {
            n = name[i];
            if ((n <= 90 && n >= 65) || (n <= 57 && n >= 48) || (n == 95))
                continue;

            return false;
        }
        if (name == name1th || name == name2th)  // name exist in players this game
        {
            cout << "This Name Exist In Names Players This Game" << endl;
            return false;
        }
        return true;
    }
    return false;
}


int add_to_lb(int n, int score)
// add new names and their scores in leaderboard , update the scores names befor exist in leaderboard
{
    string name = " ";
    string name1;
    int score1, score2 = score;
    int i = 0;
    bool cond = true;
    string names[100];
    int scores[100];

    do  // check name is correct
    {
        if (name != " ")
            cout << "Name Must Have Maximum Of 20 Char And Don't Have Any Char [a-b] [0-9] [ _ ]" << endl;

        if (mood == 0)
            cout << "What's Your Name Player " << n << " :  ";
        else 
            cout << "What's Your Name Team , Team " << n << " :  ";
        cin >> name;
        transform(name.begin(), name.end(), name.begin(), ::toupper);

    } while (!check_name(name, name.length()));

    if (name1th == " ")
        name1th = name;
    else if (name2th == " ")
        name2th = name;
    
    ifstream lb1 (address_lb);
    if (!lb1.is_open())
        cout << "This address Not Exist" << endl;

    while(lb1 >> name1 >> score1)  // read names and scores in leaderboard
    {
        if (name == name1)
        {
            score1 += score;
            score = score1;
            cond = false;
        }
        names[i] = name1;
        scores[i++] = score1;
    }
    if (cond)
    {
        names[i] = name;
        scores[i++] = score;
    }
    lb1.close();

    ofstream lb2 (address_lb);  // write names and scores in leaderboard
    for (int k = 0; k < i; k++)
        lb2 << names[k] << "\t\t" << scores[k] << "\n";
    
    lb2.close();

    cout << "You Got " << score2 << " Scores !!!" << endl;
    cout << "Your Score Is : " << score << endl;

    return 1;
}


bool winner(short* place, short np, short n, short* px, short* py, short answer)
// determines the player who wins
{
    short xp = 20, yp = 20, type = 2;
    if (answer)
        system("clear");

    for (int i = 0; i < 17; i += 2)  // declares place of flag
    {
        for (int j = 0; j < 17; j += 2)
        {
            if (place[i * 17 + j] == 88)
            {
                xp = j;
                yp = i;
            }
            if (place[i * 17 + j] == 3 || place[i * 17 + j] == 4 || nutP1 + nutP2 == 1)
                type = 4;
        }
    }

    if (np == 2 && type == 2)  // 2-players  2-nuts
    {
        if (n == 1 && *py >= 16)
        {
            cout << "Player 1 Is Winner ........................................." << endl;
            return 1;
        }
        else if (n == 2 && *py <= 0)
        {
            cout << "Player 2 Is Winner ........................................." << endl;
            return 1;
        }
        else if ((*py == yp && *px+2 == xp && check_not_wall(3, *px, *py, place)) || 
            (*py == yp && *px-2 == xp && check_not_wall(4, *px, *py, place)) || 
            (*px == xp && *py+2 == yp && check_not_wall(1, *px, *py, place)) || 
            (*px == xp && *py-2 == yp && check_not_wall(2, *px, *py, place)))
        {
            cout << "Player " << n << " Is Winner ........................................." << endl;
            return 1;
        }
    }
    else if (np == 2 && type == 4)  // 2-players  4-nuts
    {
        if ((n == 1 || n == 3) && (*py >= 16) && (nutP1 > 0))
        {
            cout << "Player 1 Is Winner ........................................." << endl;
            return 1;
        }
        else if ((n == 1 || n == 3) && (*py >= 16))
        {
            nutP1  = n;
            place[*py * 17 + *px] = 0;
            cout << "Nut " << n << " Is Reach End Board ..." << endl;
            return 0;
        }
        else if ((n == 2 || n == 4) && (*py <= 0) && (nutP2 > 0))
        {
            cout << "Player 2 Is Winner ........................................." << endl;
            return 1;
        }
        else if ((n == 2 || n == 4) && (*py <= 0))
        {
            nutP2  = n;
            place[*py * 17 + *px] = 0;
            cout << "Nut " << n << " Is Reach End Board ..." << endl;
            return 0;
        }
        else if ((n == 1 || n == 3) && nutP1 > 0 && 
                (*py == yp && *px+2 == xp && check_not_wall(3, *px, *py, place)) || 
                (*py == yp && *px-2 == xp && check_not_wall(4, *px, *py, place)) || 
                (*px == xp && *py+2 == yp && check_not_wall(1, *px, *py, place)) || 
                (*px == xp && *py-2 == yp && check_not_wall(2, *px, *py, place)))
        {
            cout << "Player 1 Is Winner ........................................." << endl;
            return 1;
        }
        else if ((n == 1 || n == 3) && 
                (*py == yp && *px+2 == xp && check_not_wall(3, *px, *py, place)) || 
                (*py == yp && *px-2 == xp && check_not_wall(4, *px, *py, place)) || 
                (*px == xp && *py+2 == yp && check_not_wall(1, *px, *py, place)) || 
                (*px == xp && *py-2 == yp && check_not_wall(2, *px, *py, place)))
        {
            nutP1  = n;
            place[*py * 17 + *px] = 0;
            cout << "Nut " << n << " Is Reach Flag ..." << endl;
            return 0;
        }
        else if ((n == 2 || n == 4) && nutP2 > 0 && 
                (*py == yp && *px+2 == xp && check_not_wall(3, *px, *py, place)) || 
                (*py == yp && *px-2 == xp && check_not_wall(4, *px, *py, place)) || 
                (*px == xp && *py+2 == yp && check_not_wall(1, *px, *py, place)) || 
                (*px == xp && *py-2 == yp && check_not_wall(2, *px, *py, place)))
        {
            cout << "Player 2 Is Winner ........................................." << endl;
            return 1;
        }
        else if ((n == 2 || n == 4) && 
                (*py == yp && *px+2 == xp && check_not_wall(3, *px, *py, place)) || 
                (*py == yp && *px-2 == xp && check_not_wall(4, *px, *py, place)) || 
                (*px == xp && *py+2 == yp && check_not_wall(1, *px, *py, place)) || 
                (*px == xp && *py-2 == yp && check_not_wall(2, *px, *py, place)))
        {
            nutP2  = n;
            place[*py * 17 + *px] = 0;
            cout << "Nut " << n << " Is Reach Flag ..." << endl;
            return 0;
        }
    }

    else if(np == 3)  // 3-players  3-nuts
    {
        if ((*py == yp && *px+2 == xp && check_not_wall(3, *px, *py, place)) || 
            (*py == yp && *px-2 == xp && check_not_wall(4, *px, *py, place)) || 
            (*px == xp && *py+2 == yp && check_not_wall(1, *px, *py, place)) || 
            (*px == xp && *py-2 == yp && check_not_wall(2, *px, *py, place)))
        {
            cout << "Player " << n << " Is Winner ........................................." << endl;
            return 1;
        }
    }

    else if (np == 4 && mood == 0)  // 4-players  normal
    {
        if (n == 1 && *py >= 16)
        {
            cout << "Player 1 Become " << rank1 << "th ........................................." << endl;
            out_player *= 2;
            place[*py * 17 + *px] = 0;
            if (++rank1 == 4)
                return 1;
            return 0;
        }
        else if (n == 2 && *px <= 0)
        {
            cout << "Player 2 Become " << rank1 << "th ........................................." << endl;
            out_player *= 3;
            place[*py * 17 + *px] = 0;
            if (++rank1 == 4)
                return 1;
            return 0;
        }
        else if (n == 3 && *py <= 0)
        {
            cout << "Player 3 Become " << rank1 << "th ........................................." << endl;
            out_player *= 5;
            place[*py * 17 + *px] = 0;
            if (++rank1 == 4)
                return 1;
            return 0;
        }
        else if (n == 4 && *px >= 16)
        {
            cout << "Player 4 Become " << rank1 << "th ........................................." << endl;
            out_player *= 7;
            place[*py * 17 + *px] = 0;
            if (++rank1 == 4)
                return 1;
            return 0;
        }
        else if ((*py == yp && *px+2 == xp && check_not_wall(3, *px, *py, place)) || 
                (*py == yp && *px-2 == xp && check_not_wall(4, *px, *py, place)) || 
                (*px == xp && *py+2 == yp && check_not_wall(1, *px, *py, place)) || 
                (*px == xp && *py-2 == yp && check_not_wall(2, *px, *py, place)))
        {
            cout << "Player " << n << " Become " << rank1 << "th ........................................." << endl;
            if (n == 1)
                out_player *= 2;
            else
                out_player *= (2 * n - 1);
            place[*py * 17 + *px] = 0;
            if (++rank1 == 4)
                return 1;
            return 0;
        }
    }
    else if (np == 4 && mood == 1)  // 4-player  tournament
    {   
        if (n == 1 && *py >= 16 && nut_team1 == 2)
        {
            cout << "Team 1 Are Winner This Section ..." << endl;
            win_team1 += 1;
            return 1;
        }
        else if (n == 2 && *px <= 0 && nut_team1 == 1)
        {
            cout << "Team 1 Are Winner This Section ..." << endl;
            win_team1 += 1;
            return 1;
        }
        else if (n == 3 && *py <= 0 && nut_team2 == 4)
        {
            cout << "Team 2 Are Winner This Section ..." << endl;
            win_team2 += 1;
            return 1;
        }
        else if (n == 4 && *px >= 16 && nut_team2 == 3)
        {
            cout << "Team 2 Are Winner This Section ..." << endl;
            win_team2 += 1;
            return 1;
        }
        else if (n == 1 && *py >= 16)
        {
            cout << "Player 1 Is Reach End Board ..." << endl;
            place[*py * 17 + *px] = 0;
            nut_team1 = n;
            return 0;
        }
        else if (n == 2 && *px <= 0)
        {
            cout << "Player 2 Is Reach End Board ..." << endl;
            place[*py * 17 + *px] = 0;
            nut_team1 = n;
            return 0;
        }
        else if (n == 3 && *py <= 0)
        {
            cout << "Player 3 Is Reach End Board ..." << endl;
            place[*py * 17 + *px] = 0;
            nut_team2 = n;
            return 0;
        }
        else if (n == 4 && *px >= 16)
        {
            cout << "Player 4 Is Reach End Board ..." << endl;
            place[*py * 17 + *px] = 0;
            nut_team2 = n;
            return 0;
        }
        else if ((*py == yp && *px+2 == xp && check_not_wall(3, *px, *py, place)) || 
                (*py == yp && *px-2 == xp && check_not_wall(4, *px, *py, place)) || 
                (*px == xp && *py+2 == yp && check_not_wall(1, *px, *py, place)) || 
                (*px == xp && *py-2 == yp && check_not_wall(2, *px, *py, place)))
        {
            if (n == 1 && nut_team1 == 2)
            {
                cout << "Team 1 Are Winner This Section ..." << endl;
                win_team1 += 1;
                return 1;
            }
            else if (n == 2 && nut_team1 == 1)
            {
                cout << "Team 1 Are Winner This Section ..." << endl;
                win_team1 += 1;
                return 1;
            }
            else if (n == 3 && nut_team2 == 4)
            {
                cout << "Team 2 Are Winner This Section ..." << endl;
                win_team2 += 1;
                return 1;
            }
            else if (n == 4 && nut_team2 == 3)
            {  
                cout << "Team 2 Are Winner This Section ..." << endl;
                win_team2 += 1;
                return 1;
            }
            else if (n == 1)
            {
                cout << "Player 1 Is Reach Flag ..." << endl;
                place[*py * 17 + *px] = 0;
                nut_team1 = n;
                return 0;
            }
            else if (n == 2)
            {
                cout << "Player 2 Is Reach Flag ..." << endl;
                place[*py * 17 + *px] = 0;
                nut_team1 = n;
                return 0;
            }
            else if (n == 3)
            {
                cout << "Player 3 Is Reach Flag ..." << endl;
                place[*py * 17 + *px] = 0;
                nut_team2 = n;
                return 0;
            }
            else if (n == 4)
            {
                cout << "Player 2 Is Reach Flag ..." << endl;
                place[*py * 17 + *px] = 0;
                nut_team2 = n;
                return 0;
            }
        }
    }
    
    return false;
}


int exit_game()
// asking player want exit game
{
    string answer;
    string answers[6] = {"yes", "yeah", "y", "no", "nop", "n"};

    do  // check input is correct
    {
        cout << "Are You Sure Want Exit Game [Yes / No] :  ";
        cin >> answer;
        transform(answer.begin(), answer.end(), answer.begin(), ::tolower);

    } while (!check_input(answers, 6, answer));
    
    if (answer[0] == 121)  // [yes , yeah , y]
    {
        exit_tournament = true;
        return 3;
    }
 
    return false;
}


int game(short* place, short np, short n, short* px, short* py, short* number_wall, string move)
// determines and directs the type of movement of the player
{
    short answer;
    string normal[4] = {"f", "b", "r", "l"};
    string diagonal[8] = {"ofr", "ofl", "obr", "obl", "orf", "orb", "olf", "olb"};
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    
    if (changeinp)
        move = change_input(move, n, np);

    // normal and jumping movements
    if (check_input(normal, 4, move))
        answer = move_normal_jumping(place, np, n, px, py, move);

    // diagonal movements
    else if (check_input(diagonal, 8, move))
        answer = move_diagonal(place, np, n, px, py, move);

    // put a wall horizontal
    else if (check_input_wall(move, 1))
        answer = put_wall(place,np , 1, number_wall, move);
    
    // put a wall vertiacal
    else if (check_input_wall(move, 2))
        answer = put_wall(place,np , 2, number_wall, move);    
    
    // exit this game
    else if (move == "exit")
        return exit_game();

    // show number of wall
    else if (move == "wall")
    {
        cout << "Your Remaining Walls : " << *number_wall << endl;
        return 0;
    }
    
    else  // input is wrong
    {
        cout << "Input Is Wrong ! TryAgain" << endl;
        return 0;
    }

    // winner
    SetConsoleTextAttribute(h, 4);
    if (winner(place, np, n, px, py, answer))
    {
        SetConsoleTextAttribute(h, 7);
        return 2;
    }
    SetConsoleTextAttribute(h, 7);

    return answer;
}


bool nut_2(short* n, char move)
// check first char in move is 1,2,3,4 and creates n for 3,4 for term_2
{
    if (move == 95  || move == 124 || move == 101 || move == 119)
        return false;
    else if ((*n == 1) && (move == 50 || move == 52))
        return true;
    else if ((*n == 2) && (move == 49 || move == 51))
        return true;
    else if (move == 49 || move == 50)  
        return false;
    else if (move == 51 || move == 52)
    {
        *n += 2;
        return false;
    }

    return true;
}


bool term(short* place, short np, short n, short* px, short* py, short* number_wall)
// does command for player in games [any classic2x & daliz2x]
{
    string move;
    short conditional = 0;

    show_map(place);
    while (conditional == 0)
    {
        cout << "Move The Player " << n << " (F,B,R,L Or Place Wall{_12ab, |12ab}) :  ";
        cin >> move;
        transform(move.begin(), move.end(), move.begin(), :: tolower);
 
        conditional = game(place, np, n, px, py, number_wall, move);
    }
    
    if (np == 4 && mood == 0)  // determines rank of players in 4-players normal games
    {
        if (rank1 == 2 && rank1 == rank2 + 1)  // 1th
        {
            rank2++;
            add_to_lb(n, 200);
        }
        else if (rank1 == 3 && rank1 == rank2 + 1)  // 2th
        {
            rank2++;
            add_to_lb(n, 50);
        }
        else if (rank1 == 4 && rank1 == rank2 + 1)  // 3th
        {
            rank2++;
            add_to_lb(n, 20);
        }
    }

    if (conditional == 2 && mood == 1)  // 4-players tournaments end a section game
        return true;
    else if (conditional == 2 && np == 4)  // 4-players normals end game
        return true;
    if (conditional == 2)  // 2-3-players end game
    {
        show_map(place);
        add_to_lb(n, 100);
        return true;
    }

    if (conditional == 3)  // exit game
        return true;
    
    return false;  
}


bool term_2(short* place, short np, short nn, short* px, short* py, short* pxx, short* pyy, short* number_wall)
// does command for player in 2 games [classic2x & daliz2x]
{
    string move = "exit";
    short conditional = 0, n = nn;

    show_map(place);
    while (conditional == 0)
    {
        n = nn;
        if (move != "exit")
            cout << "What Nut ???" << endl;

        cout << "Move The Player " << nn << " (Fron,Back,Right,Left Or Place Wall) :  ";
        cin >> move;
        transform(move.begin(), move.end(), move.begin(), :: tolower);
        
        if (!(move[0] == 95 || move[0] == 124 || move[0] == 101 || move[0] == 119))
        {
            // changes input normal to input numberical when exist a nut for player
            if (n == 1 && nutP1 == 1 && move[0] != 51)
                move = "3" + move;
            else if (n == 1 && nutP1 == 3 && move[0] != 49)
                move = "1" + move;
            else if (n == 2 && nutP2 == 2 && move[0] != 52)
                move = "4" + move;
            else if (n == 2 && nutP2 == 4 && move[0] != 50)
                move = "2" + move;
        }

        if (nut_2(&n, move[0]))  // check first char in move is 1,2,3,4
            continue;
        if (move[0] - 48 == nutP1 || move[0] - 48 == nutP2)  // removed nuts donn't move
            continue;

        if (!(move[0] == 95 || move[0] == 124 || move[0] == 101 || move[0] == 119))
            move.erase(0, 1);

        if (n == 1 || n == 2)  // players 1,2
            conditional = game(place, 2, n, px, py, number_wall, move);
        else if (n == 3 || n == 4) // players 3,4
            conditional = game(place, 2, n, pxx, pyy, number_wall, move);
    }
    
    if (conditional == 2)  // end gmae
    {
        show_map(place);
        add_to_lb(n, 100);
        return true;
    }
    
    else if (conditional == 3)  // exit game
        return true;

    return false;  
}


bool play_again(string st)
// asks the players , they want play again ?
{
    string answer = "None";
    string yes_no[6] = {"yes", "yeah", "y", "no", "nop", "n"};
    cout << "-----------------------------------------" << endl;

    do 
    {
        if (answer != "None")
            cout << "WHAT ???" << endl;
        if (st == "start" || st == "s")
            cout << "Are You Want Play Again ? [Yes / No] :  ";
        else if (st == "leaderboard" || st == "help" || st == "l" || st == "h")
            cout << "You Want Have A Game ? [Yes / No] :  ";

        cin >> answer;
        transform(answer.begin(), answer.end(), answer.begin(), ::tolower);

    } while (!(check_input(yes_no, 6, answer)));  // check input is correct
    
    

    if (answer[0] == 121)  // [y, yeah, yes]
    {
        system("clear");
        return true;
    }
    return false;  // [n, nop, no]
}


int main()
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    string startCommand, numberP = "0", typeGame, answer;
    short px1, py1, px2, py2, px3, py3, px4, py4, px0, py0;
    short nWall1, nWall2, nWall3, nWall4;
    short board[17][17] = {};
    // inputs for start command
    string inputs[6] = {"start", "leaderboard", "help", "s", "l", "h"};  
    // inputs for 2-players game
    string types2[10] = {"classic", "c", "daliz", "d", "classic2x", "c2x", "c2", "daliz2x", "d2x", "d2"};  
    // inputs for 3-players game
    string types3[4] = {"dalizcenter", "dc", "dalizleft", "dl"};  
    // inputs for 4-player game
    string types4[8] = {"classic", "c", "daliz", "d", "classic tournament", "ct", "daliz tournament", "dt"};  

    system("clear");
    SetConsoleTextAttribute(h, 14);
    cout << "Welcome To The Quoridor !!!" << endl << endl;
    SetConsoleTextAttribute(h, 7);

    while (true)
    {
        do  // check input start command 
        {
        cout << "Select A options [Start _ Leadeboard _ Help]:  ";
        cin >> startCommand;
        transform(startCommand.begin(), startCommand.end(), startCommand.begin(), ::tolower);
        } while (!check_input(inputs, 6, startCommand));
        cout << endl;

        if (startCommand == "start" || startCommand == "s")  // start
        { 
            while (!((numberP[0] == 50 || numberP[0] == 51 || numberP[0] == 52) && numberP.length() == 1))
            {
                cout << "Enter Number Of Players [2 _ 3 _ 4] :  ";
                cin >> numberP;
            }
            cout << endl;

            if (numberP[0] == 50)  // 2-players game
            {
                do  // check input types game 2-players 
                {
                    cout << "Enter Type Of Game [Classic _ Daliz _ Classic2x _ Daliz2x] :  ";
                    cin >> typeGame;
                    transform(typeGame.begin(), typeGame.end(), typeGame.begin(), ::tolower);
                }
                while (!check_input(types2, 10, typeGame));
                cout << "-----------------------------------------------------------------" << endl;

                nWall1 = 10, nWall2 = 10;

                if (typeGame == "classic" || typeGame == "c")  // classic 2-players
                {
                    px1 = 8, py1 = 0;
                    px2 = 8, py2 = 16;
                    board[py1][px1] = 1;
                    board[py2][px2] = 2;

                    while (true)  // round
                    {
                        if (term(&board[0][0], 2, 1, &px1, &py1, &nWall1))  // movement player 1 
                            break;        
                        if (term(&board[0][0], 2, 2, &px2, &py2, &nWall2))  // movement player 2
                            break;
                    }
                }

                else if (typeGame == "daliz" || typeGame == "d") // daliz 2-players
                {
                    string flag;
                    px1 = 10, py1 = 0;
                    px2 = 10, py2 = 16;
                    board[py1][px1] = 1;
                    board[py2][px2] = 2;

                    do  // check input for place flag

                    {
                        cout << "Enter Place Of Flag [a-b-c-d-e-f-g-h-i] :  ";
                        cin >> flag;
                        transform(flag.begin(), flag.end(), flag.begin(), :: tolower);

                    } while (!(flag.length() == 1 && flag[0] >= 97 && flag[0] <= 105));
                    px0 = (flag[0] - 97) * 2;
                    py0 = 8;
                    board[py0][px0] = 88;

                    while (true)  // round
                    {
                        if (term(&board[0][0], 2, 1, &px1, &py1, &nWall1))  // movement player 1 
                            break;        
                        if (term(&board[0][0], 2, 2, &px2, &py2, &nWall2))  // movement player 2
                            break;
                    }
                    
                }

                else if (typeGame == "classic2x" || typeGame == "c2x" || typeGame == "c2")  // classic2x 2-players
                {
                    string pl;
                    px1 = 8, py1 = 0;
                    px2 = 8, py2 = 16;
                    py3 = 0, py4 = 16;
                    board[py1][px1] = 1;
                    board[py2][px2] = 2;

                    do  // check input for place nut 3 player 1
                    {
                        cout << "Enter Place of The Your Nut Player 1 [a-b-c-d-f-g-h-i] :  ";
                        cin >> pl;
                        transform(pl.begin(), pl.end(), pl.begin(), :: tolower);

                    } while (!(pl.length() == 1 && pl[0] >= 97 && pl[0] <= 105 && pl[0] != 101));
                    px3 = (pl[0] - 97) * 2;
                    board[py3][px3] = 3;
                    
                    do  // check input for place nut 4 player 2
                    {
                        cout << "Enter Place of The Your Nut Player 2 [a-b-c-d-f-g-h-i] :  ";
                        cin >> pl;
                        transform(pl.begin(), pl.end(), pl.begin(), :: tolower);

                    } while (!(pl.length() == 1 && pl[0] >= 97 && pl[0] <= 105 && pl[0] != 101));
                    px4 = (pl[0] - 97) * 2;
                    board[py4][px4] = 4;

                    while (true)  // round
                    {
                        if (term_2(&board[0][0], 2, 1, &px1, &py1, &px3, &py3, &nWall1))  // movement player 1 
                            break;        
                        if (term_2(&board[0][0], 2, 2, &px2, &py2, &px4, &py4, &nWall2))  // movement player 2
                            break;
                    }
                }

                else if (typeGame == "daliz2x" || typeGame == "d2x" || typeGame == "d2")  // daliz2x 2-players
                {
                    px1 = 0, py1 = 0;
                    px2 = 0, py2 = 16;
                    px3 = 16, py3 = 0;
                    px4 = 16, py4 = 16;
                    board[8][8] = 88;
                    board[py1][px1] = 1;
                    board[py2][px2] = 2;
                    board[py3][px3] = 3;
                    board[py4][px4] = 4;

                    while (true)  // round
                    {
                        if (term_2(&board[0][0], 2, 1, &px1, &py1, &px3, &py3, &nWall1))  // movement player 1 
                            break;        
                        if (term_2(&board[0][0], 2, 2, &px2, &py2, &px4, &py4, &nWall2))  // movement player 2
                            break;
                    }
                }
            }

            else if (numberP[0] == 51)  // 3-players game
            {
                do {
                    cout << "Enter Type Of Game [DalizCenter _ DalizLeft] :  ";
                    cin >> typeGame;
                    transform(typeGame.begin(), typeGame.end(), typeGame.begin(), ::tolower);
                }
                while (!check_input(types3, 4, typeGame));
                cout << "---------------------------------------------------" << endl;

                px1 = 8;   py1 = 0;
                px2 = 16;  py2 = 8;
                px3 = 8;   py3 = 16;
                board[py1][px1] = 1;
                board[py2][px2] = 2;
                board[py3][px3] = 3;
                nWall1 = 6;
                nWall2 = 6;
                nWall3 = 6;

                if (typeGame == "dalizcenter" || typeGame == "dc")  // daliz 3-players , flag in center board
                {
                    board[8][8] = 88;
                    while (true)  // round
                    {
                        if (term(&board[0][0], 3, 1, &px1, &py1, &nWall1))  // movement player 1 
                            break;        
                        if (term(&board[0][0], 3, 2, &px2, &py2, &nWall2))  // movement player 2
                            break;
                        if (term(&board[0][0], 3, 3, &px3, &py3, &nWall3))  // movement player 3
                            break;
                    }
                }

                else if (typeGame == "dalizleft" || typeGame == "dl")  // daliz 3-player , flag in left board
                {
                    board[8][0] = 88;
                    while (true)  // round
                    {
                        if (term(&board[0][0], 3, 1, &px1, &py1, &nWall1))  // movement player 1 
                            break;        
                        if (term(&board[0][0], 3, 2, &px2, &py2, &nWall2))  // movement player 2
                            break;
                        if (term(&board[0][0], 3, 3, &px3, &py3, &nWall3))  // movement player 3
                            break;
                    }
                }               
            }

            else if (numberP[0] == 52)  // 4-players game
            {
                do {
                    cout << "Enter Type Of Game [Classic _ Daliz _ Classic Tournament _ Daliz Tournament] :  ";
                    cin >> typeGame;
                    transform(typeGame.begin(), typeGame.end(), typeGame.begin(), ::tolower);
                }
                while (!check_input(types4, 8, typeGame));

                px1 = 8;   py1 = 0;
                px2 = 16;  py2 = 8;
                px3 = 8;   py3 = 16;
                px4 = 0;   py4 = 8;
                board[py1][px1] = 1;
                board[py2][px2] = 2;
                board[py3][px3] = 3;
                board[py4][px4] = 4;
                nWall1 = 5;
                nWall2 = 5;
                nWall3 = 5;
                nWall4 = 5;
                mood = 0;
                out_player = 1;
                rank1 = 1, rank2 = 1;
                name1th = " ", name2th = " ";

                if (typeGame == "classic" || typeGame == "c")  // classic 4-players
                {
                    cout << "----------------------------------------------------------------------------------" << endl;
                    while (true)  // round
                    {
                        if (out_player % 2 != 0)  // movement player 1 
                            if (term(&board[0][0], 4, 1, &px1, &py1, &nWall1))
                                break; 
                        if (out_player % 3 != 0)  // movement player 2     
                            if (term(&board[0][0], 4, 2, &px2, &py2, &nWall2))
                                break;
                        if (out_player % 5 != 0)  // movement player 3
                            if (term(&board[0][0], 4, 3, &px3, &py3, &nWall3))  
                                break;
                        if (out_player % 7 != 0)  // movement player 4
                            if (term(&board[0][0], 4, 4, &px4, &py4, &nWall4))  
                                break;
                    }
                }

                else if (typeGame == "daliz" || typeGame == "d")  // daliz 4-players
                {
                    board[8][8] = 88;
                    cout << "----------------------------------------------------------------------------------" << endl;
                    while (true)  // round
                    {
                        if (out_player % 2 != 0)  // movement player 1 
                            if (term(&board[0][0], 4, 1, &px1, &py1, &nWall1))
                                break;   
                        if (out_player % 3 != 0)  // movement player 2    
                            if (term(&board[0][0], 4, 2, &px2, &py2, &nWall2))
                                break;
                        if (out_player % 5 != 0)  // movement player 3
                            if (term(&board[0][0], 4, 3, &px3, &py3, &nWall3))
                                break;
                        if (out_player % 7 != 0)  // movement player 4
                            if (term(&board[0][0], 4, 4, &px4, &py4, &nWall4))
                                break;
                    }
                }

                else if (typeGame == "classic tournament" || typeGame == "ct")  // classic tournament 4-players
                {
                    while (!(win_team1 == 5 || win_team2 == 5))
                    {
                        if (exit_tournament)
                            break;
                        
                        change_array(&board[0][0], 17, 17, 0);
                        px1 = 8;   py1 = 0;
                        px2 = 16;  py2 = 8;
                        px3 = 8;   py3 = 16;
                        px4 = 0;   py4 = 8;
                        board[py1][px1] = 1;
                        board[py2][px2] = 2;
                        board[py3][px3] = 3;
                        board[py4][px4] = 4;
                        nWall1 = 5;
                        nWall2 = 5;
                        nWall3 = 5;
                        nWall4 = 5;
                        nut_team1 = 0, nut_team2 = 0,
                        mood = 1;

                        cout << "----------------------------------------------------------------------------------" << endl;
                        SetConsoleTextAttribute(h, 14);
                        cout << "Score Teame 1 Is : " << win_team1 << endl;
                        cout << "Score Teame 2 Is : " << win_team2 << endl;
                        SetConsoleTextAttribute(h, 7);

                        while (true)  // round
                        {
                            if (nut_team1 != 1)  // movement player 1
                                if (term(&board[0][0], 4, 1, &px1, &py1, &nWall1))
                                    break;     
                            if (nut_team1 != 2)  // movement player 2  
                                if (term(&board[0][0], 4, 2, &px2, &py2, &nWall2))
                                    break;
                            if (nut_team2 != 3)  // movement player 3
                                if (term(&board[0][0], 4, 3, &px3, &py3, &nWall3))
                                    break;
                            if (nut_team2 != 4)  // movement player 4
                                if (term(&board[0][0], 4, 4, &px4, &py4, &nWall4))
                                    break;
                        }
                    }
                    
                    // end tournament , determines winner
                    SetConsoleTextAttribute(h, 4);
                    if (win_team1 == 5)
                    {
                        cout << "Team 1 IS Winner This Game !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;  
                        SetConsoleTextAttribute(h, 7);
                        add_to_lb(1, 500); 
                    }
                    else if (win_team2 == 5)
                    {
                        cout << "Team 2 IS Winner This Game !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
                        SetConsoleTextAttribute(h, 7);
                        add_to_lb(2, 500);
                    }
                }

                else if (typeGame == "daliz tournament" || typeGame == "dt")  // daliz tournament 4-players
                {
                    while (!(win_team1 == 5 || win_team2 == 5))
                    {
                        if (exit_tournament)
                            break;
                        
                        change_array(&board[0][0], 17, 17, 0);
                        px1 = 8;   py1 = 0;
                        px2 = 16;  py2 = 8;
                        px3 = 8;   py3 = 16;
                        px4 = 0;   py4 = 8;
                        board[py1][px1] = 1;
                        board[py2][px2] = 2;
                        board[py3][px3] = 3;
                        board[py4][px4] = 4;
                        board[8][8] = 88;
                        nWall1 = 5;
                        nWall2 = 5;
                        nWall3 = 5;
                        nWall4 = 5;
                        nut_team1 = 0, nut_team2 = 0,
                        mood = 1;

                        cout << "----------------------------------------------------------------------------------" << endl;
                        SetConsoleTextAttribute(h, 14);
                        cout << "Score Teame 1 Is : " << win_team1 << endl;
                        cout << "Score Teame 2 Is : " << win_team2 << endl;
                        SetConsoleTextAttribute(h, 7);

                        while (true)  // round
                        {
                            if (nut_team1 != 1)  // movement player 1
                                if (term(&board[0][0], 4, 1, &px1, &py1, &nWall1))
                                    break;     
                            if (nut_team1 != 2)  // movement player 2   
                                if (term(&board[0][0], 4, 2, &px2, &py2, &nWall2))
                                    break;
                            if (nut_team2 != 3)  // movement player 3
                                if (term(&board[0][0], 4, 3, &px3, &py3, &nWall3))
                                    break;
                            if (nut_team2 != 4)  // movement player 4
                                if (term(&board[0][0], 4, 4, &px4, &py4, &nWall4))
                                    break;
                        }
                    }
                    
                    // end tournament , determines winner
                    SetConsoleTextAttribute(h, 4);
                    if (win_team1 == 5)
                    {
                        cout << "Team 1 IS Winner This Game !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
                        SetConsoleTextAttribute(h, 7);
                        add_to_lb(1, 500);
                    }   
                    else if (win_team2 == 5)
                    {
                        cout << "Team 2 IS Winner This Game !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
                        SetConsoleTextAttribute(h, 7);
                        add_to_lb(2, 500);
                    }
                }
            }
        }
    
        else if (startCommand == "leaderboard" || startCommand == "l")  // leaderboard
        {
            string name;
            int score;

            cout << "-----------------------------------------" << endl;
            cout << "Name" << "\t\t\t" << "Score" << endl << endl;
            ifstream lb (address_lb);
            if (!lb.is_open())  // check address leaderboard file
                cout << "This address Not Exist" << endl;

            while(lb >> name >> score)  // show names and scores in leaderboard
                if (name.length() < 8)
                    cout << name << "\t\t\t" << score << endl;
                else if (name.length() < 16)
                    cout << name << "\t\t" << score << endl;
                else
                    cout << name << "\t" << score << endl;

            lb.close();
        }

        else if (startCommand == "help" || startCommand == "h")  // help
        {
            string words;

            ifstream help (address_help);
            if (!help.is_open())  // check address help file
                cout << "This address Not Exist" << endl;

            while (getline(help, words))  // show text in help file
                cout << words << endl;

            help.close();
        }
    
        if (!play_again(startCommand))  // play again
            break;

        change_array(&board[0][0], 17, 17, 0);
        nutP1 = 0, nutP2 = 0;
        win_team1 = 0, win_team2 = 0, exit_tournament = false;
        startCommand = "None";
        numberP = "0";
    }
   
    SetConsoleTextAttribute(h, 14);
    cout << "Goodbye Players ..." << endl << endl;
    SetConsoleTextAttribute(h, 7);
    return 0;
}

