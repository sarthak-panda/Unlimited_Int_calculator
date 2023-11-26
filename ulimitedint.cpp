/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "ulimitedint.h"
using namespace std;
void intzck(string &s)
{
    if (s.length() > 1)
    {
        if (s[0] == '0')
        {
            while (s.length() > 1)
            {
                if (s[0] == '0')
                {
                    s.erase(s.begin());
                }
                else
                {
                    break;
                }
            }
        }
    }
}
UnlimitedInt::UnlimitedInt()
{
    size = 1;
    sign = 0;
    capacity = 1;
    unlimited_int = new int[1];
}
UnlimitedInt::UnlimitedInt(string s)
{
    int c = s.length();
    if (s[0] == '-')
    {
        capacity = (c - 1);
        size = c - 1;
        sign = -1;
        unlimited_int = new int[capacity];
        for (long unsigned int x = 1; x < s.length(); x++)
        {
            unlimited_int[c - size + x - 2] = s[x] - '0';
        }
    }
    else if (s[0] == '0')
    {
        size = 1;
        sign = 0;
        capacity = 1;
        unlimited_int = new int[1];
        unlimited_int[0] = 0;
    }
    else
    {
        capacity = c;
        size = c;
        sign = 1;
        unlimited_int = new int[capacity];
        for (long unsigned int x = 0; x < s.length(); x++)
        {
            unlimited_int[c - size + x] = s[x] - '0';
        }
    }
}
UnlimitedInt::UnlimitedInt(int i)
{
    string s = std::to_string(i);
    int c = s.length();
    if (s[0] == '-')
    {
        capacity = (c - 1);
        size = c - 1;
        sign = -1;
        unlimited_int = new int[capacity];
        for (long unsigned int x = 1; x < s.length(); x++)
        {
            unlimited_int[c - size + x - 2] = s[x] - '0';
        }
    }
    else if (s[0] == '0')
    {
        size = 1;
        sign = 0;
        capacity = 1;
        unlimited_int = new int[1];
        unlimited_int[0] = 0;
    }
    else
    {
        capacity = c;
        size = c;
        sign = 1;
        unlimited_int = new int[capacity];
        for (long unsigned int x = 0; x < s.length(); x++)
        {
            unlimited_int[c - size + x] = s[x] - '0';
        }
    }
}
UnlimitedInt::~UnlimitedInt()
{
    capacity = 0;
    size = 0;
    sign = 0;
    delete[] unlimited_int;
}
int UnlimitedInt::get_size()
{
    return size;
}
int *UnlimitedInt::get_array()
{
    return unlimited_int;
}
int UnlimitedInt::get_sign()
{
    return sign;
}
UnlimitedInt *A(UnlimitedInt *i1, UnlimitedInt *i2)
{
    string s = "";
    int carry = 0;
    int temp, t;
    int k = (i2->get_size()) - 1;
    for (int j = (i1->get_size() - 1); j >= 0; j--)
    {
        if (k >= 0)
        {
            temp = (i1->get_array())[j] + (i2->get_array())[k] + carry;
            t = temp % 10;
            carry = (temp - t) / 10;
            k--;
            s = std::to_string(t) + s;
        }
        else
        {
            temp = (i1->get_array())[j] + carry;
            t = temp % 10;
            carry = (temp - t) / 10;
            s = std::to_string(t) + s;
        }
    }
    if (carry > 0)
    {
        s = std::to_string(carry) + s;
    }
    intzck(s); //////////
    UnlimitedInt *U = new UnlimitedInt(s);
    return U;
}
UnlimitedInt *UnlimitedInt::add(UnlimitedInt *i1, UnlimitedInt *i2)
{
    int sgn1 = i1->sign;
    int sgn2 = i2->sign;
    if (sgn1 == 0)
    {
        UnlimitedInt *u = new UnlimitedInt(i2->to_string());
        u->sign = i2->sign;
        return u;
    }
    else if (sgn2 == 0)
    {
        UnlimitedInt *u = new UnlimitedInt(i1->to_string());
        u->sign = i1->sign;
        return u;
    }
    else if (sgn1 == 1 and sgn2 == -1)
    {
        i2->sign = 1;
        UnlimitedInt *r = sub(i1, i2);
        i2->sign = -1;
        return r;
    }
    else if (sgn1 == -1 and sgn2 == 1)
    {
        i1->sign = 1;
        UnlimitedInt *r = sub(i2, i1);
        i1->sign = -1;
        return r;
    }
    else
    {
        if (i1->size >= i2->size)
        {
            UnlimitedInt *u = A(i1, i2);
            u->sign = sgn1;
            return u;
        }
        else
        {
            UnlimitedInt *u = A(i2, i1);
            u->sign = sgn1;
            return u;
        }
    }
    return nullptr;
}
UnlimitedInt *S(UnlimitedInt *i1, UnlimitedInt *i2)
{
    string s = "";
    int borrow = 0;
    int temp;
    int j = i1->get_size() - 1;
    int k = i2->get_size() - 1;
    while (j > 0 and k >= 0)
    {
        temp = i1->get_array()[j] - i2->get_array()[k] - borrow;
        if (temp >= 0)
        {
            borrow = 0;
            s = std::to_string(temp) + s;
        }
        else
        {
            borrow = 1;
            temp = temp + 10;
            s = std::to_string(temp) + s;
        }
        j--;
        k--;
    }
    if (j == 0 and k == 0)
    {
        temp = i1->get_array()[j] - i2->get_array()[k] - borrow;
        s = std::to_string(temp) + s;
    }
    else if (j >= 0 and k == -1)
    {
        while (j > 0)
        {
            temp = i1->get_array()[j] - borrow;
            if (temp >= 0)
            {
                borrow = 0;
                s = std::to_string(temp) + s;
            }
            else
            {
                borrow = 1;
                temp = temp + 10;
                s = std::to_string(temp) + s;
            }
            j--;
        }
        temp = i1->get_array()[j] - borrow;
        if (temp != 0)
        {
            s = std::to_string(temp) + s;
        }
    }
    intzck(s);
    UnlimitedInt *r = new UnlimitedInt(s);
    return r;
}
UnlimitedInt *UnlimitedInt::sub(UnlimitedInt *i1, UnlimitedInt *i2)
{
    int sgn1 = i1->sign;
    int sgn2 = i2->sign;
    if (sgn2 == 0)
    {
        UnlimitedInt *u = new UnlimitedInt(i1->to_string());
        u->sign = i1->sign;
        return u;
    }
    else if (sgn1 == 0)
    {
        UnlimitedInt *u = new UnlimitedInt(i2->to_string());
        u->sign = -1 * i2->sign;
        return u;
    }
    else if (sgn1 == -1 and sgn2 == 1)
    {
        i2->sign = -1;
        UnlimitedInt *r = add(i1, i2);
        i2->sign = 1;
        return r;
    }
    else if (sgn1 == 1 and sgn2 == -1)
    {
        i2->sign = 1;
        UnlimitedInt *r = add(i1, i2);
        i2->sign = -1;
        return r;
    }
    else
    {
        if (i1->size > i2->size)
        {
            UnlimitedInt *u = S(i1, i2);
            u->sign = sgn1;
            return u;
        }
        else if (i1->size < i2->size)
        {
            UnlimitedInt *u = S(i2, i1);
            u->sign = -sgn1;
            return u;
        }
        else
        {
            UnlimitedInt *u = S(i1, i2);
            if (u->sign == -1)
            {
                u = S(i2, i1);
                u->sign = -1;
            }
            return u;
        }
    }
    return nullptr;
}
UnlimitedInt *UnlimitedInt::mul(UnlimitedInt *i1, UnlimitedInt *i2)
{
    UnlimitedInt *u = new UnlimitedInt(0);
    int sgn1 = i1->sign;
    int sgn2 = i2->sign;
    if (sgn1 == 0 or sgn2 == 0)
    {
        return u;
    }
    int j = i1->size - 1;
    int k = i2->size - 1;
    int carry = 0;
    string s = "";
    string z = "";
    int temp, t;
    while (k > -1)
    {
        while (j > -1)
        {
            temp = (i1->unlimited_int[j]) * (i2->unlimited_int[k]) + carry;
            t = temp % 10;
            s = std::to_string(t) + s;
            carry = (temp - t) / 10;
            j--;
        }
        if (carry > 0)
        {
            s = std::to_string(carry) + s;
            carry = 0;
        }
        s = s + z;
        z = z + "0";
        UnlimitedInt *d = new UnlimitedInt(s); // oppourtunity
        UnlimitedInt *r = add(u, d);
        delete d;
        u->sign = r->sign;
        u->size = r->size;
        u->capacity = r->capacity;
        delete u->unlimited_int;
        u->unlimited_int = r->unlimited_int;
        k--;
        s = "";
        j = i1->size - 1;
    }
    u->sign = sgn1 * sgn2;
    return u;
}

