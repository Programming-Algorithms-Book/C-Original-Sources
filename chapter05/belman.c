for (k = 1; k <= n - 2; k++)  /* повтаряме (n-2) пъти */
  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
      if (D[i] > D[j] + A[j][i])
        D[i] = D[j] + A[j][i];


