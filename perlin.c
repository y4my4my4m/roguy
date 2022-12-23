
#ifndef PERLIN_H
#define PERLIN_H

float perlin(float x, float y) {
  int bx0, bx1, by0, by1, b00, b10, b01, b11;
  float rx0, rx1, ry0, ry1, q[2], sx, sy, a, b, u, v;
  register int i, j;

  if (start) {
    start = 0;
    init();
  }

  setup(0, bx0, bx1, rx0, rx1);
  setup(1, by0, by1, ry0, ry1);

  i = p[bx0];
  j = p[bx1];

  b00 = p[i + by0];
  b10 = p[j + by0];
  b01 = p[i + by1];
  b11 = p[j + by1];

  sx = s_curve(rx0);
  sy = s_curve(ry0);

#define at2(rx,ry) (rx * q[0] + ry * q[1])

  q[0] = g2[b00][0];
  q[1] = g2[b00][1];
  u = at2(rx0, ry0);
  q[0] = g2[b10][0];
  q[1] = g2[b10][1];
  v = at2(rx1, ry0);
  a = lerp(sx, u, v);

  q[0] = g
  q[0] = g2[b01][0];
  q[1] = g2[b01][1];
  u = at2(rx0, ry1);
  q[0] = g2[b11][0];
  q[1] = g2[b11][1];
  v = at2(rx1, ry1);
  b = lerp(sx, u, v);

  return lerp(sy, a, b);
}

#endif // PERLIN_H