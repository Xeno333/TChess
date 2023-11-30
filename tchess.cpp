#include <iostream>
#include <string>
#include <map>
#include <list>

#define Background_W "\033[47m"
#define Background_B "\033[40m"
#define Forgound "\033[35m"
#define BoardPadding " "

namespace EasterEgg {
    const std::string CopyRight = "All Rights Reserved\n\nCopyright (c) 2023 Xeno333\n\nTHE CONTENTS OF THIS PROJECT ARE PROPRIETARY AND CONFIDENTIAL.\nUNAUTHORIZED COPYING, TRANSFERRING OR REPRODUCTION OF THE CONTENTS OF THIS PROJECT, VIA ANY MEDIUM IS STRICTLY PROHIBITED.\n\nThe receipt or possession of the source code and/or any parts thereof does not convey or imply any right to use them\nfor any purpose other than the purpose for which they were provided to you.\n\nThe software is provided \"AS IS\", without warranty of any kind, express or implied, including but not limited to\nthe warranties of merchantability, fitness for a particular purpose and non infringement.\nIn no event shall the authors or copyright holders be liable for any claim, damages or other liability,\nwhether in an action of contract, tort or otherwise, arising from, out of or in connection with the software\nor the use or other dealings in the software.\n\nThe above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.\n\n";

    void EasterEgg() {
        std::cout << "Congrats, you found an easteregg!" << std::endl << CopyRight;
        std::cout << "Thanks for using tchess!" << std::endl;
    }
}

using namespace std;

class ChessBoard{

    private:
        unsigned char LastSrcCollom = 0;
        unsigned char LastSrcRow = 0;
        unsigned char LastDstCollom = 0;
        unsigned char LastDstRow = 0;
    
        list<string> WhiteTook;
        list<string> BlackTook;

        //Because the board table uses the reversed coords, only first
        map<char, unsigned char> posmap = {
            {'h', 8},
            {'g', 7},
            {'f', 6},
            {'e', 5},
            {'d', 4},
            {'c', 3},
            {'b', 2},
            {'a', 1},
            {'1', 8},
            {'2', 7},
            {'3', 6},
            {'4', 5},
            {'5', 4},
            {'6', 3},
            {'7', 2},
            {'8', 1}
        };

        map<char, int> PieceValue = {
            {'P', 1},
            {'N', 3},
            {'B', 3},
            {'R', 5},
            {'Q', 9},
            {'K', 0},
        };

        string Background_1 = Background_W;
        string Background_2 = Background_B;

        bool enpassete;

        char TurnOf;

        string Board[8][8];
        //When indexing rows it is backwards.
        string BoardFresh[8][8] = {
                {"BR", "BN", "BB", "BQ", "BK", "BB", "BN", "BR"},
                {"BP", "BP", "BP", "BP", "BP", "BP", "BP", "BP"},
                {"  ", "  ", "  ", "  ", "  ", "  ", "  ", "  "},
                {"  ", "  ", "  ", "  ", "  ", "  ", "  ", "  "},
                {"  ", "  ", "  ", "  ", "  ", "  ", "  ", "  "},
                {"  ", "  ", "  ", "  ", "  ", "  ", "  ", "  "},
                {"WP", "WP", "WP", "WP", "WP", "WP", "WP", "WP"},
                {"WR", "WN", "WB", "WQ", "WK", "WB", "WN", "WR"},
        };

