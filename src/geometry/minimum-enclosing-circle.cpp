Circle minimumEnclosingCost(vector<Point> v){
  // O(n^3) but if random_shuffle is used, it is amortized O(n)
  random_shuffle(v.begin(), v.end());
  Point p = {0, 0};
  ld r = 0; int n = v.size();
  for(int i=0; i<n; i++) if(dist(p, v[i]) > r){
    p = v[i], r = 0;
    for(int j=0; j<i; j++) if(dist(p, v[j]) > r){
      auto tmp=circle_from_2pts(v[i], v[j]);
      p = tmp.center, r = tmp.r;
      for(int k=0; k<j; k++) if(dist(p, v[k]) > r){
        auto tmp=circle_from_3pts(v[i], v[j], v[k]);
        p = tmp.center, r = tmp.r;
      }
    }
  }
  return {p, r};
}