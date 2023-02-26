#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "sources/viewer.h"

START_TEST(test_parser) {
  t_info test_info = {{0, 0, 0, 0, 0, 0}, 0, 0, NULL, NULL};
  int flag = 0;
  double test_v[18] = {0,   0,   78, 45,  45, 0, 45, -45, 0,
                       -45, -45, 0,  -45, 45, 0, 0,  0,   -78};
  int test_f[54] = {0, 1, 1, 2, 2, 0, 0, 2, 2, 3, 3, 0, 0, 3, 3, 4, 4, 0,
                    0, 4, 4, 1, 1, 0, 5, 4, 4, 3, 3, 5, 5, 3, 3, 2, 2, 5,
                    5, 2, 2, 1, 1, 5, 5, 1, 1, 0, 0, 5, 5, 0, 0, 4, 4, 5};
  double *test_dup = (double *)malloc(18 * sizeof(double));

  flag = parse("xdd", &test_info);
  ck_assert_int_eq(flag, 0);

  flag = parse("objects/diamond.obj", &test_info);
  ck_assert_int_eq(flag, 1);
  ck_assert_int_eq(test_info.v_amount, 6);
  ck_assert_int_eq(test_info.f_amount, 27);
  for (size_t i = 0; i < test_info.v_amount * 3; i++) {
    ck_assert_double_eq(test_info.vertexes[i], test_v[i]);
  }
  for (size_t i = 0; i < test_info.f_amount * 2; i++) {
    ck_assert_int_eq(test_info.facets[i], test_f[i]);
  }
  v_dup(&test_info, test_dup);
  for (size_t i = 0; i < test_info.v_amount * 3; i++) {
    ck_assert_double_eq(test_info.vertexes[i], test_dup[i]);
  }
  free(test_dup);
  free(test_info.vertexes);
  free(test_info.facets);
}
END_TEST

START_TEST(test_translate) {
  double *test_v = (double *)malloc(9 * sizeof(double));
  test_v[0] = 0;
  test_v[1] = 0;
  test_v[2] = 0;
  test_v[3] = 1;
  test_v[4] = -2;
  test_v[5] = 3;
  test_v[6] = -4;
  test_v[7] = 5;
  test_v[8] = -6;
  ft_translate(test_v, 3, 0, -2);
  double result[9] = {-2, 0, 0, -1, -2, 3, -6, 5, -6};
  for (int i = 0; i < 9; i++) {
    ck_assert_double_eq(test_v[i], result[i]);
  }
  free(test_v);
}
END_TEST

START_TEST(test_ox_rotate) {
  double *test_v = (double *)malloc(9 * sizeof(double));
  test_v[0] = 0;
  test_v[1] = 0;
  test_v[2] = 0;
  test_v[3] = 1;
  test_v[4] = -2;
  test_v[5] = 3;
  test_v[6] = -4;
  test_v[7] = 5;
  test_v[8] = -6;
  ft_ox_rotate(test_v, 3, M_PI / 4);
  double result[9] = {0, 0, 0, 1, -3.53553, 0.707107, -4, 7.77817, -0.707107};
  for (int i = 0; i < 9; i++)
    ck_assert_double_eq_tol(test_v[i], result[i], 1e-5);
  free(test_v);
}
END_TEST

START_TEST(test_oy_rotate) {
  double *test_v = (double *)malloc(9 * sizeof(double));
  test_v[0] = 0;
  test_v[1] = 0;
  test_v[2] = 0;
  test_v[3] = 1;
  test_v[4] = -2;
  test_v[5] = 3;
  test_v[6] = -4;
  test_v[7] = 5;
  test_v[8] = -6;
  ft_oy_rotate(test_v, 3, M_PI / 4);
  double result[9] = {0, 0, 0, 2.82843, -2, 1.41421, -7.07107, 5, -1.41421};
  for (int i = 0; i < 9; i++)
    ck_assert_double_eq_tol(test_v[i], result[i], 1e-5);
  free(test_v);
}
END_TEST

START_TEST(test_oz_rotate) {
  double *test_v = (double *)malloc(9 * sizeof(double));
  test_v[0] = 0;
  test_v[1] = 0;
  test_v[2] = 0;
  test_v[3] = 1;
  test_v[4] = -2;
  test_v[5] = 3;
  test_v[6] = -4;
  test_v[7] = 5;
  test_v[8] = -6;
  ft_oz_rotate(test_v, 3, M_PI / 4);
  double result[9] = {0, 0, 0, 2.12132, -0.707107, 3, -6.36396, 0.707107, -6};
  for (int i = 0; i < 9; i++)
    ck_assert_double_eq_tol(test_v[i], result[i], 1e-5);
  free(test_v);
}
END_TEST

START_TEST(test_scale) {
  double *test_v = (double *)malloc(9 * sizeof(double));
  test_v[0] = 0;
  test_v[1] = 0;
  test_v[2] = 0;
  test_v[3] = 1;
  test_v[4] = -2;
  test_v[5] = 3;
  test_v[6] = -4;
  test_v[7] = 5;
  test_v[8] = -6;
  ft_scale(test_v, 3, 2);
  double result[9] = {0, 0, 0, 2, -4, 6, -8, 10, -12};
  for (int i = 0; i < 9; i++) {
    ck_assert_double_eq(test_v[i], result[i]);
  }
  free(test_v);
}
END_TEST

int main(void) {
  Suite *parser = suite_create("Parser test");
  Suite *transformations = suite_create("Transformations tests");

  TCase *onr = tcase_create("Open and read tests");
  tcase_add_test(onr, test_parser);
  TCase *translate = tcase_create("Translate");
  tcase_add_test(translate, test_translate);
  TCase *rotate_ox = tcase_create("Rotate_oX");
  tcase_add_test(rotate_ox, test_ox_rotate);
  TCase *rotate_oy = tcase_create("Rotate_oY");
  tcase_add_test(rotate_oy, test_oy_rotate);
  TCase *rotate_oz = tcase_create("Rotate_oZ");
  tcase_add_test(rotate_oz, test_oz_rotate);
  TCase *scale = tcase_create("Scale");
  tcase_add_test(scale, test_scale);

  suite_add_tcase(parser, onr);
  suite_add_tcase(transformations, translate);
  suite_add_tcase(transformations, rotate_ox);
  suite_add_tcase(transformations, rotate_oy);
  suite_add_tcase(transformations, rotate_oz);
  suite_add_tcase(transformations, scale);

  SRunner *runner = srunner_create(parser);
  srunner_add_suite(runner, transformations);

  srunner_run_all(runner, CK_NORMAL);
  int failed_count = srunner_ntests_failed(runner);
  srunner_free(runner);

  return failed_count == 0 ? 0 : 1;
}