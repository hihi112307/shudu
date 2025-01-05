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
    /* TODO: �ˬd������O�_���Ĭ𪺼Ʀr�A�Ϊ̤w�g�񺡡C */
    for (int c = 0; c < 4; ++c) {
        if (board[cur_r][c] == board[cur_r][cur_c] && c != cur_c && board[cur_r][cur_c] != 0) {
            cout << "Horizontal conflict at row" << cur_r << endl;
            return;
        }
    }
}

void check_vertical()
{
    /* TODO: �ˬd�����C�O�_���Ĭ𪺼Ʀr�A�Ϊ̤w�g�񺡡C */
    for (int r = 0; r < 4; ++r) {
        if (board[r][cur_c] == board[cur_r][cur_c] && r != cur_r && board[cur_r][cur_c] != 0) {
            cout << "Vertical conflict at column  " << cur_c << endl;
            return;
        }
    }
}

void check_block()
{
    /* TODO: �ˬd�϶��]2x2�^���O�_���Ĭ𪺼Ʀr�A�Ϊ̤w�g�񺡡C */
    int block_r = cur_r / 2 * 2;  // �N��ƬM�g��϶�
    int block_c = cur_c / 2 * 2;  // �N�C�ƬM�g��϶�

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
    /* TODO: �b��e��ЩҦb����l��J�Ʀr�A���ˬd������B�����C�M�϶��O�_���Ĭ�C */
    
    if (num < 0 || num > 4) {
        cout << "Invalid number! Please enter a number between 1 and 4." << endl;
        return;
    }
    else if (num == 0) {
        board[cur_r][cur_c] = 0;
    } else {
        // �_�h��J�ӼƦr
        board[cur_r][cur_c] = num;
    }

    check_horizontal();
    check_vertical();
    check_block();
}

void move_cursor(char direction)
{
    /* �ھڿ�J����V���ʴ�СA���ˬd�O�_�V�ɩάO�Ӧ�m���i�s�� */
    int start_r = cur_r;
    int start_c = cur_c;

    if (direction == 'W' || direction == 'w') {
        // �q��e��}�l�V�W�d��i�s�誺��l
        do {
            if (cur_r > 0) cur_r--;
        } while (cur_r > 0 && !editable[cur_r][cur_c]);
    } 
    else if (direction == 'S' || direction == 's') {
        // �q��e��}�l�V�U�d��i�s�誺��l
        do {
            if (cur_r < 3) cur_r++;
        } while (cur_r < 3 && !editable[cur_r][cur_c]);
    } 
    else if (direction == 'A' || direction == 'a') {
        // �q��e�C�}�l�V���d��i�s�誺��l
        do {
            if (cur_c > 0) cur_c--;
        } while (cur_c > 0 && !editable[cur_r][cur_c]);
    } 
    else if (direction == 'D' || direction == 'd') {
        // �q��e�C�}�l�V�k�d��i�s�誺��l
        do {
            if (cur_c < 3) cur_c++;
        } while (cur_c < 3 && !editable[cur_r][cur_c]);
    }

    // �p�G���ʫ�A��Ц�m�����ܡA��ܥ�����s���i�s���l�A�h��_���Ӫ���m
    if (start_r == cur_r && start_c == cur_c) {
        // �Y�L�k���ʨ�s���i�s���l�A�h��^���m
        cur_r = start_r;
        cur_c = start_c;
    }
}

bool is_invalid(int i, int j)
{
    /* TODO: �ˬd board[i][j] �O�_�P��Ҧb��B�C�ΰ϶�������L�Ʀr�Ĭ�C */
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
    /* TODO: �ˬd�C���O�_�����A�Y�C�Ӯ�l���w���T�񺡡C */
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
    int start_row = (row / 2) * 2;  // ���϶����_�l��
    int start_col = (col / 2) * 2;  // ���϶����_�l�C

    for (int r = start_row; r < start_row + 2; ++r) {
        for (int c = start_col; c < start_col + 2; ++c) {
            if (board[r][c] < 1 || board[r][c] > 4) return false;  // �ˬd�Ʀr�O�_�b 1 �� 4 �d��
            if (unique_numbers.find(board[r][c]) != unique_numbers.end()) // �p�G�ӼƦr�w�g�X�{�L�A�h����
            return false;
            unique_numbers.insert(board[r][c]);
        }
    }
    return true;
}

