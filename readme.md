# Parallism in C 
- In this repository we will show the parallel versions of the two given code snippets using pthreads, openMP, MPI and both MPI and openMP.

![image](https://user-images.githubusercontent.com/56788883/124506747-9ce12600-ddcc-11eb-819b-33d22665581d.png)


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

  
