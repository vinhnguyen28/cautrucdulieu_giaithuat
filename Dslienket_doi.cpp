#include <iostream>
using namespace std;

struct Node
{
    int info = -1;
    Node *next, *previous;

    Node(int value)
    {
        info = value;
        next = nullptr;
        previous = nullptr;
    }
};

class Doubly_linked_list
{
private:
    Node *first;
    Node *last;

public:
    Doubly_linked_list()
    {
        first = nullptr;
        last = nullptr;
    }

    // Nhập
    void Input()
    {
        int number = -1;
        cout << "\n- Số lượng phần tử cần thêm: ";
        cin >> number;

        for (int i = 0; i < number; i++)
        {
            int value = -1;
            cout << "   Phần tử thứ " << i + 1 << " : ";
            cin >> value;
            Khoi_tao(value);
        }
    }

    // Xuất
    void Output()
    {
        if (first == nullptr)
        {
            cout << "Không có ds để Xuất\n";
            return;
        }

        Node *p = first;
        cout << "\n- xuất : ";
        while (p != nullptr)
        {
            cout << p->info << " ";
            p = p->next;
        }
        cout << endl;
    }

    // Khởi tạo ds ban đầu
    void Khoi_tao(int value)
    {
        Node *p = new Node(value);
        if (first == nullptr)
        {
            first = p;
            last = p;
        }
        else
        {
            last->next = p;
            p->previous = last;
            last = p;
        }
    }

    // search theo vị trí
    // Tìm kiếm giá trị người dùng nhập vào
    Node *search_index(int value)
    {
        Node *p = first;
        while (p != nullptr)
        {
            if (p->info == value)
            {
                return p;
            }
            p = p->next;
        }
        return nullptr;
    }

    // Tìm kiếm vị trí thêm giá trị
    Node *search_location(int index)
    {
        int A = 0;
        Node *p = first;
        while (p != nullptr)
        {
            A++;
            if (A == index)
            {
                return p;
            }
            p = p->next;
        }
        return nullptr;
    }

    // đến số phần tử
    int Dem()
    {
        Node *p = first;
        int sum = 0;
        while (p != nullptr)
        {
            sum++;
            p = p->next;
        }
        return sum;
    }

    // =============
    // Thêm phần tử
    // =============
    void AddElement()
    {
        int n_phan_tu = Dem();
        // Số lượng thêm
        int Soluong = -1;
        cout << "\n- Số phần tử muốn thêm vào danh sách : ";
        cin >> Soluong;

        // vị trí thêm
        int vitri = -1;
        while (vitri <= 0 || vitri > n_phan_tu)
        {
            cout << "- Nhập ví trí muốn thêm từ 1 -> " << n_phan_tu << " : ";
            cin >> vitri;
        }

        // front & back (lựa chọn thêm trước, sau)
        int before_after = -1;
        while (before_after != 1 && before_after != 2)
        {
            cout << "- Chọn ví trí muốn thêm\n";
            cout << "[1] Phía trước\n";
            cout << "[2] Phía sau\n";
            cout << "chọn : ";
            cin >> before_after;
        }

        // Nhập phần tử (Pt muốn thêm)
        Node *first_AddElement = nullptr;
        Node *last_AddElement = nullptr;
        for (int i = 0; i < Soluong; i++)
        {
            int info = -1;
            cout << "Nhập giá trị thứ " << i + 1 << " : ";
            cin >> info;

            Node *p = new Node(info);
            if (first_AddElement == nullptr)
            {
                first_AddElement = p;
                last_AddElement = p;
            }
            else
            {
                last_AddElement->next = p;
                p->previous = last_AddElement;
                last_AddElement = p;
            }
        }

        // ================
        // thêm theo vị trí
        // ================

        // Thêm đầu
        if (vitri == 1)
        {
            // phí trước phần tử đầu
            if (before_after == 1)
            {
                Node *p = first;
                first = first_AddElement;
                last_AddElement->next = p;
                p->previous = last_AddElement;
            }
            // phí sau phần tử đầu
            else
            {
                // Gắn đuôi
                Node *p = first->next;
                p->previous = last_AddElement;
                last_AddElement->next = p;

                // Gắn đầu
                first->next = first_AddElement;
                first_AddElement->previous = first;
            }
        }
        // Thêm sau first
        if (vitri > 1 && vitri <= n_phan_tu)
        {
            Node *p = search_location(vitri);
            // chèn phía trước
            if (before_after == 1)
            {
                // Gắn đầu
                Node *p_before = p->previous;
                p_before->next = first_AddElement;
                first_AddElement->previous = p_before;

                // Gắn đuôi
                last_AddElement->next = p;
                p->previous = last_AddElement;
            }
            // chèn phía sau
            else
            {
                if (vitri == n_phan_tu && before_after == 2)
                {
                    // Gắn đầu
                    p->next = first_AddElement;
                    first_AddElement->previous = p;
                }
                else
                {
                    // Gắn đuôi
                    Node *p_after = p->next;
                    last_AddElement->next = p_after;
                    p_after->previous = last_AddElement;

                    // Gắn đầu
                    p->next = first_AddElement;
                    first_AddElement->previous = p;
                }
            }
        }
    }

