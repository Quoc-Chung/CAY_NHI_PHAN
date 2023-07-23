#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>
struct Person {
    char HoTen[50];
    int Tuoi;
    float ChieuCao;
};
struct Node{
    Person data;
    struct Node *pLeft;
    struct Node *pRight;
}; typedef struct Node NODE;
   typedef NODE *TREE;

void DocFile(Person **p ,int &n, char *tentep){
    FILE *f=fopen(tentep,"r");
    if(f==NULL ){
        printf("\nKhong the mo duoc file.");
        exit(0);
    }
    fscanf(f,"%d",&n);
    (*p)=(Person *) malloc(n*sizeof(Person));
    for (int i=0;i<n;i++){
        fscanf(f," %[^\n]",(*p)[i].HoTen);
        fscanf(f,"%d",&(*p)[i].Tuoi);
        fscanf(f,"%f",&(*p)[i].ChieuCao);
    }
    fclose(f);
}
void ThongTinFile (Person *p,int n){
    printf("\nThong tin cua file la :\n");
    for(int i=0;i<n;i++){
        printf("\nHo Ten :%s --- Tuoi :%d ---Chieu cao :%.2f",p[i].HoTen,p[i].Tuoi,p[i].ChieuCao);
    }
}
NODE* KhoiTaoNode(Person p){
   NODE *p1 =(NODE *) malloc (sizeof(NODE));
   if(p1==NULL){
    printf("\nKhong the mo duoc file.");
    exit(0);
   }
     p1->data =p;
     p1->pLeft=NULL;
     p1->pRight=NULL;
  return p1;
}
void KhoiTaoCay(TREE &t){
    t=NULL;
}
void ThemNodeVaoCay(TREE &t, Person p) {
   if (t == NULL) {
      // Nếu cây đang rỗng thì khởi tạo NODE gốc cho cây
      t = KhoiTaoNode(p);
      return;
   }

   // < 0 là pLeft   ---   >0 là pRight
   if (strcmp(p.HoTen, t->data.HoTen) < 0) {
      ThemNodeVaoCay(t->pLeft, p);
   } else if (strcmp(p.HoTen, t->data.HoTen) > 0) {
      ThemNodeVaoCay(t->pRight, p);
   } else {
      printf("\nKhong the them vao vi da ton tai trong cay.");
   }
}

void DuyetCay_LNR(TREE t){
    if(t!= NULL){
        DuyetCay_LNR(t->pLeft);
        printf("\n%s -- %d -- %.2f",t->data.HoTen,t->data.Tuoi,t->data.ChieuCao);
        DuyetCay_LNR(t->pRight);
    }
}
// Hàm giải phóng bộ nhớ của cây
void GiaiPhongCay(TREE &t) {
    if (t != NULL) {
        GiaiPhongCay(t->pLeft);
        GiaiPhongCay(t->pRight);
        free(t);
        t = NULL;
    }
}
NODE* TimKiemNode(TREE t,char *Ten_Search){
    // Kiểm tra xem cây có rỗng không  
  if(t==NULL){
    return NULL;
  }
  if(strcmp(Ten_Search ,t->data.HoTen) <0 ){
     return TimKiemNode(t->pLeft,Ten_Search);
  }
  else if(strcmp(Ten_Search,t->data.HoTen) > 0){
    return TimKiemNode(t->pRight,Ten_Search);
  }
  else {
    return t;
  }
}
int main() {
   int n;
   TREE t = NULL; // Khởi tạo cây
   Person *p;
   char tentep[50] = "Person.txt";
   DocFile(&p, n, tentep);
   ThongTinFile(p, n);
   
   // Thêm dòng sau để cấp phát bộ nhớ cho cây
   for (int i = 0; i < n; i++) {
       ThemNodeVaoCay(t, p[i]);
   }

   printf("\nThong tin duyet cay la :\n");
   DuyetCay_LNR(t);

   // Giải phóng bộ nhớ cho mảng p sau khi không sử dụng nữa

   char Ten_Search[50];
   printf("\nNhap ten tim kiem :");
   fflush(stdin);
   gets(Ten_Search);
   NODE* ketQua = TimKiemNode(t, Ten_Search);
   if (ketQua != NULL) {
       // In thông tin của NODE cần tìm kiếm
       printf("\nTim thay NODE co ten: %s - Tuoi: %d - Chieu cao: %.2f", 
              ketQua->data.HoTen, ketQua->data.Tuoi, ketQua->data.ChieuCao);
   } else {
       printf("\nKhong tim thay NODE co ten: %s", Ten_Search);
   }


   free(p);
   // Giải phóng bộ nhớ cho cây sau khi đã sử dụng xong
   GiaiPhongCay(t);
}

