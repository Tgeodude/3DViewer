#include "viewer.h"

int parse(const char *fileName, t_info *info) {
  info_init(info);
  if (!vf_count(fileName, info)) return 0;
  if (!vf_parse(fileName, info)) return 0;
  return 1;
}

int vf_count(const char *fileName, t_info *info) {
  char *str = NULL;
  size_t n;

  FILE *fr = fopen(fileName, "r");
  if (!fr) return 0;
  while (getline(&str, &n, fr) != EOF) {
    if (str[0] == 'v' && str[1] == ' ')
      info->v_amount++;
    else if (str[0] == 'f' && str[1] == ' ') {
      int i = 2;
      while (str[i]) {
        if (isdigit(str[i])) {
          info->f_amount++;
          while (!isspace(str[i]) && str[i]) i++;
        } else
          i++;
      }
    }
  }
  fclose(fr);
  info->vertexes = (double *)malloc(info->v_amount * 3 * sizeof(double));
  info->facets = (int *)malloc(info->f_amount * 2 * sizeof(int));
  return 1;
}

int vf_parse(const char *fileName, t_info *info) {
  char *str = NULL;
  size_t n;
  double tmp_x, tmp_y, tmp_z;

  int v = 0;
  int f = 0;
  FILE *fr = fopen(fileName, "r");
  if (!fr) return 0;
  while (getline(&str, &n, fr) != EOF) {
    if (str[0] == 'v' && str[1] == ' ') {
      sscanf(str, "v %lf %lf %lf", &tmp_x, &tmp_y, &tmp_z);
      info->vertexes[v] = tmp_x;
      info->vertexes[v + 1] = tmp_y;
      info->vertexes[v + 2] = tmp_z;
      ft_minMax(tmp_x, tmp_y, tmp_z, info);
      v += 3;
    } else if (str[0] == 'f' && str[1] == ' ') {
      char *token, *tmpstr, *tofree;
      int tmpint;
      int start = f;
      tofree = tmpstr = strdup(str + 2);
      while ((token = strsep(&tmpstr, " "))) {
        for (size_t i = 0; i < strlen(token); i++) {
          if (token[i] == '/') {
            token[i] = 0;
            break;
          }
        }
        if (!token) continue;
        tmpint = atoi(token);
        if (!tmpint) continue;
        if (tmpint < 0)
          tmpint = info->v_amount - tmpint;
        else
          tmpint--;
        info->facets[f] = tmpint;
        f++;
        if (f != start + 1) {
          info->facets[f] = tmpint;
          f++;
        }
      }
      info->facets[f] = info->facets[start];
      f++;
      free(tofree);
    }
  }
  fclose(fr);
  return 1;
}
