// semantic errors: undeclared and type misuse (simulated)
int a;

a = 1;
b = a + 2;   // b undeclared

if (a && (c < 3)) { // c undeclared
    printf(a);
}
