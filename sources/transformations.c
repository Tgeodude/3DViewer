#include "viewer.h"

void ft_translate(double *vertexes, int v_amount, int axis, double d) {
  for (int i = 0; i <= v_amount * 3; i += 3) vertexes[i + axis] += d;
}

void ft_scale(double *vertexes, int v_amount, double x) {
  for (int i = 0; i < v_amount * 3; i++) vertexes[i] *= x;
}

void ft_ox_rotate(double *vertexes, int v_amount, double angle) {
  for (int i = 0; i < v_amount * 3; i += 3) {
    double y = vertexes[i + 1];
    double z = vertexes[i + 2];
    vertexes[i + 1] = y * cos(angle) - z * sin(angle);
    vertexes[i + 2] = y * sin(angle) + z * cos(angle);
  }
}

void ft_oy_rotate(double *vertexes, int v_amount, double angle) {
  for (int i = 0; i < v_amount * 3; i += 3) {
    double x = vertexes[i];
    double z = vertexes[i + 2];
    vertexes[i] = x * cos(angle) + z * sin(angle);
    vertexes[i + 2] = -x * sin(angle) + z * cos(angle);
  }
}
void ft_oz_rotate(double *vertexes, int v_amount, double angle) {
  for (int i = 0; i < v_amount * 3; i += 3) {
    double x = vertexes[i];
    double y = vertexes[i + 1];
    vertexes[i] = x * cos(angle) - y * sin(angle);
    vertexes[i + 1] = x * sin(angle) + y * cos(angle);
  }
}
