#include <iostream>
#include <iomanip>

using namespace std;
using std::setw;

int numX;
int ptr[50][50];
int stp[50];

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
    cout << "F: " << a << " " << b;
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
    int startPoint = stp[ptrIndex];
    int uc = ptr[ptrIndex][startPoint];
    for (int i = startPoint + 1; i <= numX; i++)
    {
        uc = UCLN(uc, ptr[ptrIndex][i]);
    }
    for (int i = startPoint; i <= numX; i++)
    {
        ptr[ptrIndex][i] = ptr[ptrIndex][i] / uc;
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

void getInput()
{
    cout << "Nhap so an cua phuong trinh: ";
    cin >> numX;
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

void createLadder()
{
    int vno = false;
    int vsn = false;
    for (int i = 0; i < numX; i++)
    {
        for (int j = i; j < numX; j++)
        {
            reduceFreeNumber(i, j);
        }
        sort();
        showMatrix();
    }
}

void solve(){
    
}

int main()
{
    getInput();
    showMatrix();
    createLadder();

    solve();
    system("pause");
    return 0;
}