bool is_row_correct(int row) {
    set<int> seen;
    for (int col = 0; col < 4; ++col) {
        if (board[row][col] == 0) // �p�G�Ӧ�m�� 0�A��ܩ|����g
            return false;
        if (seen.find(board[row][col]) != seen.end()) // �p�G�ӼƦr�w�g�X�{�L�A�h����
            return false;
        seen.insert(board[row][col]);
    }
    return true; // �p�G�Ҧ��Ʀr�������ƨåB�񺡡A��^ true
}

bool is_column_correct(int col) {
    set<int> seen;  // �ΨӰO���ӦC���w�g�X�{�L���Ʀr
    for (int row = 0; row < 4; ++row) {
        if (board[row][col] == 0) // �p�G�Ӧ�m�� 0�A��ܩ|����g
            return false;  // �C�����Ů�A��^���~
        if (seen.find(board[row][col]) != seen.end()) // �p�G�ӼƦr�w�g�X�{�L�A�h����
            return false;  // �����ƼƦr�A��^���~
        seen.insert(board[row][col]); // �O����e�Ʀr
    }
    return true; // �p�G�Ҧ��Ʀr�������ƨåB�񺡡A��^ true
}
void print_board()
{
    // �M��
    cout << "\x1b[2J\x1b[1;1H";

    // �ϥδ���
    cout << get_styled_text("W/A/S/D: ", "B") << "move cursor" << endl;
    cout << get_styled_text("    1-4: ", "B") << "fill in number" << endl;
    cout << get_styled_text("      0: ", "B") << "clear the cell" << endl;
    cout << get_styled_text("      Q: ", "B") << "quit" << endl;
    cout << endl;
    // �M���C�Ӯ�l�å��L
    for (int i = 0; i < 4; ++i)
    {
        // ���L�������j�u
        if (i && i % 2 == 0)
            cout << "---------------" << endl;

        // �C��}�l���L
        cout << "|";
        for (int j = 0; j < 4; ++j)
        {
            // �T�w��e��l���˦�
            string style = "";

            // �p�G��e��l�O��Ц�m�A�u����ܴ�м˦�
            if (cur_r == i && cur_c == j) {
                style = "C"; // ����Ŧ�I��
            }
            // �p�G��e��l�L�ġ]���Ĭ�^�A��ܬ�����
            else if (is_invalid(i, j)) {
                style = "E"; // �����ܿ��~
            }
            // �p�G�Ӧ楿�T�A�B��l�L�Ĭ�A��ܺ��
            else if (is_row_correct(i)) {
                style = "G"; // �楿�T��ܺ��
            }
            // �p�G�ӦC���T�A�B��l�L�Ĭ�A��ܺ��
            else if (is_column_correct(j)) {
                style = "G"; // �C���T��ܺ��
            }
             else if (is_block_correct(i, j)) {
                style = "G"; // �C���T��ܺ��
            }
            // �p�G��l�O��l��
            if (!editable[i][j]) {
                style += "B"; // ����
            }

            // ���L�Ʀr�ΪŮ�
            if (board[i][j] == 0)
                cout << get_styled_text(" �P ", style);
            else
                cout << get_styled_text(" " + to_string(board[i][j]) + " ", style);

            // ���L�C���j��
            if ((j + 1) % 2 == 0)
                cout << "|";
            style = ""; 
        }
        cout << '\n';
    }
}

void initialize()
{
    // �]�m Windows �W���˦��奻�C
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    SetConsoleMode(hOut, dwMode);

    // �аO�i�s�誺��l
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            editable[i][j] = !board[i][j];

    // ��ܪ�l�ѽL
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
            cout << get_styled_text("!!! �L�Ī��ާ@ !!!", "R");
    }

    return 0;
}
