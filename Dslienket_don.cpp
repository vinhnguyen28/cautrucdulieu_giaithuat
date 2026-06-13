
#include <iostream>
using namespace std;

// khởi tạo node
struct Node
{
    int number;
    Node *next;
    Node(int value)
    {
        number = value;
        next = nullptr;
    }
};

Node *first = nullptr;

// Nhập liên kết đơn
void NhapLKD()
{
    int num;
    cout << "nhập số lượng LK : ";
    cin >> num;
    Node *last;
    for (int i = 0; i < num; i++)
    {
        Node *p;
        int number;
        cout << "nhập phần tử thứ " << i + 1 << ": ";
        cin >> number;
        p = new Node(number);
        if (i == 0)
        {
            first = p;
        }
        else
        {
            last->next = p;
        }
        last = p;
    }
}

// xuất liên kết đơn
void XuatLKD()
{
    if (first == nullptr)
    {
        cout << "\nDanh sách rỗng.\n";
        return;
    }

    Node *p = first;
    cout << endl;
    while (p != nullptr)
    {
        cout << p->number << " ";
        p = p->next;
    }
    cout << endl;
}

// Tìm kiếm phần tử
void Search()
{
    if (first == nullptr)
    {
        cout << "\nDanh sách rỗng, không thể tìm kiếm phần tử.\n";
        return;
    }

    Node *p = first;
    // Node *last = first;
    int x;
    cout << "\nPhần tử muốn tìm kiếm là : ";
    cin >> x;
    while (p != nullptr && p->number != x)
    {
        // last = p;
        p = p->next;
    }
    if (p != nullptr)
    {
        cout << p->number << " ở địa chỉ : " << p << endl;
        return;
    }
    cout << "không có giá trị : " << x;
}

// Đếm số lượng phần tử
int SoLuongPhanTu()
{
    int A = 0;
    Node *p = first;

    if (p == nullptr)
        return 0;

    while (p->next != nullptr)
    {
        A += 1;
        p = p->next;
    }
    return A + 1;
}

// thêm phần tử
void AddElement()
{
    if (first == nullptr)
    {
        cout << "\nDanh sách rỗng, không thể thêm phần tử.\n";
        return;
    }
    // Số lượng thêm
    int num;
    cout << "Số lượng phần tử muốn thêm : ";
    cin >> num;

    // phần tử cần thêm
    Node *first_Element = nullptr;
    Node *last_Element = nullptr;
    for (int i = 0; i < num; i++)
    {
        Node *p;
        int number;
        cout << "Nhập phần tử thứ " << i + 1 << " : ";
        cin >> number;
        p = new Node(number);
        if (i == 0)
        {
            first_Element = p;
        }
        else
        {
            last_Element->next = p;
        }
        last_Element = p;
    }

    // Vị trí muốn thêm
    int vitri = 0;
    int before_after = 0;
    cout << "\n====== CHỌN ======";

    while (vitri > SoLuongPhanTu() || vitri <= 0)
    {
        cout << "\nVị trí có thể thêm vào từ 1 đến " << SoLuongPhanTu() << endl;
        cout << "Nhập : ";
        cin >> vitri;
    }

    while (before_after != 1 && before_after != 2)
    {
        cout << "\n[1] Thêm vào trước\n";
        cout << "[2] Thêm vào sau\n";
        cout << "Chọn : ";
        cin >> before_after;
    }

    if (vitri == 1)
    {
        if (before_after == 1)
        {
            Node *p = first;
            first = first_Element;
            last_Element->next = p;
        }
        else
        {
            Node *p = first->next;
            first->next = first_Element;
            last_Element->next = p;
        }
    }
    else if (vitri > 1)
    {
        int A = 1;
        Node *p = first;
        Node *last = nullptr;

        while (A != vitri)
        {
            A += 1;
            last = p;
            p = p->next;
        }

        if (before_after == 1)
        {
            Node *p2 = last->next;
            last->next = first_Element;
            last_Element->next = p2;
        }
        else
        {
            Node *p2 = p->next;
            p->next = first_Element;
            last_Element->next = p2;
        }
    }
}
// ===============
// xoá phần tử
// ===============
void Delete()
{
    if (first == nullptr)
    {
        cout << "\nDanh sách rỗng, không thể xoá phần tử.\n";
        return;
    }
    int n = SoLuongPhanTu();
    int dl = 0;

    cout << "\n=== Xoá Phần Tử ===\n";
    cout << "[1] Xoá theo STT\n";
    cout << "[2] Xoá theo giá trị\n";
    while (dl != 1 && dl != 2)
    {
        cout << "Chọn : ";
        cin >> dl;
    }
    // xoá theo số thứ tự
    if (dl == 1)
    {
        int Num_delete = 0;
        while (Num_delete <= 0 || Num_delete > n)
        {
            cout << "Chọn STT từ 1 --> " << n << " : ";
            cin >> Num_delete;
            if (Num_delete <= 0 || Num_delete > n)
            {
                cout << "STT Sai\n";
            }
        }

        if (Num_delete == 1)
        {
            // xoá phần tử đầu
            Node *p = first;
            first = first->next;
            delete p;
        }
        else
        {
            // xoá phần tử > 1
            int A = 1;
            Node *p = first;
            Node *last = nullptr;
            while (A != Num_delete)
            {
                A++;
                last = p;
                p = p->next;
            }
            Node *ptr = p;
            last->next = p->next;
            delete ptr;
            cout << "Đã xoá ...";
        }
    }
    // xoá phần tử theo giá trị
    else
    {

        int number = 0;
        cout << "Giá trị muốn xoá hết : ";
        cin >> number;

        // Xoá phần tử đầu tiên
        while (first != nullptr && first->number == number)
        {
            Node *ptr = first;
            first = first->next;
            delete ptr;
        }

        // Xoá hết phần tử sau first
        Node *p = first;
        Node *last = nullptr;
        while (p != nullptr)
        {
            if (first != nullptr && p->number == number)
            {
                last->next = p->next;
                delete p;
                p = last->next;
            }
            else
            {
                last = p;
                p = p->next;
            }
        }
    }
}
// xóa toàn bộ liên kết đơn
void DeleteList()
{
    Node *p = first;
    while (p != nullptr)
    {
        Node *temp = p->next;
        delete p;
        p = temp;
    }
    first = nullptr;
}

// Menu
void Menu()
{
    int choice;
    do
    {
        cout << "\n===== Menu =====\n";
        cout << "[1] Nhập liên kết đơn\n";
        cout << "[2] Xuất liên kết đơn\n";
        cout << "[3] Tìm kiếm phần tử\n";
        cout << "[4] Thêm phần tử\n";
        cout << "[5] Xoá phần tử\n";
        cout << "[0] Thoát\n";
        cout << "Chọn : ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            NhapLKD();
            break;
        case 2:
            XuatLKD();
            break;
        case 3:
            Search();
            break;
        case 4:
            AddElement();
            break;
        case 5:
            Delete();
            break;
        case 0:
            cout << "Thoát chương trình ...\n";
            break;
        default:
            cout << "Lựa chọn khdông hợp lệ. Vui lòng chọn lại.\n";
            break;
        }
    } while (choice != 0);
    DeleteList();
}

int main()
{
    Menu();
    return 0;
}