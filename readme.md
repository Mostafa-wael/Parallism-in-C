# Parallism in C 
- in this repository we will show the parallel version of the two given code snippets using pthreads, openMP, MPI and both MPI and openMP.

---
code1:

`i=0;`

`while(i <= n)
{
    A[i] += f(i);  
    i++;
}`

---
code2:

`for(int i = 0; i < n; i++)
`

`for(int j = 0; j < n; j++)
`

`A[i] += g(j,i);
`
---

  