UnlimitedInt *longdiv(UnlimitedInt *i1, UnlimitedInt *i2)
{ // just handles quotient
    int i = 0;
    string s = "";
    string res = "";
    while (i < i2->get_size())
    {
        s = s + to_string(i1->get_array()[i]);
        i++;
    }
    while (i <= i1->get_size())
    {
        UnlimitedInt *tempo = new UnlimitedInt(s), *t = new UnlimitedInt(s), *r, *mult; // oppourtunity
        int j = 1;
        while (t->get_sign() >= 0)
        {
            UnlimitedInt *J = new UnlimitedInt(j);
            mult = UnlimitedInt::mul(i2, J);
            delete J;
            delete t;
            t = UnlimitedInt::sub(tempo, mult);
            j++;
            delete mult;
        }
        r = UnlimitedInt::add(t, i2);
        delete t;
        delete tempo;
        if (r->get_sign() == 1)
        {
            s = r->to_string() + std::to_string(i1->get_array()[i]);
        }
        else if (r->get_sign() == 0)
        {
            s = std::to_string(i1->get_array()[i]);
        }
        delete r;
        j = j - 2;
        i++;
        if (res.length() > 0 or i == i1->get_size() or j > 0)
        { //!(res.length()==0 and i<i1->get_size() and j==0)
            res = res + to_string(j);
        }
    }
    intzck(res);
    UnlimitedInt *tem = new UnlimitedInt(res);
    return tem;
}

