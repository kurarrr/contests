#include "../template/template.cpp"

template <typename T>
struct Compression{
  vector<T> ary;
  #ifdef DEBUG_IS_VALID
    bool built = false;
  #endif
  Compression() : ary(vector<T>()) {;}
  void push(T val){
    ary.push_back(val);
  }
  void build(){
    #ifdef DEBUG_IS_VALID
      built = true;
    #endif
    sort(ary.begin(), ary.end());
    ary.erase(unique(ary.begin(), ary.end()), ary.end());
  }
  int size(){
    #ifdef DEBUG_IS_VALID
      assert(built);
    #endif
    return ary.size();
  }
  T f(int idx){
    #ifdef DEBUG_IS_VALID
      assert(built);
    #endif
    assert(0 <= idx && idx < ary.size());
    return ary[idx];
  }
  int inv(T val){
    #ifdef DEBUG_IS_VALID
      assert(built);
    #endif
    int idx = int(lower_bound(ary.begin(), ary.end(), val) - ary.begin());
    return idx;
  }
};
