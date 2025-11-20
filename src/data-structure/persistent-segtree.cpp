struct PST{
  struct Node{ll l,r,v;};
  vector<Node>nodes;vector<ll>root;
  PST(ll n=0,ll qmax=0){
    root.reserve(qmax+5);
    nodes.reserve(4*(n+1)+20*qmax+5);
    root.push_back(init(0,n));
  }
  ll init(ll s,ll e){
    ll cur=nodes.size();
    nodes.push_back({-1,-1,0});
    if(s<e){
        ll m=s+e>>1;
        nodes[cur].l=init(s,m),nodes[cur].r=init(m+1,e);
    }
    return cur;
  }
  ll add(ll s,ll e,ll pre,ll pos,ll val){
    ll cur=nodes.size();
    nodes.push_back(nodes[pre]);
    if(s==e){
        nodes[cur].v+=val;
        return cur;
    }
    ll m=s+e>>1;
    if(pos<=m)nodes[cur].l=add(s,m,nodes[pre].l,pos,val);
    else nodes[cur].r=add(m+1,e,nodes[pre].r,pos,val);
    nodes[cur].v=nodes[nodes[cur].l].v+nodes[nodes[cur].r].v;
    return cur;
  }
  ll query(ll s,ll e,ll u,ll v,ll l,ll r){
    if(r<s||e<l)return 0;
    if(l<=s&&e<=r)return nodes[v].v-nodes[u].v;
    ll m=s+e>>1;
    return query(s,m,nodes[u].l,nodes[v].l,l,r)
          +query(m+1,e,nodes[u].r,nodes[v].r,l,r);
  }
  // pst.init(0,n);
  // pst.add(0,n,prev_root,pos,val);
  // pst.query(0,n,root_u,root_v,l,r);
};