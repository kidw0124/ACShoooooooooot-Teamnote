struct PST_Lazy{
    struct Node{ll l,r,v,prop;};
    vector<Node>nodes;vector<ll>root;vector<ll>arr;
    PST_Lazy(ll n=0,ll qmax=0){
        root.reserve(qmax+5);
        nodes.reserve(4*(n+1)+20*qmax+5);
        arr.resize(n+1);
        root.push_back(init(0,n));
    }
    ll init(ll s,ll e){
        ll cur=nodes.size();
        nodes.push_back({-1,-1,0,0});
        if(s<e){
            ll m=s+e>>1;
            nodes[cur].l=init(s,m),nodes[cur].r=init(m+1,e);
        }
        return cur;
    }
    ll add(ll s,ll e,ll pre,ll pos_l,ll pos_r,ll val){
        ll cur=nodes.size();
        nodes.push_back(nodes[pre]);
        if(pos_r<s||e<pos_l)return cur;
        if(pos_l<=s&&e<=pos_r){
            nodes[cur].v+=val*(e-s+1);
            nodes[cur].prop+=val;
            return cur;
        }
        ll m=s+e>>1;
        nodes[cur].l=add(s,m,nodes[pre].l,pos_l,pos_r,val);
        nodes[cur].r=add(m+1,e,nodes[pre].r,pos_l,pos_r,val);
        nodes[cur].v=nodes[nodes[cur].l].v+nodes[nodes[cur].r].v+nodes[cur].prop*(e-s+1);
        return cur;
    }
    ll query(ll s,ll e,ll u,ll v,ll l,ll r){
        if(r<s||e<l)return 0;
        if(l<=s&&e<=r)return nodes[v].v-nodes[u].v;
        ll m=s+e>>1;
        ll left=query(s,m,nodes[u].l,nodes[v].l,l,r);
        ll right=query(m+1,e,nodes[u].r,nodes[v].r,l,r);
        ll overlap=(min(e,r)-max(s,l)+1)*(nodes[v].prop-nodes[u].prop);
        return left+right+overlap;
    }
};