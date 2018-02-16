#ifndef MAXC
#define MAXC
#include <iostream>
#include <algorithm>
#include <assert.h>
class Qmax
{
    const bool* const* edgls;
    int pk, lv;
    const float Tlimit;
    class Vtxs
    {
        class Vtx
        {
            int i, d;
        public:
            void setI(const int i)
            {
                this->i = i;
            }
            int getI() const
            {
                return i;
            }
            void setDeg(int d)
            {
                this->d = d;
            }
            int getDeg() const
            {
                return d;
            }
        };
        Vtx *v;
        int sz;
        static bool descDeg(const Vtx vi, const Vtx vj)
        {
            return (vi.getDeg() > vj.getDeg());
        }
    public:
        Vtxs(int size) : sz(0)
        {
            v = new Vtx[size];
        }
        ~Vtxs () {}
        void dispose()
        {
            if (v) delete [] v;
        }
        void sort()
        {
            std::sort(v, v+sz, descDeg);
        }
        void initCol();
        void setDegs(Qmax&);
        int size() const
        {
            return sz;
        }
        void push(const int i)
        {
            v[sz++].setI(i);
        };
        void pop()
        {
            sz--;
        };
        Vtx& at(const int i) const
        {
            return v[i];
        };
        Vtx& end() const
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
        void push(const int i)
        {
            this->i[sz++] = i;
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
        int& at(const int i) const
        {
            return this->i[i];
        }
        ColorClass& operator=(const ColorClass& dh)
        {
            for (int j = 0; j < dh.sz; j++) i[j] = dh.i[j];
            sz = dh.sz;
            return *this;
        }
    };
    Vtxs V;
    ColorClass *C, _QMAX, Q;
    class StpCnt
    {
        int i, j;
    public:
        StpCnt() : i(0), j(0) {}
        void setI(const int i)
        {
            this->i = i;
        }
        int getI() const
        {
            return i;
        }
        void setJ(const int j)
        {
            this->j = j;
        }
        int getJ() const
        {
            return j;
        }
        void incI()
        {
            i++;
        }
    };
    StpCnt *S;
    bool isadjacent(const int i, const int j) const
    {
        return edgls[i][j];
    }
    bool cuttable(const int, const ColorClass&);
    void cut(const Vtxs&, Vtxs&);
    void coloration(Vtxs&);
    void expand(Vtxs);
    void recursiveExpand(Vtxs);
    void degSort(Vtxs &R)
    {
        R.setDegs(*this);
        R.sort();
    }
public:
    void maxc(int*&, int&);
    Qmax(const bool* const*, const int, const float=0.025);
    int steps() const
    {
        return pk;
    }
    ~Qmax()
    {
        if (C) delete [] C;
        if (S) delete [] S;
        V.dispose();
    };
};

Qmax::Qmax (const bool* const* graph, const int sz, const float tt) : pk(0), lv(1), Tlimit(tt), V(sz), Q(sz), _QMAX(sz)
{
    assert(graph!=0 && sz>0);
    for (int i=0; i < sz; i++) V.push(i);
    edgls = graph;
    C = new ColorClass[sz + 1];
    for (int i=0; i < sz + 1; i++) C[i].init(sz + 1);
    S = new StpCnt[sz + 1];
}

void Qmax::maxc(int* &Qmax, int &sz)
{
    V.setDegs(*this);
    V.sort();
    V.initCol();

    for (int i=0; i < V.size() + 1; i++)
    {
        S[i].setI(0);
        S[i].setJ(0);
    }
    recursiveExpand(V);
    Qmax = new int[_QMAX.size()];
    for (int i=0; i<_QMAX.size(); i++)
    {
        Qmax[i] = _QMAX.at(i);
    }
    sz = _QMAX.size();
}

void Qmax::Vtxs::initCol()
{
    const int maxDeg = v[0].getDeg();
    for (int i = 0; i < maxDeg; i++)
        v[i].setDeg(i + 1);
    for (int i = maxDeg; i < sz; i++)
        v[i].setDeg(maxDeg + 1);
}

void Qmax::Vtxs::setDegs(Qmax &m)
{
    for (int i=0; i < sz; i++)
    {
        int d = 0;
        for (int j=0; j < sz; j++)
            if (m.isadjacent(v[i].getI(), v[j].getI())) d++;
        v[i].setDeg(d);
    }
}

bool Qmax::cuttable(const int pi, const ColorClass &A)
{
    for (int i = 0; i < A.size(); i++)
        if (isadjacent(pi, A.at(i)))
            return true;
    return false;
}

void Qmax::cut(const Vtxs &A, Vtxs &B)
{
    for (int i = 0; i < A.size() - 1; i++)
    {
        if (isadjacent(A.end().getI(), A.at(i).getI()))
            B.push(A.at(i).getI());
    }
}

void Qmax::coloration(Vtxs &R)
{
    int j = 0;
    int maxno = 1;
    int kmin = _QMAX.size() - Q.size() + 1;
    C[1].rewind();
    C[2].rewind();
    int k = 1;
    for (int i=0; i < R.size(); i++)
    {
        int pi = R.at(i).getI();
        k = 1;
        while (cuttable(pi, C[k]))
            k++;
        if (k > maxno)
        {
            maxno = k;
            C[maxno + 1].rewind();
        }
        C[k].push(pi);
        if (k < kmin)
        {
            R.at(j++).setI(pi);
        }
    }
    if (j > 0) R.at(j-1).setDeg(0);
    if (kmin <= 0) kmin = 1;
    for (k = kmin; k <= maxno; k++)
        for (int i = 0; i < C[k].size(); i++)
        {
            R.at(j).setI(C[k].at(i));
            R.at(j++).setDeg(k);
        }
}

void Qmax::expand(Vtxs R)
{
    while (R.size())
    {
        if (Q.size() + R.end().getDeg() > _QMAX.size())
        {
            Q.push(R.end().getI());
            Vtxs Rp(R.size());
            cut(R, Rp);
            if (Rp.size())
            {
                coloration(Rp);
                pk++;
                expand(Rp);
            }
            else if (Q.size() > _QMAX.size())
            {
                std::cout << "etape n = " << pk << " taille de clique max = " << Q.size() << std::endl;
                _QMAX = Q;
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

void Qmax::recursiveExpand(Vtxs R)
{
    S[lv].setI(S[lv].getI() + S[lv - 1].getI() - S[lv].getJ());
    S[lv].setJ(S[lv - 1].getI());
    while (R.size())
    {
        if (Q.size() + R.end().getDeg() > _QMAX.size())
        {
            Q.push(R.end().getI());
            Vtxs Rp(R.size());
            cut(R, Rp);
            if (Rp.size())
            {
                if ((float)S[lv].getI()/++pk < Tlimit)
                {
                    degSort(Rp);
                }
                coloration(Rp);
                S[lv].incI();
                lv++;
                recursiveExpand(Rp);
                lv--;
            }
            else if (Q.size() > _QMAX.size())
            {
                std::cout << "etape n = " << pk << " taille de clique max= " << Q.size() << std::endl;
                _QMAX = Q;
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