        int CheckCheck () {
            int x = 0;
            int y = 0;
            char piece[3] = {TurnOf, 'K', 0};

            while (true) {
                if (x == 8) {
                    x = 0;
                    y++;
                }
                if (Board[y][x] == piece) break;
                x++;
            }

            
            int x1 = x;
            while ((++x1 < 8) && (Board[y][x1] == "  "));
            if ((Board[y][x1][0] != TurnOf) && ((Board[y][x1][1] == 'R') || (Board[y][x1][1] == 'Q'))) {
                return 1;
            }
            x1 = x;
            while ((--x1 > -1) && (Board[y][x1] == "  "));
            if (x1 != -1) {
                if ((Board[y][x1][0] != TurnOf) && ((Board[y][x1][1] == 'R') || (Board[y][x1][1] == 'Q'))) {
                    return 1;
                }
            }

            int y1 = y;
            while ((++y1 < 8) && (Board[y1][x] == "  "));
            if ((Board[y1][x][0] != TurnOf) && ((Board[y1][x][1] == 'R') || (Board[y1][x][1] == 'Q'))) {
                return 1;
            }
            y1 = y;
            while ((--y1 > -1) && (Board[y1][x] == "  "));
            if (y1 != -1) {
                if ((Board[y1][x][0] != TurnOf) && ((Board[y1][x][1] == 'R') || (Board[y1][x][1] == 'Q'))) {
                    return 1;
                }
            }

            
            if ((((y + 1) < 8) && ((x + 2) < 8)) && (Board[y + 1][x + 2][0] != TurnOf) && (Board[y + 1][x + 2][1] == 'N')) return 1;
            if ((((y - 1) > -1) && ((x + 2) < 8)) && (Board[y - 1][x + 2][0] != TurnOf) && (Board[y - 1][x + 2][1] == 'N')) return 1;
            if ((((y + 1) < 8) && ((x - 2) > -1)) && (Board[y + 1][x - 2][0] != TurnOf) && (Board[y + 1][x - 2][1] == 'N')) return 1;
            if ((((y - 1) > -1) && ((x - 2) > -1)) && (Board[y - 1][x - 2][0] != TurnOf) && (Board[y - 1][x - 2][1] == 'N')) return 1;
            if ((((y + 2) < 8) && ((x + 1) < 8)) && (Board[y + 2][x + 1][0] != TurnOf) && (Board[y + 2][x + 1][1] == 'N')) return 1;
            if ((((y - 2) > -1) && ((x + 1) < 8)) && (Board[y - 2][x + 1][0] != TurnOf) && (Board[y - 2][x + 1][1] == 'N')) return 1;
            if ((((y + 2) < 8) && ((x - 1) > -1)) && (Board[y + 2][x - 1][0] != TurnOf) && (Board[y + 2][x - 1][1] == 'N')) return 1;
            if ((((y - 2) > -1) && ((x - 1) > -1)) && (Board[y - 2][x - 1][0] != TurnOf) && (Board[y - 2][x - 1][1] == 'N')) return 1;



            x1 = x;
            y1 = y;
            while (((--y1 > -1) && (--x1 > -1)) && (Board[y1][x1] == "  "));
            if (y1 != -1) {
                if ((Board[y1][x1][0] != TurnOf) && ((Board[y1][x1][1] == 'B') || (Board[y1][x1][1] == 'Q'))) {
                    return 1;
                }
            }
            x1 = x;
            y1 = y;
            while (((--y1 > -1) && (++x1 < 8)) && (Board[y1][x1] == "  "));
            if (y1 != -1) {
                if ((Board[y1][x1][0] != TurnOf) && ((Board[y1][x1][1] == 'B') || (Board[y1][x1][1] == 'Q'))) {
                    return 1;
                }
            }
            x1 = x;
            y1 = y;
            while (((++y1 < 8) && (--x1 > -1)) && (Board[y1][x1] == "  "));
            if (y1 != -1) {
                if ((Board[y1][x1][0] != TurnOf) && ((Board[y1][x1][1] == 'B') || (Board[y1][x1][1] == 'Q'))) {
                    return 1;
                }
            }
            x1 = x;
            y1 = y;
            while (((++y1 < 8) && (++x1 < 8)) && (Board[y1][x1] == "  "));
            if (y1 != -1) {
                if ((Board[y1][x1][0] != TurnOf) && ((Board[y1][x1][1] == 'B') || (Board[y1][x1][1] == 'Q'))) {
                    return 1;
                }
            }

            if (TurnOf == 'W') {
                if ((y - 1 > -1) && (x + 1 < 8) && (Board[y - 1][x + 1] == "BP")) return 1;
                if ((y - 1 > -1) && (x - 1 > -1) && (Board[y - 1][x - 1] == "BP")) return 1;
            }
            if (TurnOf == 'B') {
                if ((y + 1 < 8) && (x + 1 < 8) && (Board[y + 1][x + 1] == "WP")) return 1;
                if ((y + 1 < 8) && (x - 1 > -1) && (Board[y + 1][x - 1] == "WP")) return 1;
            }


            if (TurnOf == 'W') {
                if ((y - 1 > -1) && (x + 1 < 8) && (Board[y - 1][x + 1] == "BK")) return 1;
                if ((y - 1 > -1) && (x - 1 > -1) && (Board[y - 1][x - 1] == "BK")) return 1;
                if ((y + 1 < 8) && (x + 1 < 8) && (Board[y + 1][x + 1] == "BK")) return 1;
                if ((y + 1 < 8) && (x - 1 > -1) && (Board[y + 1][x - 1] == "BK")) return 1;
                if ((y + 1 < 8) && (Board[y + 1][x] == "BK")) return 1;
                if ((y - 1 > -1) && (Board[y - 1][x] == "BK")) return 1;
                if ((x + 1 < 8) && (Board[y][x + 1] == "BK")) return 1;
                if ((x - 1 > -1) && (Board[y][x - 1] == "BK")) return 1;
            }
            if (TurnOf == 'B') {
                if ((y - 1 > -1) && (x + 1 < 8) && (Board[y - 1][x + 1] == "WK")) return 1;
                if ((y - 1 > -1) && (x - 1 > -1) && (Board[y - 1][x - 1] == "WK")) return 1;
                if ((y + 1 < 8) && (x + 1 < 8) && (Board[y + 1][x + 1] == "WK")) return 1;
                if ((y + 1 < 8) && (x - 1 > -1) && (Board[y + 1][x - 1] == "WK")) return 1;
                if ((y + 1 < 8) && (Board[y + 1][x] == "WK")) return 1;
                if ((y - 1 > -1) && (Board[y - 1][x] == "WK")) return 1;
                if ((x + 1 < 8) && (Board[y][x + 1] == "WK")) return 1;
                if ((x - 1 > -1) && (Board[y][x - 1] == "WK")) return 1;
            }

            return 0;
        }