    void DeleteElement()
    {
        if (first == nullptr)
        {
            cout << "Không có ds để xoá\n";
            return;
        }
        // xoá theo vị trí
        int n_phan_tu = Dem();

        int select = -1;
        while (select != 1 && select != 2)
        {
            cout << "\n==== Delete ====\n";
            cout << "[1] Xoá theo vị trí.\n";
            cout << "[2] Xoá hết theo giá trị.\n";
            cout << "Chọn : ";
            cin >> select;
        }

        if (select == 1)
        {
            int element = -1;
            while (element <= 0 || element > n_phan_tu)
            {
                cout << "- vị trí muốn xoá từ 1 -> " << n_phan_tu << " : ";
                cin >> element;
            }

            Node *p = search_location(element);
            // Xoá Đầu
            if (element == 1)
            {
                Node *p_element = first->next;
                p_element->previous = nullptr;
                delete first;
                first = p_element;
            }
            // Xoá cuối
            else if (element == n_phan_tu)
            {
                Node *truoc = p->previous;
                truoc->next = nullptr;
                delete p;
            }
            // Xoá giữa
            else
            {
                Node *truoc = p->previous;
                Node *sau = p->next;
                truoc->next = sau;
                sau->previous = truoc;
                delete p;
            }
        }
        // xoá theo giá trị
        else
        {
            int number = -1;
            cout << "Giá trị muốn xoá : ";
            cin >> number;

            // Xoá đầu
            if (first->info == number)
            {
                while (first->info == number)
                {
                    Node *p = first->next;
                    p->previous = nullptr;
                    delete first;
                    first = p;
                }
            }
            Node *p_delete = first->next;
            while (p_delete != nullptr)
            {
                Node *p_dl = p_delete;
                p_delete = p_delete->next;
                if (p_dl->info == number)
                {
                    // xoá cuối
                    if (p_dl->next == nullptr)
                    {
                        Node *p = p_dl->previous;
                        p->next = nullptr;
                        delete p_dl;
                        return;
                    }
                    // xoá giữa
                    else
                    {
                        Node *truoc = p_dl->previous;
                        Node *sau = p_dl->next;
                        truoc->next = sau;
                        sau->previous = truoc;
                        delete p_dl;
                    }
                }
            }
        }
    }

    void clear()
    {
        Node *p = first;
        Node *last = first;
        while (p != nullptr)
        {
            p = p->next;
            delete last;
            last = p;
        }
    }

    ~Doubly_linked_list()
    {
        Node *p = first;
        Node *last = first;
        while (p != nullptr)
        {
            p = p->next;
            delete last;
            last = p;
        }
    }
};

void menu()
{
    Doubly_linked_list ds;
    int choice = -1;

    do
    {
        cout << "\n=====MENU=====\n";
        cout << "[1] Nhập danh sách\n";
        cout << "[2] In danh sách \n";
        cout << "[3] Thêm phần tử vào ds\n";
        cout << "[4] Xoá phần tử khỏi ds\n";
        cout << "[0] Thoát";
        cout << "chọn : ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            ds.Input();
            break;
        case 2:
            ds.Output();
            break;
        case 3:
            ds.AddElement();
            break;
        case 4:
            ds.DeleteElement();
        }
    } while (choice != 0);
    ds.clear();
}

int main()
{
    menu();
    return 0;
}