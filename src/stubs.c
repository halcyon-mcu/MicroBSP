void memcpy(void *dest, const void *src, unsigned int n) {
  unsigned char *d = (unsigned char *)dest;
  const unsigned char *s = (const unsigned char *)src;

  for (unsigned int i = 0; i < n; i++) {
    d[i] = s[i];
  }
}

void memzero(void *s, unsigned int n) {
  unsigned char *p = (unsigned char *)s;

  for (unsigned int i = 0; i < n; i++) {
    p[i] = 0;
  }
}
