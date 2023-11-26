/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "ulimitedrational.h"
UnlimitedRational *coprime_builder(UnlimitedInt *i1, UnlimitedInt *i2)
{
    UnlimitedInt *temp=nullptr, *g1=nullptr, *g2=nullptr, *D=nullptr, *temp1=nullptr, *temp2=nullptr;
    UnlimitedRational *R=nullptr;
    int sgn1, sgn2;
    sgn1 = i1->get_sign();
    sgn2 = i2->get_sign();
    if (sgn1 == 0)
    {
        g1 = new UnlimitedInt(0);
        g2 = new UnlimitedInt("1");
        R = new UnlimitedRational(g1, g2);
        return R;
    }
    if (sgn1 == -1)
    {
        temp = new UnlimitedInt(0);
        g1 = UnlimitedInt::sub(temp, i1);
        delete temp;
    }
    else
    {
        g1 = new UnlimitedInt(i1->to_string()); // no sign copying already>0
    }
    if (sgn2 == -1)
    {
        temp = new UnlimitedInt(0);
        g2 = UnlimitedInt::sub(temp, i2);
        delete temp;
    }
    else
    {
        g2 = new UnlimitedInt(i2->to_string()); // no sign copying already>0
    }
    while (g1->get_sign() == 1 and g2->get_sign() == 1)
    {
        D = UnlimitedInt::sub(g1, g2);
        if (D->get_sign() == 1)
        {
            temp = UnlimitedInt::mod(g1, g2);
            delete g1;
            g1 = temp;
        }
        else
        {
            temp = UnlimitedInt::mod(g2, g1);
            delete g2;
            g2 = temp;
        }
        delete D;
    }
    if (g1->get_sign() == 0)
    {
        temp1 = UnlimitedInt::div(i1, g2);
        temp2 = UnlimitedInt::div(i2, g2);
        delete g1;
        delete g2;
        g1 = temp1;
        g2 = temp2;
    }
    else
    {
        temp1 = UnlimitedInt::div(i1, g1);
        temp2 = UnlimitedInt::div(i2, g1);
        delete g1;
        delete g2;
        g1 = temp1;
        g2 = temp2;
    }
    R = new UnlimitedRational(g1, g2);
    return R;
}
UnlimitedRational::UnlimitedRational()
{
    p = new UnlimitedInt("0");
    q = new UnlimitedInt("1");
}
UnlimitedRational::UnlimitedRational(UnlimitedInt *num, UnlimitedInt *den)
{
    p = num;
    q = den;
    if (den->get_sign() == 0)
    {
        delete p;
        p = new UnlimitedInt("0");
    }
    else
    {
        UnlimitedInt *temp=nullptr, *g1=nullptr, *g2=nullptr, *D=nullptr, *temp1=nullptr, *temp2=nullptr;
        int sgn1, sgn2;
        sgn1 = p->get_sign();
        sgn2 = q->get_sign();
        if (sgn1 == 0)
        {
            g1 = new UnlimitedInt(0);
            g2 = new UnlimitedInt("1");
        }
        else
        {
            if (sgn1 == -1)
            {
                temp = new UnlimitedInt(0);
                g1 = UnlimitedInt::sub(temp, p);
                delete temp;
            }
            else
            {
                g1 = new UnlimitedInt(p->to_string()); // no sign copying already>0
            }
            if (sgn2 == -1)
            {
                temp = new UnlimitedInt(0);
                g2 = UnlimitedInt::sub(temp, q);
                delete temp;
            }
            else
            {
                g2 = new UnlimitedInt(q->to_string()); // no sign copying already>0
            }
            while (g1->get_sign() == 1 and g2->get_sign() == 1)
            {
                D = UnlimitedInt::sub(g1, g2);
                if (D->get_sign() == 1)
                {
                    temp = UnlimitedInt::mod(g1, g2);
                    delete g1;
                    g1 = temp;
                }
                else
                {
                    temp = UnlimitedInt::mod(g2, g1);
                    delete g2;
                    g2 = temp;
                }
                delete D;
            }
            if (g1->get_sign() == 0)
            {
                temp1 = UnlimitedInt::div(p, g2);
                temp2 = UnlimitedInt::div(q, g2);
                delete g1;
                delete g2;
                g1 = temp1;
                g2 = temp2;
            }
            else
            {
                temp1 = UnlimitedInt::div(p, g1);
                temp2 = UnlimitedInt::div(q, g1);
                delete g1;
                delete g2;
                g1 = temp1;
                g2 = temp2;
            }
        }
        delete p;
        p = g1;
        delete q;
        q = g2;
    }
}
UnlimitedRational::~UnlimitedRational()
{   
    delete p;
    delete q;
}
UnlimitedInt *UnlimitedRational::get_p()
{
    return p;
}
UnlimitedInt *UnlimitedRational::get_q()
{
    return q;
}
string UnlimitedRational::get_p_str()
{
    string s = p->to_string();
    if (p->get_sign() == -1)
    {
        s = "-" + s;
    }
    return s;
}
string UnlimitedRational::get_q_str()
{
    string s = q->to_string();
    if (q->get_sign() == -1)
    {
        s = "-" + s;
    }
    return s;
}
string UnlimitedRational::get_frac_str()
{
    string s = p->to_string() + "/" + q->to_string();
    if (p->get_sign() * q->get_sign() == -1)
    {
        s = "-" + s;
    }
    return s;
}
UnlimitedRational *UnlimitedRational::add(UnlimitedRational *i1, UnlimitedRational *i2)
{
    UnlimitedRational *r=nullptr;
    UnlimitedInt *u=nullptr, *temp1=nullptr, *temp2=nullptr, *temp3=nullptr;
    int sgn2 = i1->q->get_sign();
    int sgn4 = i2->q->get_sign();
    if (sgn2 == 0 or sgn4 == 0)
    {
        UnlimitedInt *u1, *u2;
        u1 = new UnlimitedInt("0");
        u2 = new UnlimitedInt("0");
        r->p = u1;
        r->q = u2;
        return r;
    }
    temp1 = UnlimitedInt::mul(i1->p, i2->q);
    temp2 = UnlimitedInt::mul(i2->p, i1->q);
    temp3 = UnlimitedInt::add(temp1, temp2);
    delete temp1;
    delete temp2;
    u = UnlimitedInt::mul(i1->q, i2->q);
    r = coprime_builder(temp3, u);
    delete u;
    delete temp3;
    return r;
}
UnlimitedRational *UnlimitedRational::sub(UnlimitedRational *i1, UnlimitedRational *i2)
{
    UnlimitedRational *r=nullptr;
    UnlimitedInt *u=nullptr, *temp1=nullptr, *temp2=nullptr, *temp3=nullptr;
    int sgn2 = i1->q->get_sign();
    int sgn4 = i2->q->get_sign();
    if (sgn2 == 0 or sgn4 == 0)
    {
        UnlimitedInt *u1, *u2;
        u1 = new UnlimitedInt("0");
        u2 = new UnlimitedInt("0");
        r->p = u1;
        r->q = u2;
        return r;
    }
    temp1 = UnlimitedInt::mul(i1->p, i2->q);
    temp2 = UnlimitedInt::mul(i2->p, i1->q);
    temp3 = UnlimitedInt::sub(temp1, temp2);
    delete temp1;
    delete temp2;
    u = UnlimitedInt::mul(i1->q, i2->q);
    r = coprime_builder(temp3, u);
    delete u;
    delete temp3;
    return r;
}
UnlimitedRational *UnlimitedRational::mul(UnlimitedRational *i1, UnlimitedRational *i2)
{
    UnlimitedRational *r=nullptr;
    UnlimitedInt *temp1=nullptr, *temp2=nullptr;
    int sgn2 = i1->q->get_sign();
    int sgn4 = i2->q->get_sign();
    if (sgn2 == 0 or sgn4 == 0)
    {
        UnlimitedInt *u1, *u2;
        u1 = new UnlimitedInt("0");
        u2 = new UnlimitedInt("0");
        r->p = u1;
        r->q = u2;
        return r;
    }
    temp1 = UnlimitedInt::mul(i1->p, i2->p);
    temp2 = UnlimitedInt::mul(i1->q, i2->q);
    r = coprime_builder(temp1, temp2);
    delete temp1;
    delete temp2;
    return r;
}
UnlimitedRational *UnlimitedRational::div(UnlimitedRational *i1, UnlimitedRational *i2)
{
    UnlimitedRational *r=nullptr;
    UnlimitedInt *temp1=nullptr, *temp2=nullptr;
    int sgn2 = i1->q->get_sign();
    int sgn3 = i2->p->get_sign();
    int sgn4 = i2->q->get_sign();
    if (sgn2 == 0 or sgn3 == 0 or sgn4 == 0)
    {
        UnlimitedInt *u1, *u2;
        u1 = new UnlimitedInt("0");
        u2 = new UnlimitedInt("0");
        r->p = u1;
        r->q = u2;
        return r;
    }
    temp1 = UnlimitedInt::mul(i1->p, i2->q);
    temp2 = UnlimitedInt::mul(i1->q, i2->p);
    r = coprime_builder(temp1, temp2);
    delete temp1;
    delete temp2;
    return r;
}