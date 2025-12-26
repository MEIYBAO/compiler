// single line comment
/* multi
   line comment */

int a, b;
int i;
float f;
double d;
void *vp;

int arr[3];
int mat[2][2];

struct Point
{
    int x;
    int y;
};

struct Point p;
struct Point *pp;

a = 10;
b = a + 2 * 3 - 4 / 2 % 3 ^ 2;
f = 3.14;
d = .5 + 2. + 1e-3;

arr[0] = a;
mat[1][1] = b;

pp = &p;
pp->x = a;
p.y = b;
vp = &arr[0];

if (a >= b && !(a == 0) || b != 1)
{
    printf(a);
}
else
{
    scanf(b);
}

while (i < 10)
{
    i = i + 1;
}

for (i = 0; i <= 3; i = i + 1)
{
    a = a + i;
}

call(a, b, f, d);
return a;

@ // illegal char for ERRORCHAR screenshot