        int MoveCheck(unsigned char src_collom, unsigned char src_row, unsigned char dst_collom, unsigned char dst_row) {
            if ((src_collom == dst_collom) && (src_row == dst_row)) {
                cout << endl << "You must move a Piece!" << endl;
                return 1;
            }
            string src_piece = Board[src_row][src_collom];
            string dst_piece = Board[dst_row][dst_collom];
            Board[dst_row][dst_collom] = Board[src_row][src_collom];
            Board[src_row][src_collom] = "  ";
            int check = CheckCheck();
            Board[dst_row][dst_collom] = dst_piece;
            Board[src_row][src_collom] = src_piece;
            if (check == 1) {
                cout << endl << "You can't put yourself in check!" << endl;
                return 1;
            }
            int x1;
            int y1;
            switch (Board[src_row][src_collom][1]) {
                case 'N':
                    if (((src_collom - 2) == dst_collom && (src_row - 1) == dst_row) || ((src_collom - 2) == dst_collom && (src_row + 1) == dst_row) || ((src_collom + 2) == dst_collom && (src_row - 1) == dst_row)|| ((src_collom + 2) == dst_collom && (src_row + 1) == dst_row) || ((src_row - 2) == dst_row && (src_collom - 1) == dst_collom) || ((src_row - 2) == dst_row && (src_collom + 1) == dst_collom) || ((src_row + 2) == dst_row && (src_collom - 1) == dst_collom) || ((src_row + 2) == dst_row && (src_collom + 1) == dst_collom)) {
                        if (Board[dst_row][dst_collom][0] == TurnOf) break;//check so im not taking my Piece
                        return 0;
                    }
                    break;
                case 'P':
                    if (dst_collom == src_collom) {
                        if (((dst_row == 3) && (src_row == 1)) || ((dst_row == 4)  && (src_row == 6))) {
                            if ((((Board[src_row + 1][src_collom][0] != ' ') || (Board[src_row + 2][src_collom][0] != ' ')) && (TurnOf == 'B')) || (((Board[src_row - 1][src_collom][0] != ' ') || (Board[src_row - 2][src_collom][0] != ' ')) && (TurnOf == 'W'))) break;
                            return 0;
                        }
                        else if ((((src_row + 1) == dst_row) && (TurnOf == 'B')) || (((src_row - 1) == dst_row) && (TurnOf == 'W'))) {
                            if (Board[dst_row][dst_collom][0] == ' ') return 0;
                        }
                    }
                    else if (((((src_row - 1) == dst_row) && (TurnOf == 'W')) || (((src_row + 1) == dst_row) && (TurnOf == 'B'))) && (((src_collom + 1) == dst_collom) || ((src_collom - 1) == dst_collom))) {
                        if ((Board[dst_row][dst_collom][0] != ' ') && (Board[dst_row][dst_collom][0] != TurnOf)) return 0;
                        else if ((Board[dst_row][dst_collom][0] == ' ') && ((Board[dst_row + 1][dst_collom] == "BP") && ((LastDstRow == (dst_row + 1) && (LastDstCollom == dst_collom)) && ((LastSrcCollom == LastDstCollom) && ((LastSrcRow + 2) == LastDstRow)))) || (Board[dst_row][dst_collom][0] == ' ') && ((Board[dst_row - 1][dst_collom] == "WP") && ((LastDstRow == (dst_row - 1) && (LastDstCollom == dst_collom)) && ((LastSrcCollom == LastDstCollom) && ((LastSrcRow - 2) == LastDstRow)))) && (Board[dst_row][dst_collom][0] != TurnOf)) {
                            enpassete = true;
                            return 0;
                        }
                    }
                    break;
                case 'R':
                    if ((src_collom == dst_collom) || (src_row == dst_row)) {
                        x1 = src_collom;
                        y1 = src_row;
                        while (((++x1 < 8)) && (Board[y1][x1] == "  ") && (x1 != dst_collom));
                        if (((x1 < 8)) && (x1 == dst_collom) && (y1 == dst_row) && (Board[y1][x1][0] != TurnOf)) return 0;
                        
                        x1 = src_collom;
                        while (((--x1 > -1)) && (Board[y1][x1] == "  ") && (x1 != dst_collom));
                        if (((x1 > -1)) && (x1 == dst_collom) && (y1 == dst_row) && (Board[y1][x1][0] != TurnOf)) return 0;

                        x1 = src_collom;
                        y1 = src_row;
                        while (((--y1 > -1)) && (Board[y1][x1] == "  ") && (y1 != dst_row));
                        if (((y1 > -1)) && (x1 == dst_collom) && (y1 == dst_row) && (Board[y1][x1][0] != TurnOf)) return 0;

                        y1 = src_row;
                        while (((++y1 < 8)) && (Board[y1][x1] == "  ")  && (y1 != dst_row));
                        if (((y1 < 8)) && (x1 == dst_collom) && (y1 == dst_row) && (Board[y1][x1][0] != TurnOf)) return 0;
                    }
                    break;
                case 'K':
                    if ((((src_collom == (dst_collom + 1)) || (src_collom == (dst_collom - 1)) || (src_collom == dst_collom)) && ((src_row == (dst_row + 1)) || (src_row == (dst_row - 1)) || (src_row == dst_row)))) {
                        if (Board[dst_row][dst_collom][0] != TurnOf) return 0;
                    }
                    break;
                case 'B':
                    x1 = src_collom;
                    y1 = src_row;
                    while (((++y1 < 8) && (++x1 < 8)) && (Board[y1][x1] == "  ") && (x1 != dst_collom) && (y1 != dst_row));
                    if (((y1 < 8) && (x1 < 8)) && (x1 == dst_collom) && (y1 == dst_row) && (Board[y1][x1][0] != TurnOf)) return 0;

                    x1 = src_collom;
                    y1 = src_row;
                    while (((++y1 < 8) && (--x1 > -1)) && (Board[y1][x1] == "  ") && (x1 != dst_collom) && (y1 != dst_row));
                    if (((y1 < 8) && (x1 > -1)) && (x1 == dst_collom) && (y1 == dst_row) && (Board[y1][x1][0] != TurnOf)) return 0;

                    x1 = src_collom;
                    y1 = src_row;
                    while (((--y1 > -1) && (++x1 < 8)) && (Board[y1][x1] == "  ") && (x1 != dst_collom) && (y1 != dst_row));
                    if (((y1 > -1) && (x1 < 8)) && (x1 == dst_collom) && (y1 == dst_row) && (Board[y1][x1][0] != TurnOf)) return 0;

                    x1 = src_collom;
                    y1 = src_row;
                    while (((--y1 > -1) && (--x1 > -1)) && (Board[y1][x1] == "  ") && (x1 != dst_collom) && (y1 != dst_row));
                    if (((y1 > -1) && (x1 > -1)) && (x1 == dst_collom) && (y1 == dst_row) && (Board[y1][x1][0] != TurnOf)) return 0;
                    break;
                case 'Q':
                    if ((src_collom == dst_collom) || (src_row == dst_row)) {
                        x1 = src_collom;
                        y1 = src_row;
                        while (((++x1 < 8)) && (Board[y1][x1] == "  ") && (x1 != dst_collom));
                        if (((x1 < 8)) && (x1 == dst_collom) && (y1 == dst_row) && (Board[y1][x1][0] != TurnOf)) return 0;
                        
                        x1 = src_collom;
                        while (((--x1 > -1)) && (Board[y1][x1] == "  ") && (x1 != dst_collom));
                        if (((x1 > -1)) && (x1 == dst_collom) && (y1 == dst_row) && (Board[y1][x1][0] != TurnOf)) return 0;

                        x1 = src_collom;
                        y1 = src_row;
                        while (((--y1 > -1)) && (Board[y1][x1] == "  ") && (y1 != dst_row));
                        if (((y1 > -1)) && (x1 == dst_collom) && (y1 == dst_row) && (Board[y1][x1][0] != TurnOf)) return 0;

                        y1 = src_row;
                        while (((++y1 < 8)) && (Board[y1][x1] == "  ")  && (y1 != dst_row));
                        if (((y1 < 8)) && (x1 == dst_collom) && (y1 == dst_row) && (Board[y1][x1][0] != TurnOf)) return 0;
                    }
                    x1 = src_collom;
                    y1 = src_row;
                    while (((++y1 < 8) && (++x1 < 8)) && (Board[y1][x1] == "  ") && (x1 != dst_collom) && (y1 != dst_row));
                    if (((y1 < 8) && (x1 < 8)) && (x1 == dst_collom) && (y1 == dst_row) && (Board[y1][x1][0] != TurnOf)) return 0;
                    
                    x1 = src_collom;
                    y1 = src_row;
                    while (((++y1 < 8) && (--x1 > -1)) && (Board[y1][x1] == "  ") && (x1 != dst_collom) && (y1 != dst_row));
                    if (((y1 < 8) && (x1 > -1)) && (x1 == dst_collom) && (y1 == dst_row) && (Board[y1][x1][0] != TurnOf)) return 0;

                    x1 = src_collom;
                    y1 = src_row;
                    while (((--y1 > -1) && (++x1 < 8)) && (Board[y1][x1] == "  ") && (x1 != dst_collom) && (y1 != dst_row));
                    if (((y1 > -1) && (x1 < 8)) && (x1 == dst_collom) && (y1 == dst_row) && (Board[y1][x1][0] != TurnOf)) return 0;

                    x1 = src_collom;
                    y1 = src_row;
                    while (((--y1 > -1) && (--x1 > -1)) && (Board[y1][x1] == "  ") && (x1 != dst_collom) && (y1 != dst_row));
                    if (((y1 > -1) && (x1 > -1)) && (x1 == dst_collom) && (y1 == dst_row) && (Board[y1][x1][0] != TurnOf)) return 0;
                    break;
                default:
                    break;
            }
            cout << endl << "Bad move!" << endl;
            return 1;
        }

