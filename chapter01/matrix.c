/* Въвеждане по редове */
for (i = 0; i < m; i++)
  for (j = 0; j < n; j++) scanf("%d", &A[i][j]);

/* Въвеждане по стълбове */
for (i = 0; i < m; i++)
  for (j = 0; j < n; j++) scanf("%d", &A[j][i]);

/* Отпечатване на матрица по редове */
for (i = 0; i < m; i++) {
  for (j = 0; j < n; j++) printf("%.3d", A[i][j]);
  printf("\n");
}
