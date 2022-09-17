//FULLY MINIMIZED
#ifndef CHT
#define CHT
#include<algorithm>
#include<vector>
class static_cht{
private:
    //Find's maximum
    //Works when future_k less than last_k for all add_line
    using ll=long long;
    using ld=long double;
    std::vector<std::pair<ll,ll>>v;
    ld get_x(ld a1,ld b1,ld a2,ld b2){
        return(b2-b1)/(a1-a2);
    }
    ld get_x(std::pair<ll,ll>a,std::pair<ll,ll>b){
        return get_x(a.first,a.second,b.first,b.second);
    }
    ll evaluate(std::pair<ll,ll>a,ll x){
        return(ll)(a.first*x+a.second);
    }
    void add_line(std::pair<ll,ll>a){
        while(v.size()>=2&&get_x(a,v[v.size()-2])>get_x(v[v.size()-1],v[v.size()-2]))v.pop_back();
        v.push_back(a);
    }
    ll get_max(ll x){
        ll i,left,right,middle;
        if(v.size()==1)return evaluate(v[0],x);
        if(x<get_x(v[v.size()-1],v[v.size()-2]))return evaluate(v[v.size()-1],x);
        left=(-1);
        right=v.size()-2;
        while(right-left>1) {
            middle=(left+right)>>1;
            if(x>=get_x(v[middle],v[middle+1]))right=middle;
            else left=middle;
        }
        return evaluate(v[right],x);
    }
public:
    void addLine(ll k,ll b){
        add_line(std::make_pair(k,b));
    }
    ll getOpt(ll x){
        return get_max(x);
    }
};
class dynamic_cht{
private:
    using ll=long long;
    //Find's minimum
    struct Line{
        ll k,b;
        Line(ll _k,ll _b){k=_k,b=_b;}
        Line(){}
        ll cost(ll x){return k*x+b;}
    };
    struct node{
        Line line;
        node *lson,*rson;
        unsigned int used;
        ll tl,tr;
        node(ll tl_,ll tr_){
            tl=tl_,tr=tr_;
            lson=nullptr,rson=nullptr;
            line=Line();
            used=0;
        }
        node(){
            node(0,0);
        }
    };
    int vis_id=1;
    node* root;
    ll MIN_X,MAX_X,INF;
    void add_line(Line cur_line,node* vertex){
        ll &tl=vertex->tl;
        ll &tr=vertex->tr;
        if(vertex->used!=vis_id){
            vertex->line=cur_line;
            vertex->used=vis_id;
            return;
        }
        if(tl==tr){
            if(cur_line.cost(tl)<vertex->line.cost(tl))vertex->line=cur_line;
            return;
        }
        ll mid=(tl+tr)>>1;
        bool f_mid=cur_line.cost(mid+1)<vertex->line.cost(mid+1);
        bool f_tl=cur_line.cost(tl)<vertex->line.cost(tl);
        if(f_mid)std::swap(cur_line,vertex->line);
        if(f_mid==f_tl){
            if(vertex->rson==nullptr)vertex->rson=new node(mid+1,tr);
            add_line(cur_line,vertex->rson);
        }else{
            if(vertex->lson==nullptr)vertex->lson=new node(tl,mid);
            add_line(cur_line,vertex->lson);
        }
    }
    ll get_opt(ll x,node* vertex){
        ll &tl=vertex->tl;
        ll &tr=vertex->tr;
        if(vertex->used!=vis_id)return INF;
        if(tl==tr)return vertex->line.cost(x);
        ll mid=(tl+tr)>>1;
        if(x<=mid){
            if(vertex->lson==nullptr)vertex->lson=new node(tl,mid);
            return std::min(vertex->line.cost(x),get_opt(x,vertex->lson));
        }else{
            if (vertex->rson==nullptr)vertex->rson=new node(mid+1,tr);
            return std::min(vertex->line.cost(x),get_opt(x,vertex->rson));
        }
    }
public:
    dynamic_cht(ll _MIN_X,ll _MAX_X,ll _INF){
        MIN_X=_MIN_X;
        MAX_X=_MAX_X;
        INF=_INF;
        root=new node(MIN_X,MAX_X);
    }
    void addLine(ll k,ll b){
        add_line(Line(k,b),root);
    }
    ll getOpt(ll x){
        return get_opt(x,root);
    }
    void clean(){
        vis_id++;
    }
    void set_id(int id){
        vis_id=id;
    }
};
#endif