        void Take(string Piece) {
            if (TurnOf == 'W') {
                WhiteTook.insert(WhiteTook.end(), Piece);
            }
            else {
                BlackTook.insert(BlackTook.end(), Piece);
            }
        }

        int Move(unsigned char src_collom, unsigned char src_row, unsigned char dst_collom, unsigned char dst_row) {
            if (Board[src_row][src_collom][0] != TurnOf) {
                cout << endl << "You can only move your pieces!" << endl;
                return 1;
            }

            if (MoveCheck(src_collom, src_row, dst_collom, dst_row) != 0) {
                return 1;
            }

            if (enpassete == true) {
                enpassete = false;
                Board[LastDstRow][LastDstCollom] = "  ";
                Take(Board[LastDstRow][LastDstCollom]);
            }
            else if (Board[dst_row][dst_collom] != "  ") {
                Take(Board[dst_row][dst_collom]);
            }
            Board[dst_row][dst_collom] = Board[src_row][src_collom];
            Board[src_row][src_collom] = "  ";

            if (TurnOf == 'W') {
                TurnOf = 'B';
            }
            else {
                TurnOf = 'W';
            }

            return 0;
        }

        void PrintBoardLine(int n) {
            cout << Forgound << Background_1 << BoardPadding << Board[n][0] << Background_2 << BoardPadding << Board[n][1] << Background_1 << BoardPadding << Board[n][2] << Background_2 << BoardPadding << Board[n][3] << Background_1 << BoardPadding << Board[n][4] << Background_2 << BoardPadding << Board[n][5] << Background_1 << BoardPadding << Board[n][6] << Background_2 << BoardPadding << Board[n][7] << Background_1 << "\033[0m";
            string H = Background_1;
            Background_1 = Background_2;
            Background_2 = H;
        }




