#include <iostream>

void e() {
  std::cout << "=";
}

class R {
private:
  static int next_id;
  int id;
  int* a;
  void give_id() { 
    id = ++next_id;
    std::cout << "Constructing " << id << std::endl;
  }
  void pcp(void) const {
    std::cout << "Copying " << id << std::endl;
  }
  void pmv(void) const {
    std::cout << "Moving " << id << std::endl;
  }
  void pde(void) const {
    std::cout << "Destroying " << id << std::endl;
  }
public:
  void pid(void) const {
    if (a == nullptr) {
      std::cout << "R " << id << " holds nothing" << std::endl;
    } else {
      std::cout << "R " << id << " holds " << a[0] << std::endl;
    }
  }
  R(void) : a {nullptr} { give_id(); }
  R(int x0) : a {new int[1]} { a[0]=x0; give_id(); }
  R(const R& r) : a {r.a} { r.pcp(); give_id();}
  R(R&& r) : a {r.a} { r.pmv(); give_id(); } 
  R& operator=(const R& r) { a = r.a; e(); r.pcp(); return *this; }
  R& operator=(const R&& r) { a = r.a; e(); r.pmv(); return *this; }
  ~R(void) { pde(); if (a != nullptr) delete [] a; }
  friend int operator+(int i, R&& r);
};

int operator+(int i, R&& r) { return i+r.a[0]; }

int R::next_id = 0;

R f(R& r) {
  return r;
}

R g(R r) {
  return r;
}

R h(int a) {
  return R {a};
}


int main(void) {
  std::cout << "--- Line A" << std::endl;
  R r1 {1};
  std::cout << "--- Line B" << std::endl;
  R r2 {r1};
  std::cout << "--- Line C" << std::endl;
  R r4 = R{1 + R {3}};
  std::cout << "--- Line D" << std::endl;
  R r5 = f(r1);
  std::cout << "--- Line E" << std::endl;
  R r7 = g(r1);
  std::cout << "--- Line F" << std::endl;
  R r8 = h(7);
  std::cout << "--- Line G" << std::endl;
  R r9;
  r9 = r1;
  std::cout << "--- Line H" << std::endl;
  R r10;
  r10 = R{11};

  r1.pid();
  r2.pid();
  r4.pid();
  r5.pid();
  r7.pid();
  r8.pid();
  r9.pid();
  r10.pid();
}

      