UnlimitedInt *rlongdiv(UnlimitedInt *i1, UnlimitedInt *i2)
{ // handles remainder accurately
    int i = 0;
    string s = "";
    string res = "";
    while (i < i2->get_size())
    {
        s = s + to_string(i1->get_array()[i]);
        i++;
    }
    while (i <= i1->get_size())
    {
        UnlimitedInt *tempo = new UnlimitedInt(s), *t = new UnlimitedInt(s), *r, *mult; // oppourtunity
        int j = 1;
        while (t->get_sign() >= 0)
        {
            UnlimitedInt *J = new UnlimitedInt(j);
            mult = UnlimitedInt::mul(i2, J);
            delete J;
            delete t;
            t = UnlimitedInt::sub(tempo, mult);
            j++;
            delete mult;
        }
        r = UnlimitedInt::add(t, i2);
        delete t;
        delete tempo;
        if (r->get_sign() == 1)
        {
            if (i < i1->get_size())
            {
                s = r->to_string() + std::to_string(i1->get_array()[i]);
            }
            else
            {
                s = r->to_string();
            }
        }
        else if (r->get_sign() == 0)
        {
            if (i < i1->get_size())
            {
                s = std::to_string(i1->get_array()[i]);
            }
            else
            {
                s = "0";
            }
        }
        delete r;
        j = j - 2;
        i++;
        if (res.length() > 0 or i == i1->get_size() or j > 0)
        { //!(res.length()==0 and i<i1->get_size() and j==0)
            res = res + to_string(j);
        }
    }
    intzck(s);
    UnlimitedInt *tem = new UnlimitedInt(s);
    return tem;
}
UnlimitedInt *UnlimitedInt::div(UnlimitedInt *i1, UnlimitedInt *i2)
{
    if (i2->sign != 0)
    {
        if (i1->sign == 0)
        {
            UnlimitedInt *u = new UnlimitedInt("0");
            return u;
        }
        else
        {
            int sgn1 = i1->sign;
            int sgn2 = i2->sign;
            i1->sign = 1;
            i2->sign = 1;
            UnlimitedInt *temp = sub(i1, i2), *tem, *r, *k;
            int subsgn = temp->sign, z;
            delete temp;
            if (subsgn >= 0)
            {
                tem = longdiv(i1, i2);
                r = rlongdiv(i1, i2);
                z = r->sign;
                delete r;
            }
            else
            {
                tem = new UnlimitedInt(0);
                if (sgn1 * sgn2 == -1)
                {
                    k = new UnlimitedInt(1);
                    r = add(tem, k);
                    delete k;
                    delete tem;
                    tem = r;
                }
                tem->sign = sgn1 * sgn2;
                i1->sign = sgn1;
                i2->sign = sgn2;
                return tem;
            }
            if (sgn1 * sgn2 == -1 and z != 0)
            {
                k = new UnlimitedInt(1);
                r = add(tem, k);
                delete k;
                delete tem;
                tem = r;
            }
            tem->sign = sgn1 * sgn2;
            i1->sign = sgn1;
            i2->sign = sgn2;
            return tem;
        }
    }
    return nullptr;
}
UnlimitedInt *UnlimitedInt::mod(UnlimitedInt *i1, UnlimitedInt *i2)
{
    UnlimitedInt *t1, *t2;
    t1 = div(i1, i2);
    t2 = mul(i2, t1);
    delete t1;
    t1 = sub(i1, t2);
    delete t2;
    return t1;
}
string UnlimitedInt::to_string()
{
    string s = "";
    for (int i = 0; i < size; i++)
    {
        s = s + std::to_string(unlimited_int[i]);
    }
    return s;
}
int UnlimitedInt::get_capacity()
{
    return capacity;
}
UnlimitedInt::UnlimitedInt(int *ulimited_int, int cap, int sgn, int sz)
{
    unlimited_int = ulimited_int;
    capacity = cap;
    sign = sgn;
    size = sz;
}
