#include <iostream> 
#include <windows.h>
#include <set>
#include <vector>

using namespace std;

int board[4][4] = {
    {0, 0, 1, 0},
    {0, 4, 0, 0},
    {0, 0, 2, 0},
    {0, 1, 0, 0},
};

bool editable[4][4];

int cur_r = 0, cur_c = 0;

void check_horizontal()
{
    /* TODO: 檢查水平行是否有衝突的數字，或者已經填滿。 */
    for (int c = 0; c < 4; ++c) {
        if (board[cur_r][c] == board[cur_r][cur_c] && c != cur_c && board[cur_r][cur_c] != 0) {
            cout << "Horizontal conflict at row" << cur_r << endl;
            return;
        }
    }
}

void check_vertical()
{
    /* TODO: 檢查垂直列是否有衝突的數字，或者已經填滿。 */
    for (int r = 0; r < 4; ++r) {
        if (board[r][cur_c] == board[cur_r][cur_c] && r != cur_r && board[cur_r][cur_c] != 0) {
            cout << "Vertical conflict at column  " << cur_c << endl;
            return;
        }
    }
}

void check_block()
{
    /* TODO: 檢查區塊（2x2）內是否有衝突的數字，或者已經填滿。 */
    int block_r = cur_r / 2 * 2;  // 將行數映射到區塊
    int block_c = cur_c / 2 * 2;  // 將列數映射到區塊

    for (int r = block_r; r < block_r + 2; ++r) {
        for (int c = block_c; c < block_c + 2; ++c) {
            if (board[r][c] == board[cur_r][cur_c] && r != cur_r && c != cur_c && board[cur_r][cur_c] != 0) {
                cout << "Block conflict at block starting at (" << block_r << ", " << block_c << ")" << endl;
                return;
            }
        }
    }
}

void fill_number(int num)
{
    /* TODO: 在當前游標所在的格子填入數字，並檢查水平行、垂直列和區塊是否有衝突。 */
    
    if (num < 0 || num > 4) {
        cout << "Invalid number! Please enter a number between 1 and 4." << endl;
        return;
    }
    else if (num == 0) {
        board[cur_r][cur_c] = 0;
    } else {
        // 否則填入該數字
        board[cur_r][cur_c] = num;
    }

    check_horizontal();
    check_vertical();
    check_block();
}

void move_cursor(char direction)
{
    /* 根據輸入的方向移動游標，並檢查是否越界或是該位置不可編輯 */
    int start_r = cur_r;
    int start_c = cur_c;

    if (direction == 'W' || direction == 'w') {
        // 從當前行開始向上查找可編輯的格子
        do {
            if (cur_r > 0) cur_r--;
        } while (cur_r > 0 && !editable[cur_r][cur_c]);
    } 
    else if (direction == 'S' || direction == 's') {
        // 從當前行開始向下查找可編輯的格子
        do {
            if (cur_r < 3) cur_r++;
        } while (cur_r < 3 && !editable[cur_r][cur_c]);
    } 
    else if (direction == 'A' || direction == 'a') {
        // 從當前列開始向左查找可編輯的格子
        do {
            if (cur_c > 0) cur_c--;
        } while (cur_c > 0 && !editable[cur_r][cur_c]);
    } 
    else if (direction == 'D' || direction == 'd') {
        // 從當前列開始向右查找可編輯的格子
        do {
            if (cur_c < 3) cur_c++;
        } while (cur_c < 3 && !editable[cur_r][cur_c]);
    }

    // 如果移動後，游標位置未改變，表示未能找到新的可編輯格子，則恢復到原來的位置
    if (start_r == cur_r && start_c == cur_c) {
        // 若無法移動到新的可編輯格子，則返回原位置
        cur_r = start_r;
        cur_c = start_c;
    }
}

bool is_invalid(int i, int j)
{
    /* TODO: 檢查 board[i][j] 是否與其所在行、列或區塊中的其他數字衝突。 */
    for (int c = 0; c < 4; ++c) {
        if (board[i][c] == board[i][j] && c != j && board[i][j] != 0)
            return true;
    }
    for (int r = 0; r < 4; ++r) {
        if (board[r][j] == board[i][j] && r != i && board[i][j] != 0)
            return true;
    }
    int block_r = i / 2 * 2;
    int block_c = j / 2 * 2;
    for (int r = block_r; r < block_r + 2; ++r) {
        for (int c = block_c; c < block_c + 2; ++c) {
            if (board[r][c] == board[i][j] && (r != i || c != j) && board[i][j] != 0)
                return true;
        }
    }
    return false;
}

bool check_win()
{
    /* TODO: 檢查遊戲是否完成，即每個格子都已正確填滿。 */
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (board[i][j] == 0 || is_invalid(i, j))
                return false;
        }
    }
    return true;
}

bool is_moving_action(char c)
{
    return (c == 'W' || c == 'w' || c == 'S' || c == 's' ||
            c == 'A' || c == 'a' || c == 'D' || c == 'd');
}

bool is_filling_action(char c)
{
    return (c >= '0' && c <= '4');
}