    public:

        int Play(string src, string dst) {
            unsigned char src_collom = posmap[src[0]];
            unsigned char src_row = posmap[src[1]];
            unsigned char dst_collom = posmap[dst[0]];
            unsigned char dst_row = posmap[dst[1]];

            if ((src_collom == 0) || (src_row == 0) || (dst_collom == 0) || (dst_row == 0)) {
                cout << endl << "Bad Coords" << endl;
                return 1;
            }

            //For the extra 1 bc of the check above.
            src_collom--;
            src_row--;
            dst_collom--;
            dst_row--;
            
            int rc = Move(src_collom, src_row, dst_collom, dst_row);

            //set last move
            LastSrcCollom = src_collom;
            LastSrcRow = src_row;
            LastDstCollom = dst_collom;
            LastDstRow = dst_row;

            return rc;
        }

        void PrintBoard() {
            cout << endl;
            cout << "8 ";
            PrintBoardLine(0);
            cout << "  ";
            for (list<string>::iterator i = BlackTook.begin(); i != BlackTook.end(); i++)
                cout << *i << " ";
            cout << endl << "7 ";
            PrintBoardLine(1);
            cout << endl << "6 ";
            PrintBoardLine(2);
            cout << endl << "5 ";
            PrintBoardLine(3);
            cout << endl << "4 ";
            PrintBoardLine(4);
            cout << endl << "3 ";
            PrintBoardLine(5);
            cout << endl << "2 ";
            PrintBoardLine(6);
            cout << endl << "1 ";
            PrintBoardLine(7);
            cout << "  ";
            for (list<string>::iterator i = WhiteTook.begin(); i != WhiteTook.end(); i++)
                cout << *i << " ";
            cout << endl << BoardPadding << "  a" BoardPadding << " b" BoardPadding << " c" BoardPadding << " d" BoardPadding << " e" BoardPadding << " f" BoardPadding << " g" BoardPadding << " h" << endl;
        }

