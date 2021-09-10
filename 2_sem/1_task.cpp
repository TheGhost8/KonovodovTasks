#include <stdio.h>
#include <iostream>
#include <stdint.h>

class ComplexNumber
{
public:
    constexpr ComplexNumber() : re(0), im(0) {};
    constexpr ComplexNumber(int new_re, int new_im) : re(new_re), im(new_im) {};
    constexpr ComplexNumber(const ComplexNumber& copied_obj) : re(copied_obj.re), im(copied_obj.im) {};
    constexpr ComplexNumber(ComplexNumber&& copied_obj) : re(copied_obj.re), im(copied_obj.im) {};

    constexpr int GetRe() const { return re; };
    constexpr int GetIm() const { return im; };
    constexpr void SetRe(int new_re) { re = new_re; };
    constexpr void SetIm(int new_im) { im = new_im; };

    constexpr bool operator==(const ComplexNumber second) const { return (re == second.re) && (im == second.im); };

private:
    int re, im;
};

constexpr ComplexNumber Conjugate(const ComplexNumber& x)
{
    ComplexNumber res;
    res.SetRe(x.GetRe());
    res.SetIm(-x.GetIm());
    return res;
}

int main()
{
    constexpr ComplexNumber a(1, 2);
    constexpr ComplexNumber b(1, -2);
    constexpr auto c = Conjugate(a);
    static_assert(b == c, "failed");
}