#ifndef MAXC
#define MAXC
#include <iostream>
#include <algorithm>
#include <assert.h>
class Maxclique
{
    const bool* const* e;
    int pk, lv;
    const float Tlimit;
    class Vertices
    {
        class Vertex
        {
            int i, d;
        public:
            void set_i(const int ii)
            {
                i = ii;
            }
            int get_i() const
            {
                return i;
            }
            void set_degree(int dd)
            {
                d = dd;
            }
            int get_degree() const
            {
                return d;
            }
        };
        Vertex *v;
        int sz;
        static bool desc_degree(const Vertex vi, const Vertex vj)
        {
            return (vi.get_degree() > vj.get_degree());
        }
    public:
        Vertices(int size) : sz(0)
        {
            v = new Vertex[size];
        }
        ~Vertices () {}
        void dispose()
        {
            if (v) delete [] v;
        }
        void sort()
        {
            std::sort(v, v+sz, desc_degree);
        }
        void init_colors();
        void set_degrees(Maxclique&);
        int size() const
        {
            return sz;
        }
        void push(const int ii)
        {
            v[sz++].set_i(ii);
        };
        void pop()
        {
            sz--;
        };
        Vertex& at(const int ii) const
        {
            return v[ii];
        };
        Vertex& end() const
        {
            return v[sz - 1];
        };
    };
    class ColorClass
    {
        int *i;
        int sz;
    public:
        ColorClass() : sz(0), i(0) {}
        ColorClass(const int sz) : sz(sz), i(0)
        {
            init(sz);
        }
        ~ColorClass()
        {
            if (i) delete [] i;
        }
        void init(const int sz)
        {
            i = new int[sz];
            rewind();
        }
        void push(const int ii)
        {
            i[sz++] = ii;
        };
        void pop()
        {
            sz--;
        };
        void rewind()
        {
            sz = 0;
        };
        int size() const
        {
            return sz;
        }
        int& at(const int ii) const
        {
            return i[ii];
        }
        ColorClass& operator=(const ColorClass& dh)
        {
            for (int j = 0; j < dh.sz; j++) i[j] = dh.i[j];
            sz = dh.sz;
            return *this;
        }
    };
    Vertices V;
    ColorClass *C, QMAX, Q;
    class StepCount
    {
        int i1, i2;
    public:
        StepCount() : i1(0), i2(0) {}
        void set_i1(const int ii)
        {
            i1 = ii;
        }
        int get_i1() const
        {
            return i1;
        }
        void set_i2(const int ii)
        {
            i2 = ii;
        }
        int get_i2() const
        {
            return i2;
        }
        void inc_i1()
        {
            i1++;
        }
    };
    StepCount *S;
    bool isadjacent(const int i, const int j) const
    {
        return e[i][j];
    }
    bool cut1(const int, const ColorClass&);
    void cut2(const Vertices&, Vertices&);
    void color_sort(Vertices&);
    void expand(Vertices);
    void expand_rec(Vertices);
    void degree_sort(Vertices &R)
    {
        R.set_degrees(*this);
        R.sort();
    }
public:
    void maxc(int*&, int&);
    Maxclique(const bool* const*, const int, const float=0.025);
    int steps() const
    {
        return pk;
    }
    ~Maxclique()
    {
        if (C) delete [] C;
        if (S) delete [] S;
        V.dispose();
    };
};

Maxclique::Maxclique (const bool* const* graph, const int sz, const float tt) : pk(0), lv(1), Tlimit(tt), V(sz), Q(sz), QMAX(sz)
{
    assert(graph!=0 && sz>0);
    for (int i=0; i < sz; i++) V.push(i);
    e = graph;
    C = new ColorClass[sz + 1];
    for (int i=0; i < sz + 1; i++) C[i].init(sz + 1);
    S = new StepCount[sz + 1];
}

