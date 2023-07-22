#include<stdio.h>
#include<math.h>
#include<string.h>
#include<ctype.h>
// Khai báo cấu trúc của một NODE 
struct Node {
  int data;
  struct Node *pLeft;
  struct Node *pRight;
}; 
typedef struct Node NODE;
// Khai bao NODE CÂY NHỊ PHÂN
typedef NODE *TREE;
// typedef struct Node *TREE cũng được 
void KhoiTaoCay (TREE &t){
    t=NULL;// Cây ban đầu rỗng
}
void ThemNodeVaoCay(TREE &t, int x) {
    // Kiểm tra cây có rỗng không
    if (t == NULL) {
        NODE *p = (NODE *)malloc(sizeof(NODE));
        if (p == NULL) {
            printf("\nKhong khoi tao duoc NODE.");
            exit(0);
        }
        p->data = x;
        p->pLeft = NULL;
        p->pRight = NULL;
        t = p; // Gán địa chỉ node mới tới con trỏ tại nơi gọi hàm
    }
    // Nếu cây đã tồn tại NODE
    else {
        // NHỎ QUA TRÁI -- LỚN QUA PHẢI
        // (NODE gốc) > (NODE thêm vào)
        if (t->data > x) {
            ThemNodeVaoCay(t->pLeft, x);
        }
        else if (t->data < x) {
            ThemNodeVaoCay(t->pRight, x);
        }
    }
}
void Xuat_Cay_NLR(TREE t) {
    if (t != NULL) {
        // Xuất thông tin node hiện tại
        printf("%d ", t->data);

        // Duyệt sang cây con bên trái
        Xuat_Cay_NLR(t->pLeft);

        // Duyệt sang cây con bên phải
        Xuat_Cay_NLR(t->pRight);
    }
}
int main() {
    TREE t;
    KhoiTaoCay(t);
    
    int arr[] = {5, 3, 7, 2, 4, 6, 8};
    // Tìm độ  dài  của cây nhị phân 
    int n = sizeof(arr) / sizeof(arr[0]);

    for (int i = 0; i < n; i++) {
        ThemNodeVaoCay(t, arr[i]);
    }
    // Xuất thông tin của cây nhị phân ra màn hình
    printf("Cay nhi phan: ");
    Xuat_Cay_NLR(t);

    return 0;
}
