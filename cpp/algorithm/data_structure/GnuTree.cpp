#include "../../template/template.cpp"

#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#include<ext/pb_ds/tag_and_trait.hpp>
using namespace __gnu_pbds;
using namespace std;

using GnuTree = tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update>;

int main(){
  GnuTree t;
  int Q; cin >> Q;
  rep(i,Q){
    int a,b; scanf("%d%d",&a,&b);
    if(a==1){
      t.insert(b);
    }else{
      auto itr = t.find_by_order(b-1);
      printf("%d\n",*itr);
      t.erase(itr);
    }
  }
  return 0;
}