void Maxclique::maxc(int* &maxclique, int &sz)
{
    V.set_degrees(*this);
    V.sort();
    V.init_colors();

    for (int i=0; i < V.size() + 1; i++)
    {
        S[i].set_i1(0);
        S[i].set_i2(0);
    }
    expand_rec(V);
    maxclique = new int[QMAX.size()];
    for (int i=0; i<QMAX.size(); i++)
    {
        maxclique[i] = QMAX.at(i);
    }
    sz = QMAX.size();
}

void Maxclique::Vertices::init_colors()
{
    const int max_degree = v[0].get_degree();
    for (int i = 0; i < max_degree; i++)
        v[i].set_degree(i + 1);
    for (int i = max_degree; i < sz; i++)
        v[i].set_degree(max_degree + 1);
}

void Maxclique::Vertices::set_degrees(Maxclique &m)
{
    for (int i=0; i < sz; i++)
    {
        int d = 0;
        for (int j=0; j < sz; j++)
            if (m.isadjacent(v[i].get_i(), v[j].get_i())) d++;
        v[i].set_degree(d);
    }
}

bool Maxclique::cut1(const int pi, const ColorClass &A)
{
    for (int i = 0; i < A.size(); i++)
        if (isadjacent(pi, A.at(i)))
            return true;
    return false;
}

void Maxclique::cut2(const Vertices &A, Vertices &B)
{
    for (int i = 0; i < A.size() - 1; i++)
    {
        if (isadjacent(A.end().get_i(), A.at(i).get_i()))
            B.push(A.at(i).get_i());
    }
}

void Maxclique::color_sort(Vertices &R)
{
    int j = 0;
    int maxno = 1;
    int min_k = QMAX.size() - Q.size() + 1;
    C[1].rewind();
    C[2].rewind();
    int k = 1;
    for (int i=0; i < R.size(); i++)
    {
        int pi = R.at(i).get_i();
        k = 1;
        while (cut1(pi, C[k]))
            k++;
        if (k > maxno)
        {
            maxno = k;
            C[maxno + 1].rewind();
        }
        C[k].push(pi);
        if (k < min_k)
        {
            R.at(j++).set_i(pi);
        }
    }
    if (j > 0) R.at(j-1).set_degree(0);
    if (min_k <= 0) min_k = 1;
    for (k = min_k; k <= maxno; k++)
        for (int i = 0; i < C[k].size(); i++)
        {
            R.at(j).set_i(C[k].at(i));
            R.at(j++).set_degree(k);
        }
}

void Maxclique::expand(Vertices R)
{
    while (R.size())
    {
        if (Q.size() + R.end().get_degree() > QMAX.size())
        {
            Q.push(R.end().get_i());
            Vertices Rp(R.size());
            cut2(R, Rp);
            if (Rp.size())
            {
                color_sort(Rp);
                pk++;
                expand(Rp);
            }
            else if (Q.size() > QMAX.size())
            {
                std::cout << "etape = " << pk << " taille de clique max = " << Q.size() << std::endl;
                QMAX = Q;
            }
            Rp.dispose();
            Q.pop();
        }
        else
        {
            return;
        }
        R.pop();
    }
}

void Maxclique::expand_rec(Vertices R)
{
    S[lv].set_i1(S[lv].get_i1() + S[lv - 1].get_i1() - S[lv].get_i2());
    S[lv].set_i2(S[lv - 1].get_i1());
    while (R.size())
    {
        if (Q.size() + R.end().get_degree() > QMAX.size())
        {
            Q.push(R.end().get_i());
            Vertices Rp(R.size());
            cut2(R, Rp);
            if (Rp.size())
            {
                if ((float)S[lv].get_i1()/++pk < Tlimit)
                {
                    degree_sort(Rp);
                }
                color_sort(Rp);
                S[lv].inc_i1();
                lv++;
                expand_rec(Rp);
                lv--;
            }
            else if (Q.size() > QMAX.size())
            {
                std::cout << "etape = " << pk << " taille de clique max= " << Q.size() << std::endl;
                QMAX = Q;
            }
            Rp.dispose();
            Q.pop();
        }
        else
        {
            return;
        }
        R.pop();
    }
}
#endif //MAXC