string get_styled_text(string text, string style)
{
    string color = "", font = "";
    for (char c : style)
    {
        if (c == 'R')
            color = "31";
        if (c == 'G')
            color = "32";
        if (c == 'E')
            color = "41";
        if (c == 'C')
            color = "106";
        if (c == 'B')
            font = ";1";
    }
    return "\x1b[" + color + font + "m" + text + "\x1b[0m";
}

bool  is_block_correct(int row, int col)
{
    set<int> unique_numbers;
    int start_row = (row / 2) * 2;  // 找到區塊的起始行
    int start_col = (col / 2) * 2;  // 找到區塊的起始列

    for (int r = start_row; r < start_row + 2; ++r) {
        for (int c = start_col; c < start_col + 2; ++c) {
            if (board[r][c] < 1 || board[r][c] > 4) return false;  // 檢查數字是否在 1 到 4 範圍內
            if (unique_numbers.find(board[r][c]) != unique_numbers.end()) // 如果該數字已經出現過，則重複
            return false;
            unique_numbers.insert(board[r][c]);
        }
    }
    return true;
}

bool is_row_correct(int row) {
    set<int> seen;
    for (int col = 0; col < 4; ++col) {
        if (board[row][col] == 0) // 如果該位置為 0，表示尚未填寫
            return false;
        if (seen.find(board[row][col]) != seen.end()) // 如果該數字已經出現過，則重複
            return false;
        seen.insert(board[row][col]);
    }
    return true; // 如果所有數字都不重複並且填滿，返回 true
}

bool is_column_correct(int col) {
    set<int> seen;  // 用來記錄該列中已經出現過的數字
    for (int row = 0; row < 4; ++row) {
        if (board[row][col] == 0) // 如果該位置為 0，表示尚未填寫
            return false;  // 列中有空格，返回錯誤
        if (seen.find(board[row][col]) != seen.end()) // 如果該數字已經出現過，則重複
            return false;  // 有重複數字，返回錯誤
        seen.insert(board[row][col]); // 記錄當前數字
    }
    return true; // 如果所有數字都不重複並且填滿，返回 true
}
void print_board()
{
    // 清屏
    cout << "\x1b[2J\x1b[1;1H";

    // 使用提示
    cout << get_styled_text("W/A/S/D: ", "B") << "move cursor" << endl;
    cout << get_styled_text("    1-4: ", "B") << "fill in number" << endl;
    cout << get_styled_text("      0: ", "B") << "clear the cell" << endl;
    cout << get_styled_text("      Q: ", "B") << "quit" << endl;
    cout << endl;
    // 遍歷每個格子並打印
    for (int i = 0; i < 4; ++i)
    {
        // 打印水平分隔線
        if (i && i % 2 == 0)
            cout << "---------------" << endl;

        // 每行開始打印
        cout << "|";
        for (int j = 0; j < 4; ++j)
        {
            // 確定當前格子的樣式
            string style = "";

            // 如果當前格子是游標位置，優先顯示游標樣式
            if (cur_r == i && cur_c == j) {
                style = "C"; // 游標藍色背景
            }
            // 如果當前格子無效（有衝突），顯示為紅色
            else if (is_invalid(i, j)) {
                style = "E"; // 紅色表示錯誤
            }
            // 如果該行正確，且格子無衝突，顯示綠色
            else if (is_row_correct(i)) {
                style = "G"; // 行正確顯示綠色
            }
            // 如果該列正確，且格子無衝突，顯示綠色
            else if (is_column_correct(j)) {
                style = "G"; // 列正確顯示綠色
            }
             else if (is_block_correct(i, j)) {
                style = "G"; // 列正確顯示綠色
            }
            // 如果格子是初始值
            if (!editable[i][j]) {
                style += "B"; // 粗體
            }

            // 打印數字或空格
            if (board[i][j] == 0)
                cout << get_styled_text(" · ", style);
            else
                cout << get_styled_text(" " + to_string(board[i][j]) + " ", style);

            // 打印列分隔符
            if ((j + 1) % 2 == 0)
                cout << "|";
            style = ""; 
        }
        cout << '\n';
    }
}

void initialize()
{
    // 設置 Windows 上的樣式文本。
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    SetConsoleMode(hOut, dwMode);

    // 標記可編輯的格子
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            editable[i][j] = !board[i][j];

    // 顯示初始棋盤
    print_board();
}

int main()
{
    char c;
    bool action_ok;

    initialize();
    while (cin >> c)
    {
        action_ok = false;
        if (is_moving_action(c))
        {
            action_ok = true;
            move_cursor(c);
        }

        if (is_filling_action(c))
        {
            action_ok = true;
            int num = c - '0'; 
            fill_number(num);
        }

        if (c == 'Q' || c == 'q')
            break;

        print_board();

        if (check_win())
        {
            cout << "YOU BEAUTIFUL CLEVER GIRL WIN" << endl;
            break;
        }

        if (!action_ok)
            cout << get_styled_text("!!! 無效的操作 !!!", "R");
    }

    return 0;
}
