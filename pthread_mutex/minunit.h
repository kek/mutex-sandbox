#define mu_assert(message, test) do { if (!(test)) return message; } while (0)
#define mu_run_test(test) do { char *message = test(); tests_run++; \
                               if (message) return message; } while (0)
#define mu_run_tests_and_report() do { \
  char *result = all_tests(); \
  if (result != 0) { printf("%s\n", result); } \
  else { printf("ALL TESTS PASSED\n"); } \
  printf("Tests run: %d\n", tests_run); \
} while (0)

extern int tests_run;
