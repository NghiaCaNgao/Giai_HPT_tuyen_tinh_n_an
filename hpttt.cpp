#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;
using std::setw;

int numX;
int ptr[50][50];
int stp[50];
float output[50];

void showMatrix()
{
    cout << "Ma tran he so mo rong \n";
    for (int i = 0; i < numX; i++)
    {
        for (int j = 0; j < numX; j++)
            cout << setw(5) << ptr[i][j] << " ";
        cout << "|" << setw(5) << ptr[i][numX] << "\n";
    }
    cout << "--------------------------------------------------- \n";
}

void showOutput()
{
    cout << "Tap nghiem la: \n";
    cout << "( ";
    for (int i = 0; i < numX; i++)
    {
        cout << output[i] << " ";
    }
    cout << ") \n";
}

void swapPtr(int i, int j)
{
    int tmp;
    for (int index = 0; index <= numX; index++)
    {
        tmp = ptr[i][index];
        ptr[i][index] = ptr[j][index];
        ptr[j][index] = tmp;
    }
    return;
}

void swapStp(int i, int j)
{
    int tmp;
    tmp = stp[i];
    stp[i] = stp[j];
    stp[j] = tmp;
}

int getStartPoint(int row)
{
    int start = 99;
    for (int i = 0; i < numX; i++)
    {
        if (ptr[row][i] != 0)
        {
            start = i;
            break;
        }
    }
    return start;
}

int UCLN(int a, int b)
{
    int r;
    do
    {
        r = a % b;
        a = b;
        b = r;
    } while (b != 0);
    return a;
}

int BCNN(int a, int b)
{
    if (a < 0)
        a = -a;
    if (b < 0)
        b = -b;
    return a * b / UCLN(a, b);
}

void reduce(int ptrIndex)
{
    bool hasUC = true;
    int startPoint = stp[ptrIndex];
    int uc = ptr[ptrIndex][startPoint];
    for (int i = startPoint + 1; i <= numX; i++)
    {
        if (ptr[ptrIndex][i] == 0)
        {
            hasUC = false;
            break;
        }
        uc = UCLN(uc, ptr[ptrIndex][i]);
    }
    if (hasUC)
    {
        for (int i = startPoint; i <= numX; i++)
        {
            ptr[ptrIndex][i] = ptr[ptrIndex][i] / uc;
        }
    }
}

void reduceFreeNumber(int bac, int ptrIndex)
{
    if (stp[ptrIndex] >= bac)
        return;
    int num1 = ptr[bac - 1][bac - 1];
    int num2 = ptr[ptrIndex][bac - 1];
    if (num2 == 0)
        return;
    // cout << bac << " " << ptrIndex << " " << num1 << " " << ptr[ptrIndex][bac - 1] << "\n";
    int boiso = BCNN(num1, num2);
    int boiso1 = boiso / num1;
    int boiso2 = boiso / num2;

    for (int m = bac - 1; m <= numX; m++)
    {
        if (m == bac - 1)
            ptr[ptrIndex][m] = 0;
        else
            ptr[ptrIndex][m] = ptr[ptrIndex][m] * boiso2 - ptr[bac - 1][m] * boiso1;
    }
    stp[ptrIndex] = getStartPoint(ptrIndex);
    if (stp[ptrIndex] != 99)
        reduce(ptrIndex);
}

void sort()
{
    for (int i = 0; i < numX; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (stp[i] < stp[j])
            {
                swapPtr(i, j);
                swapStp(i, j);
            }
        }
    }
}

void getInputByConsole()
{
    cout << "Nhap so an cua phuong trinh (Nhap so 0 de thoat): ";
    cin >> numX;
    if (numX == 0)
        exit(0);

    cout << "Tiep theo ban phai nhap tat ca " << numX << " phuong trinh. \n";
    cout << "Nhap he so va he so tu do (cach nhau boi space): \n";
    for (int i = 0; i < numX; i++)
    {
        cout << "Phuong trinh " << i + 1 << ":  ";
        for (int j = 0; j <= numX; j++)
            cin >> ptr[i][j];
        stp[i] = getStartPoint(i);
    }
    return;
}

void getInputByFile()
{
    ifstream fileInp("input.txt");

    if (fileInp)
    {
        fileInp >> numX;
        cout << numX;

        if (numX == 0)
            exit(0);

        for (int i = 0; i < numX; i++)
        {
            for (int j = 0; j <= numX; j++)
                fileInp >> ptr[i][j];
            stp[i] = getStartPoint(i);
        }
    }

    fileInp.close();
    return;
}

void createLadder()
{
    int vno = false;
    int vsn = false;
    for (int i = 0; i < numX; i++)
    {
        for (int j = i; j < numX; j++)
        {
            // cout << "Process " << i << " : " << j << "\n";
            reduceFreeNumber(i, j);
        }
        sort();
        showMatrix();
    }
}

bool solve()
{
    for (int i = numX - 1; i >= 0; i--)
    {
        float tmp = 0;
        for (int j = i + 1; j <= numX - 1; j++)
        {
            tmp += ptr[i][j] * output[j];
        }
        if ((ptr[i][i] == 0) && (i == numX - 1))
        {
            if (ptr[i][numX] == 0)
            {
                cout << "VO SO NGHIEM \n";
                return false;
            }
            else
            {
                cout << "VO NGHIEM \n";
                return false;
            }
        }
        else
            output[i] = (ptr[i][numX] * 1.0 - tmp) / ptr[i][i];
    }
    return true;
}

void menu()
{
    int select;
    cout << "1. Nhap bang console \n";
    cout << "2. Nhap bang file input.txt \n";
    cout << "Lua chon: ";
    cin >> select;
    switch (select)
    {
    case 1:
    {
        do
        {
            getInputByConsole();
            showMatrix();
            createLadder();

            if (solve())
                showOutput();
            system("pause");
        } while (true);
        break;
    }
    case 2:
    {
        getInputByFile();
        showMatrix();
        createLadder();

        if (solve())
            showOutput();
        system("pause");
    }

    default:
        break;
    }
}

int main()
{
    menu();
    return 0;
}
