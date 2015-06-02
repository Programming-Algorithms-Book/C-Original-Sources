for (i = 0; i < m; i++)
  for (j = 0; j < p; j++) {
    C[i][j] = 0;
    for (k = 0; k < n; k++) C[i][j] += A[i][k] * B[k][j];
  }
