compiler := if os() == "android" { "gcc" } else { "zig cc" }

default:
    @just --list

build in out deps="":
    {{ compiler }} {{ in }} {{ deps }} -o {{ out }}

watch in deps="" out="tmp":
    #!/usr/bin/env bash

    set -euo pipefail

    name=$(basename $(dirname "{{ in }}"))
    dest="{{ out }}/${name}"

    watchexec --clear --exts c,h \
      "just build {{ in }} ${dest} '{{ deps }}' && echo '' && ./${dest}"

ch-01-19:
    just watch 01/19-sizeof/main.c

ch-02-01:
    just watch 02/01-structs/main.c munit/munit.c

ch-03-05:
    just watch 03/05-why-pointers/main.c \
      "03/05-why-pointers/coordinate.c munit/munit.c"

ch-03-06:
    just watch 03/06-pointer-basics/main.c \
      "03/06-pointer-basics/exercise.c munit/munit.c"

ch-03-09-test:
    just watch 03/09-arrays-as-pointers/test.c \
      "munit/munit.c"

ch-03-09-example:
    just watch 03/09-arrays-as-pointers/example.c

ch-03-11:
    just watch 03/11-array-casting/main.c

ch-03-13:
    just watch 03/13-arrays-decay-to-pointers/main.c

ch-03-14-example:
    just watch 03/14-c-strings/main.c

ch-03-14-test:
    just watch 03/14-c-strings/test.c \
      "03/14-c-strings/exercise.c munit/munit.c"

ch-03-15-example:
    just watch 03/15-c-string-library/main.c

ch-03-15-test:
    just watch 03/15-c-string-library/test.c \
      "03/15-c-string-library/exercise.c munit/munit.c"

ch-03-16-test:
    just watch 03/16-forward-declarations/test.c \
      "03/16-forward-declarations/exercise.c munit/munit.c"

ch-03-17-test:
    just watch 03/17-mutual-structs/test.c \
      "03/17-mutual-structs/exercise.c munit/munit.c"

ch-04-01-test:
    just watch 04/01-enums/test.c \
      "04/01-enums/exercise.c munit/munit.c"

ch-04-02-test:
    just watch 04/02-non-default-values/test.c \
      "munit/munit.c"

ch-04-03-test:
    just watch 04/03-switch/test.c \
      "04/03-switch/exercise.c munit/munit.c"

ch-04-04-example:
    just watch 04/04-sizeof-enum/main.c

ch-05-01-test:
    just watch 05/01-union/test.c \
      "05/01-union/exercise.c munit/munit.c"

ch-05-02-example:
    just watch 05/02-memory-layout/main.c

ch-05-05-example:
    just watch 05/05-helper-fields/main.c

ch-05-05-test:
    just watch 05/05-helper-fields/test.c \
      "munit/munit.c"

ch-06-01-example:
    just watch 06/01-the-stack/main.c

ch-06-03-example:
    just watch 06/03-stack-overflow/main.c

ch-06-04-example:
    just watch 06/04-pointers-to-the-stack/main.c

ch-06-05-test:
    just watch 06/05-the-heap/test.c \
      "06/05-the-heap/exercise.c munit/munit.c"

ch-06-06-test:
    just watch 06/06-malloc/test.c \
      "06/06-malloc/exercise.c munit/munit.c"

ch-06-07-example:
    just watch 06/07-free/main.c \
      "06/07-free/exercise.c"

ch-07-01-test:
    just watch 07/01-pointer-pointers/test.c \
      "07/01-pointer-pointers/exercise.c munit/munit.c"

ch-07-01-example:
    just watch 07/01-pointer-pointers/main.c

ch-07-02-test:
    just watch 07/02-array-of-pointers/test.c \
      "07/02-array-of-pointers/exercise.c munit/munit.c"

ch-07-03-test:
    just watch 07/03-void-pointers/test.c \
      "07/03-void-pointers/exercise.c munit/munit.c"

ch-07-03-example:
    just watch 07/03-void-pointers/main.c

ch-07-04-test:
    just watch 07/04-swapping-integers/test.c \
      "07/04-swapping-integers/exercise.c munit/munit.c"

ch-07-05-test:
    just watch 07/05-swapping-strings/test.c \
      "07/05-swapping-strings/exercise.c munit/munit.c"

ch-07-06-test:
    just watch 07/06-generic-swap/test.c \
      "07/06-generic-swap/exercise.c munit/munit.c"

ch-07-06-example:
    just watch 07/06-generic-swap/main.c

ch-08-01-test:
    just watch 08/01-low-level-stack/test.c \
      "08/01-low-level-stack/snekstack.c munit/munit.c"

ch-08-02-test:
    just watch 08/02-stack-push/test.c \
      "08/02-stack-push/snekstack.c munit/munit.c"
