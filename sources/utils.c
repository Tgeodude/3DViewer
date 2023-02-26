#include "viewer.h"

void info_init(t_info *info) {
  if (info->facets) free(info->facets);
  if (info->vertexes) free(info->vertexes);
  info->minMax[0] = DBL_MAX;
  info->minMax[1] = -DBL_MAX;
  info->minMax[2] = DBL_MAX;
  info->minMax[3] = -DBL_MAX;
  info->minMax[4] = DBL_MAX;
  info->minMax[5] = -DBL_MAX;
  info->v_amount = 0;
  info->f_amount = 0;
  info->facets = NULL;
  info->vertexes = NULL;
}

void v_dup(t_info *info, double *copy) {
  for (size_t i = 0; i < info->v_amount * 3; i++) copy[i] = info->vertexes[i];
}

void ft_minMax(double x, double y, double z, t_info *info) {
  if (x < info->minMax[0]) info->minMax[0] = x;
  if (x > info->minMax[1]) info->minMax[1] = x;
  if (y < info->minMax[2]) info->minMax[2] = y;
  if (y > info->minMax[3]) info->minMax[3] = y;
  if (z < info->minMax[4]) info->minMax[4] = z;
  if (z > info->minMax[5]) info->minMax[5] = z;
}
