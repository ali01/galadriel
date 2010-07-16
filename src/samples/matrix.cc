#include <assert.h>
#include <stdlib.h>
#include <iostream>
#include <string>

template <class T>
struct Array {
    int n;
    T *e;
    Array(int n=0): n(n), e(new T[n]) {}
    ~Array() { delete e; }
    int length() { return n; }
    T& operator [](int i) {
       if(i<0 || i>=n)
           cout << "Decaf runtime error: Array subscript out of bounds" << endl, exit(0);
       else
           return e[i];
    }
};

void __Print(int i) { cout << i; }
void __Print(bool b) { cout << (b ? "true" : "false"); }
void __Print(double d) { cout << d; }
void __Print(char *s) { cout << s; }
void __Print(string s) { cout << s; }


inline int __checkarraysize(int i)
{
    if(i<0)
        cout << "Decaf runtime error: Array size is <= 0" << endl, exit(0);
    return i;
}

inline int __checkforzero(int i)
{
    if(!i)
        cout << "Decaf runtime error: Division by zero" << endl, exit(0);
    return i;
}

struct Matrix {
  virtual void Init() {
    {
      ;
    }

  }

  virtual void Set(int x, int y, int value) {
    {
      ;
    }

  }

  virtual int Get(int x, int y) {
    {
      ;
    }

  }

  virtual void PrintMatrix() {
    {
      int i;
      int j;
      for((i=0); (i<10); (i=(i+1))) {
        {
          for((j=0); (j<10); (j=(j+1))) {
            ::__Print (Get(i, j));
            ::__Print ("\t");
          ; }          ::__Print ("\n");
          ;
        }
      ; }      ;
    }

  }

  virtual void SeedMatrix() {
    {
      int i;
      int j;
      for((i=0); (i<5); (i=(i+1))) {
        for((j=0); (j<5); (j=(j+1))) {
          Set(i, j, (i+j));
        ; }      ; }      Set(2, 3, 4);
      Set(4, 6, 2);
      Set(2, 3, 5);
      Set(0, 0, 1);
      Set(1, 6, 3);
      Set(7, 7, 7);
      ;
    }

  }

};

struct Matrix;
struct DenseMatrix : public Matrix {
  Array<Array<int> * > *  m;
  virtual void Init() {
    {
      int i;
      int j;
      (m=(new Array<Array<int> * >(__checkarraysize(10))));
      for((i=0); (i<10); (i=(i+1))) {
        ((*(m))[i]=(new Array<int>(__checkarraysize(10))));
      ; }      for((i=0); (i<10); (i=(i+1))) {
        for((j=0); (j<10); (j=(j+1))) {
          ((*((*(m))[i]))[j]=0);
        ; }      ; }      ;
    }

  }

  virtual void Set(int x, int y, int value) {
    {
      ((*((*(m))[x]))[y]=value);
      ;
    }

  }

  virtual int Get(int x, int y) {
    {
      return (*((*(m))[x]))[y];
      ;
    }

  }

};

struct SparseItem;
struct SparseItem {
  int data;
  int y;
  SparseItem*  next;
  virtual void Init(int d, int y, SparseItem*  next) {
    {
      (this->data=d);
      (this->y=y);
      (this->next=next);
      ;
    }

  }

  virtual SparseItem*  GetNext() {
    {
      return next;
      ;
    }

  }

  virtual int GetY() {
    {
      return y;
      ;
    }

  }

  virtual int GetData() {
    {
      return data;
      ;
    }

  }

  virtual void SetData(int val) {
    {
      (data=val);
      ;
    }

  }

};

struct Matrix;
struct SparseItem;
struct SparseMatrix : public Matrix {
  Array<SparseItem* > *  m;
  virtual void Init() {
    {
      int i;
      (m=(new Array<SparseItem* >(__checkarraysize(10))));
      for((i=0); (i<10); (i=(i+1))) {
        ((*(m))[i]=0);
      ; }      ;
    }

  }

  virtual SparseItem*  Find(int x, int y) {
    {
      SparseItem*  elem;
      (elem=(*(m))[x]);
      while ((elem!=0)) {
        {
          if ((elem->GetY()==y)) {
            {
              return elem;
              ;
            }
          ; }
          (elem=elem->GetNext());
          ;
        }
      ; }
      return 0;
      ;
    }

  }

  virtual void Set(int x, int y, int value) {
    {
      SparseItem*  elem;
      (elem=Find(x, y));
      if ((elem!=0)) {
        {
          elem->SetData(value);
          ;
        }
      ; } else {
        {
          (elem=(new SparseItem()));
          elem->Init(value, y, (*(m))[x]);
          ((*(m))[x]=elem);
          ;
        }
      ; }
      ;
    }

  }

  virtual int Get(int x, int y) {
    {
      SparseItem*  elem;
      (elem=Find(x, y));
      if ((elem!=0)) {
        {
          return elem->GetData();
          ;
        }
      ; } else {
        {
          return 0;
          ;
        }
      ; }
      ;
    }

  }

};

void main() {
  {
    Matrix*  m;
    ::__Print ("Dense Rep \n");
    (m=(new DenseMatrix()));
    m->Init();
    m->SeedMatrix();
    m->PrintMatrix();
    ::__Print ("Sparse Rep \n");
    (m=(new SparseMatrix()));
    m->Init();
    m->SeedMatrix();
    m->PrintMatrix();
    ;
  }

}

