#include <iostream>

void e() {
  std::cout << "=";
}

class V {
private:
  static int next_id;
  int id;
  int x;
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
    std::cout << "V " << id << " holds " << x << std::endl;
  }
  V(void) : x {0} { give_id(); }
  V(int x) : x {x} { give_id(); }
  V(const V& ov) : x {ov.x} { ov.pcp(); give_id();}
  V(V&& ov) : x {ov.x} { ov.pmv(); give_id(); } 
  V& operator=(const V& ov) { x = ov.x; e(); ov.pcp(); return *this; }
  V& operator=(const V&& ov) { x = ov.x; e(); ov.pmv(); return *this; }
 ~V(void) { pde(); }
  friend int operator+(int i, V&& v);
};

int operator+(int i, V&& v) { return i+v.x; }

int V::next_id = 0;

V f(V& v) {
  return v;
}

V g(V v) {
  return v;
}

V h(int a) {
  return V {a};
}


int main(void) {
  std::cout << "--- Line A" << std::endl;
  V v1 {1};
  std::cout << "--- Line B" << std::endl;
  V v2 {v1};
  std::cout << "--- Line C" << std::endl;
  V v4 = V{1 + V {3}};
  std::cout << "--- Line D" << std::endl;
  V v5 = f(v1);
  std::cout << "--- Line E" << std::endl;
  V v7 = g(v1);
  std::cout << "--- Line F" << std::endl;
  V v8 = h(7);
  std::cout << "--- Line G" << std::endl;
  V v9;
  v9 = v1;
  std::cout << "--- Line H" << std::endl;
  V v10;
  v10 = V{11};

  v1.pid();
  v2.pid();
  v4.pid();
  v5.pid();
  v7.pid();
  v8.pid();
  v9.pid();
  v10.pid();
}

      
