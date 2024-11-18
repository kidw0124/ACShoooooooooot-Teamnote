// O(n^2) stable marriage 1-based index
// a[i][j] : i번째 그룹의 j번째 원소가 선호하는 두 번째 그룹의 원소
// b[i][j] : 두 번째 그룹의 i번째 원소가 선호하는 첫 번째 그룹의 원소
// x[i] : 첫 번째 그룹의 i번째 원소가 매칭된 두 번째 그룹의 원소
// y[i] : 두 번째 그룹의 i번째 원소가 매칭된 첫 번째 그룹의 원소
void matching(vector<vector<int>> &a, vector<vector<int>> &b, vector<int> &x, vector<int> &y) {
    int k, n = a.size() - 1;
    vector<int> p(n + 1);
    for(int i = 1; i <= n; i++) x[i] = y[i] = p[i] = 0;
    for(int t = 1; t <= n; t++) {
        for(int i = 1; i <= n; i++){
            if(x[i])continue;
            for(; ++p[i]; ){
                int w = a[i][p[i]];
                if(!y[w]){
                    x[i] = w;
                    y[w] = i;
                    break;
                }
                if(b[w][i] < b[w][y[w]]){
                    x[i] = w;
                    x[y[w]] = 0;
                    y[w] = i;
                    break;
                }
            }
        }
    }
}