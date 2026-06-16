#include <iostream>
#include <cmath>
using namespace std;

struct diem
{
    double a = 0;
    double b = 0;
};

struct tamgiac
{
    diem A;
    diem B;
    diem C;
};

struct Danhsachdac
{
    int n = 0;
    tamgiac *arr = nullptr;
};

double KhoangCach(const diem &p1, const diem &p2)
{
    double num = sqrt(
        (p1.a - p2.a) * (p1.a - p2.a) +
        (p1.b - p2.b) * (p1.b - p2.b));
    return num;
}

bool KiemtTraTG(const tamgiac &t)
{
    double AB = KhoangCach(t.A, t.B);
    double AC = KhoangCach(t.A, t.C);
    double BC = KhoangCach(t.B, t.C);

    return AB + AC > BC && AB + BC > AC && AC + BC > AB;
}

double DienTichTG(const tamgiac &t)
{
    double P = 0;
    double AB = KhoangCach(t.A, t.B);
    double AC = KhoangCach(t.A, t.C);
    double BC = KhoangCach(t.B, t.C);
    P = (AB + AC + BC) / 2;
    return sqrt(P * (P - AB) * (P - AC) * (P - BC));
}

diem TrongTamTG(const tamgiac &t)
{
    diem G;
    G.a = (t.A.a + t.B.a + t.C.a) / 3;
    G.b = (t.A.b + t.B.b + t.C.b) / 3;
    return G;
}

// Định nghĩa toán tử nhập điểm
istream &operator>>(istream &in, diem &p)
{
    in >> p.a;
    in >> p.b;
    return in;
}
// Định nghĩa toán tử nhập tam giác
istream &operator>>(istream &in, tamgiac &t)
{
    cout << "\nCặp tạo độ 1 : ";
    in >> t.A;
    cout << "Cặp tạo độ 2 : ";
    in >> t.B;
    cout << "Cặp tạo độ 3 : ";
    in >> t.C;
    cout << endl;
    return in;
}

// Định nghĩa toán tử xuất điểm
ostream &operator<<(ostream &out, const diem &p)
{
    out << "(" << p.a << "," << p.b << ")";
    return out;
}
// Định nghĩa toán tử xuất tam giác
ostream &operator<<(ostream &out, const tamgiac &t)
{
    out << t.A << t.B << t.C;
    return out;
}

// Định nghĩa toán tử nhập ds tam giác
istream &operator>>(istream &input, Danhsachdac &D)
{
    cout << "So tam giac muon nhap : ";
    input >> D.n;
    cout << endl;
    D.arr = new tamgiac[D.n];
    for (int i = 0; i < D.n; i++)
    {
        while (true)
        {
            cout << "Nhap tam giac " << i + 1;
            input >> D.arr[i];
            if (KiemtTraTG(D.arr[i]))
            {
                break;
            }
            cout << "không hợp lệ !! \n";
        }
    }
    return input;
}

ostream &operator<<(ostream &output, const Danhsachdac &D)
{

    for (int i = 0; i < D.n; i++)
    {
        cout << "\nTam giac thu " << i + 1 << " : ";
        output << D.arr[i];
        cout << ", S = " << DienTichTG(D.arr[i]);
    }
    return output;
}

void SoSanhDT(const Danhsachdac &D)
{
    double S = 0;
    cout << "\nNhập diện tích so sánh : ";
    cin >> S;

    const double EPS = 1e-6;
    for (int i = 0; i < D.n; i++)
    {
        if (fabs(DienTichTG(D.arr[i]) - S) < EPS)
        {
            cout << D.arr[i] << ", S = " << DienTichTG(D.arr[i]);
        }
    }
}

// bubbleSort lớn đến nhỏ
void bubbleSort(Danhsachdac &D)
{
    const double EPS = 1e-6;
    for (int i = 0; i < D.n; i++)
    {
        for (int j = 0; j < D.n - i - 1; j++)
        {
            double S1 = DienTichTG(D.arr[j]);
            double S2 = DienTichTG(D.arr[j + 1]);
            if (S2 - S1 > EPS)
            {
                swap(D.arr[j], D.arr[j + 1]);
            }
        }
    }
}

void TimTGgannhau(Danhsachdac &D)
{
    if (D.n < 2)
    {
        cout << "Cần ít nhất 2 tam giác!\n";
        return;
    }
    tamgiac A = D.arr[0];
    tamgiac B = D.arr[1];

    double minkc = KhoangCach(
        TrongTamTG(D.arr[0]),
        TrongTamTG(D.arr[1]));

    const double EPS = 1e-6;
    for (int i = 0; i < D.n; i++)
    {
        for (int j = i + 1; j < D.n; j++)
        {
            diem G1 = TrongTamTG(D.arr[i]);
            diem G2 = TrongTamTG(D.arr[j]);
            double d = KhoangCach(G1, G2);
            if (d < minkc - EPS)
            {
                minkc = d;
                A = D.arr[i];
                B = D.arr[j];
            }
        }
    }
    cout << "tam giac 1: " << A;
    cout << "\ntam giac 2: " << B;
    cout << "\nkhoang cach la : " << minkc << endl;
}

void menu()
{
    Danhsachdac D;
    int choice;
    do
    {
        cout << endl;
        cout << "[1] Nhap danh sach\n";
        cout << "[2] In danh sach \n";
        cout << "[3] Tim kiem theo dien tich\n";
        cout << "[4] bubble sort lon -> nho\n";
        cout << "[5] Tim 2 tam giac gan nhat\n";
        cout << "[0] thoat\n";
        cout << "chon : ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            cin >> D;
            break;
        case 2:
            cout << D;
            break;
        case 3:
            SoSanhDT(D);
            break;
        case 4:
            bubbleSort(D);
            break;
        case 5:
            TimTGgannhau(D);
            break;
        }
    } while (choice != 0);
    delete[] D.arr;
}

int main()
{
    menu();
    return 0;
}