#include "aocutil.h"
#include <stdio.h>
#include <stdlib.h>
#include <uthash.h>

typedef enum Result_Type { IS_TRIPLET, IS_PAIR, IS_NONE } RESULT_TYPE;
struct Result {
  RESULT_TYPE result_type;
  int x;
  int y;
  int z;
};

void part1(const hashable_int *even_numbers, const hashable_int *odd_numbers);
void part2(const hashable_int *even_numbers, const hashable_int *odd_numbers);

static struct Result find_pair_sum(const hashable_int *head,
                                   const int value_to_find,
                                   const int exclude_nth) {
  struct Result result = {IS_NONE, -1, -1, -1};
  int i = 0;

  for (const hashable_int *val = head; val != NULL; val = val->hh.next) {
    if (i == exclude_nth)
      continue;
    hashable_int *difference = NULL;
    HASH_FIND_INT(head, &(int){value_to_find - val->value}, difference);
    i++;
    if (difference == NULL)
      continue;
    result.result_type = IS_PAIR;
    result.x = val->value;
    result.y = difference->value;
    break;
  }
  return result;
}

static struct Result find_triplet_sum(const hashable_int *head,
                                      const int value_to_find,
                                      const int exclude_nth,
                                      const hashable_int *alt_head) {
  struct Result result = {IS_NONE, -1, -1, -1};
  int i = 0;

  for (const hashable_int *val = head; val != NULL; val = val->hh.next) {
    if (i == exclude_nth)
      continue;
    int pair_sum_value_to_find = value_to_find - val->value;
    result = find_pair_sum(head, pair_sum_value_to_find, i);
    i++;
    if (result.result_type == IS_NONE && alt_head != NULL)
      result = find_pair_sum(alt_head, pair_sum_value_to_find, -1);
    if (result.result_type == IS_NONE)
      continue;
    result.result_type = IS_TRIPLET;
    result.z = val->value;
    break;
  }
  return result;
}

int main(void) {
  FILE *expenses = ensure_open("inputs/day1_p1.txt", "r");
  int expense = 0;
  hashable_int *odd_numbers = NULL;
  hashable_int *even_numbers = NULL;

  while (!feof(expenses)) {
    fscanf(expenses, "%d", &expense);
    hashable_int *report = malloc(sizeof(hashable_int));
    report->value = expense;
    if (expense % 2 == 0) {
      HASH_ADD_INT(even_numbers, value, report);
    } else {
      HASH_ADD_INT(odd_numbers, value, report);
    }
  }
  fclose(expenses);

  part1(even_numbers, odd_numbers);
  part2(even_numbers, odd_numbers);

  CLEAR_AND_DELETE(hashable_int, even_numbers);
  CLEAR_AND_DELETE(hashable_int, odd_numbers);
  return 0;
}

void part1(const hashable_int *even_numbers, const hashable_int *odd_numbers) {
  struct Result result = find_pair_sum(even_numbers, 2020, -1);

  if (result.result_type == IS_NONE)
    result = find_pair_sum(odd_numbers, 2020, -1);
  if (result.result_type == IS_NONE) {
    puts("Couldn't find it! Blame kame!");
  } else if (result.result_type == IS_PAIR) {
    printf("%d x %d = %d\n", result.x, result.y, result.x * result.y);
  }
}

void part2(const hashable_int *even_numbers, const hashable_int *odd_numbers) {
  struct Result result = find_triplet_sum(even_numbers, 2020, -1, NULL);

  if (result.result_type == IS_NONE)
    result = find_triplet_sum(even_numbers, 2020, -1, odd_numbers);
  if (result.result_type == IS_NONE) {
    puts("Couldn't find it! Blame kame!");
  } else if (result.result_type == IS_TRIPLET) {
    printf("%d x %d x %d = %d \n", result.x, result.x, result.z,
           result.x * result.y * result.z);
  }
}