        void init() {
            //copy from FreshBoad to Board
            for (int j = 0; j < 8; j++) for (int i = 0; i < 8; i++) Board[j][i] = BoardFresh[j][i];
            //Turn
            TurnOf = 'W';

            LastSrcCollom = 0;
            LastSrcRow = 0;
            LastDstCollom = 0;
            LastDstRow = 0;
            enpassete = false;

            //Clear taken
            WhiteTook.clear();
            BlackTook.clear();
        }
};



int play() {
    ChessBoard Game;
    Game.init();
    Game.PrintBoard();

    bool turn = true;//black is false

    string src, dst;

    while (true) {
        cout << "Enter coords of peice you want to move: ";
        cin >> src;
        cout << "Enter coords of place you want to move to: ";
        cin >> dst;

        if ((src == "q") || (dst == "q")) {
            cout << endl << "Game aborted!" << endl;
            return -1;
        }
        if (Game.Play(src, dst) == 0) {
            Game.PrintBoard();
            if (turn == true) {
                cout << "Black's turn" << endl;
                turn = false;
            }
            else {
                cout << "White's turn" << endl;
                turn = true;
            }
        }
        else {
            cout << "Be real!" << endl;
        }
    }

    return 0;
}



int main() {
    string in;

    while (true) {
        cout << "Would you like to play a game?(y, n) " << endl;
        cin >> in;

        if (in == "y") {
            play();
        }
        else if (in == "q") {
            cout << "Bye" << endl;
            break;
        }
        else if (in == "who") {
            EasterEgg::EasterEgg();
        }
        else if (in == "help") {
            cout << "q Quite" << endl << "y, n Play or not" << endl;
        }
        else if (in == "n") {
            cout << "Loser!" << endl;
        }
    }

    return 0;
}